//============================================================================
// Name        : .cpp
// Author      : Dr. Sibt Ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<string>
#include <fstream>


#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
bool win=0;
bool isplaying=false;
bool isplaying2=false;
double fare=0;
int gamestate=0;
int remainingTime = 180;
bool gameOver = 0;
double money=10000;
int score=0;
bool ride=false;
int grid[21][22]={0};
bool state=0;
string name="";
int carcount=3;


class Petrol{
public:
float petrol;
void setPetrol(){
petrol=50;
}
void operator++(int){
if(petrol<=97)
petrol+=3;
else if(petrol<=98)
petrol+=2;
else if(petrol<=99)
petrol+=1;
}
void operator--(int){
petrol-=1;
}
bool operator<(int x){
if(petrol<100)
return true;
else 
return false;
}

};
class Object{
public:
int x;
int y;
int getX(){return x;};
int getY(){return y;};
};
class Car : public Object {
public:
    virtual void draw() {
        DrawCircle(x*40+10-2, y*30+10+16, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+16, 3, colors[BLACK]);
        DrawRoundRect(x*40+10, y*30+10, 20, 18, colors[BLUE], 10);
        DrawCircle(x*40+10-2, y*30+10+2, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+2, 3, colors[BLACK]);
    }
    virtual void setCar(){
    }
 
};
class MyCar: public Car{
    public:
    Petrol P;
    void draw() override {
        DrawCircle(x*40+10-2, y*30+10+16, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+16, 3, colors[BLACK]);
        DrawRoundRect(x*40+10, y*30+10, 20, 18, colors[BLUE], 10);
        DrawCircle(x*40+10-2, y*30+10+2, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+2, 3, colors[BLACK]);
    }
    void setCar() override{
     x=2;
    y=20;
    P.setPetrol();
    system("mpg123 start.mp3 &");
    }
};

