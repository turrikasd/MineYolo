#include "Chunk.h"

Chunk::Chunk(int posX, int posZ) : positionX(posX), positionZ(posZ)
{
	isEnabled = true;

	// Create blocks
	m_pBlocks = new Block**[CHUNK_SIZE];

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		m_pBlocks[i] = new Block*[CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			m_pBlocks[i][j] = new Block[CHUNK_SIZE];
		}
	}

	float height = CHUNK_SIZE / 2;

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			height = -10 * IntegerNoise(x * z);

			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				if (y < height)
					m_pBlocks[x][y][z].SetActive(true);
			}
		}
	}

}

Chunk::~Chunk()
{
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			delete [] m_pBlocks[i][j];
		}

		delete [] m_pBlocks[i];
	}

	delete [] m_pBlocks;
}

void Chunk::CreateMesh()
{
	
}

void Chunk::CreateCube(int x, int y, int z)
{
	glBegin(GL_QUADS);

	if (z == 15 || !m_pBlocks[x][y][z + 1].IsActive())
	{
		// FRONT
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}

	if (z == 0 || !m_pBlocks[x][y][z - 1].IsActive())
	{
		// BACK
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}

	if (x == 0 || !m_pBlocks[x - 1][y][z].IsActive())
	{
		// LEFT
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}

	if (x == 15 || !m_pBlocks[x + 1][y][z].IsActive())
	{
		// RIGHT
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}

	if (y == 0 || !m_pBlocks[x][y - 1][z].IsActive())
	{
		// TOP
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
	}

	if (y == 15 || !m_pBlocks[x][y + 1][z].IsActive())
	{
		// BOTTOM
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}

	glEnd();
}

float IntegerNoise(int n)
{
	n = (n >> 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((float) nn / 1073741824.0);
}

void Chunk::Render()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				// Skip Inactive blocks
				if (!m_pBlocks[x][y][z].IsActive())
					continue;

				glPushMatrix();

				glTranslatef(positionX * CHUNK_SIZE + x, y, positionZ * CHUNK_SIZE + z);
				glColor3f(0, 0.2f, 0.2f);
				CreateCube(x, y, z);

				glPopMatrix();
			}
		}
	}
}