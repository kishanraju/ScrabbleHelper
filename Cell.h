#ifndef SCRABBLEAI_CELL_H
#define SCRABBLEAI_CELL_H

class Cell
{
    int wordMultiplier = 1;
    int letterMultiplier = 1;
    int row, col;
    char value = 0;
public:
    Cell(int row, int col);
    void setWordMultiplier(int);
    void setLetterMultiplier(int);
    int getWordMultiplier();
    int getLetterMultiplier();
    void setValue(char c);
    char getValue();
    bool isEmpty();
    int getRow();
    int getCol();
    char getValueToPrint();
};


#endif //SCRABBLEAI_CELL_H