class Building: public Object{
public:
void random() {// generate obstacle on random index
x = rand() % 18 + 3;  // x [4, 21]
y = rand()%18+2; // y [1, 20]
grid[y][x]=1;
}
void drawObstacle(){
if(grid[y][x+1]!=1 && grid[y][x-1]!=1&& grid[y+1][x]!=1 && grid[y-1][x]!=1){
  DrawTriangle( x*40+20, y*30+15 , x*40+10, y*30 , x*40+30 , y*30, colors[BROWN] ); 
  DrawCircle(x*40+20,y*30+15,10,colors[GREEN]);
}
else
DrawSquare(x*40, y*30, 39, colors[BLACK]);
}
bool operator==(Car &C){
if (C.x==this->x&&C.y==this->y){
system("mpg123 crash.mp3 &");
return true;
}
else 
return false;
}
};
Building B[140];
MyCar playerCar;
class FuelStation: public Object{
public:

void random() {
    bool match;
    do {
        match = false; 
        x = rand() % 19 + 2;  
        y = rand() % 20 + 1;

        for (int i = 0; i < 140; i++) {
            if (x == B[i].x && y == B[i].y) {
                match = true; 
                break;
            }
        }
        if(x==2&&y==1)
        match=true;
    } while (match); 
}
void draw(){
DrawSquare(x*40, y*30, 39, colors[RED]);
}
bool operator==(const MyCar& C){
      if(C.x==this->x&&C.y==this->y)
      return true;
      else 
      return false;
}
};
FuelStation fuel[3];
class Destination: public Object{
public:
void setd(int a, int b) { 
x=a;
y=b;
}

bool isEqual(MyCar & C){
if (C.x==this->x&&C.y==this->y){
return true;
}
else 
return false;
} 
void draw(){
DrawSquare(x*40, y*30, 39, colors[YELLOW]);
}
};
class people: public Object{
public:
void set(){
 bool match;
    do {
        match = false; 
        x = rand() % 19 + 2;  
        y = rand() % 20 + 1;

        for (int i = 0; i < 140; i++) {
            if (x == B[i].x && y == B[i].y) {
                match = true; 
                break;
            }
        }
        if(x==playerCar.x&&y==playerCar.y)
        match=true;
        for(int i=0;i<3; i++){
        if(fuel[i].x==x&&fuel[i].y==y)
        match=true;
        }
        if(x==2&&y==1)
        match=true;
    } while (match);
    }
bool operator==(const MyCar& C){
      if (C.x==this->x&&C.y==this->y){
system("mpg123 crash.mp3 &");
return true;
}
      else 
      return false;
}
void draw(){
DrawLine(x*40+10,y*30+10,x*40+20,y*30-8+30,2,colors[BROWN]);
	DrawLine(x*40+20,y*30+30-8,x*40+30,y*30+10,2,colors[BROWN]);
	DrawLine(x*40+20,y*30+8,x*40+20,y*30-8+30,2,colors[BROWN]);
	DrawLine(x*40+10,y*30,x*40+20,y*30+8,2,colors[BROWN]);
	DrawLine(x*40+20,y*30+8,x*40+30,y*30,2,colors[BROWN]);
	DrawCircle(x*40+20,y*30-8+30,6,colors[BLACK]);
	DrawCircle(x*40+20,y*30+30-8,4,colors[BROWN]);

	}
};
people ppl[3];
class Job: public Object{
public:
Destination *D;
bool picked;
MyCar *ref;
void random() {// set for Job
picked=false;
ref=nullptr;
    bool match;
    do {
        match = false; 
        x = rand() % 19 + 2;  
        y = rand() % 20 + 1;

        for (int i = 0; i < 140; i++) {
            if (x == B[i].x && y == B[i].y) {
                match = true; 
                break;
            }
        }
    } while (match); 
}
void SetD(){ // Set for destination
bool match;
int a,b;
    do {
        match = false; 
        a = rand() % 19 + 2;  
        b = rand() % 20 + 1;

        for (int i = 0; i < 140; i++) {
            if (a == B[i].x && b == B[i].y) {
                match = true; 
                break;
            }
        }
        if(a==this->x && b==this->y){        
        match=true;
        break;
        }
    } while (match);
    D=new Destination();
    D->setd(a,b);
}

bool operator==(MyCar &C){
if (C.x==this->x&&C.y==this->y){
ref=&C;
system("mpg123 destination.mp3 &");
this->SetD();
return true;
}
else 
return false;
}

void drawPerson(){
if(picked && ref!=nullptr){
x=ref->x;
y=ref->y;
if(state==1){
DrawCircle(x*40+20,y*30-8+30,6,colors[BLACK]);
DrawCircle(x*40+20,y*30+30-8,4,colors[ORANGE]);
}
else
DrawSquare(x*40+15, y*30+12, 10, colors[ORANGE]);
}
else{
        if(state==1){
	DrawLine(x*40+10,y*30+10,x*40+20,y*30-8+30,2,colors[BLACK]);
	DrawLine(x*40+20,y*30+30-8,x*40+30,y*30+10,2,colors[BLACK]);
	DrawLine(x*40+20,y*30+8,x*40+20,y*30-8+30,2,colors[BLACK]);
	DrawLine(x*40+10,y*30,x*40+20,y*30+8,2,colors[BLACK]);
	DrawLine(x*40+20,y*30+8,x*40+30,y*30,2,colors[BLACK]);
	DrawCircle(x*40+20,y*30-8+30,6,colors[BLACK]);
	DrawCircle(x*40+20,y*30+30-8,4,colors[ORANGE]);
	}
	else{
DrawSquare(x*40+7, y*30+7, 25, colors[BROWN]);
DrawSquare(x*40+10, y*30+9, 20, colors[ORANGE]);
    }
  }
}
void delivered(){
delete D;
system("mpg123 destination.mp3 &");
money+=fare;
fare=0;
score+=10;
this->random();
}
};
Job P[3];


class OtherCar: public Car {
public:
    void setCar(int a, int b) {
    x=a;
    y=b;
      //  x = 3;
      //  y = 20;
    }

