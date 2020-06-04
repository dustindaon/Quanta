#pragma once
#include "Command.h"
#include "RenderingManager.h"

class InputHandler	
{
public:
	void Initialize(shared_ptr<GameObject> cursorSprite);

	vector<shared_ptr<Command>> HandleInput(float deltaTime);
	static void SetMousePos(glm::vec2 newPos);
	glm::vec2 GetMousePos();
	static void SetMouseScroll(glm::vec2 newScroll);
	glm::vec2 GetMouseScroll();

	shared_ptr<Command> buttonWCmd;
	shared_ptr<Command> buttonACmd;
	shared_ptr<Command> buttonSCmd;
	shared_ptr<Command> buttonDCmd;
	shared_ptr<Command> leftClickCmd;
	shared_ptr<Command> rightClickCmd;
	shared_ptr<Command> scrollCmd;

private:
	weak_ptr<GLFWwindow> m_gameWindow;

	shared_ptr<GameObject> m_cursorObject;

	bool m_mouseLeftDown = false;
	bool m_mouseRightDown = false;

	static glm::vec2 m_mousePos;
	static glm::vec2 m_mouseOldPos;
	static glm::vec2 m_mouseScroll;

	static bool m_mouseDidMove;
	static bool m_mouseDidScroll;

	void ProcessKeys(float deltaTime);
	vector<shared_ptr<Command>> ProcessMouse();
	void HandleMouseMovement();
	shared_ptr<Command> HandleMouseLeftClick();
	shared_ptr<Command> HandleMouseRightClick();
	void UpdateCursor();
};

