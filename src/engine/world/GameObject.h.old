#include "../common.h"
#include "../graphics/shader.h"
#include <vector>

class GameObject
{
private:

    typedef struct
    {
        float x;
        float y;
        float z;
    } vertex;
    

    float posx, posy, posz;
    const char* o_name;
    char* o_texture;
    Shader o_shader;
    char* o_vertex_shader;
    char* o_fragment_shader;
    char* o_object_model;
    int o_num_of_vertices;

    std::vector<vertex> o_vertices;
    unsigned int o_vao, o_vbo;

public:
    GameObject();
    GameObject(const char* name,const char* vertex_shader,const char* fragment_shader);
    GameObject(const char* name);
    ~GameObject();

    void genBlock();
    void render();
    char* printInfo();
};

GameObject::GameObject(const char* name){
    o_name = name;
}

GameObject::GameObject(const char* name,const char* vertex_shader,const char* fragment_shader){
    o_name = name;
    o_shader = Shader(vertex_shader, fragment_shader);
    std::cout << "gameobject constructor" << std::endl;
    genBlock();
}

GameObject::~GameObject()
{
}

void GameObject::genBlock(){

    o_vertices.push_back({-1.0f, -1.0f , 1.0f});
    o_vertices.push_back({ 0.0f,  1.0f , 1.0f});
    o_vertices.push_back({ 1.0f, -1.0f , 1.0f});

    glGenVertexArrays(1, &o_vao);
    glGenBuffers(1, &o_vbo);

    glBindVertexArray(o_vao);

    glBindBuffer(GL_ARRAY_BUFFER, o_vbo);
    glBufferData(GL_ARRAY_BUFFER, o_vertices.size() * sizeof(vertex), &o_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GameObject::render(){
    o_shader.use();
    glBindVertexArray(o_vao);
    std::cout << o_vao << std::endl;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 300.0f);
    o_shader.setMat4("projection", projection);
  
    glm::mat4 view = glm::mat4(1.0f);
    o_shader.setMat4("view", view);
    
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
    o_shader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    std::cout << "rendering object " << o_name << std::endl;
}
char* GameObject::printInfo(){
    //std::cout << o_name << std::endl;
    return (char*)o_name;
}