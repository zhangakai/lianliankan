#include "stdafx.h"
#include "Graph.h"


CGraph::CGraph()
{
	InitGraph();
}


CGraph::~CGraph()
{
}

void CGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		m_Vertexs[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_AdjMatrix[i][j] = false;
	}
}

void CGraph::AddVertex(int ninfo)
{
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return;
	}	
	m_Vertexs[m_nVexnum] = ninfo;
	m_nVexnum++;
}

void CGraph::AddArc(int nV1Index, int nV2Index)//��ӱ�
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertexs[nIndex];
}
