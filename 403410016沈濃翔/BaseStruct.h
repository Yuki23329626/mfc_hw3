// BaseStruct.h :  基本幾何結構資料
#include "stdafx.h"
#include <fstream>
#include <string>
using namespace std;
class Shape	// Base Class
{
public:
	CPoint StartPnt, EndPnt, Prepoint;	//定義形狀的終點與起點
	int LineWidth;
	// BOOL Draw1;
	int shapenum;	// 形狀代號
	COLORREF color;
	BOOL Filled;	// 設定繪製形狀時，是否填滿
	int LineType;
	int FillHatchType;
	int Fill_Selected; public:

		// Constructor
		Shape()
		{
			LineWidth = 1;
			LineType = 0;
			Filled = 0;
			color = RGB(255, 0, 0);
		}
		// Override operator=
		Shape & operator= (Shape & s)
		{
			StartPnt = s.StartPnt;	//設定起點
			EndPnt = s.EndPnt;	//設定終點
			return *this;
		}
		virtual void draw(CDC & aDC, COLORREF color, COLORREF fcolor, int width, int lineType, BOOL Filled = false) = 0;
		int GetShapeNum()	//取得形狀代號
		{
			return shapenum;
		}
		void SetPoint(CPoint SPnt, CPoint EPnt)	//設定形狀的起點、終點
		{
			StartPnt = SPnt;
			EndPnt = EPnt;
		}
};

class MyPoint
{
public:
	CPoint point;	//定義形狀的終點與起點
	COLORREF color;
	int shapenum;

	// Constructor
	MyPoint()
	{
		color = RGB(255, 0, 0);
		shapenum = ID_DRAW_POINT;
		point = (0, 0);


	}

