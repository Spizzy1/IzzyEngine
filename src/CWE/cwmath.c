#include "cwmath.h"

struct Vec3 MVult(struct Mat3 X, struct Vec3 v){

    struct Vec3 result = add(scale(X.xh, v.x) , add(scale(X.yh, v.y), scale(X.zh, v.z)));
    return result;
}

struct Mat3 MMult(struct Mat3 X, struct Mat3 Y){

    struct Mat3 result; 

    result.xh = MVult(X, Y.xh); 
    result.yh = MVult(X, Y.yh); 
    result.zh = MVult(X, Y.zh); 

    return result;

}

