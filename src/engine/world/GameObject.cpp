#include "GameObject.h"

GameObject::GameObject(const char* name)
    : g_name(name)
    {
    vertices.push_back({-1.0f, -1.0f, 0.0f});
    vertices.push_back({ -1.0f,  1.0f, 0.0f});
    vertices.push_back({ 1.0f, 1.0f, 0.0f});

    vertices.push_back({ -1.0f, -1.0f, 0.0f});
    vertices.push_back({ 1.0f, 1.0f, 0.0f});
    vertices.push_back({ 1.0f, -1.0f, 0.0f});
    setupMesh();
    g_shader = new Shader("/home/d/code/SandboxGame/shaders/block.vert", "/home/d/code/SandboxGame/shaders/block.frag");
}
void GameObject::render(Player* p){
    g_shader->use();

    glm::mat4 projection = glm::perspective(glm::radians(p->Zoom), (float)16.0f / (float)9.0f , 0.1f, 100.0f);
    g_shader->setMat4("projection", projection);

    glm::mat4 view = p->GetViewMatrix();
    g_shader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    g_shader->setMat4("model", model);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    //std::cout << "rendering: " << g_name << vao << std::endl;

}
void GameObject::setupMesh(){
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    std::cout << vao << std::endl;
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    //std::cout << vertices << std::endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}