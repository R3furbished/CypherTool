#include "vigenere.h"
VEC_OF_PAIRS generate_pairs(std::string key, std::string text) {
  VEC_OF_PAIRS pair_vec{};
  int key_index = 0;

  for (int i = 0; i < text.size(); i++) {
    if (text.at(i) != ' ') {
      pair_vec.push_back({text.at(i), key.at(key_index % 7)});
      key_index++;
    } else
      pair_vec.push_back({' ', ' '});
  }
  return pair_vec;
}

void encrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec) {
  int first = pair.first;
  if (first == 32)
    return_vec.push_back(char(32));
  else {
    int second = pair.second;
    // Move first letter by that much forward even if it loops back;
    int alphabet_value = (first + second) % 26;
    char result = (char)(alphabet_value + 65);
    // Add the resulting letter to RESULTING_TEXT vector;
    return_vec.push_back(result);
  }
}

void decrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec) {
  int first = pair.first;
  if (first == 32)
    return_vec.push_back(char(32));
  else {
    int second = pair.second;
    // Need to beware of modulos of negative numbers;
    int difference = (first - second);
    int alphabet_value;
    difference >= 0 ? alphabet_value = (difference) % 26
                    : alphabet_value = (26 + (difference));
    char result = (char)(alphabet_value + 65);
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
