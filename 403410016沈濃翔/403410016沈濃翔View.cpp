
// 403410016沈濃翔View.cpp : implementation of the CMy403410016沈濃翔View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "403410016沈濃翔.h"
#endif

#include "MainFrm.h"
#include "403410016沈濃翔Doc.h"
#include "403410016沈濃翔View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy403410016沈濃翔View

IMPLEMENT_DYNCREATE(CMy403410016沈濃翔View, CView)

BEGIN_MESSAGE_MAP(CMy403410016沈濃翔View, CView)
	ON_COMMAND(ID_FILE_EXIT, &CMy403410016沈濃翔View::OnFileExit)
	ON_COMMAND(ID_DRAW_POINT, &CMy403410016沈濃翔View::OnDrawPoint)
	ON_COMMAND(ID_DRAW_LINE, &CMy403410016沈濃翔View::OnDrawLine)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CMy403410016沈濃翔View::OnDrawEllipse)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CMy403410016沈濃翔View::OnDrawRectangle)
	ON_COMMAND(ID_COLOR_RED, &CMy403410016沈濃翔View::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CMy403410016沈濃翔View::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CMy403410016沈濃翔View::OnColorBlue)
	ON_COMMAND(ID_COLOR_OTHER1, &CMy403410016沈濃翔View::OnColorOther1)
	ON_COMMAND(ID_COLOR_OTHER2, &CMy403410016沈濃翔View::OnColorOther2)
	ON_COMMAND(ID_COLOR_MANUALCOLOR, &CMy403410016沈濃翔View::OnColorManualcolor)
	ON_COMMAND(ID_COLOR_FILLCOLOR, &CMy403410016沈濃翔View::OnColorFillcolor)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POINT, &CMy403410016沈濃翔View::OnUpdateDrawPoint)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CMy403410016沈濃翔View::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CMy403410016沈濃翔View::OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CMy403410016沈濃翔View::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMy403410016沈濃翔View::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMy403410016沈濃翔View::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMy403410016沈濃翔View::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_OTHER1, &CMy403410016沈濃翔View::OnUpdateColorOther1)
	ON_UPDATE_COMMAND_UI(ID_COLOR_OTHER2, &CMy403410016沈濃翔View::OnUpdateColorOther2)
	ON_COMMAND(ID_FILE_NEW, &CMy403410016沈濃翔View::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMy403410016沈濃翔View::OnFileOpen)
	ON_COMMAND(ID_FILE_OPENCSV, &CMy403410016沈濃翔View::OnFileOpencsv)
	ON_COMMAND(ID_FILE_SAVE, &CMy403410016沈濃翔View::OnFileSave)
	ON_COMMAND(ID_FILE_SAVECSV, &CMy403410016沈濃翔View::OnFileSavecsv)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_POLYLINE, &CMy403410016沈濃翔View::OnDrawPolyline)
	ON_COMMAND(ID_DRAW_POLYGON, &CMy403410016沈濃翔View::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYLINE, &CMy403410016沈濃翔View::OnUpdateDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CMy403410016沈濃翔View::OnUpdateDrawPolygon)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CMy403410016沈濃翔View construction/destruction

CMy403410016沈濃翔View::CMy403410016沈濃翔View()
{
	// Load Cursor image
	hcursor[0] = AfxGetApp()->LoadCursor(IDC_POINT);
	hcursor[1] = AfxGetApp()->LoadCursor(IDC_LINE);
	hcursor[2] = AfxGetApp()->LoadCursor(IDC_RECT);
	hcursor[3] = AfxGetApp()->LoadCursor(IDC_ELLIPSE);
	hcursor[4] = AfxGetApp()->LoadCursor(IDC_POLYLINE);
	hcursor[5] = AfxGetApp()->LoadCursor(IDC_POLYGON);

	// Default Setting
	m_newfont = new CFont();
	LineWidth = 10;
	color = RGB(255, 0, 0);
	Bcolor = RGB(255, 255, 255);
	fcolor = RGB(0, 0, 255);
	Wordcolor = RGB(255, 0, 0);
	LineType = BS_SOLID;
	Filled = 1;
	bFinished = 1;
	Fill_Selected = 0;
	m_newfont->CreateFont(480, 40, 0, 50, 10, TRUE, TRUE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, "標楷體");
}

CMy403410016沈濃翔View::~CMy403410016沈濃翔View()
{
}

BOOL CMy403410016沈濃翔View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy403410016沈濃翔View drawing

