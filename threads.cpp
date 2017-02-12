/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#include "threads.h"
#include <lfsr.h>

//------------------------------------------------------------------------------
// Construye un nuevo objeto de BufferWorker con puntero al padre 'parent'

BufferWorker::BufferWorker(QObject *parent) : QThread(parent)
{
    nBytes = LBUFFER;
    bufPublic = new char[LBUFFER];
    bufPrivate = new char[LBUFFER];
}

//------------------------------------------------------------------------------
// Destructor de BufferWorker

BufferWorker::~BufferWorker()
{
    delete [] bufPublic;
    delete [] bufPrivate;
}

//------------------------------------------------------------------------------
// Construye un nuevo objeto con clave 'key'

Producer::Producer(QObject *parent, unsigned int key) : BufferWorker(parent)
{
    lfsr = new Lfsr(key);
}

//------------------------------------------------------------------------------
// Destructor de Producer

Producer::~Producer()
{
    delete lfsr;
}

//------------------------------------------------------------------------------
// Metodo de lectura

void Reader::run()
{
    qint64 nBytes;
    char *bufSwapping;

    do {
        nBytes = file->read(bufPrivate, LBUFFER);

        semSwap.acquire();
        bufSwapping = bufPublic;
        bufPublic = bufPrivate;
        bufPrivate = bufSwapping;

        this->nBytes = nBytes;
        semReady.release();
    } while (nBytes == LBUFFER);
}

//------------------------------------------------------------------------------
// Metodo de escritura

void Writer::run()
{
    qint64 nBytes;
    char *bufSwapping;

    do {
        semSwap.acquire();
        bufSwapping = bufPublic;
        bufPublic = bufPrivate;
        bufPrivate = bufSwapping;

        nBytes = this->nBytes;
        semReady.release();

        file->write(bufPrivate, nBytes);
    } while (nBytes == LBUFFER);
}

//------------------------------------------------------------------------------
// Metodo de produccion

void Producer::run()
{
    qint64 nBytes = LBUFFER;
    char *bufSwapping;

    do {
        for (int i = 0; i < LBUFFER; i += 4)
            *(unsigned int *)&bufPrivate[i] = lfsr->nextInt();

        semSwap.acquire();
        bufSwapping = bufPublic;
        bufPublic = bufPrivate;
        bufPrivate = bufSwapping;

        nBytes = this->nBytes;
        semReady.release();

    } while (nBytes == LBUFFER);
}
