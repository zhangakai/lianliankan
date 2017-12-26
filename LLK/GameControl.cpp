#include "stdafx.h"
#include "GameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{ 
     pGameMap= m_GameLogic.InitMap();
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}
int CGameControl::GetElement(int nRow, int nCol)
{
	return pGameMap[nRow][nCol];
	//return m_Graph.GetVertex(nRow*16+ncol);
}
int CGameControl::IsWin(int nTime)
{
	if (nTime <= 0) {
		for (int i = 0; i <10; i++) {
			for (int j = 0; j < 16; j++)
				pGameMap[i][j] = BLANK;
		}
		return GAME_LOSS;

	}
	
	if (m_GameLogic.IsBlank(pGameMap) == true)
		return GAME_SUCCESS; 
	return GAME_PLAY;
}
bool CGameControl::Help(Vertex avPath[4], int & nVexnum,Vertex m_Vertex[2])
{
	if (m_GameLogic.IsBlank(pGameMap) == false) {
		bool b_Search=m_GameLogic.SearchValidPath(pGameMap, m_Vertex);
		nVexnum = m_GameLogic.GetVexPath(avPath);
		m_GameLogic.ClearStack();
		return b_Search;
	}
	return false;
}
void CGameControl::Reset()
{
	m_GameLogic.ResetGraph(pGameMap);
}
bool CGameControl::Link(Vertex avPath[4], int &nVexnum)
{
	// 判断是否同一张图片
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}
	// 判断图片是否相同
	if (pGameMap[m_svSelFst.row][m_svSelFst.col] != pGameMap[m_svSelSec.row][m_svSelSec.col])
	{
		return false;
	}
	if (m_GameLogic.IsLink(pGameMap, m_svSelFst, m_svSelSec))
	{
		// 消子
		m_GameLogic.Clear(pGameMap, m_svSelFst, m_svSelSec);
		// 返回路径顶点
		nVexnum = m_GameLogic.GetVexPath(avPath);
		m_GameLogic.ClearStack();
		//memset(avPath, -1, 4 * sizeof(Vertex));
		return true;
	}
	return false;
}

