#ifndef ENIGMA
#define ENIGMA
#define ROTOR_NUM 3
#include <string>


const char rotors_config[5][27] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                            "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                            "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                            "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                            "VZBRGITYUPSDNHLXAWMJQOFECK"};

class Enigma_encoder
{
    private:
        // The enigma rotor config
        char exchange_rotor[27];
        char rotors[ROTOR_NUM][27];
        char reflector[27];
        // The enigma initial config
        int rotor_idx[ROTOR_NUM];
        char rotor_clock[ROTOR_NUM];
    public:
        Enigma_encoder(int _rotor_index[ROTOR_NUM], char _rotor_clock[ROTOR_NUM]);
        ~Enigma_encoder();
};

#endif