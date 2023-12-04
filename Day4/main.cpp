#include "../utils.h"

#define FILE_PATH "Day4/input.txt"

int main(){
    std::ifstream stream;
    load_file(&stream, FILE_PATH);

    stream.close();
    return 0;
}