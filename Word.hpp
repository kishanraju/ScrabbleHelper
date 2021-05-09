#ifndef Word_hpp
#define Word_hpp

#include <stdio.h>
#include <string>

struct Word
{
    Word() = default;
    int row, col, score=0;
    char direction;
    std::string word;
    Word(int row, int col, char direction, std::string word);
};


#endif /* Word_hpp */
