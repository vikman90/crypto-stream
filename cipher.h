/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#ifndef CIPHER_H
#define CIPHER_H

#include <QThread>
#include <QFile>
#include <QWidget>
#include <QString>

//------------------------------------------------------------------------------
// Hebra encargada de cifrar los archivos

class Cipher : public QThread
{
    Q_OBJECT

public:

    /*
     * Constructor
     * parent:  Puntero al widget principal
     * pathIn:  Ruta de acceso al archivo origen
     * pathOut: Ruta de acceso al archivo destino
     * key:     Clave de cifrado
     */
    explicit Cipher(QWidget *parent, const QString &pathIn, const QString &pathOut, unsigned int key);

    // Destructor
    ~Cipher();

    /*
     * Apertura de archivos correcta
     * Si devuelve 'false', se deberia destruir y crear un objeto nuevo.
     */
    inline bool openOK() const
    {
        return opened;
    }

signals:

    // Se envia para actualizar la barra de progreso (0..100)
    void progress(int);

protected:

    // Metodo asociado a la hebra
    void run();

private:
    QFile fileIn;       // Archivo de entrada
    QFile fileOut;      // Archivo de salida
    unsigned int key;   // Clave de cifrado
    bool opened;        // Apertura correcta
};

#endif // CIPHER_H
