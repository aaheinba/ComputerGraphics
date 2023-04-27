/// \file RealOpenGLContext.hpp
/// \brief Declaration of RealOpenGLContext and any associated global
///   functions.
/// \author Chad Hogg
/// \version A02

#ifndef REAL_OPENGL_CONTEXT_HPP
#define REAL_OPENGL_CONTEXT_HPP

#include "OpenGLContext.hpp"

/// \brief A subclass of OpenGLContext that simply passes calls directly to
///   OpenGL.
///
/// For normal applications, this is the only subclass of OpenGLContext that
///   will be needed.  All OpenGL calls should be made through an instance of
///   this class.
class RealOpenGLContext : public OpenGLContext
{
public:

  /// Constructs a RealOpenGLContext.
  RealOpenGLContext ();

  /// Destructs a RealOpenGLContext.
  virtual
  ~RealOpenGLContext ();

  /// Copy constructor deleted because you should not be copying
  ///   RealOpenGLContexts.
  RealOpenGLContext (const RealOpenGLContext&) = delete;

  /// Assignment operator deleted because you should not be assigning
  ///   RealOpenGLContexts.
  RealOpenGLContext&
  operator= (const RealOpenGLContext&) = delete;


  virtual void
  attachShader (GLuint program, GLuint shader);
  
  virtual void
  bindBuffer (GLenum target, GLuint buffer);

  virtual void
  bindVertexArray (GLuint array);

  virtual void
  bufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);

  virtual void
  clear (GLbitfield mask);

  virtual void
  clearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

  virtual void
  compileShader (GLuint shader);

  virtual GLuint
  createProgram ();

  virtual GLuint
  createShader (GLenum shaderType);

  virtual void
  cullFace (GLenum mode);

  virtual void
  deleteBuffers (GLsizei n, const GLuint* buffers);

  virtual void
  deleteProgram (GLuint program);

  virtual void
  deleteShader (GLuint shader);

  virtual void
  deleteVertexArrays (GLsizei n, const GLuint* arrays);

  virtual void
  detachShader (GLuint program, GLuint shader);

  virtual void
  drawArrays (GLenum mode, GLint first, GLsizei count);

  virtual void
  enable (GLenum cap);

  virtual void
  enableVertexAttribArray (GLuint index);

  virtual void
  frontFace (GLenum mode);

  virtual void
  genBuffers (GLsizei n, GLuint* buffers);

  virtual void
  genVertexArrays (GLsizei n, GLuint* arrays);

  virtual GLint
  getAttribLocation (GLuint program, const GLchar* name);

  virtual void
  getProgramInfoLog (GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);

  virtual void
  getProgramiv (GLuint program, GLenum pname, GLint* params);

  virtual void
  getShaderInfoLog (GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
  
  virtual void
  getShaderiv (GLuint shader, GLenum pname, GLint* params);

  virtual const GLubyte*
  getString (GLenum name);

  virtual GLint
  getUniformLocation (GLuint program, const GLchar* name);

  virtual void
  linkProgram (GLuint program);

  virtual void
  shaderSource (GLuint shader, GLsizei count, const GLchar** string, const GLint* length);

  virtual void
  uniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

  virtual void
  useProgram (GLuint program);
  
  virtual void
  vertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

  virtual void
  viewport (GLint x, GLint y, GLsizei width, GLsizei height);
};

#endif//REAL_OPENGL_CONTEXT_HPP
