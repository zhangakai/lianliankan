#pragma once
//图类
class CGraph
{
public:
	CGraph();
	~CGraph();
protected:
#define MAX_VERTEX_NUM 160
	typedef  int Vertexs[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	Vertexs m_Vertexs;
	AdjMatrix m_AdjMatrix;
	int m_nVexnum;//顶点数
	int m_nArcnum;//边数
protected:
	void InitGraph();
public:
	void AddVertex(int ninfo);
	void AddArc(int nV1Index, int nV2Index);
	int GetVertex(int nIndex);
	
};
