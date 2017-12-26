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
	int GetElement(int nRow, int nCol);//  �õ�ĳһ��Ԫ��
    int  IsWin(int nTime);
	bool Help(Vertex avPath[4], int &nVexnum,Vertex m_Vertex[2]);
	void Reset();
	static const int s_nRows=10; // ��Ϸ����
	static const int s_nCols=16;// ��Ϸ����
	static const int s_nPicNum=16;  //ͼƬ��
protected:
	int **pGameMap;//��Ϸ��ͼ����ָ��
	CGameLogic m_GameLogic;// ��Ϸ�߼���������
	Vertex m_svSelFst;
	Vertex m_svSelSec;
};

