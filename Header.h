#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "cprocessing.h"

#include "Player.h"
#include "Platform.h"
#include "Shark.h"


//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") <- 콘솔 창 띄워서 디버깅 가능한 함수

enum BUFFER_SIZE
{
	BUFFERSIZE = 512
};

enum PLATFORM_TYPE
{
	NORMAL = 0,
	//불, 물...ETC
};
