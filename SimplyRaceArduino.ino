#include<ISAOLED.h>
#include<DueTimer.h>
#include<ISADefinitions.h>
#include<ISALiquidCrystal.h>
#include<cstdlib>
#include<string>
#include<time.h>
#include<ISA7SegmentDisplay.h>
ISA7SegmentDisplay sseg;
ISAOLED oled;
ISALiquidCrystal lcd;
int x = 30;
int x2 = 90;
int y = 60;
int xobstacle = 40;
int xobstacle2 = 100;
int yobstacle2 = 10;
int posX2 = 95;
int yobstacle = 10;
int yspeed = 1;
int count = 0;
bool finish = false;
bool whowin = false;
int minuta;
const char *tekst = "Player 1 lose";
const char *tekst2 = "Player 2 lose";
int a = 1;
int actualtime = 0;
long seed = 0;
int sizeObstacle = 15;
void setup() {
  // put your setup code here, to run once:
  sseg.init();
  lcd.begin(); 
  oled.begin();
  oled.gotoXY(x,y);
  drawMap();
  oled.writeRect(x,y,1,1,true);
  oled.writeRect(x2,y,1,1,true);
  for (int i = 0; i < 12; i++)
    seed += analogRead(i);
  randomSeed(seed);
  xobstacle2= random(80,115);
  xobstacle = random(6,45);
  sizeObstacle = random(1,15);
  oled.renderAll();
  
  Timer3.attachInterrupt(puttime);
  Timer3.start(1000000);
  Timer4.attachInterrupt(playerTwo);
  Timer4.start(40000);
  Timer5.attachInterrupt(playerOne);
  Timer5.start(40000);
  Timer7.attachInterrupt(drawObstacle2);
  Timer7.start(70000);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  
  digitalWrite(LEDS[0],HIGH);
  
}

void loop() {
  if(a == 1){
  if(finish == false){
  oled.renderAll();
  }else{
    if(whowin == false){
    lcd.print(tekst);
    oled.clear();
    a =3;}else{
      lcd.print(tekst2);
    oled.clear();
    a = 3;
    }
  }
  }
}


void puttime(){
  if(finish == false){
  actualtime++;
  if(actualtime < 10){
  sseg.displayDigit(actualtime, 0);
  }else if(actualtime < 60){
    int sekten = actualtime / 10;
    int sek = actualtime % 10;
    sseg.displayDigit(sekten, 1);
    sseg.displayDigit(sek, 0);
  }else if(actualtime == 60){
    minuta++;
    actualtime == 0;
    sseg.displayDigit(minuta, 2,true);
    sseg.displayDigit(0, 1);
    sseg.displayDigit(0, 0);
  }
  }
}

void playerOne(){
   int joyx = analogRead(JOY1X);
  
  if(finish == false){ 
  if(joyx < 7){
    clearCar(x);
    x+=2;
    drawCar(x);
  } else if(joyx == 1023){
    clearCar(x);
    x-=2;
    drawCar(x);
  }
  }
}

void showSpeed(int a){
  for(int i=0;i<a;i++){
    digitalWrite(LEDS[i],HIGH);
  }
}
void clearCar(int x){
  oled.setPixel(x,y,false);
}

void playerTwo(){
  int joy2x = analogRead(JOY2X);
  if(finish == false){
 if(joy2x < 7){
  clearCar(x2);
    x2-=2;
    drawCar(x2);
  } else if(joy2x >1000){
    clearCar(x2);
    x2+=2;
    drawCar(x2);
  }
  }
}

void drawMap(){
  for(int y=0;y<64;y++){
    oled.setPixel(5,y,true);
    oled.setPixel(55,y,true);
    oled.setPixel(75,y,true);
    oled.setPixel(123,y,true);
  }
}

void drawCar(int x){
  lcd.clear();
  if(x> 55 && x<65){
    finish = true;
    }else if(x>65 && x<75){
      whowin = true;
     finish = true;
    }else if(x<5){
    finish = true;
    }else if(x>123 ){
       whowin = true;
     finish = true;
    }else{
  oled.setPixel(x,y,true);
  }
}

void checkColl(int xcoll,int ycoll,int xlocal){
    for(int i = xcoll;i<xcoll+10;i++){
    for(int j = ycoll;j<ycoll+10;j++){
    if(i == xlocal && j == y ) {
      finish = true;
      if(xlocal == x2){
        whowin = true;
      }
    }
    }
    }
    
}


void clearObstacle(int x,int y){
  for(int i = 0;i<sizeObstacle;i++){
    for(int j=0;j<sizeObstacle;j++){
    oled.setPixel(x+i,y+j,false);
  }}
}





void drawObstacle2(){

  checkColl(xobstacle2,yobstacle2,x2);
  if(finish == false){
  clearObstacle(xobstacle2,yobstacle2);
  yobstacle2 +=yspeed;
  if(yobstacle2<74){
  for(int i = 0;i<sizeObstacle;i++){
    for(int j=0;j<sizeObstacle;j++){
    oled.setPixel(xobstacle2+i,yobstacle2+j,true);
  }}}else{
    if(count < 3){
    count++;    
  sizeObstacle = random(1,15);
  }else{
      count = 0;
      yspeed++;
      showSpeed(yspeed);
  sizeObstacle =random(1,15);
    }
    yobstacle2=1;
    xobstacle2  = random(70,115);
  }
  }

  checkColl(xobstacle,yobstacle,x);
  if(finish == false){
    
  clearObstacle(xobstacle,yobstacle);
  yobstacle+=yspeed;
  if(yobstacle<74){
    
  for(int i = 0;i<sizeObstacle;i++){
    for(int j=0;j<sizeObstacle;j++){
    oled.setPixel(xobstacle+i,yobstacle+j,true);
  }}}else{  
    if(count < 3){
    count++;
  sizeObstacle = random(1,15);
    }else{
      count = 0;
      yspeed++;
      showSpeed(yspeed);
  sizeObstacle = random(1,15);
    }
    yobstacle=1;
    xobstacle = random(6,45);
  }
  }
}
 