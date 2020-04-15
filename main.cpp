#include "enigma.h"
#include <iostream>

using namespace std;

int main()
{
    Enigma_encoder enig_test;
    /*
    enig_test.encode_paragraph("original_text");
    enig_test.poland_decode("cipher_text");
    */

    int rotor_index[3] = {2, 1, 0};
    enig_test.reset_rotor_index(rotor_index);
    char rotor_clock[3] = {'A', 'W', 'E'};
    enig_test.reset_rotor_clock(rotor_clock);
    /*
    char x;
    while (true)
    {
        cin >> x;
        cout << enig_test.encode(x);
    }
    */
    enig_test.turing_decode("original_cipher_text");
    return 0;
}