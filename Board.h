#ifndef SCRABBLEAI_BOARD_H
#define SCRABBLEAI_BOARD_H


#include <vector>
#include <map>
#include "Cell.h"
#include "Word.hpp"

class Board
{
    std::vector<std::vector<Cell>> cells;
public:
    static std::vector<std::string> dictionary;
    static std::map<char, int> points;
    Board();
    void addWord(int row, int col, char direction, std::string word);
    void findBestMove(std::vector<char>& letters);
    void print();
    std::vector<std::vector<Cell>> getColumns();
    std::vector<std::vector<Cell>> getRows();
    std::vector<std::string> getEligibleWords(std::map<char, int> lettersOwned, std::vector<Cell>& cells);
    void findMatches(std::vector<Cell>& cells, std::map<char, int> lettersOwned, char direction, std::vector<Word>& results);
    std::vector<Cell> getColumn(int);
    int getScore(Word word);
};


#endif //SCRABBLEAI_BOARD_H
