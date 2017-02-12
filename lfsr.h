/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#ifndef LFSR_H
#define LFSR_H

// Polinomio x^32 + x^30 + x^29 + x^27 + 1

#define LFSR_A 31
#define LFSR_B 29
#define LFSR_C 28
#define LFSR_D 26

//------------------------------------------------------------------------------
// Registro de desplazamiento con retroalimentacion lineal

class Lfsr {
public:

    // Crea un nuevo objeto con semilla 'seed'
    Lfsr(unsigned int seed);

    // Generar un bit
    unsigned int nextBit();

    // Generar un entero (32 bits)
    unsigned int nextInt();

    // Generar un byte (8 bits)
    char nextChar();

private:

    // Desplazar 'count' veces
    void shift(int count = 1);

    // Estado del registro
    unsigned int state;
};

#endif // LFSR_H
