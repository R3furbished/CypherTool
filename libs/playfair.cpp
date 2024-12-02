#include "playfair.h"
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<char> Playfair::build_grid(const std::string &key) {
  // I use a map here for faster look ups
  // to check if letter is already added.
  // TODO::decide wether or not to keep the map;
  std::unordered_map<char, int> unique_letters_from_key{};
  std::vector<char> ordered_grid;

  int index{};
  for (char c : key) {
    char upper = std::toupper(c);
    if (!unique_letters_from_key.contains(upper)) {
      unique_letters_from_key.insert({upper, index});
      ordered_grid.push_back(upper);
      index++;
    }
  }

  // I = 73 J = 74
  if (unique_letters_from_key.contains('J')) {
    for (int i = ASCII_START; i < ASCII_END + 1; i++) {
      // skip over the letter I
      if (i != 73) {
        if (!unique_letters_from_key.contains((char)i)) {
          ordered_grid.push_back((char)i);
        }
      }
    }
  } else {
    for (int i = ASCII_START; i < ASCII_END + 1; i++) {
      // skip over the letter J
      if (i != 74) {
        if (!unique_letters_from_key.contains((char)i)) {
          ordered_grid.push_back((char)i);
        }
      }
    }
  }
  return ordered_grid;
}

std::vector<char> parse_input(const std::string &input) {
  // TODO::test if this implementatio works;
  std::vector<char> filtred_input{};
  filtred_input.push_back(std::toupper(input[0]));
  for (int i = 1; i < input.size(); i++) {
    char upper_input = std::toupper(input[i]);
    if (input[i] != ' ') {
      if (upper_input == filtred_input[i - 1]) {
        filtred_input.push_back('X');
        filtred_input.push_back(upper_input);
      } else {
        filtred_input.push_back(upper_input);
      }
      // If we dont have even size we need
      // to add an X to create the last pair;
      if (i == input.size() - 1) {
        if (filtred_input.size() % 2 != 0) {
          filtred_input.push_back('X');
        }
      }
    }
  }
  return filtred_input;
}
int index_of(const char &letter, const std::vector<char> &grid) {
  // The first if clauses are here to satisfy I and J
  // behaving like the same letter
  if (letter == 'I') {
    for (int i{}; i < grid.size(); i++) {
      if (grid[i] == letter || grid[i] == 'J') {
        return i;
      }
    }
  } else if (letter == 'J') {
    for (int i{}; i < grid.size(); i++) {
      if (grid[i] == letter || grid[i] == 'I') {
        return i;
      }
    }
  } else {
    for (int i{}; i < grid.size(); i++) {
      if (grid[i] == letter) {
        return i;
      }
    }
  }

  return -1;
}

std::string get_pair_rule(int x_first, int y_first, int x_second,
                          int y_second) {
  std::string rule{};
  if (x_first == x_second) {
    rule += "same_row";
  } else if (y_first == y_second) {
    rule += "same_col";
  } else {
    rule += "square";
  }
  return rule;
}

std::vector<Playfair::ValidPair>
Playfair::generate_pairs(const std::vector<char> &grid,
                         const std::string &text_input) {
  std::vector<ValidPair> pairs;
  //
  std::vector<char> parsed_input = parse_input(text_input);

  for (int i{}; i < parsed_input.size(); i += 2) {
    char first_letter = parsed_input[i];
    char second_letter = parsed_input[i + 1];
    int first_index = index_of(first_letter, grid);
    int second_index = index_of(second_letter, grid);
    ValidPair pair;
    pair.first = first_letter;
    pair.second = second_letter;
    pair.x_first = first_index / GRID_SIZE;
    pair.y_first = first_index % GRID_SIZE;
    pair.x_second = second_index / GRID_SIZE;
    pair.y_second = second_index % GRID_SIZE;
    pair.rule =
        get_pair_rule(pair.x_first, pair.y_first, pair.x_second, pair.y_second);
    pairs.push_back(pair);
  }

  return pairs;
}