void CMy403410016沈濃翔View::OnDraw(CDC* pDC)
{
	CMy403410016沈濃翔Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i;
	doc = GetDocument();
	int Pnum = doc->PArray.GetSize(); // Point
	int Lnum = doc->LArray.GetSize(); // Line
	int Rnum = doc->RArray.GetSize(); // Rectangle
	int Enum = doc->EArray.GetSize(); // Ellipse
	int PLnum = doc->PLArray.GetSize(); // PolyLine
	int PGnum = doc->PGArray.GetSize(); // PolyGon

	for (i = 0; i < Pnum; i++)
	{
		pDC->SetPixel(doc->PArray[i].point, doc->PArray[i].color); // Redraw Points
	}
	for (i = 0; i < Rnum; i++)
	{
		doc->RArray[i].draw2(*pDC);	// Redraw Rectangle Objects
	}
	for (i = 0; i < Lnum; i++)
	{
		doc->LArray[i].draw2(*pDC);	// Redraw Line Objects
	}
	for (i = 0; i < Enum; i++)
	{
		doc->EArray[i].draw2(*pDC);	// Redraw Ellipse Objects
	}
	for (i = 0; i < PLnum; i++)
	{
		doc->PLArray[i].draw2(*pDC); // Redraw PolyLine Objects
	}
	for (i = 0; i < PGnum; i++)
	{
		doc->PGArray[i].draw2(*pDC); // Redraw PolyGon Objects
	}
}


// CMy403410016沈濃翔View diagnostics

#ifdef _DEBUG
void CMy403410016沈濃翔View::AssertValid() const
{
	CView::AssertValid();
}

void CMy403410016沈濃翔View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy403410016沈濃翔Doc* CMy403410016沈濃翔View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy403410016沈濃翔Doc)));
	return (CMy403410016沈濃翔Doc*)m_pDocument;
}
#endif //_DEBUG

// 初始化設定

void CMy403410016沈濃翔View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	doc = GetDocument();

	// Default Setting
	doc->shapenum = ID_DRAW_POINT;
	doc->Obj_Color = RGB(255, 0, 0);
	((CMainFrame *)GetParentFrame())->OnSwitchEnglishMenu();

	UINT n;
	int check;
	COLORREF *tempcolor;
	// CFont *tempFont, *tempFont2;
	// tempcolor=new COLORREF();
	check = AfxGetApp()->GetProfileInt(_T("InitData"), _T("Start Check"), 0);
	if (check == 2018)
	{
		LineWidth = AfxGetApp()->GetProfileInt(_T("InitData"), _T("system LineWidth"), 0);
		Filled = AfxGetApp()->GetProfileInt(_T("InitData"), _T("system Filled"), 0);
		LineType = AfxGetApp()->GetProfileInt(_T("InitData"), _T("system LineType"), 0);
		FillHatchType = AfxGetApp()->GetProfileInt(_T("InitData"), _T("system FillHatchType"), 0);
		//Fill_Selected=AfxGetApp()->GetProfileInt(_T("InitData"),_T("system Fill_Selected"),0);
		AfxGetApp()->GetProfileBinary(_T("InitData"), _T("system color"), (LPBYTE*)&tempcolor, &n);
		//ASSERT(n == sizeof(tempcolor);
		color = (COLORREF)*tempcolor;
		AfxGetApp()->GetProfileBinary(_T("InitData"), _T("Wordcolor"), (LPBYTE*)&tempcolor, &n);
		Wordcolor = *tempcolor;
		AfxGetApp()->GetProfileBinary(_T("InitData"), _T("Bcolor"), (LPBYTE*)&tempcolor, &n);
		Bcolor = *tempcolor;
		AfxGetApp()->GetProfileBinary(_T("InitData"), _T("fcolor"), (LPBYTE*)&tempcolor, &n);
		fcolor = *tempcolor;
		//AfxGetApp()->GetProfileBinary(_T("InitData"),_T("font"),(LPBYTE*)&tempFont, &n);
		// m_newfont=(CFont::FromHandle(*tempFont));
		// m_newfont.CreateFontA(tempFont);
		// m_newfont=(CFont)(*tempFont).ge;
	}
}

