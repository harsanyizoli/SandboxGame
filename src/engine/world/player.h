#include "GameObject.h"
#include "../common.h"

class player : public GameObject
{
private:
    glm::vec3 Front;

public:
    player();
    ~player();
};

player::player()
{
}

player::~player()
{
}
