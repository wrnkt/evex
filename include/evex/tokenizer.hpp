#include <cstddef>
#include <unordered_map>
#include <vector>

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
};
