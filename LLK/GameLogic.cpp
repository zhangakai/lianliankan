#include "stdafx.h"
#include "GameLogic.h"
#include "GameException.h"
#include "GameControl.h"

CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
}


CGameLogic::~CGameLogic()
{
}

int ** CGameLogic::InitMap()
{
	// 获取地图大小和花色
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	// 开辟内存区域
	int** pGameMap = (int **)malloc(sizeof(int*)*nRows);
	if (NULL == pGameMap)
	{
		throw  CGameException("内存操作异常！\n");
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = (int*)malloc(nCols*sizeof(int));
			if (NULL == pGameMap)
			{
				throw  CGameException("内存操作异常！\n");
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}
	// 多少花色
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw  CGameException("游戏花色与游戏地图大小不匹配！");
	}
	int nRepeatNum =nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		// 重复数
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}
	// 设置种子
	srand((int)time(NULL));
	// 随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1  %  nCols] = pGameMap[nIndex2 /
			nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
	return pGameMap;
}

void CGameLogic::ReleaseMap(int** &pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}
bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	PushVertex(v1);
	// X 直连方式
	if (v1.row == v2.row)
	{
		if (LinkInRow(pGameMap, v1, v2) == true) {
			PushVertex(v2);
			return true;
		}
	}
	//Y 直连方式
	if (v1.col == v2.col)
	{
		if (LinkInCol(pGameMap, v1, v2) == true) {
			PushVertex(v2);
			return true;
		}
	}
	if (OneCornerLink(pGameMap, v1, v2) == true) {
		PushVertex(v2);
		return true;
	}
	if (TwoCornerLink(pGameMap, v1, v2) == true) {
		PushVertex(v2);
		return true;
	}

	PopVertex();

	return false;
	
}
bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2) {
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;
	//保证 nCol1 的值小于 nCol2
	if (nCol1 > nCol2)
	{
		//数据交换
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	//直通
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2) return true;
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	//直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)  return true;
		if (pGameMap[i][nCol] != BLANK) break;
	}
	return false;
}
bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	// 直角能够消子，那么顶点一定在与两个点的行和列相交的点，只有这两个点为空，
	//才有可能实现二条直线消子
		if (pGameMap[v1.row][v2.col] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col,
				v2.col))
			{
				Vertex v = { v1.row, v2.col, BLANK };
				PushVertex(v);
				return true;
			}
		}
	if (pGameMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col,
			v2.col))
		{
			Vertex v = { v2.row, v1.col, BLANK };
			PushVertex(v);
			return true;
		}
	}
	return false;
}
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	//
	for (int nCol = 0; nCol < CGameControl::s_nCols; nCol++)
	{
		// 找到一条与 Y 轴平行的连通线段
		if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, nCol))
			{
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row,
					v2.col, nCol))
				{
					// 保存节点
					Vertex vx1 = { v1.row, nCol, BLANK };
					Vertex vx2 = { v2.row, nCol, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < CGameControl::s_nRows; nRow++)
	{
		// 找到一条与 X 轴平行的连通线段
		if (pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK)
		{
			if (LineX(pGameMap, nRow, v1.col, v2.col))
			{
				if (LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow,
					v2.row, v2.col))
				{
					// 保存节点
					Vertex vx1 = { nRow, v1.col, BLANK };
					Vertex vx2 = { nRow, v2.col, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}
void CGameLogic::UpdateArc(CGraph & graph, int nrow, int ncol)
{
	int nV1Index = nrow * 16 + ncol;
	if (ncol > 0) {
		int nV2Index = nV1Index - 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);

	}
	if (ncol <16) {
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);

	}
	if (nrow > 0) {
		int nV2Index = nV1Index - 16;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);

	}
	if (nrow<10) {
		int nV2Index = nV1Index + 16;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);

	}

}
void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}
void CGameLogic::PopVertex()
{
	m_nVexNum--;
}
bool CGameLogic::IsBlank(int ** pGameMap)
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			if (pGameMap[i][j] != -1) {
				return false;
			}
		}
	}
	return true;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
void CGameLogic::ClearStack()
{
	m_nVexNum = 0;
	memset(m_avPath, -1, sizeof(Vertex) * 4);
}

void CGameLogic::Clear(int ** pGameMap, Vertex v1, Vertex v2)
{
	pGameMap[v1.row][v1.col] = -1;
	pGameMap[v2.row][v2.col] = -1;
}

bool CGameLogic::LineX(int ** pGameMap, int nRow, int nCol1, int nCol2)
{
	if (nCol1 > nCol2)
	{
		//数据交换
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	//直通
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2) return true;
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LineY(int ** pGameMap, int nRow1, int nRow2, int nCol)
{
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	//直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)  return true;
		if (pGameMap[i][nCol] != BLANK) break;
	}
	return false;
}

bool CGameLogic::SearchValidPath(int ** pGmaeMap,Vertex m_Vertex[2])
{

	Vertex v1;
	Vertex v2;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			if (pGmaeMap[i][j] ==BLANK)
				continue;
			if (i == 9 && j == 15)
				return false;
			for (int a= 0; a + i < 10; a++) {
				for (int b = 1; b <=(159 - i * 16 - j); b++) {
					int c = (j + b) % 16;
					if (pGmaeMap[i][j] == pGmaeMap[i + a][c]) {
						v1.row = i;
						v1.col = j;
						v2.col = c;
						v2.row = i + a;
						if (IsLink(pGmaeMap, v1, v2)) {
							m_Vertex[0] = v1;
							m_Vertex[1] = v2;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void CGameLogic::ResetGraph(int ** pGameMap)
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	srand((int)time(NULL));
	// 随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1  %  nCols] = pGameMap[nIndex2 /
			nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
}
