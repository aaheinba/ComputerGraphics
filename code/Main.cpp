/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg, Aaron Heinbaugh
/// \version A02
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.  It
///   allows limited movement of a very simple virtual camera.


/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include "ColorMesh.hpp"
#include "NormalsMesh.hpp"

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>


// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>


/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "MyScene.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "KeyBuffer.hpp"
#include "MouseBuffer.hpp"
#include "Matrix4.hpp"



/******************************************************************/
// Local types



/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

// We use one VAO for each object we draw
/// \brief A collection of the VAOs for each of the objects we want to draw.
///
/// This will be filled in initScene, and its contents need to be deleted in
///   releaseGlResources.
Scene* g_scene; 

/// \brief The ShaderProgram that transforms and lights the primitives.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderProgram;

ShaderProgram* g_shaderProgramNorm;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

KeyBuffer* g_keyBuffer;

MouseBuffer* g_mouseBuffer;

bool firstMouse;

double lastX;
double lastY;
double fov = 50.0;
double aspectRatio = 1200.0f / 900;
int state = 0;





/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init (GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw ();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew ();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow (GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to reset.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport (GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene ();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders ();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera ();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene (double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene (GLFWwindow* window);

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.

//void
//processKeys (GLFWwindow* window, int key, int scanCode, int action,
//	     int modifiers);



void
processKeys ();

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

static void 
recordMouse(GLFWwindow* window, int button, int action, int mods);

static void 
recordMousePosition(GLFWwindow* window, double xpos, double ypos);

void 
cursor_enter_callback(GLFWwindow* window, int entered);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);






/// \brief Cleans up all resources as program exits.
void
releaseGlResources ();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError (int error, const char* description);

/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main (int argc, char* argv[])
{
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys();
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  KeyBuffer* kb = new KeyBuffer;
  g_keyBuffer = kb;
  MouseBuffer* mb = new MouseBuffer;
  g_mouseBuffer = mb;
  firstMouse = true;
  lastX = 400;
  lastY = 300;
  g_context = new RealOpenGLContext ();
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (800, 600, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 200, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys /*processKeys*/);
  glfwSetMouseButtonCallback(window, recordMouse);
  glfwSetCursorPosCallback(window, recordMousePosition);
  glfwSetFramebufferSizeCallback (window, resetViewport);
  glfwSetCursorEnterCallback(window, cursor_enter_callback);
  glfwSetScrollCallback(window, scroll_callback);
  // Specify background color
  g_context->clearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace (GL_CCW);
  g_context->cullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  aspectRatio = (double) width / height;
  g_camera->setProjectionSymmetricPerspective(fov, aspectRatio, 0.01, 40.0);
  g_context->viewport (0, 0, (double) width, height);
}

/******************************************************************/

void
initScene ()
{
  
  Scene* tri = new MyScene(g_context, g_shaderProgram, g_shaderProgramNorm);
  g_scene = tri;

}



/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderProgram = new ShaderProgram (g_context);
  g_shaderProgram->createVertexShader ("Vec3.vert");
  g_shaderProgram->createFragmentShader ("Vec3.frag");
  g_shaderProgram->link ();
/*
  g_shaderProgramNorm = new ShaderProgram (g_context);
  g_shaderProgramNorm->createVertexShader ("Vec3Norm.vert");
  g_shaderProgramNorm->createFragmentShader ("Vec3.frag");
*/
  g_shaderProgramNorm = new ShaderProgram (g_context);
  g_shaderProgramNorm->createVertexShader ("GeneralShader.vert");
  g_shaderProgramNorm->createFragmentShader ("GeneralShader.frag");
  g_shaderProgramNorm->link ();

/*
  g_shaderProgramNorm = new ShaderProgram (g_context);
  g_shaderProgramNorm->createVertexShader ("GenShaderCopy.vert");
  g_shaderProgramNorm->createFragmentShader ("Vec3.frag");

  //g_shaderProgramNorm->createFragmentShader ("Vec3.frag");
  g_shaderProgramNorm->link ();
  */
  
}

/******************************************************************/

void
initCamera ()
{ 
  float verticalFov = 38.0f;  //orginal 50
  // Near plane
  float nearZ = 0.01f; //.01
  // Far plane
  float farZ = 40.0f; //40
//original
//    g_camera = new Camera (Vector3 (0, 0, 25.0f), Vector3(0, 0, 1.0f), nearZ, farZ, aspectRatio, verticalFov); 
  
  //optimal setting for black
  //g_camera = new Camera (Vector3 (3.5, 8, 12.0f), Vector3(0, 1, 1.0f), nearZ, farZ, aspectRatio, verticalFov);
  
  //optimal setting for white
  g_camera = new Camera (Vector3 (3.5, 8, -5), Vector3(0, 1, -1.0f), nearZ, farZ, aspectRatio, verticalFov);

  g_shaderProgram->enable ();
}

/******************************************************************/

  //g_camera = new Camera (Vector3 (3.5, 8, 12.0f), Vector3(0, 1, 1.0f), nearZ, farZ, aspectRatio, verticalFov);
  
  //optimal setting for white
  //g_camera = new Camera (Vector3 (3.5, 8, -5), Vector3(0, 1, -1.0f), nearZ, farZ, aspectRatio, verticalFov);
int t = 0;
bool hold = false;
bool pausebutton = false;

void whiteCamera()
{

  g_shaderProgramNorm->setUniformVec3 ("uEyePosition", Vector3(3.5, 8, -5));
  g_camera->resetPose();
  hold = true;
}

void blackCamera()
{

  g_shaderProgramNorm->setUniformVec3 ("uEyePosition", Vector3(3.5, 8, 12.0));
  g_camera->setPosition(Vector3 (3.5, 8, 12));
  g_camera->pitch(45);
  g_camera->yaw(180);
  g_camera->pitch(-45);
  hold = true;
}



void
updateScene (double time)
{
  g_shaderProgramNorm->enable();  
  //0.03 speeed good for laptop
  //.15 lab comps
  float speed = .15;
  
   if(pausebutton == true)
  {
    return;
  }
  
  if(hold == true){
    ++t;
    //150 lab comps
    //500 good pause for laptop
    if(t == 500){
      ++state;
      t = 0;
      hold = false;
    }
    return;
  }

 
  
  
  if (state == 0)
  {
    //whiteCamera();
    g_scene->setActiveMesh("pawn4");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 3){
      ++state;
    }
  }
  if (state == 1)
  {
    g_scene->setActiveMesh("bpawn4");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 4){
      ++state; 
    }
  }
  if (state == 2)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 3)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 2)
      ++state;
  }
    if (state == 4)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2)
      ++state;
  }
    if (state == 5)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
    if (state == 6)
  {
    g_scene->setActiveMesh("bpawn5");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5){
      ++state;
    }
  }
  if (state == 7)
  {
    g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 3)
      ++state;
  }
  if (state == 8)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 1)
      ++state;
  }
  if (state == 9)
  {
    g_scene->setActiveMesh("bpawn4");
    g_scene->getActiveMesh()->moveLocal(10, Vector3(5,0,0));
    ++state;
  }
      if (state == 10)
    {
    //whiteCamera();
    g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3)
      ++state;
  }
  if (state == 11)
  {
    g_scene->setActiveMesh("knight"); 
    g_scene->getActiveMesh()->moveLocal(3, Vector3(-5,0,0));
      ++state;
  }
    if (state == 12)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2)
      ++state;
  }
      if (state == 13)
  {
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3)
      ++state;
  }
      if (state == 14)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveLocal(12, Vector3(5,0,0));

      ++state;
  }
        if (state == 15)
  {
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 2)
      ++state;
  }
  
  if(state == 16)
  {
      g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(-5,0,0));
    ++state;
  }
  if(state == 17)
  {
    g_scene->setActiveMesh("bpawn5");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3)
      ++state;
  }
    if(state == 18)
  {
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 5)
      ++state;
  }
  if (state == 19)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 20)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      ++state;
  }
    if (state == 21)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2)
      ++state;
  }
    if (state == 22)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 23)
  {
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveRight(speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
        if (state == 24)
  {
    g_scene->setActiveMesh("bqueen");
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    g_scene->getActiveMesh()->moveBack(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      ++state;
  }
if (state == 25)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 26)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 2)
      ++state;
  }
    if (state == 27)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 5)
      ++state;
  }
    if (state == 28)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 29)
  {
    g_scene->setActiveMesh("bpawn6");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      ++state;
  }
        if (state == 30)
  {
    g_scene->setActiveMesh("bishop2");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 1)
      ++state;
  }
          if (state == 31)
  {
    g_scene->setActiveMesh("bpawn7");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 4)
      ++state;
  }
  if (state == 32)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 33)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 4)
      ++state;
  }
    if (state == 34)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
              if (state == 35)
  {
    g_scene->setActiveMesh("bpawn7");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(5,0,0));
      ++state;
  }
    
    if (state == 36)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 37)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(-5,0,0));
      ++state;
  }
      if (state == 38)
  {
    g_scene->setActiveMesh("bpawn6");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
          if (state == 39)
  {
    g_scene->setActiveMesh("bpawn6");
        g_scene->getActiveMesh()->moveLocal(4, Vector3(5,0,0));
      ++state;
  }  
      
      if(state == 40)
  {
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
  if (state == 41)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 42)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      ++state;
  }
    if (state == 43)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      ++state;
  }
    if (state == 44)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 45)
  {
    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      ++state;
  }
  if (state == 46)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 47)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 5)
      ++state;
  }
    if (state == 48)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 49)
  {
    g_scene->setActiveMesh("brook1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      ++state;
  }  
        if (state == 50)
  {
    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 5)
      ++state;
  }
      if (state == 51)
  {
    g_scene->setActiveMesh("bknight2");
      g_scene->getActiveMesh()->moveLocal(4, Vector3(-5,0,0));
      ++state;
  }    
          if (state == 52)
  {
    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6){
      ++state;  
       g_scene->getActiveMesh()->moveLocal(10, Vector3(-5,0,0));
    }
  }
            if (state == 53)
  {
    g_scene->setActiveMesh("brook1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      ++state;  
  }
              if (state == 54)
  {
    g_scene->setActiveMesh("rook");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 4)
      ++state;  
  }
                if (state == 55)
  {
    g_scene->setActiveMesh("bqueen");
    g_scene->getActiveMesh()->moveBack(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      ++state;  
  }
                  if (state == 56)
  {
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 5)
      ++state;  
  }
              if (state == 57)
  {
    g_scene->setActiveMesh("brook1");
     g_scene->getActiveMesh()->moveLocal(10, Vector3(5,0,0));
      ++state;  
  }
                  if (state == 58)
  {
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6)
      ++state;  
  }
   if (state == 59)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 60)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6)
      ++state;
  }
    if (state == 61)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 4)
      ++state;
  }
                      if (state == 62)
  {
    g_scene->setActiveMesh("bishop");
      g_scene->getActiveMesh()->moveLocal(12, Vector3(-5,0,0));

      ++state;  
  }
    
    if (state == 63)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
      if (state == 64)
  {
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      ++state;
  }
  if (state == 65)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 66)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      ++state;
  }
    if (state == 67)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
                      if (state == 68)
  {
    g_scene->setActiveMesh("queen");
      g_scene->getActiveMesh()->moveLocal(12, Vector3(-5,0,0));

      ++state;  
  }
    
    if (state == 69)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      ++state;
  }
                if (state == 70)
  {
    g_scene->setActiveMesh("rook");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      ++state;  
  }
                  if (state == 71)
  {
    g_scene->setActiveMesh("bking");
    g_scene->getActiveMesh()->pitch(1);
    if(g_scene->getActiveMesh()->getWorld().getUp().m_y <= 0)
      ++state;  
  }


