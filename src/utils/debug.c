//
// Created by pedram on 7/4/23.
//

#include "debug.h"

void printArray(unsigned char* data, size_t len){
    for(size_t i = 0 ; i < len ; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}