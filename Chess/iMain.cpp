#pragma comment (lib, "legacy_stdio_definitions.lib")
#include "iGraphics.h"
#include "bitmap_loader.h"

int cur_x=10,cur_y=10;
int p,q;
int g=0;
int sel=0;
int cursor=1;
int flag=-1;
int x_ax,y_ax;
int i,j;
int s=1;
int turn=1;
int deadWhitePiece_x=700;
int deadWhitePiece_y=605;
int deadBlackPiece_x=700;
int deadBlackPiece_y=10;
int board[680][680]={};
int k;
int mposx, mposy;




/*Here all the pictures are initialized. the buttons, homemenu page, game page, score page, credits and all pieces pics*/
char button[6][20] = {"image\\ng.bmp","image\\sc.bmp","image\\contr.bmp","image\\settings.bmp","image\\cr.bmp","image\\exit.bmp"};
char homemenu[20] = "image\\home.bmp";
char play[20] = "image\\board.bmp";
char score[20] = "image\\score.bmp";
char ins[20] = "image\\instruct.bmp";
char sett[20] = "image\\set.bmp";
char credit[20] = "image\\credit.bmp";
char picpic[32][25] = {"image\\Pieces\\rb.bmp","image\\Pieces\\nb.bmp","image\\Pieces\\bb.bmp","image\\Pieces\\qb.bmp","image\\Pieces\\kb.bmp","image\\Pieces\\bb.bmp","image\\Pieces\\nb.bmp","image\\Pieces\\rb.bmp",
	"image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp","image\\Pieces\\pb.bmp",
	"image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp","image\\Pieces\\pw.bmp",
	"image\\Pieces\\rw.bmp","image\\Pieces\\nw.bmp","image\\Pieces\\bw.bmp","image\\Pieces\\kw.bmp","image\\Pieces\\qw.bmp","image\\Pieces\\bw.bmp","image\\Pieces\\nw.bmp","image\\Pieces\\rw.bmp"};

/*this structure is created for defining the x-axis and y-axis for each buttons*/
struct buttonCoordinate
{
	int x;
	int y;
}bCoordinate[6];

/*this structure is created for defining the x-axis and y-axis for each pieces and their individual image*/
typedef struct pieces pieces;
struct pieces
{
	int px;
	int py;
	char piecePic[25];
}piece[32];

/*this function prints the 8*8 chess board in grey and white color.Each block is 85*85 pixel,
So, x-axis is increasing by 85 while y-axis remains same. after printing 8 blocks, x-axis 
returns to 1st position and y-axis increses by 85*/
void printboard(){
	int x=10;int y=10;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if((i+j)%2==0)
				iSetColor(120,120,120);
			else
				iSetColor(255,255,255);

			iFilledRectangle(x,y,85,85);
			x+=85;
		}
		x=10;
		y+=85;
	}
}
/*this function prints the 32 pieces in an initial position. every piece's image is 85*85 pixel.
So, x-axis is increasing by 85 while y-axis remains same. after printing 8 pieces, x-axis 
returns to 1st position and y-axis increses by 85. then after finishing printing the gold pieces,
the y-axis goes to 520 and prints the remaining white pieces.*/
void pieceInitialize()
{   
	y_ax=10;x_ax=10;
	for (int n=0;n<32;n++){
		piece[n].px=x_ax;
		piece[n].py=y_ax;
		x_ax+=85;
		if(n==7){
			x_ax=10;
			y_ax+=85;
		}
		if(n==15){
			x_ax=10;
			y_ax=520;
		}
		if(n==23){
			x_ax=10;
			y_ax+=85;
		}
	}


}

/*this fuction defines the available path for every pieces. board array defines the chess board block position
. every block where there is a gold piece the block is defined as 1 and for white piece it is 2. and the emtpy 
position is 0*/
void availableSlot(){
	for(int n=10;n<680;n+=85){
		for(int m=10;m<680;m+=85){
			for(int o=0;o<32;o++){
				if(piece[o].px==n && piece[o].py==m && o<16){
					board[n][m]=1;
				}

				else if(piece[o].px==n && piece[o].py==m && o>15){
					board[n][m]=2;
				}

			}

		}
	}
}


/*this function determines which piece is selected and saves the selected piece's number in a variable*/
void pieceSelect()
{
	if(sel==1){
		for(int n=0;n<32;n++){
			if(piece[n].px==p && piece[n].py==q){
				flag=n;
			}
		}
	}

}
//rook

