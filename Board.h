#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"
#include "lexicon.h"

#include <QWidget>
#include <QRandomGenerator>
#include <QMouseEvent>

class Board : public QWidget
{
    Q_OBJECT

    friend class BoggleWindow;
    friend class Depository;

public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    void shake();


public:
    QString currentWord;
    int *wordIndex;
    Lexicon lex;

signals:
    void isWord();

public slots:
    void mousePress();


private:
    int size;
    Cube **cubes;
    QString *letters;
    inline int index(int i, int j) { return i * size + j; }
    bool ifAdjoin(int a,int b);
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

int generateRandomNumber(int min, int max);




#endif // BOARD_H
