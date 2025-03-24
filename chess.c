#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define BOARD_SIZE 8

int knight_pos[8][2] = {{ 2, 1},
		       {-2,-1},
		       {-2, 1},
		       { 2,-1},
		       { 1, 2},
		       {-1,-2},
		       {-1, 2},
		       { 1,-2}};

struct MoveData{
  bool f_player;
  int yx_target_arr[2];
  int yx_origin_arr[2];
  bool capture;
  char name;
  //example 1: up, 2:right, 3: down, 4:left
  int change_pos;
};

void create_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Initialize the chessboard with empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '.';
        }
    }

    // White pieces
    board[0][0] = board[0][7] = 'R';  // Rooks
    board[0][1] = board[0][6] = 'N';  // Knights
    board[0][2] = board[0][5] = 'B';  // Bishops
    board[0][3] = 'Q';                // Queen
    board[0][4] = 'K';                // King
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = 'P';  // Pawns
    }

    // Black pieces
    board[7][0] = board[7][7] = 'r';  // Rooks
    board[7][1] = board[7][6] = 'n';  // Knights
    board[7][2] = board[7][5] = 'b';  // Bishops
    board[7][3] = 'q';                // Queen
    board[7][4] = 'k';                // King
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[6][i] = 'p';  // Pawns
    }
}
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
int found_line(struct MoveData *piece, char board[BOARD_SIZE][BOARD_SIZE]){
    int found_piece = 0;
    int directions[4][2] = {{ 0, 1},  // Right
                             { 0,-1},  // Left
                             { 1, 0},  // Down
                             {-1, 0}}; // Up

    for(int dir = 0; dir < 4; dir++){
        int i = piece -> yx_target_arr[0] + directions[dir][0];
        int j = piece -> yx_target_arr[1] + directions[dir][1];
        
        // Iterate in the current direction
        while(i >= 0 && i < 8 && j >= 0 && j < 8){
	  if(board[i][j] != '.' && board[i][j] != piece -> name  && ! piece -> capture){
              break;  // Stop if blocked
          }
            if(board[i][j] == piece -> name){
                piece -> yx_origin_arr[0] = i;
                piece -> yx_origin_arr[1] = j;
                found_piece++;
            }
            i += directions[dir][0];
            j += directions[dir][1];
        }

        if(found_piece > 1){
            printf("Invalid move identify the ");
            return found_piece;  // Return early if more than one piece is found
        }
    }

    return found_piece;
}
int found_diag(struct MoveData *piece, char board[BOARD_SIZE][BOARD_SIZE]){
  int found_piece = 0;
  int directions[4][2] = {{ 1, 1},
			  { 1,-1},
			  {-1, 1},
			  {-1,-1}};
  for(int dir = 0; dir < 4; dir++){
    int i = piece -> yx_target_arr[0] + directions[dir][0];
    int j = piece -> yx_target_arr[1] + directions[dir][1];
    while(i >= 0 && i < 8 && j >= 0 && j < 8){
      if(board[i][j] != '.' && board[i][j] != piece -> name && !piece -> capture){
	//printf("Invalid move the bishop in %c%d is blocked.\n", (char) j+65,i);
	break;
      }
      if(board[i][j] == piece -> name){
	piece -> yx_origin_arr[0] = i;
	piece -> yx_origin_arr[1] = j;
	found_piece++;
      }
      i += directions[dir][0];
      j += directions[dir][1];
    }
    if( found_piece > 1){
      printf("Invalid move identify the ");
      return found_piece;
      break;
    }
  }
  return found_piece;
}
int queen_move(struct MoveData *queen, char board[BOARD_SIZE][BOARD_SIZE]){
  if(found_line( queen, board) == 0){
    if(found_diag( queen, board) == 0){
      printf("Invalid move no queen founded.\n");
      return 0;
    }else if(found_diag( queen, board) > 1){
      printf("queen.\n");
      return 0;
    }    
  }else if(found_line( queen, board) > 1){
    printf("queen.\n");
    return 0;
  }
  
  if(queen -> f_player ? isupper(board[ queen -> yx_target_arr[0] ][ queen -> yx_target_arr[1] ]) : islower(board[ queen -> yx_target_arr[0] ][ queen -> yx_target_arr[1] ])){
    printf("Invalid move can't capture your own pieces.\n");
    return 0;
  }
  board[ queen -> yx_origin_arr[0] ][ queen -> yx_origin_arr[1] ] = '.';  
  board[ queen -> yx_target_arr[0] ][ queen -> yx_target_arr[1] ] = queen -> name;
  return 1;
}
int rook_move(struct MoveData *rook, char board[BOARD_SIZE][BOARD_SIZE]){
  if(found_line( rook, board) == 0){
    printf("Invalid move no rook founded.\n");
    return 0;
  }else if(found_line( rook, board) > 1){
    printf("rook.\n");
    return 0;
  }
  if(rook -> f_player ? isupper(board[ rook -> yx_target_arr[0] ][ rook -> yx_target_arr[1] ]) : islower(board[ rook -> yx_target_arr[0] ][ rook -> yx_target_arr[1] ])){
    printf("Invalid move can't capture your own pieces.\n");
    return 0;
  }
  board[ rook -> yx_origin_arr[0] ][ rook -> yx_origin_arr[1] ] = '.';  
  board[ rook -> yx_target_arr[0] ][ rook -> yx_target_arr[1] ] = rook -> name;
  return 1;
}
int bishop_move(struct MoveData *bishop, char board[BOARD_SIZE][BOARD_SIZE]){
  if(found_diag( bishop, board) == 0){
    printf("Invalid move no bishop founded.\n");
    return 0;
  }else if(found_diag( bishop, board) > 1){
    printf("bishop.\n");
    return 0;
  }
  
  if(bishop -> f_player ? isupper(board[ bishop -> yx_target_arr[0] ][ bishop -> yx_target_arr[1] ]) : islower(board[ bishop -> yx_target_arr[0] ][ bishop -> yx_target_arr[1] ])){
    printf("Invalid move can't capture your own pieces.\n");
    return 0;
  }
  board[ bishop -> yx_origin_arr[0] ][ bishop -> yx_origin_arr[1] ] = '.';  
  board[ bishop -> yx_target_arr[0] ][ bishop -> yx_target_arr[1] ] = bishop -> name;
  return 1;
}
int knight_move(struct MoveData *knight, int knight_pos[8][2],char board[BOARD_SIZE][BOARD_SIZE]){
  if(board[ knight -> yx_target_arr[0] ][ knight -> yx_target_arr[1] ] != '.' && !knight -> capture){
    return 0;
  }
  int horses_found = 0;
  for(int i = 0; i < 8; i++){
    int target_y = knight->yx_target_arr[0] + knight_pos[i][0];
    int target_x = knight->yx_target_arr[1] + knight_pos[i][1];
    
    // Print the new target positions (for debugging purposes)
    printf("Move possibility: Target = (%d, %d), Current = (%d, %d) + (%d, %d)\n",
	   target_y, target_x, knight->yx_target_arr[0], knight->yx_target_arr[1],
           knight_pos[i][0], knight_pos[i][1]);
    
    // Check if a valid target position has been found (you might want to use this to validate moves)
    if ( board[ target_y ][ target_x ] == knight -> name) {
      knight -> yx_origin_arr[0] = target_y;
      knight -> yx_origin_arr[1] = target_x;
      horses_found++;
    }
  }
  if( horses_found == 0){
    printf("Invalid move no knight founded\n");
    return 0;
  }else if( horses_found > 1){
    printf("Invalid move identify the knight.\n");
    return 0;
  }else if( board[ knight -> yx_origin_arr[0] ][ knight -> yx_origin_arr[1] ] == knight -> name){
    board[ knight -> yx_origin_arr[0] ][ knight -> yx_origin_arr[1] ] = '.';
  }
  
  board[ knight -> yx_target_arr[0] ][ knight -> yx_target_arr[1] ] = knight -> name;
  return 1;
}
int pawn_capture(struct MoveData *pawn, char board[BOARD_SIZE][BOARD_SIZE]){
      
  int sum = +1;
  pawn -> name = 'p';

  if(pawn -> f_player){
    pawn -> name = 'P';
    sum = -1;
  }
  if(! board[ pawn -> yx_target_arr[0] + sum ][ pawn -> yx_origin_arr[1] ] == pawn -> name){
    return 0;
  }
  board[ pawn -> yx_target_arr[0] ][ pawn -> yx_target_arr[1] ] = pawn -> name;
  board[ pawn -> yx_target_arr[0] + sum ][ pawn -> yx_origin_arr[1] ] = '.';

  return 1;
}
int pawn_move(struct MoveData *pawn, char board[BOARD_SIZE][BOARD_SIZE]){
  int start = pawn -> yx_target_arr[0];
  int end = pawn -> f_player ? 1 : 6;
  int increment = pawn -> f_player ? -1 : 1;
  if(board[ pawn -> yx_target_arr[0] ][ pawn -> yx_target_arr[1] ] != '.')
    return 0;
  for (int i = start; pawn -> f_player ? i > end : i < end; i += increment) {
    if (board[i][ pawn -> yx_target_arr[1] ] != '.' && i != pawn -> yx_target_arr[0] +increment) {
      return 0;
    }
  }
  if( abs(start - end) == 2 && board[ end ][ pawn -> yx_target_arr[1] ] == pawn -> name){
    board[ end ][ pawn -> yx_target_arr[1] ] = '.';
  }else if(board[ pawn -> yx_target_arr[0] + increment][ pawn -> yx_target_arr[1] ]  == pawn -> name){
    board[ pawn -> yx_target_arr[0] + increment ][ pawn -> yx_target_arr[1] ] = '.';
  }else{
    return 0;
  }
  board [ pawn -> yx_target_arr[0] ][ pawn -> yx_target_arr[1] ] = pawn -> name;
  
  return 1;
}
int parse_moves(struct MoveData *move, char movement[6], int knight_pos[8][2], char board[BOARD_SIZE][BOARD_SIZE],bool *game_end){
  int movement_size = strlen(movement);
  move -> yx_target_arr[0] = (int) movement[ movement_size -1 ] - '1';
  move -> yx_target_arr[1] = (int) tolower(movement[ movement_size -2 ]) - 'a';
  switch (movement_size){
    case 2:
      move -> name = 'p';
      if(move -> f_player)
	move -> name = 'P';
      move -> yx_origin_arr[1] = (int) tolower(movement[0]) - 'a';
      return pawn_move(move, board);
      break;

    case 3:
      move -> name = tolower(movement[0]);
      if(move -> f_player)
	move -> name = toupper(movement[0]);

      if(board[ move -> yx_target_arr[0] ][ move -> yx_target_arr[1] ] != '.' && !move -> capture)
	return 0;

      if( tolower( move -> name ) == 'n')
	return knight_move(move, knight_pos, board);
      if( tolower( move -> name ) == 'b')
	return bishop_move(move, board);
      if( tolower( move -> name ) == 'r')
	return rook_move(move, board);
      if( tolower( move -> name ) == 'q')
	return queen_move(move, board);
      break;

    case 4:
      move -> name = tolower(movement[0]);
      if(move -> f_player)
	move -> name = toupper(movement[0]);

      if( tolower( movement[1] ) == 'x')
	move -> capture = true;
      move -> yx_origin_arr[1] = (int) tolower(movement[0]) - 'a';
      if( tolower( move -> name ) == 'n')
	return knight_move(move, knight_pos, board); 
      if( tolower( move -> name ) == 'b')
	return bishop_move(move, board);
      if( tolower( move -> name ) == 'r')
	return rook_move(move, board);
      if( tolower( move -> name ) == 'q')
	return queen_move(move, board);
      else
       return pawn_capture(move, board);
      break;
  }
  return 0;
}
int main(void){

  char board[BOARD_SIZE][BOARD_SIZE];

  char movement[7];
  bool game_end = false;
  bool check = false;
  int counter = 0;

  create_board(board);

  while(!game_end){

    print_board(board);

    struct MoveData move;
    if(counter % 2 != 0){
      move.name = 'k';
      move.f_player = false;
    }else{
      move.name = 'K';
      move.f_player = true;
    }

    // Parsing movements to a function
    printf("Digite seu lançe em notação algebrica : ");
    fgets(movement, 6, stdin);
    movement[strcspn(movement, "\n")] = 0;  // Remove a nova linha
    counter += parse_moves(&move, movement, knight_pos, board, &game_end);
  }
  return 0;
}
