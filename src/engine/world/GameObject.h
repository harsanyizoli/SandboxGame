#include "../../common.h"
#include "../graphics/shader.h"

class GameObject
{
private:

    float posx, posy, posz;
    char* o_name;
    char* o_texture;
    Shader o_shader;
    char* o_vertex_shader;
    char* o_fragment_shader;
    char* o_object_model;
    int o_num_of_vertices;

    float o_vertex[9] = {
        -0.5f, -0.5f, -0.5f,
         0.0f, 0.5f, 0.0f, 
         0.5, -0.5f, 0.5f
    };

    int o_vao;

public:
    GameObject();
    GameObject(char* name, char* vertex_shader, char* fragment_shader);
    GameObject(char* name);
    ~GameObject();

    void render();
    void printInfo();
};

GameObject::GameObject(char* name){
    this->o_name = name;
}

GameObject::GameObject(char* name, char* vertex_shader, char* fragment_shader){
    this->o_name = name;
    o_shader = Shader(vertex_shader, fragment_shader);
}

GameObject::~GameObject()
{
}

void GameObject::render(){
    std::cout << "rendering object " << this->o_name << std::endl;
}
void GameObject::printInfo(){
    std::cout << this->o_name << std::endl;
}