//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_PARSER_CODON_H_
#define REGEX_COMPILER_PARSER_CODON_H_

#include <memory>
#include <string>
#include <vector>

namespace compiler {

enum class CodonType {
  /**
   * The root node of the regex parser tree.
   */
  ROOT,

  /**
   * A strict pattern.
   */
  PATTERN,

  /**
   * A wildcard acceptable.
   */
  WILDCARD,

  /**
   * A repeating pattern
   */
  REPITITION
};

class Codon {
 public:
  /**
   * Create a new codon in the parsed regular expression tree.
   *
   * @param type the CodonType this node represents.
   * @param pattern the characters informing the codon being created.
   * @param final if the codon is the last codon within the expression.
   */
  Codon(CodonType type, const std::string& pattern, bool final);

  /**
   * @return the CodonType this node represents.
   */
  CodonType type() const;

  /**
   * @return the characters informing the node being created.
   */
  std::string pattern() const;

  /**
   * @return true if the codon is the final pattern in the regular expression, false otherwise.
   */
  bool final() const;

  /**
   * @return the direct children of the Codon node.
   */
  std::vector<std::shared_ptr<Codon>> children() const;

  /**
   * Add the given Codon node to the set of children this node maintains.
   *
   * @param child the node to add.
   */
  void addChild(std::shared_ptr<Codon> child);

 private:
  const bool final_;
  const CodonType type_;
  const std::string pattern_;
  std::vector<std::shared_ptr<Codon>> children_;
};

}

#endif //REGEX_COMPILER_PARSER_CODON_H_
