//
// Created by todd on 11/18/18.
//

#include <parser/Codon.h>

#include "parser/Codon.h"

namespace compiler {

Codon::Codon(CodonType type, std::string pattern) : type_ { type }, pattern_ { pattern } { }

CodonType Codon::type() const {
  return type_;
}

std::string Codon::pattern() const {
  return pattern_;
}

std::vector<std::shared_ptr<Codon>> Codon::children() const {
  return children_;
}

void Codon::addChild(std::shared_ptr<Codon> child) {
  children_.push_back(child);
}

}