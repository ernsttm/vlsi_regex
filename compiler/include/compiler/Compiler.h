//
// Created by todd on 11/18/18.
//

#ifndef REGEX_COMPILER_COMPILER_COMPILER_H_
#define REGEX_COMPILER_COMPILER_COMPILER_H_

#include <atomic>
#include <string>

#include "parser/Codon.h"

namespace compiler {

/**
 * An interface to defining capabilities of a compilation unit within the regular expression framework.
 */
class Compiler {
 public:
  /**
   * Create a Compiler, with a unique identifier.
   */
  Compiler();

  /**
   * Compile the given regular expression into a Verilog module which can be used to recognize the given pattern
   * within hardware (or a simulator).
   *
   * @param regexString the expression to compile into Verilog.
   * @throws std::invalid_argument if the regular expression doesn't conform to the constrained regular expression
   * definitions implemented in this project.
   */
   virtual void handleCodon(std::shared_ptr<Codon> codon) = 0;

   /**
    * @return the initialization text this module requires.
    */
   virtual std::string initializationText() = 0;

   /**
    * @return the combinational logic this module requires.
    */
   virtual std::string combinationalText() = 0;

   /**
    * @return the sequential logic this module requires.
    */
   virtual std::string sequentialText() = 0;

   virtual ~Compiler() = default;

   static std::shared_ptr<Compiler> compile(std::shared_ptr<Codon> codon);

 protected:
  // A protected constructor to make tests more repeatable
  explicit Compiler(uint patternId);

  const uint patternId_;

  static size_t incrementPatternSize(size_t size);

 private:
  static size_t PATTERN_SIZE;
  static std::atomic_uint PATTERN_COUNTER;
};

}

#endif //REGEX_COMPILER_COMPILER_COMPILER_H_
