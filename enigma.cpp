#include "enigma.h"

Enigma_encoder::Enigma_encoder(int _rotor_index[ROTOR_NUM], char _rotor_clock[ROTOR_NUM])
{
    for(int i=0;i<ROTOR_NUM;i++)
    {
        rotor_idx[i] = _rotor_index[i];
        rotor_clock[i] = _rotor_clock[i];
        std::string rotor_set = rotors_config[rotor_idx[i]];
        int temp = 0;
        for(int i=0;i<rotor_set.length();i++)
        {}
    }
}

