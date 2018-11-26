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

void TestSimplePattern::SetUp() {
  createSimulation(A_FILE, A_REGEX);
}

void TestSimplePattern::createSimulation(const std::string& fileName, const std::string& regex) {
  static const std::string TEMP_NAME = "Temp.v";

  compiler::Parser parser { };
  std::shared_ptr<compiler::Codon> root = parser.parse(regex);
  std::shared_ptr<compiler::Compiler> module = compiler::Compiler::compile(root);
  compiler::Compiler::output(TEMP_NAME, module);

  std::stringstream command { };
  command << "iverilog -o " << fileName << " " << TEMP_NAME << " ../test/integration/test_main.v";
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
    std::string start = buffer.substr(0, buffer.find(','));
    std::string end = buffer.substr(buffer.find(','));
    RegexResult result { std::atoi(start.c_str()), std::atoi(end.c_str()) };
    results.push_back(result);
  }

  return results;
}

TEST_F(TestSimplePattern, aBasicMatch) {
  std::vector<RegexResult> results = execSimulation(A_FILE, FILE_PREFIX + "aBasicMatch.txt");

  ASSERT_TRUE(true);
}

}