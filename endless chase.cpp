#include<iostream>

#include<random>

#include<stdio.h>

#include<stdlib.h>

constexpr int N = 8; // board size
using board_type = bool[N][N]; // array

//board is valid
bool valid(int row_or_col) {
  return row_or_col >= 0 && row_or_col < N;
}
//use for clear board
void clear(board_type & board) {
  for (auto & row: board)
    for (auto & v: row) v = false;
}
//
void set_if_valid(board_type & board, int row, int col) {
  if (valid(row) && valid(col)) board[row][col] = true;
}
//function for select possibile moves for knight with destination position
void possibile_knight_moves(board_type & board, int row, int col) {
  clear(board);
  //search knight target position col and row
  if (valid(row) && valid(col)) {
    for (const int row_delta: {
        -2,
        +2
      })
      for (const int col_delta: {
          -1,
          +1
        }) {
        set_if_valid(board, row + row_delta, col + col_delta);
      }

    for (const int row_delta: {
        -1,
        +1
      })
      for (const int col_delta: {
          -2,
          +2
        }) {
        set_if_valid(board, row + row_delta, col + col_delta);
      }
  }
}

//======chess board class=========
class ChessBoard {
  public: static
  const int ROWS = 8,
    COLS = 8;
  //constructor
  ChessBoard() {}
  //clear func
  void clear();
  char getValue(int row, int col) const {
    return data[row][col];
  }
  void show() const;
  private:
    char data[ROWS][COLS];
};
//set all array val = ' '
void ChessBoard::clear() {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      data[row][col] = ' ';
    }
  }
}
//show chess board array with col and row in array
void ChessBoard::show() const {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      //out << getValue(row, col) << ' ';
      std::cout << '(' << row << ',' << col << ')' << ' ';
    }
    std::cout << std::endl;
  }
}

//===============
bool canQueenAttack(int qR, int qC, int oR, int oC) {
  // If queen and the opponent are in the same row 
  if (qR == oR)
    return true;

  // If queen and the opponent are in the same column 
  if (qC == oC)
    return true;

  // If queen can attack diagonally 
  if (abs(qR - oR) == abs(qC - oC))
    return true;

  // Opponent is safe 
  return false;
}
int main() {
  board_type board {}; // array
  //srand and time for random choice
  srand((unsigned) time(0));
  //define queen row and col and knight row and col random
  int qR, qC, kR = (rand() % 8), kC = (rand() % 8);
  int row, col = 0;
  //use chess board class for show board
  ChessBoard cboard;
  cboard.show();
  std::cout << sizeof(board) << std::endl;
  std::cout << "Please enter row and col of queen position example 3 2 " << std::endl;
  std::cin >> qR >> qC;
  std::cout << "Queen init position" << '(' << qR << ',' << qC << ')' << std::endl;
  std::cout << "knight init position" << '(' << kR << ',' << kC << ')' << std::endl;
  int newqR, newqC;
  int counter = 0;
  //if turn: false--->queen , true --> knight
  bool turn = false;
  while (true) {
    //if queen action
    if (!turn) {
      //if queen can not attack knight
      if (!canQueenAttack(qR, qC, kR, kC)) {
        //select random position for queen
        newqR = (rand() % 8), newqC = (rand() % 8);
        //if selected queen random position is true and new position threat knight.
        if (canQueenAttack(qR, qC, newqR, newqC) &&
          canQueenAttack(newqR, newqC, kR, kC)) {
          //set new position for queen.     
          qR = newqR, qC = newqC;
        }
      }
      //if queen can attack knight! 
      else {
        //print queen position.
        std::cout << "Queen position" << '(' << qR << ',' << qC << ')' << std::endl;
        //knight must do next action
        turn = true;
      }
    }
    //if knight action
    else {
      ///put current knight position to row and col 
      col = kC;
      row = kR;
      //give row and col to function for searching...
      possibile_knight_moves(board, row, col);
      //if loop state equal to false exit current loop
      bool loopstat = true;
      //loop for search in chess board for knight possible ways
      for (int row = 0; row < N; ++row)
        for (int col = 0; col < N && loopstat == true; ++col) {
          //select possible knight way that not threaten by queen!
          if (board[row][col] == true &&
            canQueenAttack(qR, qC, row, col) == false) {
            //set this row and col to knight position
            kR = row;
            kC = col;
            std::cout << "knight position" << '(' << kR << ',' << kC << ')' << std::endl;
            std::cout << "=================" << std::endl;
            //set loopstat false to exit current loop
            loopstat = false;
            //queen must do next action
            turn = false;
          }
        }
    }
  }
  return 0;
}