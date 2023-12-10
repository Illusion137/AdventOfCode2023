#include "../utils.h"
#include <array>
#include <numeric>
#include <unordered_set>

#define FILE_PATH "Day7/input.txt"

bool get_high_card_val(std::vector<int> hand, std::vector<int> hand2){
    for(int i = 0; i < 5; i++) 
        if(hand[i] < hand2[i]) return true;
        else if(hand[i] > hand2[i]) return false;
    assert(false);
    return false;
}

int card_to_val_2(char c){
    switch (c)
    {
    case 'A': return 13;
    case 'K': return 12;
    case 'Q': return 11;
    case 'T': return 10;
    case 'J': return 1;
    default: { assert(isdigit(c)); return c - '0';};
    }
}
std::vector<int> hand_to_vec_2(const std::string& hand){
    std::vector<int> hand_vec;
    for(const char& c : hand){
        hand_vec.push_back(card_to_val_2(c));
    }
    return hand_vec;
}
int get_hand_2(std::vector<int> hand){
    std::sort(hand.begin(), hand.end());

    int high_card = hand[hand.size()-1];

    std::vector<int> counts;
    std::unordered_set<int> checked = { 1 };
    int jokers = std::count_if(hand.begin(), hand.end(), [](int i){ return i == 1; });

    for(int i = 0; i < hand.size(); i++) { 
        int count = 0;
        if(!checked.count(hand[i])){
            for(int j = 0; j < hand.size(); j++)
                if(hand[i] == hand[j]) count++;
            checked.insert(hand[i]);
        }
        counts.push_back(count);
    }
    std::sort(counts.begin(), counts.end());
    int max_el = counts[counts.size() - 1];
    int sec_max_el = counts[counts.size() - 2];

    if(max_el == 5 || max_el + jokers >= 5) return 700;
    if(max_el == 4 || max_el + jokers >= 4) return 600;
    if(max_el == 3 || max_el + jokers >= 3){
        int jokers_used = 3 - max_el; 
        if(sec_max_el == 2 || sec_max_el + (jokers - jokers_used) >= 2) return 500;
        else return 400;
    }
    if(max_el == 2 || max_el + jokers >= 2){
        int jokers_used = 2 - max_el;
        if(sec_max_el == 2  || sec_max_el + (jokers - jokers_used) >= 2) return 300;
        else return 200;
    }
    return 100;
}

bool compare_hand_2(std::pair<std::vector<int>, std::string> hp1, std::pair<std::vector<int>, std::string> hp2){
    int hand_val_1 = get_hand_2(hp1.first);
    int hand_val_2 = get_hand_2(hp2.first);
    if(hand_val_1 != hand_val_2) return hand_val_1 < hand_val_2;
    return get_high_card_val(hp1.first, hp2.first);
}
int card_to_val(char c){
    switch (c)
    {
    case 'A': return 13;
    case 'K': return 12;
    case 'Q': return 11;
    case 'J': return 10;
    case 'T': return 9;
    default: { assert(isdigit(c)); return c - '1';};
    }
}
std::vector<int> hand_to_vec(const std::string& hand){
    std::vector<int> hand_vec;
    for(const char& c : hand){
        hand_vec.push_back(card_to_val(c));
    }
    return hand_vec;
}
int get_hand(std::vector<int> hand){

    std::sort(hand.begin(), hand.end());

    int high_card = hand[hand.size()-1];

    std::vector<int> counts;
    std::unordered_set<int> checked;

    for(int i = 0; i < hand.size(); i++) { 
        int count = 0;
        if(!checked.count(hand[i])){
            for(int j = 0; j < hand.size(); j++)
                if(hand[i] == hand[j]) count++;
            checked.insert(hand[i]);
        }
        counts.push_back(count);
    }
    {
        int acc = std::accumulate(counts.begin(), counts.end(), 0);
        assert(acc == 5);
    }
    // printvec(counts);
    std::sort(counts.begin(), counts.end());
    int max_el = counts[counts.size() - 1];
    int sec_max_el = counts[counts.size() - 2];
    // println(max_el);
    // println(sec_max_el);
    if(max_el == 5) return 700;
    if(max_el == 4) return 600;
    if(max_el == 3) 
        if(sec_max_el == 2) return 500;
        else return 400;
    if(max_el == 2){
        if(sec_max_el == 2) return 300;
        else return 200;
    }
    return 100;
}

bool compare_hand(std::pair<std::vector<int>, std::string> hp1, std::pair<std::vector<int>, std::string> hp2){
    int hand_val_1 = get_hand(hp1.first);
    int hand_val_2 = get_hand(hp2.first);
    if(hand_val_1 != hand_val_2) return hand_val_1 < hand_val_2;
    return get_high_card_val(hp1.first, hp2.first);
}

int part1(std::ifstream& stream){ // 255028414 - 253919613
    std::vector<std::vector<std::string>> hand_bids;
    std::vector<std::pair<std::vector<int>, std::string>> hand_bids_pairs;
    std::string line;
    while(std::getline(stream, line)) hand_bids.push_back(str_csplit(line, ' '));
    hand_bids_pairs.reserve(hand_bids.size());
    for(const auto& h : hand_bids){
        std::vector<int> cards = hand_to_vec(h[0]);
        hand_bids_pairs.push_back({cards, h[1]});
    } 

    std::sort(hand_bids_pairs.begin(), hand_bids_pairs.end(), compare_hand);
    
    int twinnings = 0, i = 1;
    for(const auto& h : hand_bids_pairs){
        int add = std::stoi(h.second) * i++;
        twinnings += add;
    }
    return twinnings;
}
int part2(std::ifstream& stream){
    std::vector<std::vector<std::string>> hand_bids;
    std::vector<std::pair<std::vector<int>, std::string>> hand_bids_pairs;
    std::string line;
    while(std::getline(stream, line)) hand_bids.push_back(str_csplit(line, ' '));
    hand_bids_pairs.reserve(hand_bids.size());
    for(const auto& h : hand_bids){
        std::vector<int> cards = hand_to_vec_2(h[0]);
        hand_bids_pairs.push_back({cards, h[1]});
    } 

    std::sort(hand_bids_pairs.begin(), hand_bids_pairs.end(), compare_hand_2);
    
    int twinnings = 0, i = 1;
    for(const auto& h : hand_bids_pairs){
        int add = std::stoi(h.second) * i++;
        twinnings += add;
    }
    return twinnings;
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