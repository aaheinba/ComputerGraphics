/// \file ColorMesh.hpp
/// \brief Declaration of ColorMesh class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A08

#include "Mesh.hpp"

class ColorMesh: public Mesh
{
    public:

    ColorMesh (OpenGLContext* context, ShaderProgram* shader);

    ~ColorMesh();

    virtual unsigned int
    getFloatsPerVertex () const;

    virtual void
    enableAttributes();
};