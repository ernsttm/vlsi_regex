//
// Created by todd on 11/18/18.
//

#include "parser/Parser.h"

#include "parser/ParserException.h"

namespace compiler {

std::shared_ptr<Codon> Parser::parse(std::string regExpr) {
  // First create the root node
  std::shared_ptr<Codon> rootNode = std::make_shared<Codon>(CodonType::ROOT, "", false);

  // Iterate through the expression from the back to front, since the rear character defines how the preceding
  // characters should be interpreted.  Since the regular expression is being parsed from back to front, the first
  // codon detected will be the final one interpreted.
  bool final = true;
  std::shared_ptr<Codon>& currentRoot = rootNode;
  int index = (int)(regExpr.size() - 1);
  while (index >= 0) {
    char c = regExpr[index];

    if (standardCharacter(c)) {
      std::string pattern = getPattern(regExpr, index);
      index -= pattern.size();
      std::shared_ptr<Codon> patternCodon = std::make_shared<Codon>(CodonType::PATTERN, pattern, final);
      currentRoot->addChild(patternCodon);
    } else if ('.' == c) {
      index -= 1;
      std::shared_ptr<Codon> wildcardCodon = std::make_shared<Codon>(CodonType::WILDCARD, "", final);
      currentRoot->addChild(wildcardCodon);
    } else if ('+' == c) {
      index -= 1;

      if (regExpr[index] == ')') {
        index -= 1;
      }

      std::string pattern = getPattern(regExpr, index);
      index -= pattern.size();
      std::shared_ptr<Codon> repetitionCodon = std::make_shared<Codon>(CodonType::REPITITION, pattern, final);
      currentRoot->addChild(repetitionCodon);

      if (regExpr[index] == '(') {
        index -= 1;
      }
    } else {
      std::string errorMessage = "Unsupported character : ";
      throw ParserException(errorMessage + c);
    }

    final = false;
  }

  return rootNode;
}

std::string Parser::getPattern(std::string regExpr, int start) {
  std::string pattern;

  char c = regExpr[start];
  while (standardCharacter(c) && start >= 0) {
    pattern.insert(0, 1, c);
    c = regExpr[--start];
  }

  return pattern;
}

bool Parser::standardCharacter(char c) {
  return (('0' <= c && c <= '9') || ('A' <= c && c <='Z') || ('a' <= c && c <= 'z'));
}

}