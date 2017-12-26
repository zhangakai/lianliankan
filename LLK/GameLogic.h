#pragma once
#include "global.h"
#include "Graph.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	int **InitMap();
	void ReleaseMap(int **& pGameMap);
	int GetVexPath(Vertex avPath[4]);


	void Clear(int** pGameMap, Vertex v1, Vertex v2);
	bool LineX(int** pGameMap, int nRow,int nCol1,int nCol2);
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);


	void UpdateArc(CGraph &graph,int nV1Index, int nV2Index);
	void ClearStack();
	Vertex m_avPath[4];
	Vertex m_Vertex[2];
	int m_nVexNum;
	void PushVertex(Vertex v);
	void PopVertex();
	bool IsBlank(int** pGameMap);//  判断图中顶点是不是全为空
	bool SearchValidPath(int** pGmaeMap,Vertex m_Vertex[2]);
	void ResetGraph(int** pGameMap);

	CGraph m_graph;
};

