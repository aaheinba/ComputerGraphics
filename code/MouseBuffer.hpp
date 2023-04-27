/// \file MouseBuffer.hpp
/// \brief Declaration of MouseBuffer class and any associated global functions.
/// \author Chad Hogg
/// \version A06

#ifndef MOUSE_BUFFER_HPP
#define MOUSE_BUFFER_HPP

/// \brief A class that remembers the status of the mouse.
class MouseBuffer
{
 public:

  /// \brief Initializes the buffer.
  /// \post All buttons are set to up.
  /// \post The cursor is at (0,0).
  MouseBuffer ();

  /// \brief Records the status of the left mouse button.
  /// \param[in] down Whether the button is down (true) or up (false).
  /// \post The left button's status has been updated.
  void
  setLeftButton (bool down);

  /// \brief Records the status of the right mouse button.
  /// \param[in] down Whether the button is down (true) or up (false).
  /// \post The right button's status has been updated.
  void
  setRightButton (bool down);

  /// \brief Gets the status of the left mouse button.
  /// \return True if the button is down, or false if it is up.
  bool
  getLeftButton () const;

  /// \brief Gets the status of the right mouse button.
  /// \return True if the button is down, or false if it is up.
  bool
  getRightButton () const;

  /// \brief Sets the position of the mouse cursor.
  /// \param[in] x The new x-coordinate of the mouse cursor.
  /// \param[in] y The new y-coordinate of the mouse cursor.
  /// \post The cursor position has been updated.
  void
  setPosition (double x, double y);

  /// \brief Gets the X-coodinate of the cursor.
  /// \return The X-coordinate of the cursor.
  double
  getX () const;

  /// \brief Gets the Y-coordinate of the cursor.
  /// \return The Y-coordinate of the cursor.
  double
  getY () const;

 private:
  /// \brief The status of the left mouse button (true=down, false=up).
  bool m_leftButton;
  /// \brief The status of the right mouse button (true=down, false=up).
  bool m_rightButton;
  /// \brief The X-coodinate of the cursor.
  double m_xPos;
  /// \brief The Y-coordinate of the cursor.
  double m_yPos;
};


#endif//KEY_BUFFER_HPP
