#include <cstddef>
#include <optional>
#include <unordered_map>
#include <vector>
#include <string>

#include "./evex.hpp"

class tokenizer_t
{
  public:
    tokenizer_t();
    ~tokenizer_t();

    tokenizer_t(std::string src);

  private:
    std::string src;
    std::vector<token_t> tokens;

    size_t start { 0 };
    size_t current { start };

    bool at_end();
    char advance();
    std::optional<token_t> scan_token();
};
