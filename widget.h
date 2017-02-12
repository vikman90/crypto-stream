/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Cipher;

//------------------------------------------------------------------------------
// Widget principal del programa

class Widget : public QWidget
{
    Q_OBJECT

public:

    // Construye un nuevo objeto con puntero al padre 'parent'
    explicit Widget(QWidget *parent = 0);

    // Destructor
    ~Widget();

private:
    Ui::Widget *ui; // Formulario
    Cipher *cipher; // Hebra de cifrado

private slots:

    // Explorar origen
    void browseSource();

    // Explorar destino
    void browseTarget();

    // Encriptar
    void crypt();

    // Notificacion de progreso (value : 0..100)
    void progress(int value);

    // Notificacion de finalizacion de cifrado
    void cipherFinished();
};

#endif // WIDGET_H
