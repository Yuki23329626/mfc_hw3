
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
	ON_COMMAND(ID_DRAW_UNDO, &CMy403410016沈濃翔View::OnDrawUndo)
	ON_COMMAND(ID_DRAW_REDO, &CMy403410016沈濃翔View::OnDrawRedo)
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
	LineWidth = 3;
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

	int i, iP = 0, iL = 0, iR = 0, iE = 0, iPL = 0, iPG = 0;
	doc = GetDocument();
	int Pnum = doc->PArray.GetSize(); // Point
	int Lnum = doc->LArray.GetSize(); // Line
	int Rnum = doc->RArray.GetSize(); // Rectangle
	int Enum = doc->EArray.GetSize(); // Ellipse
	int PLnum = doc->PLArray.GetSize(); // PolyLine
	int PGnum = doc->PGArray.GetSize(); // PolyGon
	int RecNum = doc->RecArray.GetSize();
	int count = doc->currentStep;

	for (i = 0; i < count; i++) {
		switch (doc->RecArray[i]) {
		case ID_DRAW_POINT:
			pDC->SetPixel(doc->PArray[iP].point, doc->PArray[iP].color); // Redraw Points
			iP++;
			break;
		case ID_DRAW_LINE:
			doc->LArray[iL++].draw2(*pDC);	// Redraw Line Objects
			break;
		case ID_DRAW_RECTANGLE:
			doc->RArray[iR++].draw2(*pDC);	// Redraw Rectangle Objects
			break;
		case ID_DRAW_ELLIPSE:
			doc->EArray[iE++].draw2(*pDC);	// Redraw Ellipse Objects
			break;
		case ID_DRAW_POLYLINE:
			doc->PLArray[iPL++].draw2(*pDC); // Redraw PolyLine Objects
			break;
		case ID_DRAW_POLYGON:
			doc->PGArray[iPG++].draw2(*pDC); // Redraw PolyGon Objects
			break;
		}
	}//*/
	/*
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
	//*/
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
		CArray <int, int> test;

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

