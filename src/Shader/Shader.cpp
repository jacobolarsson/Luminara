#include "Shader.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

unsigned CompileAttachShader(unsigned shaderId, const char* filename, unsigned shaderType)
{
    // load shader file
    std::ifstream inFile(filename, std::ios::in);
    if (!inFile) {
        std::cerr << "File not found." << std::endl;
        return 0;
    }

    std::ostringstream codeStream;
    while (inFile.good()) {
        int c = inFile.get();
        if (!inFile.eof())
            codeStream << static_cast<char>(c);
    }
    inFile.close();

    // Create shader
    unsigned shaderhandle = 0;
    shaderhandle = glCreateShader(shaderType);

    // Set source to shader
    std::string code = codeStream.str();
    const char* c_code = code.c_str();
    glShaderSource(shaderhandle, 1, &c_code, NULL);

    // Compile the shader
    glCompileShader(shaderhandle);

    // Check for errors
    int result;
    glGetShaderiv(shaderhandle, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {
        // Compile failed, store log and return false
        int length = 0;

        glGetShaderiv(shaderhandle, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            char* c_log = new char[static_cast<size_t>(length) + 1];
            int    written = 0;
            glGetShaderInfoLog(shaderhandle, length, &written, c_log);
            std::cerr << c_log << std::endl;
            delete[] c_log;
        }

        return 0;
    }
    else {
        // Compile succeeded, attach shader and return true
        glAttachShader(shaderId, shaderhandle);

        glDeleteShader(shaderhandle);
        return shaderId;
    }
}

unsigned LinkProgram(unsigned shaderId)
{
    if (shaderId <= 0u) {
        return 0u;
    }

    // Link shader program
    glLinkProgram(shaderId);

    // Check for errors
    int status = 0;
    glGetProgramiv(shaderId, GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        // Store log and return false
        int length = 0;

        glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            char* c_log = new char[static_cast<size_t>(length) + 1];
            int    written = 0;
            glGetProgramInfoLog(shaderId, length, &written, c_log);
            std::cerr << c_log << std::endl;
            delete[] c_log;
        }

        return 0u;
    }

    return shaderId;
}

Shader::Shader(const char* vertFilename, const char* fragFilename) : m_id(0u)
{
    m_id = glCreateProgram();
    if (m_id == 0u) {
        std::cerr << "Unable to create shader handle id." << std::endl;
        return;
    }
    if (CompileAttachShader(m_id, vertFilename, GL_VERTEX_SHADER) == 0u) {
        std::cerr << "Unable to compile vertex shader." << std::endl;
        return;
    }
    if (CompileAttachShader(m_id, fragFilename, GL_FRAGMENT_SHADER) == 0u) {
        std::cerr << "Unable to compile fragment shader." << std::endl;
        return;
    }
    if (LinkProgram(m_id) == 0u) {
        std::cerr << "Unable to link shader program." << std::endl;
        return;
    }
}

void Shader::Use() const
{
    if (m_id != 0u) {
        glUseProgram(m_id);
    } else {
        std::cerr << "Shader handle id not set" << std::endl;
    }
}

void Shader::UploadMat4x4(const char* name, mat4x4 const& mat) const
{
    glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, name), 1, GL_FALSE, &mat[0][0]);
}