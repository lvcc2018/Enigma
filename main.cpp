#include "enigma.h"
#include <iostream>
using namespace std;

int main()
{
    int rot[3] = {2,1,0};
    char rot_chr[3] = {'X','D','H'};
    cout << "Please set the rotor order" << endl;
    for (int i = 0; i < 3; i++)
        cin >> rot[i];
    cout << "Please set the rotor initial position" << endl;
    for (int i = 0; i < 3; i++)
        cin >> rot_chr[i];
    Enigma_encoder enig_test(rot, rot_chr);
    enig_test.show_info();
    char input;
    char output;
    while (true)
    {
        cin >> input;
        output = enig_test.encode(input);
    }

    return 0;
}