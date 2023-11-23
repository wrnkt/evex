#ifndef EVEX_H
#define EVEX_H

#include <string>
#include <unordered_map>

typedef enum {
  L_PAREN,
  R_PAREN,
  MINUS,
  PLUS,
  SLASH,
  STAR,
  //
  NUMBER,
} TOKEN_TYPE;

struct token_t {
  TOKEN_TYPE type;
  std::string lexeme;
  std::size_t loc;
};

const std::unordered_map<char, TOKEN_TYPE> TOKEN_MAP = {
  {'(', L_PAREN },
  {')', R_PAREN },
  {'-', MINUS },
  {'+', PLUS },
  {'/', SLASH },
  {'*', STAR },
};

#endif // EVEX_H