// Mouse Events
// Left button down
void CMy403410016沈濃翔View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	SetCapture();
	doc = GetDocument();
	if (doc->shapenum == ID_DRAW_LINE)
	{
		TempLine.EndPnt = TempLine.StartPnt = point;
		TempLine.color = color;
		TempLine.LineWidth = LineWidth;
		TempLine.LineType = LineType;
	}
	else if (doc->shapenum == ID_DRAW_RECTANGLE || doc->shapenum == 30)
	{
		//	doc->lArray[doc->lArray.GetSize()].StartPnt=point;
		TempRectangle.EndPnt = TempRectangle.StartPnt = point;
		TempRectangle.color = color;
		TempRectangle.fcolor = fcolor;
		TempRectangle.LineWidth = LineWidth;
		TempRectangle.LineType = LineType;
		TempRectangle.Fill_Selected = Fill_Selected;
		TempRectangle.FillHatchType = FillHatchType;
		TempRectangle.Filled = Filled;
		//	doc->lArray.Add(line);Fill_Selected
	}
	else if (doc->shapenum == ID_DRAW_ELLIPSE)
	{
		TempEllipse.EndPnt = TempEllipse.StartPnt = point;
		TempEllipse.color = color;
		TempEllipse.LineWidth = LineWidth;
		TempEllipse.LineType = LineType;
		TempEllipse.fcolor = fcolor;
		TempEllipse.Filled = Filled;
		TempEllipse.Fill_Selected = Fill_Selected;
		TempEllipse.FillHatchType = FillHatchType;
	}
	else if (doc->shapenum == ID_DRAW_POLYLINE) { // PolyLine
		bFinished = FALSE;
		TempLine.EndPnt = TempLine.StartPnt = point;
		TempLine.color = color;
		TempLine.LineWidth = LineWidth;
		TempLine.LineType = LineType;
		TempPolyLine.color = color;
		TempPolyLine.LineWidth = LineWidth;
		TempPolyLine.LineType = LineType;
		TempPolyLine.PArray.Add(TempLine.StartPnt);

		int PArrSize = TempPolyLine.PArray.GetSize();
		// TRACE("PArrSize = %d\n", PArrSize);
		if (PArrSize == 1) {
			MyLine myLine(TempPolyLine.PArray[0], TempPolyLine.PArray[0], color);
			CClientDC aDC(this);
			myLine.draw(aDC, color, fcolor, LineWidth, LineType);
		}
		else if (PArrSize > 1) {
			MyLine myLine(TempPolyLine.PArray[PArrSize - 2], TempPolyLine.PArray[PArrSize - 1], color);
			CClientDC aDC(this);
			myLine.draw(aDC, color, fcolor, LineWidth, LineType);
		}
	}
	else if (doc->shapenum == ID_DRAW_POLYGON) { // PolyGon
		bFinished = FALSE;
		TempLine.EndPnt = TempLine.StartPnt = point;
		TempLine.color = color;
		TempLine.LineWidth = LineWidth;
		TempLine.LineType = LineType;

		TempPolyGon.color = color;
		TempPolyGon.LineWidth = LineWidth;
		TempPolyGon.LineType = LineType;
		TempPolyGon.fcolor = fcolor;
		TempPolyGon.Filled = Filled;
		TempPolyGon.Fill_Selected = Fill_Selected;
		TempPolyGon.FillHatchType = FillHatchType;
		TempPolyGon.PArray.Add(TempLine.StartPnt);
	}
}

// Left button up
void CMy403410016沈濃翔View::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
	doc = GetDocument();

	CString temp;
	// int index0;
	if (doc->shapenum == ID_DRAW_LINE)
	{
		CClientDC aDC(this);
		TempLine.EndPnt = point;
		TempLine.draw2(aDC);
		doc->LArray.Add(TempLine);
	}
	else  if (doc->shapenum == ID_DRAW_RECTANGLE || (this == GetCapture() && doc->shapenum == 30))
	{
		CClientDC aDC(this);
		TempRectangle.EndPnt = point;
		if (doc->shapenum == ID_DRAW_RECTANGLE)
		{
			TempRectangle.draw2(aDC);
			doc->RArray.Add(TempRectangle);
		}
		else
			TempRectangle.drawBMP(aDC, BitmapFileNamePath, m_bitmap, m_dc);
	}
	else if (doc->shapenum == ID_DRAW_ELLIPSE)
	{
		CClientDC aDC(this);
		TempEllipse.EndPnt = point;
		// TempRectangle.draw(aDC,TempRectangle.color, TempRectangle.fcolor,TempRectangle.LineWidth,TempRectangle.Filled);
		// TempRectangle.draw(aDC,TempRectangle.color, TempRectangle.fcolor,TempRectangle.LineWidth,0);
		TempEllipse.draw2(aDC);
		doc->EArray.Add(TempEllipse);
		// AddDialog(3);
	}
	ReleaseCapture();

	if ((doc->shapenum == ID_DRAW_POLYLINE) || (doc->shapenum == ID_DRAW_POLYGON)) {
		SetCapture();
	}
}

