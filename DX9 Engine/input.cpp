#include "input.h"


EngineInput::EngineInput()
{
	this->isActive = 0;
}

bool EngineInput::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		this->m_keys[i] = false;
	}

	return true;
}

bool EngineInput::Cleanup()
{
	return true;
}

void EngineInput::keyDown(unsigned int key)
{
	this->m_keys[key] = true;
}

void EngineInput::keyUp(unsigned int key)
{
	this->m_keys[key] = false;
}

bool EngineInput::isKeyDown(unsigned int key)
{
	return this->m_keys[key];
}