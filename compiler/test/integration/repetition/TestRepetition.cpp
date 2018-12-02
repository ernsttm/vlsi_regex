//
// Created by todd on 11/30/18.
//

#include "TestRepetition.h"

namespace integration_test {

const std::string FILE_PREFIX = "../test/integration/repetition/";

const std::string AREP_FILE = "arep.vpp";
const std::string AREP_REGEX = "a+";

void TestRepetition::SetUp() {
  createSimulation(AREP_FILE, AREP_REGEX);
}

TEST_F(TestRepetition, aBasicMatch) {
  std::vector<RegexResult> results = execSimulation(AREP_FILE, FILE_PREFIX + "aBasicMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(0, results[0].start);
  ASSERT_EQ(3, results[0].end);
}

TEST_F(TestRepetition, aEndMatch) {
  std::vector<RegexResult> results = execSimulation(AREP_FILE, FILE_PREFIX + "aEndMatch.txt");

  ASSERT_EQ(1, results.size());
  ASSERT_EQ(3, results[0].start);
  ASSERT_EQ(3, results[0].end);
}

TEST_F(TestRepetition, aMultipleMatch) {
  std::vector<RegexResult> results = execSimulation(AREP_FILE, FILE_PREFIX + "aMultipleMatch.txt");

  ASSERT_EQ(3, results.size());
  ASSERT_EQ(2, results[0].start);
  ASSERT_EQ(3, results[0].end);
  ASSERT_EQ(6, results[1].start);
  ASSERT_EQ(9, results[1].end);
  ASSERT_EQ(13, results[2].start);
  ASSERT_EQ(13, results[2].end);
}

TEST_F(TestRepetition, aNoMatch) {
  std::vector<RegexResult> results = execSimulation(AREP_FILE, FILE_PREFIX + "aNoMatch.txt");

  ASSERT_EQ(0, results.size());
}

}