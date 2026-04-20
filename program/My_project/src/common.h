#pragma once

#define DEBUG_MODE

#include <stdio.h>
#include <DxLib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

//unsigned intŒ^‚ğUIntŒ^‚Æ‚µ‚Ä’è‹`
typedef unsigned int UInt;

//unsigned charŒ^‚ğUnCharŒ^‚Æ‚µ‚Ä’è‹`
typedef unsigned char UChar;

//unsigned shortŒ^‚ğUnShortŒ^‚Æ‚µ‚Ä’è‹`
typedef unsigned short UShort;

//unsigned longŒ^‚ğUnLongŒ^‚Æ‚µ‚Ä’è‹`
typedef unsigned long ULong;

//unsigned long longŒ^‚ğUnLgLgŒ^‚Æ‚µ‚Ä’è‹`
typedef unsigned long long ULgLg;

//‰æ–Ê‚Ì‰¡•‚Æc•
static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 800;

//‰æ–Ê‚Ì’†S
static constexpr int WINDOW_CENTER_WIDTH = WINDOW_WIDTH / 2;
static constexpr int WINDOW_CENTER_HEIGHT = WINDOW_HEIGHT / 2;

static constexpr int PLAYER_MOVE_LIMIT_LEFT = WINDOW_CENTER_WIDTH - 224;

static constexpr int PLAYER_MOVE_LIMIT_RIGHT = WINDOW_CENTER_WIDTH + 224;

static constexpr int BLOCK_COL = 5;
static constexpr int BLOCK_ROW = 5;

static constexpr int BLOCK_MAX = BLOCK_COL * BLOCK_ROW;


static constexpr int ENEMY_MAX = 1;


//‰æ–Ê‚Ì‰¡•‚Æc•‚ÌÅ‘å’l
static constexpr int WINDOW_WIDTH_MAX = 1920;
static constexpr int WINDOW_HEIGHT_MAX = 1080;

static const char* GRAP_FILE_PATH = "data/csv/graphic.csv";


