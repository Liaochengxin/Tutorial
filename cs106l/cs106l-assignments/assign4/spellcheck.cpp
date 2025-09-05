#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

namespace views = std::ranges::views;
template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  Corpus token;
  auto whitespace_position = find_all(source.begin(), source.end(), ::isspace);

  std::transform(whitespace_position.begin(), std::prev(whitespace_position.end()), 
      std::next(whitespace_position.begin()),
      std::inserter(token, token.end()),
      [&source](auto space_pos, auto next_space_pos){
          auto token_start = (space_pos==source.begin()) ? space_pos : std::next(space_pos);
          if(token_start < next_space_pos){
            return Token(source, space_pos, next_space_pos); 
            }
          return Token{source, source.end(), source.end()};
      });
  std::erase_if(token, [](const Token& t) { 
        return t.content.empty(); 
    });

  return token; 
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  auto mispelling_view = source 
    | views::filter([&](const Token& t){return !dictionary.contains(t.content); })
    | views::transform([&](const Token& t){
        auto suggestions_view = dictionary 
        | views::filter([&](const std::string& word){
          return levenshtein(t.content, word) == 1;
        });
        std::set<std::string> suggestions(
                suggestions_view.begin(),
                suggestions_view.end()
        );
    return Mispelling(t, suggestions);
    })
    | views::filter([](const Mispelling& m){ return !m.suggestions.empty(); });

  return {mispelling_view.begin(), mispelling_view.end()};
};

/* Helper methods */

#include "utils.cpp"
