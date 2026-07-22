#pragma once
#include <glad/glad.h>
#include <vector>

class VBO {
public:
    unsigned int ID;

    // Constructor: Veriyi alıp doğrudan GPU'ya yükler
    VBO(const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    // RAII: Sınıf yok olduğunda GPU'daki buffer'ı siler
    ~VBO() {
        glDeleteBuffers(1, &ID);
    }

    // Kopyalamayı engelle (Aynı ID'nin iki defa silinmesini önler)
    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    // Taşıma (Move) işlemlerine izin ver
    VBO(VBO&& other) noexcept : ID(other.ID) {
        other.ID = 0;
    }
    VBO& operator=(VBO&& other) noexcept {
        if (this != &other) {
            glDeleteBuffers(1, &ID);
            ID = other.ID;
            other.ID = 0;
        }
        return *this;
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};