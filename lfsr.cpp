/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#include "lfsr.h"

//------------------------------------------------------------------------------
// Crea un nuevo objeto con semilla 'seed'

Lfsr::Lfsr(unsigned int seed)
{
    state = seed;
}

//------------------------------------------------------------------------------
// Generar un bit

unsigned int Lfsr::nextBit()
{
    unsigned int bits = (state & 0x80000000) >> 31;
    shift();
    return bits;
}

//------------------------------------------------------------------------------
// Generar un entero (32 bits)

unsigned int Lfsr::nextInt()
{
    unsigned int bits = state;
    shift(32);
    return bits;
}

//------------------------------------------------------------------------------
// Generar un byte (8 bits)

char Lfsr::nextChar()
{
    char bits = (state & 0xFF000000) >> 24;
    shift(8);
    return bits;
}

//------------------------------------------------------------------------------
// Desplazar 'count' veces

void Lfsr::shift(int count)
{
    for (int i = 0; i < count; i++)
        state = (state << 1) | (((state >> LFSR_A) ^ (state >> LFSR_B) ^
                                 (state >> LFSR_C) ^ (state >> LFSR_D)) & 1);
}
