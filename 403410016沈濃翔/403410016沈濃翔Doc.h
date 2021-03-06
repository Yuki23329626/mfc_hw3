
// 403410016沈濃翔Doc.h : interface of the CMy403410016沈濃翔Doc class
//


#pragma once

#include "BaseStruct.h"

class CMy403410016沈濃翔Doc : public CDocument
{
protected: // create from serialization only
	CMy403410016沈濃翔Doc();
	DECLARE_DYNCREATE(CMy403410016沈濃翔Doc)

// Attributes
public:
	CArray <MyPoint, MyPoint &> PArray;
	CArray <MyLine, MyLine &> LArray;
	CArray <MyEllipse, MyEllipse &> EArray;
	CArray <MyRectangle, MyRectangle &> RArray;
	CArray <MyPolyLine, MyPolyLine &> PLArray;
	CArray <MyPolyGon, MyPolyGon &> PGArray;
	CArray <int, int> RecArray;
	int currentStep = 0;

	int shapenum;     //系統幾何編號   0:點 1:線
	COLORREF Obj_Color;   //系統幾何顏色
	int P_Type;    //系統點總類  0:點 1:圓點

// Operations
public:
	void RemoveAll()
	{
		PArray.RemoveAll();
		LArray.RemoveAll();
		EArray.RemoveAll();
		RArray.RemoveAll();
		PLArray.RemoveAll();
		PGArray.RemoveAll();
		RecArray.RemoveAll();
		currentStep = 0;
	}
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMy403410016沈濃翔Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
