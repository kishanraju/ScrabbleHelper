Commands: 

ADD R C D WORD
- adds WORD to the board at row R and column C. If D is “H”, the word is added horizontally, otherwise it is added vertically.

PRINT
- prints the current board

BEST L1 L2 L3 L4 L5 L6 L7
- prints the 5 best moves to make, based on the current state of the board, where L1, …, L7 are the player’s letters in hand (inputted as uppercase). This command outputs 5 rows of the form “R C D WORD X” where R and C are the row and column where the word should be placed, D is the direction (“H” for horizontal or “V” for vertical), WORD is the word to be added, and X is the number of points awarded for the move.