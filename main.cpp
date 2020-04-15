#include "enigma.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int rot[3];
    char rot_chr[3];
    char original_text[100];
    char cipher_text[100];
    char daily_key[6];
    ifstream fin("original_text");
    for (int i = 0; i < 3; i++)
        fin >> rot[i];
    for (int i = 0; i < 3; i++)
        fin >> rot_chr[i];
    int idx = 0;
    while (!fin.eof())
        fin >> original_text[idx++];
    fin.close();
    Enigma_encoder enig_test;
    enig_test.reset_rotor_index(rot);
    enig_test.reset_rotor_clock(rot_chr);
    enig_test.show_info();
    daily_key[0] = enig_test.encode(rot_chr[0]);
    daily_key[1] = enig_test.encode(rot_chr[1]);
    daily_key[2] = enig_test.encode(rot_chr[2]);
    daily_key[3] = enig_test.encode(rot_chr[0]);
    daily_key[4] = enig_test.encode(rot_chr[1]);
    daily_key[5] = enig_test.encode(rot_chr[2]);
    enig_test.reset_rotor_index(rot);
    enig_test.reset_rotor_clock(rot_chr);
    for (int i = 0; i < idx - 1; i++)
        cipher_text[i] = enig_test.encode(original_text[i]);
    ofstream fout("cipher_text");
    for (int i = 0; i < 6; i++)
        fout << daily_key[i];
    fout << endl;
    for (int i = 0; i < idx - 1; i++)
        fout << cipher_text[i];
    fout << endl;
    fout.close();
    return 0;
}