#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char Board[8][9];
  char movement[7];
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 9; j++){
      if(i == 2 && j!=0){
	Board[i][j] = 'p';
      }else if (i == 6 && j!=0){
	Board[i][j] = 'P'; 
      }else if (i==1 && (j == 3 || j == 6)){
	Board[i][j] = 'b';
      }else if (i==7 && (j == 3 || j == 6)){
	Board[i][j] = 'B';
      }else if (i==7 && (j == 2 || j == 7)){
	Board[i][j] = 'N';
      }else if (i==1 && (j == 2 || j == 7)){
	Board[i][j] = 'n';
      }else if (i==1 && (j == 1 || j == 8)){
	Board[i][j] = 'r';
      }else if (i==7 && (j == 1 || j == 8)){
	Board[i][j] = 'R';
      }else if ((i != 7 || i != 1) && (j != 4 || j != 5)){
	Board[i][j] = '.';
      }
      if(i == 0){
	int intbuf = j+49;
	char buf = (char)intbuf;
	Board[i][j] = buf;
      }
      if(j == 0){
	int intbuf = i+49;
	char buf = (char)intbuf;
	Board[i][j] = buf;
      }
      Board[7][4] = 'Q';
      Board[7][5] = 'K';
      Board[1][4] = 'q';
      Board[1][5] = 'k';

    }
  }

  for(int i = 0; i < 8; i++){
    
    for(int j = 0; j < 9; j++){
      printf("%c", Board[i][j]);
    }

    printf("\n");
  }

    return 0;
}
