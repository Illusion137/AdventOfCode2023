#include "../utils.h"
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#define FILE_PATH "Day3/input.txt"
#define SCHEMATIC_WIDTH 140

std::string schematic[140];

inline bool isinbounds(size_t pos){ return pos >= 0 && pos < SCHEMATIC_WIDTH; }
inline bool issymbol(char c){ return !isdigit(c) && c != '.'; }

bool has_close_symbol1(int row, int lbound, int rbound){
    const int distance = (rbound - lbound) + 1;

    //Check Sides
    if(isinbounds(lbound - 1) && issymbol( schematic[row][lbound - 1] ) ) return true;
    if(isinbounds(rbound + 1) && issymbol( schematic[row][rbound + 1] ) ) return true;

    if(isinbounds(row-1)){ // Check top row
        if(isinbounds(lbound - 1) && issymbol(schematic[row-1][lbound-1]) ) return true;
        for(int i = 0; i < distance; i++)
            if(issymbol(schematic[row-1][lbound + i]) ) return true;
        if(isinbounds(rbound + 1) && issymbol(schematic[row-1][rbound+1]) ) return true;
    }

    if(isinbounds(row+1)){ // Check bottom row
        if(isinbounds(lbound - 1) && issymbol(schematic[row+1][lbound-1]) ) return true;
        for(int i = 0; i < distance; i++)
            if(issymbol(schematic[row+1][lbound + i]) ) return true;
        if(isinbounds(rbound + 1) && issymbol(schematic[row+1][rbound+1]) ) return true;
    }
    return false;
}

size_t part1(){
    size_t sum_part_nums = 0;
    for(int r = 0; r < SCHEMATIC_WIDTH; r++){
        int lbound = 0, rbound = 0;
        for(int c = 0; c < SCHEMATIC_WIDTH; c++){
            if(schematic[r][c] == '.') continue;
            if(isdigit(schematic[r][c])){
                lbound = c, rbound = c;
                while( isinbounds(rbound + 1) && isdigit( schematic[r][rbound+1] ) ) {rbound++; c++;};
                // printf("[%d:%d]\n", lbound, rbound);
                if(has_close_symbol1(r, lbound, rbound)) {
                    int dist = (rbound - lbound) + 1;
                    std::string num; num.reserve(dist);
                    for(int i = 0; i < dist; i++) num += schematic[r][lbound + i];
                    
                    sum_part_nums += std::atoi(num.c_str());
                }
            }
        }
    }
    return sum_part_nums;
}
size_t part2(){
    typedef std::pair<int, std::vector<int>> Gear;
    std::vector<Gear> gears;
    size_t gear_ratio_sum = 0;

    for(auto& gear : gears){
        if(gear.second.size() == 2){
            gear_ratio_sum += gear.second[0] * gear.second[1];
        }
    }
    return gear_ratio_sum;
}

int main(int argc, char **argv){
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    //load schematic    
    for(int i = 0; i < SCHEMATIC_WIDTH; std::getline(stream, schematic[i++]));
    stream.close();
    printf("Part 1: %zu\n", part1());
    stream.seekg(stream.beg);
    printf("Part 2: %zu\n", part2());
    return 0;
}