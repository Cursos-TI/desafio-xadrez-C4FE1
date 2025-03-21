/*
int check_pawn(int pawn_y_target, int pawn_x_pos,char Board[9][9]){
  if(pawn_y_target == 4 && Board[7][pawn_x_pos] == 'P'){
    return 0;
  }else if (pawn_y_target == 5 && Board[2][pawn_x_pos] == 'p'){
    return 1;
  }
  return -1;
  }*/
/*
    char * check_pos = strstr(movement,"+");
    if((tolower(movement[0]) != 'p' || tolower(movement[0]) != 'n' || tolower(movement[0]) != 'b' || tolower(movement[0]) != 'q' || tolower(movement[0]) != 'k'|| tolower(movement[0]) != 'r') && check_pos == NULL){
	int movement_len = strlen(movement);
	int pawn_y_pos = (int)movement[movement_len -1] - '0';
	int pawn_x_pos = (int)toupper(movement[0]) - '@';
	
	printf("%d e %d", pawn_y_pos, pawn_x_pos);
	
	if(Board[9-pawn_y_pos][pawn_x_pos] == '.'){
	  if(check_pawn(pawn_y_pos, pawn_x_pos, Board) == 0){
	    Board[9-pawn_y_pos][pawn_x_pos] = Board[7][pawn_x_pos];
	    Board[7][pawn_x_pos] = '.';
	  }else if (check_pawn(pawn_y_pos, pawn_x_pos, Board) == 1){
	    Board[9-pawn_y_pos][pawn_x_pos] = Board[2][pawn_x_pos];
	    Board[2][pawn_x_pos] = '.';
	  }else if(f_player&& Board[9-pawn_y_pos+1][pawn_x_pos] == 'P'){
	    Board[9-pawn_y_pos][pawn_x_pos] = Board[9-pawn_y_pos+1][pawn_x_pos];
	    Board[9-pawn_y_pos+1][pawn_x_pos] = '.';
	  }
	}
	
	if(tolower(Board[pawn_y_pos +3][pawn_x_pos]) == 'p'){
	  Board[pawn_y_pos +1][pawn_x_pos]= Board[pawn_y_pos +3][pawn_x_pos];
	  Board[pawn_y_pos +3][pawn_x_pos] = '.';
	}else if(tolower(Board[pawn_y_pos+4][pawn_x_pos]) == 'p'){
	  Board[pawn_y_pos -2][pawn_x_pos]= Board[pawn_y_pos -1][pawn_x_pos];
	  Board[pawn_y_pos -1][pawn_x_pos] = '.';
	}
	
      }
  
    //if(check_pos !=NULL)
    //  printf("Você está em cheque\n");
    */
