#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "http_handler.hpp"
#include "utils.hpp"
#include "responses.hpp"
#include "constants.hpp"

std::string GetResponse(std::stringstream &requestLine, std::string &url, bool is_head) {
    std::string version;

    std::getline(requestLine, version, ' ');

    if (version != HTTP_1_1 && version != HTTP_1_0) {
        //  std::cout << version << "\n";

        std::string response = VERSION_NOT_SUPPORTED;
        return response;
    }

    url = DecodeURL(url);
    url = StripQueryParams(url);

    url.insert(0, ".."); // httptest will contain all the files the server serves

    bool is_dir = false;
    if (std::filesystem::is_directory(url)) {
        url += ROOT_FILE;
        is_dir = true;
    }

    // Loading the requested file
    std::fstream targetFile;
    targetFile.open(url, std::ios::in);

    if (!targetFile.is_open()) {// if it doesn't open we handle the error
        if (is_dir) {
            std::cerr << "Failed to load index.html in dir path" << std::endl;

            std::string response = FORBIDDEN;
            if (!is_head) {
                response += FORBIDDEN_BODY;
            }
            return response;
        }

        //  std::cerr << "Failed to load the file" << std::endl;
        // for now we assume that every time a file doesn't open, it's a bad request
        return NotFound();
    }

    // If everything is good we load the file
    auto res = ReadFile(url);

    // Preparing and sending the response
    std::string response = Head();
    auto length = res.size();

    response = response + CONTENT_LENGTH + " " + std::to_string(length);;
    if (!is_head) {
        if (std::filesystem::is_regular_file(url)) {
            response += "\r\n" + CONTENT_TYPE + " " + ParseMime(url);
        }

        response += "\r\n\r\n" + res;
    } else {
        response += "\r\n\r\n";
    }

    return response;
}
std::string HTTPHandler::handle(const std::string &request) const {
    // Parsing
    std::stringstream reqStream(request);
    std::string line;
    std::getline(reqStream, line);

    std::stringstream requestLine(line);
    std::string method;
    std::getline(requestLine, method, ' ');

    std::string url;

    std::getline(requestLine, url, ' ');

    if (url.find("../") != std::string::npos) {
        return NotFound();
    }

    bool is_head = false;
    if (method != HEAD && method != GET) {
        return NotImplemented();
    }

    if (method == HEAD) {
        is_head = true;
    }

    return GetResponse(requestLine, url, is_head);
}
