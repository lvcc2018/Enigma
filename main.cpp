#include "enigma.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int rotor_index[3] = {2, 1, 0};
    char rotor_clock[3] = {'A', 'W', 'E'};
    int action = 0;
    cout << "Please tell me the order number:" << endl;
    cout << "0: Enigma encode" << endl
         << "1: Poland decode presentation" << endl
         << "2: Turing decode presentation" << endl;
    cin >> action;
    if (action == 0)
    {
        cout << "Please cin the rotor index: " << endl;
        cin >> rotor_index[0] >> rotor_index[1] >> rotor_index[2];
        cout << "Please cin the rotor initial letter: " << endl;
        cin >> rotor_clock[0] >> rotor_clock[1] >> rotor_clock[2];
        cout<<"Now you can type in the origin letter or paragraph: "<<endl;
        Enigma_encoder enig_test;
        enig_test.reset_rotor_index(rotor_index);
        enig_test.reset_rotor_clock(rotor_clock);
        char x;
        while (true)
        {
            cin >> x;
            cout << enig_test.encode(x)<<endl;
        }
    }
    else if (action == 1)
    {
        Enigma_encoder enig_test;
        cout<<"Encode the origin text from the original_text...";
        enig_test.encode_paragraph("original_text");
        cout<<"Completed!"<<endl;
        enig_test.poland_decode("cipher_text");
        cout<<"Decode the cipher text from the cipher_text...";
        cout<<"Completed! Decode completed"<<endl;
    }
    else if(action == 2)
    {
        Enigma_encoder enig_test;
        enig_test.reset_rotor_index(rotor_index);
        enig_test.reset_rotor_clock(rotor_clock);
        enig_test.turing_decode("original_cipher_text");
    }
    else cout<<"Wrong order"<<endl;
    return 0;
}