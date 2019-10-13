#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(QWidget *parent) : QPushButton(parent)
{
    ifChosen = false;

    this->setText("");
    QFont font = this->font();
    font.setPointSize(20);
    this->setFont(font);

    this->setFixedSize(50, 50);
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");

}

void Cube::setLetter(QString l)
{
    this->setText(l);
}

QString Cube::getLetter()
{
    return this->text();
}
