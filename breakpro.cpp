#include "raylib.h"
#include <string>
#include <cstring>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// compile: g++ breakpro.cpp -o breakpro -lraylib -lm -ldl -lpthread -lGL -lX11
// run:     ./breakpro
// Ctrl-C to close crashed program
// raylib uses float for most numbers, and so use 2.0f to convert int to float. Note that 2.0 will be a double
// Only use GameMaker for final animations and sound. Make full game (o/w animations) with raylib

using namespace std;
int screenWidth = 1200; 
int screenHeight = 800;
int blocks[800][800];
int blockssize = 4;
int ballx = 600;
int bally = 800-50;
int balldx = 0;
int balldy = -1;
int paddlex = 600;
int paddley = 800-20;


void clearblocks()
{
  for (int i=0;i < 800; i++ )
         for (int j=0; j < 800; j++)
           blocks[j][i] = 0;
}

Color HexToColour(int hexValue) {
    Color c;
    c.r = (hexValue >> 16) & 0xFF;  // red
    c.g = (hexValue >> 8) & 0xFF;   // green
    c.b = hexValue & 0xFF;          // blue
    c.a = 255;                      // default opaque
    return c;
}


#pragma region fixed LED Colours
 // DO NOT CHANGE
 // needed for LEDColour pixel editor
Color rbblack = HexToColour(0x000000);
Color rberaser = HexToColour(0x000001); 
Color rbwhite = HexToColour(0xFFFFFF);
Color rblightblue = HexToColour(0xB5B3F5);
Color rbblue = HexToColour(0x0000FF);
Color rbdarkblue = HexToColour(0x00008B);
Color rblightred = HexToColour(0xFF6666);
Color rbred = HexToColour(0xFF0000);
Color rbdarkred = HexToColour(0x8B0000);
Color rborange = HexToColour(0xFF5900);
Color rblightorange = HexToColour(0xFFD580);
Color rbdarkorange = HexToColour(0xFF8C00);  
Color rblightgreen = HexToColour(0x66C266);
Color rbgreen = HexToColour(0x279627);  
Color rbdarkgreen = HexToColour(0x006400);
Color rblightpink = HexToColour(0xFFD1F0);
Color rbpink = HexToColour(0xF498EC);  
Color rbdarkpink = HexToColour(0xC71585);
Color rblightyellow = HexToColour(0xFFFFE0);
Color rbyellow = HexToColour(0xFFFF00);
Color rbdarkyellow = HexToColour(0xB8860B);  
Color rblightgrey = HexToColour(0xDDDDDD);
Color rbgrey = HexToColour(0xAAAAAA);
Color rbdarkgrey = HexToColour(0x777777);
Color rblightbrown = HexToColour(0xC19153);
Color rbbrown = HexToColour(0x8B4513);
Color rbdarkbrown = HexToColour(0x4C3A23);
Color rblightaqua = HexToColour(0xE0FFFF);
Color rbaqua = HexToColour(0x00FFFF);
Color rbdarkaqua = HexToColour(0x008B8B);
Color rblightpurple = HexToColour(0xE6E6FA);
Color rbpurple = HexToColour(0xBE1CBE);
Color rbdarkpurple = HexToColour(0x4B0082);

Color rbgray00 = HexToColour(0x666666);
Color rbgray0 = HexToColour(0x999999);
Color rbgray1 = HexToColour(0xAAAAAA);
Color rbgray2 = HexToColour(0xCCCCCC);
Color rbgraytext = HexToColour(0x1E1E1E);
Color rbgray24 = HexToColour(0xC8C8C8);
Color rbgray3 = HexToColour(0xEEEEEE);


 // DO NOT CHANGE
 // needed for LEDColour pixel editor
Color AllColours[60] = {rblightblue, rbblue, rbdarkblue, rblightred, rbred, rbdarkred, rblightorange, rborange, rbdarkorange,
                       rblightgreen, rbgreen, rbdarkgreen, rblightpink, rbpink, rbdarkpink, rblightyellow, rbyellow, rbdarkyellow,
                       rblightgrey, rbgrey, rbdarkgrey, rblightbrown, rbbrown, rbdarkbrown, rblightaqua, rbaqua, rbdarkaqua,
                       rblightpurple, rbpurple, rbdarkpurple, rbblack, rberaser, rbwhite};                    
 // for LEDColour pixel editor
Color getColour(int myindex)
{
  if ( (myindex >= 1) and (myindex <= 33))
    return AllColours[myindex-1];
  else
    return rbblack; 
}

//Color ColourRainbow[10] = { rbwhite, rblightgreen, rbdarkyellow,
//                              rbdarkpink, rbblue, rbred, rbgreen, rbbrown, rbaqua, rbpurple};

