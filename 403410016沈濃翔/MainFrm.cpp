
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "403410016沈濃翔.h"

#include "MainFrm.h"
#include "403410016沈濃翔Doc.h"
#include "403410016沈濃翔View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_SWITCH_SWITCHCHINESEMENU, &CMainFrame::OnSwitchSwitchChineseMenu)
	ON_COMMAND(ID_D_SWITCHENGLISHMENU, &CMainFrame::OnSwitchEnglishMenu)
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_DESCRIPTION,
	ID_INDICATOR_MOUSE_POSITION,
	ID_INDICATOR_DRAW,
	ID_INDICATOR_TIME,
	/*ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,*/
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	chMainMenu.LoadMenu(IDR_CH_MENU);
	enMainMenu.LoadMenu(IDR_MAINFRAME);
	popMenu = new CMenu();
	menuType = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetTimer(1, 1000, NULL); // 起用定時器
	menuType = IDR_MAINFRAME;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_DESCRIPTION, SBPS_POPOUT, 100);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_MOUSE_POSITION, SBPS_POPOUT, 100);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_DRAW, SBPS_POPOUT, 100);
	m_wndStatusBar.SetPaneInfo(4, ID_INDICATOR_TIME, SBPS_POPOUT, 300);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("無法建立工具列\n");
		return -1;      // 無法建立
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnSwitchSwitchChineseMenu()
{
	SetMenu(&chMainMenu);
	menuType = IDR_CH_MENU;
}

void CMainFrame::OnSwitchEnglishMenu()
{
	SetMenu(&enMainMenu);
	menuType = IDR_MAINFRAME;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent = 1)
	{
		SYSTEMTIME st, lt;
		GetSystemTime(&st);
		GetLocalTime(&lt);
		CString Time_str;
		Time_str.Format("%d/%d/%d %02d:%02d:%02d", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond);

		//  printf("The system time is: %02d:%02d\n", st.wHour, st.wMinute);
		//  printf(" The local time is: %02d:%02d\n", lt.wHour, lt.wMinute);
		//CTime time=CTime::GetCurrentTime();      
		//int sec=time.GetSecond();
		//int min=time.GetMinute();
		//int hour=time.GetHour();
		// Time_str = time.Format(_T("%Y/%m/%d %H:%M:%S"));
		m_wndStatusBar.SetPaneText(4, Time_str.GetBuffer(80));
	}

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMy403410016沈濃翔View *view;
	view = CMy403410016沈濃翔View::GetView();
	if (view->bFinished == FALSE) {
		return;
	}
	// TODO: Add your message handler code here
	CMenu menu;
	if (menuType == IDR_MAINFRAME) {
		menu.LoadMenu(IDR_MAINFRAME);	//載入選單資源
	}
	else if (menuType == IDR_CH_MENU) {
		menu.LoadMenu(IDR_CH_MENU);	//載入選單資源
	}

	short Ct = ::GetAsyncKeyState(VK_CONTROL);
	short Sh = ::GetAsyncKeyState(VK_LSHIFT);
	if (Ct != 0)
		popMenu = menu.GetSubMenu(2);	//取得第2個選單的指標
	else if (Sh != 0)
		popMenu = menu.GetSubMenu(1);	//取得第1個選單的指標
	else
		popMenu = menu.GetSubMenu(3);	//取得第3個選單的指標	
	popMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	//建立蹦現選單
	menu.Detach();
}
