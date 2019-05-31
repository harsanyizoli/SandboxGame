#include "physics.hpp"

bool Physics::AABBtoAABB(const AABB& t1, const AABB& t2){
        return(t1.p_vecMax.x > t2.p_vecMin.x &&
            t1.p_vecMin.x < t2.p_vecMax.x &&
            t1.p_vecMax.y > t2.p_vecMin.y &&
            t1.p_vecMin.y < t2.p_vecMax.y &&
            t1.p_vecMax.z > t2.p_vecMin.z &&
            t1.p_vecMin.z < t2.p_vecMax.z);
}