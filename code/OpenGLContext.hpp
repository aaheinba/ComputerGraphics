/// \file OpenGLContext.hpp
/// \brief Declaration of OpenGLContext class and any associated global
///   functions.
/// \author Chad Hogg
/// \version A02


#ifndef OPENGL_CONTEXT_HPP
#define OPENGL_CONTEXT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// \brief A class that works as a proxy between clients and the OpenGL
///   library.
///
/// The reason this exists is to make testing of OpenGL programs easier.  This
///   is an abstract class, and a subclass that directly passes calls on to
///   OpenGL is provided, ReadOpenGLContext.  Other subclasses allow inspection
///   or mocking of OpenGL calls.
/// Clients that have access to an OpenGLContext should *never* make OpenGL
///   calls directly; only through it.
class OpenGLContext
{
public:

  /// Destructs an OpenGLContext.
  virtual
  ~OpenGLContext () = 0;

  /// See documentation of glAttachShader.
  virtual void
  attachShader (GLuint program, GLuint shader) = 0;

  /// See documentation of glBindBuffer.
  virtual void
  bindBuffer (GLenum target, GLuint buffer) = 0;

  /// See documentation of glBindVertexArray.
  virtual void
  bindVertexArray (GLuint array) = 0;

  /// See documentation of glBufferData.
  virtual void
  bufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) = 0;

  /// See documentation of glClear.
  virtual void
  clear (GLbitfield mask) = 0;

  /// See documentation of glClearColor.
  virtual void
  clearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = 0;

  /// See documentation of glCompileShader.
  virtual void
  compileShader (GLuint shader) = 0;

  /// See documentation of glCreateProgram.
  virtual GLuint
  createProgram () = 0;

  /// See documentation of glCreateShader.
  virtual GLuint
  createShader (GLenum shaderType) = 0;

  /// See documentation of glCullFace.
  virtual void
  cullFace (GLenum mode) = 0;

  /// See documentation of glDeleteBuffers.
  virtual void
  deleteBuffers (GLsizei n, const GLuint* buffers) = 0;

  /// See documentation of glDeleteProgram.
  virtual void
  deleteProgram (GLuint program) = 0;

  /// See documentation of glDeleteShader.
  virtual void
  deleteShader (GLuint shader) = 0;

  /// See documentation of glDeleteVertexArrays.
  virtual void
  deleteVertexArrays (GLsizei n, const GLuint* arrays) = 0;

  /// See documentation of glDetachShader.
  virtual void
  detachShader (GLuint program, GLuint shader) = 0;

  /// See documentation of glDrawArrays.
  virtual void
  drawArrays (GLenum mode, GLint first, GLsizei count) = 0;

  /// See documentation of glEnable.
  virtual void
  enable (GLenum cap) = 0;

  /// See documentation of glEnableVertexAttribArray.
  virtual void
  enableVertexAttribArray (GLuint index) = 0;

  /// See documentation of glFrontFace.
  virtual void
  frontFace (GLenum mode) = 0;

  /// See documentation of glGenBuffers.
  virtual void
  genBuffers (GLsizei n, GLuint* buffers) = 0;

  /// See documentation of glGenVertexArrays.
  virtual void
  genVertexArrays (GLsizei n, GLuint* arrays) = 0;

  /// See documentation of glGetAttribLocation.
  virtual GLint
  getAttribLocation (GLuint program, const GLchar* name) = 0;

  /// See documentation of glGetProgramInfoLog.
  virtual void
  getProgramInfoLog (GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = 0;

  /// See documentation of glGetProgramiv.
  virtual void
  getProgramiv (GLuint program, GLenum pname, GLint* params) = 0;

  /// See documentation of glGetShaderInfoLog.
  virtual void
  getShaderInfoLog (GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = 0;

  /// See documentation of glGetShaderiv.
  virtual void
  getShaderiv (GLuint shader, GLenum pname, GLint* params) = 0;

  /// See documentation of glGetString.
  virtual const GLubyte*
  getString (GLenum name) = 0;

  /// See documentation of glGetUniformLocation.
  virtual GLint
  getUniformLocation (GLuint program, const GLchar* name) = 0;

  /// See documentation of glLinkProgram.
  virtual void
  linkProgram (GLuint program) = 0;

  /// See documentation of glShaderSource.
  virtual void
  shaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = 0;

  /// See documentation of glUniformMatrix4fv.
  virtual void
  uniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;

  /// See documentation of glUseProgram.
  virtual void
  useProgram (GLuint program) = 0;

  /// See documentation of glVertexAttribPointer.
  virtual void
  vertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) = 0;

  /// See documentation of glViewport.
  virtual void
  viewport (GLint x, GLint y, GLsizei width, GLsizei height) = 0;

};

#endif//OPENGL_CONTEXT_HPP
