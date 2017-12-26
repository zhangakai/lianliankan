#pragma once
#include "GameLogic.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void  StartGame();
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int &nVexnum);
	int GetElement(int nRow, int nCol);//  得到某一个元素
    int  IsWin(int nTime);
	bool Help(Vertex avPath[4], int &nVexnum,Vertex m_Vertex[2]);
	void Reset();
	static const int s_nRows=10; // 游戏行数
	static const int s_nCols=16;// 游戏列数
	static const int s_nPicNum=16;  //图片数
protected:
	int **pGameMap;//游戏地图数组指针
	CGameLogic m_GameLogic;// 游戏逻辑操作对象
	Vertex m_svSelFst;
	Vertex m_svSelSec;
};

