#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

// http://www.satrancokulu.com/nasil-yapilir/satranc-kurallari-2/satrancta-berabere-nasil-olur/ 50 hamle berabere kurali yapmadin yap!!

enum Pieces {
	empty,Wpawn,Wbishop,Wknight,Wqueen,Wrook,Wking,Bpawn,Bbishop,Bknight,Bqueen,Brook,Bking
};

typedef enum Pieces piece; 

enum GameSituation {
	repetitionDraw,patDraw,draw,Player1win,Player2win,continueGame
};

typedef enum GameSituation game;

int abs(number) {
	if(number<0) return -number;
	return number;
}

void printBoard(piece board[8][8],char *pieces[14]) {
	printf("\n                                                 CHESS GAME!!\n\n\n\n\n\n");
	printf("                                   |");
	for (int i = 0; i<8; i++) {
		printf("  %c |",97+i);
	}
	printf("\n");
	printf("                                    _______________________________________");
	printf("\n");
	for (int i = 0; i<8; i++) {
		printf("                                 %d |",i+1);
		for (int j = 0; j<8; j++) {
			printf(" %s |",pieces[board[i][j]]);
		}
		printf("\n");
	}
	
}

char* playerInput(int square) {
	char *cell = malloc(2*sizeof(char));
	if(square == 0) {
		printf("           old square : ");
	} else {
		printf("           new square : ");
	}
	
	gets(cell);
	
	return cell;
}

bool isPawnPos (piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	int number;
	
	if (board[horizontal][vertical] < 7) {
		if(horizontal == 6) {
			number = 3;
		} 
		if (horizontal <6) {
			number = 2;
		}
		if (abs(horizontal-newHorizontal)<number && abs(horizontal-newHorizontal)>0) {
			for (int i = horizontal-1; i>=newHorizontal; i--) {
				if(i == newHorizontal) {
					if(abs(newVertical-vertical) == 1) {
						if(board[i][newVertical] >= 7) {
							return true;
						} else {
							return false;
						}
					} else if (abs(newVertical-vertical) == 0) {
						if(board[i][newVertical] == 0) {
							return true;
						} else {
							return false;
						}
					} else {
						return false;
					}
				}
				if(board[i][vertical] != empty) {
					return false;
				}
			}
		} else {
			return false;
		}
	} else {
		if(horizontal == 1) {
			number = 3;
		} 
		if (horizontal > 1) {
			number = 2;
		}
		
		if (newHorizontal-horizontal<number && newHorizontal-horizontal>0) {
			for (int i = horizontal+1; i<=newHorizontal; i++) {
				if(i == newHorizontal) {
					if(abs(newVertical-vertical) == 1) {
						if(board[i][newVertical] < 7 && board[i][newVertical] > 0) {
							return true;
						} else {
							return false;
						}
					} else if (abs(newVertical-vertical) == 0) {
						if(board[i][newVertical] == 0) {
							return true;
						} else {
							return false;
						}
					} else {
						return false;
					}
				}
				if(board[i][vertical]  != 0) {
					return false;
				}
			}
		} else {
			return false;
		}
	}
}

