#include "Board.h"
#include "Word.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

std::vector<std::string> Board::dictionary;
std::map<char, int> Board::points;

Board::Board()
{
    for(int r = 0; r < 15; r++)
    {
        std::vector<Cell> row;
        for(int c = 0; c < 15; c++)
        {
            row.push_back(Cell(r, c));
        }
        cells.push_back(row);
    }
    
    std::string word;
    char character;
    int val;
    std::ifstream dictionaryFile("./dictionary.txt");
    std::ifstream pointsFile("./points.txt");

    while(dictionaryFile >> word)
        Board::dictionary.push_back(word);

    while(pointsFile >> character >> val)
        Board::points.insert(std::pair<char, int>(character, val));
    
    std::ifstream doubleLetter("./DoubleLetter.txt");
    std::ifstream doubleWord("./DoubleWord.txt");
    std::ifstream trippleLetter("./TrippleLetter.txt");
    std::ifstream trippleWord("./TrippleWord.txt");
    
    int r=0, c=0;
    while(doubleLetter >> r >> c)
    {
        cells[r][c].setLetterMultiplier(2);
    }
    
    while(doubleWord >> r >> c)
    {
        cells[r][c].setWordMultiplier(2);
    }
    
    while(trippleLetter >> r >> c)
    {
        cells[r][c].setLetterMultiplier(3);
    }
    
    while(trippleWord >> r >> c)
    {
        cells[r][c].setWordMultiplier(3);
    }
}

void Board::addWord(int row, int col, char direction, std::string word)
{
    for(char c : word)
    {
        if(row >= 0 && col >= 0 && row < 15 && col < 15)
        {
            cells[row][col].setValue(c);
            cells[row][col].setWordMultiplier(1);
            cells[row][col].setLetterMultiplier(1);
        }
        
        if(direction == 'H')
            col++;
        else
            row++;
    }
}

std::map<char, int> getHashMap()
{
    std::map<char, int> map;
    for(char letter = 'A'; letter <= 'Z'; letter++)
    {
        map[letter] = 0;
    }
    
    return map;
}

bool hasRequiredLetters(std::map<char, int>& owned, std::map<char, int>& required)
{
    for(char letter = 'A'; letter <= 'Z'; letter++)
    {
        if(owned[letter] < required[letter])
        {
            return false;
        }
    }
    
    return true;
}

bool hasLetters(std::string word, std::map<char, int> lettersOwned)
{
    for(char letter : word)
    {
        if(lettersOwned[letter] == 0)
            return false;
        lettersOwned[letter]--;
    }
    
    return true;
}

std::vector<std::string> Board::getEligibleWords(std::map<char, int> lettersOwned, std::vector<Cell>& cells)
{
    std::vector<std::string> words;
    for(Cell cell: cells)
    {
        if(!cell.isEmpty())
            lettersOwned[cell.getValue()]++;
    }
    
    for(std::string word : dictionary)
    {
        if(hasLetters(word, lettersOwned))
           words.push_back(word);
    }
    
    return words;
}

