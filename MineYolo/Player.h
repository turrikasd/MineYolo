#include <freeglut.h>

class Player
{
public:
	Player();
	~Player();

	void HandleInput(unsigned char key, int x, int y);
	void Update();

private:
	GLfloat x, y, z, rotW, rotX, rotY, rotZ;
	unsigned char m_key;

public:
	GLfloat GetX() { return x; }
	GLfloat GetY() { return y; }
	GLfloat GetZ() { return z; }
	GLfloat GetRotW() { return rotW; }
	GLfloat GetRotX() { return rotX; }
	GLfloat GetRotY() { return rotY; }
	GLfloat GetRotZ() { return rotZ; }

};