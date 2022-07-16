/*

*/

//friction, needs grav constant. a = gu
const float grav = 9.82;
const float PI = 3.14159;
const float rad2deg = 180/PI;
int8_t frictionMultiplier = 1;

#ifndef friction
#      define friction 0.35;
#endif

//Take Final delta values pre-liftoff, apply kinetic. May need to pull LAST deltas, as liftoff detection may occur at same time of x/y wipe. 
float xVal = 0; //will be int in the final op, currently a test value. Will be equal to x delta.
float yVal = 0; //will be int in the final op, currently a test value. Will be equal to y delta. 


bool LIFTOFF = TRUE; //False being contact, True being finger off. 
bool kineticInit = TRUE; //variable to initialize the kinetic values before start. "inverted" to make logic more visually correct


typedef struct {
    int xPoint;
    int yPoint;
    float magValue;
    float angValue;
} mouseThings;

//Function Declarations
float kineticDrag (float vecAngle, float vecMagn);
void kineticVector (int xMouse, int yMouse);
void kineticCirque (void);
