#include "BoggleWindow.h"
#include "lexicon.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
#include <QtDebug>
#include <QStack>

BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);

    QString letters;
    for(int i = 0; i < 25;++i) letters.append(board->cubes[i]->text());
    ai = new Depo(letters);

    me->setGeometry(20, 20, 230, 320);
    board->setGeometry(250, 20, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 320);
    console->setGeometry(30, 360, 740, 210);

    /*
    for (std::string s: lex) {
        std::cout << s << std::endl;
    }
    */

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    Lexicon temp(qFile);
    this->flex = temp;

    console->write("Welcome to the game Boggle!\ninput s ->shake\ninput --- ->recursion\ninput 1 space ->clear board\ninput 2 space ->clear me and computer and the board");

    connect(this->console,SIGNAL(newLineWritten(QString)),this,SLOT(consoleTextChange()));
    connect(this->board,SIGNAL(isWord()),this,SLOT(addWordToME()));
    connect(this->ai,SIGNAL(isWord()),this,SLOT(addWordToComputer()));

}

BoggleWindow::~BoggleWindow()
{
}

/* posibilities
 * 1.totally wrong -> do nothing
 * 2.posible to be a word -> do nothing
 * 3.the word has been added (no word after extension) -> do nothing
 * 4.the word has been added (there are words after extension)
 * 5.new word
 */


/*
 * input"s" ->shake
 * input"---" ->recursion
 * input" " ->clear board
 * input"  " ->clear me and computer and the board
 *
 */

void BoggleWindow::consoleTextChange()
{
    QString temp = console->text;
    if(temp == "s") this->shake();
    else if (temp == "---") computerSearch();
    else if (temp == "  ") ALLreset();
    else if(temp == " ") reset();
    else {
        int *p = isWord(temp);

        if (p == nullptr) return;

        for (int i = 0;i < 25;++i) {
            this->board->cubes[i]->ifChosen = true;
            this->board->cubes[i]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");;
        }

        for (int i = 0;i < temp.length();++i) {
            this->board->cubes[p[i]]->setStyleSheet("background-color:#FFE4E1; border: 3px solid; border-radius: 15px");
        }
        this->board->currentWord = "";

        this->me->addWord(temp);
        this->me->addScore(temp.length()-3);

        delete [] p;
    }

}


bool BoggleWindow::findCube(QString letter,int *path,int pos,bool *b)
{
    if(pos == letter.length()) return true;

    for (int i = 0;i < 25; ++i) {
        if(!b[i] && this->board->ifAdjoin(i,path[pos-1]) && letter.at(pos) == this->board->cubes[i]->getLetter().toLower()){
            path[pos] = i;b[i] = true;
            if(findCube(letter,path,pos+1,b)) return true;
            b[i] = false;
        }
    }
    return false;
}

int * BoggleWindow::isWord(QString text)
{
    if(text.length() < 4 || !this->flex.contains(text.toStdString())) return nullptr;

    text = text.toLower();
    int length = text.length();
    int *index = new int[length];
    bool *ifChosen = new bool[25];

    for (int i = 0;i < 25;++i) {
        if(this->board->cubes[i]->getLetter().toLower() == text.at(0)){
            index[0] = i;ifChosen[i] = true;
            if(findCube(text,index,1,ifChosen)) return index;
            ifChosen[i] = false;
        }
    }

    return nullptr;
}

void BoggleWindow::addWordToME()
{
    QString word = this->board->currentWord;
    if(this->me->words.contains(word) || this->computer->words.contains(word)) return;
    if(word.length() > 3){
        this->me->addWord(word);
        this->me->addScore(word.length()-3);
    }
}


void BoggleWindow::addWordToComputer()
{
    QString word = this->ai->currentWord;
    if(this->me->words.contains(word) || this->computer->words.contains(word)) return;
    if(word.length() > 3){
        this->computer->addWord(word);
        this->computer->addScore(word.length()-3);
    }
}


void BoggleWindow::computerSearch()
{    
    ai->addALlWords();
}

void BoggleWindow::shake()
{
    this->board->shake();

    me->reset();
    computer->reset();

    QString letters;
    for(int i = 0; i < 25;++i) letters.append(board->cubes[i]->text());
    ai->setBoardLetters(letters);
}

void BoggleWindow::reset()
{
    for (int i = 0;i < 25;++i) {
        this->board->cubes[i]->ifChosen = false;
        this->board->cubes[i]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");;
    }
    this->board->currentWord = "";
}

void BoggleWindow::ALLreset()
{
    me->reset();
    me->wordTable->clear();
    computer->reset();
    me->wordTable->clear();

    for (int i = 0;i < 25;++i) {
        this->board->cubes[i]->ifChosen = false;
        this->board->cubes[i]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");;
    }

}



