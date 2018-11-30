//
// Created by todd on 11/29/18.
//

#include "TestWildcard.h"

namespace integration_test {

const std::string FILE_PREFIX = "../test/integration/wildcard/";

const std::string WILDCARD_FILE = "wildcard.vpp";
const std::string WILDCARD_REGEX = ".";

void TestWildcard::SetUp() {
  createSimulation(WILDCARD_FILE, WILDCARD_REGEX);
}

TEST_F(TestWildcard, wildcardBasicMatch) {
  std::vector<RegexResult> results = execSimulation(WILDCARD_FILE, FILE_PREFIX + "wildcardBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(0, results[0].end);
}

TEST_F(TestWildcard, wildcardDoubleMatch) {
  std::vector<RegexResult> results = execSimulation(WILDCARD_FILE, FILE_PREFIX + "wildcardDoubleMatch.txt");

  ASSERT_EQ(2, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(0, results[0].end);
  ASSERT_EQ(1, results[0].start);
  ASSERT_EQ(1, results[0].end);
}

TEST_F(TestWildcard, wildcardNoMatch) {
  std::vector<RegexResult> results = execSimulation(WILDCARD_FILE, FILE_PREFIX + "wildcardNoMatch.txt");

  ASSERT_EQ(0, results.size());
}

}