#ifndef __GLOBALS__ 
#define __GLOBALS__

#include <new>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <string>

typedef unsigned int uint;

int random_sign();

#define SCREEN_WIDTH 192 // pixels
#define SCREEN_HEIGHT 242 // pixels

const uint ball_init_x     = SCREEN_WIDTH/2;  //pixels
const uint ball_init_y     = SCREEN_HEIGHT/2; //pixels
const uint ball_init_vel_x = 3;               //pixels/update
const uint ball_init_vel_y = 1;               //pixels/update
const uint ball_sprite_x   = 73;              //pixels
const uint ball_sprite_y   = 104;             //pixels
const uint ball_sprite_w   = 4;               //pixels
const uint ball_sprite_h   = 4;               //pixels
const uint paddle_sprite_x  = 29;    //pixels
const uint paddle_sprite_y  = 94;    //pixels
const uint paddle_sprite_w  = 4;     //pixels
const uint paddle_sprite_h  = 14;    //pixels
const int paddle_velocity_x = 0;   //pixels/update
const int paddle_velocity_y = 4;   //pixels/update
const uint player_init_x = 4;
const uint player_init_y = (SCREEN_HEIGHT-paddle_sprite_h)/2;
const uint opponent_init_x = SCREEN_WIDTH - 4;
const uint opponent_init_y = player_init_y;

const char spritesheet_fullfilename[] = "Resources/sprites.bmp";
const char paddle_sound_fullfilename[] = "Resources/paddle.wav";
const char edge_sound_fullfilename[] = "Resources/edge.wav";
const char point_sound_fullfilename[] = "Resources/point.wav";

#endif