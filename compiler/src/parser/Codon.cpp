//
// Created by todd on 11/18/18.
//

#include <parser/Codon.h>

#include "parser/Codon.h"

namespace compiler {

Codon::Codon(CodonType type, const std::string& pattern, bool final)
    : type_ { type }, pattern_ { pattern }, final_ { final } { }

CodonType Codon::type() const {
  return type_;
}

std::string Codon::pattern() const {
  return pattern_;
}

bool Codon::final() const {
  return final_;
}

std::vector<std::shared_ptr<Codon>> Codon::children() const {
  return children_;
}

void Codon::addChild(std::shared_ptr<Codon> child) {
  children_.push_back(child);
}

}