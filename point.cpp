#include "point.h"
#include "player.h"

Point::Point(int radius, double theta) {
    this->radius = radius;
    this->theta = Radian( theta );
    normalize();
}

Point::Point(int radius, Radian theta) {
    this->radius = radius;
    this->theta = theta;
}

Point::Point(){
    this->radius = 0;
    this->theta = Radian( (double) 0 );
}

Point::Point(const Point& other) {
    this->radius = other.radius;
    this->theta = other.theta;
}

Point::normalize(){
    // if rad is negative, subtract pi from theta
    // normalize theta
    // save and return
}

Point::toXY(){ // convert a point to cartisian coordinates
    return (cartesian){ this->radius *cos( this->theta ) , this->radius *sin( this->theta ) }
}

Point::between(Radian LFOV, Radian RFOV, Radian FOV){ // Two normalized radian angles, representing Left Field of View and Right Field of View
        // the difference the right bound of view and this theta is less than the length of our FOV
        // meaning it would be within the field of view
        // AND the duck is greater than the right field of view (meaning its CCW of the right FOV)
    if ( ( abs( RFOV - this->theta ) < FOV ) && ( this->theta > RFOV) ) return true;

        // the difference the left bound of view and this theta is less than the length of our FOV
        // meaning it would be within the field of view
        // AND the duck angle is less than the left field of view (meaning its CW of the left FOV)
    if ( ( abs( LFOV - this->theta ) < FOV ) && ( this->theta < LFOV) ) return true;
    
    // if we haven't returned yet, none of the above are true
    return false;
}

Point::between( Player p ){
    printf("=====Half angle: %f\n", (p.getAngle()/2) );
    printf("=====Left Bound: %f\n", (p.getFov() + (p.getAngle()/2) );
    printf("=====Right Bound: %f\n", (p.getFov() - (p.getAngle()/2) );

    return between( (p.getFov() + (p.getAngle()/2) ), (p.getFov() - (p.getAngle()/2) ), p.getAngle() )
}