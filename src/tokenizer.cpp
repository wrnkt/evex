#include "evex/tokenizer.hpp"

std::unordered_map<char, TOKEN_TYPE> TOKEN_MAP = {
  {'(', L_PAREN },
  {')', R_PAREN },
  {'-', MINUS },
  {'+', PLUS },
  {'/', SLASH },
  {'*', STAR },
};

tokenizer_t::tokenizer_t() {}
tokenizer_t::~tokenizer_t() {}

tokenizer_t::tokenizer_t(std::string src)
{
  this->src = src;
}

bool tokenizer_t::at_end() {
  return current >= src.size();
}
