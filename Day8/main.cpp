#include "../utils.h"
#include <array>
#include <numeric>
#include <unordered_set>

#define FILE_PATH "Day8/input.txt"

struct Map {
    int in;
    int out_left;
    int out_right;
};

int hash(std::string s){
    int h = 0;
    for(int i = 0; i < s.size(); i++) h |= s[i] << (i * 8);
    return h;
}
std::string unhash(int h){
    std::string s = "000";
    for(int i = 0; i < 3; i++) s[i] = (h >> (i * 8)) & 0xff;
    return s;
}

std::vector<Map> get_maps(std::ifstream& stream){
    std::vector<Map> maps;
    
    std::string line;
    std::getline(stream, line);
    while(std::getline(stream, line)){
        Map m;
        m.in = hash(line.substr(0,3));
        m.out_left = hash(line.substr(7,3));
        m.out_right = hash(line.substr(12,3));
        maps.push_back(m);
    }

    return maps;
}

bool all_end_in_z(const std::vector<Map>& search_maps){
    return std::all_of(search_maps.begin(), search_maps.end(), [](Map m){ auto h = unhash(m.in); return h[h.size()-1] == 'Z'; })    ;
}

//Stole this :3
int gcd(int a, int b){
    for (;;) {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

//And this :3 ... from stackoverflow :3
int lcm(int a, int b){
    int temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

int part1(std::ifstream& stream){
    std::string right_left;
    std::getline(stream, right_left);
    
    std::vector<Map> maps = get_maps(stream);

    auto rl_it = right_left.begin();

    int step = 0, aHash = hash("AAA"), zHash = hash("ZZZ");
    Map cMap = *std::find_if(maps.begin(), maps.end(), [aHash](Map m){ return m.in == aHash; });
    while(cMap.in != zHash){
        if(*rl_it == 'L')
            cMap = *std::find_if(maps.begin(), maps.end(), [cMap](Map m){ return m.in == cMap.out_left; });
        else
            cMap = *std::find_if(maps.begin(), maps.end(), [cMap](Map m){ return m.in == cMap.out_right; });
        if(++rl_it == right_left.end()) rl_it = right_left.begin();
        step++;
    }
    return step;
}
long long part2(std::ifstream& stream){
std::string right_left;
    std::string line;
    std::getline(stream, right_left);

    std::vector<Map> _maps = get_maps(stream);
    std::vector<Map> fmaps = _maps;
    for(auto& map : fmaps){
        for(int i = 0; i < _maps.size(); i++){
            if(map.out_left == _maps[i].in) map.out_left = i;
            if(map.out_right == _maps[i].in) map.out_right = i;
        }
    }

    auto rl_it = right_left.begin();

    std::vector<Map> AMaps;
    std::copy_if(fmaps.begin(), fmaps.end(), std::back_inserter(AMaps), [](Map m){ auto h = unhash(m.in); return h[2] == 'A'; });
    const int mSize = AMaps.size();
    std::vector<long long> steps(mSize, 0);
    
    for(int i = 0; i < mSize; i++){
        std::string h = "AAA";     
        while(h[2] != 'Z'){
            if(*rl_it == 'L')
                AMaps[i] = fmaps[AMaps[i].out_left];
            else
                AMaps[i] = fmaps[AMaps[i].out_right];
            if(++rl_it == right_left.end()) rl_it = right_left.begin();
            steps[i]++;
            // assert(steps[i] != LLONG_MAX);
            h = unhash(AMaps[i].in);;
        }
        println(steps[i]);
    }
    return std::accumulate(steps.begin(), steps.end(), 1, lcm); //Bitch ass trick I had to cheat on :P
}

int main(){ 
    std::ifstream stream;
    load_file(&stream, FILE_PATH);
    printf("Part 1: %d\n", part1(stream));
    stream.close();
    load_file(&stream, FILE_PATH);
    printf("Part 2: %lld\n", part2(stream));
    stream.close();
    return 0;
}