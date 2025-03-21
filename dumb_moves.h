#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int horse_pos[8][2] = {{ 2, 1},
		       {-2,-1},
		       {-2, 1},
		       { 2,-1},
		       { 1, 2},
		       {-1,-2},
		       {-1, 2},
		       { 1,-2}};

int king_pos[8][2] = {{ 1, 1},
		      {-1,-1},
		      {-1, 1},
		      { 1,-1},
		      { 1, 0},
		      {-1, 0},
		      { 0,-1},
		      { 0, 1}};
void print_board(char Board[9][9]){
    for(int i = 0; i < 9; i++){
      
      for(int j = 0; j < 9; j++){
	printf("%c", Board[i][j]);
      }

      printf("\n");
    }
}
void create_board(char Board[9][9]){

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(i == 2 && j!=0){
	Board[i][j] = 'p';
      }else if (i == 7 && j!=0){
	Board[i][j] = 'P'; 
      }else if (i==1 && (j == 3 || j == 6)){
	Board[i][j] = 'b';
      }else if (i==8 && (j == 3 || j == 6)){
	Board[i][j] = 'B';
      }else if (i==8 && (j == 2 || j == 7)){
	Board[i][j] = 'N';
      }else if (i==1 && (j == 2 || j == 7)){
	Board[i][j] = 'n';
      }else if (i==1 && (j == 1 || j == 8)){
	Board[i][j] = 'r';
      }else if (i==8 && (j == 1 || j == 8)){
	Board[i][j] = 'R';
      }else if ((i != 8 || i != 1) && (j != 4 || j != 5)){
	Board[i][j] = '.';
      }
      if(i == 0){
	int intbuf = j+64;
	char buf = (char)intbuf;
	Board[i][j] = buf;
      }
      if(j == 0){
	int intbuf = 57-i;
	char buf = (char)intbuf;
	if(buf != '9'){
	  Board[i][j] = buf;
	}else{
	  Board[i][j] = '@';
	}
      }
      Board[8][4] = 'Q';
      Board[8][5] = 'K';
      Board[1][4] = 'q';
      Board[1][5] = 'k';

    }
  }
}
bool found_diag(int pawn_y_target, int pawn_x_target, char Board[9][9], char piece, int bishop_pos[2]){
  bishop_pos[0] = -1;
  bishop_pos[1] = -1;
  bool found_flag =false;
  // Diagonal front-right
  for (int i = pawn_y_target + 1, j = pawn_x_target + 1; i < 9 && j < 9; i++, j++) {
    if(Board[i][j] != '.' && Board[i][j] !=piece){
      break;
    }
    if (Board[i][j] == piece) {
      bishop_pos[0]=i;
      bishop_pos[1]=j;
      found_flag =true;
      break;
    }
  }
	    
  // Diagonal front-left
  if(found_flag == false){
    for (int i = pawn_y_target + 1, j = pawn_x_target - 1; i < 9 && j >= 0; i++, j--) {
      if(Board[i][j] != '.' && Board[i][j] !=piece){
	break;
      }
      if (Board[i][j] == piece) {
	bishop_pos[0]=i;
	bishop_pos[1]=j;
	found_flag =true;
	break;
      }
    }
  }
  // Diagonal back-right
  if(found_flag == false){ 
    for (int i = pawn_y_target - 1, j = pawn_x_target + 1; i >= 0 && j < 9; i--, j++) {
      if(Board[i][j] != '.' && Board[i][j] !=piece){
	break;
      }
      if (Board[i][j] == piece) {
	bishop_pos[0]=i;
	bishop_pos[1]=j;
	found_flag =true;
	break;
      }
    }
  }
  // Diagonal back-left
  if(found_flag == false){
    for (int i = pawn_y_target - 1, j = pawn_x_target - 1; i >= 0 && j >= 0; i--, j--) {
      if(Board[i][j] != '.' && Board[i][j] !=piece){
	break;
      }
      if (Board[i][j] == piece) {
	bishop_pos[0]=i;
	bishop_pos[1]=j;
	found_flag =true;
	break;
      }
    }
  }
  if(found_flag == true){
    return found_flag;
  }
  return false;
}
int bishop_move(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9], char piece){
  bool found_flag = false;
  int bishop_pos[2];
  
  found_flag = found_diag(pawn_y_target, pawn_x_target, Board, piece, bishop_pos);
  if(found_flag){
    Board[pawn_y_target][pawn_x_target] = piece;
    Board[bishop_pos[0]][bishop_pos[1]] = '.';
    return 1;
  }
  return 0;
}
void make_L(int pawn_y_target, int pawn_x_target, char Board[9][9], int horse_pos[8][2], char piece){
  for(int i=0;i<8;i++){
    if(Board[pawn_y_target + horse_pos[i][0]][pawn_x_target + horse_pos[i][1]] == piece){
      Board[pawn_y_target + horse_pos[i][0]][pawn_x_target + horse_pos[i][1]] = '.';
      Board[pawn_y_target][pawn_x_target] = piece;
      break;
    }
  }
}
int knight_move(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9], int horse_pos[8][2]){
  char piece;
  if(!f_player){
    piece = 'n';
  }else{
    piece = 'N';
  }
  make_L(pawn_y_target, pawn_x_target, Board, horse_pos, piece);
  return 1;
}
void kings_square(int pawn_y_target, int pawn_x_target, char Board[9][9], int king_pos[8][2], char piece){

  for(int i=0;i<8;i++){
    if(Board[pawn_y_target + king_pos[i][0]][pawn_x_target + king_pos[i][1]] == piece){
      Board[pawn_y_target + king_pos[i][0]][pawn_x_target + king_pos[i][1]] = '.';
      Board[pawn_y_target][pawn_x_target] = piece;
      break;
    }
  }
}
int king_move(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9], int king_pos[8][2],  bool house_attack){
  char piece;
  if(!f_player && !house_attack){
    piece = 'k';
  }else if(f_player && !house_attack){
    piece = 'K';
  }else{
    return 0;
  }
  kings_square(pawn_y_target, pawn_x_target, Board, king_pos, piece);
  return 1;
}
bool check_attacks(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9], int king_pos[8][2], int horse_pos[8][2]){
  int bishop_pos[2];
  char pawn_char = 'p';
  char horse_char = 'n';
  char bishop_char = 'b';
  char rook_char = 'r';
  char king_char = 'k';
  int sum = -1;
  if(!f_player){
    pawn_char = 'P';
    horse_char = 'N';
    bishop_char = 'B';
    rook_char = 'R';
    king_char = 'K';
    sum = +1;
  }
  if(Board[pawn_y_target+sum][pawn_x_target+1] == pawn_char){
    return true;
  }
    
  if(Board[pawn_y_target+sum][pawn_x_target-1] == pawn_char){
    return true;
  }
  for(int i = 0; i < 8;i++) {
    if(Board[pawn_y_target + king_pos[i][0]][pawn_x_target + king_pos[i][1]] == king_char){
      return true;
    }
  }
  for(int i=1;i<9;i++){
    if(Board[i][pawn_x_target] == rook_char){
      return true;
    }else if(Board[pawn_y_target][i] == rook_char){
      return true;
    }
  }
  for(int i=0;i<8;i++){
    if(Board[pawn_y_target + horse_pos[i][0]][pawn_x_target + horse_pos[i][1]] == horse_char){
      return true;
    }
  }
  
  if(found_diag(pawn_y_target, pawn_x_target, Board, bishop_char, bishop_pos) == true){
    return true;
  }
    return false;
}