void Board::findMatches(std::vector<Cell>& cells, std::map<char, int> lettersOwned, char direction, std::vector<Word>& results)
{
    std::vector<std::string> words = getEligibleWords(lettersOwned, cells);
    
    for(std::string word : words)
    {
        int start = 0;
        while(start <= 15 - word.size())
        {
            bool valid = true;
            bool hasLetter = false;
            bool usesLetter = false;
            std::map<char, int> lettersRequired = getHashMap();
            if((start > 0 && !cells[start-1].isEmpty()) || (start + word.size() < 15 && !cells[start+word.size()].isEmpty()))
                valid = false;
            else
            {
                for(int i = 0; i < word.size(); i++)
                {
                    if(!cells[start+i].isEmpty())
                    {
                        hasLetter = true;
                    }
                    
                    if(!cells[start+i].isEmpty() && cells[start+i].getValue() != word[i])
                    {
                        valid = false;
                        break;
                    }
                    else if(cells[start+i].isEmpty())
                    {
                        usesLetter = true;
                        lettersRequired[word[i]]++;
                        if(direction == 'H')
                        {
                            int r1 = cells[0].getRow() + 1;
                            int r2 = cells[0].getRow() - 1;
                            if((r1 <= 14 && !this->cells[r1][start+i].isEmpty()) || (r2 >= 0 && !this->cells[r2][start+i].isEmpty()))
                            {
                                valid = false;
                                break;
                            }
                        }
                        else
                        {
                            int c1 = cells[0].getCol() + 1;
                            int c2 = cells[0].getCol() - 1;
                            if((c1 <= 14 && !this->cells[start+i][c1].isEmpty()) || (c2 >= 0 && !this->cells[start+i][c2].isEmpty()))
                            {
                                valid = false;
                                break;
                            }
                        }
                    }
                }
            }
            
            if(valid && usesLetter && hasLetter && hasRequiredLetters(lettersOwned, lettersRequired))
            {
                //std::cout << cells[start].getRow() << " " << cells[start].getCol() << " " << direction << " " << word << " ";
                Word newWord(cells[start].getRow(), cells[start].getCol(), direction, word);
                newWord.score = getScore(newWord);
                results.push_back(newWord);
                //std::cout << getScore(results.back()) << std::endl;
            }
            
            start++;
        }
    }
}

std::vector<Cell> Board::getColumn(int col)
{
    std::vector<Cell> column;
    for(int r = 0; r < 15; r++)
    {
        column.push_back(cells[r][col]);
    }
    
    return column;
}

int Board::getScore(Word word)
{
    int row = word.row;
    int col = word.col;
    int wordMultiplier = 1;
    int sum = 0;
    for(int i = 0; i < word.word.size(); i++)
    {
        sum += Board::points[word.word[i]] * cells[row][col].getLetterMultiplier();
        wordMultiplier *= cells[row][col].getWordMultiplier();
        
        if(word.direction == 'H')
            col++;
        else
            row++;
    }
    
    return sum*wordMultiplier;
}

bool wordsComp(Word w1, Word w2)
{
    return w1.score > w2.score;
}

void Board::findBestMove(std::vector<char>& letters)
{
    std::map<char, int> lettersOwned = getHashMap();
    std::vector<Word> words;
    
    for(char l : letters)
    {
        lettersOwned[l]++;
    }
    
    for(std::vector<Cell>& row : getRows())
    {
        std::cout << words.size() << std::endl;
        findMatches(row, lettersOwned, 'H', words);
    }
    
    for(std::vector<Cell>& col : getColumns())
    {
        std::cout << words.size() << std::endl;
        findMatches(col, lettersOwned, 'V', words);
    }
        
    std::sort(words.begin(), words.end(), wordsComp);
    
    for(int i = 0; i < 5; i++)
    {
        std::cout << words[i].row << " " << words[i].col << " " << words[i].direction << " " << words[i].word << " " << words[i].score << std::endl;
    }
}

std::vector<std::vector<Cell>> Board::getRows()
{
    std::vector<std::vector<Cell>> rows;
    for(std::vector<Cell>& row : cells)
    {
        bool hasLetter = false;
        for(Cell& c : row)
        {
            if(!c.isEmpty())
                hasLetter = true;
        }
        
        if(hasLetter)
            rows.emplace_back(row);
    }
    
    return rows;
}

std::vector<std::vector<Cell>> Board::getColumns()
{
    std::vector<std::vector<Cell>> columns;
    for(int col = 0; col < 15; col++)
    {
        bool hasLetter = false;
        std::vector<Cell> column;
        for(int row = 0; row < 15; row++)
        {
            column.push_back(cells[row][col]);
            if(!cells[row][col].isEmpty())
                hasLetter = true;
        }
        
        if(hasLetter)
            columns.emplace_back(column);
    }
    
    return columns;
}

void Board::print()
{
    for(int i = 0; i < 15; i++)
    {
        std::cout << cells[i][0].getValueToPrint();
        for(int j = 1; j < 15; j++)
        {
            std::cout << " " << cells[i][j].getValueToPrint();
        }
        std::cout << std::endl;
    }
}
