#include "evex/evex.hpp"
#include "evex/tokenizer.hpp"


tokenizer_t::tokenizer_t() {}
tokenizer_t::~tokenizer_t() {}

tokenizer_t::tokenizer_t(std::string src)
{
  this->src = src;
}

char tokenizer_t::advance()
{
  return this->src[this->current++];
}

bool tokenizer_t::at_end() {
  return current >= src.size();
}

std::optional<token_t> tokenizer_t::scan_token()
{
  char c = this->advance();
  auto it = TOKEN_MAP.find(c);

  if(it != TOKEN_MAP.end()) {
    return token_t {
      it->second,
      "",
      this->current
    };
  }
}
