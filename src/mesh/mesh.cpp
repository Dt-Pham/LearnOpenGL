#include "mesh.hpp"




Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    setupMesh();
}

void Mesh::Draw(const Shader &shader)
{

}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}