#pragma once
#include <string>
class ShaderProgram
{
private:
    unsigned int m_ProgramID;
    void AttachAndLinkProgram(unsigned int vertexShader, unsigned int fragmentShader);
    unsigned int CompileShader(unsigned int type, std::string& source);
public:
    ShaderProgram(const std::string& vsPath,const std::string& fsPath);
    ~ShaderProgram();
    void Use();
    operator unsigned int() {return m_ProgramID;}
    // Vector Uniform Set Fonksiyonları (Ham Float)
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
};

 