#include "enigma.h"

int main()
{
    int rot[3] = {2,1,0};
    int init[3] = {23,3,7};
    Enigma_encoder enig_test(rot,init);
    enig_test.show_info();
    enig_test.clock_tik();
    enig_test.rotor_encode(0);
    
    return 0;
}