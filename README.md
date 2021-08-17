# Game game

Game game with command line interface

General game information and rules can be read at https://en.wikipedia.org/wiki/Mastermind_(board_game).

## Program arguments

1. Number of colors a code peg can have
2. Number of pegs per code
3. Number of rows in a game  
4. Number of games to play

all arguments are to be integers otherwise default values are used.

## Peg representation

Empty code pegs and key pegs are represented by 0.

Code peg color is represented as numbers from 1 up to 9 depending on program argument 1.

Key peg color is represented by 

- (1) indicating that code peg has the right color but not the right position
- (2) indicating that code peg has the right color and position 

## Game procedure

First the two players has to agree who is player 0 and player 1. Player 0 starts as the code maker 

The game starts by the code maker entering a secrete code, this code is not shown in the terminal and the code maker thus needs to remember it them selves. Next the code maker is prompted for a code guess for which the code breaker is prompted for feedback. In between rounds the game board will be shown in the terminal and at the end of a game the current score is also shown.
