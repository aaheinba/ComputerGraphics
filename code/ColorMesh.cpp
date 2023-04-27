/// \file ColorMesh.cpp
/// \brief ColorMesh class and any associated functions.
/// \author Aaron Heinbaugh
/// \version A08

#include "Mesh.hpp"
#include "ColorMesh.hpp"

    ColorMesh::ColorMesh (OpenGLContext* context, ShaderProgram* shader):
    Mesh::Mesh(context, shader)
    {};

    ColorMesh::~ColorMesh(){}

    unsigned int
    ColorMesh::getFloatsPerVertex () const
    {
        return Mesh::getFloatsPerVertex() + 3;
    };

    void
    ColorMesh::enableAttributes()
    {
        Mesh::enableAttributes();
        const GLint COLOR_ATTRIB_INDEX = 1;
        m_context->enableVertexAttribArray (COLOR_ATTRIB_INDEX);
        // Colors have 3 parts, each are floats, and start at 10th position in array
        m_context->vertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
			reinterpret_cast<void*> (3 * sizeof(float)));
    };