// mouse move
void CMy403410016沈濃翔View::OnMouseMove(UINT nFlags, CPoint point)
{
	// Show mouse position on status bar
	CString currentMousePosition;
	currentMousePosition.Format("X:%4d, Y:%4d", point.x, point.y);
	((CMainFrame*)GetParentFrame())->m_wndStatusBar.SetPaneText(2, currentMousePosition);

	CView::OnMouseMove(nFlags, point);
	doc = GetDocument();
	CClientDC aDC(this);
	MyPoint temppoint;   //Carray temp point
	if (this == GetCapture() && (doc->shapenum == 0))
	{
		::SetCursor(hcursor[1]);
	}
	else if (this == GetCapture() && (doc->shapenum == ID_DRAW_POINT))
	{
		::SetCursor(hcursor[2]);
	}
	else if (this == GetCapture() && (doc->shapenum == ID_DRAW_LINE))
	{
		::SetCursor(hcursor[3]);
	}
	else if (this == GetCapture() && (doc->shapenum == ID_DRAW_POLYLINE)) {
		::SetCursor(hcursor[4]);
	}
	else if (this == GetCapture() && (doc->shapenum == ID_DRAW_POLYGON)) {
		::SetCursor(hcursor[5]);
	}


	//      if (this == GetCapture()&&(doc->shapenum==0))
	//	  {
	//	   CClientDC aDC(this);
	//	   doc->Obj_Color=color;
	//	   if(doc->P_Type==0)
	//	   aDC.SetPixel(point,doc->Obj_Color );
	//	   else
	//       aDC.Ellipse(point.x - 3, point.y - 3, point.x + 3, point.y + 3);
	//	   ////將系統參數傳給 //Carray temp point
	//	   temppoint.point=point;	   
	//	   temppoint.color=doc->Obj_Color;
	////	   temppoint.Tpye=doc->P_Type;
	//	   doc->PArray.Add(temppoint); //記錄在 CMFCTestDoc PArray 中
	//	  }


	if (this == GetCapture() && (doc->shapenum == ID_DRAW_POINT))
	{
		//  aDC.SetPixel(point, RGB(255,255,0) );  
		TempPoint.color = color;
		TempPoint.point = point;
		::SetCursor(hcursor[0]);

		aDC.SetPixel(point, color);
		doc->PArray.Add(TempPoint);
	}
	else if (this == GetCapture() && doc->shapenum == ID_DRAW_LINE)	//判斷滑鼠游標是否在正在執行的視窗中
	{
		::SetCursor(hcursor[1]);
		aDC.SetROP2(R2_NOTXORPEN);	//設定繪圖模式 R2_NOT R2_NOTXORPEN   
		TempLine.draw2(aDC);	//清除上一筆
		TempLine.EndPnt = point;	//設定新物件座標點
		TempLine.draw2(aDC);	//再畫出新形狀物件
	}
	else if (this == GetCapture() && (doc->shapenum == ID_DRAW_RECTANGLE || doc->shapenum == 30))	//判斷滑鼠游標是否在正在執行的視窗中
	{
		::SetCursor(hcursor[2]);
		CClientDC aDC(this);	//建立畫布
		aDC.SetROP2(R2_NOTXORPEN);	//設定繪圖模式 R2_NOTXORPEN   
		TempRectangle.draw2(aDC);	//畫出形狀物件
		TempRectangle.EndPnt = point;	//設定終點
		TempRectangle.draw2(aDC);	//再畫出形狀物件
	}
	else if (this == GetCapture() && doc->shapenum == ID_DRAW_ELLIPSE)	//判斷滑鼠游標是否在正在執行的視窗中
	{
		::SetCursor(hcursor[3]);
		CClientDC aDC(this);	//建立畫布
		aDC.SetROP2(R2_NOTXORPEN);	//設定繪圖模式 R2_NOTXORPEN   
		TempEllipse.draw2(aDC);	//畫出形狀物件
		TempEllipse.EndPnt = point;	//設定終點
		TempEllipse.draw2(aDC);	//再畫出形狀物件
	}
	else if (this == GetCapture() && doc->shapenum == ID_DRAW_POLYLINE)	//判斷滑鼠游標是否在正在執行的視窗中
	{
		::SetCursor(hcursor[4]);
		CClientDC aDC(this);	//建立畫布
		aDC.SetROP2(R2_NOTXORPEN);	//設定繪圖模式 R2_NOTXORPEN   
		TempLine.draw2(aDC);	//畫出形狀物件
		TempLine.EndPnt = point;	//設定終點
		TempLine.draw2(aDC);	//再畫出形狀物件
	}
	else if (this == GetCapture() && doc->shapenum == ID_DRAW_POLYGON)	//判斷滑鼠游標是否在正在執行的視窗中
	{
		::SetCursor(hcursor[5]);
		CClientDC aDC(this);	//建立畫布
		aDC.SetROP2(R2_NOTXORPEN);	//設定繪圖模式 R2_NOTXORPEN   
		TempLine.draw2(aDC);	//畫出形狀物件
		TempLine.EndPnt = point;	//設定終點
		TempLine.draw2(aDC);	//再畫出形狀物件
	}
}

