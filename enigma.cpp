#include "enigma.h"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

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
    for (int i = 0; i < ROTOR_NUM; i++)
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

void Enigma_encoder::poland_decode(std::string _cipher_text)
{
    int rotor_idx[3];
    std::ifstream fin(_cipher_text);
    for (int i = 0; i < 3; i++)
        fin >> rotor_idx[i];
    reset_rotor_index(rotor_idx);
    int idx = 0;
    char daily_key[6];
    char cipher_text[MAX_LENGTH];
    for (int i = 0; i < 6; i++)
        fin >> daily_key[i];
    while (!fin.eof())
        fin >> cipher_text[idx++];
    fin.close();
    char rotor_clock[3];
    std::ofstream fout("translate_text");
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
            {
                rotor_clock[0] = order2letter(i);
                rotor_clock[1] = order2letter(j);
                rotor_clock[2] = order2letter(k);
                reset_rotor_clock(rotor_clock);
                char temp1 = encode(daily_key[0]);
                char temp2 = encode(daily_key[1]);
                char temp3 = encode(daily_key[2]);
                temp1 = encode(temp1);
                temp2 = encode(temp2);
                temp3 = encode(temp3);
                if (temp1 == daily_key[3] && temp2 == daily_key[4] && temp3 == daily_key[5])
                {
                    reset_rotor_clock(rotor_clock);
                    for (int i = 0; i < idx - 1; i++)
                        fout << encode(cipher_text[i]);
                    fout << std::endl;
                }
            }
    fout.close();
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

void Enigma_encoder::encode_paragraph(std::string _origin_text)
{
    int rot[3];
    char rot_chr[3];
    char original_text[MAX_LENGTH];
    char cipher_text[MAX_LENGTH];
    char daily_key[6];
    std::ifstream fin(_origin_text);
    for (int i = 0; i < 3; i++)
        fin >> rot[i];
    for (int i = 0; i < 3; i++)
        fin >> rot_chr[i];
    int idx = 0;
    while (!fin.eof())
        fin >> original_text[idx++];
    fin.close();
    reset_rotor_index(rot);
    reset_rotor_clock(rot_chr);
    // show_info();
    daily_key[0] = encode(rot_chr[0]);
    daily_key[1] = encode(rot_chr[1]);
    daily_key[2] = encode(rot_chr[2]);
    daily_key[3] = encode(rot_chr[0]);
    daily_key[4] = encode(rot_chr[1]);
    daily_key[5] = encode(rot_chr[2]);
    reset_rotor_index(rot);
    reset_rotor_clock(rot_chr);
    for (int i = 0; i < idx - 1; i++)
        cipher_text[i] = encode(original_text[i]);
    std::ofstream fout("cipher_text");
    for (int i = 0; i < ROTOR_NUM; i++)
        fout << rotor_idx[i] << " ";
    fout << std::endl;
    for (int i = 0; i < 6; i++)
        fout << daily_key[i] << " ";
    fout << std::endl;
    for (int i = 0; i < idx - 1; i++)
        fout << cipher_text[i];
    fout << std::endl;
    fout.close();
}

void Enigma_encoder::turing_decode(std::string _origin_cipher_text)
{
    int idx = 0;
    char origin_text[MAX_LENGTH];
    char cipher_text[MAX_LENGTH];
    std::ifstream fin(_origin_cipher_text);
    char chr;
    while (true)
    {
        fin.get(chr);
        if (chr == '\n')
            break;
        origin_text[idx] = chr;
        idx++;
    }

    idx = 0;
    while (!fin.eof())
    {
        fin.get(chr);
        cipher_text[idx] = chr;
        idx++;
    }
    idx--;

    int map[26][26] = {0};
    for (int i = 0; i < idx; i++)
        map[letter2order(origin_text[i])][letter2order(cipher_text[i])]++;

    int ring_three[MAX_LENGTH][3] = {0};
    // int ring_five[MAX_LENGTH][5] = {0};
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (map[i][j] > 0)
            {
                for (int k = 0; k < 26; k++)
                {
                    if (map[j][k] > 0 && map[k][i] > 0)
                    {
                        bool same = false;
                        for (int l = 0; l < idx1; l++)
                        {
                            if (i == ring_three[l][0] || i == ring_three[l][1] || i == ring_three[l][2])
                            {
                                same = true;
                                break;
                            }
                        }
                        if (!same)
                        {
                            ring_three[idx1][0] = i;
                            ring_three[idx1][1] = j;
                            ring_three[idx1][2] = k;
                            idx1++;
                        }
                    }
                    /*
                    if (map[j][k] > 0)
                    {
                        for (int l = 0; l < 26; l++)
                        {
                            if (map[k][l] > 0)
                            {
                                for (int m = 0; m < 26; m++)
                                {
                                    if (map[l][m] > 0 && map[m][i] > 0)
                                    {
                                        bool same = false;
                                        for (int m = 0; m < idx2; m++)
                                        {
                                            if (i == ring_five[m][0] || i == ring_five[m][1] || i == ring_five[m][2] || i == ring_five[m][3] || i == ring_five[m][4])
                                            {
                                                same = true;
                                                break;
                                            }
                                        }
                                        if (!same)
                                        {
                                            ring_five[idx2][0] = i;
                                            ring_five[idx2][1] = j;
                                            ring_five[idx2][2] = k;
                                            ring_five[idx2][3] = l;
                                            ring_five[idx2][4] = m;
                                            idx2++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    */
                }
            }
        }
    }
    /*
    for (int i = 0; i < idx1; i++)
        for (int j = 0; j < 3; j++)
            std::cout << ring_three[i][j] << ' ';
    std::cout << std::endl;
    for (int i = 0; i < idx2; i++)
        for (int j = 0; j < 5; j++)
            std::cout << ring_five[i][j] << ' ';
    if (ring_three[0][0] == 0 && ring_three[0][1] == 0 && ring_three[0][2] == 0 && ring_five[0][0] == 0 && ring_five[0][1] == 0 && ring_five[0][2] == 0 && ring_five[0][3] == 0)
    {
        std::cout << "Finding rings failed..." << std::endl;
        return;
    }
    */

    int index[MAX_LENGTH][3];
    for (int j = 0; j < idx1; j++)
        for (int i = 0; i < idx; i++)
        {
            if (origin_text[i] == order2letter(ring_three[j][0]) && cipher_text[i] == order2letter(ring_three[j][1]))
                index[j][0] = i;
            if (origin_text[i] == order2letter(ring_three[j][1]) && cipher_text[i] == order2letter(ring_three[j][2]))
                index[j][1] = i;
            if (origin_text[i] == order2letter(ring_three[j][2]) && cipher_text[i] == order2letter(ring_three[j][0]))
                index[j][2] = i;
        }
    long long sum = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            if (i == j)
                continue;
            for (int k = 0; k < 5; k++)
            {
                if (k == i || k == j)
                    continue;
                int rotor_index[3] = {i, j, k};
                reset_rotor_index(rotor_index);
                for (int l = 0; l < 26; l++)
                    for (int m = 0; m < 26; m++)
                        for (int n = 0; n < 26; n++)
                        {
                            char rotor_clock[3] = {order2letter(l), order2letter(m), order2letter(n)};
                            reset_rotor_clock(rotor_clock);
                            bool perhaps_right = true;
                            for (int p = 0; p < idx1; p++)
                            {
                                perhaps_right = test_ring(index[p][0], index[p][1], index[p][2]);
                            }
                            if (perhaps_right)
                                sum++;
                            bool bingo = true;
                            reset_rotor_clock(rotor_clock);
                            for (int tic = 0; tic < idx; tic++)
                            {
                                if (cipher_text[tic] == encode(origin_text[tic]))
                                    continue;
                                else
                                {
                                    bingo = false;
                                    break;
                                }
                            }
                            if (bingo)
                                std::cout <<"The initial rotor index is "<< i << ' ' << j << ' ' << k << "  The initial letter is " << order2letter(l) << ' ' << order2letter(m) << ' ' << order2letter(n) << std::endl;
                        }
            }
        }
    return;
}

bool Enigma_encoder::test_ring(int idx1, int idx2, int idx3)
{
    for (int o = 0; o < 26; o++)
    {
        char v1 = order2letter(o);
        for (int order = 0; order < idx1; order++)
            clock_tik();
        char v2 = encode(v1);
        for (int order = idx1 + 1; order < idx2; order++)
            clock_tik();
        char v3 = encode(v2);
        for (int order = idx2 + 1; order < idx3; order++)
            clock_tik();
        char v4 = encode(v3);
        if (v1 == v4)
        {
            return true;
        }
    }
    return false;
}