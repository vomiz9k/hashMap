#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"


#define _OPTIMIZATION
//#define _ASM
#include "hash_funcs.h"



const int MAX_STR_LEN = 50;
const int WORDS_COUNT = 370102;
#ifndef _OPTIMIZATION
const int SKIP_EVERY = 7;
const int HASH_TABLE_SIZE = 2017;
#else
const int HASH_TABLE_SIZE = 59999;
#endif

char* random_word(int max_len);


int main()
{
    FILE* words = fopen("words.txt", "r");
    int size = WORDS_COUNT;
    char** vec = (char**)calloc(sizeof(char*), size);

    int cntr = 0;
    char* string = (char*)calloc(sizeof(char), MAX_STR_LEN + 1);


    while (cntr < size)
    {
        //vec[cntr++] = random_word(100);
        vec[cntr++] = fgets(string, MAX_STR_LEN, words);
        string = (char*)calloc(sizeof(char), MAX_STR_LEN + 1);
    }
    
    
#ifdef _OPTIMIZATION
    hash_table table(HASH_TABLE_SIZE, ded_hash);
    for (int j = 0; j < 100; ++j)
        for (int i = 0; i < size; ++i)
            if((i + j) % 2)
                table.insert(vec[rand() % size]);
            else
                table.remove(vec[rand() % size]);
#else
    for (int j = 0; j < sizeof(hash_funcs) / sizeof(hash_funcs[0]); ++j)
    {
        hash_table table(HASH_TABLE_SIZE, hash_funcs[j].func);
        for (int i = 0; i < size / SKIP_EVERY; ++i)
            table.insert(vec[i * SKIP_EVERY]);

        table.print_diagram(hash_funcs[j].name);
    }
#endif
}



char* random_word(int max_len)
{
    int len = rand() % (max_len - 2) + 2;
    char* word = (char*)calloc(sizeof(char), len + 1);
    word[len] = 0;

    for (int i = 0; i < len; ++i)
        word[i] = rand() % ('z' - 'a') + 'a';
    return word;
}