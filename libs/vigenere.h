#ifndef _VIGENERE_

#define _VIGENERE_

#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

typedef std::vector<std::pair<char, char> > VEC_OF_PAIRS;

VEC_OF_PAIRS generate_pairs(std::string key, std::string text);

void encrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec);

void decrypt_pair(std::pair<char, char> pair, std::vector<char> &return_vec);

void encrypt_parallel(int start_index, int end_index, const VEC_OF_PAIRS &vec,
                      std::vector<char> &output);

void decrypt_parallel(int start_index, int end_index, const VEC_OF_PAIRS &vec,
                      std::vector<char> &output);
#endif // !_VIGENERE_
