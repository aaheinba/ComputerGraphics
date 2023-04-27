/// \file NormalsMesh.hpp
/// \brief Declaration of NormalsMesh class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A08


#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// You also need to make a change to your Makefile.
// It contains a list of libraries to link in, and you need to add -lassimp to that list.

#include "Mesh.hpp"

class NormalsMesh: public Mesh
{
    public:

    /// \brief Constructs a NormalsMesh with triangles pulled from a file.
    /// \param[in] context A pointer to an objec tthrough which the Mesh will be
    ///   able to make OpenGL calls.
    /// \param[in] shader A pointer to the shader program that should be used for
    ///   drawing this mesh.
    /// \param[in] fileName The name of the file this mesh's geometry should be
    ///   read from.
    /// \param[in] meshNum The 0-based index of which mesh from that file should
    ///   be used.
    /// \post A unique VAO, VBO, and IBO have been generated for this Mesh and
    ///   stored for later use.
    /// \post If that file exists and contains a mesh of that number, the indexes
    ///   and geometry from it have been pre-populated into this Mesh.  Otherwise
    ///   this Mesh is empty and an error message has been printed.
    NormalsMesh (OpenGLContext* context, ShaderProgram* shader);

    NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string fileName, unsigned int meshNum);

    ~NormalsMesh();

    virtual unsigned int
    getFloatsPerVertex () const;

    virtual void
    enableAttributes();
};