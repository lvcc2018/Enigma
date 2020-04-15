#include "enigma.h"
#include <iostream>

using namespace std;

int main()
{
    Enigma_encoder enig_test;
    enig_test.encode_paragraph("original_text");
    enig_test.poland_decode("cipher_text");
    return 0;
}