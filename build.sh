cd ./build/
g++ -std=c++20 ../src/main.cpp ../libs/vigenere.cpp -o vigenere
cd ..
./build/vigenere d SEGREDO "`cat result`"
