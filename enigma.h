#ifndef ENIGMA
#define ENIGMA
#define ROTOR_NUM 3
#include <string>


const char rotors_config[5][27] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
                            "AJDKSIRUXBLHWTMCQGZNPYFVOE",
                            "BDFHJLCPRTXVZNYEIWGAKMUSQO",
                            "ESOVPZJAYQUIRHXLNFTGKDCMWB",
                            "VZBRGITYUPSDNHLXAWMJQOFECK"};
const char reflector[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
class Enigma_encoder
{
    private:
        // The enigma rotor config
        int exchange_rotor[26];
        int reflect_rotor[26];
        int candidate_rotors[5][27];
        // The enigma initial config
        int rotor_idx[ROTOR_NUM];
        int rotor_clock[ROTOR_NUM];
        int clock_temp1, clock_temp2;
    public:
        Enigma_encoder(int _rotor_index[ROTOR_NUM], char _rotor_clock[ROTOR_NUM]);
        void show_info();
        void clock_tik();
        int rotor_encode(int _char_index);
        int exchange_encode(int _char_index);
        int reflect_encode(int _char_index);
        char encode(char _char);
        void reset_rotor_index(char _rotor_clock[ROTOR_NUM]);
        void poland_decode(char _daily_key[6]);
};


#endif