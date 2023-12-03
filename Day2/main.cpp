#include "../utils.h"
#include <vector>
#include <string>
#include <string.h>

#define FILE_PATH "Day2/input.txt"
#define GAME_COUNT 100
#define MAX_CUBE_SIZE 3

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

struct Bag {
    int red; 
    int blue; 
    int green;
};

Bag parse_bag(std::string data){
    Bag b = { -1,-1,-1 };
nextitem:
    size_t comma_location = data.find(',');
    size_t space_location = data.find(' ');
    int num = std::atoi( std::string(data.begin(), data.begin() + space_location).c_str() ); //space after number
    char id = *(data.begin() + space_location + 1);
    switch(id){
    case 'r': b.red = num; break;
    case 'b': b.blue = num; break;
    case 'g': b.green = num; break;
    default: assert(false);
    }

    if(comma_location != std::string::npos){
        data = data.substr(comma_location + 2);
        goto nextitem;
    }
    // printf("[Bag]:red %d, blue %d, green %d\n", b.red,b.blue,b.green);
    return b;
}
typedef std::string::iterator StrIt;

bool part1(std::string game_line){
    std::string data = game_line.substr(game_line.find(':') + 2); // +2 for skipping colon and space
    StrIt prev_end_it = data.begin();
nextbag:
    StrIt bag_begin_it = prev_end_it; //start at number
    size_t semicolon_location = data.find(';');

    StrIt bag_end_it = semicolon_location == std::string::npos ? 
        data.end() : bag_begin_it + semicolon_location;
    std::string bag_data = std::string( bag_begin_it, bag_end_it );

    Bag b = parse_bag( bag_data );
    if(b.red > RED_MAX || b.blue > BLUE_MAX || b.green > GREEN_MAX)
        return false;
    if(semicolon_location != std::string::npos){
        data = data.substr(bag_end_it + 2 - data.begin());
        prev_end_it = data.begin();
        goto nextbag;
    }
    
    return true;
}

size_t part2(std::string game_line){
    Bag min_req_bag = { 0 };
    std::string data = game_line.substr(game_line.find(':') + 2); // +2 for skipping colon and space
    StrIt prev_end_it = data.begin();
nextbag:
    StrIt bag_begin_it = prev_end_it; //start at number
    size_t semicolon_location = data.find(';');

    StrIt bag_end_it = semicolon_location == std::string::npos ? 
        data.end() : bag_begin_it + semicolon_location;
    std::string bag_data = std::string( bag_begin_it, bag_end_it );

    Bag b = parse_bag( bag_data );
    min_req_bag.red = std::max(b.red, min_req_bag.red);
    min_req_bag.green = std::max(b.green, min_req_bag.green);
    min_req_bag.blue = std::max(b.blue, min_req_bag.blue);
    if(semicolon_location != std::string::npos){
        data = data.substr(bag_end_it + 2 - data.begin());
        prev_end_it = data.begin();
        goto nextbag;
    }
    size_t cube = min_req_bag.red * min_req_bag.green * min_req_bag.blue;
    return cube;
}

int run_part1(std::ifstream& stream){
    int sum_total_possible_game_ids = 0;
    for(int i = 0; i < GAME_COUNT; i++){
        std::string line;
        std::getline(stream, line);
        bool possible = part1(line);
        if(possible)
            sum_total_possible_game_ids += (i + 1);
    }
    return sum_total_possible_game_ids;
}
size_t run_part2(std::ifstream& stream){
    size_t sum_total_cubes = 0;
    for(int i = 0; i < GAME_COUNT; i++){
        std::string line;
        std::getline(stream, line);
        size_t cube = part2(line);
        sum_total_cubes += cube;
    }
    return sum_total_cubes;
}

int main(int argc, char **argv){ // TOO LOW
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %d\n", run_part1(stream));
    stream.seekg(stream.beg);
    printf("Part 2: %zu\n", run_part2(stream));
    return 0;
}