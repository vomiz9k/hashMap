#include "list.h"

void list::insert_front(unsigned int pos, char* value)
{
    unsigned int skipped = 0;
    list_node* curr_node = head;
    list_node* prev_node = nullptr;
    while (++skipped < pos)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    list_node* next_node = curr_node->next;
    curr_node->next = (list_node*)calloc(1, sizeof(list_node));
    curr_node->next->next = next_node;
    if (!next_node)
        tail = curr_node->next;

    curr_node->next->value = value;
    ++list_size;
}

void list::push_front(char* value)
{
    list_node* new_node = (list_node*)calloc(1, sizeof(list_node));
    new_node->value = value;
    new_node->next = head;
    if (!head)
        tail = new_node;
    head = new_node;
    ++list_size;
}

void list::push_back(char* value)
{
    list_node* new_node = (list_node*)calloc(1, sizeof(list_node));
    new_node->value = value;
    if (!tail)
        tail->next = new_node;
    else
        head = new_node;
    tail = new_node;
}

void list::insert(unsigned int pos, char* value)
{
    if (pos == 0 || empty())
        push_front(value);
    else if (pos >= list_size)
        push_back(value);

    insert_front(pos, value);
}

bool list::remove(char* value)
{
    list_node* curr_node = head;
    list_node* prev_node = nullptr;
    while (curr_node && strcmp(curr_node->value, value))
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    if (!curr_node)
        return false;
    if (curr_node == head)
        head = curr_node->next;
    if (curr_node == tail)
        tail = prev_node;
    if (prev_node)
        prev_node->next = curr_node->next;

    free(curr_node);
    list_size--;
    return true;
}

bool list::contains(char* value)
{
    list_node* curr_node = head;
    while (curr_node && strcmp(curr_node->value, value))
        curr_node = curr_node->next;
    return curr_node != nullptr;
}

bool list::empty()
{
    return list_size == 0;
}

unsigned int list::size()
{
    return list_size;
}

list::~list()
{
    if (head == nullptr)
        return;

    list_node* curr_node = head->next;
    list_node* prev_node = head;
    while (curr_node != nullptr)
    {
        free(prev_node);
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    free(prev_node);
}
