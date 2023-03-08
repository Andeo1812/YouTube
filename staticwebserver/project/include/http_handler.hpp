#pragma once

#include <string>

class HTTPHandler {
 public:
  std::string handle(const std::string &request) const;
};
