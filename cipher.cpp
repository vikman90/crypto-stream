/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#include "cipher.h"
#include <QMessageBox>
#include "threads.h"

//------------------------------------------------------------------------------
// Constructor

Cipher::Cipher(QWidget *parent, const QString &pathIn, const QString &pathOut, unsigned int key)
{
    fileIn.setFileName(pathIn);
    fileOut.setFileName(pathOut);

    if (!fileIn.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(parent, "Error de apertura", QString("El archivo de origen no se pudo abrir."));
        opened = false;
        return;
    }

    if (!fileOut.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(parent, "Error de apertura", QString("El archivo destino no se pudo abrir."));
        fileIn.close();
        opened = false;
        return;
    }

    this->key = key;
    this->opened = true;
    moveToThread(this);
}

//------------------------------------------------------------------------------
// Destructor

Cipher::~Cipher()
{
    fileIn.close();
    fileOut.close();
}

//------------------------------------------------------------------------------
// Metodo asociado a la hebra

void Cipher::run()
{
    qint64 fileSize = fileIn.size();
    qint64 nBytes = 0;
    BufferWorker* workers[3];

    workers[0] = new Reader(this, fileIn);
    workers[1] = new Writer(this, fileOut);
    workers[2] = new Producer(this, key);

    for (int i = 0; i < 3; i++)
        workers[i]->start();

    workers[2]->swap();

    do {
        workers[0]->swap();

        for (int i = 0; i < workers[0]->nBytes; i++)
            workers[1]->getBuffer()[i] = workers[0]->getBuffer()[i] ^ workers[2]->getBuffer()[i];

        workers[1]->nBytes = workers[0]->nBytes;
        workers[2]->nBytes = workers[0]->nBytes;
        workers[1]->swap();
        workers[2]->swap();

        nBytes += workers[1]->nBytes;
        emit progress((int)((double)nBytes / fileSize * 100));

    } while (workers[0]->nBytes == LBUFFER);

    for (int i = 0; i < 3; i++)
        workers[i]->wait();
}
