/*
initial testing with online C compilers. integration with zmk/qmk converters required, and change variables to be time vs. loop based.

add functionality for friction modifiers and keys, high and low friction to allow long glide or fast stop. 
    Change primary functionality of friction to be less x/y based and mainly magnitude, so Radial can be passed in. 
*/

#include <stdio.h>
#include <math.h>
#include "cirque_kinetic.h"
#include "report.h"

#include "print.h"


extern struct pinnacle_data_t cirqueData;

mouseThings mVector = {0};

//friction function
float kineticDrag (float vecAngle, float vecMagn){
    if (vecMagn - ((grav*friction*frictionMultiplier)/(decimalPrecision*100)) <=0){ //if magnitude of the vector is less than zero after calculation, zero it out. 
        mVector.xPoint = 0;
        mVector.yPoint = 0;
    } else {
        mVector.xPoint = cos(vecAngle)*vecMagn; //pull decimal precision down, to final values
        mVector.yPoint = sin(vecAngle)*vecMagn; //pull decimal precision down, to final values 
    }
    return vecMagn - ((grav*friction*frictionMultiplier)/(decimalPrecision*100));
}

//inputs to this should be x and y vectors!
void kineticVector (int32_t xMouse, int32_t yMouse){
    //setting vector magnitude and angle
    mVector.magValue = sqrt((xMouse*xMouse)+(yMouse*yMouse));
    mVector.angValue = atan2(yMouse, xMouse);
}



void kineticCirque(report_mouse_t *mouse_report){   
    if(mVector.xTemp != xVal || mVector.yTemp != yVal){ //if there is a change in position, update delta. otherwise ignore. prevents zeroing deltas. 
    mVector.xDel = xVal - mVector.xTemp;
    mVector.yDel = yVal - mVector.yTemp; //since xVal is absolute position, convert to change in co ords

    mVector.xTemp = xVal;
    mVector.yTemp = yVal; //update temp values to curent position
    }

    if (LIFTOFF){ 
        if (kineticInit){ //initialize the vector values. ensures it is run once ONLY per liftoff event. 
            kineticVector(mVector.xDel, mVector.yDel); //will take deltaX and deltaY, and calculate into the xPoint and yPoints.
            kineticInit = 0;
            uprintf("init. xDel: %i, yDel: %i. friction: %i \n", mVector.xDel, mVector.yDel, frictionMultiplier*friction);
        }

        if (mVector.magValue > 0){
            //printf("loop entered. logic to follow. \n");            
                mVector.magValue = kineticDrag(mVector.angValue, mVector.magValue);

                mouse_report->x = mVector.xPoint;
                mouse_report->y = mVector.yPoint;
                /*
                BREAKOUT POSITION FOR TAKING XPOINT AND YPOINT TO FIRMWARE POINTER CODE. GUARDS IN PLACE FOR NEGATIVE MAGNITUDES.
                */
               uprintf("Kinetic. vect.x: %d, vect.y: %d || mouse x: %i, mouse y: %i\n", mVector.xPoint, mVector.yPoint, mouse_report->x, mouse_report->y);
        }
    } else if (!LIFTOFF){
        if (!kineticInit){
            kineticVector(0, 0); //reinitialize to zero. ensure we have no residual data. 
            kineticInit = 1; //if finger is touching, reset init lock. 
        }
    }
    
//    return Pass;
}