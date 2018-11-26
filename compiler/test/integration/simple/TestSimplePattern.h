//
// Created by todd on 11/26/18.
//

#ifndef TEST_REGEX_COMPILER_INTEGRATION_SIMPLE_TESTSIMPLEPATTERN_H_
#define TEST_REGEX_COMPILER_INTEGRATION_SIMPLE_TESTSIMPLEPATTERN_H_

#include <gtest/gtest.h>

namespace integration_test {

struct RegexResult {
  int start;
  int end;
};

class TestSimplePattern : public ::testing::Test {
 protected:
  void SetUp() override;

  /**
   * This method takes the regular expression, and compiles it into an executable with the given name.
   *
   * @param fileName the name of the executable file.
   * @param regex the regular expression to compile.
   */
  void createSimulation(const std::string& fileName, const std::string& regex);

  /**
   * Execute the simulation against the given input pattern, and return the standard output.
   *
   * @param simulationFile the simulation file to run.
   * @param inputFile the characters to run against the pattern.
   * @return the pairs of matching patterns detected.
   */
  std::vector<RegexResult> execSimulation(const std::string& simulationFile, const std::string& inputFile);
};

}

#endif //TEST_REGEX_COMPILER_INTEGRATION_SIMPLE_TESTSIMPLEPATTERN_H_