 bool canMoveTo(int newX, int newY) {
  if (newX < 3 || newX > 21 || newY < 1 || newY > 20)
      return false;
  if (grid[newY][newX] == 1)
       return false;
if (playerCar.x == newX && playerCar.y == newY)
    return false;     
        for(int i=0; i<3;i++)
        if ( newX==P[i].x && newY== P[i].y)
            return false;

        return true;
    }

    void tryMoveLeft() {
        if (canMoveTo(x - 1, y)) 
        x--;
    }

    void tryMoveRight() {
        if (canMoveTo(x + 1, y)) 
        x++;
    }

    void tryMoveUp() {
        if (canMoveTo(x, y + 1)) 
        y++;
    }

    void tryMoveDown() {
        if (canMoveTo(x, y - 1)) 
        y--;
    }

  void draw() override {
        DrawCircle(x*40+10-2, y*30+10+16, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+16, 3, colors[BLACK]);
        DrawRoundRect(x*40+10, y*30+10, 20, 18, colors[RED], 10);
        DrawCircle(x*40+10-2, y*30+10+2, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+2, 3, colors[BLACK]);
    }
    bool operator==(const MyCar &C){
if (C.x==this->x&&C.y==this->y){
system("mpg123 crash.mp3 &");
return true;
}
else 
return false;
} 
};
OtherCar Car[5];
class Garage: public Object{
public: 
void set(){
x=2;
y=1;
}
void draw(){
DrawTriangle( x*40+20, y*30+50 , x*40+40, y*30+20 , x*40 , y*30+20, colors[BROWN] ); 
DrawSquare(x*40+8, y*30, 25, colors[DARK_OLIVE_GREEN]);
}
bool operator==(const MyCar & C){
if (C.x==this->x&&C.y==this->y){
system("mpg123 crash.mp3 &");
return true;
}
else 
return false;
}
};
Garage G;


  // X=col*40;
  // Y=col*30;

//int xI = 90, yI = 610;

void drawCar(double x, double y) {
        DrawCircle(x*40+10-2, y*30+10+16, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+16, 3, colors[BLACK]);
        DrawRoundRect(x*40+10, y*30+10, 20, 18, colors[RED], 10);
        DrawCircle(x*40+10-2, y*30+10+2, 3, colors[BLACK]);
        DrawCircle(x*40+10+20, y*30+10+2, 3, colors[BLACK]);
	glutPostRedisplay();
}

bool flag = false;
void moveCar(int &a, int &b) {
	if (flag) { // moving left
		if (a > 3 && Car[1].canMoveTo(a - 1, b)) {
			a -= 1;
			cout << "going left";
		} else {
			flag = false; 
		}
	} else { // moving right
		if (a < 21 && Car[1].canMoveTo(a + 1, b)) {
			a += 1;
			cout << "going right";
		} else {
			flag = true; 
		}
	}
}



/*
 * Main Canvas drawing function.
 * */
