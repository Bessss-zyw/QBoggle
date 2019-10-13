#include "BoggleWindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoggleWindow w;
    w.show();

    return a.exec();
}


//check toWord()
//each button can only be used once
