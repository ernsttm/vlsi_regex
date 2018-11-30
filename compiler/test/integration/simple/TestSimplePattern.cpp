//
// Created by todd on 11/26/18.
//

#include <cstdlib>

#include "TestSimplePattern.h"

#include "compiler/Compiler.h"
#include "parser/Parser.h"

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

std::string TestSimplePattern::trim(const std::string &str) {
  std::string trimmedStr { };

  for (char c : str) {
    if ('0' <= c && c <= '9') {
      trimmedStr += c;
    }
  }

  return trimmedStr;
}

void TestSimplePattern::createSimulation(const std::string& fileName, const std::string& regex) {
  static const std::string tempName = fileName + "_temp.v";

  compiler::Parser parser { };
  std::shared_ptr<compiler::Codon> root = parser.parse(regex);
  std::shared_ptr<compiler::Compiler> module = compiler::Compiler::compile(root);
  compiler::Compiler::output(tempName, module);

  std::stringstream command { };
  command << "iverilog -o " << fileName << " " << tempName << " ../test/integration/test_main.v";
  system(command.str().c_str());
}

std::vector<RegexResult> TestSimplePattern::execSimulation(const std::string& simulationFile,
                                                           const std::string& inputFile) {
  std::string buffer;
  buffer.resize(25);
  std::stringstream command { };
  command << "vvp " << simulationFile << " +DATA_FILE=" << inputFile;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.str().c_str(), "r"), pclose);
  if (!pipe) {
    throw std::runtime_error { "popen() failed!" };
  }

  std::vector<RegexResult> results;
  while (fgets((char*)buffer.data(), (int)buffer.size(), pipe.get()) != nullptr) {
    std::string start = trim(buffer.substr(0, buffer.find(',')));
    std::string end = trim(buffer.substr(buffer.find(',')));
    RegexResult result { std::atoi(start.c_str()), std::atoi(end.c_str()) };
    results.push_back(result);
  }

  return results;
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