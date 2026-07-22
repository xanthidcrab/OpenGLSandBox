#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    unsigned int ID;

    VAO() {
        glGenVertexArrays(1, &ID);
    }

    ~VAO() {
        glDeleteVertexArrays(1, &ID);
    }

    // Kopyalamayı engelle & Taşıma izni ver
    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

    VAO(VAO&& other) noexcept : ID(other.ID) {
        other.ID = 0;
    }
    VAO& operator=(VAO&& other) noexcept {
        if (this != &other) {
            glDeleteVertexArrays(1, &ID);
            ID = other.ID;
            other.ID = 0;
        }
        return *this;
    }

    void Bind() const {
        glBindVertexArray(ID);
    }

    void Unbind() const {
        glBindVertexArray(0);
    }

    // VBO'yu VAO'ya bağlayan ve düzenini (layout) belirten pratik metod
    void LinkAttribute(const VBO& vbo, GLuint layout, GLint count, GLenum type, GLsizei stride, const void* offset) const {
        Bind();
        vbo.Bind();
        glVertexAttribPointer(layout, count, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        Unbind();
    }
};