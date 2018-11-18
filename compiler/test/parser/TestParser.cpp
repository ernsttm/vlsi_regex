//
// Created by todd on 11/18/18.
//

#include <gtest/gtest.h>

#include "parser/Parser.h"

namespace parser_test {

TEST(parser_test, simplePattern) {
  std::string regEx = "test";

  compiler::Parser parser { };
  std::shared_ptr<compiler::Codon> root = parser.parse(regEx);

  ASSERT_EQ(compiler::CodonType::ROOT, root->type());
  ASSERT_EQ("", root->pattern());

  std::vector<std::shared_ptr<compiler::Codon>> children = root->children();
  ASSERT_EQ(1, children.size());
  std::shared_ptr<compiler::Codon> child = children[0];

  ASSERT_EQ(compiler::CodonType::PATTERN, child->type());
  ASSERT_EQ(regEx, child->pattern());

  ASSERT_TRUE(child->children().empty());
}

}
