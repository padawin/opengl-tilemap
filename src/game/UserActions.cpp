#include "UserActions.hpp"
#include <fstream>
#include <cstdlib>
#include <cstring>
using std::ifstream;


const int MAX_CHAR_COMMAND = 128;
const int MAX_CHARS_PER_LINE = 134; // 128 + 6
const char* const DELIMITER = ";";

UserActions::UserActions(std::shared_ptr<InputHandler> inputHandler) :
	m_inputHandler(inputHandler),
	m_mMappings({})
{}

void UserActions::add(std::string name, S_Command c) {
	if (!m_mMappings.count(name)) {
		std::vector<S_Command> tempCommands;
		m_mMappings[name] = tempCommands;
	}

	m_mMappings[name].push_back(c);
}

int UserActions::getActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return 0;
	}

	std::vector<S_Command> commands = m_mMappings[name];
	int ret = 0;
	for (unsigned int c = 0; c < commands.size(); c++) {
		if (commands[c].type == KEYBOARD_KEY) {
			ret = m_inputHandler->isKeyPressed(commands[c].key);
		}

		if (ret != 0) {
			break;
		}
	}

	return ret;
}

int UserActions::setActionsFromFile(const char* mappingFile) {
	// create a file-reading object
	ifstream fin;
	fin.open(mappingFile); // open a file
	if (!fin.good()) {
		fin.close();
		return NO_FILE_FOUND; // exit if file not found
	}

	// read each line of the file
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		char commandName[MAX_CHAR_COMMAND];
		char* token;
		InputType type;
		int value;

		// @TODO Check buffer overflow
		token = strtok(buf, DELIMITER);
		strncpy(commandName, token, MAX_CHAR_COMMAND - 1);

		// @TODO check missing values
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_TYPE_FOUND;
		}

		type = (InputType) atoi(token);
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_VALUE_FOUND;
		}

		value = atoi(token);
		token = strtok(0, DELIMITER);

		S_Command c;
		c.type = type;
		if (type == KEYBOARD_KEY) {
			c.key = value;
		}
		else {
			return INVALID_TYPE;
		}
		add(commandName, c);
	}

	fin.close();
	return 0;
}