int found_line(int pawn_y_target, int pawn_x_target, char Board[9][9], bool capture, char piece){
  for(int)
  
  return 0; // Return 0 if no piece was found in the same line or column
  
}
int rook_move(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9], bool capture, char piece){
  int delta = 18;
  int origin;
  
  origin = found_line(pawn_y_target, pawn_x_target, Board, capture, piece, delta);
  if(origin - delta < 0 ){
    Board[pawn_y_target][origin] = '.';
    Board[pawn_y_target][pawn_x_target] = piece;
  }else{
    origin -= delta;
    Board[origin][pawn_x_target] = '.';
    Board[pawn_y_target][pawn_x_target] = piece;
  }
  
  return 1;
}
int queen_move(bool f_player, int pawn_y_target, bool capture, int pawn_x_target, char Board[9][9], char piece){
 
  
  return 0;
}
int pawn_move(bool f_player, int pawn_y_target, int pawn_x_target, char Board[9][9]){
  if(Board[pawn_y_target][pawn_x_target] == '.'){
    if(f_player){
      if(pawn_y_target != 7 && Board[pawn_y_target+1][pawn_x_target] != 'P'){
	if(Board[7][pawn_x_target] == 'P' && 7-pawn_y_target == 2){
	  Board[pawn_y_target][pawn_x_target] = 'P';
	  Board[7][pawn_x_target] = '.';
	}else if(Board[pawn_y_target+1][pawn_x_target] == 'P'){
	  Board[pawn_y_target][pawn_x_target] = 'P';
	  Board[pawn_y_target+1][pawn_x_target] = '.';
	}else{
	  return 0;
	}
      }else{
	return 0;
      }
    }else{
      if(pawn_y_target != 2 && Board[pawn_y_target -1][pawn_x_target] != 'p'){
	if(Board[2][pawn_x_target] == 'p' && pawn_y_target-2 == 2){
	  Board[pawn_y_target][pawn_x_target] = 'p';
	  Board[2][pawn_x_target] = '.';
	}else if(Board[pawn_y_target-1][pawn_x_target] == 'p'){
	  Board[pawn_y_target][pawn_x_target] = 'p';
	  Board[pawn_y_target-1][pawn_x_target] = '.';
	}else{
	  return 0;
	}
      }else{
	return 0;
      }
    }
  }else{
    return 0;
  }
  return 1;
}
