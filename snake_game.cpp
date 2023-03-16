//#include "snake_work.h"
# include "iGraphics.h"
#define screenWidth 392
#define screenLength 700

char playmenu[100]="picture\\menu1.bmp";
char homemenu[100]="picture\\menu.bmp";
char background[100]="picture\\bg.bmp";
char go[100]="picture\\goButton.bmp";
char tips[100]="picture\\tips.bmp";
char home[100]="picture\\home.bmp";
char back[100]="picture\\back.bmp";
char back1[100]="picture\\back1.bmp";
char credit[100]="picture\\credit.bmp";
char gameOver[100]="picture\\gameOver.bmp";

int gameState = 0;

int size = 20;
int dirrection = 1;
int x,y;
int pause = 0;


char menu[100] = "picture\\menu.bmp";
//int gameState = 0; 

void drawS(int x,int y){
	iFilledRectangle(x*size,y*size,size,size);  ///snake body rectangle
	iSetColor(0,0,0);
	iRectangle(size*x+1,size*y+1,size-1,size-1);  /// snake separate rectangle
}
int s[1000][2]; 
int snake_length=3;      /// length of the snake
int foodX,foodY;      ///Cordinate of the food
bool hit=false;         ///flag to determine if the snake collide with its body 
int score = 0, hscore;
int count =0;
void iSnakeDraw()
{
    //printf("drawing ");
	//place your drawing codes here
	iClear();
	
	iShowBMP(0,0,"picture\\bg.bmp");
	char scr[100], highScr[100];
	sprintf(scr, "YOUR SCORE: %d", score);
	sprintf(highScr, "High Score: %d", hscore);
    iSetColor(255,255,0);
    iText(0,370,scr,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(0,350,highScr,GLUT_BITMAP_TIMES_ROMAN_24);
    //iSetColor(255,255,255);

	if(hit){
		iShowBMP(0,0,gameOver);
		iSetColor(255,252,63);
		iText(15,63,scr,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(20,35,highScr,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,252,54);
		iText(490,30,"click to exit...",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,252,54);
		iText(230,360,"-->Thanks For Playing_^_^",GLUT_BITMAP_TIMES_ROMAN_24);
		iPauseTimer(0); ///play stop when hit occurs7
		PlaySound(NULL,0,0); ///sound off when hit occurs

	}
	else{
		
		iSetColor(255,255,255);
		drawS(foodX,foodY); ///calling the draws() function
		iSetColor(255,255,255);
		for(int i=0;i<snake_length;i++){
			int red = rand()%255;
			int green = rand()%255;
			int blue = rand()%255;
			iSetColor(red,green,blue);
		    drawS(s[i][0],s[i][1]);
			
		}
		
	}
	
}
void snake_keys(unsigned char key)
{
	///Movement of the snake
	///1 r,2 l,3 U,4 D
	if(key == GLUT_KEY_LEFT)
	{
		if(dirrection!=1)dirrection=2;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		if(dirrection!=2)dirrection=1;
	}
	if(key == GLUT_KEY_UP)
	{
		if(dirrection!=4)dirrection=3;
	}
	if(key == GLUT_KEY_DOWN)
	{
		if(dirrection!=3)dirrection=4;
	}
	//place your codes for other keys here
}
void extend(){
	for(int i=snake_length;i>0;i--){
		s[i][0]=s[i-1][0];
		s[i][1]=s[i-1][1];
	}
}
void change(){
	for(int i=1;i<snake_length;i++){
	if(s[i][0]==s[0][0]&&s[i][1]==s[0][1]){
		hit = true;
        PlaySound("music\\gameover.wav",NULL,SND_ALIAS);
		if (score > hscore){
			hscore = score;
			FILE * fptr = fopen("score_board.txt", "w");
			if (fptr)
				fprintf(fptr, "%d\n", hscore);
			fclose(fptr);
		}
	}
	}
	if(s[0][0]==foodX && s[0][1]==foodY){
		foodX = rand()%(screenLength/size);
		foodY = rand()%(screenWidth/size);
		snake_length++;
		score++;
	}	
	extend();
	if(dirrection==1)s[0][0]++;
	if(dirrection==2)s[0][0]--;
	if(dirrection==4)s[0][1]--;
	if(dirrection==3)s[0][1]++;
	if(s[0][0]*size>=screenLength)s[0][0]=0;
	if(s[0][1]*size>=screenWidth)s[0][1]=0;
	if(s[0][0]<0)s[0][0]=screenLength/size;
	if(s[0][1]<0)s[0][1]=size-1;
}
/*gameState=0-->first snake menu ; gamestate=1-->menu1 ; 
gameState=2-->iSnakeDraw() function call ; gameState=3-->tips*/
void iDraw() {
	//place your drawing codes here
	iClear();
   
    if(gameState ==0){
        iShowBMP(0,0,homemenu); ///Home manu drawing 
		iShowBMP2(534,10,go,0); /// GO button code  to entry
        iSetColor(0,0,0);
        iText(210,30,"Click GO button to Continue...",GLUT_BITMAP_TIMES_ROMAN_24);
    } 
    else if(gameState==1){
        iShowBMP(0,0,playmenu);
		iShowBMP(600,0,back); //menu1 picture
       }
	else if (gameState==2){
		//printf("I snake Draw");
        iSnakeDraw(); ///calling the snakeDraw function to draw the snake
    }
    else if(gameState==3){
        iShowBMP(0,0,tips); 
		iShowBMP(600,0,back1);  ///showing the tips picture
		}
	else if(gameState==4){
		//printf("hi");
		iShowBMP(0,0,credit);
		iShowBMP(600,0,back1);
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		    if(gameState==0 &&(mx>=544 && mx<=594) && (my>=30 && my<=71)){
             gameState=1;
			}
            if(gameState==1 && mx>=356 && mx<=656 && my>=300 && my<=372){
				//printf("gamestate = 2\n");
				PlaySound("music\\sherlock_home.wav",NULL,SND_LOOP||SND_ALIAS );
				gameState=2;
			}    
            
			if(gameState==1 && mx>=398 && mx<=605 && my>=105 && my<=171){
			  gameState=3;
		    }

			if(gameState==1 && mx>=600 && mx<=700 && my>=0 && my<=45){
				gameState=0;
			}
			
			if(gameState==3 && mx>=600 && mx<=700 && my>=0 &&my<=45){
				gameState=1;
			}
			
			if(gameState==1 && mx>=40 && mx<=200 && my>=25 && my<=70){
				//printf("gamestate =4\n");
				gameState=4;
			}
			if(gameState==4 && mx>=600 && mx<=700 && my>=0 &&my<=45){
				gameState=1;
			}
			if (gameState==2 && hit && mx>=0 && mx<=700 && my>=0 && my<=392){
				exit(1);
			}
			 
}
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key){
	if ( gameState==2 && key == 'e') {
		exit(0);
	}
	if (gameState == 2 && key == ' '){
		pause = !pause;
		if (pause)
			iPauseTimer(0);
		else
			iResumeTimer(0);
	}
	//place your codes for other keys here
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
void iSpecialKeyboard(unsigned char key) {
    if (gameState==2){
        snake_keys(key);
    }

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


int main() {
	FILE * fptr = fopen("score_board.txt", "r");
	if (fptr == NULL){
		hscore = 0;
	}
	else fscanf(fptr, "%d", &hscore);
	fclose(fptr);
	//place your own initialization codes here.
    //place your own initialization codes here.
	s[0][0] = rand()%(screenLength/size);
	s[0][1] = rand()%(screenWidth/size);
	foodX = rand()%(screenLength/size);
	foodY = rand()%(screenWidth/size);
	iSetTimer(200,change);
	iInitialize(700,392, "Snake and Play");
	return 0;
}
  