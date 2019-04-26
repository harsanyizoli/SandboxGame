#include "engine/common.h"
#include "engine/engine.hpp"
#include "engine/utils/util.h"

float deltaTime, lastFrame;
FPS fps = {0, 0};

int main(int argc, char const *argv[])
{
    Engine game;
    game.run();
}
