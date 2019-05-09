#include "text_buffer.hpp"

TextBuffer::TextBuffer(size_t s)
    :size(s){
    ptr = allocateBufferMemory(size);
    ta = {0};
    ta.shader = new Shader("/home/d/Documents/SandboxGL/shaders/text.vert" ,"/home/d/Documents/SandboxGL/shaders/text.frag");
    ta.normal = 0;
    ta.uv = 1;
    ta.program = ta.shader->ID;
    ta.sampler = glGetUniformLocation(ta.program, "Texture");
    std::cout << "Constructor" << std::endl;
    makeChar("asd");
    genBuffers();
    std::cout << "texture loading" << std::endl;
    loadTexture((char*)"/home/d/Documents/SandboxGL/textures/font.png");
}

TextBuffer::~TextBuffer()
{
}

char* TextBuffer::allocateBufferMemory(size_t size){
    return (char*)allocate_memory(size);
}
void TextBuffer::setTextToBeRendered(){
    //TODO
}
void TextBuffer::makeChar(std::string string){
    vertex_2d v1 = {origin_x, origin_y, 127/512, 31/512};
    vertex_2d v2 = {origin_x + 32, origin_y, 127/512, 63/512};
    vertex_2d v3 = {origin_x + 32, origin_y + 32, 159/512, 63/512};

    vertex_2d v4 = {origin_x, origin_y , 127/512, 31/512};
    vertex_2d v5 = {origin_x + 32, origin_y + 32, 159/512, 63/512};
    vertex_2d v6 = {origin_x, origin_y + 32, 159/512, 31/512};

    vertices.emplace_back(v1);
    vertices.emplace_back(v2);
    vertices.emplace_back(v3);
    vertices.emplace_back(v4);
    vertices.emplace_back(v5);
    vertices.emplace_back(v6);
}
void TextBuffer::genBuffers(){
    std::cout << "Textbuffer genbuffer" << std::endl;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_2d), &vertices[0], GL_STATIC_DRAW);
    std::cout << vertices.size() << std::endl;
    glVertexAttribPointer(ta.normal, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(ta.uv, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(ta.normal);
    glEnableVertexAttribArray(ta.uv);
}
void TextBuffer::bind(){
    glBindVertexArray(vao);
    std::cout << "Textbuffer bind" << std::endl;
}
void TextBuffer::unbind(){
    glBindVertexArray(0);
    std::cout << "Textbuffer unbind" << std::endl;
}
void TextBuffer::loadTexture(char* filename){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    unsigned int error;
    unsigned char *data;
    unsigned int width, height;
    error = lodepng_decode32_file(&data, &width, &height, filename);
    if (error) {
        fprintf(stderr, "load_png_texture %s failed, error %u: %s\n", filename, error, lodepng_error_text(error));
        exit(1);
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    free(data);
    ta.shader->use();
    ta.shader->setInt("Texture", 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}