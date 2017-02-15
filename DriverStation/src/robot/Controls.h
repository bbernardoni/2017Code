#pragma once
#include <SFML/Window/Joystick.hpp>

// Control macros
#define LX						(sf::Joystick::X)
#define LY						(sf::Joystick::Y)
#define RX						(sf::Joystick::U)
#define RY						(sf::Joystick::R)
#define TG						(sf::Joystick::Z)
#define POVX					(sf::Joystick::PovX)
#define POVY					(sf::Joystick::PovY)

#define A_BUT					(0)
#define B_BUT					(1)
#define X_BUT					(2)
#define Y_BUT					(3)
#define LB						(4)
#define RB						(5)
#define BACK					(6)
#define START					(7)
#define L_CLICK					(8)
#define R_CLICK					(9)

#define RAW_AXIS(IN, AXIS)		(sf::Joystick::getAxisPosition(IN, AXIS)/100.0f)
#define DB_CONST				(0.15f)
#define DEADBAND(VAL)			((fabs(VAL) < DB_CONST)? 0.0f: VAL)
#define DB_AXIS(IN, AXIS)		(DEADBAND(RAW_AXIS(IN, AXIS)))

#define GET_BUTTON(IN, BUT)		(sf::Joystick::isButtonPressed(IN, BUT))

// Controls
#define CTRL_TRANS_X            ( DB_AXIS(0, LX))
#define CTRL_TRANS_Y            (-DB_AXIS(0, LY))
#define CTRL_ROT                ( DB_AXIS(0, RX))
#define CTRL_TANK_LEFT          (-DB_AXIS(0, LY))
#define CTRL_TANK_RIGHT         (-DB_AXIS(0, RY))

#define CTRL_GYRO_RESET         (GET_BUTTON(0, A_BUT))
#define CTRL_GYRO_ROT_CCW       (GET_BUTTON(0, LB))
#define CTRL_GYRO_ROT_CW        (GET_BUTTON(0, RB))
#define CTRL_TOGGLE_MODE        (GET_BUTTON(0, START))


