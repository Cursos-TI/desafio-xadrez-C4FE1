#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct PieceRules{
  int y_target;
  int x_target;
  int y_origin;
  int x_origin;
  bool capture;
  char name;
};
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
bool found_diag(struct PieceRules *Bishop_Queen, char Board[9][9], int bishop_pos[2]){
  bishop_pos[0] = -1;
  bishop_pos[1] = -1;
  bool found_flag =false;
  // Diagonal front-right
  for (int i = Bishop_Queen->y_target + 1, j = Bishop_Queen->x_target + 1; i < 9 && j < 9; i++, j++) {
    if(Board[i][j] != '.' && Board[i][j] !=Bishop_Queen->name){
      break;
    }
    if (Board[i][j] == Bishop_Queen->name) {
      bishop_pos[0]=i;
      bishop_pos[1]=j;
      found_flag =true;
      break;
    }
  }
	    
  // Diagonal front-left
  if(found_flag == false){
    for (int i = Bishop_Queen->y_target + 1, j = Bishop_Queen->x_target - 1; i < 9 && j >= 0; i++, j--) {
      if(Board[i][j] != '.' && Board[i][j] !=Bishop_Queen->name){
	break;
      }
      if (Board[i][j] == Bishop_Queen->name) {
	bishop_pos[0]=i;
	bishop_pos[1]=j;
	found_flag =true;
	break;
      }
    }
  }
  // Diagonal back-right
  if(found_flag == false){ 
    for (int i = Bishop_Queen->y_target - 1, j = Bishop_Queen->x_target + 1; i >= 0 && j < 9; i--, j++) {
      if(Board[i][j] != '.' && Board[i][j] !=Bishop_Queen->name){
	break;
      }
      if (Board[i][j] == Bishop_Queen->name) {
	bishop_pos[0]=i;
	bishop_pos[1]=j;
	found_flag =true;
	break;
      }
    }
  }
  // Diagonal back-left
  if(found_flag == false){
    for (int i = Bishop_Queen->y_target - 1, j = Bishop_Queen->x_target - 1; i >= 0 && j >= 0; i--, j--) {
      if(Board[i][j] != '.' && Board[i][j] !=Bishop_Queen->name){
	break;
      }
      if (Board[i][j] == Bishop_Queen->name) {
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
int bishop_move(bool f_player, struct PieceRules *Bishop ,char Board[9][9]){
  bool found_flag = false;
  int bishop_pos[2];
  
  found_flag = found_diag(Bishop, Board, bishop_pos);
  if(found_flag){
    Board[Bishop->y_target][Bishop->x_target] = Bishop->name;
    Board[bishop_pos[0]][bishop_pos[1]] = '.';
    return 1;
  }
  return 0;
}
void make_L(struct PieceRules *Horse, char Board[9][9], int horse_pos[8][2]){
  for(int i=0;i<8;i++){
    if(Board[Horse->y_target + horse_pos[i][0]][Horse->x_target + horse_pos[i][1]] == Horse->name){
      Board[Horse->y_target + horse_pos[i][0]][Horse->x_target + horse_pos[i][1]] = '.';
      Board[Horse->y_target][Horse->x_target] = Horse->name;
      break;
    }
  }
}
int knight_move(bool f_player, struct PieceRules *Horse, char Board[9][9], int horse_pos[8][2]){
  make_L(Horse, Board, horse_pos);
  return 1;
}
void kings_square(struct PieceRules *King, char Board[9][9], int king_pos[8][2]){

  for(int i=0;i<8;i++){
    if(Board[King->y_target + king_pos[i][0]][King->x_target + king_pos[i][1]] == King->name){
      Board[King->y_target + king_pos[i][0]][King->x_target + king_pos[i][1]] = '.';
      Board[King->y_target][King->x_target] = King->name;
      break;
    }
  }
}
int king_move(bool f_player, struct PieceRules *King, char Board[9][9], int king_pos[8][2],  bool house_attack){
  if(house_attack){
    return 0;
  }
  kings_square(King, Board, king_pos);
  return 1;
}
bool check_attacks(bool f_player, struct PieceRules *King, char Board[9][9], int king_pos[8][2], int horse_pos[8][2]){
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
  if(Board[King->y_target+sum][King->x_target+1] == pawn_char){
    return true;
  }
    
  if(Board[King->y_target+sum][King->x_target-1] == pawn_char){
    return true;
  }
  for(int i = 0; i < 8;i++) {
    if(Board[King->y_target + king_pos[i][0]][King->x_target + king_pos[i][1]] == king_char){
      return true;
    }
  }
  for(int i=1;i<9;i++){
    if(Board[i][King->x_target] == rook_char){
      return true;
    }else if(Board[King->y_target][i] == rook_char){
      return true;
    }
  }
  for(int i=0;i<8;i++){
    if(Board[King->y_target + horse_pos[i][0]][King->x_target + horse_pos[i][1]] == horse_char){
      return true;
    }
  }
  if(found_diag(King, Board, bishop_pos) == true){
    return true;
  }
    return false;
}

int found_line(struct PieceRules *Rook_Queen, char Board[9][9]){
  bool found_piece = false;
  int origin_value;
  for(int i=1;i<9; i++){
    if(found_piece == true){
      return 0;
    }
    if(Board[i][Rook_Queen->x_target] == Rook_Queen->name){
      found_piece = true;
      origin_value = i;
    }
    if(Board[Rook_Queen->y_target][i] == Rook_Queen->name){
      found_piece = true;
      origin_value = i;
    }
  }
  if(found_piece == true){
    return origin_value;
  }
  return 0; // Return 0 if no piece was found in the same line or column
  
}
int rook_move(bool f_player, struct PieceRules *Rook, char Board[9][9]){
  int delta = 18;
  int origin;
  origin = found_line(Rook, Board);
  if(origin - delta < 0 ){
    Board[Rook->y_target][origin] = '.';
    Board[Rook->y_target][Rook->x_target] = Rook->name;
  }else{
    Board[origin][Rook->x_target] = '.';
    Board[Rook->y_target][Rook->x_target] = Rook->name;
  }
  
  return 1;
}
int queen_move(bool f_player,struct PieceRules *Queen , char Board[9][9]){
 
  
  return 0;
}
int pawn_advance(struct PieceRules *Pawn, char Board[9][9], int sum, int mul, int bas){
  if(Pawn->y_target != bas && Board[Pawn->y_target+sum][Pawn->x_target] != Pawn->name){
    if(Board[bas][Pawn->x_target] == Pawn->name && (Pawn->y_target-bas)*mul == 2){
      Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
      Board[bas][Pawn->x_target] = '.';
      return 1;
    }else if(Board[Pawn->y_target+sum][Pawn->x_target] == Pawn->name){
      Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
      Board[Pawn->y_target+sum][Pawn->x_target] = '.';
      return 1;
    }
  }
  return 0;
}
int pawn_move(bool f_player,struct PieceRules *Pawn, char Board[9][9]){
  if(Board[Pawn->y_target][Pawn->x_target] == '.'){
    if(f_player){
      
      if(Pawn->y_target != 7 && Board[Pawn->y_target+1][Pawn->x_target] != Pawn->name){
	if(Board[7][Pawn->x_target] == Pawn->name && 7-(Pawn->y_target) == 2){
	  Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
	  Board[7][Pawn->x_target] = '.';
	  return 1;
	}else if(Board[Pawn->y_target+1][Pawn->x_target] == Pawn->name){
	  Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
	  Board[Pawn->y_target+1][Pawn->x_target] = '.';
	  return 1;
	}
      }
    }else{
      if(Pawn->y_target != 2 && Board[Pawn->y_target -1][Pawn->x_target] != Pawn->name){
	if(Board[2][Pawn->x_target] == Pawn->name && Pawn->y_target-2 == 2){
	  Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
	  Board[2][Pawn->x_target] = '.';
	  return 1;
	}else if(Board[Pawn->y_target-1][Pawn->x_target] == Pawn->name){
	  Board[Pawn->y_target][Pawn->x_target] = Pawn->name;
	  Board[Pawn->y_target-1][Pawn->x_target] = '.';
	  return 1;
	}
      }
    }
  }
  return 0;
}
