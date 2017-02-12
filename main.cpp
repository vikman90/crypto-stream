/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#include <QApplication>
#include "widget.h"

// Punto de entrada al programa

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget widget;

    widget.show();
    return app.exec();
}
