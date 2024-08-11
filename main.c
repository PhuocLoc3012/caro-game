#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>


void guide();
void menu();
int isWinner(char chessBoard[][100], int ROWS,int COLUMNS,int x, int y, int COUNT);
void createChessBoard(char chessBoard[][100], int ROWS,int COLUMNS );
void drawChessBoard(char chessBoard[][100], int ROWS,int COLUMNS);
char currentPlayer[100];
char player1[100];
char player2[100];
int winner=0;
int count=0;
int full=0;

int main(int argc, char *argv[]) {
	char chessBoard[100][100];
	int ROWS, COLUMNS;
	int COUNT=0;
	int choice;
	do
	{
	menu();
	scanf("%d", &choice);
	if ( choice == 1 || choice == 2)
	{	
		printf("Enter Player 1's name: ");		
		fflush(stdin);
		gets(player1);
		printf("Enter Player 2's name: ");
		fflush(stdin);			
		gets(player2);
		printf("Enter your chessboard size\nRows: ");
		scanf("%d", &ROWS);
		printf("Columns: ");
		scanf("%d", &COLUMNS);
		printf("Input the win condition: ");
		scanf("%d", &COUNT);
		createChessBoard(chessBoard,ROWS,COLUMNS);		
		drawChessBoard(chessBoard,ROWS,COLUMNS);
		strcpy(currentPlayer, player1);	
		while(winner==0)
		{	
			TextColor(7);
			printf("%s  is playing...",currentPlayer);
			int x,y;
			scanf("%d %d", &x, &y);
			
	//1.NEU NHAP SAI SIZE		
			if ( x < 0 || x >= ROWS || y < 0 || y >= COLUMNS)
			{
				TextColor(12);			
				printf("Input error!\n");
				TextColor(7);			
							
			}	
	//2. NEU O VUONG CON TRONG 
				
			else if (chessBoard[x][y]==' ')
			 {
			 	if(strcmp(currentPlayer, player1)==0)// neu nguoi choi hien tai la player 1
				{									// in X
					TextColor(4);
					chessBoard[x][y] = 'X';
					TextColor(7);				 
					 full++;
				}
					 	
			else if(strcmp(currentPlayer, player2)==0)// neu nguoi choi hien tai la player 2
				{									//in O
					chessBoard[x][y] = 'O';					
					full++;
				}
					
				system ("cls");
				drawChessBoard(chessBoard,ROWS,COLUMNS);				
				winner =isWinner(chessBoard,ROWS,COLUMNS,x, y, COUNT);
				if ( winner == 1)
				{	TextColor(6);
					printf("The winner is %s. Congratulations!\n\n", currentPlayer);	
					TextColor(7);	
					break;		
				}
				if (checkDraw(chessBoard,ROWS,COLUMNS)==1)
				{
					TextColor(6);
					printf("Both of you DRAW!\n\n");
					TextColor(7);				
					break;
				}
					 
				//doi luot choi			 
				if(strcmp(currentPlayer, player1)==0)
					strcpy(currentPlayer, player2);
				else 
					strcpy(currentPlayer, player1);							 
			}
			
	//		3. NEU O VUONG  KHAC KHOANG TRANG (CO DU LIEU ROI)	
			else 	
			{
				TextColor(12);
				printf("The box is full !\n");	
				TextColor(7);		
			}			
		}
	}
	if ( choice ==3)
		guide();
	if ( choice ==4)
	{
		printf("Goodbye\n");
		break;		
	}
	
	} while ( choice >= 1 && choice <= 4);
	return 0;
}
void createChessBoard(char chessBoard[][100], int ROWS,int COLUMNS){
	int i;
	for (i=0; i < ROWS; i++)
	{
		int j;
		for (j =0; j < COLUMNS; j++)
		{
			chessBoard[i][j]=' ';
		}
	}
	
	
}
void drawChessBoard(char chessBoard[][100], int ROWS,int COLUMNS){
    TextColor(6);
    printf("\n    	       %s (X)___vz___%s (O)\n\n", player1, player2);
    TextColor(11);
    int i,j;
    printf("  ");
    for(j=0; j<COLUMNS; j++){
        printf(" %d  ", j);
    }
    printf("\n");
    for(i=0; i<ROWS; i++)
	{
        printf(" %d", i);
        for(j=0; j<COLUMNS; j++)
        {
           printf(" %c ", chessBoard[i][j]);
            if(j < COLUMNS-1) 
				printf("|");
    }
    printf("\n");
        if(i < ROWS - 1)
		{
            printf("  ");
            for(j=0; j<COLUMNS; j++)
			{
                printf("---");
                if(j < COLUMNS - 1) 
					printf("|");
            }
            printf("\n");
        }
    }
    printf("\n");
}