// Right button down
void CMy403410016沈濃翔View::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (doc->shapenum == ID_DRAW_POLYLINE) {

	}
	else if (doc->shapenum == ID_DRAW_POLYGON) {

	}
}

// Right button up
void CMy403410016沈濃翔View::OnRButtonUp(UINT nFlags, CPoint point)
{

	CView::OnRButtonUp(nFlags, point);
	doc = GetDocument();

	if (doc->shapenum == ID_DRAW_POLYLINE) {
		if (bFinished == TRUE) { // If polyline has not start
			return;
		}

		CClientDC aDC(this);
		TempPolyLine.EndPnt = point;
		TempLine.draw2(aDC);

		TempPolyLine.PArray.Add(point);
		doc->PLArray.Add(TempPolyLine);

		TempPolyLine.PArray.RemoveAll();
		bFinished = TRUE;
	}
	else if (doc->shapenum == ID_DRAW_POLYGON) {
		if (bFinished == TRUE) { // If polygon has not start
			return;
		}

		CClientDC aDC(this);
		aDC.SetROP2(R2_NOTXORPEN); // not xor pen
		TempLine.draw2(aDC); // 清除上一次繪圖

		CClientDC pDC(this);
		TempLine.EndPnt = TempPolyGon.PArray[0];
		TempLine.draw2(pDC);

		TempPolyGon.draw2(pDC);
		doc->PGArray.Add(TempPolyGon);

		TempPolyGon.PArray.RemoveAll();
		bFinished = TRUE;
	}

	ReleaseCapture();
}


// CMy403410016沈濃翔View message handlers

// 資料清除
void CMy403410016沈濃翔View::OnFileNew()
{
	doc = GetDocument();
	doc->RemoveAll();
	doc->shapenum = ID_DRAW_POINT;
	Invalidate();
}