/*this funtion moves the rook's position when it is selected and puts it in a valid position
where the player desires. a rook only moves up, down, left, right. So, when it moves up or down
it's x-position is fixed and when it moves left or right it's y-position remains fixed*/ 
void rook(){
	if((sel == 2||sel == 0)){
		if((flag==0||flag==7) && (turn%2)!=0){
			if((i!=p && j==q) && (board[i][j]!=1)){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			} 
			else if((i==p && j!=q) && (board[i][j]!=1)){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
		}

		else if((flag==24||flag==31)  && (turn%2)==0){
			if(i!=p && j==q && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			} 
			else if(i==p && j!=q && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			}
		}


	}
}
/*this function shows the possible path for rook and which piece it can kill*/
void rookPossibleTurn(int a)
{
	int flag1,flag2;
	if(sel==1 && ((turn%2)!=0 && ((piece[a].px==p && piece[a].py==q)))){flag1=2;flag2=1;}
	else if(sel==1 && ((turn%2)==0 && ((piece[a].px==p && piece[a].py==q)))){flag1=1;flag2=2;}
	if(sel==1 && (((piece[a].px==p) && (piece[a].py==q)))){
		for(int n=p+85;n<615;n+=85){
			if(board[n][q]==flag1){iRectangle(n,q,85,85);break;}
			else if(board[n][q]==flag2){break;}
			else if(board[n][q]==0){iSetColor(0,255,0);
			iFilledCircle(n+42.5,q+42.5,5);
			}
		}

		for(int n=q+85;n<615;n+=85){
			if(board[p][n]==0){iSetColor(0,255,0);
			iFilledCircle(p+42.5,n+42.5,5);
			}
			else if(board[p][n]==flag1){iRectangle(p,n,85,85);break;}
			else if(board[p][n]==flag2){break;}
		}
		for(int n=p-85;n>0;n-=85){
			if(board[n][q]==flag1){iRectangle(n,q,85,85);break;}
			else if(board[n][q]==flag2){break;}
			else if(board[n][q]==0){iSetColor(0,255,0);
			iFilledCircle(n+42.5,q+42.5,5);
			}
		}
		for(int n=q-85;n>0;n-=85){
			if(board[p][n]==flag1){iRectangle(p,n,85,85);break;}
			else if(board[p][n]==flag2){break;}
			else if(board[p][n]==0){iSetColor(0,255,0);
			iFilledCircle(p+42.5,n+42.5,5);
			}
		}
	}

}

//knight
/*this function moves the knight. a knight can move to highest 8 diffrent position 
if possible from it's previous position*/
void knight(){
	if((sel == 2||sel == 0)){
		if((flag==1||flag==6)  && (turn%2)!=0){
			if(((i==(p+85) && j==(q+170)) || (i==(p-85) && j==(q+170)) ||
				(i==(p+170) && j==(q+85)) || (i==(p-170) && j==(q+85)) ||
				(i==(p+170) && j==(q-85)) || (i==(p-170) && j==(q-85)) ||
				(i==(p+85) && j==(q-170)) || (i==(p-85) && j==(q-170))) && board[i][j]!=1){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=1;
					turn++;
			}
		}

		else if((flag==25||flag==30)  && (turn%2)==0){
			if(((i==(p+85) && j==(q+170)) || (i==(p-85) && j==(q+170)) ||
				(i==(p+170) && j==(q+85)) || (i==(p-170) && j==(q+85)) ||
				(i==(p+170) && j==(q-85)) || (i==(p-170) && j==(q-85)) ||
				(i==(p+85) && j==(q-170)) || (i==(p-85) && j==(q-170))) && board[i][j]!=2){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=2;
					turn++;
			}
		}


	}


}

//bishop
/* a bishop can move only diagonaly (where x and position are same) from it's previous position. So, if we subtract
it's desired x position and it's previous x position and desired y position and it's previous y position, then 
if the values are same the piece can move*/
void bishop(){
	if((sel == 2||sel == 0)){
		if((flag==2||flag==5) && (turn%2)!=0){
			if((((i-p)==(j-q)) || ((p-i)==(j-q))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
		}
		else if((flag==26||flag==29)  && (turn%2)==0){
			if((((i-p)==(j-q)) || ((p-i)==(j-q))) && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			}
		}

	}
}
/*this function shows the possible path for bishop and which piece it can kill*/
void bishopPossibleTurn(int a){
	bool k=false;
	int flag1=-1,flag2=-1;
	bool move[8][8]={};
	if(sel==1 && turn%2!=0 && ((piece[a].px==p) && (piece[a].py==q))){flag1=2;flag2=1;}
	else if(sel==1 && turn%2==0 && ((piece[a].px==p) && (piece[a].py==q))){flag1=1;flag2=2;}
	if(sel==1 && (piece[a].px==p && piece[a].py==q)){
		for(int n=p+85;n<615;n+=85){
			for(int m=q+85;m<615;m+=85){
				if(((n-p)==(m-q)) && 0<n-p && n-p<605 && 0<m-q && m-q<605){
					if(board[n][m]==flag1){iRectangle(n,m,85,85);k=true;break;}
					else if(board[n][m]==flag2){k=true;break;}
					else if(board[n][m]==0){iSetColor(0,255,0);
					iFilledCircle(n+42.5,m+42.5,5);
					}
				}
			}
			if(k){k=false;break;}
		}
		for(int n=p-85;n>0;n-=85){
			for(int m=q-85;m>0;m-=85){
				if(((p-n)==(q-m)) && 0<p-n && p-n<605 && 0<q-m && q-m<605){
					if(board[n][m]==flag1){iRectangle(n,m,85,85);k=true;break;}
					else if(board[n][m]==flag2){k=true;break;}
					else if(board[n][m]==0){iSetColor(0,255,0);
					iFilledCircle(n+42.5,m+42.5,5);
					}
				}
			}
			if(k){k=false;break;}
		}
		for(int n=p-85;n>0;n-=85){
			for(int m=q+85;m<615;m+=85){
				if(((p-n)==(m-q)) && 0<p-n && p-n<605 && 0<m-q && m-q<605){
					if(board[n][m]==flag1){iRectangle(n,m,85,85);k=true;break;}
					else if(board[n][m]==flag2){k=true;break;}
					else if(board[n][m]==0){iSetColor(0,255,0);
					iFilledCircle(n+42.5,m+42.5,5);
					}
				}
			}
			if(k){k=false;break;}
		}
		for(int n=p+85;n<615;n+=85){
			for(int m=q-85;m>0;m-=85){
				if(((n-p)==(q-m)) && 0<n-p && n-p<605 && 0<q-m && q-m<605){
					if(board[n][m]==flag1){iRectangle(n,m,85,85);k=true;break;}
					else if(board[n][m]==flag2){k=true;break;}
					else if(board[n][m]==0){iSetColor(0,255,0);
					iFilledCircle(n+42.5,m+42.5,5);
					}
				}
			}
			if(k){k=false;break;}
		}
	}

}

//queen
/*the queen's movement is the combination of bishop and rook. so, if we combine their logic
we get queen's movement*/
void queen(){
	if((sel == 2||sel == 0)){
		if(flag==3 && (turn%2)!=0){
			if((i!=p && j==q) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
			else if((i==p && j!=q) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
			else if((((i-p)==(j-q)) || ((p-i)==(j-q))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
		}
		else if(flag==28  && (turn%2)==0){
			if((i!=p && j==q) && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			}
			else if((i==p && j!=q) && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			}
			else if((((i-p)==(j-q)) || ((p-i)==(j-q))) && board[i][j]!=2){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=2;
				turn++;
			}
		}
	}
}
/*this function shows the possible path for queen and which piece it can kill*/
void queenPossibleTurn(int a){
	rookPossibleTurn(a);
	bishopPossibleTurn(a);

}

//king
/*a king can move only one postion away from it's previous position. so, when it moves up or down
the x-pos is same and when it moves left or right the y-pos is same.but, when it moves diagonally
both position changes*/
void king(){
	if((sel == 2||sel == 0)){
		if((flag==4 && (turn%2)!=0) || (flag==27 && (turn%2)==0)){
			if(((((i-p)==85) && (j==q)) || (((i-p)==-85) && (j==q))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
			else if((((i==p) && ((j-q)==85)) || ((i==p) && ((j-q)==-85))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
			else if((((i-p)==85 && ((j-q)==85)) || ((i-p)==-85 && ((j-q)==-85))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
			else if((((i-p)==-85 && ((j-q)==85)) || ((i-p)==85 && ((j-q)==-85))) && board[i][j]!=1){
				piece[flag].px=i;
				piece[flag].py=j;
				board[p][q]=0;
				board[i][j]=1;
				turn++;
			}
		}
	}
}
/*this function shows the possible path for king and which piece it can kill*/
void kingPossibleTurn(int a){
	int flag1;
	if(sel==1 && ((turn%2)!=0 && ((piece[a].px==p && piece[a].py==q)))){flag1=2;}
	else if(sel==1 && ((turn%2)==0 && ((piece[a].px==p && piece[a].py==q)))){flag1=1;}

	if(sel==1 && (((piece[a].px==p) && (piece[a].py==q)))){
		if(board[p+85][q]==flag1){iRectangle(p+85,q,85,85);}
		else if(board[p+85][q]==0){iSetColor(0,255,0);
		iFilledCircle(p+85+42.5,q+42.5,5);
		}
		if(board[p+85][q+85]==flag1){iRectangle(p+85,q+85,85,85);}
		else if(board[p+85][q+85]==0){iSetColor(0,255,0);
		iFilledCircle(p+85+42.5,q+85+42.5,5);
		}
		if(board[p-85][q]==flag1){iRectangle(p-85,q,85,85);}
		else if(board[p-85][q]==0){iSetColor(0,255,0);
		iFilledCircle(p-85+42.5,q+42.5,5);
		}
		if(board[p-85][q-85]==flag1){iRectangle(p-85,q-85,85,85);}
		else if(board[p-85][q-85]==0){iSetColor(0,255,0);
		iFilledCircle(p-85+42.5,q-85+42.5,5);
		}
		if(board[p][q+85]==flag1){iRectangle(p,q+85,85,85);}
		else if(board[p][q+85]==0){iSetColor(0,255,0);
		iFilledCircle(p+42.5,q+85+42.5,5);
		}
		if(board[p][q-85]==flag1){iRectangle(p,q-85,85,85);}
		else if(board[p][q-85]==0){iSetColor(0,255,0);
		iFilledCircle(p+42.5,q-85+42.5,5);
		}
		if(board[p+85][q-85]==flag1){iRectangle(p+85,q-85,85,85);}
		else if(board[p+85][q-85]==0){iSetColor(0,255,0);
		iFilledCircle(p+85+42.5,q-85+42.5,5);
		}
		if(board[p-85][q+85]==flag1){iRectangle(p-85,q+85,85,85);}
		else if(board[p-85][q+85]==0){iSetColor(0,255,0);
		iFilledCircle(p-85+42.5,q+85+42.5,5);
		}
	}
}
//pawn
/*when the pawn is moved for the first time it can go two postion up. From then,
it can only go one position up. it can kill a piece when the piece is in one diagonal 
positon up from the pawn*/
void pawn(){
	if((sel == 2||sel == 0)){
		for(int n = 8;n<16;n++){
			if(n==flag && (turn%2)!=0){
				if((i==p && j==265) && board[i][j]!=1){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=1;
					turn++;
				}
				else if((i==p && j==(q+85)) && board[i][j]!=1){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=1;
					turn++;
				}
			}
		}
		for(int n = 16;n<24;n++){
			if(n==flag && (turn%2)==0){
				if((i==p && j==350) && board[i][j]!=2){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=2;
					turn++;
				}
				else if((i==p && j==(q-85)) && board[i][j]!=2){
					piece[flag].px=i;
					piece[flag].py=j;
					board[p][q]=0;
					board[i][j]=2;
					turn++;
				}
			}
		}
	}
}

/*when a piece gets to the position of the opponents piece, the opponent piece is killed
and moved from the board to outside of the board. so that the players can see which pieces 
they have lost*/
void killPiece(){
	if(turn%2==0){
		for(int n=0;n<16;n++){
			for(int m=16;m<32;m++){
				if((piece[n].px==piece[m].px) && (piece[n].py==piece[m].py)){
					piece[m].px=deadWhitePiece_x+10;
					piece[m].py=deadWhitePiece_y+10;
					deadWhitePiece_x+=85;
				}
			}
		}
	}
	else if(turn%2!=0){
		for(int m=16;m<32;m++){
			for(int n=0;n<16;n++){
				if((piece[n].px==piece[m].px) && (piece[n].py==piece[m].py)){
					piece[n].px=deadBlackPiece_x+10;
					piece[n].py=deadBlackPiece_y+10;
					deadBlackPiece_x+=85;
				}
			}
		}
	}
}


/*this function shows the possible path for knight and which piece it can kill*/
void knightPossibleTurn()
{
	int flag1=-1;
	if(sel==1 && ((turn%2)!=0 && ((piece[1].px==p && piece[1].py==q)||(piece[6].px==p && piece[6].py==q)))){flag1=2;}
	else if(sel==1 && ((turn%2)==0 && ((piece[25].px==p && piece[25].py==q)||(piece[30].px==p && piece[30].py==q)))){flag1=1;}
	if(sel==1 && (((piece[1].px==p && piece[1].py==q)||(piece[6].px==p && piece[6].py==q))||((piece[25].px==p && piece[25].py==q)||(piece[30].px==p && piece[30].py==q)))){

		int n=85,m=170;
		if(0<p+n && p+n<615 && 0<q+m && q+m<615){

			if(board[p+n][q+m]==flag1){
				iRectangle(p+n,q+m,85,85);
			}
			else if(board[p+n][q+m]==0){
				iFilledCircle(p+n+42.5,q+m+42.5,5);
			}
		}
		if(0<p-n && p-n<615 && 0<q+m && q+m<615){
			if(board[p-n][q+m]==flag1){
				iRectangle(p-n,q+m,85,85);
			}
			else if(board[p-n][q+m]==0){
				iFilledCircle((p-n)+42.5,q+m+42.5,5);
			}
		}
		if(0<p+m && p+m<615 && 0<q+n && q+n<615){
			if(board[p+m][q+n]==flag1){
				iRectangle(p+m,q+n,85,85);
			}
			else if(board[p+m][q+n]==0){
				iFilledCircle(p+m+42.5,q+n+42.5,5);
			}
		}
		if(0<(p-m) && (p-m)<615 && 0<q+n && q+n<615){
			if(board[p-m][q+n]==flag1){
				iRectangle((p-m),q+n,85,85);
			}
			else if(board[p-m][q+n]==0){
				iFilledCircle((p-m)+42.5,q+n+42.5,5);
			}
		}
		if(0<p+m && p+m<615 && 0<q-n && q-n<615){

			if(board[p+m][q-n]==flag1){
				iRectangle(p+m,q-n,85,85);
			}
			else if(board[p+m][q-n]==0){
				iFilledCircle(p+m+42.5,(q-n)+42.5,5);
			}
		}
		if(0<p-m && p-m<615 && 0<q-n && q-n<615){
			if(board[p-m][q-n]==flag1){
				iRectangle(p-m,q-n,85,85);
			}
			else if(board[p-m][q-n]==0){
				iFilledCircle(p-m+42.5,(q-n)+42.5,5);
			}
		}
		if(0<p+n && p+n<615 && 0<q-m && q-m<615){
			if(board[p+n][q-m]==flag1){
				iRectangle(p+n,q-m,85,85);
			}
			else if(board[p+n][q-m]==0){
				iFilledCircle(p+n+42.5,(q-m)+42.5,5);
			}
		}
		if(0<p-n && p-n<615 && 0<q-m && q-m<615){
			if(board[p-n][q-m]==flag1){
				iRectangle(p-n,q-m,85,85);
			}
			else if(board[p-n][q-m]==0){
				iFilledCircle((p-n)+42.5,(q-m)+42.5,5);
			}
		}

	}
}





/*
function iDraw() is called again and again by the system.

*/


int gamestate = -1;
void iDraw()
{
	//place your drawing codes here
	iClear();
	if (gamestate == -1)
	{
		//homemenu
		iShowBMP(0,0,homemenu);
		for(int i=0; i<6; i++)
		{
			iShowBMP2(bCoordinate[i].x,bCoordinate[i].y,button[i],0);
		}
	}

	else if(gamestate == 0)
	{
		iShowBMP(0,0,"image\\gameplay.bmp");
		printboard();
		/*here all pieces is printed in it's initial position*/
		for(int n =0;n<32;n++){
			iShowBMP2(piece[n].px,piece[n].py,piece[n].piecePic,0);

		}
		pieceSelect();
		availableSlot();
		iSetColor(0,200,0);
		rookPossibleTurn(0);
		rookPossibleTurn(7);
		rookPossibleTurn(24);
		rookPossibleTurn(31);
		knightPossibleTurn();
		bishopPossibleTurn(2);
		bishopPossibleTurn(5);
		bishopPossibleTurn(26);
		bishopPossibleTurn(29);
		queenPossibleTurn(3);
		queenPossibleTurn(28);
		kingPossibleTurn(4);
		kingPossibleTurn(27);
		rook();
		knight();
		bishop();
		queen();
		king();
		pawn();

		killPiece();
		/*it shows which player turn it is */
		if(turn%2!=0){
			iSetColor(0,0,0);
			iText(750,350,"Player 2(Gold)",GLUT_BITMAP_HELVETICA_18);
		}
		else {iSetColor(0,0,0);
		iText(750,350,"Player 1(White)",GLUT_BITMAP_HELVETICA_18);}
		//possibleTurn();
		//if(leave == true){
		//printf("%d ",turn);
		//}
		//else printf("false ");




		if(cursor==1){
			iSetColor(0,0,255);
			iRectangle(cur_x,cur_y,85,85);
			iRectangle(cur_x+1,cur_y+1,85,85);
			iRectangle(cur_x+2,cur_y+2,85,85);
		}
		if(sel==1){
			iSetColor(0,200,200);

			iRectangle(p,q,85,85);
			iRectangle(p+1,q+1,85,85);
			iRectangle(p+2,q+2,85,85);

		}






	}
	//highscore
	else if(gamestate == 1)
	{
		iShowBMP(0,0,score);
	}
	//instruction
	else if(gamestate == 2)
	{
		iShowBMP(0,0,ins);
	}
	//settings
	else if(gamestate == 3)
	{
		iShowBMP(0,0,sett);
	}
	//credits
	else if(gamestate == 4)
	{
		iShowBMP(0,0,credit);
	}
	//exit;
	else if(gamestate == 5)
	{
		exit(0);
	}


}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	if (my > 35 && my <= 700 && mx > 35 && mx <700 )
	{

	}

}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		for(int i=0;i<6;i++)
		{

			if (mx>=bCoordinate[i].x && mx<=bCoordinate[i].x + 100 && my>=bCoordinate[i].y && my <= bCoordinate[i].y + 30 && gamestate == -1){
				gamestate = i;
			}

		}


	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{


	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 27)
	{
		if(gamestate!=-1){
			gamestate=-1;
		}
	}
	else if (key == ' ')
	{
		if(sel==0||sel==2){
			if(turn%2!=0 && board[cur_x][cur_y]==1){
				sel=1;	
				p=cur_x;q=cur_y;
			}
			else if(turn%2==0 && board[cur_x][cur_y]==2){
				sel=1;	
				p=cur_x;q=cur_y;
			}
		}

		else if(sel==1){
			sel=2;
			i=cur_x;j=cur_y;

		}
	}



}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	else if (key == GLUT_KEY_UP)
	{
		if (cur_y < 605 && gamestate==0){
			cur_y=cur_y+85;
		}


	}
	else if (key == GLUT_KEY_DOWN)
	{
		if (cur_y > 10 && gamestate==0){
			cur_y=cur_y-85;
		}

	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (cur_x < 605 && gamestate==0){
			cur_x=cur_x+85;
		}

	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (cur_x > 10 && gamestate==0){
			cur_x=cur_x-85;
		}

	}

}

int main()
{
	for(int n=0;n<32;n++){
		strcpy(piece[n].piecePic,picpic[n]);

	}
	pieceInitialize();
	availableSlot();
	rookPossibleTurn(0);
	rookPossibleTurn(7);
	rookPossibleTurn(24);
	rookPossibleTurn(31);
	knightPossibleTurn();
	bishopPossibleTurn(2);
	bishopPossibleTurn(5);
	bishopPossibleTurn(26);
	bishopPossibleTurn(29);
	queenPossibleTurn(3);
	queenPossibleTurn(27);
	kingPossibleTurn(4);
	kingPossibleTurn(27);
	rook();
	knight();
	bishop();
	queen();
	king();
	pawn();
	killPiece();
	//possibleTurn();
	for(int n=10;n<680;n+=85){
		for(int m=10;m<680;m+=85){
			printf(" %d ",board[n][m]);

		}
	}
	int sum = 20;
	for(int i=0;i<6;i++)
	{
		bCoordinate[i].x = sum;
		bCoordinate[i].y = 50;
		sum+=200;
	}

	iInitialize(1200, 700, "my demo");
	iStart(); // it will start drawing
	return 0;
}
