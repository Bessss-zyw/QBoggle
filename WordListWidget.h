#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include "WordTable.h"

#include <QWidget>
#include <QLabel>

class WordListWidget : public QWidget
{
    friend class BoggleWindow;

    Q_OBJECT
public:
    explicit WordListWidget(QWidget *parent = nullptr, QString label = "");
    void addScore(int s);
    void addWord(QString word);
    void reset();
signals:

public slots:

private:
    QLabel *scoreLabel;
    QString label;
    QList<QString> words;
    int score;
    WordTable *wordTable;
};

#endif // WORDLISTWIDGET_H
