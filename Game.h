#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "cprocessing.h"

#include "Player.h"
#include "Platform.h"
#include "Shark.h"
#include "Camera.h"
#include "item.h"
#include "Header.h"

void game_init(void);
void game_update(void);
void game_exit(void);