#include "ShaderProgram.h"
#include <glad/glad.h>
#include "File.h"
 
ShaderProgram::ShaderProgram(const std:: string& vertexPath, const std::string& fragmentPath):
m_ProgramID(0)
{
    std::string vertexCode = File::readTextFileToCString(vertexPath);
    std::string fragmentCode = File::readTextFileToCString(fragmentPath);
    
    if (vertexCode.length() == 0 || fragmentCode.length() == 0)
    {
        std::cout << "Erro while reading shader files" << std::endl;
        return;
    }
    
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID,fragmentShader);
    glLinkProgram(m_ProgramID);

    int success;
    char infolog[512];
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ProgramID, 512,NULL,infolog);
        std::cerr << "[SHADER LINK ERROR]\n" << infolog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

ShaderProgram::~ShaderProgram() {
    if (m_ProgramID != 0)
    {
        glDeleteProgram(m_ProgramID);
    }
    
}

void ShaderProgram::Use()
{
    glUseProgram(m_ProgramID);
}

unsigned int ShaderProgram::compileShader(unsigned int type, std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    char infolog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS,&success);
    if (!success)
    {
        glGetShaderInfoLog(id,512,NULL, infolog);
        std::string shaderTypeString = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cerr << "[SHADER COMPILE ERROR] (" << shaderTypeString <<")\n" << infolog << std::endl;
    }

    return id;
}
// --- Uniform Yardımcıları ---
void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}