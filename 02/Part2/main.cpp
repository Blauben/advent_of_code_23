#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <queue>
#include "main.h"

int main() {
    std::fstream file;
    file.open("../sample.txt", std::ios::in);
    if(!file.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return 1;
    }
    unsigned sum{0};
    std::string line;
    while(std::getline(file, line)) {
        auto draws = parseGameStr(line);
        sum += powerOfGame(draws);
    }
    std::cout << "Power sum is " << sum << std::endl;
    return 0;
}

unsigned powerOfGame(const std::vector<Draw>& draws) {
    auto min = calculateMinCount(draws);
    return min.red_count * min.green_count * min.blue_count;
}

MinCubeCount calculateMinCount(const std::vector<Draw>& draws) {
    MinCubeCount min;
    for(auto draw : draws) {
        min.red_count = std::max(draw.red_count, min.red_count);
        min.blue_count = std::max(draw.blue_count, min.blue_count);
        min.green_count = std::max(draw.green_count, min.green_count);
    }
    return min;
}

std::string_view removeGamePrefix(std::string_view gameStr) {
    int begin = static_cast<int>(std::distance(gameStr.cbegin(), std::find_if(gameStr.cbegin(), gameStr.cend(), [](char c){return c == ':';})) + 1);
    return gameStr.substr(begin, gameStr.length()-begin);
}

std::vector<Draw> parseGameStr(std::string_view gameStr) {
    std::vector<std::string> drawStr = splitStrByDelim(removeGamePrefix(gameStr), ';');
    std::vector<Draw> draws(drawStr.size());
    std::transform(drawStr.begin(), drawStr.end(), draws.begin(), constructDraw);
    return draws;
}

std::vector<std::string> splitStrByDelim(const std::string_view str, char delim) {
    int idx{-1};
    // find start index, so that Game <num>: prefix is not in the tested sample anymore
    int start{0};
    std::vector<std::string> splitStr{};
    auto isDelim = [&delim](const char c){return c == delim;};
    while(str.cbegin() + start < str.cend()) {
        auto delimItr = std::find_if(str.cbegin() + start, str.cend(), isDelim);
        idx = static_cast<int>(std::distance(str.cbegin(), delimItr));
        splitStr.emplace_back(str.substr(start, idx - start));
        start = idx + 1;
        idx = -1;
    }
    return splitStr;
}

void setColorSample(Draw& draw, const std::string& color, int count);
std::vector<std::pair<std::string, int>> splitDrawIntoColorPair(const std::string&);

Draw constructDraw(const std::string& drawStr) {
    Draw sample;
    for(const auto& pair : splitDrawIntoColorPair(drawStr)) {
        setColorSample(sample, pair.first, pair.second);
    }
    return sample;
}

std::vector<std::pair<std::string, int>> splitDrawIntoColorPair(const std::string& drawStr) {
    static std::regex expr{R"((\d+) (red|blue|green))"};
    std::smatch clauses;
    std::vector<std::pair<std::string, int>> result{};
    for(const auto& substring : splitStrByDelim(drawStr, ',')) {
        std::regex_search(substring, clauses, expr);
        result.push_back(std::make_pair<std::string, int>(clauses[2], std::stoi(clauses[1])));
    }
    return result;
}


void setColorSample(Draw& draw, const std::string& color, int count) {
    if(color == "red") {
        draw.red_count = count;
    } else if(color == "blue") {
        draw.blue_count = count;
    } else if(color == "green") {
        draw.green_count = count;
    }
}

