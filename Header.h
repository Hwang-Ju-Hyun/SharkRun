#pragma once

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "cprocessing.h"
#include "main.h"
#include "Player.h"
#include "Platform.h"
#include "Shark.h"
#include "Game.h"
#include "Collision.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define PI 3.141592

enum BUFFER_SIZE
{
	BUFFERSIZE = 512
};


enum GROUND_OR_AIR
{
	GROUND = 0,
	AIR = 1
};

enum PLATFORM_TYPE
{
	NORMAL = 0,
	//ºÒ, ¹°...ETC
};