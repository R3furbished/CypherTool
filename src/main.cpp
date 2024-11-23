#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

typedef std::vector<std::pair<char, char>> VEC_OF_PAIRS;

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

int main() {
  VEC_OF_PAIRS boas = generate_pairs(std::string("SEGREDO"),
                                     std::string("TREINO DE CRIPTOGRAFIA"));

  for (auto pair : boas) {
    std::cout << pair.first << "|" << pair.second << " ";
  }
  std::cout << std::endl;
  std::string enc_text{};
  std::vector<char> encrypted{};
  for (int i = 0; i < boas.size(); i++) {
    encrypt_pair(boas.at(i), encrypted);
  }
  for (char c : encrypted) {
    enc_text.push_back(c);
  }

  VEC_OF_PAIRS result = generate_pairs(std::string("SEGREDO"), enc_text);
  for (auto pair : result) {
    std::cout << pair.first << "|" << pair.second << " ";
  }
  std::cout << std::endl;

  std::vector<char> decrypted{};
  for (int i = 0; i < result.size(); i++) {
    decrypt_pair(result.at(i), decrypted);
  }
  for (char c : decrypted) {
    std::cout << c;
  }
  std::cout << std::endl;
  return 0;
}
