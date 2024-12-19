#pragma once
#include "common.h"

extern Entity player;

void initStage(void);
static void initPlayer();

static void logic(void);
static void doPlayer();
static void doBullets();

static void draw(void);


