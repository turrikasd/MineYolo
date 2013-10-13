#pragma once

#include "Chunk.h"
#include <vector>

class ChunkMgr
{
public:
	ChunkMgr();
	~ChunkMgr();

	void GenerateChunk(int x, int z);
	void Render();

private:
	std::vector<Chunk*> m_chunks;
};

