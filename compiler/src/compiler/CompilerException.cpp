//
// Created by todd on 11/18/18.
//

#include "compiler/CompilerException.h"

namespace compiler {

CompilerException::CompilerException(const std::string& msg)
    : msg_ { msg } { }

const char* CompilerException::what() const noexcept {
  return msg_.c_str();
}

}