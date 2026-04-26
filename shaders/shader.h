#ifndef SHADER_H
#define SHADER_H

#include "../glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  private:
    GLuint ProgramID;
    GLuint compileShader(const std::string &source, GLenum type);
    std::string ReadShader(const std::string &FilePath);

  public:
    Shader(const std::string &vShaderPath, const std::string &fShaderPath);
    ~Shader();

    void use() const;
    GLuint getID() const;
};

#endif