void CMy403410016沈濃翔View::OnFileOpen()
{
	CString fileString, fileString2;
	OnFileNew(); // Clear screen
	doc = GetDocument();
	MyPoint TempPoint;
	MyLine TempLine;
	MyRectangle TempRectangle;
	MyEllipse TempEllipse;
	MyPolyLine TempPolyLine;
	MyPolyGon TempPolyGon;
	CFileDialog Filedlgsig(TRUE, NULL, NULL,
		OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, "DPV File|*.DPV|RP Model\0"); // lpszFilter 必須以"\0"結尾
	
	// File Dialog 中, 是否按下確定按鈕 (IDOK: 確定; IDCANCEL: 取消)
	if (Filedlgsig.DoModal() == IDOK)
	{
		fileString = Filedlgsig.GetPathName();
		ifstream filePtr; //建立輸出檔案物件
		filePtr.open(fileString, ios::binary | ios::in); //開啟二進位檔
		int Pnum, Lnum, Anum, Enum, PLnum, PLPnum, PGnum, PGPnum;
		filePtr.read((char*)&Pnum, sizeof(Pnum)); //讀取資料到緩衝區
		filePtr.read((char*)&Lnum, sizeof(Lnum)); //讀取資料到
		filePtr.read((char*)&Anum, sizeof(Anum)); //讀取資料到緩衝區
		filePtr.read((char*)&Enum, sizeof(Enum)); //讀取資料到緩衝區
		filePtr.read((char*)&PLnum, sizeof(PLnum)); //讀取資料到緩衝區
		filePtr.read((char*)&PGnum, sizeof(PGnum)); //讀取資料到緩衝區
		int i, j;
		for (i = 0; i < Pnum; i++)
		{
			filePtr.read((char*)&TempPoint, sizeof(TempPoint)); //讀取資料到緩衝區
			doc->PArray.Add(TempPoint);
		}
		for (i = 0; i < Lnum; i++)
		{
			filePtr.read((char*)&TempLine, sizeof(TempLine)); // 讀取資料到緩衝區
			doc->LArray.Add(TempLine);
		}
		for (i = 0; i < Anum; i++)
		{
			filePtr.read((char*)&TempRectangle, sizeof(TempRectangle)); //讀取資料到緩衝區
			doc->RArray.Add(TempRectangle);
		}
		for (i = 0; i < Enum; i++)
		{
			filePtr.read((char*)&TempEllipse, sizeof(TempEllipse)); //讀取資料到緩衝區
			doc->EArray.Add(TempEllipse);
		}
		//*/
		for (i = 0; i < PLnum; i++)
		{
			filePtr.read((char*)&TempPolyLine.StartPnt, sizeof(TempPolyLine.StartPnt));
			filePtr.read((char*)&TempPolyLine.color, sizeof(TempPolyLine.color));
			filePtr.read((char*)&TempPolyLine.LineWidth, sizeof(TempPolyLine.LineWidth));
			filePtr.read((char*)&TempPolyLine.EndPnt, sizeof(TempPolyLine.EndPnt));
			filePtr.read((char*)&TempPolyLine.shapenum, sizeof(TempPolyLine.shapenum));
			filePtr.read((char*)&TempPolyLine.LineType, sizeof(TempPolyLine.LineType));
			filePtr.read((char*)&PLPnum, sizeof(PLPnum));
			for (j = 0; j < PLPnum; j++) {
				CPoint currentPoint;
				filePtr.read((char*)&currentPoint, sizeof(currentPoint));
				TempPolyLine.PArray.Add(currentPoint);
			}
			doc->PLArray.Add(TempPolyLine);
			TempPolyLine.PArray.RemoveAll();
		}
		for (i = 0; i < PGnum; i++)
		{
			filePtr.read((char*)&TempPolyGon.StartPnt, sizeof(TempPolyGon.StartPnt));
			filePtr.read((char*)&TempPolyGon.color, sizeof(TempPolyGon.color));
			filePtr.read((char*)&TempPolyGon.LineWidth, sizeof(TempPolyGon.LineWidth));
			filePtr.read((char*)&TempPolyGon.EndPnt, sizeof(TempPolyGon.EndPnt));
			filePtr.read((char*)&TempPolyGon.shapenum, sizeof(TempPolyGon.shapenum));
			filePtr.read((char*)&TempPolyGon.LineType, sizeof(TempPolyGon.LineType));
			filePtr.read((char*)&TempPolyGon.Filled, sizeof(TempPolyGon.Filled));
			filePtr.read((char*)&TempPolyGon.fcolor, sizeof(TempPolyGon.fcolor));
			filePtr.read((char*)&PGPnum, sizeof(PGPnum));
			for (j = 0; j < PGPnum; j++) {
				CPoint currentPoint;
				filePtr.read((char*)&currentPoint, sizeof(currentPoint));
				TempPolyGon.PArray.Add(currentPoint);
			}
			doc->PGArray.Add(TempPolyGon);
			TempPolyGon.PArray.RemoveAll();
		}
		filePtr.close();
		//*/

		CString APP_NAME;
		APP_NAME.LoadString(ID_APP_NAME);
		fileString2.Format("%s - %s", fileString, APP_NAME);
		AfxGetApp()->m_pMainWnd->SetWindowText(fileString2);

		// What are these functions do for?
		UpdateData(0);
		Invalidate();
	}
}


void CMy403410016沈濃翔View::OnFileOpencsv()
{
	// TODO: Add your command handler code here
}