// 回到某次步驟後，有新繪圖動作時，移除已有的重做
int CMy403410016沈濃翔View::RemoveRedo()
{
	// TODO: Add your implementation code here.
	doc = GetDocument();
	int i = doc->RecArray.GetSize() - 1, limit = doc->currentStep;
	while (i >= limit) {
		switch (doc->RecArray[i])
		{
		case ID_DRAW_POINT:
			doc->RecArray.RemoveAt(i, 1);
			doc->PArray.RemoveAt(doc->PArray.GetSize() - 1, 1);
			break;
		case ID_DRAW_LINE:
			doc->RecArray.RemoveAt(i, 1);
			doc->LArray.RemoveAt(doc->LArray.GetSize() - 1, 1);
			break;
		case ID_DRAW_RECTANGLE:
			doc->RecArray.RemoveAt(i, 1);
			doc->RArray.RemoveAt(doc->RArray.GetSize() - 1, 1);
			break;
		case ID_DRAW_ELLIPSE:
			doc->RecArray.RemoveAt(i, 1);
			doc->EArray.RemoveAt(doc->EArray.GetSize() - 1, 1);
			break;
		case ID_DRAW_POLYLINE:
			doc->RecArray.RemoveAt(i, 1);
			doc->PLArray.RemoveAt(doc->PLArray.GetSize() - 1, 1);
			break;
		case ID_DRAW_POLYGON:
			doc->RecArray.RemoveAt(i, 1);
			doc->PGArray.RemoveAt(doc->PGArray.GetSize() - 1, 1);
			break;
		default:
			break;
		}
		i--;
	}
	return 0;
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
		if (doc->currentStep == doc->RecArray.GetSize()) {
			doc->LArray.Add(TempLine);
			doc->RecArray.Add(ID_DRAW_LINE);
			doc->currentStep++;
		}
		else {
			//TRACE("\n\ncurrentStep = %d, size = %d\n\n", doc->currentStep, doc->RecArray.GetSize());
			RemoveRedo();
			//TRACE("\n\ncurrentStep = %d, size = %d\n\n", doc->currentStep, doc->RecArray.GetSize());
			doc->LArray.Add(TempLine);
			doc->RecArray.Add(ID_DRAW_LINE);
			doc->currentStep++;
		}
		FileUnsaved();
	}
	else  if (doc->shapenum == ID_DRAW_RECTANGLE || (this == GetCapture() && doc->shapenum == 30))
	{
		CClientDC aDC(this);
		TempRectangle.EndPnt = point;
		if (doc->shapenum == ID_DRAW_RECTANGLE)
		{
			TempRectangle.draw2(aDC);
			if (doc->currentStep == doc->RecArray.GetSize()) {
				doc->RArray.Add(TempRectangle);
				doc->RecArray.Add(ID_DRAW_RECTANGLE);
				doc->currentStep++;
			}
			else {
				RemoveRedo();
				doc->RArray.Add(TempRectangle);
				doc->RecArray.Add(ID_DRAW_RECTANGLE);
				doc->currentStep++;
			}
			FileUnsaved();
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
		if (doc->currentStep == doc->RecArray.GetSize()) {
			doc->EArray.Add(TempEllipse);
			doc->RecArray.Add(ID_DRAW_ELLIPSE);
			doc->currentStep++;
		}
		else {
			RemoveRedo();
			doc->EArray.Add(TempEllipse);
			doc->RecArray.Add(ID_DRAW_ELLIPSE);
			doc->currentStep++;
		}
		FileUnsaved();
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
		//TempPoint.draw2(aDC);

		if (doc->currentStep == doc->RecArray.GetSize()) {
			doc->PArray.Add(TempPoint);
			doc->RecArray.Add(ID_DRAW_POINT);
			doc->currentStep++;
		}
		else {
			RemoveRedo();
			doc->PArray.Add(TempPoint);
			doc->RecArray.Add(ID_DRAW_POINT);
			doc->currentStep++;
		}
		FileUnsaved();
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
		if (doc->currentStep == doc->RecArray.GetSize()) {
			doc->PLArray.Add(TempPolyLine);
			doc->RecArray.Add(ID_DRAW_POLYLINE);
			doc->currentStep++;
		}
		else {
			RemoveRedo();
			doc->PLArray.Add(TempPolyLine);
			doc->RecArray.Add(ID_DRAW_POLYLINE);
			doc->currentStep++;
		}
		FileUnsaved();

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
		if (doc->currentStep == doc->RecArray.GetSize()) {
			doc->PGArray.Add(TempPolyGon);
			doc->RecArray.Add(ID_DRAW_POLYGON);
			doc->currentStep++;
		}
		else {
			RemoveRedo();
			doc->PGArray.Add(TempPolyGon);
			doc->RecArray.Add(ID_DRAW_POLYGON);
			doc->currentStep++;
		}
		FileUnsaved();

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
	FileUnsaved();
	Invalidate();
}

int CMy403410016沈濃翔View::FileUnsaved()
{
	CString APP_NAME, newTitle;
	APP_NAME.LoadString(ID_APP_NAME);
	newTitle.Format("%s* - %s", filePath, APP_NAME);
	AfxGetApp()->m_pMainWnd->SetWindowText(newTitle);
	bSaved = FALSE;
	return 0;
}


int CMy403410016沈濃翔View::FileSaved()
{
	CString APP_NAME, newTitle;
	APP_NAME.LoadString(ID_APP_NAME);
	newTitle.Format("%s - %s", filePath, APP_NAME);
	AfxGetApp()->m_pMainWnd->SetWindowText(newTitle);
	bSaved = TRUE;
	return 0;
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
	int TempRec;
	CFileDialog Filedlgsig(TRUE, NULL, NULL,
		OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, "DPV File|*.DPV|RP Model\0"); // lpszFilter 必須以"\0"結尾

	// File Dialog 中, 是否按下確定按鈕 (IDOK: 確定; IDCANCEL: 取消)
	if (Filedlgsig.DoModal() == IDOK)
	{
		fileString = Filedlgsig.GetPathName();
		ifstream filePtr; //建立輸出檔案物件
		filePtr.open(fileString, ios::binary | ios::in); //開啟二進位檔
		int Pnum, Lnum, Anum, Enum, PLnum, PLPnum, PGnum, PGPnum, RecNum, count;
		filePtr.read((char*)&Pnum, sizeof(Pnum)); //讀取資料到緩衝區
		filePtr.read((char*)&Lnum, sizeof(Lnum)); //讀取資料到
		filePtr.read((char*)&Anum, sizeof(Anum)); //讀取資料到緩衝區
		filePtr.read((char*)&Enum, sizeof(Enum)); //讀取資料到緩衝區
		filePtr.read((char*)&PLnum, sizeof(PLnum)); //讀取資料到緩衝區
		filePtr.read((char*)&PGnum, sizeof(PGnum)); //讀取資料到緩衝區
		filePtr.read((char*)&RecNum, sizeof(RecNum)); //讀取資料到緩衝區
		filePtr.read((char*)&count, sizeof(count)); //讀取資料到緩衝區
		doc->currentStep = count;

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
		for (i = 0; i < RecNum; i++)
		{
			filePtr.read((char*)&TempRec, sizeof(TempRec)); //讀取資料到緩衝區
			doc->RecArray.Add(TempRec);
		}
		filePtr.close();
		//*/
		filePath = fileString;
		FileSaved();
		bOpenFile = TRUE;

		// What are these functions do for?
		UpdateData(0);
		Invalidate();
	}
}


void CMy403410016沈濃翔View::OnFileSave()
{
	CString fileString2;
	/*
	explicit CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL,
	LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL, DWORD dwSize = 0, BOOL bVistaStyle = TRUE );
	*/
	if (bOpenFile == FALSE) {
		CFileDialog Filedlgsig(FALSE, "DPV", NULL, OFN_OVERWRITEPROMPT, "DPV File|*.DPV|RP Model\0"); // lpszFilter 必須以"\0"結尾

		bOpenFile = TRUE;
		// File Dialog 中, 是否按下確定按鈕 (IDOK: 確定; IDCANCEL: 取消)
		if (Filedlgsig.DoModal() == IDOK)
		{
			filePath = Filedlgsig.GetPathName();
			FileSaved();
		}
	}
	else {
		TRACE("SHIT\n\n");
		FileSaved();
	}

	doc = GetDocument();
	ofstream filePtr;//建立輸出檔案物件
	filePtr.open(filePath, ios::binary | ios::out);
	//開啟二進位檔
	int Pnum = doc->PArray.GetSize();
	int Lnum = doc->LArray.GetSize();
	int Rnum = doc->RArray.GetSize();
	int Enum = doc->EArray.GetSize();
	int PLnum = doc->PLArray.GetSize();
	int PGnum = doc->PGArray.GetSize();
	int RecNum = doc->RecArray.GetSize();
	int count = doc->currentStep;
	filePtr.write((char*)&Pnum, sizeof(Pnum)); // 寫出點數
	filePtr.write((char*)&Lnum, sizeof(Lnum)); // 寫出線數
	filePtr.write((char*)&Rnum, sizeof(Rnum));
	filePtr.write((char*)&Enum, sizeof(Enum));
	filePtr.write((char*)&PLnum, sizeof(PLnum));
	filePtr.write((char*)&PGnum, sizeof(PGnum));
	filePtr.write((char*)&RecNum, sizeof(RecNum));
	filePtr.write((char*)&count, sizeof(count));

	int i, j;
	for (i = 0; i < Pnum; i++) {
		filePtr.write((char*)&doc->PArray[i], sizeof(doc->PArray[i]));
	}
	for (i = 0; i < Lnum; i++) {
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
	for (i = 0; i < RecNum; i++) {
		filePtr.write((char*)&doc->RecArray[i], sizeof(doc->RecArray[i]));
	}
	filePtr.close();
}


void CMy403410016沈濃翔View::OnFileSavecsv()
{
	CFileDialog Filedlgsig(FALSE, "csv", NULL, OFN_HIDEREADONLY, "CSV FILE|*.csv\0");
	if (Filedlgsig.DoModal() == IDOK) {
		CString strFilePath = Filedlgsig.GetPathName();
		errno_t err;
		FILE *fptr;
		if ((err = fopen_s(&fptr, strFilePath, "w")) != 0) //開啟存檔
		{
			MessageBox("File Save Error.", " Save Error", MB_ICONSTOP);
			return;
		}

		doc = GetDocument();
		int Pnum = doc->PArray.GetSize();
		fprintf(fptr, "點數,%d\n", Pnum); //字串寫入檔案
		int i, j;
		for (i = 0; i < doc->PArray.GetSize(); i++)
		{
			int CR = GetRValue(doc->PArray[i].color);
			int CG = GetGValue(doc->PArray[i].color);
			int CB = GetBValue(doc->PArray[i].color);
			fprintf(fptr, "%d,%d,%d,%d,%d\n",
				doc->PArray[i].point.x,
				doc->PArray[i].point.y,
				CR,
				CG,
				CB);
		}
		int Lnum = doc->LArray.GetSize();
		fprintf(fptr, "線數,%d\n", Lnum); //字串寫入檔案
		for (i = 0; i < Lnum; i++)
		{
			int CR = GetRValue(doc->LArray[i].color);
			int CG = GetGValue(doc->LArray[i].color);
			int CB = GetBValue(doc->LArray[i].color);
			fprintf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				doc->LArray[i].StartPnt.x,
				doc->LArray[i].StartPnt.y,
				doc->LArray[i].EndPnt.x,
				doc->LArray[i].EndPnt.y,
				doc->LArray[i].LineWidth,
				doc->LArray[i].LineType,
				CR,
				CG,
				CB);
		}

		int Rnum = doc->RArray.GetSize();
		fprintf(fptr, "矩形數,%d\n", Rnum); //字串寫入檔案
		for (i = 0; i < Rnum; i++)
		{
			int CR = GetRValue(doc->RArray[i].color);
			int CG = GetGValue(doc->RArray[i].color);
			int CB = GetBValue(doc->RArray[i].color);
			int FR = GetRValue(doc->RArray[i].fcolor);
			int FG = GetGValue(doc->RArray[i].fcolor);
			int FB = GetBValue(doc->RArray[i].fcolor);
			fprintf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				doc->RArray[i].StartPnt.x,
				doc->RArray[i].StartPnt.y,
				doc->RArray[i].EndPnt.x,
				doc->RArray[i].EndPnt.y,
				doc->RArray[i].LineWidth,
				doc->RArray[i].LineType,
				CR, CG, CB,
				doc->RArray[i].Filled,
				FR, FG, FB);
		}

		int Enum = doc->EArray.GetSize();
		fprintf(fptr, "橢圓數,%d\n", Enum); //字串寫入檔案
		for (i = 0; i < Enum; i++)
		{
			int CR = GetRValue(doc->EArray[i].color);
			int CG = GetGValue(doc->EArray[i].color);
			int CB = GetBValue(doc->EArray[i].color);
			int FR = GetRValue(doc->EArray[i].fcolor);
			int FG = GetGValue(doc->EArray[i].fcolor);
			int FB = GetBValue(doc->EArray[i].fcolor);
			fprintf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				doc->EArray[i].StartPnt.x,
				doc->EArray[i].StartPnt.y,
				doc->EArray[i].EndPnt.x,
				doc->EArray[i].EndPnt.y,
				doc->EArray[i].LineWidth,
				doc->EArray[i].LineType,
				CR, CG, CB,
				doc->EArray[i].Filled,
				FR, FG, FB);
		}

		int PLnum = doc->PLArray.GetSize();
		fprintf(fptr, "折線數,%d\n", PLnum); //字串寫入檔案
		for (i = 0; i < PLnum; i++)
		{
			int CR = GetRValue(doc->PLArray[i].color);
			int CG = GetGValue(doc->PLArray[i].color);
			int CB = GetBValue(doc->PLArray[i].color);
			fprintf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				doc->PLArray[i].StartPnt.x,
				doc->PLArray[i].StartPnt.y,
				doc->PLArray[i].EndPnt.x,
				doc->PLArray[i].EndPnt.y,
				doc->PLArray[i].LineWidth,
				doc->PLArray[i].LineType,
				CR,
				CG,
				CB);
			int PLPnum = doc->PLArray[i].PArray.GetSize();
			fprintf(fptr, "折線%d:CArray元素數, %d\n", i, PLPnum);
			for (j = 0; j < PLPnum; j++) {
				fprintf(fptr, "%d,%d\n",
					doc->PLArray[i].PArray[j].x,
					doc->PLArray[i].PArray[j].y);
			}

		}

		int PGnum = doc->PGArray.GetSize();
		fprintf(fptr, "多邊形,%d\n", PGnum); //字串寫入檔案
		for (i = 0; i < PGnum; i++)
		{
			int CR = GetRValue(doc->PGArray[i].color);
			int CG = GetGValue(doc->PGArray[i].color);
			int CB = GetBValue(doc->PGArray[i].color);
			int FR = GetRValue(doc->PGArray[i].fcolor); //TRACE("=============/nFilled RED = %d\n", FR);
			int FG = GetGValue(doc->PGArray[i].fcolor); //TRACE("Filled GREEN = %d\n", FG);
			int FB = GetBValue(doc->PGArray[i].fcolor); //TRACE("Filled BLUE = %d\n=============/n", FB);
			fprintf(fptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				doc->PGArray[i].StartPnt.x,
				doc->PGArray[i].StartPnt.y,
				doc->PGArray[i].EndPnt.x,
				doc->PGArray[i].EndPnt.y,
				doc->PGArray[i].LineWidth,
				doc->PGArray[i].LineType,
				CR, CG, CB,
				doc->PGArray[i].Filled,
				FR, FG, FB);
			int PGPnum = doc->PGArray[i].PArray.GetSize();
			fprintf(fptr, "多邊形%d:CArray元素數, %d\n", i, PGPnum);
			for (j = 0; j < PGPnum; j++) {
				fprintf(fptr, "%d,%d\n",
					doc->PGArray[i].PArray[j].x,
					doc->PGArray[i].PArray[j].y);
			}
		}

		fclose(fptr);//寫入檔案結束
		CString strWndText, APP_NAME;
		APP_NAME.LoadString(ID_APP_NAME);
		strWndText.Format("%s - %s", strFilePath, APP_NAME);
		AfxGetApp()->m_pMainWnd->SetWindowText(strWndText);
	}
}

