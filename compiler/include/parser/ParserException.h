//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_PARSER_PARSEREXCEPTION_H_
#define REGEX_COMPILER_PARSER_PARSEREXCEPTION_H_

#include <exception>
#include <string>

namespace compiler {

/**
 * A custom exception for the parser namespace, allowing more restricted exception control flow statements.
 */
class ParserException : public std::exception {
 public:
  /**
   * Create an exception with the given error message.
   *
   * @param msg the error message.
   */
  explicit ParserException(const std::string& msg);

  /**
   * @return the cause of the thrown exception.
   */
  const char* what() const noexcept override;

 private:
  std::string msg_;
};

}

#endif //REGEX_COMPILER_PARSER_PARSEREXCEPTION_H_
