cd ./build/
++ -std=c++20 ../src/main.cpp ../libs/vigenere.cpp -o vigenere `../../WxWidgetsSrc/wxWidgets-3.2.6/MacBuild/wx-config --cxxflags --libs`
cd ..
./build/vigenere d SEGREDO "`cat result`"

