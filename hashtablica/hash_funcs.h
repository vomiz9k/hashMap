unsigned int stupid_hash(char* string)
{
    return 1;
}

unsigned int strlen_hash(char* string)
{
    return strlen(string);
}

unsigned int ascii_sum_hash(char* string)
{
    unsigned int hash_sum = 0;
    while (*string != 0)
        hash_sum += *(string++);
    return hash_sum;
}

unsigned int mid_ascii_hash(char* string)
{
    unsigned int hash_sum = 0;
    unsigned int str_len = 0;
    while (*string != 0)
    {
        hash_sum += *(string++);
        str_len++;
    }
    return hash_sum / str_len;
}

unsigned int ded_hash(char* string)
{
#ifndef _ASM
    unsigned int hash_sum = 0;
    while (*string != 0)
    {
        hash_sum ^= *string;
        hash_sum = (hash_sum << 1) | (hash_sum >> 31);
        ++string;
    }
    return hash_sum;
#else
    _asm
    {
        mov ebx, string
        xor eax, eax
        xor edx, edx
        _loop :
        mov dl, [ebx]
        xor eax, edx
        rol eax, 1
        inc ebx
        cmp[ebx], 0
        jne _loop
    }
#endif
}

struct hash_func
{
    char name[20];
    unsigned int (*func)(char* string);
};

hash_func hash_funcs[] = { {"stupid.csv", stupid_hash}, {"strlen.csv", strlen_hash}, {"ascii.csv", ascii_sum_hash}, {"mid_ascii.csv", mid_ascii_hash}, {"ded.csv", ded_hash } };