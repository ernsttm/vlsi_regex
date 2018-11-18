//
// Created by todd on 11/18/18.
//

#include "parser/ParserException.h"

namespace compiler {

ParserException::ParserException(const std::string &msg) : msg_ { msg } { }

const char *ParserException::what() const noexcept {
  return msg_.c_str();
}

}