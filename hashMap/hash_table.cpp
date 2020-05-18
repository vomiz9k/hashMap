#include "hash_table.h"




static unsigned default_hash(char* string)
{
    unsigned int hash_sum = 0;
    while (*string != 0)
    {
        hash_sum += *string;
        string++;
    }
    return hash_sum;
}

void hash_table::insert(char* string)
{
    int hash_sum = hash(string) % table_size;
    if (array[hash_sum].contains(string))
        return;

    array[hash_sum].push_front(string);
    string_count++;
}

void hash_table::remove(char* string)
{
    if (array[hash(string) % table_size].remove(string))
        string_count--;
}

bool hash_table::contains(char* string)
{
    return array[hash(string) % table_size].contains(string);
}

void hash_table::print_diagram(const char* of_name)
{
    char* command = (char*) calloc(45, sizeof(char));
    char command_start[] = "py graph.py ";
    strcpy(command, command_start);
    strcpy(command + sizeof(command_start) - 1, of_name);
    FILE* out = fopen(of_name, "w");
    for (unsigned int i = 0; i < table_size; ++i)
        fprintf(out, "%d, %d\n", i, array[i].size());
    fclose(out);
    system(command);
    free(command);
}

hash_table::hash_table(unsigned int size)
{
    table_size = size;
    hash = default_hash;
    array = (list*)calloc(sizeof(list), table_size);
}

hash_table::hash_table()
{
    hash = default_hash;
    array = (list*)calloc(sizeof(list), table_size);
}

hash_table::hash_table(unsigned int (*other_hash)(char* string))
{
    hash = other_hash;
    array = (list*)calloc(sizeof(list), table_size);
}

hash_table::hash_table(unsigned int size, unsigned int (*other_hash)(char* string))
{
    hash = other_hash;
    table_size = size;
    array = (list*)calloc(sizeof(list), table_size);
}

hash_table::~hash_table()
{
    for (int i = 0; i < table_size; ++i)
        array[i].~list();
    free(array);
}