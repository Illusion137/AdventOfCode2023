#include "../utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <thread>
#include <limits.h>

#define FILE_PATH "Day5/input.txt"
#define TOTAL_MAPS    7
#define DST_RANGE_BEG 0
#define SRC_RANGE_BEG 1
#define RANGE_LEN     2

typedef long long _size_t;
typedef std::vector<std::vector<_size_t>> almanac_map;
struct Almanac {
    std::vector<_size_t> seeds;
    std::vector<std::vector<_size_t>> new_seeds;
    almanac_map seed_to_soil;
    almanac_map soil_to_fertilizer;
    almanac_map fertilizer_to_water;
    almanac_map water_to_light;
    almanac_map light_to_temperature;
    almanac_map temperature_to_humidity;
    almanac_map humidity_to_location;
};

std::vector<std::vector<_size_t>> seeds_to_new_seeds(std::vector<_size_t> seeds){
    std::vector<std::vector<_size_t>> out;
    for(int i = 0; i < seeds.size(); i+=2){
        std::vector<_size_t> nseeds = {
            seeds[i],
            seeds[i+1]
        };
        out.push_back(nseeds);
    }
    return out;
}

_size_t almanac_map_get(almanac_map& map, _size_t in){
  _size_t out = in;
  for(int i = 0; i < map.size(); i++){
    if(in >= map[i][SRC_RANGE_BEG] && in < map[i][SRC_RANGE_BEG] + map[i][RANGE_LEN]){
      out = map[i][DST_RANGE_BEG] + in - map[i][SRC_RANGE_BEG];
    }
  }
  return out;
}
std::vector<_size_t> parse_nums(std::string line){
    std::vector<_size_t> nums; nums.reserve(3);
    auto it = line.begin();
    std::string::iterator delimiter_it;
    while((delimiter_it = std::find(it, line.end(), ' ')) != line.end()){
        _size_t num = std::stoll(std::string(it, delimiter_it));
        nums.push_back(num);
        it = delimiter_it + 1;
    }
    delimiter_it = std::find(it, line.end(), ' ');
    int num = stoi(std::string(it, delimiter_it));
    nums.push_back(num);
    return nums;
}
std::vector<_size_t> parse_seeds(std::string line){
    int start_pos = line.find_first_of(':') + 2;
    return parse_nums(line.substr(start_pos));
}

_size_t seed_to_location(Almanac& a, _size_t seed){
    _size_t ss, sf, fw, wl, lt, th, hl;
    ss = almanac_map_get(a.seed_to_soil, seed);
    sf = almanac_map_get(a.soil_to_fertilizer, ss);
    fw = almanac_map_get(a.fertilizer_to_water, sf);
    wl = almanac_map_get(a.water_to_light, fw);
    lt = almanac_map_get(a.light_to_temperature, wl);
    th = almanac_map_get(a.temperature_to_humidity, lt);
    hl = almanac_map_get(a.humidity_to_location, th);
    return hl;
}
Almanac create_almanac(std::ifstream& stream){
    Almanac a;
    std::string line;
    std::getline(stream, line);
    a.seeds = parse_seeds(line);

    std::vector<std::vector<std::vector<_size_t>>> maps_data(TOTAL_MAPS, std::vector<std::vector<_size_t>>());
    std::getline(stream, line);std::getline(stream, line);
    for(int i = 0; i < TOTAL_MAPS; i++){
        while(std::getline(stream, line) && line != "") { maps_data[i].push_back(parse_nums(line)); }
        std::getline(stream, line);
    }

    a.seed_to_soil = maps_data[0];
    a.soil_to_fertilizer = maps_data[1];
    a.fertilizer_to_water = maps_data[2];
    a.water_to_light = maps_data[3];
    a.light_to_temperature = maps_data[4];
    a.temperature_to_humidity = maps_data[5];
    a.humidity_to_location = maps_data[6];

    return a;
}

_size_t part1(std::ifstream& stream){
    Almanac a = create_almanac(stream);
    _size_t lowest_loc = INT_MAX;
    for(auto seed : a.seeds){
        _size_t loc = seed_to_location(a, seed);
        // printf("[%lld:%lld]\n", seed, loc);
        lowest_loc = lowest_loc > loc ? loc : lowest_loc; 
    }

    return lowest_loc;
}

_size_t lowest_loc = INT_MAX;

Almanac global_almanac;
void thread_part2(std::vector<_size_t> seeds){
    for(int i = 0; i < seeds[1]; i++){
        auto loc = seed_to_location(global_almanac, i + seeds[0]);
        lowest_loc = lowest_loc > loc ? loc : lowest_loc; 
    }
    // printf("LowLoc:(%lld)\n", lowest_loc);
}

_size_t part2(std::ifstream& stream){
    global_almanac = create_almanac(stream);
    global_almanac.new_seeds = seeds_to_new_seeds(global_almanac.seeds);
    std::vector<std::thread> threads;

    for(auto seeds : global_almanac.new_seeds){
        threads.emplace_back(std::thread(thread_part2, seeds));
    }

    //wait for them to complete
    for (auto& th : threads) 
        th.join();
    
    return lowest_loc;
}//10834440
int main(){
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %lld\n", part1(stream));
    stream.close();
    load_file(&stream, FILE_PATH);
    printf("Part 2: %lld\n", part2(stream));
    stream.close();
    return 0;
}