bool isBishopPos (piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	int control1, control2;
	
	if(board[horizontal][vertical] >= 7) {
		control1 = 1;
		control2 = 6;
	} else if (board[horizontal][vertical] < 7 && board[horizontal][vertical] > 0) {
		control1 = 7;
		control2 = 12;
	}
	if (abs(newHorizontal - horizontal) != abs(newVertical - vertical)) {
		return false;
	}
	while (horizontal != newHorizontal && vertical != newVertical) {
		if (horizontal < newHorizontal) {
			horizontal++;
		} 
		if (horizontal > newHorizontal) {
			horizontal--;
		}
		if(vertical < newVertical) {
			vertical++;
		} 
		if (vertical > newVertical) {
			vertical--;
		}
		if(horizontal != newHorizontal && vertical != newVertical) {
			if (board[horizontal][vertical] != empty) {
				return false;
			}
		} 
		if (horizontal == newHorizontal && vertical == newVertical) {
			if ((board[horizontal][vertical] >= control1 && board[horizontal][vertical] <= control2) || (board[horizontal][vertical] == empty)) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

bool isKnightPos(piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	if(abs(horizontal-newHorizontal) == 2) {
		if(abs(vertical-newVertical) == 1) {
			return true;
		}
	}
	if(abs(horizontal-newHorizontal) == 1) {
		if(abs(vertical-newVertical) == 2) {
			return true;
		}
	}
	return false;
}

bool isRookPos (piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	int i,j,control,control1,control2;
	
	if (horizontal == newHorizontal) {
		i = vertical;
		control = newVertical;
		j = horizontal;
	} else if (vertical == newVertical) {
		i = horizontal;
		control = newHorizontal;
		j = vertical;
	} else {
		return false;
	}
	
	if (board[horizontal][vertical] >=1 && board[horizontal][vertical] <=6) {
		control1 = 7;
		control2 = 12;
	} else {
		if (board[horizontal][vertical] >=7 && board[horizontal][vertical] <=12) {
			control1 = 1;
			control2 = 6;
		}
	}
	
	while (i != control) {
	
		
		if(i < control) {
			i++;
		} else if(i > control) {
			i--;
		}
		if (i != control) {
			if (j == horizontal) {
				if (board[horizontal][i] >= control1 && board[horizontal][i] <= control2) {
					return false;
				}	
			} else if (j == vertical) {
				if (board[i][vertical] >= control1 && board[i][vertical] <= control2) {
					return false;
				}
			}
		} else {
			if (j == horizontal) {
				if ((board[horizontal][i] >= control1 && board[horizontal][i] <= control2) || board[horizontal][i] == empty) {
					return true;
				}	
			} 
			if (j == vertical) {
				if ((board[i][vertical] >= control1 && board[i][vertical] <= control2) || board[i][vertical] == empty) {
					return true;
				}
			}
		}
	}
	return false;
}	

bool isKingPos (piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	int control1,control2;
	if(board[horizontal][vertical] >=1 && board[horizontal][vertical] <= 6) {
		control1 = 1;
		control2 = 6;
	} else {
		if(board[horizontal][vertical] >= 7 && board[horizontal][vertical] <= 12) {
			control1 = 7;
			control2 = 12;
		}	
	}
	if(abs(horizontal - newHorizontal) <=1 && abs(vertical-newVertical) <= 1) {
		if(board[newHorizontal][newVertical]>=control1 && board[newHorizontal][newVertical] <= control2) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

bool isQueenPos (piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	if(horizontal == newHorizontal || vertical == newVertical) {
		if(isRookPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	} else {
		if(isBishopPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	return false;
}

bool controlMove(piece board[8][8],int horizontal,int vertical,int newHorizontal,int newVertical) {
	if (board[horizontal][vertical] == Wpawn || board[horizontal][vertical] == Bpawn) {
		if(isPawnPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	if (board[horizontal][vertical] == Wbishop || board[horizontal][vertical] == Bbishop) {
		if(isBishopPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	if (board[horizontal][vertical] == Wknight || board[horizontal][vertical] == Bknight) {
		if(isKnightPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	if (board[horizontal][vertical] == Wqueen || board[horizontal][vertical] == Bqueen) {
		if(isQueenPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	if (board[horizontal][vertical] == Wrook || board[horizontal][vertical] == Brook) {
		if(isRookPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
	if (board[horizontal][vertical] == Wking || board[horizontal][vertical] == Bking) {
		if(isKingPos(board,horizontal,vertical,newHorizontal,newVertical) == true) return true;
		return false;
	}
}

bool check(piece board[8][8],int king) {
	
	int horizontal,vertical,control1,control2;
	
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] == Wking && king == 0) {
				horizontal = i;
				vertical = j;
				control1 = 7;
				control2 = 12;
			} 
			if (board[i][j] == Bking && king == 1) {
				horizontal = i;
				vertical = j;
				control1 = 1;
				control2 = 6;
			}
		}
	}
	
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] >= control1 && board[i][j] <= control2) {
				if(controlMove(board,i,j,horizontal,vertical) == true) return false;
			}
		}
	}
	
	return true;
}

bool checkMate (piece board[8][8],int king) {
	piece copyBoard[8][8];
	int horizontal,vertical,control1,control2;
	
	for (int i = 0; i<8; i++) {
		for(int j = 0; j<8; j++) {
			copyBoard[i][j] = board[i][j];
		}
	}
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] == Wking && king == 0) {
				horizontal = i;
				vertical = j;
				control1 = 1;
				control2 = 6;
				break;
			} 
			if (board[i][j] == Bking && king == 1) {
				horizontal = i;
				vertical = j;
				control1 = 7;
				control2 = 12;
				break;
			}
		}
	}
	int number = 0;
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if(board[i][j] >= control1 && board[i][j] <= control2) {
				number++;
			}
		}
	}
	number = number-1;
	
	while (number != 0) {
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				if (board[i][j] >= control1 && board[i][j] <= control2) {
					for (int k = 0; k<8; k++) {
						for (int m = 0; m<8; m++) {
							if((k != i) && (m != j)) {
								if (controlMove(copyBoard,i,j,k,m) == true) {
									piece allyPiece = copyBoard[k][m];
									piece enemyPiece = copyBoard[i][j];
									copyBoard[k][m] = copyBoard[i][j];
									copyBoard[i][j] = empty;
									if (check(copyBoard, king) == true) {
										return false;
									} else {
										copyBoard[i][j] = enemyPiece;
										copyBoard[k][m] = allyPiece;
										number--;
										if(number == 0) {
											return true;
										}	
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool isCastlingPos (piece board[8][8],int king,int rookX,int rookY,int rookBoard[8][8]) {
	int horizontal,vertical,control1,control2;
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] == Wking && king == 0) {
				horizontal = i;
				vertical = j;
				control1 = 1;
				control2 = 6;
			} 
			if (board[i][j] == Bking && king == 1) {
				horizontal = i;
				vertical = j;
				control1 = 7;
				control2 = 12;
			}
		}
	}
	
	
	if(rookBoard[rookX][rookY] == 0 && rookBoard[horizontal][vertical] == 0 && (abs(rookX-rookY) == 8 || abs(rookX-rookY) == 0)) {
		if(rookY<vertical) {
			for(int i = rookY+1; i<vertical; i++) {
				if(board[horizontal][i] >= control1 && board[horizontal][i] <= control2) {
					return false;
				}  
			}
			for (int k = 0; k<8; k++) {
				for (int m =0; m<8; m++) {
					if(board[k][m] >=(control1+6)%12 && board[k][m] <= (control2+6)%12) {
						if(controlMove(board,k,m,horizontal,vertical-1) == true || (controlMove(board,k,m,horizontal,vertical-2) == true)) return false;
					}
				}
			}
			
		} else {
			for(int i = rookY-1; i>vertical; i--) {
				if(board[horizontal][i] >= control1 && board[horizontal][i] <= control2) {
					return false;
				}  
			}
			for (int k = 0; k<8; k++) {
				for (int m =0; m<8; m++) {
					if(board[k][m] >=(control1+6)%12 && board[k][m] <= (control2+6)%12) {
						if(controlMove(board,k,m,horizontal,vertical+1) == true || (controlMove(board,k,m,horizontal,vertical+2) == true)) return false;
					}
				}
			}
		}
	} else {
		return false;
	}
	return true;
}

game drawBoard(piece board[8][8], piece gameBoard[200][8][8], int gameNumber,int king, int pawnBoard[200][8][8]) {
	int copy = 0,number,numberPiece;
	int control1,control2;
	
	if (king == 0) {
		control1 = 1;
		control2 = 6;
	} 
	if (king == 1) {
		control1 = 7;
		control2 = 12;
	}
	
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			gameBoard[gameNumber][i][j] = board[i][j];
			if(board[i][j] == Wpawn || board[i][j] == Bpawn) {
				pawnBoard[gameNumber][i][j] = 1;
			} else {
				pawnBoard[gameNumber][i][j] = 0;
			}
		}
	}
	
	int p,r,s;
	for(p = 0; p<=gameNumber; p++) {
		for(r = 0; r<8; r++) {
			for (s = 0; s<8; s++) {
				if (gameBoard[p][r][s] != board[r][s]) {
					break;
				}
			}
			if (gameBoard[p][r][s] != board[r][s]) {
				break;
			}
		}
		if(s == 8 && r == 7) {
			copy++;
		}
		if(copy == 3) {
			return draw;
		}
	}
	
	for (int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			if (board[i][j] == Wking || board[i][j] == Bking || board[i][j] == Wbishop || board[i][j] == Bbishop || board[i][j] == Wknight || board[i][j] == Bknight) {
				numberPiece++;
			} 
			if (board[i][j] != empty) {
				number++;
			}
		}
	}
	if(numberPiece == 3 && number == 3) {
		return draw;
	}
	int n,o;
	for (n = 0; n<8; n++) {
		for (o = 0; o<8; o++) {
			if (board[n][o] >= control1 && board[n][o] <= control2) {
				for (int k = 0; k<8; k++) {
					for (int m = 0; m<8; m++) {
						if(controlMove(board,n,o,k,m) == true && check(board,king) == true && n != k && o != m) {
							return continueGame;
						}
					}
				}
			} 
		}
		if(n == 7 && o == 8) {
			return draw;
		}
	}
	
	
	if (gameNumber-99 > 0 && gameNumber%2 == 0) {
		int first = 0;
	
		for (int i = 0; i<8; i++) {
			for (int j = 0; j<8; j++) {
				if (gameBoard[gameNumber-99][i][j] != empty) {
					first++;
				}
			}
		}
	
		int number = 0;
		
		for (int i = gameNumber-98; i<=gameNumber; i++) {
			for (int j = 0; j<8; j++) {
				for (int k = 0; k<8; k++) {
					if(gameBoard[i][j][k] != empty) {
						number++;	
					}
					if (gameBoard[i-1][j][k] != gameBoard[i][j][k]) {
						return continueGame;
					}
				}
			}
			if(number != first) {
				return continueGame;
			} else {
				number = 0;
			}
			if (i == gameNumber) {
				return draw;
			}
		}
	}
	
	return continueGame;
}

piece pawnChange(piece board[8][8],int horizontal, int vertical) {
	piece number;
	if (horizontal == 0) {
		printf("1-Wbishop\n2-Wknight\n3-Wqueen\n4-Wrook\nSelect your new piece : ");
		scanf("%d",&number);
		number = number+1;
	} else {
		printf("1-Bbishop\n2-Bknight\n3-Bqueen\n4-Brook\nSelect your new piece : ");
		scanf("%d",&number);
		number = number+7;
	}
	return number; 
}

int main () {
	piece board[8][8] = {{Brook,Bknight,Bbishop,Bqueen,Bking,Bbishop,Bknight,Brook},
						 {Bpawn,Bpawn,Bpawn,Bpawn,Bpawn,Bpawn,Bpawn,Bpawn},
						 {empty,empty,empty,empty,empty,empty,empty,empty},
						 {empty,empty,empty,empty,empty,empty,empty,empty},
						 {empty,empty,empty,empty,empty,empty,empty,empty},
						 {empty,empty,empty,empty,empty,empty,empty,empty},
						 {Wpawn,Wpawn,Wpawn,Wpawn,Wpawn,Wpawn,Wpawn,Wpawn},
						 {Wrook,Wknight,Wbishop,Wqueen,Wking,Wbishop,Wknight,Wrook}};
	game situation = continueGame;
	char *pieces[14] = {"  ","WP","WB","WN","WQ","WR","WK","BP","BB","BN","BQ","BR","BK"};
	int square = 0;
	int playerNumber = 0;
	int rookBoard[8][8];
	int pawnBoard[200][8][8];
	piece gameBoard[200][8][8];
	int newX,newY,oldX,oldY;
	int round = 1;
	int gameNumber = 0;
	for(int i = 0; i<8; i++) {
		for (int j = 0; j<8; j++) {
			rookBoard[i][j] = 0;
		}
	}
	
	while (situation == continueGame) {
		system("CLS");
		system("color F0");
		
		printBoard(board,pieces);
		printf("\n\n");
		if(round > 0) {
			situation = drawBoard(board,gameBoard,gameNumber,playerNumber,pawnBoard);
			gameNumber++;
		}
		
		if(situation != continueGame) {
			printBoard(board,pieces);
			if(situation == draw) {
				printf("DRAW!!");
			}
			if(situation == patDraw) {
				printf("PAT!!");
			}
			break;
		}
		
		round = 0;
		char *oldSquare = playerInput(square);
		oldX = oldSquare[1]-49;
		oldY = oldSquare[0]-97;
		
		
		if (board[oldX][oldY] != 0) {
			if((playerNumber == 0 && board[oldX][oldY] < 7) || (playerNumber == 1 && board[oldX][oldY] >= 7)) {
				square++;
				char *newSquare = playerInput(square);
				newX = newSquare[1]-49;
				newY = newSquare[0]-97;
				if((board[oldX][oldY] == Wking && board[newX][newY] == Wrook) || (board[oldX][oldY] == Bking && board[newX][newY] == Brook)) {
					if(isCastlingPos(board,playerNumber,newX,newY,rookBoard) && check(board,playerNumber) == true) {
						if(newY>oldY) {
							board[oldX][oldY+2] = board[oldX][oldY];
							board[newX][newY-2] = board[newX][newY];
							board[oldX][oldY] = empty;
							board[newX][newY] = empty;
						} else {
							board[oldX][oldY-2] = board[oldX][oldY];
							board[newX][newY+3] = board[newX][newY];
							board[oldX][oldY] = empty;
							board[newX][newY] = empty;
						}
						rookBoard[oldX][oldY] = 1;
						rookBoard[newX][newY] = 1;
						round++;
					} else {
						printf("You can't play this move\n");
					}
				} else {
					if (controlMove(board,oldX,oldY,newX,newY) == true && check(board,playerNumber) == true) {
						if(board[oldX][oldY] == Wking || board[oldX][oldY] == Wrook || board[oldX][oldY] == Bking || board[oldX][oldY] == Brook) {
							rookBoard[oldX][oldY] = 1;
						}
						board[newX][newY] = board[oldX][oldY];
						board[oldX][oldY] = empty;
						round++;
					} else {
						printf("You can't play this move\n");
					}
				}
			} else {
				printf("You entered enemy piece's square! \n");
			}
		} else {
			printf("You entered invalid value! \n");
		}
		
		if ((board[newX][newY] == Wpawn && newX == 0) || (board[newX][newY] == Bpawn && newX == 7)) {
			board[newX][newY] = pawnChange(board,newX,newY);
		}
		if(round > 0) {
			playerNumber = (playerNumber+1)%2;
		}
		
		
		if(check(board,playerNumber) == false) {
			if(checkMate(board,playerNumber) == true) {
				printf("CHECKMATE !!!");
					
				if(playerNumber == 1) {
					printf("WHITE WIN \n");
				} else {
					printf("BLACK WIN \n");
				}
				break;
			}
			
			if (playerNumber == 1) {
				printf("CHECK TO BLACK\n");
			} else {
				printf("CHECK TO WHITE\n");
			}
		}
		Sleep(1000);	
		square = 0;
	}			  
}
