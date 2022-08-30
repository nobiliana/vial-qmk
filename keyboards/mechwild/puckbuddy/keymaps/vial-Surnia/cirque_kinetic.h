/*

*/

#pragma once

#include "report.h"

//friction, needs grav constant. a = gu
const float grav = 9.82;
const float PI = 3.14159;
const float rad2deg = 180/PI;
int8_t frictionMultiplier = 1;

#ifndef friction
#      define friction 0.35
#endif

//Take Final delta values pre-liftoff, apply kinetic. May need to pull LAST deltas, as liftoff detection may occur at same time of x/y wipe. 
float xVal = 0; //will be int in the final op, currently a test value. Will be equal to x delta.
float yVal = 0; //will be int in the final op, currently a test value. Will be equal to y delta. 


int8_t LIFTOFF = 1; //False being contact, True being finger off. 
int8_t kineticInit = 1; //variable to initialize the kinetic values before start. "inverted" to make logic more visually correct


typedef struct {
    int16_t xPoint;
    int16_t yPoint;
    float magValue;
    float angValue;
    int16_t xTemp;
    int16_t yTemp;
    int16_t xDel;
    int16_t yDel;
} mouseThings;

//Function Declarations
float kineticDrag (float vecAngle, float vecMagn);
void kineticVector (int8_t xMouse, int8_t yMouse);
void kineticCirque (report_mouse_t *mouse_report);
