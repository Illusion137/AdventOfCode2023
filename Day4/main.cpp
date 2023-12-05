#include "../utils.h"
#include <iostream>
#include <vector>
#include <valarray>
#include <queue>
#include <algorithm>
#include <numeric>

#define FILE_PATH "Day4/input.txt"

int part1(std::ifstream& stream){
    int cards_point_val_sum = 0;
    
    std::string line;
    while(std::getline(stream, line)){
        int start_pos = line.find_first_of(':');
        int curr_pos = start_pos + 2;

        std::vector<bool> winning_numbers(100, false);
        while(line[curr_pos] != '|'){
            int tens = line[curr_pos] == ' ' ? 0 : (line[curr_pos] - '0') * 10;
            int ones = line[curr_pos + 1] - '0';
            winning_numbers[ tens + ones ] = true;
            curr_pos += 3;
        }
        int card_point_val = 0, winning_numbers_count = 0;
        curr_pos += 2;
        while(line[curr_pos]){
            int tens = line[curr_pos] == ' ' ? 0 : (line[curr_pos] - '0') * 10;
            int ones = line[curr_pos + 1] - '0';
            if(winning_numbers[ tens + ones ])
                card_point_val = std::pow(2,winning_numbers_count++);
            curr_pos += 3;
        }
        cards_point_val_sum += card_point_val;
    }
    return cards_point_val_sum;
}
size_t part2(std::ifstream& stream){
    std::vector<int> wins_per_card;
    wins_per_card.reserve(201);
    
    std::string line;
    while (std::getline(stream, line)) { 
        int start_pos = line.find_first_of(':');
        int curr_pos = start_pos + 2;
        std::vector<int> winning_numbers; 
        winning_numbers.reserve(10);

        while(line[curr_pos] != '|'){
            int tens = line[curr_pos] == ' ' ? 0 : (line[curr_pos] - '0') * 10;
            int ones = line[curr_pos+1];
            winning_numbers.push_back(tens + ones);
            curr_pos += 3;
        }
        curr_pos += 2;
        int win_num_count = 0;
        while(line[curr_pos]){
            int tens = line[curr_pos] == ' ' ? 0 : (line[curr_pos] - '0') * 10;
            int ones = line[curr_pos+1];
            if(std::find(winning_numbers.begin(), winning_numbers.end(), tens + ones) != winning_numbers.end())
                win_num_count++;
            curr_pos += 3;
        }
        wins_per_card.push_back(win_num_count);
    }
    size_t total_cards = 0;
    std::vector<size_t> total_cards_vec(wins_per_card.size(),1);
    for(int i = 0; i < wins_per_card.size(); i++){
        auto inc = total_cards_vec[i];
        for(int j = 0; j < wins_per_card[i]; j++){
            total_cards_vec[(i+1)+j] += inc;
        }
        total_cards += total_cards_vec[i];
        // printf("[%d:%zu]\n", wins_per_card[i], total_cards_vec[i]);
    }
    return total_cards;
}
int main(){
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %d\n", part1(stream));
    stream.close();
    load_file(&stream, FILE_PATH);
    printf("Part 2: %zu\n", part2(stream));
    stream.close();
    return 0;
}