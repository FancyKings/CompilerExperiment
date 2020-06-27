//
// Created by FancyKing on 2020/3/30.
//

#include "scanner.hpp"

int main() {

    // D:\Code\CompilerExperiment\resources\main.cpp
    std::string file_path = R"(D:\Code\CompilerExperiment\resources\main.cpp)";
    cout << "Please input file FULL PATH: ";
    cin >> file_path;
    lexicalAnalyze(file_path);

    return 0;
}