#include "Board.h"
#include "Cube.h"

#include <QGridLayout>
#include <QtDebug>
#include <QChar>
#include <QTextStream>

int generateRandomNumber(int min,int max)
{
    int v = QRandomGenerator::global()->bounded(min, max+1);
    return v;
}


const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];
    this->wordIndex = new int[size*size];

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    Lexicon temp(qFile);
    this->lex = temp;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->letters[index(i, j)].at(0));
        }
    }
    // this->setStyleSheet("background-color:grey; border: 3px solid");

    for(int i = 0;i < size*size;++i)
        connect(this->cubes[i],SIGNAL(clicked()),this,SLOT(mousePress()));
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}


void Board::shake()
{
    // Shake Cubes
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->letters[index(i, j)].at(generateRandomNumber(0,5)));
            this->cubes[index(i, j)]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
            this->cubes[index(i, j)]->ifChosen = false;
        }
    }
    currentWord = "";

}

bool Board::ifAdjoin(int a, int b)
{
    int ax = a / size, ay = a % size;
    int bx = b / size, by = b % size;
    if(ax - bx >= -1 && ax - bx <= 1 && ay - by >= -1 && ay-by <= 1) return true;
    return false;
}

void Board::mousePress()
{
    for (int i = 0;i < size*size;++i) {
        if (this->cursor().pos().x() > mapToGlobal(cubes[i]->pos()).x() && this->cursor().pos().x() < mapToGlobal(cubes[i]->pos()).x() + 50
                && this->cursor().pos().y() > mapToGlobal(cubes[i]->pos()).y()   && this->cursor().pos().y() < mapToGlobal(cubes[i]->pos()).y() + 50)
        {
            if(cubes[i]->ifChosen){
                //judge legality
                if(i != wordIndex[currentWord.length()-1]) return;

                cubes[i]->ifChosen = false;
                this->cubes[i]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
                currentWord.remove(currentWord.length()-1,1);
            }
            else {
                //judge legality
                if(currentWord.length() != 0 && !ifAdjoin(wordIndex[currentWord.length()-1],i)) return;

                cubes[i]->ifChosen = true;
                this->cubes[i]->setStyleSheet("background-color:grey; border: 3px solid; border-radius: 15px");
                wordIndex[currentWord.length()] = i;
                currentWord.append(cubes[i]->text().toLower());

                if(this->lex.contains(currentWord.toStdString())){
                    emit isWord();

                    if(!this->lex.containsPrefix(currentWord.toStdString())){
                        for (int m = 0;m < currentWord.length();++m) {
                            cubes[wordIndex[m]]->ifChosen = false;
                            cubes[wordIndex[m]]->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
                        }
                        currentWord = "";
                    }
                }

            }

            qDebug() << currentWord;
            return;
        }
    }
}

