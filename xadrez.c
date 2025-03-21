#include "dumb_moves.h"

int main() {
  char Board[9][9];
  create_board(Board);
  char movement[7];
  
 bool game_end=false;
 int counter = 0;
 bool capture = false;
 bool f_player = false;
  while(!game_end){
    if(counter % 2 == 0){
      printf("Jogada do primeiro Jogador\n");
      f_player = true;
    }else {
      printf("Jogada do segundo Jogador \n");
      f_player = false;
    }
    bool horse_atack = false;
    bool rook_atack = false;
    print_board(Board);
    printf("Digite seu movimento em Notação Algebrica : ");
    fgets(movement, 6, stdin);
    movement[strcspn(movement, "\n")] = 0;  // Remove a nova linha
    int movement_size = strlen(movement);
    
    if(movement_size == 2){
      int pawn_y_target = (int) movement[1] - '0';
      pawn_y_target = 9- pawn_y_target;
      int pawn_x_target = (int) toupper(movement[0]) - '@';
      counter += pawn_move(f_player,pawn_y_target,pawn_x_target, Board);
      
    }else if (movement_size == 3){
	int pawn_y_target = (int) movement[2] - '0';
	pawn_y_target = 9- pawn_y_target;
	int pawn_x_target = (int) toupper(movement[1]) - '@';
	bool capture = false;
	char piece;
	if(Board[pawn_y_target][pawn_x_target] == '.'){
	  if (f_player){
	    piece = toupper(movement[0]);
	  }else{
	    piece = tolower(movement[0]);
	  }
	}
	
	if (tolower(movement[0]) == 'n'){
	  counter += knight_move(f_player, pawn_y_target, pawn_x_target, Board, horse_pos);
	}else if(tolower(movement[0]) == 'r'){
	  counter += rook_move(f_player, pawn_y_target, pawn_x_target, Board, capture, piece);
	}else if(tolower(movement[0]) == 'b'){
	  counter += bishop_move(f_player, pawn_y_target, pawn_x_target, Board, piece);
	}else if (tolower(movement[0]) == 'k'){
	  bool house_attack = check_attacks(f_player, pawn_y_target, pawn_x_target, Board, king_pos, horse_pos);
	  counter += king_move(f_player, pawn_y_target, pawn_x_target, Board, king_pos, house_attack);
	}else if(tolower(movement[0]) == 'q'){
	  counter += queen_move(f_player, pawn_y_target,pawn_x_target, capture, Board, piece);
	}
       }else if (movement_size == 4){
	//printf("chegou aqui");
	int pawn_y_target = (int) movement[3] - '0';
	pawn_y_target = 9- pawn_y_target;
	int pawn_x_target = (int) toupper(movement[2]) - '@';
	int pawn_x_attacker = (int) toupper(movement[0]) - '@';
	char piece;
	int sum;
	if (Board[pawn_y_target][pawn_x_target] != '.' && tolower(movement[1]) == 'x'){
	  capture = true;
	  if(!f_player){
	    piece = toupper(movement[0]);
	    sum = -1;
	  }else{
	    piece = tolower(movement[0]);
	    sum = +1;
	  }
	  if(tolower(movement[0]) == 'n'){
	    counter += knight_move(f_player, pawn_y_target, pawn_x_target, Board, horse_pos);
	  }else if(tolower(movement[0]) == 'r'){
	    counter += rook_move(f_player, pawn_y_target, pawn_x_target, Board, capture, piece);
	  }else if(tolower(movement[0]) == 'k'){
	    bool house_attack = check_attacks(f_player, pawn_y_target, pawn_x_target, Board, king_pos, horse_pos);
	    king_move(f_player, pawn_y_target, pawn_x_target, Board, king_pos, house_attack);
	  }else if(Board[pawn_y_target+sum][pawn_x_attacker] == piece){
	    Board[pawn_y_target][pawn_x_target] = piece;
	    Board[pawn_y_target+sum][pawn_x_attacker] = '.';
	    counter++;
	  }
	  
	}
    }else{
      counter +=0;
      printf("Invalid Move %s\n", movement);
    }
    
  printf("%d\n" ,counter);
  }
  return 0;
}
