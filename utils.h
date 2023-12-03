#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

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
