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
#define EXP(VAL)				(VAL*(DB_CONST*DB_CONST - VAL*VAL)/(DB_CONST*DB_CONST - 1))
#define DB_AXIS(IN, AXIS)		(DEADBAND(RAW_AXIS(IN, AXIS)))
#define EXP_AXIS(IN, AXIS)		(EXP(RAW_AXIS(IN, AXIS)))

#define GET_BUTTON(IN, BUT)		(sf::Joystick::isButtonPressed(IN, BUT))

// Controls
#define CTRL_TRANS_X            ( EXP_AXIS(0, LX))
#define CTRL_TRANS_Y            (-EXP_AXIS(0, LY))
#define CTRL_ROT                ( EXP_AXIS(0, RX))
#define CTRL_TANK_LEFT          (-EXP_AXIS(0, LY))
#define CTRL_TANK_RIGHT         (-EXP_AXIS(0, RY))

#define CTRL_GYRO_RESET         (GET_BUTTON(0, A_BUT))
#define CTRL_GYRO_ROT_CCW       (GET_BUTTON(0, LB))
#define CTRL_GYRO_ROT_CW        (GET_BUTTON(0, RB))
#define CTRL_TOGGLE_MODE        (GET_BUTTON(0, START))
#define CTRL_AUTO_MODE			(GET_BUTTON(0, B_BUT))

#define CTRL_RETRIEVE_POS       (GET_BUTTON(1, RB))
#define CTRL_INS_POS            (GET_BUTTON(1, LB))
#define CTRL_GRAB_KEY           (GET_BUTTON(1, X_BUT))
#define CTRL_MAN_SHOULDER       (DB_AXIS(1, RY))
#define CTRL_MAN_WRIST          (DB_AXIS(1, LY))

#define CTRL_INTAKE             (GET_BUTTON(1, Y_BUT))
#define CTRL_DOOR               (GET_BUTTON(1, A_BUT))
#define CTRL_SCORE              (GET_BUTTON(1, B_BUT))