void myDraw(){
if(!gameOver && gamestate==1){
	for(int i=2; i<22; i++)
	for(int j=1; j<21; j++)
	DrawSquare(i*40, j*30, 40, colors[MISTY_ROSE]);
	for(int i=0; i<3; i++)
	fuel[i].draw();
	for(int i=0; i<140; i++)
	B[i].drawObstacle();
	
	
	DrawString( 50, 750, "Score= "+to_string(score), colors[MISTY_ROSE]);
	DrawString( 740, 750, "Balance= "+to_string(money), colors[MISTY_ROSE]);
	DrawString( 740, 720, "Fare per/km= "+to_string(fare), colors[MISTY_ROSE]);
	DrawString( 30, 800, "Driver: "+name, colors[MISTY_ROSE]);
	DrawString( 50, 700, "Petrol= "+to_string(playerCar.P.petrol)+" %", colors[RED]);
	DrawString( 420, 700, "Time= "+to_string(remainingTime), colors[MISTY_ROSE]);
	
	
	if(playerCar.P.petrol>75 && playerCar.P.petrol<=100){
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	}
	else if(playerCar.P.petrol>45&&playerCar.P.petrol<=75){
	DrawCircle(50,670,10,colors[RED]);
	DrawCircle(70,670,10,colors[RED]);
	}
	else if(playerCar.P.petrol>0&&playerCar.P.petrol<=45){
	
	DrawCircle(50,670,10,colors[RED]);
	}
	else
	playerCar.P.petrol=0;
	
	 for(int i=0; i<3;i++){
	if(P[i].picked){
	P[i].D->draw();
	}
	}
	playerCar.draw();
	for(int i=0; i<3; i++){
         P[i].drawPerson();
         }
         

for(int i=0; i<carcount; i++)
        Car[i].draw();
        for(int i=0; i<3; i++){
         ppl[i].draw();
         }
	G.draw();
	
    }
}
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Red Square
	
	//Green Square
	
	
	//Display Score
	if(gamestate==0 || gameOver
	){
	for(int i=2; i<22; i++)
	for(int j=1; j<21; j++)
	DrawSquare(i*40, j*30, 50, colors[DARK_SEA_GREEN]);
          for (int i = 2; i < 22; i++) {
    for (int j = 1; j < 21; j++) {
        int row = i + 2;

        if (row == 6 + 2 && j >= 8 && j <= 13)
            DrawSquare(j * 40, (20 - row) * 40, 45, colors[BLUE]);

        else if (row == 7 + 2 && j >= 7 && j <= 14)
            DrawSquare(j * 40, (20 - row) * 40, 45, colors[BLUE]);
        else if ((row == 8 + 2 || row == 9 + 2) && j >= 5 && j <= 16)
            DrawSquare(j * 40, (20 - row) * 40, 45, colors[BLUE]);
        else if (row == 10 + 2 && (j == 6 || j == 15))
            DrawCircle(j * 40 + 10 - 2, (20 - row) * 40 + 10 + 16, 38, colors[BLACK]);
    }
}

        if(win){
        DrawString( 285, 460, "CONGRATULATIONS YOU WON", colors[RED]);
        }
        DrawString( 285, 430, "WELCOME TO RUSH HOUR", colors[BLACK]);
	 DrawString( 285, 330, "PLAY NEW GAME", colors[BLACK]);
	 DrawString( 285, 290, "->Select Role:", colors[BLACK]);
	 DrawString( 285, 250, "->press 'd' for Delivery Car and 't' for Taxi Cab.", colors[BLACK]);
	 DrawString( 285, 210, "Leaderboard", colors[BLACK]);
	}
	myDraw();
	

	

	
	glutSwapBuffers(); // do not modify this line..

}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

if(!gameOver){

    if (playerCar.x > 2 && key == GLUT_KEY_LEFT) {
        playerCar.x -= 1;

        for(int i=0; i<carcount; i++){
        if(Car[i]==playerCar){
        playerCar.x += 1;
        score-=3;
        for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
            }
         } 
        for (int i = 0; i < 140; i++) {
if (B[i] == playerCar) {
            score-=2;
            for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
                playerCar.x += 1;
  
            }
        }
    } 
    else if (playerCar.x < 21 && key == GLUT_KEY_RIGHT) {
        playerCar.x += 1;
        for(int i=0; i<carcount; i++){
        if(Car[i]==playerCar){
        playerCar.x -= 1;
        score-=3;
        for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
            }
         } 
        for (int i = 0; i < 140; i++) {
            if (B[i] == playerCar) {
                score-=2;
                for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
                playerCar.x -= 1;
            }
        }
    } 
    else if (playerCar.y < 20 && key == GLUT_KEY_UP) {
        playerCar.y += 1;
        
        
        for(int i=0; i<carcount; i++){
        if(Car[i]==playerCar){
        playerCar.y -= 1;
        score-=3;
       for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
            }
         } 
        for (int i = 0; i < 140; i++) {
if (B[i] == playerCar) {
            score-=2;
                playerCar.y -= 1;
                for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
                
            }
        }
    } 
    else if (playerCar.y > 1 && key == GLUT_KEY_DOWN) {
        playerCar.y -= 1;
      
        for(int i=0; i<carcount; i++){
        if(Car[i]==playerCar){
        playerCar.y += 1;
        for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
        score-=3;
            }
         } 
        for (int i = 0; i < 140; i++) {
if (B[i] == playerCar) {
 for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score-=2;
        }
        
                score-=2;
                playerCar.y += 1;
            }
        }
    }
    
    playerCar.P--;
    for(int i=0; i<3; i++){
        if(P[i].picked==true)
        fare+=20;
        }
        for(int i=0; i<3; i++){
        if(ppl[i]==playerCar){
        score=score-5;
         for(int j=0; j<3; j++){
        if(P[j].picked==true)
        score=score-3;
        }}
}}

    glutPostRedisplay();
}


