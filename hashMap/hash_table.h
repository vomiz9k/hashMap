#include "list.h"
class hash_table
{
    unsigned int table_size = 59999;
    unsigned int string_count = 0;
    list* array = nullptr;
    unsigned int (*hash)(char* string);


public:

    void insert(char* string);

    void remove(char* string);
    bool contains(char* string);

    void print_diagram(const char* of_name);

    hash_table(unsigned int size);

    hash_table();

    hash_table(unsigned int (*other_hash)(char* string));

    hash_table(unsigned int size, unsigned int (*other_hash)(char* string));

    ~hash_table();
}; 
