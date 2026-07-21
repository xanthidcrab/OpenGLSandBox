#pragma once
#include <string>
class ShaderProgram{
    private: 
        unsigned int m_ProgramID;
        unsigned int compileShader(unsigned int type, std::string& source);

    public:
        ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
        ~ShaderProgram();
        void Use();
        unsigned int getProgramID() const {return m_ProgramID;}


        // Uniform ayarlama yardımcı fonksiyonları (örnek olarak birkaçı)
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
};