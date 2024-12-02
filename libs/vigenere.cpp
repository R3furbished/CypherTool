#include "vigenere.h"

const int SPACE_BAR = 32;
const int ALPHABETE_SIZE = 26;
const int ASCII_VALUE_OF_A = 65;

VEC_OF_PAIRS generate_pairs(std::string key, std::string text) {
  VEC_OF_PAIRS pair_vec{};
  int key_index = 0;
  int key_size = key.size();

  for (int i = 0; i < text.size(); i++) {
    if (text.at(i) != ' ') {
      pair_vec.push_back({text.at(i), key.at(key_index % key_size)});
      key_index++;
    } else
      pair_vec.push_back({' ', ' '});
  }
  return pair_vec;
}

void encrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec) {
  int first = pair.first;
  if (first == SPACE_BAR)
    return_vec.push_back(char(SPACE_BAR));
  else {
    int second = pair.second;
    // Move first letter by that much forward even if it loops back;
    int alphabet_value = (first + second) % ALPHABETE_SIZE;
    char result = (char)(alphabet_value + ASCII_VALUE_OF_A);
    // Add the resulting letter to RESULTING_TEXT vector;
    return_vec.push_back(result);
  }
}

void decrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec) {
  int first = pair.first;
  if (first == SPACE_BAR)
    return_vec.push_back(char(SPACE_BAR));
  else {
    int second = pair.second;
    // Need to beware of modulos of negative numbers;
    int difference = (first - second);
    int alphabet_value;
    difference >= 0 ? alphabet_value = (difference) % ALPHABETE_SIZE
                    : alphabet_value = (ALPHABETE_SIZE + (difference));
    char result = (char)(alphabet_value + ASCII_VALUE_OF_A);
    // Add the resulting letter to RESULTING_TEXT vector;
    return_vec.push_back(result);
  }
}
void encrypt_parallel(int start_index, int end_index, const VEC_OF_PAIRS &vec,
                      std::vector<char> &output) {
  for (int i = start_index; i < end_index; i++) {
    encrypt_pair(vec.at(i), output);
  }
}

void decrypt_parallel(int start_index, int end_index, const VEC_OF_PAIRS &vec,
                      std::vector<char> &output) {
  for (int i = start_index; i < end_index; i++) {
    decrypt_pair(vec.at(i), output);
  }
}
