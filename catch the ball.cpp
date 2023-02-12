#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define SPACEBAR 32

using namespace std;

// Dispaly Gameover screen and reset score
void GameOver();

// Draw game board and score / control area
void DrawBoard();

// if enemy hit player this function returns 1 
int circleCollideCircle(int x1, int y1, int size1, int x2, int y2, int size2);
 
// Reference Circle Variables
int rSize = 56;
int rx = ((ScWidth-OpWidth)/2), ry = 350;

// Player Variables
int pSize = 50, step = 30;// player size, player speed
double px = ((ScWidth-OpWidth)/2), py = 350; // player X, player Y

// Other Variables
char option, txtScore[5];
int score = 0;

int main(){
	// to make sure generation of random numbers
	srand((unsigned) time(0));
	
	// Initialize Graphics
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
  	 
	while(1){ // for keeping game playing
		
		// Draws game board and score/controls area
		DrawBoard();
		
		// Drawing reference circle
		circle(rx, ry, rSize);
		
		// drawing player
		setcolor(YELLOW);
		setfillstyle(1, YELLOW);
		fillellipse(px, py, pSize, pSize);
		
		// if any key is pressed
		if( kbhit()){
			option = getch(); // catch key in option variable
			 
			if(option == SPACEBAR){ // if key is spacebar shoot bullet
	            // if player overlaps reference circle
	  		    if( circleCollideCircle(px,py,pSize,rx,ry,rSize)==1 ){
	  		    	score++;
	  		    }
	  		    // if player is completely inside reference circle
	  			else if (circleCollideCircle(px,py,pSize,rx,ry,rSize)==2){
					score += 5;	
					
					setcolor(LIGHTGREEN);
					setfillstyle(1, LIGHTGREEN);
					fillellipse(px, py, pSize, pSize);
					delay(100);
	  		    }
	  		    // if player is completely outside reference circle
			  	else{
	  		    	GameOver();
	  		    } 
	  		    delay(100);
			}
		}
		
		// update player position
		py += step;
		// change direction if player goes outside bounds
		if( py > 600 || py < 100 ){
			step = -step;
		}
		
		delay(40);
		cleardevice();
	}
	
	getch();
	closegraph();
}


void GameOver(){
	cleardevice(); // clear screen
	
	setcolor(WHITE);
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to restart...");
	getch();
	score = 0; // reset score
} 

void DrawBoard(){	

	setcolor(WHITE);
	
	// draw board
	rectangle(0,0,ScWidth-OpWidth,ScHeight);
	rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);
	
	// draw title
	settextstyle(4,0,4);
	outtextxy(ScWidth-375, 50, "Catch the Ball");
	
	// print score
	// itoa function converts number to character array
	settextstyle(4,0,9);
	if( score<10 )
		outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
	else if( score>=10 )
		outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));
	
	settextstyle(4,0,1);
	outtextxy(ScWidth-375, 500, "Controls: "); 
	outtextxy(ScWidth-300, 550, "Spacebar to Stop ");
}

int circleCollideCircle(int x1, int y1, int size1, int x2, int y2, int size2){
	// if player is inside reference circle
	if( y1 == y2 ){
		return 2;
	}
	// if player overlaps reference circle from top
	if( y1 - size1 <= y2 + size2 && y1 - size1 >= y2 - size2 ){
		return 1;
	}
	// if player overlaps reference circle from bottom
	else if( y1 + size1 >= y2 - size2 && y1 - size1 <= y2 - size2 ){
		return 1;
	}
	// in any other case
	return 0;
}
