#include "shader.h"

std::string Shader::ReadShader(const std::string &FilePath) {
    std::ifstream file(FilePath);
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compileShader(const std::string &source, GLenum type) {
    GLuint shader = glCreateShader(type);
    const char* code = source.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog;
    }

    return shader;
}

Shader::Shader(const std::string &vShaderPath, const std::string &fShaderPath) {
    std::string vCode = ReadShader(vShaderPath);
    std::string fCode = ReadShader(fShaderPath);

    GLuint vertexShader = compileShader(vCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fCode, GL_FRAGMENT_SHADER);

    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexShader);
    glAttachShader(ProgramID, fragmentShader);
    glLinkProgram(ProgramID);

    int success;
    char infoLog[512];
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED: " << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(ProgramID);
}

void Shader::use() const {
    glUseProgram(ProgramID);
}

GLuint Shader::getID() const {
    return ProgramID;
}

