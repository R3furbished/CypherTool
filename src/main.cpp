#include "../libs/vigenere.h"
#include <functional>
#include <thread>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 4)
    return EXIT_FAILURE;

  // Take 2 inputs : key & text;
  char *operation = argv[1];
  std::string key = argv[2];
  std::string text = argv[3];
  //
  // Create Pairs vector;
  const VEC_OF_PAIRS vector_of_pairs = generate_pairs(key, text);
  int size_to_mid = vector_of_pairs.size() / 2;
  //
  // Create Result vectors for threads;
  std::vector<char> thread1_arr;
  std::vector<char> thread2_arr;
  //
  if (*operation == 'e') {
    // Spawn extra threads;
    std::thread thread1(encrypt_parallel, 0, size_to_mid,
                        std::ref(vector_of_pairs), std::ref(thread1_arr));
    std::thread thread2(encrypt_parallel, size_to_mid, vector_of_pairs.size(),
                        std::ref(vector_of_pairs), std::ref(thread2_arr));
    //
    // Join threads;
    thread1.join();
    thread2.join();
  } else if (*operation == 'd') {
    // Spawn extra threads;
    std::thread thread1(decrypt_parallel, 0, size_to_mid,
                        std::ref(vector_of_pairs), std::ref(thread1_arr));
    std::thread thread2(decrypt_parallel, size_to_mid, vector_of_pairs.size(),
                        std::ref(vector_of_pairs), std::ref(thread2_arr));
    //
    // Join threads;
    thread1.join();
    thread2.join();
  }
  //
  // Agregate the result
  std::vector<char> result;
  result.insert(result.end(), thread1_arr.begin(), thread1_arr.end());
  result.insert(result.end(), thread2_arr.begin(), thread2_arr.end());
  //
  // Publish Result
  for(char c : result){
    std::cout << c << " ";
  }
  std::cout<<"\n";

}
