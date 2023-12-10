#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

typedef long long llong;

size_t get_file_size(FILE *file){
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);
    return fsize;
}
char *get_file_contents(const char* path){
    FILE* file = fopen(path, "r");
    assert(file && "Couldn't open file");

    size_t fsize = get_file_size(file);

    char* buf = (char*)calloc(fsize, sizeof(char));
    assert(buf && "file buf is NULL");

    if (buf && file) {
        fread(buf, sizeof(char), fsize, file);
    }

    if (file) {
        fclose(file);
    }

    return buf;
};
bool load_file(std::ifstream* stream, std::string filename) {
	stream->open(filename);
	stream->seekg(0, std::ios::beg);
	assert (stream != NULL);
	return true;
}

bool inrange(int i, int min, int max){
    return i >= min && i <= max;
}

template<class T> std::vector<T> get_nums_in_line(std::string line){
    std::vector<T> nums;
 next:
    auto not_ws = line.begin() + line.find_first_not_of(' ');
    auto ws = std::find(not_ws, line.end(), ' ');
    bool end = ws == line.end();
    nums.push_back(std::stoll( std::string(not_ws, ws) ));
    
    line = std::string(ws, line.end());

    if(!end) goto next;

    return nums;
}

std::vector<std::string> str_split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
std::vector<std::string> str_csplit (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

template<class T> void print(T value){
    std::cout << "[" << value << "]";
}
template<class T> void println(T value){
    std::cout << "[" << value << "]\n";
}
template<class T> void printvec(std::vector<T> vec){
    if(vec.size() == 0) return;
    std::cout << "{ ";
    for(int i = 0; i < vec.size() - 1; i++)
        std::cout << vec[i] << ", ";
    std::cout << vec[vec.size()-1] << " }\n";
}
template<class T> void printvecln(std::vector<T> vec){
    if(vec.size() == 0) return;
    std::cout << "{\n";
    for(const auto& v : vec)
        std::cout << "  [" << v << "],\n";
    std::cout << "}\n";
}