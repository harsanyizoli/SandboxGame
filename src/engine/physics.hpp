#ifndef PHYSICS_H
#define PHYSICS_H

#include "common.h"

namespace Physics
{
    struct AABB {
        glm::vec3 p_vecMin;
        glm::vec3 p_vecMax;

        AABB(glm::vec3 min, glm::vec3 max):p_vecMin(min), p_vecMax(max){}

        void move(glm::vec3 pos){
            p_vecMin += pos;
            p_vecMax += pos;
        }
        void moveYto(float y){
            p_vecMin.y = y;
            p_vecMax.y = y;
        }
    };

    bool AABBtoAABB(const AABB& t1, const AABB& t2);
} // namespace Physics

#endif