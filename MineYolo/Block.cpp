#include "Block.h"

Block::Block() { m_active = false; }
Block::~Block() { }

bool Block::IsActive()
{
	return m_active;
}

void Block::SetActive(bool active)
{
	m_active = active;
}