/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'f') //Key for placing the bomb
	{
        for(int i=0; i<3; i++){
        if(fuel[i]==playerCar){
        if(playerCar.P<100){
      playerCar.P++;
        money-=30;
        }
          }
        }	
	}
	if (key == 'p') // for picking Job
	{
       for(int i=0; i<3; i++){
          if(P[i]==playerCar){
        P[i].picked=true;
        }
        }}
        if (key == 'd') // for picking Job
	{
	
       for(int i=0; i<3; i++){
       if(P[i].picked){
          if(P[i].D->isEqual(playerCar)){
        P[i].picked=false;
        P[i].ref=nullptr;
        P[i].delivered();
        }}}
        }
         if (key == 'g') // for role change
	{
	for(int i=0; i<3; i++){
       if(!(P[i].picked)){
	if(G==playerCar){ 
	state=(!state);
	
	P[i].random();
	}
	}}}  
	if (key == 'd' && gamestate==0) {
	state=0;
	}
	if (key == 't' && gamestate==0) {
	state=1;
	}
	if(key=='h'){
	if(!isplaying){
	system("mpg123 horn.mp3 &");
	isplaying=true;
	}else{
	        system("killall mpg123");
	        isplaying=false;
	        }
	 }
	 if(key=='s'){
	 if(!isplaying2){
	system("mpg123 moving.mp3 &");
	isplaying2=true;
	}else{
	        system("killall mpg123");
	        isplaying2=false;
	        }
	 
	 }

	 
	 
	
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
 struct Player {
    string name;
    int score;
};

Player leaderboard[10];
int currentSize = 0;
int stringToInt(string str) {
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
        }
    }
    return num;
}
void parseLine(string line, string &name, int &score) {
    int i = 0;
    while (line[i] != ':' && line[i] != '\0') i++;
    i++; // move to space
    while (line[i] == ' ') i++;

    name = "";
    while (line[i] != 'S' && line[i] != '\0') {
        name += line[i];
        i++;
    }

    while (line[i] != ':' && line[i] != '\0') i++;
    i++; 
    while (line[i] == ' ') i++;

    string scoreStr = "";
    while (line[i] != '\0') {
        scoreStr += line[i];
        i++;
    }

    score = stringToInt(scoreStr);
}
void insertSorted(string name, int score) {
    int pos = 0;

    while (pos < currentSize && leaderboard[pos].score >= score) {
        pos++;
    }

    if (currentSize == 10 && pos == 10) return;

    int limit = (currentSize < 10) ? currentSize : 9;
    for (int i = limit; i > pos; i--) {
        leaderboard[i] = leaderboard[i - 1];
    }

    leaderboard[pos].name = name;
    leaderboard[pos].score = score;

    if (currentSize < 10) currentSize++;
}
void updateLeaderboard() {
    ifstream infile("leaderboard.txt");
    if (infile) {
        string line;
        while (getline(infile, line)) {
            string name;
            int score;
            parseLine(line, name, score);
            insertSorted(name, score);
        }
        infile.close();
    }

    ofstream outfile("leaderboard.txt");
    for (int i = 0; i < currentSize; i++) {
        outfile << "Player Name: " << leaderboard[i].name << "     Score: " << leaderboard[i].score << endl;
    }
    outfile.close();
    ofstream out("leaderboard.bin", ios::binary);
for (int i = 0; i < currentSize; i++) {
    out.write((char*)&leaderboard[i], sizeof(leaderboard[i]));
}
out.close();

    
}

