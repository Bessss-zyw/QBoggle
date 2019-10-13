#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "Depo.h"

#include <QMainWindow>
#include <QPushButton>

class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoggleWindow(QWidget *parent = nullptr);
    ~BoggleWindow();

    int * isWord(QString text);
    bool findCube(QString letter,int *path,int pos,bool *b);
    void computerSearch();
    void shake();
    void reset();
    void ALLreset();

private:
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    Depo *ai;
    Lexicon flex;


    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 600;

protected:

public slots:
    void addWordToME();
    void addWordToComputer();
    void consoleTextChange();
};


#endif // BOGGLEWINDOW_H
