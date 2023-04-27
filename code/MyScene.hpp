/// \file MyScene.hpp
/// \brief Declaration of MyScene class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A02

#include "Scene.hpp"

class MyScene: public Scene
{
    public:
    
    MyScene (OpenGLContext* context, ShaderProgram* shader, ShaderProgram* shaderNorm);

    MyScene (const MyScene&) = delete;
 
    void
    operator= (const MyScene&) = delete;

};