std::string Playfair::decrypt(const std::string &key, const std::string &text) {

  std::vector<char> grid = build_grid(key);
  std::vector<Playfair::ValidPair> pairs = generate_pairs(grid, text);

  std::string decrypted_text{};

  for (ValidPair pair : pairs) {
    if (pair.rule == "same_row") {
      int y_first;
      int y_second;

      // Need to watch out for negative values when it wraps around;
      (pair.y_first - 1) < 0 ? y_first = (pair.y_first - 1) + GRID_SIZE
                             : y_first = (pair.y_first - 1) % GRID_SIZE;

      (pair.y_second - 1) < 0 ? y_second = (pair.y_second - 1) + GRID_SIZE
                              : y_second = (pair.y_second - 1) % GRID_SIZE;

      char letter_1 = grid[(pair.x_first * GRID_SIZE) + y_first];

      decrypted_text += letter_1;

      char letter_2 = grid[(pair.x_second * GRID_SIZE) + y_second];

      decrypted_text += letter_2;

    } else if (pair.rule == "same_col") {
      int x_first;
      int x_second;
      // Need to watch out for negative values when it wraps around;
      (pair.x_first - 1) < 0 ? x_first = (pair.x_first - 1) + GRID_SIZE
                             : x_first = (pair.x_first - 1) % GRID_SIZE;
      (pair.x_second - 1) < 0 ? x_second = (pair.x_second - 1) + GRID_SIZE
                              : x_second = (pair.x_second - 1) % GRID_SIZE;

      char letter_1 = grid[(x_first * GRID_SIZE) + pair.y_first];

      decrypted_text += letter_1;

      char letter_2 = grid[(x_second * GRID_SIZE) + pair.y_second];

      decrypted_text += letter_2;

    } else {
      char letter_1 = grid[(pair.x_first * GRID_SIZE) + pair.y_second];

      decrypted_text += letter_1;

      char letter_2 = grid[(pair.x_second * GRID_SIZE) + pair.y_first];

      decrypted_text += letter_2;
    }
  }
  std::cout << decrypted_text << "\n";
  return decrypted_text;
}

std::string Playfair::encrypt(const std::string &key, const std::string &text) {

  std::vector<char> grid = build_grid(key);
  std::vector<Playfair::ValidPair> pairs = generate_pairs(grid, text);

  std::string encrypted_text{};

  for (ValidPair pair : pairs) {
    // This loop uses the formula "X * GRID_SIZE + Y" to get X and Y from
    // vector index;
    if (pair.rule == "same_row") {
      int y_first = (pair.y_first + 1) % GRID_SIZE;
      int y_second = (pair.y_second + 1) % GRID_SIZE;

      char letter_1 = grid[(pair.x_first * GRID_SIZE) + y_first];

      encrypted_text += letter_1;

      char letter_2 = grid[(pair.x_second * GRID_SIZE) + y_second];

      encrypted_text += letter_2;

    } else if (pair.rule == "same_col") {
      int x_first = (pair.x_first + 1) % GRID_SIZE;
      int x_second = (pair.x_second + 1) % GRID_SIZE;

      char letter_1 = grid[(x_first * GRID_SIZE) + pair.y_first];

      encrypted_text += letter_1;

      char letter_2 = grid[(x_second * GRID_SIZE) + pair.y_second];

      encrypted_text += letter_2;

    } else {
      char letter_1 = grid[(pair.x_first * GRID_SIZE) + pair.y_second];

      encrypted_text += letter_1;

      char letter_2 = grid[(pair.x_second * GRID_SIZE) + pair.y_first];

      encrypted_text += letter_2;
    }
  }
  std::cout << encrypted_text << "\n";
  return encrypted_text;
}

int main() {
  std::string key = "SEGREDO";
  std::string text = "YCAPVHSGLCPWNCRDBOPI";
  Playfair::decrypt(key, text);
  return 0;
}
