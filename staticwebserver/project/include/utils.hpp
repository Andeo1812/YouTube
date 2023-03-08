#pragma once

#include <string>
#include "responses.hpp"

std::string DecodeURL(const std::string &url);
std::string DeadFile(const std::string &path);
std::vector<std::string> Tokenize(const std::string &s, const std::string &del);
std::string StripQueryParams(const std::string &s);

std::string ParseMime(const std::string &s);
std::string NotImplemented();
std::string NotFound();

std::string Head();
std::string GetDate();
