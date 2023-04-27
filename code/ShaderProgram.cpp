/// \file ShaderProgram.cpp
/// \brief Definitions of ShaderProgram class member and associated global
///   functions.
/// \author Gary M. Zoppetti, Ph.D. & Chad Hogg
/// \version A02

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.hpp"
#include "Matrix4.hpp"
#include "Vector3.hpp"

ShaderProgram::ShaderProgram (OpenGLContext* context)
  : m_context (context), m_programId (m_context->createProgram ()), m_vertexShaderId (0), m_fragmentShaderId (0)
{
}

ShaderProgram::~ShaderProgram ()
{
  // Delete shaders and delete the program object.
  // We assume shaders are not shared among multiple programs.
  m_context->deleteShader (m_vertexShaderId);
  m_context->deleteShader (m_fragmentShaderId);
  m_context->deleteProgram (m_programId);
}

GLint
ShaderProgram::getAttributeLocation (const std::string& attributeName) const
{
  return m_context->getAttribLocation (m_programId, attributeName.c_str ());
}

GLint
ShaderProgram::getUniformLocation (const std::string& uniformName) const
{
  return m_context->getUniformLocation (m_programId, uniformName.c_str ());
}

void
ShaderProgram::setUniformMatrix (const std::string& uniform, const Matrix4& value)
{
  GLint location = getUniformLocation (uniform);
  m_context->uniformMatrix4fv (location, 1, GL_FALSE, value.data());
}

void
ShaderProgram::setUniformVec3 (const std::string& uniform, const Vector3& value)
{
  GLint location = getUniformLocation (uniform);
  glUniform3fv(location, 1, &value.m_x);
}

void
ShaderProgram::setUniformInt (const std::string& uniform, const int& value)
{
  GLint location = getUniformLocation (uniform);
  glUniform1i (location, value);
}

void
ShaderProgram::setUniformFloat (const std::string& uniform, const float& value)
{
  GLint location = getUniformLocation (uniform);
  glUniform1f (location, value);
}

void
ShaderProgram::createVertexShader (const std::string& vertexShaderFilename)
{
  m_vertexShaderId = m_context->createShader (GL_VERTEX_SHADER);
  if (m_vertexShaderId == 0)
  {
    fprintf (stderr, "Failed to create vertex shader object; exiting\n");
    exit (-1);
  }
  compileShader (vertexShaderFilename, m_vertexShaderId);
}

void
ShaderProgram::createFragmentShader (const std::string& fragmentShaderFilename)
{
  m_fragmentShaderId = m_context->createShader (GL_FRAGMENT_SHADER);
  if (m_fragmentShaderId == 0)
  {
    fprintf (stderr, "Failed to create fragment shader object; exiting\n");
    exit (-1);
  }
  compileShader (fragmentShaderFilename, m_fragmentShaderId);
}

void
ShaderProgram::compileShader (const std::string& shaderFilename,
			      GLuint shaderId)
{
  std::string sourceCode = readShaderSource (shaderFilename);
  const GLchar* sourceCodePtr = sourceCode.c_str ();
  // One array of char*. Do not need to specify length if null-terminated.
  m_context->shaderSource (shaderId, 1, &sourceCodePtr, nullptr);
  m_context->compileShader (shaderId);
  GLint isCompiled;
  m_context->getShaderiv (shaderId, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    std::string logFile = shaderFilename + ".log";
    writeInfoLog (shaderId, true, logFile);
    fprintf (stderr, "Compilation error for %s -- see log; exiting\n",
	     shaderFilename.c_str ());
    exit (-1);
  }
  m_context->attachShader (m_programId, shaderId);
}

void
ShaderProgram::link () const
{
  fprintf (stdout, "Linking shader program %d\n", m_programId);
  m_context->linkProgram (m_programId);
  GLint isLinked;
  m_context->getProgramiv (m_programId, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE)
  {
    writeInfoLog (0, false, "Link.log");
    fprintf (stderr, "Link error -- see log\n");
    exit (-1);
  }
  // After linking, the shader objects no longer need to be attached.
  // A shader won't be deleted until it is detached.
  m_context->detachShader (m_programId, m_vertexShaderId);
  m_context->detachShader (m_programId, m_fragmentShaderId);
}

void
ShaderProgram::enable ()
{
  m_context->useProgram (m_programId);
}

void
ShaderProgram::disable ()
{
  m_context->useProgram (0);
}

std::string
ShaderProgram::readShaderSource (const std::string& filename) const
{
  std::ifstream inFile (filename);
  if (!inFile)
  {
    fprintf (stderr, "File %s does not exist; exiting\n", filename.c_str ());
    exit (-1);
  }
  std::string fileString
    { std::istreambuf_iterator<char> (inFile), std::istreambuf_iterator<char> () };

  return fileString;
}

void
ShaderProgram::writeInfoLog (GLuint shaderId, bool isShader,
			     const std::string& logFilename) const
{
  GLint infoLogLength = 0;
  if (isShader)
    m_context->getShaderiv (shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  else
    m_context->getProgramiv (m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0)
  {
    // Avoid the overhead of vector<char>, which has to initialize
    //   each char.
    std::unique_ptr<char[]> infoLog (new char[infoLogLength]);
    if (isShader)
      m_context->getShaderInfoLog (shaderId, infoLogLength, nullptr, infoLog.get ());
    else
      m_context->getProgramInfoLog (m_programId, infoLogLength, nullptr, infoLog.get ());
    std::ofstream logStream (logFilename);
    logStream << infoLog.get () << std::endl;
  }
}
