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
        return VERSION_NOT_SUPPORTED;
    }

    url = DecodeURL(url);
    url = StripQueryParams(url);

    //  httptest will contain all the files the server serves
    url.insert(0, "..");

    bool is_dir = false;
    if (std::filesystem::is_directory(url)) {
        url += ROOT_FILE;
        is_dir = true;
    }

    //  Loading the requested file
    std::fstream targetFile;
    targetFile.open(url, std::ios::in);

    //  If it doesn't open we handle the error
    if (!targetFile.is_open()) {
        if (is_dir) {
            if (!is_head) {
                return FORBIDDEN + FORBIDDEN_BODY;
            }

            return FORBIDDEN;
        }

        //  For now we assume that every time a file doesn't open, it's a bad request
        return NOT_FOUND;
    }

    targetFile.close();

    // If everything is good we load the file
    auto res = ReadFile(url);

    //  Preparing and sending the response
    std::string response = RESPONSE_OK + GetDate() + "\r\n";;
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
        return NOT_FOUND;
    }

    bool is_head = false;
    if (method != HEAD && method != GET) {
        return NOT_IMPLEMENTED;
    }

    if (method == HEAD) {
        is_head = true;
    }

    return GetResponse(requestLine, url, is_head);
}