/*
Camera swapining and added lights. 
All point lights are intended to be spot lights but my spot lights do not work
Also my lighting only works from one direction.
The lights illuminate the endpoint of each move and turn red if its a capture.
Point lights above king turn red when in check and go away otherwise.
*/

/*
 if (state == 0)
  {
    //whiteCamera();
    g_scene->setActiveMesh("pawn4");
    g_scene->getActiveMesh()->moveBack(speed);
    g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,3));

    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 3){
      blackCamera();
    }
  }
  if (state == 1)
  {
    g_scene->setActiveMesh("bpawn4");
    g_scene->getActiveMesh()->moveBack(-speed);
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,4));
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 4){
       whiteCamera();
    }
  }
  if (state == 2)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveUp(speed);
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(2,2,2));
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 3)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 2)
      ++state;
  }
    if (state == 4)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2)
      ++state;
  }
    if (state == 5)
  {
    g_scene->setActiveMesh("knight");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0){
      blackCamera();}
  }
  
    if (state == 6)
  {
    g_scene->setActiveMesh("bpawn5");
    g_scene->getActiveMesh()->moveBack(-speed);
    
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,5));
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5){
      whiteCamera();
    }
  }
  if (state == 7)
  {
    g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveBack(speed);
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,3));
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 3){
      blackCamera();
    }
  }
  if (state == 8)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(-speed);
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(1,2,3));
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 1){
      whiteCamera();}
  }
  if (state == 9)
  {
  g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.0,0.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.0,0.0));  
   g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,4));
  g_scene->setActiveMesh("bpawn4");
    g_scene->getActiveMesh()->moveLocal(10, Vector3(5,0,0));
    ++state;
  }
      if (state == 10)
    {
    //whiteCamera();
    g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3){
      blackCamera();}
  }
  if (state == 11)
  {
      g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.0,0.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.0,0.0));  
   g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(2,2,2));
    g_scene->setActiveMesh("knight"); 
    g_scene->getActiveMesh()->moveLocal(3, Vector3(-5,0,0));
      ++state;
  }
    if (state == 12)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2){
      whiteCamera();}
  }
      if (state == 13)
  {
          g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.0,0.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.0,0.0));  
   g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(2,2,2));
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3){
      state++;}
  }
      if (state == 14)
  {
    g_scene->setActiveMesh("bbishop2");
    g_scene->getActiveMesh()->moveLocal(12, Vector3(5,0,0));

      ++state;
  }
        if (state == 15)
  {
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 2){
      blackCamera();}
  }
  
  if(state == 16)
  {
          g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.0,0.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.0,0.0));  
   g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,4));
    g_scene->setActiveMesh("pawn5");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(-5,0,0));
    ++state;
  }
  if(state == 17)
  {
    g_scene->setActiveMesh("bpawn5");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 3){
      whiteCamera();}
  }
    if(state == 18)
  {
       g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.9,0.9));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.9,0.9));
       g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(5,2,3));

    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 5)
      blackCamera();
  }
  if (state == 19)
  {
       g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(2,2,5));

    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 20)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      ++state;
  }
    if (state == 21)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 2)
      ++state;
  }
    if (state == 22)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      whiteCamera();
  }
      if (state == 23)
  {
       g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(6,2,2));

    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveRight(speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      blackCamera();
  }
        if (state == 24)
  {
     g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,6));
    g_scene->setActiveMesh("bqueen");
    g_scene->getActiveMesh()->moveRight(-speed * .4);
    g_scene->getActiveMesh()->moveBack(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      whiteCamera();
  }
if (state == 25)
  {
     g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(5,2,2));
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 26)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 2)
      ++state;
  }
    if (state == 27)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 5)
      ++state;
  }
    if (state == 28)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      blackCamera();
  }
      if (state == 29)
  {
     g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(5,2,5));
    g_scene->setActiveMesh("bpawn6");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      whiteCamera();
  }
        if (state == 30)
  {
     g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(1,2,4));
    g_scene->setActiveMesh("bishop2");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 1)
      blackCamera();
  }
          if (state == 31)
  {
     g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(6,2,4));
    g_scene->setActiveMesh("bpawn7");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 4)
      whiteCamera();
  }
  if (state == 32)
  {
   g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.0,0.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.0,0.0));
    g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(6,2,4));
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 33)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 4)
      ++state;
  }
    if (state == 34)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
              if (state == 35)
  {
    g_scene->setActiveMesh("bpawn7");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(5,0,0));
      ++state;
  }
    
    if (state == 36)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      blackCamera();
  }
      if (state == 37)
  {
    g_scene->setActiveMesh("knight2");
    g_scene->getActiveMesh()->moveLocal(8, Vector3(-5,0,0));
      ++state;
  }
      if (state == 38)
  {
    g_scene->setActiveMesh("bpawn6");
    g_scene->getActiveMesh()->moveBack(-speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      whiteCamera();
  }
          if (state == 39)
  {
    g_scene->setActiveMesh("bpawn6");
        g_scene->getActiveMesh()->moveLocal(4, Vector3(5,0,0));
      ++state;
  }  
      
      if(state == 40)
  {
  g_shaderProgramNorm->setUniformVec3("uLights[3].position", Vector3(3,2,7));
      g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      blackCamera();
  }
  if (state == 41)
  {
       g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.9,0.9));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.9,0.9));
    g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,6));
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 42)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      ++state;
  }
    if (state == 43)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      ++state;
  }
    if (state == 44)
  {
    g_scene->setActiveMesh("bknight2");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0){
      g_shaderProgramNorm->setUniformVec3("uLights[3].position", Vector3(3,10000,7));

      whiteCamera();}
  }
      if (state == 45)
  {
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,0));

    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      ++state;
  }
  if (state == 46)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 47)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 5)
      ++state;
  }
    if (state == 48)
  {
    g_scene->setActiveMesh("king");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      blackCamera();
  }
      if (state == 49)
  {
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,7));

    g_scene->setActiveMesh("brook1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x <= 4)
      whiteCamera();
  }  
        if (state == 50)
  {
    g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,.0,.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,.0,.0));
        g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,6));

    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 5)
      ++state;
  }
      if (state == 51)
  {
    g_scene->setActiveMesh("bknight2");
      g_scene->getActiveMesh()->moveLocal(4, Vector3(-5,0,0));
      ++state;
  }    
          if (state == 52)
  {
    g_scene->setActiveMesh("rook2");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6){
      blackCamera();  
    }
  }
  if (state == 53)
  {
    g_scene->getActiveMesh()->moveLocal(10, Vector3(-5,0,0));
    ++state;
  }
    if (state == 54)
  {
    g_scene->setActiveMesh("brook1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 6)
      whiteCamera();  
  }
              if (state == 55)
  {
    g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.9,0.9));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.9,0.9));
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,0));

    g_scene->setActiveMesh("rook");
    g_scene->getActiveMesh()->moveRight(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 4)
      blackCamera();  
  }
                if (state == 56)
  {
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(3,2,5));

    g_scene->setActiveMesh("bqueen");
    g_scene->getActiveMesh()->moveBack(-speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z <= 5)
      whiteCamera();  
  }
                  if (state == 57)
  {
  g_shaderProgramNorm->setUniformVec3("uLights[3].position", Vector3(3,2,7));
        g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,.0,.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,.0,.0));
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,6));
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 5)
      ++state;  
  }
              if (state == 58)
  {
    g_scene->setActiveMesh("brook1");
     g_scene->getActiveMesh()->moveLocal(10, Vector3(5,0,0));
      ++state;  
  }
                  if (state == 59)
  {
    g_scene->setActiveMesh("bishop");
    g_scene->getActiveMesh()->moveBack(speed);
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6)
      blackCamera();  
  }
   if (state == 60)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 61)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 6)
      ++state;
  }
    if (state == 62)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 4){
      ++state;
      g_shaderProgramNorm->setUniformVec3("uLights[3].position", Vector3(3,10000,7));
  }}
                      if (state == 63)
  {
    g_scene->setActiveMesh("bishop");
      g_scene->getActiveMesh()->moveLocal(12, Vector3(-5,0,0));

      ++state;  
  }
    
    if (state == 64)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      whiteCamera();
  }
      if (state == 65)
  {
        //check update king
          g_shaderProgramNorm->setUniformVec3("uLights[3].position", Vector3(3,2,7));

        g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.9,0.9));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.9,0.9));
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(6,2,7));
    g_scene->setActiveMesh("queen");
    g_scene->getActiveMesh()->moveBack(speed * .4);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      blackCamera();
  }
  if (state == 66)
  {
    g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,.0,.0));
  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,.0,.0));
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(6,2,7));
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y >= 1)
      ++state;
  }
  if (state == 67)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveBack(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      ++state;
  }
    if (state == 68)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveRight(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_x >= 6)
      ++state;
  }
                      if (state == 69)
  {
    g_scene->setActiveMesh("queen");
      g_scene->getActiveMesh()->moveLocal(12, Vector3(-5,0,0));

      ++state;  
  }
    
    if (state == 70)
  {
    g_scene->setActiveMesh("bknight1");
    g_scene->getActiveMesh()->moveUp(-speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_y <= 0)
      whiteCamera();
  }
                if (state == 71)
  {
    g_shaderProgramNorm->setUniformVec3("uLights[2].diffuseIntensity", Vector3(0.9,0.9,0.9));
  

  g_shaderProgramNorm->setUniformVec3("uLights[2].specularIntensity", Vector3(0.9,0.9,0.9));
            g_shaderProgramNorm->setUniformVec3("uLights[2].position", Vector3(4,2,7));
    g_scene->setActiveMesh("rook");
    g_scene->getActiveMesh()->moveBack(speed);
    if(g_scene->getActiveMesh()->getWorld().getPosition().m_z >= 7)
      ++state;  
  }
                  if (state == 72)
  {
    g_scene->setActiveMesh("bking");
    g_scene->getActiveMesh()->pitch(1);
    if(g_scene->getActiveMesh()->getWorld().getUp().m_y <= 0)
      ++state;  
  }
*/
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{

  g_context->clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Transform modelView = g_camera->getViewMatrix();
  Matrix4 projectionMatrix = g_camera->getProjectionMatrix();
  g_scene->draw(modelView, projectionMatrix);
  glfwSwapBuffers (window);
  
}


