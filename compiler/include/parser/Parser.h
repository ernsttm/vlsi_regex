//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_PARSER_PARSER_H_
#define REGEX_COMPILER_PARSER_PARSER_H_

#include <memory>
#include <string>

#include "parser/Codon.h"

namespace compiler {

/**
 * The class responsible for taking an input string and translating it into a set of Regular expression codons.
 */
class Parser {
 public:
  /**
   * Create a Parser instance.
   */
  Parser() = default;

  /**
   * Take the given regular expression and decompose it into an Abstract Syntax Tree of regular expression codons. In
   * the backend of the compiler this AST can then be composed into instructions in a verilog module.
   *
   * @param regExpr the regular expression to decompose.
   * @return the head of the AST (containing a "ROOT" node CodonType).
   * @throws ParserException if unable to decompose the given string.
   */
  std::shared_ptr<Codon> parse(std::string regExpr);

  ~Parser() = default;

 private:
  // Iterate through the regex until a non-standard character is discovered, or regExpr is empty.
  // This useful for getting the pattern strings, once the codon type is known.
  std::string getPattern(std::string regExpr, int start);

  // return true if c is a standard character (i.e. 0-9, a-z, or A-Z), otherwise return false.
  bool standardCharacter(char c);
};

}

#endif //REGEX_COMPILER_PARSER_PARSER_H_
