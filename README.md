# Анализ простейших хэш-функций и методы их оптимизации на ассемблере.

## Рассматриваемые функции:

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
# Проанализируем распределение слов в хэш-таблице.
Выборка: ~60000 существующих английских слов

Размер хэш-таблицы: 2017
#### stupid_hash:
![stupid_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/stupid.png "stupid_hash")
#### strlen_hash:
![strlen_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/strlen.png "strlen_hash")
#### mid_ascii_hash:
![mid_ascii_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/mid_ascii.png "mid_ascii_hash")
#### ascii_sum_hash:
![ascii_sum_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/ascii.png "ascii_sum_hash")
#### ded_hash:
![ded_hash](https://github.com/vomiz9k/hashMap/blob/master/hashMap/graph/ded.png "ded_hash")
###
## Лучшее распределение показывает ded_hash, будем оптимизировать его.
```cpp
#define _OPTIMIZATION
```
### Профилируем:
Выборка: ~370000 английских слов, над которыми проводятся операции вставки и удаления (см. words.txt)

Размер хэш-таблицы: 59999

Работаем следующим образом:
```cpp
for (int j = 0; j < 100; ++j)
    for (int i = 0; i < size; ++i)
        if((i + j) % 2)
            hash_map.insert(words_array[i]);
        else
            hash_map.remove(words_array[i]);
 ```
 ### Результаты профилирования:
#### Без оптимизации. Время работы: 24,7 с.
![no optinization](https://github.com/vomiz9k/hashMap/blob/master/hashMap/pictures_before_asm/o0.png "no optimization")
#### -O1. Время работы: 23 с.
![O1](https://github.com/vomiz9k/hashMap/blob/master/hashMap/pictures_before_asm/o1.png "O1")
#### -O2. Время работы: 18,8 с.
![O2](https://github.com/vomiz9k/hashMap/blob/master/hashMap/pictures_before_asm/o2.png "O2")
#### Или, более наглядно:
![diagram](https://github.com/vomiz9k/hashMap/blob/master/hashMap/pictures_before_asm/diagram.png "diagran")

## Делаем вставку на языке ассемблера:
```cpp
#define _ASM
```
```cpp
unsigned int ded_hash(char* string)
{
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
}
```
### Снова проводим замеры:
Время работы: 19,6 с.
![asm](https://github.com/vomiz9k/hashMap/blob/master/hashMap/pictures_before_asm/asm.png "asm")
# Момент истины: сравним с предыдущими результатами.
#### Относительное время:
![relative](https://github.com/vomiz9k/hashMap/blob/master/hashMap/diagrams/relative.png "relative")
#### Время работы программы:
![runtime](https://github.com/vomiz9k/hashMap/blob/master/hashMap/diagrams/runtime.png "runtime")
#### Время, потраченное на работу данной хэш-функции:
![absolute](https://github.com/vomiz9k/hashMap/blob/master/hashMap/diagrams/absolute%20time.png "absolute")
## Полученные коэффициенты ускорения(абсолютное время до оптимизации / абсолютное время после оптимизации)
<table>
    <tr>
        <td>Оптимизация</td><td>Od</td><td>-O1</td><td>-O2</td>
    </tr>
    <tr>
        <td>Коэффициент</td><td>1,79</td><td>1,39</td><td>0,93</td>
    </tr>
</table> 


