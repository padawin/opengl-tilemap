#ifndef __UserActions__
#define __UserActions__

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "game/InputHandler.hpp"

#define NO_FILE_FOUND 1
#define NO_TYPE_FOUND 2
#define NO_VALUE_FOUND 3
#define INVALID_TYPE 4

struct S_Command {
	InputType type = NULL_TYPE;
	int key = -1;
};

class UserActions {
	protected:
	std::shared_ptr<InputHandler> m_inputHandler;
	std::map<std::string, std::vector<S_Command>> m_mMappings;

	public:
	~UserActions() {}
	UserActions(std::shared_ptr<InputHandler> inputHandler);
	void add(std::string name, S_Command c);
	int getActionState(std::string name);
	int setActionsFromFile(const char* mappingFile);
};

#endif
