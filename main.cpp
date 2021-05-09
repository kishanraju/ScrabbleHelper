#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Board.h"

std::vector<std::string> dictionary;
std::map<char, int> points;

int main()
{
    Board board = Board();
    
    while(true)
    {
        std::string command;
        std::cin >> command;
        
        if(command == "ADD")
        {
            int row, col;
            char direction;
            std::string word;
            std::cin >> row;
            std::cin >> col;
            std::cin >> direction;
            std::cin >> word;
            board.addWord(row, col, direction, word);
        }
        else if(command == "BEST")
        {
            std::vector<char> letters;
            for(int i = 0; i < 7; i++)
            {
                char letter;
                std::cin >> letter;
                letters.push_back(letter);
            }
            
            board.findBestMove(letters);
        }
        else if(command == "PRINT")
        {
            board.print();
        }
    }
}
