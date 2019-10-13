#ifndef DEPO_H
#define DEPO_H

#include <QWidget>
#include <QFile>

#include <lexicon.h>


class Depo : public QWidget
{
    Q_OBJECT

signals:
    void isWord();

public slots:

public:
    explicit Depo(QString b,QWidget *parent = nullptr);
    QString toWord(QStack<int> index);
    void setBoardLetters(QString b);
    void recursion();
    void addALlWords();

public:
    QString currentWord;


private:
    Lexicon *lex;
    QStack<int> *index;
    int size;
    QString boardLetters;
    bool *ifChosen;



};



#endif // DEPO_H
