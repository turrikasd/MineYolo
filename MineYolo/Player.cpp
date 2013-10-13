#include "Player.h"

Player::Player()
{
	x = -25.0f;
	y = -15.0f;
	z = -45.0f;
	rotW = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
}

Player::~Player()
{
}

void Player::HandleInput(unsigned char key, int x, int y)
{
	m_key = key;
}

void Player::Update()
{
	switch (m_key)
	{
	case 119: // W
		z += 0.2f;
		break;

	case 115: // S
		z -= 0.2f;
		break;

	case 100: // D
		x -= 0.2f;
		break;

	case 97: // A
		x += 0.2f;
		break;

	default:
		break;
	}
}