#include "ShaderProgram.h"
#include "FileReared.h"
#include<iostream>
#include<glad/glad.h>

ShaderProgram::ShaderProgram(const std::string& vsFile, const std::string& fsFile)
{
    std::string vertexCode = FileReared::ReadFileFromSource(vsFile);
    std::string fragmentCode = FileReared::ReadFileFromSource(fsFile);
    
    if (vertexCode.length() == 0 || fragmentCode.length() == 0)
    {
        std::cout << "ERROR WHILE READING FILE !!!" << std::endl; 
        return;
    }
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);
    m_ProgramID = glCreateProgram();
    AttachAndLinkProgram(vertexShader,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
ShaderProgram::~ShaderProgram(){
    if (m_ProgramID != 0)
    {
        glDeleteProgram(m_ProgramID);
    };
    
}
void ShaderProgram::Use()
{
    glUseProgram(m_ProgramID);
}
unsigned int ShaderProgram::CompileShader(unsigned int type, std::string& source)
{
    unsigned int id = glCreateShader(type); // ilgili type da boş bir shader oluştur.
    const char* src = source.c_str(); // gelen stringi c stringe çevir öyle kabul edio
    glShaderSource(id,1,&src,nullptr); // ilgili id den 1 adet gelen string ile nullptr uzunluğunda bir shader sourcesi al
    glCompileShader(id); // aldığın shaderi compile et procedural library awk arkaya bir yere atio.

    int success;
    char infolog[512];

    //error check
    glGetShaderiv(id,GL_COMPILE_STATUS, &success); // ilgili shader idsine göre compile status bilgisini ürettiriyoruz.
    if (!success)
    {
        glGetShaderInfoLog(id,512,NULL,infolog); // ilgili shader idsinin 512 charlik logunu alıyoruz
        std::string shaderTypeString = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT"; // tip ternarysi
        std::cerr << "[SHADER COMPILE ERROR] (" << shaderTypeString <<")\n" << infolog << std::endl;
    };
    return id;
}
void ShaderProgram::AttachAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    int success; 
    char infolog[512];
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS,&success);
    if (!success)
    {
        glGetProgramInfoLog(m_ProgramID,512,NULL,infolog);
        std::cerr << "[SHADER LINK ERROR]\n" << infolog << std::endl;
    }
}

void ShaderProgram::setVec2(const std::string& name, float x, float y) const 
{
    glUniform2f(glGetUniformLocation(m_ProgramID,name.c_str()), x, y);
}
void ShaderProgram::setVec3(const std::string& name, float x, float y,float z) const 
{
    glUniform3f(glGetUniformLocation(m_ProgramID,name.c_str()), x, y,z);
}
void ShaderProgram::setVec4(const std::string& name, float x, float y, float z ,float w) const 
{
    glUniform4f(glGetUniformLocation(m_ProgramID,name.c_str()), x, y, z,w);
}