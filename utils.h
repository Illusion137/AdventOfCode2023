#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

std::vector<int> get_nums_in_line(std::string line){
    std::vector<int> nums;
 next:
    auto not_ws = line.begin() + line.find_first_not_of(' ');
    auto ws = std::find(not_ws, line.end(), ' ');
    bool end = ws == line.end();
    nums.push_back(std::stoi( std::string(not_ws, ws) ));
    
    line = std::string(ws, line.end());

    if(!end) goto next;

    return nums;
}

std::vector<llong> get_llong_nums_in_line(std::string line){
    std::vector<llong> nums;
 next:
    auto not_ws = line.begin() + line.find_first_not_of(' ');
    auto ws = std::find(not_ws, line.end(), ' ');
    bool end = ws == line.end();
    nums.push_back(std::stoll( std::string(not_ws, ws) ));
    
    line = std::string(ws, line.end());

    if(!end) goto next;

    return nums;
}

std::vector<size_t> get_ullong_nums_in_line(std::string line){
    std::vector<size_t> nums;
 next:
    auto not_ws = line.begin() + line.find_first_not_of(' ');
    auto ws = std::find(not_ws, line.end(), ' ');
    bool end = ws == line.end();
    nums.push_back(std::stoull( std::string(not_ws, ws) ));
    
    line = std::string(ws, line.end());

    if(!end) goto next;

    return nums;
}