int isWinner(char chessBoard[][100], int ROWS,int COLUMNS,int x,int y, int COUNT){

// tao  ra 2 ben trai phai cua x va y
//KIEM TRA NGANG

//gioi han ben trai	
	int count= 1;
	int j1=y-1; //   j1  <---tru di 1 ----y -----> cong them 1--->   j2   // giu nguyen hang chi tru cot
//gioi han ben phai		
	int j2=y+1;
	while(j1 >= 0 && chessBoard[x][j1] == chessBoard[x][y] )
	{	
		j1--;
		count++;
	}

	while(j2 < COLUMNS && chessBoard[x][j2] == chessBoard[x][y] )
	{
		j2++;// giu nguyen hang chi cong cot
		count++;	
	}
	if ( count >= COUNT)// tru di chinh no
		return 1;

//	KIEM TRA COT
		
//gioi han ben trai		
	int count2= 1;
	int i1=x-1; //   j1  <---tru di 1 ----y -----> cong them 1--->   j2   // giu nguyen hang chi tru cot
//gioi han ben phai		
	int i2=x+1;
	while(i1 >= 0 && chessBoard[i1][y] == chessBoard[x][y] )
	{	
		i1--;
		count2++;	
	}

	while(i2 < ROWS && chessBoard[i2][y] == chessBoard[x][y] )
	{	
		i2++;// giu nguyen hang chi cong cot
		count2++;	
	}
	if ( count2 >= COUNT)//  hoac cong truoc tru di chinh no 
		return 1;	


//KIEM TRA DUONG CHEO CHINH
	int count3= 1;
//gioi han ben trai	
	i1=x -1;
	j1=y-1;
	while (i1 >= 0 && j1 >= 0 && chessBoard[i1][j1]==chessBoard[x][y])
	{
		i1--;
		j1--;
		count3++;
	}
//gioi han ben phai
	i2=x +1;
	j2=y+1;
	while (i2 < ROWS && j2 < COLUMNS && chessBoard[i2][j2]==chessBoard[x][y])
	{
		i2++;
		j2++;
		count3++;
	}
	if ( count3 >= COUNT)
		return 1;	
		
//KIEM TRA CHEO PHU
	int count4= 1;// lan dau da dem so do roi
//gioi han ben trai	
	i1=x +1;
	j1= y -1;
	while ( i1 < ROWS && j1 >=0 && chessBoard[i1][j1]==chessBoard[x][y])
	{
		i1++;
		j1--;
		count4++;	
	}
	
//gioi han ben phai	
	i2= x -1;
	j2= y +1;
	while ( j2 < COLUMNS && i2 >= 0 && chessBoard[i2][j2]==chessBoard[x][y])
	{
		i2--;
		j2++;
		count4++;	
	}
	if ( count4 >= COUNT)	
		return 1;			
	return 0;					
}

void menu(){
	TextColor(12);
	printf("****************CARO-GAME*****************\n");
	TextColor(3);	
	printf("**	1. Play game with Other Player	**\n");
	printf("**	2. Replace	        	**\n");
	printf("**	3. Guild	        	**\n");
	printf("**	4. Exit			        **\n");
	printf("******************************************\n");
	TextColor(2);	
	printf("Press number to choice:	");
	TextColor(7);	
}
void guide(){
	system("cls");
	TextColor(9);
	printf("-----______________CARO GAME______________-----\n");
	TextColor(11);	
	printf("It is a simple game that everyone can play even kids.\n ");
	printf("Rule Game:\n");
	printf("1. The play must press : row column to moving. EX: 2 0\n");
	printf("2. Winning condition:\n");
	printf("a) If the player has 4 moves in a row horizontally, vertically or diagonally, he wins\n");
	printf("b) If a row of 4 moves is blocked at the head, tail or both, 5 moves are needed to win\n");
	printf("	Who has these first that will be a winner.\n");
	printf("c) If the boxes in the chessboard are full but no winner has been found, both players draw .\n");
	printf("''''GOOD LUCK TO YOU!''''\n\n");
}
int checkDraw(char chessBoard[][100], int ROWS,int COLUMNS){
	if ( full == ROWS*COLUMNS )
		return 1;
	return 0;		
}
void TextColor(int x)//X là mã màu
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

