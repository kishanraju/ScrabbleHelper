#include "Cell.h"

Cell::Cell(int r, int c) : row(r), col(c) {}

void Cell::setWordMultiplier(int multiplier)
{
    wordMultiplier = multiplier;
}

void Cell::setLetterMultiplier(int multiplier)
{
    letterMultiplier = multiplier;
}

int Cell::getWordMultiplier()
{
    return wordMultiplier;
}

int Cell::getLetterMultiplier()
{
    return letterMultiplier;
}

void Cell::setValue(char c)
{
    value = c;
}

char Cell::getValue()
{
    return value;
}

int Cell::getRow()
{
    return row;
}

int Cell::getCol()
{
    return col;
}

bool Cell::isEmpty()
{
    return value == 0;
}

char Cell::getValueToPrint()
{
    if(isEmpty())
        return '-';
    else
        return value;
}
