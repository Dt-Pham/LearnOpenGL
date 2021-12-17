#ifndef shader_hpp
#define shader_hpp

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // Constructor
    Shader(const char *vertexPath, const char *fragmentPath);
    
    // getter
    unsigned int ID() const;
    
    // activate the shader
    void use() const;
    
    // untility uniform functions
    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
    void setMat4(const char *name, const glm::mat4 &value) const;

private:
    unsigned int programID;
};

#endif /* shader_hpp */