Color ColourRainbow[10] = {  rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, rblightgreen, 
                             rblightgreen, rblightgreen, rblightgreen};

Color ColourCASIOArray[10] = { rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext,rbgraytext};


Color EnemyColourArray[10];

Color resultcolour = rblightgreen;
#pragma endregion


#pragma region LED graphics arrays
int CharBob[64] = {1,18,23,23,23,23,18,18,1,18,18,23,23,23,18,18,14,16,16,16,16,16,16,16,17,16,0,0,16,0,0,16,0,16,0,0,16,0,0,16,0,16,16,16,16,16,16,16,0,18,1,1,1,1,17,17,23,23,23,18,18,18,23,23};
int CharEnemy1[64] = {5,0,0,17,0,0,0,5,0,5,0,0,17,0,5,0,5,0,11,17,0,11,0,5,0,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,5,24,33,24,33,5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,0};
int CharBall[64] = {0,0,0,21,21,0,0,0,0,0,19,19,19,19,0,0,0,19,16,16,16,16,19,0,21,19,16,33,33,16,19,21,21,19,16,33,33,16,19,21,0,19,16,16,16,16,19,0,0,0,19,19,19,19,0,0,0,0,0,21,21,0,0,0};
int CharBallSmall[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,19,21,0,0,0,0,0,19,33,19,0,0,0,0,0,21,19,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharCrate[256] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,17,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17};
int CharCrateWide[1024] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,17,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,17,0,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int CharBlock[576] = {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,33,19,19,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};

