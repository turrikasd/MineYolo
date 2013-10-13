#pragma once

#include "freeglut.h"

#include "Block.h"

class Chunk
{
public:
	Chunk(int positionX, int positionZ);
	~Chunk();

	void Update();
	void CreateMesh();
	void CreateCube(int x, int y, int z);
	void Render();

	bool isEnabled;

	static const int CHUNK_SIZE = 16;

private:
	int positionX, positionZ;
	Block*** m_pBlocks;
};

float IntegerNoise(int n);