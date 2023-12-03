#include "../utils.h" 

#include <string>
#include <cstring>

#define FILE_PATH "Day1/code.txt"
#define FILE_LINE_COUNT 1000
#define LINE_RERSERVE 8

constexpr size_t HASH(const char *c, int size){
    size_t hash = 0;
    for(int i = 0; i < size; i++) hash |= ((size_t)c[i] << (size_t)(i * 8));
    return hash;
}
int try_find_strint(char *c){
    switch (HASH(c, 3)) {
        case HASH("one",3): return 1;
        case HASH("two",3): return 2;
        case HASH("six",3): return 6;
        default: break;
    }
    switch (HASH(c, 4)) {
        case HASH("four",4): return 4;
        case HASH("five",4): return 5;
        case HASH("nine",4): return 9;
        default: break;
    }
    switch (HASH(c, 5)) {
        case HASH("three",5): return 3;
        case HASH("seven",5): return 7;
        case HASH("eight",5): return 8;
        default: break;
    }
    return -1;
}

int main(){
    size_t sum = 0;
    char *contents = get_file_contents(FILE_PATH);
    char *c = contents;

    for(int i = 0; i < FILE_LINE_COUNT; i++){
        int d1 = - 1, d2 = -1;
        while(*c != '\n'){
            if(isdigit(*c)){
                d2 = *c - '0';
                if(d1 == -1) d1 = d2;
            } else if(!isdigit(*(c+2)) && !isdigit(*(c+2))) {
                char strint_window[6];
                memcpy((void*)strint_window, (void*)c, 5 * sizeof(char));
                int strint = try_find_strint(strint_window);
                if(strint != -1){
                    d2 = strint;
                    if(d1 == -1) d1 = d2;
                }
            }
            c++; //Next character
        }
        c++; //Eat newline
        sum += (d1 * 10) + d2;
    }
    free(contents);
    printf("%zu\n", sum);
    return sum;
}