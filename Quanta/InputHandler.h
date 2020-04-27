#pragma once
#include "Command.h"
#include "RenderingManager.h"

class InputHandler
{
public:
	Command* HandleInput();
	static void SetMousePos(glm::vec2 newPos);
	glm::vec2 GetMousePos();
	static void SetMouseScroll(glm::vec2 newScroll);
	glm::vec2 GetMouseScroll();


private:
	Command* m_buttonW;
	Command* m_buttonA;
	Command* m_buttonS;
	Command* m_buttonD;

	static glm::vec2 m_mousePos;
	static glm::vec2 m_mouseOldPos;
	static glm::vec2 m_mouseScroll;

	static bool m_mouseMoved;
	static bool m_mouseScrolled;

	void ProcessKeys();
	void ProcessMouse();
};