void Timer(int m) {


 if(remainingTime<=100){
        int dir = rand() % 4;
        if (dir == 0) Car[0].tryMoveLeft();
        else if (dir == 1) Car[0].tryMoveRight();
        else if (dir == 2) Car[0].tryMoveUp();
        else Car[0].tryMoveDown();
        int dir2 = rand() % 4;
        if (dir2 == 0) Car[2].tryMoveLeft();
        else if (dir2 == 1) Car[2].tryMoveRight();
        else if (dir2 == 2) Car[2].tryMoveUp();
        else Car[2].tryMoveDown();
        if(carcount==4){
        int dir3 = rand() % 4;
        if (dir3 == 0) Car[3].tryMoveLeft();
        else if (dir3 == 1) Car[3].tryMoveRight();
        else if (dir3 == 2) Car[3].tryMoveUp();
        else Car[3].tryMoveDown();
        }
        if(carcount==5){
        int dir4 = rand() % 4;
        if (dir4 == 0) Car[4].tryMoveLeft();
        else if (dir4 == 1) Car[4].tryMoveRight();
        else if (dir4 == 2) Car[4].tryMoveUp();
        else Car[4].tryMoveDown();
        }
        moveCar(Car[1].x,Car[1].y);
        }
	// implement your functionality here
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}
void appendToLeaderboard() {
    ofstream outfile("leaderboard.txt", ios::app); // text file in append mode

    if (!outfile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    // Write name and score to file in plain text
    outfile << "Player Name: "<<name << "     Score: " << score << endl;

    outfile.close();
}
void TimeCountdown(int value) {
    if (!gameOver) {
        remainingTime--;
        if(remainingTime>100){
        int dir = rand() % 4;
        if (dir == 0) Car[0].tryMoveLeft();
        else if (dir == 1) Car[0].tryMoveRight();
        else if (dir == 2) Car[0].tryMoveUp();
        else Car[0].tryMoveDown();
        int dir2 = rand() % 4;
        if (dir2 == 0) Car[2].tryMoveLeft();
        else if (dir2 == 1) Car[2].tryMoveRight();
        else if (dir2 == 2) Car[2].tryMoveUp();
        else Car[2].tryMoveDown();
        moveCar(Car[1].x,Car[1].y);
        }
       

        if (remainingTime <= 0 ||score<0 ||playerCar.P.petrol<=0||score>=100) {
        if(score>=100)
        win=1;
        appendToLeaderboard();
        updateLeaderboard();
        system("killall mpg123");
        system("mpg123 end.mp3 &");        
            gameOver = true;
            state=0;
        } else {
            glutTimerFunc(1000, TimeCountdown, 0); // Call this function again after 1 second
        }
    }
    glutPostRedisplay();
}


/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
			
            if (y >= 410 && y <= 430) {
            gamestate=1;
            if(gameOver){
            playerCar.P.petrol=50;
            remainingTime=180;
            playerCar.setCar();
            score=0;
            gameOver=0;
            }
            remainingTime=180;
        }

			
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}


// Function to append entry


/*
 * our gateway main function
 * */

 
 
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	cout<<"Enter the player name ";
	getline(cin,name);

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	 glutTimerFunc(1000, TimeCountdown, 0); // Start the countdown timer
	SetCanvasSize(width, height); // set the number of pixels...
	
      playerCar.setCar();
      Car[0].setCar(8,1);
      Car[1].setCar(3,20);
      Car[2].setCar(19,1);
for(int i=0; i<140; i++)
	B[i].random();
	for(int i=0; i<3; i++)
	fuel[i].random();
	for(int i=0; i<3; i++)
	P[i].random();
	G.set();
	for(int i=0; i<3; i++)
	ppl[i].set();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	 
	glutMainLoop();
	return 1;
	
}
#endif /* RushHour_CPP_ */
