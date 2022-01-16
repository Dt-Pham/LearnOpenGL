#ifndef mesh_hpp
#define mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> textures);
    
    void Draw(const Shader &shader);

    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
private:
    // render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif