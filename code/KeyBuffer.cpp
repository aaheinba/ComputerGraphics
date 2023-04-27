/// \file KeyBuffer.hpp
/// \brief Declaration of KeyBuffer class and any associated global functions.
/// \author Chad Hogg and Aaron Heinbaugh
/// \version A04

#include "KeyBuffer.hpp"
#include <array>
  
  
  KeyBuffer::KeyBuffer (){
      this->reset();
  };

  /// \brief Records that a key is "down".
  /// \param[in] key The key that was pressed (a GLFW_KEY_? constant).
  /// \postcondition That key is "down".
  void
  KeyBuffer::setKeyDown (int key){
      keyIsPressed[key] = true;
  };

  /// \brief Sets all keys to "up".
  /// \postcondition All keys are assumed to be "up".
  void
  KeyBuffer::reset (){
      for(int i = 0; i < GLFW_KEY_LAST + 1; ++i){
        keyIsPressed[i] = false;
      }
  };

  /// \brief Records that a key is "up".
  /// \param[in] key The key that was released (a GLFW_KEY_?) constant).
  /// \postcondition That key is "up".
  void
  KeyBuffer::setKeyUp (int key){
      keyIsPressed[key] = false;
  };

  /// \brief Checks whether or not a key "down".
  /// \parm[in] key The key that you want to know about (a GLFW_KEY_? constant).
  /// \return True if that key is "down", otherwise false.
  bool
  KeyBuffer::isKeyDown (int key) const{
      return keyIsPressed[key];
  };

