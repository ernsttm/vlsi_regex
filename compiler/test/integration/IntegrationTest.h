//
// Created by todd on 11/29/18.
//

#ifndef TEST_REGEX_COMPILER_INTEGRATION_INTEGRATIONTEST_H_
#define TEST_REGEX_COMPILER_INTEGRATION_INTEGRATIONTEST_H_

#include <gtest/gtest.h>

namespace integration_test {

struct RegexResult {
  int start;
  int end;
};

class IntegrationTest : public ::testing::Test {
 protected:
  /**
   * Remove trailing and leading whitespace from the given string.
   *
   * @param str the string to trim.
   * @return the trimmed string.
   */
  std::string trim(const std::string& str);

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

#endif //TEST_REGEX_COMPILER_INTEGRATION_INTEGRATIONTEST_H_
