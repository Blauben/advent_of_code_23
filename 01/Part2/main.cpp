#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "main.h"

int main() {
    std::fstream file;
    file.open("../sample.txt", std::ios::in);
    if (!file.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return 1;
    }
    std::string line;
    int sum{0};
    while (std::getline(file, line)) {
        add_calibration_number(line, sum);
    }

    std::cout << "Calibration number sum: " << std::to_string(sum) << std::endl;
    return 0;
}

void add_calibration_number(const std::string &line, int &acc) {
    if (line.empty()) {
        return;
    }
    std::smatch matches;
    std::regex first_digit{".*?(\\d|one|two|three|four|five|six|seven|eight|nine)"};
    std::regex last_digit{
            "(\\d|one|two|three|four|five|six|seven|eight|nine)(?!.*(\\d|one|two|three|four|five|six|seven|eight|nine))"};

    if (std::regex_search(line, matches, first_digit)) {
        acc += parse_string_num(matches[1].str()) * 10;
    }
    if (std::regex_search(line, matches, last_digit)) {
        acc += parse_string_num(matches[0].str());
    }
}

int parse_string_num(const std::string& match) {
    static std::unordered_map<std::string, int> conversion{{"one",   1},
                                                           {"two",   2},
                                                           {"three", 3},
                                                           {"four",  4},
                                                           {"five",  5},
                                                           {"six",   6},
                                                           {"seven", 7},
                                                           {"eight", 8},
                                                           {"nine",  9}};
    try {
        return conversion.at(match);
    } catch (std::out_of_range&) {
        return std::stoi(match);
    }
}