	// Override operator=
	MyPoint & operator= (MyPoint & p)
	{
		point = p.point;
		color = p.color;
		shapenum = p.shapenum;
		return *this;
	}
};
//
//class MyArrow : public Shape	//直線類別
//{
//public:
//	int Length;
//	CPoint  ArrowUp, ArrowDown;
//	MyArrow()
//	{
//		color = RGB(255, 0, 0);
//		shapenum = 10;
//		StartPnt.SetPoint(500, 300);
//		//StartPnt.x=StartPnt.y=400;
//		LineWidth = 1;
//		Length = 300;
//		EndPnt.SetPoint(StartPnt.x + Length, StartPnt.y);
//		ArrowUp.SetPoint(int(EndPnt.x - Length / 10.), int(EndPnt.y + Length / 10.));
//		ArrowDown.SetPoint(int(EndPnt.x - Length / 10.), int(EndPnt.y - Length / 10.));
//	}
//
//	//建構子
//	MyArrow(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
//	{
//		color = color2;
//		shapenum = ID_DRAW_LINE;
//		StartPnt = StartPnt2;
//		EndPnt = EndPnt2;
//
//	}
//	//過載=運算子
//	MyArrow & operator= (MyArrow & l)
//	{
//		StartPnt = l.StartPnt;
//		color = l.color;
//		LineWidth = l.LineWidth;
//		EndPnt = l.EndPnt;
//		shapenum = l.shapenum;
//		return *this;
//	}
//	void draw(CDC &dc, COLORREF color, COLORREF fcolor,
//		int width, int lineType, BOOL Filled = false)
//	{
//		CPen pen(lineType, width, color);	//建立畫筆物件
//		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
//		dc.MoveTo(StartPnt);	//移至直線起點
//		dc.LineTo(EndPnt);	//移至直線終點
//		dc.SelectObject(oldPen);	//還原選取的畫筆物件
//	}
//	void draw2(CDC &dc)
//	{
//		CPen pen(LineType, LineWidth, color);	//建立畫筆物件//PS_DASHDOT PS_SOLID
//		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
//		dc.MoveTo(StartPnt);	//移至直線起點
//		dc.LineTo(EndPnt);	//移至直線終點
//		dc.SelectObject(oldPen);	//還原選取的畫筆物件
//	}
//	void draw3(CDC &dc, int angle)
//	{
//		double tempang, x, y, tempangu, tempangd;
//		double ang0, angu, angd, Statangle, angS;
//		double LengthU, LengthD;
//		//	CPen pen(PS_SOLID, LineWidth,color);	//建立畫筆物件
//		CPen pen(PS_SOLID, 3, color);	//建立畫筆物件
//		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
//		CBrush m_newbrush;
//		//   ang0=atan2((double)-1.0,(double)0);
//		Statangle = 245;
//		angS = -3.14159 * 2 / (360. / Statangle);
//		ang0 = atan2((double)0, (double)1) + angS;
//		x = (ArrowUp.x - StartPnt.x);
//		y = (ArrowUp.y - StartPnt.y);
//		angu = atan2((double)y, (double)x) + angS;
//		x = (ArrowDown.x - StartPnt.x);
//		y = (ArrowDown.y - StartPnt.y);
//		angd = atan2((double)y, (double)x) + angS;
//		tempang = ang0 + (angle*3.14159 * 2) / 60.;
//		tempangu = angu + (angle*3.14159 * 2) / 60.;
//		tempangd = angd + (angle*3.14159 * 2) / 60.;
//		/* EndPnt.x=EndPnt.x+Length*cos(tempang);
//		EndPnt.y=EndPnt.y+Length*sin(tempang);
//		ArrowUp.x=ArrowUp.x+Length*cos(tempang);
//		ArrowUp.y=ArrowUp.y+Length*sin(tempang);
//		ArrowDown.x=ArrowDown.x+Length*cos(tempang);
//		ArrowDown.y=ArrowDown.y+Length*sin(tempang); 		*/
//		int EndPnt_x, EndPnt_y;
//		int ArrowUp_x, ArrowUp_y;
//		int ArrowDown_x, ArrowDown_y;
//		/*    EndPnt_x=(EndPnt.x-StartPnt.x)*cos(tempang)+StartPnt.x;
//		EndPnt_y=(EndPnt.y-StartPnt.y)*cos(tempang)+StartPnt.y;
//		ArrowUp_x=(ArrowUp.x-StartPnt.x)*cos(tempang)+StartPnt.x;
//		ArrowUp_y=(ArrowUp.y-StartPnt.y)*cos(tempang)+StartPnt.y;
//		ArrowDown_x=(ArrowDown.x-StartPnt.x)*cos(tempang)+StartPnt.x;
//		ArrowDown_y=(ArrowDown.y-StartPnt.y)*cos(tempang)+StartPnt.y;*/
//
//		LengthU = sqrt(double(ArrowUp.x - StartPnt.x)*(ArrowUp.x - StartPnt.x) + (ArrowUp.y - StartPnt.y)*(ArrowUp.y - StartPnt.y));
//
//		LengthD = sqrt(double(ArrowDown.x - StartPnt.x)*(ArrowDown.x - StartPnt.x) + (ArrowDown.y - StartPnt.y)*(ArrowDown.y - StartPnt.y));
//		EndPnt_x = Length * cos(tempang) + StartPnt.x;
//		EndPnt_y = Length * sin(tempang) + StartPnt.y;
//		ArrowUp_x = LengthU * cos(tempangu) + StartPnt.x;
//		ArrowUp_y = LengthU * sin(tempangu) + StartPnt.y;
//		ArrowDown_x = LengthD * cos(tempangd) + StartPnt.x;
//		ArrowDown_y = LengthD * sin(tempangd) + StartPnt.y;
//
//		CPoint Pt[3];
//		Pt[0].SetPoint(EndPnt_x, EndPnt_y);
//		Pt[1].SetPoint(ArrowUp_x, ArrowUp_y);
//		Pt[2].SetPoint(ArrowDown_x, ArrowDown_y);
//		//  m_newbrush.CreateSolidBrush(color);
//		m_newbrush.CreateHatchBrush(5, RGB(0, 55, 55));
//
//		dc.SelectObject(&m_newbrush);
//		dc.MoveTo(StartPnt);	//移至直線起點
//		dc.LineTo(Pt[0]);	//移至直線終點
//		dc.Polygon(Pt, 3);	//繪出矩形
//		dc.SelectObject(oldPen);	//還原選取的畫筆物件
//	}
//
//};

