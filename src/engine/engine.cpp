#include "engine.hpp"

Engine::Engine(){
    std::cout << "[] Engine created" << std::endl;
    init();
}

void Engine::update(){
    
}
Engine::~Engine(){
    std::cout << "[] Engine destroyed" << std::endl;
}

void Engine::init(){
    
    e_window = new Window("Sandbox Test", 1600, 900, false);
    e_window->createContext();
}

void Engine::start(){

    std::cout << e_window->m_title << std::endl;

    float lastFrame, deltaTime;
    std::cout << "[] Engine started" << std::endl;
    while(!glfwWindowShouldClose(e_window->getWindow())){

        e_window->clear();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //std::cout << deltaTime*1000 << std::endl; 

        e_window->update();
    }
}