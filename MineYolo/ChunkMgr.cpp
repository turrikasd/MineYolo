#include "ChunkMgr.h"


ChunkMgr::ChunkMgr()
{
}

ChunkMgr::~ChunkMgr()
{
}

void ChunkMgr::GenerateChunk(int x, int z)
{
	m_chunks.push_back(new Chunk(x, z));
}

void ChunkMgr::Render()
{
	for (auto iter : m_chunks)
	{
		if (iter->isEnabled != NULL)
		{
			iter->Render();
		}
	}
}