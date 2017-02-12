#-------------------------------------------------------------------------------
#
# Cifrado de Vernam (Vernam stream cipher)
# Copyleft 2012 Victor Manuel Fernandez Castro - All rights revoked.
# September 7th, 2012
#
#-------------------------------------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cryptostream
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    threads.cpp \
    cipher.cpp \
    lfsr.cpp

HEADERS  += widget.h \
    threads.h \
    cipher.h \
    lfsr.h

FORMS    += widget.ui

RESOURCES += \
    icons.qrc

RC_FILE += icon.rc
