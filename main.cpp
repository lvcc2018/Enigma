#include "enigma.h"
#include <iostream>
using namespace std;

int main()
{
    int rot[3] = {2,1,0};
    int init[3] = {23,3,7};
    Enigma_encoder enig_test(rot,init);
    enig_test.show_info();
    char input;
    char output;
    while(true)
    {
        cin>>input;
        output = enig_test.encode(input);
    }
    
    
    return 0;
}