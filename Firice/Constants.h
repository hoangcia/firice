#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int LIMIT_FPS = 60;
const unsigned int LIMIT_ANIMATED_FPS = 4;
const unsigned long SECONDS_PER_FRAME = 1000 / LIMIT_FPS;
const unsigned int DEFAULT_SCREEN_WIDTH = 1024;
const unsigned int DEFAULT_SCREEN_HEIGHT = 768;
const unsigned int ANIMATED_FRAME_WIDTH = 98;
const unsigned int ANIMATED_FRAME_HEIGHT = 90;
const float CHAR_MAX_VELOCITY = 150.0f;
const float CHAR_MOVING_ACCELERATION = 5.0f;
const float CHAR_JUMPING_VELOCITY = 300.0F;

const float GAME_GRAVITY = 50.0f;
#endif