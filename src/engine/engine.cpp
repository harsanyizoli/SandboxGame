#include "engine.hpp"



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
    e_window = new Window("Sandbox Test", scr_width, scr_height, false);
    e_window->createContext();
    e_world = new World();

    Renderer::gen_text_buffer("asd");
    
}

void Engine::run(){

    float lastFrame, deltaTime;
    std::cout << "[] Engine started" << std::endl;

    while(!glfwWindowShouldClose(e_window->getWindow())){

        e_window->clear();
        float currentFrame = glfwGetTime();
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