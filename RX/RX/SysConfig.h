#pragma once
#include "Config.h"

enum mode
    {
    lock,
    neutral,
    eco,
    normal,
    sport
    };


#define VESC_DEADBAND 0.15

// Modes config:

// ECO
#define PPM_MIN_ECO (PPM_MIN * 0.25 + PPM_MID * 0.75)
#define PPM_MAX_ECO (PPM_MAX * 0.25 + PPM_MID * 0.75)

// NORMAL
#define PPM_MIN_NRM (PPM_MIN * 0.5 + PPM_MID * 0.5)
#define PPM_MAX_NRM (PPM_MAX * 0.5 + PPM_MID * 0.5)

// SPORT
#define PPM_MIN_SPR (PPM_MIN * 1.0 + PPM_MID * 0.0)
#define PPM_MAX_SPR (PPM_MAX * 1.0 + PPM_MID * 0.0)