void CMy403410016沈濃翔View::OnFileSave()
{
	CString fileString, fileString2;
	/*
	explicit CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL,
	LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL, DWORD dwSize = 0, BOOL bVistaStyle = TRUE );
	*/
	CFileDialog Filedlgsig(FALSE, "DPV", NULL, OFN_OVERWRITEPROMPT, "DPV File|*.DPV|RP Model\0"); // lpszFilter 必須以"\0"結尾

	// File Dialog 中, 是否按下確定按鈕 (IDOK: 確定; IDCANCEL: 取消)
	if (Filedlgsig.DoModal() == IDOK) 
	{
		fileString = Filedlgsig.GetPathName();
		doc = GetDocument();
		ofstream filePtr;//建立輸出檔案物件
		filePtr.open(fileString, ios::binary | ios::out);
		//開啟二進位檔
		int Pnum = doc->PArray.GetSize();
		int Lnum = doc->LArray.GetSize();
		int Rnum = doc->RArray.GetSize();
		int Enum = doc->EArray.GetSize();
		int PLnum = doc->PLArray.GetSize();
		int PGnum = doc->PGArray.GetSize();
		filePtr.write((char*)&Pnum, sizeof(Pnum)); // 寫出點數
		filePtr.write((char*)&Lnum, sizeof(Lnum)); // 寫出線數
		filePtr.write((char*)&Rnum, sizeof(Rnum));
		filePtr.write((char*)&Enum, sizeof(Enum));
		filePtr.write((char*)&PLnum, sizeof(PLnum));
		filePtr.write((char*)&PGnum, sizeof(PGnum));

		int i, j;
		for (i = 0; i < Pnum; i++){
			filePtr.write((char*)&doc->PArray[i], sizeof(doc->PArray[i]));
		}
		for (i = 0; i < Lnum; i++){
			filePtr.write((char*)&doc->LArray[i], sizeof(doc->LArray[i]));
		}
		for (i = 0; i < Rnum; i++) {
			filePtr.write((char*)&doc->RArray[i], sizeof(doc->RArray[i]));
		}
		for (i = 0; i < Enum; i++) {
			filePtr.write((char*)&doc->EArray[i], sizeof(doc->EArray[i]));
		}
		for (i = 0; i < PLnum; i++) {
			filePtr.write((char*)&doc->PLArray[i].StartPnt, sizeof(doc->PLArray[i].StartPnt));
			filePtr.write((char*)&doc->PLArray[i].color, sizeof(doc->PLArray[i].color));
			filePtr.write((char*)&doc->PLArray[i].LineWidth, sizeof(doc->PLArray[i].LineWidth));
			filePtr.write((char*)&doc->PLArray[i].EndPnt, sizeof(doc->PLArray[i].EndPnt));
			filePtr.write((char*)&doc->PLArray[i].shapenum, sizeof(doc->PLArray[i].shapenum));
			filePtr.write((char*)&doc->PLArray[i].LineType, sizeof(doc->PLArray[i].LineType));
			int PLPnum = doc->PLArray[i].PArray.GetSize();
			filePtr.write((char*)&PLPnum, sizeof(PLPnum));
			for (j = 0; j < PLPnum; j++) {
				CPoint currentPoint;
				currentPoint = doc->PLArray[i].PArray[j];
				filePtr.write((char*)&currentPoint, sizeof(currentPoint));
			}
		}
		for (i = 0; i < PGnum; i++) {
			filePtr.write((char*)&doc->PGArray[i].StartPnt, sizeof(doc->PGArray[i].StartPnt));
			filePtr.write((char*)&doc->PGArray[i].color, sizeof(doc->PGArray[i].color));
			filePtr.write((char*)&doc->PGArray[i].LineWidth, sizeof(doc->PGArray[i].LineWidth));
			filePtr.write((char*)&doc->PGArray[i].EndPnt, sizeof(doc->PGArray[i].EndPnt));
			filePtr.write((char*)&doc->PGArray[i].shapenum, sizeof(doc->PGArray[i].shapenum));
			filePtr.write((char*)&doc->PGArray[i].LineType, sizeof(doc->PGArray[i].LineType));
			filePtr.write((char*)&doc->PGArray[i].Filled, sizeof(doc->PGArray[i].Filled));
			filePtr.write((char*)&doc->PGArray[i].fcolor, sizeof(doc->PGArray[i].fcolor));
			int PGPnum = doc->PGArray[i].PArray.GetSize();
			filePtr.write((char*)&PGPnum, sizeof(PGPnum));
			for (j = 0; j < PGPnum; j++) {
				CPoint currentPoint;
				currentPoint = doc->PGArray[i].PArray[j];
				filePtr.write((char*)&currentPoint, sizeof(currentPoint));
			}
		}
		filePtr.close();
	}
	CString APP_NAME;
	APP_NAME.LoadString(ID_APP_NAME);
	fileString2.Format("%s - %s", fileString, APP_NAME);
	AfxGetApp()->m_pMainWnd->SetWindowText(fileString2);
}


void CMy403410016沈濃翔View::OnFileSavecsv()
{
	// TODO: Add your command handler code here
}

void CMy403410016沈濃翔View::OnFileExit()
{
	// TODO: Add your command handler code here
}


void CMy403410016沈濃翔View::OnDrawPoint()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_POINT;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnDrawLine()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_LINE;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnDrawEllipse()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_ELLIPSE;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnDrawRectangle()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_RECTANGLE;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnColorRed()
{
	doc = GetDocument();
	color = RGB(255, 0, 0);
	doc->Obj_Color = RGB(255, 0, 0);
}