class MyLine : public Shape	// 直線類別 
{
public:
	// Constructor
	MyLine()
	{
		color = RGB(255, 0, 0);
		shapenum = ID_DRAW_LINE;
		StartPnt = (0, 0);
	}

	// Constructor
	MyLine(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = ID_DRAW_LINE;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;

	}
	// Override operator=
	MyLine & operator= (MyLine & l)
	{
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		LineType = l.LineType;
		return *this;
	}
	void draw(CDC &dc, COLORREF color, COLORREF fcolor,
		int width, int lineType, BOOL Filled = false)
	{
		CPen pen(lineType, width, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);	//移至直線起點
		dc.LineTo(EndPnt);	//移至直線終點
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw2(CDC &dc)
	{
		CPen pen(LineType, LineWidth, color);	//建立畫筆物件//PS_DASHDOT PS_SOLID
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);	//移至直線起點
		dc.LineTo(EndPnt);	//移至直線終點
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw3(CDC &dc)
	{
		CPen pen(LineType, LineWidth, RGB(0, 0, 0));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);	//移至直線起點
		dc.LineTo(EndPnt);	//移至直線終點
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
};

class MyEllipse : public Shape	//橢圓形類別
{
public:
	BOOL Filled;
	COLORREF fcolor;

	// Constructor
	MyEllipse()
	{
		color = RGB(0, 255, 0);
		fcolor = RGB(0, 0, 255);
		shapenum = ID_DRAW_ELLIPSE;
		StartPnt = (0, 0);
		Filled = 1;
	}
	MyEllipse(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = ID_DRAW_ELLIPSE;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}
	// Override operator=
	MyEllipse & operator= (MyEllipse & l)	//過載=運算子
	{
		Filled = l.Filled;
		fcolor = l.fcolor;
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		LineType = l.LineType;
		return *this;
	}
	void draw(CDC & dc, COLORREF color, COLORREF fcolor, int width, int lineType, BOOL Filled = false)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(lineType, width, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件		
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			//  m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Ellipse(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}

	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(LineType, LineWidth, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件

		if (Filled)
		{
			if (Fill_Selected == 0)
				m_newbrush.CreateSolidBrush(fcolor);
			else
				m_newbrush.CreateHatchBrush(FillHatchType, fcolor);    	//    m_newbrush.CreateSolidBrush(fcolor);
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Ellipse(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}
	void draw3(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(LineType, LineWidth, RGB(0, 0, 0));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件

		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Ellipse(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}
};

class MyRectangle : public Shape	//矩形類別 
{
public:
	BOOL Filled;
	COLORREF fcolor;

	// Constructor
	MyRectangle()
	{
		color = RGB(255, 0, 0);
		shapenum = ID_DRAW_RECTANGLE;
		StartPnt = (0, 0);
		Filled = 1;
	}
	MyRectangle(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = ID_DRAW_RECTANGLE;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}

	// Override operator=
	MyRectangle & operator= (MyRectangle & l)	//過載=運算子
	{
		Filled = l.Filled;
		fcolor = l.fcolor;
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		LineType = l.LineType;
		return *this;
	}
	void draw(CDC & dc, COLORREF color, COLORREF fcolor, int width, int lineType, BOOL Filled = false)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(lineType, width, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件

		if (Filled)
		{
			//  m_newbrush.CreateSolidBrush(RGB(0,255,255));
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 55, 55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Rectangle(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(LineType, LineWidth, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		SetBkMode(dc, TRANSPARENT);
		if (Filled)
		{
			if (Fill_Selected == 0)
				m_newbrush.CreateSolidBrush(fcolor);
			else
				m_newbrush.CreateHatchBrush(FillHatchType, fcolor);    	//    m_newbrush.CreateSolidBrush(fcolor);
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Rectangle(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}


	void draw3(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);	//建立CRect物件
		CBrush m_newbrush;
		CPen pen(LineType, LineWidth, RGB(0, 0, 0));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件

		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//	m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}
		dc.Rectangle(rect);	//繪出矩形
		dc.SelectObject(oldPen);	//還原畫筆物件
									//	m_newbrush.DeleteObject();
	}
	void drawBMP(CDC & aDC, CString FileNamePath, CBitmap &m_bitmap, CDC &m_dc)
	{

		BITMAP   bmstru;
		CPoint BMPSt = StartPnt;
		CPoint BMPEt = EndPnt;
		int bx = abs(BMPSt.x - BMPEt.x);
		int by = abs(BMPSt.y - BMPEt.y);
		m_bitmap.m_hObject = (HBITMAP)LoadImage(NULL, FileNamePath, IMAGE_BITMAP, bx, by, LR_LOADFROMFILE);
		// int j= m_bitmap.LoadBitmap(IDB_BITMAP3);
		m_bitmap.SetBitmapDimension(bx, by);
		m_dc.CreateCompatibleDC(&aDC);
		m_bitmap.GetBitmap(&bmstru);
		m_dc.SelectObject(&m_bitmap);
		int Sx, Sy;
		if ((BMPEt.x - BMPSt.x) < 0 && (BMPEt.y - BMPSt.y) < 0)
		{
			//aDC.BitBlt(BMPEt.x,BMPEt.y,bx,by,&m_dc,0,0,SRCCOPY);
			Sx = BMPEt.x;
			Sy = BMPEt.y;
		}
		else if ((BMPEt.x - BMPSt.x) < 0 && (BMPEt.y - BMPSt.y) > 0)
		{
			//   aDC.BitBlt(BMPEt.x,BMPSt.y,bx,by,&m_dc,0,0,SRCCOPY);
			Sx = BMPEt.x;
			Sy = BMPSt.y;
		}
		else if ((BMPEt.x - BMPSt.x) > 0 && (BMPEt.y - BMPSt.y) < 0)
		{
			//   aDC.BitBlt(BMPSt.x,BMPEt.y,bx,by,&m_dc,0,0,SRCCOPY);
			Sx = BMPSt.x;
			Sy = BMPEt.y;

		}
		else
		{
			//aDC.BitBlt(BMPSt.x,BMPSt.y,bx,by,&m_dc,0,0,SRCCOPY);
			Sx = BMPSt.x;
			Sy = BMPSt.y;

		}
		//bx=bmstru.bmWidth;
		//by=bmstru.bmHeight;
		//aDC.SetStretchBltMode(1);
		//aDC.StretchBlt(Sx,Sy, bx, by,&m_dc, 0, 0, bmstru.bmWidth,bmstru.bmHeight,SRCCOPY);
		aDC.BitBlt(Sx, Sy, bx, by, &m_dc, 0, 0, SRCCOPY);
		COLORREF transparent_color = RGB(255, 255, 255);
		//aDC.TransparentBlt(Sx,Sy, bx, by,&m_dc, 0, 0, bx,by,transparent_color);
		m_bitmap.DeleteObject();
		m_dc.DeleteDC();

	}

};




class PalletTemplate	//橢圓形類別
{
public:
	CString PalletName;
	CString Filepath;
	CArray <MyEllipse, MyEllipse &>    EArray;
	CArray <MyRectangle, MyRectangle &>    RArray;
	CArray <MyLine, MyLine &>    LArray;
	CArray <MyPoint, MyPoint &>    PArray;
	PalletTemplate & operator= (PalletTemplate & l)	//過載=運算子
	{
		PalletName = l.PalletName;
		Filepath = l.Filepath;
		for (int i = 0; i < l.EArray.GetCount(); i++)
		{

			EArray.Add(l.EArray[i]);

		}
		for (int i = 0; i < l.RArray.GetCount(); i++)
		{

			RArray.Add(l.RArray[i]);

		}
		for (int i = 0; i < l.EArray.GetCount(); i++)
		{

			EArray.Add(l.EArray[i]);

		}
		for (int i = 0; i < l.LArray.GetCount(); i++)
		{

			LArray.Add(l.LArray[i]);

		}
		return *this;
	}
	void draw2(CDC &dc)
	{
		CPen pen(0, 5, RGB(234, 237, 120));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		for (int i = 0; i < LArray.GetCount(); i++)
		{
			CPoint x = LArray[i].StartPnt;
			CPoint y = LArray[i].EndPnt;

			dc.MoveTo(LArray[i].StartPnt);	//移至直線起點
			dc.LineTo(LArray[i].EndPnt);	//移至直線起點

		}

		for (int i = 0; i < RArray.GetCount(); i++)
		{
			CRect rect(RArray[i].StartPnt, RArray[i].EndPnt);	//建立CRect物件
			dc.Rectangle(rect);	//繪出矩形

		}
		for (int i = 0; i < EArray.GetCount(); i++)
		{
			CRect rect(EArray[i].StartPnt, EArray[i].EndPnt);	//建立CRect物件
			dc.Ellipse(rect);
		}


		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}

};

class MyPolyLine : public Shape	//直線類別
{
public:
	CArray <CPoint, CPoint&> PArray;
	MyPolyLine()
	{
		color = RGB(255, 0, 0);
		shapenum = ID_DRAW_POLYLINE;
		StartPnt = (0, 0);
	}

	// Constructor
	MyPolyLine(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = ID_DRAW_POLYLINE;
		PArray.Add(StartPnt2);
		PArray.Add(EndPnt2);
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}

	MyPolyLine(MyPolyLine &myPolyLine) {
		StartPnt = myPolyLine.StartPnt;
		color = myPolyLine.color;
		LineWidth = myPolyLine.LineWidth;
		EndPnt = myPolyLine.EndPnt;
		shapenum = myPolyLine.shapenum;
		LineType = myPolyLine.LineType;
		for (int i = 0; i < myPolyLine.PArray.GetSize(); i++) {
			PArray.Add(myPolyLine.PArray[i]);
		}
	}

	// Override operator=
	MyPolyLine & operator= (MyPolyLine & myPolyLine)
	{
		StartPnt = myPolyLine.StartPnt;
		color = myPolyLine.color;
		LineWidth = myPolyLine.LineWidth;
		EndPnt = myPolyLine.EndPnt;
		shapenum = myPolyLine.shapenum;
		LineType = myPolyLine.LineType;
		for (int i = 0; i < myPolyLine.PArray.GetSize(); i++) {
			PArray.Add(myPolyLine.PArray[i]);
		}
		return *this;
	}
	void draw(CDC &dc, COLORREF color, COLORREF fcolor,
		int width, int lineType, BOOL Filled = false)
	{
		CPen pen(lineType, width, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		int PNum = PArray.GetSize() - 1;
		for (int i = 0; i < PNum; i++) {
			dc.MoveTo(PArray[i]);	//移至直線起點
			dc.LineTo(PArray[i + 1]);	//移至直線終點
		}
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw2(CDC &dc)
	{
		CPen pen(LineType, LineWidth, color);	//建立畫筆物件//PS_DASHDOT PS_SOLID
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		int PNum = PArray.GetSize();
		CPoint* pnts = (CPoint*)calloc(PNum, sizeof(CPoint));
		for (int i = 0; i < PNum; i++) {
			//dc.MoveTo(PArray[i]);	//移至直線起點
			//dc.LineTo(PArray[i + 1]);	//移至直線終點
			pnts[i] = PArray[i];
		}
		dc.Polyline(pnts, PNum);
		free(pnts);
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw3(CDC &dc)
	{
		CPen pen(LineType, LineWidth, RGB(0, 0, 0));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		int PNum = PArray.GetSize() - 1;
		for (int i = 0; i < PNum; i++) {
			dc.MoveTo(PArray[i]);	//移至直線起點
			dc.LineTo(PArray[i + 1]);	//移至直線終點
		}
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
};

class MyPolyGon : public Shape	//直線類別
{
public:
	BOOL Filled;
	COLORREF fcolor;
	CArray <CPoint, CPoint&> PArray;
	MyPolyGon()
	{
		color = RGB(255, 0, 0);
		shapenum = ID_DRAW_POLYGON;
		StartPnt = (0, 0);
	}

	//建構子
	MyPolyGon(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = ID_DRAW_POLYGON;
		PArray.Add(StartPnt2);
		PArray.Add(EndPnt2);
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
		Filled = 1;
	}

	MyPolyGon(MyPolyGon &myPolyGon) {
		StartPnt = myPolyGon.StartPnt;
		color = myPolyGon.color;
		LineWidth = myPolyGon.LineWidth;
		EndPnt = myPolyGon.EndPnt;
		shapenum = myPolyGon.shapenum;
		LineType = myPolyGon.LineType;
		for (int i = 0; i < myPolyGon.PArray.GetSize(); i++) {
			PArray.Add(myPolyGon.PArray[i]);
		}
	}

	// Override operator=
	MyPolyGon & operator= (MyPolyGon & MyPolyGon)
	{
		StartPnt = MyPolyGon.StartPnt;
		color = MyPolyGon.color;
		LineWidth = MyPolyGon.LineWidth;
		EndPnt = MyPolyGon.EndPnt;
		shapenum = MyPolyGon.shapenum;
		LineType = MyPolyGon.LineType;
		Filled = MyPolyGon.Filled;
		fcolor = MyPolyGon.fcolor;
		for (int i = 0; i < MyPolyGon.PArray.GetSize(); i++) {
			PArray.Add(MyPolyGon.PArray[i]);
		}
		return *this;
	}
	void draw(CDC &dc, COLORREF color, COLORREF fcolor,
		int width, int lineType, BOOL Filled = false)
	{
		CPen pen(lineType, width, color);	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		int PNum = PArray.GetSize() - 1;
		for (int i = 0; i < PNum; i++) {
			dc.MoveTo(PArray[i]);	//移至直線起點
			dc.LineTo(PArray[i + 1]);	//移至直線終點
		}
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw2(CDC &dc)
	{
		CPen pen(LineType, LineWidth, color);	//建立畫筆物件//PS_DASHDOT PS_SOLID
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		CBrush myBrush;
		if (Filled)
		{
			if (Fill_Selected == 0)
				myBrush.CreateSolidBrush(fcolor);
			else
				myBrush.CreateHatchBrush(FillHatchType, fcolor);    	//    myBrush.CreateSolidBrush(fcolor);
			dc.SelectObject(&myBrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
		}

		int PNum = PArray.GetSize();
		CPoint* pnts = (CPoint*)calloc(PNum+1, sizeof(CPoint));
		for (int i = 0; i < PNum; i++) {
			//dc.MoveTo(PArray[i]);	//移至直線起點
			//dc.LineTo(PArray[i + 1]);	//移至直線終點
			pnts[i] = PArray[i];
			TRACE("%d, %d\n", pnts[i].x, pnts[i].y);
		}
		dc.Polygon(pnts, PNum);
		free(pnts);
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	void draw3(CDC &dc)
	{
		CPen pen(LineType, LineWidth, RGB(0, 0, 0));	//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
		int PNum = PArray.GetSize() - 1;
		for (int i = 0; i < PNum; i++) {
			dc.MoveTo(PArray[i]);	//移至直線起點
			dc.LineTo(PArray[i + 1]);	//移至直線終點
		}
		dc.SelectObject(oldPen);	//還原選取的畫筆物件
	}
	//void draw4(CDC &dc)
	//{
	//	CPen pen(LineType, LineWidth, color);	//建立畫筆物件//PS_DASHDOT PS_SOLID
	//	CPen *oldPen = dc.SelectObject(&pen);	//設定DC物件使用pen物件
	//	CBrush myBrush;
	//	if (Filled)
	//	{
	//		if (Fill_Selected == 0)
	//			myBrush.CreateSolidBrush(fcolor);
	//		else
	//			myBrush.CreateHatchBrush(FillHatchType, fcolor);    	//    myBrush.CreateSolidBrush(fcolor);
	//		dc.SelectObject(&myBrush);
	//	}
	//	else
	//	{
	//		dc.SelectStockObject(NULL_BRUSH);	//設定DC物件不使用畫筆
	//	}

	//	int PNum = PArray.GetSize();
	//	CPoint* pnts = (CPoint*)calloc(PNum, sizeof(CPoint));
	//	for (int i = 0; i < PNum; i++) {
	//		//dc.MoveTo(PArray[i]);	//移至直線起點
	//		//dc.LineTo(PArray[i + 1]);	//移至直線終點
	//		pnts[i] = PArray[i];
	//		TRACE("%d, %d\n", pnts[i].x, pnts[i].y);
	//	}
	//	dc.Polygon(pnts, PNum);
	//	free(pnts);
	//	dc.SelectObject(oldPen);	//還原選取的畫筆物件
	//}
};