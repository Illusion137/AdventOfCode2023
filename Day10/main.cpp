#include "../utils.h"
#include <array>
#include <numeric>
#include <unordered_set>

#define FILE_PATH "Day10/input.txt"

int part1(std::ifstream& stream){
    return 0;
}
int part2(std::ifstream& stream){
    return 0;
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