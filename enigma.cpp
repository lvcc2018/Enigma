#include "enigma.h"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

int letter2order(char letter)
{
    int order = letter;
    if (order > 90)
        order -= 32;
    return order - 65;
}

char order2letter(int order)
{
    char letter = order + 65;
    return letter;
}

char getBig(char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        letter -= 32;
    }
    return letter;
}

Enigma_encoder::Enigma_encoder()
{
    clock_temp1 = clock_temp2 = 0;
    for (int i = 0; i < ROTOR_NUM; i++)
    {
        rotor_idx[i] = i;
        rotor_clock[i] = letter2order(i);
    }
    for (int i = 0; i < 26; i++)
    {
        exchange_rotor[i] = i;
        reflect_rotor[i] = letter2order(reflector[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            candidate_rotors[i][j] = letter2order(rotors_config[i][j]);
        }
    }
}

void Enigma_encoder::reset_rotor_clock(char _rotor_clock[ROTOR_NUM])
{
    clock_temp1 = clock_temp2 = 0;
    for (int i = 0; i < ROTOR_NUM; i++)
    {
        rotor_clock[i] = letter2order(_rotor_clock[i]);
    }
}

void Enigma_encoder::reset_rotor_index(int _rotor_index[ROTOR_NUM])
{
    for(int i=0;i<ROTOR_NUM;i++)
    {
        rotor_idx[i] = _rotor_index[i];
    }
}

void Enigma_encoder::show_info()
{
    printf("rotor index: ");
    for (int i = 0; i < ROTOR_NUM; i++)
        printf("%d ", rotor_idx[i]);
    printf("\nrotor clock: ");
    for (int i = 0; i < ROTOR_NUM; i++)
        printf("%c ", order2letter(rotor_clock[i]));
    printf("\nexchange: ");
    for (int i = 0; i < 26; i++)
        printf("%d ", exchange_rotor[i]);
    printf("\nreflect: ");
    for (int i = 0; i < 26; i++)
        printf("%d ", reflect_rotor[i]);
    printf("\n");
}

void Enigma_encoder::clock_tik()
{
    rotor_clock[0] = (rotor_clock[0] + 1) % 26;
    clock_temp1 += 1;
    if (clock_temp1 > 26)
    {
        rotor_clock[1] = (rotor_clock[1] + 1) % 26;
        clock_temp1 = 0;
    }
    if (clock_temp2 > 26)
    {
        rotor_clock[2] = (rotor_clock[2] + 1) % 26;
        clock_temp2 = 0;
    }
    /*
    for (int i = 0; i < ROTOR_NUM; i++)
        printf("%d ", rotor_clock[i]);
    printf("\n");
    */
}

int Enigma_encoder::exchange_encode(int _char_index)
{
    return exchange_rotor[_char_index];
}

int Enigma_encoder::reflect_encode(int _char_index)
{
    return reflect_rotor[_char_index];
}

int Enigma_encoder::rotor_encode(int _char_index)
{
    int idx = _char_index;
    // printf("%d%c ", idx, order2letter(idx));
    idx = (rotor_clock[0] + idx) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    idx = candidate_rotors[rotor_idx[0]][idx];
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx - rotor_clock[0] + rotor_clock[1] + 26) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    idx = candidate_rotors[rotor_idx[1]][idx];
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx - rotor_clock[1] + rotor_clock[2] + 26) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    idx = candidate_rotors[rotor_idx[2]][idx];
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx - rotor_clock[2] + 26) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    idx = reflect_encode(idx);
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx + rotor_clock[2]) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    for (int i = 0; i < 26; i++)
        if (candidate_rotors[rotor_idx[2]][i] == idx)
        {
            idx = i;
            break;
        }
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx + rotor_clock[1] - rotor_clock[2] + 26) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    for (int i = 0; i < 26; i++)
        if (candidate_rotors[rotor_idx[1]][i] == idx)
        {
            idx = i;
            break;
        }
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx + rotor_clock[0] - rotor_clock[1] + 26) % 26;
    // printf("%d%c ", idx, order2letter(idx));
    for (int i = 0; i < 26; i++)
        if (candidate_rotors[rotor_idx[0]][i] == idx)
        {
            idx = i;
            break;
        }
    // printf("%d%c ", idx, order2letter(idx));
    idx = (idx - rotor_clock[0] + 26) % 26;
    // printf("%d%c\n", idx, order2letter(idx));
    return idx;
}

char Enigma_encoder::encode(char _char)
{
    clock_tik();
    int idx = letter2order(_char);
    idx = exchange_encode(idx);
    idx = rotor_encode(idx);
    idx = exchange_encode(idx);
    char ans = order2letter(idx);
    //printf("%c\n", ans);
    return ans;
}

void Enigma_encoder::poland_decode(char _daily_key[6])
{
    char rotor_clock[3];
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
            {
                rotor_clock[0] = order2letter(i);
                rotor_clock[1] = order2letter(j);
                rotor_clock[2] = order2letter(k);
                reset_rotor_clock(rotor_clock);
                char temp1 = encode(_daily_key[0]);
                char temp2 = encode(_daily_key[1]);
                char temp3 = encode(_daily_key[2]);
                temp1 = encode(temp1);
                temp2 = encode(temp2);
                temp3 = encode(temp3);
                if (temp1 == _daily_key[3] && temp2 == _daily_key[4] && temp3 == _daily_key[5])
                {
                    printf("%c %c %c\n", order2letter(i), order2letter(j), order2letter(k));
                }
            }
    return;
}

void Enigma_encoder::reset_exchange_rotor(char _exchange_rotor[26])
{
    for (int i = 0; i < 26; i++)
    {
        exchange_rotor[i] = letter2order(_exchange_rotor[i]);
    }
    return;
}