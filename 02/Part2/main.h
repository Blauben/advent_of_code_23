//
// Created by balthazar on 02.12.23.
//

#ifndef INC_01_MAIN_H
#define INC_01_MAIN_H

#include <vector>
#include <string>

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

struct Draw {
    unsigned red_count{0};
    unsigned blue_count{0};
    unsigned green_count{0};
};

using MinCubeCount = Draw;

std::vector<Draw> parseGameStr(std::string_view);
std::vector<std::string> splitStrByDelim(std::string_view, char);
Draw constructDraw(const std::string&);

int parseGameIndex(const std::string&);
unsigned powerOfGame(const std::vector<Draw> &draws);
MinCubeCount calculateMinCount(const std::vector<Draw>&);

#endif //INC_01_MAIN_H
