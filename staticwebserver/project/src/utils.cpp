#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

#include "utils.hpp"

std::string GetDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    char dateMessage[24];

    std::strftime(dateMessage, sizeof(dateMessage), "%a, %d %b %Y %T %Z", &tm);

    return std::string{dateMessage};
}

std::string DecodeURL(const std::string &url) {
    std::string decoded_url;

    for (int i = 0; i < url.size(); i++) {
        if (url[i] == '%') {
            decoded_url += static_cast<char>(strtoll(url.substr(i + 1, 2).c_str(), nullptr, 16));

            i += 2;
        } else {
            decoded_url += url[i];
        }
    }

    return decoded_url;
}
std::string ReadFile(const std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);

    std::stringstream fl;
    if (file.is_open()) {
        fl << file.rdbuf();
    }

    file.close();

    return fl.str();
}

std::vector<std::string> Tokenize(const std::string &s, const std::string &del = " ") {
    std::vector<std::string> res;

    int start = 0;
    int end = s.find(del);

    while (end != -1) {
        res.push_back(s.substr(start, end - start));

        start = end + del.size();
        end = s.find(del, start);
    }

    res.push_back(s.substr(start, end - start));

    return res;
}
std::string StripQueryParams(const std::string &s) {
    auto tokens = Tokenize(s, "/");

    auto last = tokens[tokens.size() - 1];

    auto checkParams = last.rfind('?');

    if (checkParams != -1) {
        last = last.substr(0, checkParams);
    }

    std::string newPath;
    for (auto i = 0; i < tokens.size() - 1; i++) {
        newPath += tokens[i] + "/";
    }
    newPath += last;

    return newPath;
}

std::string ParseMime(const std::string &s) {
    auto xs = s.substr(s.rfind('.'), s.size());

    if (xs == ".html") {
        return "text/html";
    }

    if (xs == ".js") {
        return "application/javascript";
    }

    if (xs == ".css") {
        return "text/css";
    }

    if (xs == ".jpg") {
        return "image/jpeg";
    }

    if (xs == ".jpeg") {
        return "image/jpeg";
    }

    if (xs == ".png") {
        return "image/png";
    }

    if (xs == ".gif") {
        return "image/gif";
    }

    if (xs == ".swf") {
        return "application/x-shockwave-flash";
    }

    return "none";
}