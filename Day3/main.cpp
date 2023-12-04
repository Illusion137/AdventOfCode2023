#include "../utils.h"
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_set>

#define FILE_PATH "Day3/input.txt"
#define SCHEMATIC_WIDTH 140

std::string schematic[140];

inline bool isinbounds(size_t pos){ return pos >= 0 && pos < SCHEMATIC_WIDTH; }
inline bool issymbol(char c){ return !isdigit(c) && c != '.'; }

bool has_close_symbol(int row, int lbound, int rbound){
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

inline int get_number(int row, int lbound, int rbound){
    int dist = (rbound - lbound) + 1;
    std::string num; num.reserve(dist);
    for(int i = 0; i < dist; i++) num += schematic[row][lbound + i];
    
    return std::atoi(num.c_str());
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
                if(has_close_symbol(r, lbound, rbound)) {
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

typedef std::pair<int, std::vector<int>> Gear;

bool insert_into_gears(std::vector<Gear>& gears, int index, int number){
    int gear_index_in_gears = -1, i = 0;
    for(auto& gear : gears) {if(gear.first == index) gear_index_in_gears = i; i++;}
    if(gear_index_in_gears != -1){
        gears[gear_index_in_gears].second.push_back(number);
        return false;
    }
    gears.push_back( std::make_pair(index, std::vector<int>(1, number)) ); 
    return true;
}

inline int get_index(int row, int col){
    return (row * SCHEMATIC_WIDTH) + (col);
}

bool add_close_gears2(std::vector<Gear>& gears, int row, int lbound, int rbound){
    const int distance = (rbound - lbound) + 1;
    std::string num; num.reserve(distance);
    for(int i = 0; i < distance; i++) num += schematic[row][lbound + i];
    int number = std::atoi(num.c_str());
    //Check Sides
    if(isinbounds(lbound - 1) && schematic[row][lbound - 1] == '*' ) 
        insert_into_gears(gears, get_index(row, lbound - 1), number);
    if(isinbounds(rbound + 1) && schematic[row][rbound + 1] == '*' ) 
        insert_into_gears(gears, get_index(row, rbound + 1), number);

    if(isinbounds(row-1)){ // Check top row
        if(isinbounds(lbound - 1) && schematic[row-1][lbound-1] == '*' ) 
            insert_into_gears(gears, get_index(row - 1, lbound - 1), number);
        for(int i = 0; i < distance; i++)
            if(schematic[row-1][lbound + i] == '*' ) 
                insert_into_gears(gears, get_index(row - 1, lbound + i), number);
        if(isinbounds(rbound + 1) && schematic[row-1][rbound+1] == '*' ) 
            insert_into_gears(gears, get_index(row-1, rbound + 1), number);
    }

    if(isinbounds(row+1)){ // Check bottom row
        if(isinbounds(lbound - 1) && schematic[row+1][lbound-1] == '*' ) 
            insert_into_gears(gears, get_index(row+1, lbound - 1), number);
        for(int i = 0; i < distance; i++)
            if(schematic[row+1][lbound + i] == '*' ) 
                insert_into_gears(gears, get_index(row+1, lbound + i), number);
        if(isinbounds(rbound + 1) && schematic[row+1][rbound+1] == '*' ) 
            insert_into_gears(gears, get_index(row+1, rbound + 1), number);
    }
    return false;
}

size_t part2(){
    std::vector<Gear> gears;
    size_t gear_ratio_sum = 0;

    for(int r = 0; r < SCHEMATIC_WIDTH; r++){
        int lbound = 0, rbound = 0;
        for(int c = 0; c < SCHEMATIC_WIDTH; c++){
            if(schematic[r][c] == '.') continue;
            if(isdigit(schematic[r][c])){
                lbound = c, rbound = c;
                while( isinbounds(rbound + 1) && isdigit( schematic[r][rbound+1] ) ) {rbound++; c++;};
                add_close_gears2(gears, r, lbound, rbound);
            }
        }
    }
    for(auto& gear : gears){
        if(gear.second.size() == 2){
            // printf("%d : [%d, %d]\n", gear.first, gear.second[0], gear.second[1]);
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
    //
    printf("Part 1: %zu\n", part1()); //519444
    printf("Part 2: %zu\n", part2()); //74528807
    return 0;
}