/******************************************************************/
static void 
recordMouse (GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    { 
        g_mouseBuffer->setLeftButton(true);
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    { 
        g_mouseBuffer->setLeftButton(false);
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        g_mouseBuffer->setRightButton(true);
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    { 
        g_mouseBuffer->setRightButton(false);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

  std::cout << xoffset << "  :  " << yoffset << std::endl;
  if (yoffset == 1 && fov < 120)
  {
    ++fov;
    g_camera->setProjectionSymmetricPerspective(fov, aspectRatio, 0.1, 40 );
  }
  if (yoffset == -1 && fov > 1)
  {
    --fov;
    g_camera->setProjectionSymmetricPerspective(fov, aspectRatio, 0.1, 40 );
  }

}


void 
cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        // The cursor entered the content area of the window
         printf("cursor entered \n");
    }
    else
    {
        // The cursor left the content area of the window
        printf("cursor left \n");
    }
}

static void 
recordMousePosition(GLFWwindow* window, double xpos, double ypos)
{
    g_mouseBuffer->setPosition(xpos, ypos);
 
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float sensitivity = 0.1;
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity; 
    lastX = xpos;
    lastY = ypos;
  
    if (g_mouseBuffer->getRightButton() == true)
      g_camera->roll(xoffset);
    if (g_mouseBuffer->getLeftButton() == true)
    {
      g_camera->pitch(yoffset);
      g_camera->yaw(xoffset);
    }

}

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_W);
  if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_W);
  if (key == GLFW_KEY_S && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_S);
  if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_S);
  if (key == GLFW_KEY_A && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_A);
  if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_A);
  if (key == GLFW_KEY_D && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_D);
  if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_D);
  if (key == GLFW_KEY_C && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_C);
  if (key == GLFW_KEY_C && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_C);
  if (key == GLFW_KEY_F && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_F);
  if (key == GLFW_KEY_F && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_F);
  if (key == GLFW_KEY_J && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_J);
  if (key == GLFW_KEY_J && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_J);
  if (key == GLFW_KEY_L && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_L);
  if (key == GLFW_KEY_L && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_L);
  if (key == GLFW_KEY_R && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_R);
  if (key == GLFW_KEY_R && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_R);
  if (key == GLFW_KEY_I && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_I);
  if (key == GLFW_KEY_I && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_I);
  if (key == GLFW_KEY_K && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_K);
  if (key == GLFW_KEY_K && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_K);
  if (key == GLFW_KEY_N && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_N);
  if (key == GLFW_KEY_N && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_N);    
  if (key == GLFW_KEY_M && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_M);
  if (key == GLFW_KEY_M && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_M);
  if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_1);
  if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_1);    
  if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_2);
  if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_2);
  if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_3);
  if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_3);    
  if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_4);
  if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_4);    
  if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_5);
  if (key == GLFW_KEY_5 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_5);    
  if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_6);
  if (key == GLFW_KEY_6 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_6);
  if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_7);
  if (key == GLFW_KEY_7 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_7);    
  if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    g_keyBuffer->setKeyDown(GLFW_KEY_8);
  if (key == GLFW_KEY_8 && action == GLFW_RELEASE)
    g_keyBuffer->setKeyUp(GLFW_KEY_8);
  if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    g_scene->activateNextMesh();
  if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    g_scene->activatePreviousMesh();
  if (key == GLFW_KEY_O && action == GLFW_PRESS)
    g_camera->setProjectionOrthographic(-5.0, 5.0, -5.0, 5.0, -30.0, 30.0);
  if (key == GLFW_KEY_P && action == GLFW_PRESS)
    g_camera->setProjectionSymmetricPerspective(fov, aspectRatio, 0.01, 40.0);
  if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
    g_camera->setProjectionAsymmetricPerspective(-4.0, 5.0, -5.0, 4.0, -9.0, 10.0);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
    if (pausebutton == true)
      pausebutton = false;
    else  
      pausebutton = true;
  }
}


