#include <cstdio>
#include <iostream>
using namespace std;



// The enigma config
const char rotors[5][27] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                            "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                            "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                            "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                            "VZBRGITYUPSDNHLXAWMJQOFECK"};
const char reflector[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
char excg[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char p[3];
int rotor_num[3];

void enigma_clock(){
    int c1 = (letter2order(p[0]) + 1)%26;
    int c2 = (letter2order(p[1]) + (letter2order(p[0])+1) / 26) % 26;
    int c3 = (letter2order(p[2]) + (letter2order(p[1]) + (letter2order(p[0])+1) / 26) / 26) %26;
    p[0] = order2letter(c1);
    p[1] = order2letter(c2);
    p[2] = order2letter(c3);
}

char rotorCore(char input, int position, int rotor_num)
{
    int offset = letter2order(p[position])+1;
    int index = (letter2order(input) + offset) % 26;
    char output = rotors[rotor_num][index];
    enigma_clock();
    if(position == 2){
        return output;
    }
    int back_offset = (26 + letter2order(p[position]) - letter2order(p[position+1])) % 26;
    output = order2letter((letter2order(output) + 26 - back_offset)%26);
    return output;
}

char enigma_decode(char input){
    int offset = letter2order(p[0])+1;
    int index = (letter2order(input) + offset) % 26;
    char output = rotors[rotor_num[0]][index];
    cout<<output;
    int back_offset = (26 + letter2order(p[0]) - letter2order(p[1])) % 26;
    output = order2letter((letter2order(output) + 26 - back_offset)%26);
    output = rotors[rotor_num[1]][letter2order(output)];
    cout<<output;
    back_offset = (26 + letter2order(p[1]) - letter2order(p[2])) % 26;
    output = order2letter((letter2order(output) + 26 - back_offset)%26);
    output = rotors[rotor_num[2]][letter2order(output)];
    enigma_clock();
    cout<<p[0]<<p[1]<<p[2];
    return output;
}

int main()
{
    // Initialize the Enigma settings
    printf("Please set the rotors order:\n");
    cin>>rotor_num[0]>>rotor_num[1]>>rotor_num[2];
    printf("Please set the initial rotors position:\n");
    cin>>p[0]>>p[1]>>p[2];
    for(int i=0;i<3;i++){
        p[i] = getBig(p[i]);
    }
    printf("Please set the exchange word letter couple num and couples:\n");
    int exnum;
    char e1, e2;
    scanf("%d", &exnum);
    for (int i = 0; i < exnum; i++)
    {
        cin>>e1>>e2;
        excg[letter2order(e1)] = getBig(e2);
        excg[letter2order(e2)] = getBig(e1);
    }
    char input;
    while(true){
        cin>>input;
        cout<<enigma_decode(input);
    }
    return 0;
}