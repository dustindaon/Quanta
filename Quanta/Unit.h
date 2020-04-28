#pragma once
#include "GameObject.h"

#define NULL_DEST glm::vec3(-100, -100, -100)

class Unit : public GameObject
{
public:
	Unit(string name, Model model, Shader shader) : GameObject(name, model, shader) {};
	Unit();

	void Update(float deltaTime);

	virtual glm::vec3 GetDestination();
	virtual void SetDestination(glm::vec3 newDestination);

	virtual vector<glm::vec3> GetRoute();
	virtual void SetRoute(vector<glm::vec3> newRoute);

	virtual float GetMovementSpeed();
	virtual void SetMovementSpeed(float newSpeed);

	virtual float GetAttackSpeed();
	virtual void SetAttackSpeed(float newSpeed);

	virtual int GetAttackDamage();
	virtual void SetAttackDamage(int newDamage);

	virtual int GetAttackRange();
	virtual void SetAttackRange(float newRange);

	virtual int GetCost();
	virtual void SetCost(int newCost);

	virtual int GetMaxHealth();
	virtual void SetMaxHealth(int newHealth);

	virtual int GetCurrentHealth();
	virtual void SetCurrentHealth(int newHealth);

	virtual weak_ptr<Unit> GetCurrentTarget();
	virtual void SetCurrentTarget(weak_ptr<Unit> newTarget);

	virtual void TakeDamage(int damage);
	virtual void Die();
	virtual void Move(float deltaTime);

private:
	glm::vec3 m_destination = NULL_DEST;
	float m_movementSpeed = 0;
	float m_reachedDestinationMargin = 0.05;
	float m_attackSpeed = 0;
	float m_attackRange = 0;
	int m_attackDamage = 0;
	int m_cost = 0;
	int m_maxHealth = 0;
	int m_currentHealth = 0;
	weak_ptr<Unit> m_currentTarget;
	vector<glm::vec3> m_route;
	int m_currentRoutePos = 0;

	void GetNewDestination();
};

