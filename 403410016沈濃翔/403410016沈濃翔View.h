
// 403410016沈濃翔View.h : interface of the CMy403410016沈濃翔View class
//

#pragma once
#define MAX_UNDO 100

class CMy403410016沈濃翔View : public CView
{
protected: // create from serialization only
	CMy403410016沈濃翔View();
	DECLARE_DYNCREATE(CMy403410016沈濃翔View)

// Attributes
public:
	static CMy403410016沈濃翔View * GetView(); // Get view
	CMy403410016沈濃翔Doc* GetDocument() const;
	CMy403410016沈濃翔Doc* doc;
	COLORREF color;
	COLORREF Wordcolor;
	COLORREF Bcolor;
	COLORREF fcolor;
	int LineWidth;
	int LineType;
	BOOL Filled;
	BOOL bFinished;
	HCURSOR hcursor[10];
	CFont *m_newfont, *m_oldfont;
	CBitmap m_bitmap;
	CDC m_dc;
	BITMAP bitmap;
	CString BitmapFileNamePath;
	CBitmap m_bitmapA[10];
	int Animated_Counter, Sleep_value, Clock_Counter;
	bool dirflag;
	int FillHatchType;
	int Fill_Selected;// 作業
	MyPoint TempPoint;
	MyLine TempLine;
	//MyArrow TempArrow;
	MyRectangle TempRectangle;
	MyEllipse TempEllipse;
	MyPolyLine TempPolyLine;
	MyPolyGon TempPolyGon;
	BOOL bOpenFile = FALSE;
	BOOL bSaved = TRUE;
	CString filePath;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMy403410016沈濃翔View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnFileExit();
	afx_msg void OnDrawPoint();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawRectangle();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnColorOther1();
	afx_msg void OnColorOther2();
	afx_msg void OnColorManualcolor();
	afx_msg void OnColorFillcolor();
	afx_msg void OnUpdateDrawPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorOther1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorOther2(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpencsv();
	afx_msg void OnFileSave();
	afx_msg void OnFileSavecsv();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
//	afx_msg void OnSwitchSwitchchinesemenu();
	afx_msg void OnDrawPolyline();
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolyline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPolygon(CCmdUI *pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnDrawUndo();
	afx_msg void OnDrawRedo();
	int RemoveRedo();
//	int TitleUnsaved();
	int FileUnsaved();
	int FileSaved();
};

#ifndef _DEBUG  // debug version in 403410016沈濃翔View.cpp
inline CMy403410016沈濃翔Doc* CMy403410016沈濃翔View::GetDocument() const
   { return reinterpret_cast<CMy403410016沈濃翔Doc*>(m_pDocument); }
#endif

