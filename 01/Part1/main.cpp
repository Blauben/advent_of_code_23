#include <cstdio>
#include <iostream>
#include <fstream>
#include <regex>
#include "main.h"

int main() {
    std::fstream file;
    file.open("../sample.txt", std::ios::in);
    if(!file.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return 1;
    }
    std::string line;
    int sum{0};
    while(std::getline(file, line)) {
        add_calibration_number(line, sum);
    }

    std::cout << "Calibration number sum: " << std::to_string(sum) << std::endl;
    return 0;
}

void add_calibration_number(const std::string& line, int& acc) {
    if(line.empty()) {
        return;
    }
    std::smatch matches;
    std::regex first_digit{".*?(\\d)"};
    std::regex last_digit{"(\\d)[^\\d]*$"};

    if(std::regex_search(line, matches, first_digit)) {
        acc += std::stoi(matches[1].str()) * 10;
    }
    if(std::regex_search(line, matches, last_digit)) {
        acc += std::stoi(matches[1].str());
    }
}