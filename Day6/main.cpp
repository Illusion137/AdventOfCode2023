#include "../utils.h"
#include <iostream>
#include <vector>
#include <string>

#define FILE_PATH "Day6/input.txt"

typedef std::pair<int,int> time_distance_pair;
typedef std::pair<llong,llong> long_time_distance_pair;

long_time_distance_pair parse_race(std::ifstream& stream){
    time_distance_pair pair;

    std::string time_line;
    std::string dist_line;
    std::getline(stream, time_line);
    std::getline(stream, dist_line);
    
    int t_pos = time_line.find(':') + 1, d_pos = dist_line.find(':') + 1;

    auto times = get_llong_nums_in_line(time_line.substr(t_pos));
    auto distances = get_llong_nums_in_line(dist_line.substr(d_pos));

    std::string time;
    std::string dist;
    for(int i = 0; i < times.size(); i++){
        time += std::to_string(times[i]);
        dist += std::to_string(distances[i]);
    }

    return { std::stoll(time), std::stoll(dist) };
}

std::vector<time_distance_pair> parse_races(std::ifstream& stream){
    std::vector<time_distance_pair> pairs;

    std::string time_line;
    std::string dist_line;
    std::getline(stream, time_line);
    std::getline(stream, dist_line);
    
    int t_pos = time_line.find(':') + 1, d_pos = dist_line.find(':') + 1;

    auto times = get_nums_in_line(time_line.substr(t_pos));
    auto distances = get_nums_in_line(dist_line.substr(d_pos));

    for(int i = 0; i < times.size(); i++)
        pairs.push_back({times[i], distances[i]});
    return pairs;
}

int part1(std::ifstream& stream){
    auto time_distance_pairs = parse_races(stream);
    int wins_possibilities_mult = 1;
    for(auto pair : time_distance_pairs){
        int wins_possibilities = 0;
        for(int speed = 0; speed < pair.first; speed++){
            int distance = speed * (pair.first - speed);
            if(distance > pair.second)
                wins_possibilities++;
        }
        if(wins_possibilities) wins_possibilities_mult *= wins_possibilities;
    }
    return wins_possibilities_mult;
}
int part2(std::ifstream& stream){
    auto pair = parse_race(stream);
    int wins_possibilities = 0;
    for(llong speed = 0; speed < pair.first; speed++){
        llong distance = speed * (pair.first - speed);
        if(distance > pair.second)
            wins_possibilities++;
    }
    return wins_possibilities;
}

int main(){ // 26961642
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %d\n", part1(stream));
    stream.close();
    load_file(&stream, FILE_PATH);
    printf("Part 2: %d\n", part2(stream));
    stream.close();
    return 0;
}