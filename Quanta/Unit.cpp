#include "Unit.h"

#define NULL_DEST glm::vec3(-100, -100, -100)

Unit::Unit()
{
}

void Unit::Update(float deltaTime)
{
	Move(deltaTime);
}

void Unit::SetSprite(string spritePath)
{
	m_sprite = make_shared<Model>(spritePath, true);
}

shared_ptr<Model> Unit::GetSprite()
{
	return m_sprite;
}

glm::vec3 Unit::GetDestination()
{
	return m_destination;
}

void Unit::SetDestination(glm::vec3 newDestination)
{
	m_destination = newDestination;
}

vector<glm::vec3> Unit::GetRoute()
{
	return m_route;
}

void Unit::SetRoute(vector<glm::vec3> newRoute)
{
	m_route = newRoute;
	m_currentRoutePos = 0;
	SetDestination(m_route[0]);
}

float Unit::GetMovementSpeed()
{
	return m_movementSpeed;
}

void Unit::SetMovementSpeed(float newSpeed)
{
	m_movementSpeed = newSpeed;
}

float Unit::GetAttackSpeed()
{
	return m_attackSpeed;
}

void Unit::SetAttackSpeed(float newSpeed)
{
	m_attackSpeed = newSpeed;
}

int Unit::GetAttackDamage()
{
	return m_attackDamage;
}

void Unit::SetAttackDamage(int newDamage)
{
	m_attackDamage = newDamage;
}

int Unit::GetAttackRange()
{
	return m_attackRange;
}

void Unit::SetAttackRange(float newRange)
{
	m_attackRange = newRange;
}

int Unit::GetCost()
{
	return m_cost;
}

void Unit::SetCost(int newCost)
{
	m_cost = newCost;
}

int Unit::GetMaxHealth()
{
	return m_maxHealth;
}

void Unit::SetMaxHealth(int newHealth)
{
	m_maxHealth = newHealth;
}

int Unit::GetCurrentHealth()
{
	return m_currentHealth;
}

void Unit::SetCurrentHealth(int newHealth)
{
	m_currentHealth = newHealth;
}

weak_ptr<Unit> Unit::GetCurrentTarget()
{
	return m_currentTarget;
}

void Unit::SetCurrentTarget(weak_ptr<Unit> newTarget)
{
	m_currentTarget = newTarget;
}

void Unit::TakeDamage(int damage)
{
	m_currentHealth -= damage;

	if (m_currentHealth <= 0)
	{
		Die();
	}
	else if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

void Unit::Die()
{
}

void Unit::Move(float deltaTime)
{
	if (m_destination == NULL_DEST)
	{
		if (m_route.empty())
		{
			return;
		}

		GetNewDestination();
		return;
	}

	if (glm::length(GetTransform().GetPosition() - m_destination) <= m_reachedDestinationMargin)
	{
		//cout << "Made it to my destination! Getting a new one now" << endl;
		GetNewDestination();
	}

	glm::vec3 newPos = glm::normalize(m_destination - GetTransform().GetPosition());
	if (glm::any(glm::isnan(newPos)))
	{
		GetNewDestination();
	}
	else
	{
		newPos = (newPos * m_movementSpeed * deltaTime) + GetTransform().GetPosition();
		GetTransform().SetPosition(newPos);
	}
}

void Unit::GetNewDestination()
{
	m_currentRoutePos += 1;
	if (m_currentRoutePos >= m_route.size())
	{
		m_destination = NULL_DEST;
		return;
	}
	glm::vec3 newDest = m_route[m_currentRoutePos];

	SetDestination(newDest);
	//cout << "New Destination is: " << newDest.x << ", " << newDest.y << ", " << newDest.z << endl;
}
