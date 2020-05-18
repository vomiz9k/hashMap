# Анализ простейших хэш-функций и методы их оптимизации на ассемблере.

### Рассматриваемые функции:

```cpp
unsigned int stupid_hash(char* string)
{
    return 1;
}
```

```cpp
unsigned int strlen_hash(char* string)
{
    return strlen(string);
}
```

```cpp
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
```

```cpp
unsigned int ascii_sum_hash(char* string)
{
    unsigned int hash_sum = 0;
    while (*string != 0)
        hash_sum += *(string++);
    return hash_sum;
}
```

```cpp
unsigned int ded_hash(char* string)
{
    unsigned int hash_sum = 0;
    while (*string != 0)
    {
        hash_sum ^= *string;
        hash_sum = (hash_sum << 1) | (hash_sum >> 31);
        ++string;
    }
    return hash_sum;
}
```
## Проанализируем распределение слов в хэш-таблице.
### Выборка: ~60000 существующих английских слов
### Размер хэш-таблицы: 2017
![stupid_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/stupid.pdf "stupid_hash")

