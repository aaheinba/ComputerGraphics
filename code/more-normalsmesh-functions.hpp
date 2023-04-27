// This file contains an additional constructor you will add to your NormalsMesh class.
// Don't actually put this file into your project -- just copy from it.

// In order to use this, you need the following includes:

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

// You also need to make a change to your Makefile.
// It contains a list of libraries to link in, and you need to add -lassimp to that list.

// This goes in the header file:

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
  NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string fileName, unsigned int meshNum);


// This goes in the source file:

NormalsMesh::NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string filename, unsigned int meshNum)
  : NormalsMesh (context, shader)
{
  Assimp::Importer importer;
  unsigned int flags =
    aiProcess_Triangulate              // convert all shapes to triangles
    | aiProcess_GenSmoothNormals       // create vertex normals if not there
    | aiProcess_JoinIdenticalVertices; // combine vertices for indexing
  const aiScene* scene = importer.ReadFile (filename,
					    flags);
  if (scene == nullptr)
  {
    auto error = importer.GetErrorString ();
    std::cerr << "Failed to load model " << filename << " with error " << error << std::endl;
  }
  else
  {
    if(meshNum >= scene->mNumMeshes)
    {
      std::cerr << "Could not read mesh " << meshNum << " from " << filename << " because it only has " << scene->mNumMeshes << " meshes." << std::endl;
    }
    else
    {
      const aiMesh* mesh = scene->mMeshes[meshNum];
      std::vector<float> vertexData;
      std::vector<unsigned int> indexes;
      for (unsigned vertexNum = 0; vertexNum < mesh->mNumVertices; ++vertexNum)
      {
	vertexData.push_back (mesh->mVertices[vertexNum].x);
	vertexData.push_back (mesh->mVertices[vertexNum].y);
	vertexData.push_back (mesh->mVertices[vertexNum].z);
	vertexData.push_back (mesh->mNormals[vertexNum].x);
	vertexData.push_back (mesh->mNormals[vertexNum].y);
	vertexData.push_back (mesh->mNormals[vertexNum].z);
      }
      for (unsigned int faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
      {
	const aiFace& face = mesh->mFaces[faceNum];
	for (unsigned int indexNum = 0; indexNum < 3; ++indexNum)
	{
	  unsigned int vertexNum = face.mIndices[indexNum];
	  indexes.push_back (vertexNum);
	}
      }
      addGeometry (vertexData);
      addIndices (indexes);
    }
  }
}
