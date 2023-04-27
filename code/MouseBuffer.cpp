/// \file MouseBuffer.hpp
/// \brief MouseBuffer class and any associated global functions.
/// \author Aaron Heinbaugh
/// \version A06

#include "MouseBuffer.hpp"
#include <array>

  /// \brief Initializes the buffer.
  /// \post All buttons are set to up.
  /// \post The cursor is at (0,0).
  MouseBuffer::MouseBuffer ()
  : m_leftButton(false), m_rightButton(false), m_xPos(0), m_yPos(0)
  {};

  /// \brief Records the status of the left mouse button.
  /// \param[in] down Whether the button is down (true) or up (false).
  /// \post The left button's status has been updated.
  void
  MouseBuffer::setLeftButton (bool down)
  {
      m_leftButton = down;
  }

  /// \brief Records the status of the right mouse button.
  /// \param[in] down Whether the button is down (true) or up (false).
  /// \post The right button's status has been updated.
  void
  MouseBuffer::setRightButton (bool down)
  {
      m_rightButton = down;
  }

  /// \brief Gets the status of the left mouse button.
  /// \return True if the button is down, or false if it is up.
  bool
  MouseBuffer::getLeftButton () const
  {
      return m_leftButton;
  }
  

  /// \brief Gets the status of the right mouse button.
  /// \return True if the button is down, or false if it is up.
  bool
  MouseBuffer::getRightButton () const
  {
      return m_rightButton;
  }

  /// \brief Sets the position of the mouse cursor.
  /// \param[in] x The new x-coordinate of the mouse cursor.
  /// \param[in] y The new y-coordinate of the mouse cursor.
  /// \post The cursor position has been updated.
  void
  MouseBuffer::setPosition (double x, double y)
  {
      m_xPos = x;
      m_yPos = y;
  }

  /// \brief Gets the X-coodinate of the cursor.
  /// \return The X-coordinate of the cursor.
  double
  MouseBuffer::getX () const
  {
      return m_xPos;
  }

  /// \brief Gets the Y-coordinate of the cursor.
  /// \return The Y-coordinate of the cursor.
  double
  MouseBuffer::getY () const
  {
      return m_yPos;
  }