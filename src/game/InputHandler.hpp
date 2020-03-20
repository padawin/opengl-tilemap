#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <map>

enum JoystickControl {LEFT_STICK_X, LEFT_STICK_Y, RIGHT_STICK_X, RIGHT_STICK_Y, NULL_CONTROL};

enum InputType {KEYBOARD_KEY, CONTROLLER_BUTTON, CONTROLLER_STICK, NULL_TYPE};

enum InputUpdateResult {QUIT, HAS_EVENT, HAS_NO_EVENT};

class InputHandler {
	public:
	virtual ~InputHandler() {}

	/**
	 * Method used to process the events poll.
	 */
	InputUpdateResult update();

	/**
	 * Returns true if the provided key (from the keyboard) is pressed, false
	 * otherwise
	 */
	virtual bool isKeyPressed(const int key) = 0;
};

#endif
