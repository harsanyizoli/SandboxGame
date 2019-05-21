#include "engine.hpp"
#include <filesystem>
#include <thread>

Engine::Engine(){
    std::cout << "[] Engine created" << std::endl;
    init();
}

void Engine::update(float delta){
    e_world->update(delta);
    //std::cout << e_world->name << std::endl;
}

Engine::~Engine(){
    std::cout << "[] Engine destroyed" << std::endl;
}

void Engine::init(){   
    e_window = new Window(config.title, config.scr_width, config.scr_height, config.fullscr);
    e_window->createContext();
    e_world = new World();}


void Engine::run(){

    //std::cout << "thread id engine" << std::this_thread::get_id() << std::endl;

    float lastFrame, deltaTime;
    std::cout << "[] Engine started" << std::endl;

    while(!glfwWindowShouldClose( e_window->getWindow() )){

        e_window->clear();
        float currentFrame = getTimer();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        std::cout << 1/deltaTime << std::endl;
        //Renderer::draw_fps(deltaTime);
        update(deltaTime);
        chechForClose();

        e_window->update();
    }
}
void Engine::chechForClose(){
    if(Window::isKeyPressed(GLFW_KEY_ESCAPE))
        e_window->close(true);
}

double Engine::getTimer(){
    return Window::getCurrentTimer();
}