//
// Created by todd on 11/29/18.
//

#include "IntegrationTest.h"

#include "compiler/Compiler.h"
#include "parser/Parser.h"

namespace integration_test {

std::string IntegrationTest::trim(const std::string &str) {
  std::string trimmedStr { };

  for (char c : str) {
    if ('0' <= c && c <= '9') {
      trimmedStr += c;
    }
  }

  return trimmedStr;
}

void IntegrationTest::createSimulation(const std::string& fileName, const std::string& regex) {
  std::string tempName = fileName + "_temp.v";

  compiler::Parser parser { };
  std::shared_ptr<compiler::Codon> root = parser.parse(regex);
  std::shared_ptr<compiler::Compiler> module = compiler::Compiler::compile(root);
  compiler::Compiler::output(tempName, module);

  std::stringstream command { };
  command << "iverilog -o " << fileName << " " << tempName << " ../test/integration/test_main.v";
  system(command.str().c_str());
}

std::vector<RegexResult> IntegrationTest::execSimulation(const std::string& simulationFile,
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

}