void CMy403410016沈濃翔View::OnFileOpencsv()
{
	CString  strFilePath, filestring2;
	char gettring[600];
	const char *d = ",\n";
	errno_t err;
	FILE *fptr;
	char *ptr, *temp;
	OnFileNew();
	int Pnum, Lnum, Rnum, Enum, PLnum, PGnum;
	int CR, CG, CB;
	int FR, FG, FB;
	MyPoint TempPoint;
	MyLine TempLine;
	MyRectangle TempRectangle;
	MyEllipse TempEllipse;
	CFileDialog Filedlgsig(TRUE, "csv", NULL, OFN_OVERWRITEPROMPT, "CSV File|*.csv\0");
	if (Filedlgsig.DoModal() == IDOK)
	{
		strFilePath = Filedlgsig.GetPathName();

		if ((err = fopen_s(&fptr, strFilePath, "r")) != 0) //開啟讀檔
		{
			MessageBox("File Save Error.", " Save Error", MB_ICONSTOP);
			return;
		}
		doc = GetDocument();

		fseek(fptr, 0, SEEK_SET); // 到檔案最開頭(吧?
		fgets(gettring, 500, fptr);
		ptr = strtok_s(gettring, d, &temp);
		ptr = strtok_s(NULL, d, &temp);
		Pnum = atoi(ptr);//stof(ptr);
		int i, j;
		for (i = 0; i < Pnum; i++)
		{
			fgets(gettring, 500, fptr);
			ptr = strtok_s(gettring, d, &temp);
			TempPoint.point.x = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempPoint.point.y = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);//stof(ptr);
			TempPoint.color = RGB(CR, CG, CB);
			doc->PArray.Add(TempPoint);
		}
		fgets(gettring, 500, fptr);
		ptr = strtok_s(gettring, d, &temp);
		ptr = strtok_s(NULL, d, &temp);
		Lnum = atoi(ptr);//stof(ptr);
		for (i = 0; i < Lnum; i++)
		{
			fgets(gettring, 500, fptr);
			ptr = strtok_s(gettring, d, &temp);
			TempLine.StartPnt.x = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempLine.StartPnt.y = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempLine.EndPnt.x = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempLine.EndPnt.y = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempLine.LineWidth = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempLine.LineType = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);//stof(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);//stof(ptr);
			TempLine.color = RGB(CR, CG, CB);
			doc->LArray.Add(TempLine);
		}

		// 取得 Rectangle 個數
		fgets(gettring, 500, fptr);
		ptr = strtok_s(gettring, d, &temp);
		ptr = strtok_s(NULL, d, &temp);
		Rnum = atoi(ptr);
		for (i = 0; i < Rnum; i++)
		{
			fgets(gettring, 500, fptr);
			ptr = strtok_s(gettring, d, &temp);
			TempRectangle.StartPnt.x = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.StartPnt.y = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.EndPnt.x = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.EndPnt.y = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.LineWidth = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.LineType = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);
			TempRectangle.color = RGB(CR, CG, CB);

			ptr = strtok_s(NULL, d, &temp);
			TempRectangle.Filled = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FR = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FG = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FB = atoi(ptr);
			TempRectangle.fcolor = RGB(FR, FG, FB);
			doc->RArray.Add(TempRectangle);
		}

		// 取得 Ellipse 個數
		fgets(gettring, 500, fptr);
		ptr = strtok_s(gettring, d, &temp);
		ptr = strtok_s(NULL, d, &temp);
		Enum = atoi(ptr);
		for (i = 0; i < Enum; i++)
		{
			fgets(gettring, 500, fptr);
			ptr = strtok_s(gettring, d, &temp);
			TempEllipse.StartPnt.x = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.StartPnt.y = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.EndPnt.x = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.EndPnt.y = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.LineWidth = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.LineType = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);
			TempEllipse.color = RGB(CR, CG, CB);
			ptr = strtok_s(NULL, d, &temp);
			TempEllipse.Filled = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FR = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FG = atoi(ptr);
			ptr = strtok_s(NULL, d, &temp);
			FB = atoi(ptr);
			TempEllipse.fcolor = RGB(FR, FG, FB);
			doc->EArray.Add(TempEllipse);
		}

		fgets(gettring, 500, fptr); //第一行
		ptr = strtok_s(gettring, d, &temp); //字串"折線數"
		ptr = strtok_s(NULL, d, &temp); //折線數量
		PLnum = atoi(ptr); //PLnum = 折線數量
		for (i = 0; i < PLnum; i++)
		{
			//第二行
			fgets(gettring, 500, fptr);
			//StartPnt.x
			ptr = strtok_s(gettring, d, &temp);
			TempPolyLine.StartPnt.x = atoi(ptr);
			//StartPnt.y
			ptr = strtok_s(NULL, d, &temp);
			TempPolyLine.StartPnt.y = atoi(ptr);
			//EndPnt.x
			ptr = strtok_s(NULL, d, &temp);
			TempPolyLine.EndPnt.x = atoi(ptr);
			//EndPnt.y
			ptr = strtok_s(NULL, d, &temp);
			TempPolyLine.EndPnt.y = atoi(ptr);
			//LineWidth
			ptr = strtok_s(NULL, d, &temp);
			TempPolyLine.LineWidth = atoi(ptr);
			//LineType
			ptr = strtok_s(NULL, d, &temp);
			TempPolyLine.LineType = atoi(ptr);
			//Color RED
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);
			//Color Green
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);
			//Color Blue
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);
			//RGB(RED, GREEN, BLUE)
			TempPolyLine.color = RGB(CR, CG, CB);
			//折線結構內的CArray陣列
			fgets(gettring, 500, fptr);//新的一行
			ptr = strtok_s(gettring, d, &temp); //字串"折線i:CArray元素數
			ptr = strtok_s(NULL, d, &temp); //CArray元素數
			int PLAnum = atoi(ptr); //PLnum = CArray元素數
			for (j = 0; j < PLAnum; j++) {
				//第j行Cpoint CArray組合
				fgets(gettring, 500, fptr);
				//PArray[j].x
				ptr = strtok_s(gettring, d, &temp);
				int tempX = atoi(ptr);
				//PArray[j].y
				ptr = strtok_s(NULL, d, &temp);
				int tempY = atoi(ptr);
				TempPolyLine.PArray.Add(CPoint(tempX, tempY));
			}
			doc->PLArray.Add(TempPolyLine);
			TempPolyLine.PArray.RemoveAll();
		}

		fgets(gettring, 500, fptr); //第一行
		ptr = strtok_s(gettring, d, &temp); //字串"折線數"
		ptr = strtok_s(NULL, d, &temp); //折線數量
		PGnum = atoi(ptr); //PLnum = 折線數量
		for (i = 0; i < PGnum; i++)
		{
			//第二行
			fgets(gettring, 500, fptr);
			//StartPnt.x
			ptr = strtok_s(gettring, d, &temp);
			TempPolyGon.StartPnt.x = atoi(ptr);
			//StartPnt.y
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.StartPnt.y = atoi(ptr);
			//EndPnt.x
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.EndPnt.x = atoi(ptr);
			//EndPnt.y
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.EndPnt.y = atoi(ptr);
			//LineWidth
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.LineWidth = atoi(ptr);
			//LineType
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.LineType = atoi(ptr);
			//Color RED
			ptr = strtok_s(NULL, d, &temp);
			CR = atoi(ptr);
			//Color Green
			ptr = strtok_s(NULL, d, &temp);
			CG = atoi(ptr);
			//Color Blue
			ptr = strtok_s(NULL, d, &temp);
			CB = atoi(ptr);
			//RGB(RED, GREEN, BLUE)
			TempPolyGon.color = RGB(CR, CG, CB);
			//Filled
			ptr = strtok_s(NULL, d, &temp);
			TempPolyGon.Filled = atoi(ptr);
			//FColor RED
			ptr = strtok_s(NULL, d, &temp);
			FR = atoi(ptr);
			//FColor Green
			ptr = strtok_s(NULL, d, &temp);
			FG = atoi(ptr);
			//FColor Blue
			ptr = strtok_s(NULL, d, &temp);
			FB = atoi(ptr);
			//RGB(RED, GREEN, BLUE)
			TempPolyGon.fcolor = RGB(FR, FG, FB);
			//折線結構內的CArray陣列
			fgets(gettring, 500, fptr);//新的一行
			ptr = strtok_s(gettring, d, &temp); //字串"折線i:CArray元素數
			ptr = strtok_s(NULL, d, &temp); //CArray元素數
			int PGAnum = atoi(ptr); //PLnum = CArray元素數
			for (j = 0; j < PGAnum; j++) {
				//第j行Cpoint CArray組合
				fgets(gettring, 500, fptr);
				//PArray[j].x
				ptr = strtok_s(gettring, d, &temp);
				int tempX = atoi(ptr);
				//PArray[j].y
				ptr = strtok_s(NULL, d, &temp);
				int tempY = atoi(ptr);
				TempPolyGon.PArray.Add(CPoint(tempX, tempY));
			}
			doc->PGArray.Add(TempPolyGon);
			TempPolyGon.PArray.RemoveAll();
		}

		fclose(fptr);//寫入檔案結束
		CString strWndText, APP_NAME;
		APP_NAME.LoadString(ID_APP_NAME);
		strWndText.Format("%s - %s", strFilePath, APP_NAME);
		AfxGetApp()->m_pMainWnd->SetWindowText(strWndText);
		Invalidate();//<---做甚麼用的?
		// HWND hWnd=NULL;

	}
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

void CMy403410016沈濃翔View::OnDrawUndo()
{
	// TODO: Add your command handler code here
	if (doc->currentStep == 0) {
		AfxMessageBox("It has been the first step!", MB_ICONSTOP);
	}
	else {
		doc->currentStep--;
		FileUnsaved();
		Invalidate();
	}
}


void CMy403410016沈濃翔View::OnDrawRedo()
{
	// TODO: Add your command handler code here
	if (doc->currentStep == doc->RecArray.GetSize()) {
		AfxMessageBox("It has been the last step!", MB_ICONSTOP);
	}
	else {
		doc->currentStep++;
		FileUnsaved();
		Invalidate();
	}
}