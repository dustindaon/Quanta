#include <memory>
#include "ScrollCommand.h"

ScrollCommand::ScrollCommand(glm::vec2 scroll)
{
	m_scroll = scroll;
}

void ScrollCommand::Execute()
{
	shared_ptr<Transform> trans = Camera::MainCamera->GetTransform();

	float fov = Camera::MainCamera->fieldOfView;

	if (fov >= 1.0f && fov <= 45.0f)
		fov -= m_scroll.y;
	else if (fov <= 1.0f)
		fov = 1.0f;
	else if (fov >= 45.0f)
		fov = 45.0f;

	Camera::MainCamera->fieldOfView = fov;
}
