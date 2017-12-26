
#include "stdafx.h"
#include "GameDlg.h"
#include "string.h"
#include <tchar.h>

// GameDlg.cpp : ʵ���ļ�
//


// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.SetPoint(20, 50);
	m_sizeElem.SetSize(40, 40);
	m_rtGameRect.SetRect({ 0,0 }, { 800,600 });
	m_bFirstPoint = true;
	m_bplaying = false;
}


CGameDlg::~CGameDlg()
{
}

void CGameDlg::InitBackGround()
{
	CClientDC dc(this);
	HANDLE  hBmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMem.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMem.SelectObject(hBmp);

	HANDLE  hBmp2 = ::LoadImageW(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcBG.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcBG.SelectObject(hBmp2);
}

void CGameDlg::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // ��ô��ڴ�С
	this->GetClientRect(rtClient); // ��ÿͻ�����С
								   // ����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// ���ô��ڴ�С
	MoveWindow(0, 0,800 + nSpanWidth, 600 + nSpanHeight);
	// ���öԻ�����ʾ�ǣ��� windows ���������롣
	CenterWindow();
}


void CGameDlg::InitElement(void)
{
	// ��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	// ���� BMP ͼƬ��Դ
	HANDLE  hBmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcElement.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcElement.SelectObject(hBmp);
	// �������� BMP ͼƬ��Դ
	HANDLE  hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcMask.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol*m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow*m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}


void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_Progress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BtnStart, &CGameDlg::OnBnClickedBtnstart)
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_But_Help, &CGameDlg::OnBnClickedButHelp)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BtnStop, &CGameDlg::OnBnClickedBtnstop)
	ON_BN_CLICKED(IDC_INTRODUCE, &CGameDlg::OnBnClickedIntroduce)
	ON_BN_CLICKED(IDC_BtnMusic, &CGameDlg::OnBnClickedBtnmusic)
END_MESSAGE_MAP()


// CGameDlg ��Ϣ�������


BOOL CGameDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	InitElement();
	m_Play = false;
	Play = 0;
	InitBackGround();
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetConsoleTitle(L"����������������ģʽ");
	//m_Progress.SetRange(0, 3);
	//m_Progress.SetStep(-1);
	//m_Progress.SetPos(3);
	//this->SetTimer(1, 1000, NULL);
	//m_Progress.ShowWindow(false);
	//m_GameC.StartGame();
	//UpdateMap();
	//InvalidateRect(m_rtGameRect);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);			   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}




void CGameDlg::OnBnClickedBtnstart()
{
	m_Progress.SetRange(0, 300);
	m_Progress.SetStep(-1);
	m_Progress.SetPos(300);
	this->SetTimer(1, 1000, NULL);
	//m_Progress.ShowWindow(TRUE);
	m_GameC.StartGame();
	UpdateMap();
	InvalidateRect(&m_rtGameRect);
	m_bplaying = true;
	m_bPause = false;
	(CButton*)GetDlgItem(IDC_BtnStart)->EnableWindow(false);
}

void CGameDlg::UpdateMap(void)
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i<nRows; i++)
		for (int j = 0; j < nCols; j++) {
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK)
				continue;
			//��������������򣬱߱�����ͼ������Ϊ1
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH, SRCPAINT);
			//��������Ԫ�����룬�߱�����ͼ������ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
		}
}



void CGameDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//exit(0);
	CDialogEx::OnClose();
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �ж������������
	if (m_bplaying == false) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom
		|| point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nrow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int ncol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nrow > 9 || ncol > 15) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		DrawTipFrame(nrow, ncol);
		m_GameC.SetFirstPoint(nrow, ncol);
	}
	else {
		DrawTipFrame(nrow, ncol);
		m_GameC.SetSecPoint(nrow, ncol);
		Vertex avPath[4];
		int m_nVexNum=0;
		bool bSuc = m_GameC.Link(avPath, m_nVexNum);
		if (bSuc == true)
		{
			// ����ʾ��
			DrawTipLine(avPath, m_nVexNum);
			// ���µ�ͼ
			UpdateMap();
			//Invalidate(true);
			
		}
		Sleep(20000);
		InvalidateRect(&m_rtGameRect);
		/*if (m_GameC.IsWin()) {
			CString str;
			str.SetString(_T("��ϲ�����ʤ����"));
			MessageBox(str);
			m_bplaying = false;
			(CButton*)GetDlgItem(IDC_BtnStart)->EnableWindow(true);
		}*/
		
	}
	m_bFirstPoint = !m_bFirstPoint;
}



void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum){
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 1; i < nVexnum; i++)
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

void CGameDlg::OnBnClickedButHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Vertex avPath[4];
	int m_nVexNum = 0;
	Vertex m_Vertex[2];
	bool bHelp = m_GameC.Help(avPath, m_nVexNum, m_Vertex);
	if (bHelp == true) {
		DrawTipFrame(m_Vertex[0].row, m_Vertex[0].col);
		DrawTipFrame(m_Vertex[1].row, m_Vertex[1].col);
		DrawTipLine(avPath, m_nVexNum);
		Sleep(20000);
		InvalidateRect(&m_rtGameRect);//Invalidate(true);
	}
}


void CGameDlg::OnBnClickedBtnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_GameC.Reset();
	UpdateMap();
	Sleep(200);
	InvalidateRect(&m_rtGameRect);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1 && m_bplaying&&!m_bPause) {
		m_Progress.StepIt();
	}
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::JudgeWin()
{
	int bGame = m_GameC.IsWin(m_Progress.GetPos());
	if (bGame == GAME_PLAY) {
		return;
	}
	else
	{
		m_bplaying = false;
		KillTimer(1);
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGame == GAME_SUCCESS) {
			MessageBox(_T("��ϲ����ʤ��"), strTitle);
		}
		else if (bGame =GAME_LOSS)
			MessageBox(_T("���ź�ʱ�䵽��- -"), strTitle);
		this->GetDlgItem(IDC_BtnStart)->EnableWindow(TRUE);
	}
}


void CGameDlg::OnBnClickedBtnstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bplaying == false) {
		return;
	}
	if (m_bPause == false) {
		PauseMap();
		Sleep(200);
		InvalidateRect(&m_rtGameRect);
		SetDlgItemText(IDC_BtnStop, _T("������Ϸ"));
		(CButton*)GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	}
	if (m_bPause == true) {
		UpdateMap();
		Sleep(200);
		InvalidateRect(&m_rtGameRect);
		SetDlgItemText(IDC_BtnStop, _T("��ͣ��Ϸ"));
		(CButton*)GetDlgItem(IDC_BTN_RESET)->EnableWindow(true);
	}
	m_bPause = !m_bPause;
}

void CGameDlg::PauseMap()
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i<nRows; i++)
		for (int j = 0; j < nCols; j++) {
			int nElemVal;
			if (nElemVal = BLANK)
				continue;
			//��������������򣬱߱�����ͼ������Ϊ1
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH, SRCPAINT);
			//��������Ԫ�����룬�߱�����ͼ������ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
		}
}


void CGameDlg::OnBnClickedIntroduce()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WinExec("HH res\\llk.chm", SW_SHOW);
}


void CGameDlg::OnBnClickedBtnmusic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Play = !m_Play;
	int n = Play % 3;

	if (m_Play)
	{
		PlaySound((LPCTSTR)str[n], NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
		SetDlgItemText(IDC_BtnMusic, _T("��ͣ"));
		Play++;
	}
	else
	{
		PlaySound(NULL, NULL, SND_PURGE);
		SetDlgItemText(IDC_BtnMusic, _T("����"));
	}
}