int CharA[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharB[64] = {0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharC[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharD[64] = {0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharE[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharF[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharG[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharH[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharI[64] = {0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharJ[64] = {0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int CharK[64] = {0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharL[64] = {0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharM[64] = {1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharN[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharO[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharP[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharQ[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1};
int CharR[64] = {0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharS[64] = {0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharT[64] = {0,1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharU[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int CharV[64] = {1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharW[64] = {1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharX[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0};
int CharY[64] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharZ[64] = {0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};

int Char0[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char1[64] = {0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int Char2[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int Char3[64] = {0,16,16,16,16,16,0,0,16,16,0,0,0,16,16,0,0,0,0,0,0,16,16,0,0,0,0,16,16,16,0,0,0,0,0,0,0,16,16,0,16,16,0,0,0,16,16,0,0,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0};
int Char4[64] = {0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0};
int Char5[64] = {1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char6[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char7[64] = {1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
int Char8[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int Char9[64] = {0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharPlus1[64] = {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
int CharPlus2[64] = {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharUnderline[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0};
int CharEquals[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharUpArrow[64] = {0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};
int CharColon[64] = {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharRightArrow[64] = {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};

int CharLEDRightArrow[64] = {0,0,16,17,0,0,0,0,0,0,0,16,17,0,0,0,0,0,0,0,16,17,0,0,0,0,0,0,0,16,16,0,0,0,0,0,16,17,0,0,0,0,0,16,17,0,0,0,0,0,16,17,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDDownArrow[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,16,0,17,16,0,0,0,16,17,0,0,17,16,0,16,17,0,0,0,0,17,16,17,0,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDUpArrow[64] = {0,0,0,16,0,0,0,0,0,0,17,16,17,0,0,0,0,17,16,0,16,17,0,0,17,16,0,0,0,16,17,0,16,0,0,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenRightArrow[64] = {0,0,10,11,0,0,0,0,0,0,0,10,11,0,0,0,0,0,0,0,10,11,0,0,0,0,0,0,0,10,10,0,0,0,0,0,10,11,0,0,0,0,0,10,11,0,0,0,0,0,10,11,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenDownArrow[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,10,0,11,10,0,0,0,10,11,0,0,11,10,0,10,11,0,0,0,0,11,10,11,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0};
int CharLEDGreenUpArrow[64] = {0,0,0,10,0,0,0,0,0,0,11,10,11,0,0,0,0,11,10,0,10,11,0,0,11,10,0,0,0,10,11,0,10,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int CharLEDSelector[1024] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,10,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,17,0,0,0,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,0,0,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,17,17,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,17,11,11,17,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,11,10,10,11,17,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,10,16,16,10,11,17,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,16,16,16,16,10,11,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,17,17,17,17,10,11,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,10,17,17,10,11,17,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,11,10,10,11,17,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,17,11,11,17,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,17,17,0,0,0,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,17,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int* digitarray[10] = {Char0, Char1, Char2, Char3,  // array of pointers to chars, this works well! Access with digitarray[charnum][bitnum] 
                       Char4, Char5, Char6, Char7, Char8, Char9};  

int* alphaarray[26] = {CharA, CharB, CharC, CharD, CharE, CharF, CharG, CharH, CharI, CharJ, CharK, CharL, CharM, CharN, CharO, CharP, CharQ, 
                       CharR, CharS, CharT, CharU, CharV, CharW, CharX, CharY, CharZ}; 
#pragma endregion


#pragma region Draw Functions
void drawLine3Colour(float fromx, float fromy, float tox, float toy, int psize, int xstep, int ystep, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  Vector2 vstart = { fromx, fromy};
  Vector2 vend = { tox, toy};
  DrawLineEx(vstart, vend, psize, Mycolour1);
  vstart.x = vstart.x + xstep;
  vstart.y = vstart.y + ystep;
  vend.x = vend.x + xstep;
  vend.y = vend.y + ystep;
  DrawLineEx(vstart, vend, psize, Mycolour2);
  vstart.x = vstart.x + xstep;
  vstart.y = vstart.y + ystep;
  vend.x = vend.x + xstep;
  vend.y = vend.y + ystep;
  DrawLineEx(vstart, vend, psize, Mycolour3);
}

void drawRect3Colour(float fromx, float fromy, float tox, float toy, int psize, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  
  //drawLine3Colour(fromx, fromy, fromx, toy,psize,psize,0, Mycolour1, Mycolour2, Mycolour3);
  //drawLine3Colour(fromx, toy-psize*2, tox, toy-psize*2,psize,0,psize, Mycolour1, Mycolour2, Mycolour3);
  //drawLine3Colour(tox, fromy, tox, toy,psize,psize,0, Mycolour1, Mycolour2, Mycolour3);
  //;drawLine3Colour(fromx+psize*2, fromy, tox, fromy,psize,0,psize, Mycolour1, Mycolour2, Mycolour3);

  Rectangle rect1={fromx,fromy,tox-fromx,toy-fromy};
  DrawRectangleLinesEx(rect1,psize*3,Mycolour3);
  DrawRectangleLinesEx(rect1,psize*2,Mycolour2);
  DrawRectangleLinesEx(rect1,psize*1,Mycolour1);
}

void drawCharfromArray(int previewx, int previewy, int psize, int width, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       for (int i=0;i < width; i++ )
         for (int j=0; j < width; j++)
            {
              if (myarray[loc] != 0)
              {
               Mycolour = getColour(myarray[loc]);
               DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void drawCharOneColour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour)
     {
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void drawChar3Colour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour1, Color Mycolour2, Color Mycolour3)
     {
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               if (i<2) 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour1);  
               else if (i>3) 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour3);
               else 
                  DrawRectangle(previewx+j*psize,previewy+i*psize,psize,psize,Mycolour2);     
              }
              loc++;
            }        
     }

void drawRetroCharOneColour(int previewx, int previewy, int psize, int bitwidth, int myarray[], Color Mycolour)
     {
       int loc = 0;
       int gap = 1;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               DrawRectangle(previewx+j*(psize+gap),previewy+i*(psize+gap),psize,psize,Mycolour);  
              }
              loc++;
            }        
     }

void drawcharinblocks(int previewx, int previewy, int bitwidth, int myarray[], Color Mycolour)
     {
       int loc = 0;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               blocks[previewx+j][previewy+i] = 1;    
              }
              loc++;
            }        
     }     

void drawRetroChar(int previewx, int previewy, int psize, int bitwidth, int myarray[])
     {
       Color Mycolour;
       int loc = 0;
       int gap = 1;
       for (int i=0;i < bitwidth; i++ )
         for (int j=0; j < bitwidth; j++)
            {
              if (myarray[loc] != 0)
              {
               Mycolour = getColour(myarray[loc]);
               DrawRectangle(previewx+j*(psize+gap),previewy+i*(psize+gap),psize,psize,Mycolour);    
              }
              loc++;
            }        
     }

void draw2digits(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawRetroCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawRetroCharOneColour(locx+ 8*(psize+1), locy, psize, 8, digitarray[second], Mycolour);
}

void draw2digits3colour(int locx, int locy, int mynum, int psize, Color Mycolour1, Color Mycolour2, Color Mycolour3)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawChar3Colour(locx, locy, psize, 8, digitarray[first], Mycolour1, Mycolour2, Mycolour3 );
   }
  drawChar3Colour(locx+ 8*(psize), locy, psize, 8, digitarray[second], Mycolour1, Mycolour2, Mycolour3);
}

void draw2digitsSolid(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawCharOneColour(locx+ 8*(psize+1), locy, psize, 8, digitarray[second], Mycolour);
}

void draw2digitsSolid2(int locx, int locy, int mynum, int psize, Color Mycolour)
{
  int first = mynum / 10;
  int second = mynum % 10;
  if (first > 0) 
   { 
    drawCharOneColour(locx, locy, psize, 8, digitarray[first], Mycolour);
   }
  drawCharOneColour(locx+ 6*psize, locy, psize, 8, digitarray[second], Mycolour);
}

void ShowColourScore2(int locx, int locy, int myscore, int psize, Color Mycolour,  int numzeros=9)
{
string stringscore="";
string num = to_string(myscore);
for (int i = num.length(); i < numzeros; i++) // Add leading zeros until the string reaches numzeros length
{
    stringscore += '0';
}
stringscore += num;
 
for (int i = 0; i < stringscore.size(); i++) 
{
    char c = stringscore[i];
    int index = c - '0';
    auto value = digitarray[0];
    if (c >= '0' && c <= '9')  
       {
        value = digitarray[c - '0'];
       }
    drawRetroCharOneColour(locx+ i*8*(psize+1), locy, psize, 8, value, Mycolour);
}
}

string ToUpperCase(string mystring)
{
  char c;
  string resultstring = mystring;
  for (int i = 0; i < mystring.size(); i++)
  {
    c = mystring[i];
    if (c >= 'a' and c <= 'z')
       c = c - 32; // convert to UpperCase character;
    resultstring[i] = c;
  }
  return resultstring;
}

void ShowColourText(int locx, int locy, string mytext, int psize, Color Mycolour)
{
   char c;
   string UPtext;
   UPtext = ToUpperCase(mytext);
   for (int i = 0; i < UPtext.size(); i++) 
   {
     c = UPtext[i];
     auto value = alphaarray[0];
     if (c >= 'A' && c <= 'Z')  
       {
        value = alphaarray[c - 'A'];
       }
     if (c == ':') value = CharColon;
     if (c == '=') value = CharEquals;
     if (c == '+') value = CharPlus2;
     if (c >= '0' && c <= '9')  
       {
        value = digitarray[c - '0'];
       }
     if (c != ' ')
        {
         // drawRetroCharOneColour(locx+ i*8*(psize+1), locy, psize, 8, value, Mycolour);
          drawcharinblocks(locx/4+i*8, locy/4, 8, value, Mycolour);
        }
   }
}

void drawblocks()
{
  for (int i = 0; i < 800; i++) 
     for (int j = 0; j < 800; j++)
     {
      if (blocks[j][i] == 1)
      {
        DrawRectangle(j*(blockssize+1),i*(blockssize+1),blockssize,blockssize,rbwhite);   
      }
     } 
}

void drawpaddle()
 {
  DrawRectangle(paddlex-100,paddley,200,20,rbaqua); 
 }

 void drawball()
 {
  DrawRectangle(ballx-2,bally-2,4,4,rbaqua); 
 }


#pragma endregion



Color rbbackgroundcolour = BLACK;
Vector2 MousePos;

void moveball()
{
  ballx = ballx + balldx;
  bally = bally + balldy;
}

void testcollision()
{
  if (blocks[ballx/4][bally/4] == 1 or blocks[ballx/4+1][bally/4] == 1 or bally <= 0 or bally >= screenHeight)
  {
    balldy = -balldy;
    bally = bally + balldy;
    blocks[ballx/4][bally/4] = 0;
    blocks[ballx/4][bally/4+1] = 0;
    blocks[ballx/4][bally/4-1] = 0;
    blocks[ballx/4+1][bally/4] = 0;
    blocks[ballx/4+1][bally/4+1] = 0;
    blocks[ballx/4+1][bally/4-1] = 0;
    for (int i =0; i< 800;i++)
        blocks[i][bally/4] = 0;
    
  }
}

int main() {
    // To list all fonts installed:
    // find /usr/share/fonts -type f -name "*.ttf"
    // find ~/.local/share/fonts -type f -name "*.ttf"
    clearblocks();
    InitWindow(screenWidth, screenHeight, "Break Program"); // RNG seed is set randomly in InitWindow !!
    // create fonts AFTER InitWindow !!!!
    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        BeginDrawing();         // these two lines MUST go first when drawing
        ClearBackground(rbbackgroundcolour); // these two lines MUST go first when drawing
        MousePos = GetMousePosition();
        paddlex = MousePos.x;
        ShowColourText(90, 20,  "10 rem test program", 3, YELLOW);
        ShowColourText(90, 60,  "20 let i=1", 3, YELLOW);
        ShowColourText(90, 100, "30 let j=1", 3, YELLOW);
        ShowColourText(90, 140, "40 j=j+1", 3, YELLOW); // need to create blocks at start of main (not in main loop)
        drawblocks();
        drawpaddle();
        drawball();
        moveball();
        testcollision();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
