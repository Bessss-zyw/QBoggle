#include "Depo.h"

#include <QtDebug>
#include <qmath.h>
#include <qstack.h>


Depo::Depo(QString b,QWidget *parent) : QWidget(parent)
{
    size = (b.length()%2 == 0?4:5);
    boardLetters = b;
    ifChosen = nullptr;
    qDebug() << "new file name recursion";

    currentWord = "abc";

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    this->lex = new Lexicon(qFile);

}


QString Depo::toWord(QStack<int> s)
{
    QString word;
    QStack<int> tmp;

    while(!s.isEmpty()) {
        word.insert(0,boardLetters.at(s.top()));
        tmp.push(s.pop());
    }
    while(!tmp.isEmpty()) {
        s.push(tmp.pop());
    }

    return word.toLower();
}


void Depo::setBoardLetters(QString b)
{
    this->boardLetters = b;
}

void Depo::recursion()
{
    if(index->isEmpty()) return;

    QString temp = toWord(*index);

    if(this->lex->containsPrefix(temp.toStdString())){
        if(this->lex->contains(temp.toStdString())){
            this->currentWord = temp;
            emit isWord();
        }

        int ax = index->top() / size,ay = index->top() % size;
        for (int i = 0;i < size*size;++i) {
            int ix = i / size,iy = i % size;
            if(!ifChosen[i] && ix-ax >= -1 && ix-ax <= 1 && iy-ay >= -1 && iy-ay <= 1){
                index->push(i);ifChosen[i] = true;
                recursion();
                index->pop();ifChosen[i] = false;
            }
        }
    }
    else if(this->lex->contains(temp.toStdString())){
        this->currentWord = temp;
        emit isWord();
    }



/*    switch(WordSituation(temp))
    {
    case 0:
        return;
    case 1:
        if(temp.length() > 3) {
            this->currentWord = temp;
            emit isWord();}
        return;
    case 2:    case 3:
        if(WordSituation(temp) == 3 && temp.length() >3){
            this->currentWord = temp;
            emit isWord();
        }

        int ax = index->top() / size,ay = index->top() % size;
        for (int i = 0;i < size*size;++i) {
            int ix = i / size,iy = i % size;
            if(!ifChosen[i] && ix-ax >= -1 && ix-ax <= 1 && iy-ay >= -1 && iy-ay <= 1){
                index->push(i);ifChosen[i] = true;
                recursion();
                index->pop();ifChosen[i] = false;
            }
        }
    }
*/
}


//recursion
void Depo::addALlWords()
{
    index = new QStack<int>;
    ifChosen = new bool[size*size];

    for(int i = 0;i < size*size;++i)
    {
        qDebug() << i << "recurson";
        index->push(i);ifChosen[i] = true;
        recursion();
        index->pop();ifChosen[i] = false;

    }

    delete index;
}


/*
int Depo::WordSituation(QString text)
{

      no such word = 0
     * is a word = 1
     * posible to be a word = 2
     * is a word and posible to be longer = 3



    if(words.contains(text+'\n')){
        str = words.value(words.indexOf(text)+1);
        str.resize(text.length());
        if(str == text) return 3;
        else return 1;
    }


    QString str;
    int i = words.indexOf(text.left(1));
    bool isWord = 0;
    while(i < words.length()){
        str = words.value(i);

        if(str == text) isWord = 1;
        else if(str > text){
            str.resize(text.length());
            if(str == text && isWord) return 3;
            else if(str == text && !isWord) return 2;
            else if(isWord) return 1;
            else return 0;
        }
        ++i;
    }
    return false;


    bool isWord = 0;
    QString flag = myfile->readLine();
    flag.remove(flag.length()-1,1);
    QString string;
    while(string != flag){
//        QByteArray line = myfile->readLine();
        string = myfile->readLine();
        QString str(string.remove(string.length()-1,1));

        if(str == text)
            isWord = 1;
        else if(str > text){
            str.resize(text.length());
            if(str == text && isWord == 1) {
                return 3;
            }
            else if(str == text && isWord == 0) {
                return 2;
            }
            else if(str != text && isWord == 1) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return false;


     if(this->lex->contains(text.toStdString()))
     {
         if(this->lex->containsPrefix(text.toStdString())) return 3;
         else return 1;
     }
     else {
         if(this->lex->containsPrefix(text.toStdString())) return 2;
         else return 0;
     }

}

*/
