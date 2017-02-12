/*
 * Cifrado de Vernam (Vernam stream cipher)
 * Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
 * September 7th, 2012
 */

#include "widget.h"
#include "ui_widget.h"
#include <QThreadPool>
#include <QFileDialog>
#include <QMessageBox>
#include "cipher.h"

//------------------------------------------------------------------------------
// Construye un nuevo objeto con puntero al padre 'parent'

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    cipher = NULL;

    connect(ui->btBrowseSource, SIGNAL(clicked()), SLOT(browseSource()));
    connect(ui->btBrowseTarget, SIGNAL(clicked()), SLOT(browseTarget()));
    connect(ui->btStart, SIGNAL(clicked()), SLOT(crypt()));
}

//------------------------------------------------------------------------------
// Destructor

Widget::~Widget()
{
    delete ui;
}

//------------------------------------------------------------------------------
// Explorar origen

void Widget::browseSource()
{
    ui->lnSource->setText(QFileDialog::getOpenFileName(this, "Seleccione origen"));
}

//------------------------------------------------------------------------------
// Explorar destino

void Widget::browseTarget()
{
    ui->lnTarget->setText(QFileDialog::getSaveFileName(this, "Seleccione destino"));
}

//------------------------------------------------------------------------------
// Encriptar

void Widget::crypt()
{
    bool ok;
    unsigned int key = ui->lnKey->text().toUInt(&ok);

    if (!ok || key == 0) {
        QMessageBox::warning(this, "Clave incorrecta", "No ha escrito una clave valida.");
        return;
    }

    if (ui->lnSource->text().size() == 0 || ui->lnTarget->text().size() == 0) {
        QMessageBox::warning(this, "Introduzca rutas de archivo", "No ha especificado nombres de archivo.");
        return;
    }

    cipher = new Cipher(this, ui->lnSource->text(), ui->lnTarget->text(), key);

    if (cipher->openOK()) {
        connect(cipher, SIGNAL(progress(int)), SLOT(progress(int)));
        connect(cipher, SIGNAL(finished()), SLOT(cipherFinished()));
        ui->btStart->setEnabled(false);
        cipher->start();
    }
}

//------------------------------------------------------------------------------
// Notificacion de progreso (value : 0..100)

void Widget::progress(int value)
{
    ui->barProgress->setValue(value);
}

//------------------------------------------------------------------------------
// Notificacion de finalizacion de cifrado

void Widget::cipherFinished()
{
    disconnect(cipher, SIGNAL(progress(int)), this, SLOT(progress(int)));
    ui->btStart->setEnabled(true);
    delete cipher;
    cipher = NULL;
}
