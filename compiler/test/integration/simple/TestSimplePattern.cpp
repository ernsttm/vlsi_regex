//
// Created by todd on 11/26/18.
//

#include "TestSimplePattern.h"

namespace integration_test {

const std::string FILE_PREFIX = "../test/integration/simple/";

const std::string A_FILE = "a.vpp";
const std::string A_REGEX = "a";

const std::string TEST_FILE = "test.vpp";
const std::string TEST_REGEX = "test";

void TestSimplePattern::SetUp() {
  createSimulation(A_FILE, A_REGEX);
  createSimulation(TEST_FILE, TEST_REGEX);
}

TEST_F(TestSimplePattern, aBasicMatch) {
  std::vector<RegexResult> results = execSimulation(A_FILE, FILE_PREFIX + "aBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(0, results[0].end);
}

TEST_F(TestSimplePattern, aTwoMatches) {
  std::vector<RegexResult> results = execSimulation(A_FILE, FILE_PREFIX + "aTwoMatches.txt");

  ASSERT_EQ(2, results.size());
  ASSERT_EQ(2, results[0].start);
  ASSERT_EQ(2, results[0].end);
  ASSERT_EQ(6, results[1].start);
  ASSERT_EQ(6, results[1].end);
}

TEST_F(TestSimplePattern, aNoMatches) {
  std::vector<RegexResult> results = execSimulation(A_FILE, FILE_PREFIX + "aNoMatches.txt");

  ASSERT_EQ(0, results.size());
}

TEST_F(TestSimplePattern, testBasicMatch) {
  std::vector<RegexResult> results = execSimulation(TEST_FILE, FILE_PREFIX + "testBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(3, results[0].end);
}

TEST_F(TestSimplePattern, testFailSucceed) {
  std::vector<RegexResult> results = execSimulation(TEST_FILE, FILE_PREFIX + "testFailSucceed.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(5, results[0].start);
  ASSERT_EQ(8, results[0].end);
}

TEST_F(TestSimplePattern, testMultipleFailures) {
  std::vector<RegexResult> results = execSimulation(TEST_FILE, FILE_PREFIX + "testMultipleFailures.txt");

  ASSERT_EQ(0, results.size());
}

}