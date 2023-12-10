#include "../utils.h"
#include <array>
#include <numeric>
#include <unordered_set>

#define FILE_PATH "Day9/input.txt"

int get_next_value(const std::vector<int>& values){
    std::vector<std::vector<int>> extrap;
    extrap.push_back(values);
    extrap.push_back( std::vector<int>() );
    int i = 1;
    extrap[i].reserve(extrap[i-1].size()-1);
    while( !std::all_of(extrap[i-1].begin(), extrap[i-1].end(), [](int i){ return i == 0; }) ){
        for(int j = 0; j < extrap[i-1].size()-1; j++)
            extrap[i].push_back( extrap[i-1][j+1] - extrap[i-1][j] );

        extrap.push_back( std::vector<int>() );
        extrap[i+1].reserve(extrap[i].size()-1);
        i++;
    }
    //-1 to get to 0,0,0,0
    for(int j = extrap.size()-3; j >= 0; j--){
        extrap[j].push_back( extrap[j][ extrap[j].size()-1 ] + extrap[j+1][ extrap[j+1].size()-1 ] );
    }
    
    return extrap[0][extrap[0].size()-1];
}

int get_next_value_reverse(const std::vector<int>& values){
    std::vector<std::vector<int>> extrap;
    extrap.push_back(values);
    extrap.push_back( std::vector<int>() );
    int i = 1;
    extrap[i].reserve(extrap[i-1].size()-1);
    while( !std::all_of(extrap[i-1].begin(), extrap[i-1].end(), [](int i){ return i == 0; }) ){
        for(int j = 0; j < extrap[i-1].size()-1; j++)
            extrap[i].push_back( extrap[i-1][j+1] - extrap[i-1][j] );

        extrap.push_back( std::vector<int>() );
        extrap[i+1].reserve(extrap[i].size()-1);
        i++;
    }
    //-2 to get to 0,0,0,0
    int prev_val = 0;
    for(int j = extrap.size()-3; j >= 0; j--){
        prev_val = extrap[j][ 0 ] - prev_val;
    }
    
    return prev_val;
}

int part1(std::ifstream& stream){
    int sum = 0;
    std::string line;
    while(std::getline(stream,line))
        sum += get_next_value( get_nums_in_line<int>(line) );
    return sum;
}
int part2(std::ifstream& stream){
    int sum = 0;
    std::string line;
    while(std::getline(stream,line))
        sum += get_next_value_reverse( get_nums_in_line<int>(line) );
    return sum;  
}

int main(){ 
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %d\n", part1(stream));
    stream.close();
    load_file(&stream, FILE_PATH);
    printf("Part 2: %d\n", part2(stream));
    stream.close();
    return 0;
}