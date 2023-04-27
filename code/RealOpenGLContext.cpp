/// \file RealOpenGLContext.cpp
/// \brief Definitions of RealOpenGLContext member and associated global
///   functions.
/// \author Chad Hogg
/// \version A02

#include "RealOpenGLContext.hpp"

RealOpenGLContext::RealOpenGLContext ()
{
}

RealOpenGLContext::~RealOpenGLContext ()
{
}


void
RealOpenGLContext::attachShader (GLuint program, GLuint shader)
{
  glAttachShader (program, shader);
}

void
RealOpenGLContext::bindBuffer (GLenum target, GLuint buffer)
{
  glBindBuffer (target, buffer);
}

void
RealOpenGLContext::bindVertexArray (GLuint array)
{
  glBindVertexArray (array);
}

void
RealOpenGLContext::bufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
  glBufferData (target, size, data, usage);
}

void
RealOpenGLContext::clear (GLbitfield mask)
{
  glClear (mask);
}

void
RealOpenGLContext::clearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  glClearColor (red, green, blue, alpha);
}

void
RealOpenGLContext::compileShader (GLuint shader)
{
  glCompileShader (shader);
}

GLuint
RealOpenGLContext::createProgram ()
{
  return glCreateProgram ();
}

GLuint
RealOpenGLContext::createShader (GLenum shaderType)
{
  return glCreateShader (shaderType);
}

void
RealOpenGLContext::cullFace (GLenum mode)
{
  glCullFace (mode);
}

void
RealOpenGLContext::deleteBuffers (GLsizei n, const GLuint* buffers)
{
  glDeleteBuffers (n, buffers);
}

void
RealOpenGLContext::deleteProgram (GLuint program)
{
  glDeleteProgram (program);
}

void
RealOpenGLContext::deleteShader (GLuint shader)
{
  glDeleteShader (shader);
}

void
RealOpenGLContext::deleteVertexArrays (GLsizei n, const GLuint* arrays)
{
  glDeleteVertexArrays (n, arrays);
}

void
RealOpenGLContext::detachShader (GLuint program, GLuint shader)
{
  glDetachShader (program, shader);
}

void
RealOpenGLContext::drawArrays (GLenum mode, GLint first, GLsizei count)
{
  glDrawArrays (mode, first, count);
}

void
RealOpenGLContext::enable (GLenum cap)
{
  glEnable (cap);
}

void
RealOpenGLContext::enableVertexAttribArray (GLuint index)
{
  glEnableVertexAttribArray (index);
}

void
RealOpenGLContext::frontFace (GLenum mode)
{
  glFrontFace (mode);
}

void
RealOpenGLContext::genBuffers (GLsizei n, GLuint* buffers)
{
  glGenBuffers (n, buffers);
}

void
RealOpenGLContext::genVertexArrays (GLsizei n, GLuint* arrays)
{
  glGenVertexArrays (n, arrays);
}

GLint
RealOpenGLContext::getAttribLocation (GLuint program, const GLchar* name)
{
  return glGetAttribLocation (program, name);
}

void
RealOpenGLContext::getProgramInfoLog (GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog)
{
  glGetProgramInfoLog (program, maxLength, length, infoLog);
}

void
RealOpenGLContext::getProgramiv (GLuint program, GLenum pname, GLint* params)
{
  glGetProgramiv (program, pname, params);
}

void
RealOpenGLContext::getShaderInfoLog (GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog)
{
  glGetShaderInfoLog (shader, maxLength, length, infoLog);
}

void
RealOpenGLContext::getShaderiv (GLuint shader, GLenum pname, GLint* params)
{
  glGetShaderiv (shader, pname, params);
}

const GLubyte*
RealOpenGLContext::getString (GLenum name)
{
  return glGetString (name);
}

GLint
RealOpenGLContext::getUniformLocation (GLuint program, const GLchar* name)
{
  return glGetUniformLocation (program, name);
}

void
RealOpenGLContext::linkProgram (GLuint program)
{
  glLinkProgram (program);
}

void
RealOpenGLContext::shaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
  glShaderSource (shader, count, string, length);
}

void
RealOpenGLContext::uniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  glUniformMatrix4fv (location, count, transpose, value);
}

void
RealOpenGLContext::useProgram (GLuint program)
{
  glUseProgram (program);
}

void
RealOpenGLContext::vertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
  glVertexAttribPointer (index, size, type, normalized, stride, pointer);
}

void
RealOpenGLContext::viewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
  glViewport (x, y, width, height);
}
