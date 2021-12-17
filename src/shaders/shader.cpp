#include "shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // 1. Read shaders from file
    std::string vertexSource;
    std::string fragmentSource;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vertexSource = vShaderStream.str();
        fragmentSource = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    
    const char *vShaderCode = vertexSource.c_str();
    const char *fShaderCode = fragmentSource.c_str();
    
    // 2. Compile shaders
    unsigned int vShader, fShader;
    int success;
    constexpr int logSize = 512;
    char infoLog[logSize];
    
    // vertex shader
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderCode, NULL);
    glCompileShader(vShader);
    
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, logSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // fragment shader
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderCode, NULL);
    glCompileShader(fShader);
    
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, logSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    // shader program
    programID = glCreateProgram();
    glAttachShader(programID, vShader);
    glAttachShader(programID, fShader);
    glLinkProgram(programID);
    
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, logSize, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

unsigned int Shader::ID() const
{
    return programID;
}

void Shader::use() const
{
    glUseProgram(programID);
}

void Shader::setInt(const char *name, int value) const
{
    GLint loc = glGetUniformLocation(programID, name);
    glUniform1i(loc, value);
}

void Shader::setBool(const char *name, bool value) const
{
    GLint loc = glGetUniformLocation(programID, name);
    glUniform1i(loc, static_cast<int>(value));
}

void Shader::setFloat(const char *name, float value) const
{
    GLint loc = glGetUniformLocation(programID, name);
    glUniform1f(loc, value);
}

void Shader::setMat4(const char *name, glm::mat4 value) const
{
    GLint loc = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
