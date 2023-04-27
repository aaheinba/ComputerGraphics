/// \file ShaderProgram.hpp
/// \brief Declaration of ShaderProgram class and any associated global
///   functions.
/// \author Gary M. Zoppeti, Ph.D., Chad Hogg
/// \version A02

#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>

#include <glm/mat4x4.hpp>

#include "OpenGLContext.hpp"
#include "Matrix4.hpp"
#include "Vector3.hpp"

/// \brief A class that simplifies creation of and access to shaders.
class ShaderProgram
{
public:

  /// \brief Constructs a new ShaderProgram with no attached shaders.
  /// \param[in] context A pointer to an object through which the
  ///   ShaderProgram can make OpenGL calls.
  ShaderProgram (OpenGLContext* context);

  /// \brief Destructs this ShaderProgram, which deletes all OpenGL resources
  ///   used by it.
  ~ShaderProgram ();

  /// \brief Copy constructor removed because you shouldn't be copying
  ///   ShaderPrograms.
  ShaderProgram (const ShaderProgram&) = delete;

  /// \brief Assignment operator removed because you shouldn't be assigning
  ///   ShaderPrograms.
  ShaderProgram&
  operator= (const ShaderProgram&) = delete;

  /// \brief Gets the OpenGL location of the attribute with a certain name.
  /// \param[in] attributeName The name of the requested attribute.
  /// \return The location of that attribute.
  /// \pre This ShaderProgram is enabled.
  /// \pre An attached shader has declared the attribute variable.
  GLint
  getAttributeLocation (const std::string& attributeName) const;

  /// \brief Gets the OpenGL location of the uniform with a certain name.
  /// \param[in] uniformName The name of the requested uniform.
  /// \return The location of that uniform.
  /// \pre This ShaderProgram is enabled.
  /// \pre An attached shader has declared the uniform variable.
  GLint
  getUniformLocation (const std::string& uniformName) const;

  /// \brief Sets the value of a uniform 4x4 matrix of floats.
  /// \param[in] uniform The name of the uniform.
  /// \param[in] value The matrix to use.
  /// \pre This ShaderProgram is enabled.
  /// \pre An attached shader has declared the uniform variable.
  void
  setUniformMatrix (const std::string& uniform, const Matrix4& value);

  void
  setUniformVec3 (const std::string& uniform, const Vector3& value);

  void
  setUniformFloat (const std::string& uniform, const float& value);
  
  void
  setUniformInt (const std::string& uniform, const int& value);

  /// \brief Creates and attaches a vertex shader.
  /// \param[in] vertexShaderFilename The name of a file that contains the
  ///   vertex shader's source code.
  /// \pre No vertex shader was previously created.
  void
  createVertexShader (const std::string& vertexShaderFilename);

  /// \brief Creates and attaches a fragment shader.
  /// \param[in] fragmentShaderFilename The name of a file that contains the
  ///   fragment shader's source code.
  /// \pre No fragment shader was previously created.
  void
  createFragmentShader (const std::string& fragmentShaderFilename);

  /// \brief Links the attached shaders into this ShaderProgram.
  /// \pre A vertex and fragment shader had been created.
  /// \pre This ShaderProgram had not already been linked.
  void
  link () const;

  /// \brief Makes this ShaderProgram the one that will be used by future
  ///   OpenGL calls.
  void
  enable ();

  /// \brief Ensures that future OpenGL calls will not affect this
  ///   ShaderProgram (until it is subsequently re-enabled).
  void
  disable ();

private:

  /// \brief Compiles a shader.
  /// \param[in] shaderFilename The name of a file that contains the shader's
  ///   source code.
  /// \param[in] shaderId The OpenGL identifier associated with the shader.
  void
  compileShader (const std::string& shaderFilename, GLuint shaderId);

  /// \brief Reads the source code for a shader from a file.
  /// \param[in] filename The name of a file that contains the shader's source
  ///   code.
  /// \return The contents of that file.
  std::string
  readShaderSource (const std::string& filename) const;

  /// \brief Writes an info log to a file.
  /// \param[in] shaderId The OpenGL identifier associated with the shader the
  ///   log should come from, if associated with a specific shader.
  /// \param[in] isShader Whether we want a log for a specific shader or the
  ///   program as a whole.
  /// \param[in] logFilename The name of a file to which the log should be
  ///   written.
  /// \post That file has been created / truncated and filled with the info
  ///   log.
  void
  writeInfoLog (GLuint shaderId, bool isShader,
		const std::string& logFilename) const;

private:

  /// An object through which this ShaderProgram can make OpenGL calls.
  OpenGLContext* m_context;
  /// The OpenGL identifier given to this ShaderProgram.
  GLuint m_programId;
  /// The OpenGL identifier given to the vertex shader.
  GLuint m_vertexShaderId;
  /// The OpenGL identifier given to the fragment shader.
  GLuint m_fragmentShaderId;
};

#endif//SHADER_PROGRAM_HPP
