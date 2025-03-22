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

    struct PieceRules piece;
    bool horse_atack = false;
    bool rook_atack = false;
    print_board(Board);
    printf("Digite seu movimento em Notação Algebrica : ");
    fgets(movement, 6, stdin);
    movement[strcspn(movement, "\n")] = 0;  // Remove a nova linha

    int movement_size = strlen(movement);
    if(movement_size == 2){
      piece.y_target = 9 - ((int) movement[1] - '0');
      piece.x_target = (int) toupper(movement[0]) - '@';
      piece.name = 'p';

      if(f_player){
	piece.name = 'P';
      }
      counter += pawn_move(f_player, &piece, Board);

    }else if (movement_size == 3){
        piece.y_target = 9 - ((int) movement[2] - '0');
	piece.x_target = (int) toupper(movement[1]) - '@';
	piece.capture = false;
	piece.name;

	if(Board[piece.y_target][piece.x_target] == '.'){
	  if (f_player){
	    piece.name = toupper(movement[0]);

	  }else{
	    piece.name = tolower(movement[0]);
	  }
	}
	
	if (tolower(movement[0]) == 'n'){
	  counter += knight_move(f_player,&piece, Board, horse_pos);

	}else if(tolower(movement[0]) == 'r'){
	  counter += rook_move(f_player, &piece,Board);

	}else if(tolower(movement[0]) == 'b'){
	  counter += bishop_move(f_player, &piece, Board);

	}else if (tolower(movement[0]) == 'k'){
	  bool house_attack = check_attacks(f_player, &piece, Board, king_pos, horse_pos);
	  counter += king_move(f_player, &piece, Board, king_pos, house_attack);

	}else if(tolower(movement[0]) == 'q'){
	  counter += queen_move(f_player, &piece, Board);
	}

    }else if (movement_size == 4){

        piece.y_target = 9 - ((int) movement[3] - '0');
	piece.x_target = (int) toupper(movement[2]) - '@';
	piece.x_origin = (int) toupper(movement[0]) - '@';
	piece.name;
	int sum;
	if (Board[piece.y_target][piece.x_target] != '.' && tolower(movement[1]) == 'x'){

	  piece.capture = true;

	  if(!f_player){
	    piece.name = toupper(movement[0]);
	    sum = -1;
	  }else{
	    piece.name = tolower(movement[0]);
	    sum = 1;
	  }

	  if(tolower(movement[0]) == 'n'){
	    counter += knight_move(f_player, &piece, Board, horse_pos);

	  }else if(tolower(movement[0]) == 'r'){
	    counter += rook_move(f_player, &piece, Board);

	  }else if(tolower(movement[0]) == 'k'){
	    bool house_attack = check_attacks(f_player, &piece, Board, king_pos, horse_pos);
	    king_move(f_player, &piece, Board, king_pos, house_attack);

	  }else if(Board[piece.y_target+sum][piece.x_origin] == piece.name){
	    Board[piece.y_target][piece.x_target] = piece.name;
	    Board[piece.y_target][piece.x_origin] = '.';
	    counter++;
	  }else if(tolower(movement[0]) == 'b'){
	    bishop_move(f_player, &piece, Board);
	  }else{
	    char name_tmp = piece.name;
	    piece.name = 'p';
	    if(f_player){
	      piece.name = 'P';
	    }
	    if(Board[piece.y_target+sum][piece.x_origin] == piece.name){
	      Board[piece.y_target][piece.x_target] = piece.name;
	      Board[piece.y_target+sum][piece.x_origin] = '.';
	      counter++;
	    }else{
	      piece.name = name_tmp;
	    }
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
