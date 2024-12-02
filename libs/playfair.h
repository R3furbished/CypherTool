#ifndef PLAYFAIR_H
#define PLAYFAIR_H
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#define ASCII_START 65
#define ASCII_END 90
#define GRID_SIZE 5

namespace Playfair {

struct ValidPair{
  char first;
  char second;
  int x_first;
  int x_second;
  int y_first;
  int y_second;
  std::string rule;
};

std::vector<char> build_grid(const std::string& key);

std::vector<ValidPair> generate_pairs(const std::vector<char> &grid, const std::string &text_input);

std::string encrypt(const std::string &key, const std::string& text);
std::string decrypt(const std::string &key, const std::string& text);


}
#endif // !PLAYFAIR_H
