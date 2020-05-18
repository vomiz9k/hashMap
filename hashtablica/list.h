#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
class list
{
    class list_node
    {
        char* value = 0;
        list_node* next = 0;
        friend class list;
    };

    list_node* head = 0;
    list_node* tail = 0;
    unsigned int list_size = 0;
    unsigned int last = 0;

    void insert_front(unsigned int pos, char* value);

public:

    void push_front(char* value);
    void push_back(char* value);
    void insert(unsigned int pos, char* value);
    bool remove(char* value);
    bool contains(char* value);
    bool empty();
    unsigned int size();

    ~list();
};