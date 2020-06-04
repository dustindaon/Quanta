#pragma once
#include "Command.h"
#include "Camera.h"

class ScrollCommand :
	public Command
{
public:
	ScrollCommand(glm::vec2 scroll);
	void Execute();

private:
	glm::vec2 m_scroll;
};

