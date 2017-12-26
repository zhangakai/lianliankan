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
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();
	void InitBackGround(); //��ʼ�����ڱ���
	void UpdateWindow();//���½���
	virtual BOOL OnInitDialog();//���ڳ�ʼ������
	afx_msg void OnPaint();//WM_PAINT ��Ϣ����
	afx_msg void OnBnClickedBtnstart();//��ʼ��ť
	void UpdateMap(void);  //������Ϸ��ͼ
	void InitElement(void);//��ʼ��Ԫ��ͼƬ�� DC
	bool m_bplaying;
	bool m_bPause;
	int Play;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CDC m_dcMem; //�ڴ� DC
	CDC m_dcBG; //���� DC
	CDC m_dcElement;//  Ԫ���ڴ� DC
	CDC m_dcMask;//  �����ڴ� DC
	CPoint m_ptGameTop;//��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ�������,��������ڴ��ڿͻ�����
	CSize m_sizeElem;//  Ԫ��ͼƬ�Ĵ�С
	CSize size;	
	CRect m_rtGameRect;
	CString str[3];
	bool m_bFirstPoint;
	bool m_Play;
	void DrawTipFrame(int nRow, int nCol);// ��Ϸ�����С(������Ϊ��Ϸ���������С�����ǵ����滭���ߣ����ܻᳬ��ͼƬ����һ����Χ)
	CGameControl m_GameC;// ��Ϸ������
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
