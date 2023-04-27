/// \file Scene.cpp
/// \brief Scene class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A02

#include "Mesh.hpp"
#include <vector>
#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "RealOpenGLContext.hpp"
#include <string>
#include "Scene.hpp"
#include <utility>
#include "Transform.hpp"
#include <iterator>
#include <list>
#include "Matrix4.hpp"


Scene::Scene () {
    std::map<std::string, Mesh*> m_scene;
    std::array<LightSource, 8>* uLights;
};

Scene::~Scene (){
    for(auto it = m_scene.begin(); it != m_scene.end(); ++it){
        it->second->~Mesh();
    }
};

void
Scene::add (const std::string& meshName, Mesh* mesh){
    m_scene.insert(std::make_pair(meshName, mesh));
    if (m_scene.size() == 1)
        active = meshName;
};

void
Scene::remove (const std::string& meshName){
    if (active == meshName)
        this->activateNextMesh();
    delete m_scene.find(meshName)->second;
    m_scene.erase(meshName);
};

void
Scene::clear (){
    for(auto it = m_scene.begin(); it != m_scene.end(); ++it){
        delete it->second;
    }
    m_scene.clear();
};

void
Scene::draw (const Transform& viewMatrix, const Matrix4& projectionMatrix){
    for(auto it = m_scene.begin(); it != m_scene.end(); ++it){
        it->second->draw(viewMatrix, projectionMatrix);
    }
};

bool
Scene::hasMesh (const std::string& meshName){
    return m_scene.count(meshName);
};

Mesh*
Scene::getMesh (const std::string& meshName){
    auto it = m_scene.find(meshName);
    if(it != m_scene.end()){
        return it->second;
    }
};

  /// \brief Sets the active mesh to the mesh named "meshName".
  /// The active mesh is the one affected by transforms.
  /// \param[in] meshName The name of the mesh that should be active.
  /// \pre The scene contains a mesh with that name.
  /// \post The mesh with that name becomes the active mesh.
  void
  Scene::setActiveMesh (const std::string& meshName){
      active = meshName;
  };

  /// \brief Gets the active mesh.
  /// \pre The scene has at least one mesh.
  /// \return The active mesh.
  Mesh*
  Scene::getActiveMesh (){
    auto it = m_scene.find(active);
    if(it != m_scene.end()){
        return it->second;
    }
  }
  /// \brief Switches active meshes in the forward direction.
  /// \pre The scene has at least one mesh.
  /// \post The next mesh becomes active.  If the last mesh was active, the
  ///   first mesh becomes active.
  
  void
  Scene::activateNextMesh (){
    if (m_scene.size() < 2) 
        active = m_scene.begin()->first;
    auto it = m_scene.find(active);
    ++it;
    if(it == m_scene.end())
        active = m_scene.begin()->first;
    else
        active = it->first;
  }

  /// \brief Switches active meshes in the backward direction.
  /// \pre The scene has at least one mesh.
  /// \post The previous mesh becomes active.  If the first mesh was active,
  ///   the last mesh becomes active.
  void
  Scene::activatePreviousMesh (){
    if (m_scene.size() < 2) 
        active = m_scene.begin()->first;
    auto it = m_scene.find(active);
    if(it == m_scene.begin()){
        it = m_scene.end();
        --it;
        active = it->first; 
    }
    else
    {
        --it;
        active = it->first;
    }    

  }