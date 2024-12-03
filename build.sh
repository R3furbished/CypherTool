cd ./build/
g++ -std=c++20 ../src/main.cpp ../libs/vigenere.cpp ../libs/playfair.cpp -o program `../../WxWidgetsSrc/wxWidgets-3.2.6/MacBuild/wx-config --cxxflags --libs`
cd ..