void
processKeys ()
{
  const float MOVEMENT_DELTA = 0.05f;
  if (g_keyBuffer->isKeyDown(GLFW_KEY_W))
    g_camera->moveBack(-MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_S))
    g_camera->moveBack(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_A))
    g_camera->moveRight(-MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_D))
    g_camera->moveRight(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_C))
    g_camera->moveUp(-MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_F))
    g_camera->moveUp(MOVEMENT_DELTA);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_R))
    g_camera->resetPose();
  if (g_keyBuffer->isKeyDown(GLFW_KEY_J))
    g_scene->getActiveMesh()->yaw(0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_L))
    g_scene->getActiveMesh()->yaw(-0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_I))
    g_scene->getActiveMesh()->pitch(0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_K))
    g_scene->getActiveMesh()->pitch(-0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_N))
    g_scene->getActiveMesh()->roll(0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_M))
    g_scene->getActiveMesh()->roll(-0.25);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_1))
    g_scene->getActiveMesh()->moveRight(0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_2))
    g_scene->getActiveMesh()->moveRight(-0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_3))
    g_scene->getActiveMesh()->moveUp(0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_4))
    g_scene->getActiveMesh()->moveUp(-0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_5))
    g_scene->getActiveMesh()->moveBack(0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_6))
    g_scene->getActiveMesh()->moveBack(-0.05);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_7))
    g_scene->getActiveMesh()->scaleLocal(1.01);
  if (g_keyBuffer->isKeyDown(GLFW_KEY_8))
    g_scene->getActiveMesh()->scaleLocal(0.99);
}
/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete g_scene;
  delete g_camera;
  delete g_shaderProgram;
  delete g_context;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