void CMy403410016沈濃翔View::OnColorGreen()
{
	doc = GetDocument();
	color = RGB(0, 255, 0);
	doc->Obj_Color = RGB(0, 255, 0);
}


void CMy403410016沈濃翔View::OnColorBlue()
{
	doc = GetDocument();
	color = RGB(0, 0, 255);
	doc->Obj_Color = RGB(0, 0, 255);
}


void CMy403410016沈濃翔View::OnColorOther1()
{
	doc = GetDocument();
	color = RGB(255, 255, 0);
	doc->Obj_Color = RGB(255, 255, 0);
}


void CMy403410016沈濃翔View::OnColorOther2()
{
	doc = GetDocument();
	color = RGB(255, 0, 255);
	doc->Obj_Color = RGB(255, 0, 255);
}


void CMy403410016沈濃翔View::OnColorManualcolor()
{
	CColorDialog dlgColor(color);
	if (dlgColor.DoModal() == IDOK)
	{
		color = dlgColor.GetColor();
	}
}


void CMy403410016沈濃翔View::OnColorFillcolor()
{
	CColorDialog dlgColor(color);
	if (dlgColor.DoModal() == IDOK)
	{
		fcolor = dlgColor.GetColor();
	}
}


void CMy403410016沈濃翔View::OnUpdateDrawPoint(CCmdUI *pCmdUI)
{
	doc = GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_POINT);
	if (doc->shapenum == ID_DRAW_POINT) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "Point");
	}
}


void CMy403410016沈濃翔View::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_LINE);
	if (doc->shapenum == ID_DRAW_LINE) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "Line");
	}
}


void CMy403410016沈濃翔View::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_ELLIPSE);
	if (doc->shapenum == ID_DRAW_ELLIPSE) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "Ellipse");
	}
}


void CMy403410016沈濃翔View::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_RECTANGLE);
	if (doc->shapenum == ID_DRAW_RECTANGLE) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "Rectangle");
	}
}


void CMy403410016沈濃翔View::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->Obj_Color == RGB(255, 0, 0));
}


void CMy403410016沈濃翔View::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	doc = GetDocument();
	pCmdUI->SetCheck(doc->Obj_Color == RGB(0, 255, 0));
}


void CMy403410016沈濃翔View::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	doc = GetDocument();
	pCmdUI->SetCheck(doc->Obj_Color == RGB(0, 0, 255));
}


void CMy403410016沈濃翔View::OnUpdateColorOther1(CCmdUI *pCmdUI)
{
	doc = GetDocument();
	pCmdUI->SetCheck(doc->Obj_Color == RGB(255, 255, 0));
}


void CMy403410016沈濃翔View::OnUpdateColorOther2(CCmdUI *pCmdUI)
{
	doc = GetDocument();
	pCmdUI->SetCheck(doc->Obj_Color == RGB(255, 0, 255));
}

void CMy403410016沈濃翔View::OnDrawPolyline()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_POLYLINE;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnDrawPolygon()
{
	doc = GetDocument();
	doc->shapenum = ID_DRAW_POLYGON;
	doc->Obj_Color = color;
}


void CMy403410016沈濃翔View::OnUpdateDrawPolyline(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_POLYLINE);
	if (doc->shapenum == ID_DRAW_POLYLINE) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "PolyLine");
	}
}


void CMy403410016沈濃翔View::OnUpdateDrawPolygon(CCmdUI *pCmdUI)
{
	CMy403410016沈濃翔Doc* doc = (CMy403410016沈濃翔Doc*)GetDocument();
	pCmdUI->SetCheck(doc->shapenum == ID_DRAW_POLYGON);
	if (doc->shapenum == ID_DRAW_POLYGON) {
		((CMainFrame *)GetParentFrame())->m_wndStatusBar.SetPaneText(3, "PolyGon");
	}
}

// It's static function, uesd to get pointer of the cview from other places
CMy403410016沈濃翔View * CMy403410016沈濃翔View::GetView()
{
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	CView * pView = pFrame->GetActiveView();

	if (!pView)
		return NULL;

	// Fail if view is of wrong kind
	// (this could occur with splitter windows, or additional
	// views on a single document

	if (!pView->IsKindOf(RUNTIME_CLASS(CMy403410016沈濃翔View)))
		return NULL;

	return (CMy403410016沈濃翔View *)pView;
}