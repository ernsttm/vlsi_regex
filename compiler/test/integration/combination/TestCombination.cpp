//
// Created by todd on 12/2/18.
//

#include "TestCombination.h"

namespace integration_test {

const std::string FILE_PREFIX = "../test/integration/combination/";

const std::string REP_FINAL_FILE = "rep_final.vpp";
const std::string REP_FINAL_REGEX = "test.(ab)+";

const std::string SIMPLE_FINAL_FILE = "simple_final.vpp";
const std::string SIMPLE_FINAL_REGEX = "(ab)+.test";

void TestCombination::SetUp() {
  createSimulation(REP_FINAL_FILE, REP_FINAL_REGEX);
  createSimulation(SIMPLE_FINAL_FILE, SIMPLE_FINAL_REGEX);
}

TEST_F(TestCombination, repFinalBasicMatch) {
  std::vector<RegexResult> results = execSimulation(REP_FINAL_FILE, FILE_PREFIX + "repFinalBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(6, results[0].end);
}

TEST_F(TestCombination, repFinalRepeat) {
  std::vector<RegexResult> results = execSimulation(REP_FINAL_FILE, FILE_PREFIX + "repFinalRepeat.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(4, results[0].start);
  ASSERT_EQ(12, results[0].end);
}

TEST_F(TestCombination, repFinalNoMatch) {
  std::vector<RegexResult> results = execSimulation(REP_FINAL_FILE, FILE_PREFIX + "repFinalNoMatch.txt");

  ASSERT_EQ(0, results.size());
}

TEST_F(TestCombination, simpleFinalBasicMatch) {
  std::vector<RegexResult> results = execSimulation(SIMPLE_FINAL_FILE, FILE_PREFIX + "simpleFinalBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(6, results[0].end);
}

TEST_F(TestCombination, simpleFinalRepeatMatch) {
  std::vector<RegexResult> results = execSimulation(SIMPLE_FINAL_FILE, FILE_PREFIX + "simpleFinalRepeatMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(3, results[0].start);
  ASSERT_EQ(11, results[0].end);
}

TEST_F(TestCombination, simpleFinalNoMatch) {
  std::vector<RegexResult> results = execSimulation(SIMPLE_FINAL_FILE, FILE_PREFIX + "simpleFinalNoMatch.txt");
}

}