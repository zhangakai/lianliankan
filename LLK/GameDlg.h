#pragma once
#include "GameControl.h"
#include "stdafx.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "LLKDlg.h"
#include "GameLogic.h"
#include "afxcmn.h"
#include <mmsystem.h> 
#pragma comment (lib, "winmm.lib")
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();
	void InitBackGround(); //初始化窗口背景
	void UpdateWindow();//更新界面
	virtual BOOL OnInitDialog();//窗口初始化函数
	afx_msg void OnPaint();//WM_PAINT 消息函数
	afx_msg void OnBnClickedBtnstart();//开始按钮
	void UpdateMap(void);  //更新游戏地图
	void InitElement(void);//初始化元素图片与 DC
	bool m_bplaying;
	bool m_bPause;
	int Play;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcMem; //内存 DC
	CDC m_dcBG; //背景 DC
	CDC m_dcElement;//  元素内存 DC
	CDC m_dcMask;//  掩码内存 DC
	CPoint m_ptGameTop;//游戏区起始点（游戏第一张图片的顶点坐标,坐标相对于窗口客户区）
	CSize m_sizeElem;//  元素图片的大小
	CSize size;	
	CRect m_rtGameRect;
	CString str[3];
	bool m_bFirstPoint;
	bool m_Play;
	void DrawTipFrame(int nRow, int nCol);// 游戏区域大小(该区域为游戏更新区域大小，考虑到后面画的线，可能会超出图片区域一定范围)
	CGameControl m_GameC;// 游戏控制类
		DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipLine(Vertex asvPath[4], int nVexnum);
	afx_msg void OnBnClickedButHelp();
	afx_msg void OnBnClickedBtnReset();
	CProgressCtrl m_Progress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void JudgeWin();
	afx_msg void OnBnClickedBtnstop();
	void PauseMap();
	afx_msg void OnBnClickedIntroduce();
	afx_msg void OnBnClickedBtnmusic();
};
