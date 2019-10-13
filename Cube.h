#ifndef CUBE_H
#define CUBE_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>

class Cube : public QPushButton
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);
    void setLetter(QString l);
    QString getLetter();

signals:

public slots:

public:
    bool ifChosen;

};

#endif // CUBE_H
