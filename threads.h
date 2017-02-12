/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#ifndef THREADS_H
#define THREADS_H

#include <QThread>
#include <QSemaphore>
#include <QFile>

#define LBUFFER 4096

class Lfsr;

//------------------------------------------------------------------------------
// Clase abstracta de ejecutable con doble buffer

class BufferWorker : public QThread
{
public:

    /*
     * Devuelve el buffer publico
     * Debe usarse siempre a continuacion de swap()
     */
    inline char* getBuffer()
    {
        return bufPublic;
    }

    // Intercambiar buffers (bloquea a la hebra que llama)
    inline void swap()
    {
        semSwap.release();
        semReady.acquire();
    }

    // Numero de bytes implicados en el buffer publico
    qint64 nBytes;

protected:

    // Construye un nuevo objeto con puntero al padre 'parent'
    BufferWorker(QObject *parent);

    // Destructor
    ~BufferWorker();

    char* bufPublic;    // Buffer publico
    char* bufPrivate;   // Buffer privado

    QSemaphore semSwap;     // Hace que la hebra espere a que se pida un cambio
    QSemaphore semReady;    // Señala que la hebra ha terminado de intercambiar
};

//------------------------------------------------------------------------------
// Subproceso lector

class Reader : public BufferWorker
{
public:

    // Construye un nuevo objeto con el padre 'parent' y referencia a un archivo de entrada
    explicit Reader(QObject *parent, QFile &fileIn) : BufferWorker(parent), file(&fileIn) { }

    // Metodo de lectura
    void run();

private:
    QFile *file;    // Archivo de entrada
};

//------------------------------------------------------------------------------
// Subproceso escritor

class Writer : public BufferWorker
{
public:

    // Construye un nuevo objeto con el padre 'parent' y referencia a un archivo de salida
    explicit Writer(QObject *parent, QFile &fileOut) : BufferWorker(parent), file(&fileOut) { }

    // Metodo de escritura
    void run();

private:
    QFile *file;    // Archivo de salida
};

//------------------------------------------------------------------------------
// Subproceso productor de flujo LFSR

class Producer : public BufferWorker
{
public:

    // Construye un nuevo objeto con el padre 'parent' y clave 'key'
    explicit Producer(QObject *parent, unsigned int key);

    // Destructor
    ~Producer();

    // Metodo de produccion
    void run();

private:
    Lfsr *lfsr; // Registro de desplazamiento
};

#endif // THREADS_H
