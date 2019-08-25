
// PaintBGDlg.h : header file
//
#if !defined(AFX_PaintBGDlg_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
#define AFX_PaintBGDlg_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <vector>
#include "Shapes.h"
#include "afxwin.h"
#include "UndoRedo.h"
using namespace std;

// CPaintBGDlg dialog
class CPaintBGDlg : public CDialogEx
{
// Construction
public:
	CPaintBGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PAINTBG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	enum SHAPES{RECTANGLE,SQUARE,ELLIPSE,CIRCLE,TRIANGLE,LINE,CHANGE_OBJECT,MOVE_OBJECT,CHANGE_COLOR};
	vector <Shapes*> myShapes;

	void ClearScreen();
	~CPaintBGDlg();

private:
	SHAPES shapeType;
    COLORREF curColor;
	int index,iMax;
	UndoRedo moves;
	bool isPressed;
	CPoint startP;
	CPoint endP;

public:
	CButton RecPic;
	CButton SquarePic;
	CButton ElipPic;
	CButton CirPic;
	CButton TraPic;
	CButton LinePic;
	CButton MovePic;
	CButton FillPic;
	CButton ColorPic;
	CButton redoPic; //redo
	CButton undoPic; //undo
	CButton SavePic;
	CButton NewPic;
	CButton LoadPic;
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedSquare();
	afx_msg void OnBnClickedEllipse();
	afx_msg void OnBnClickedCircle();
	afx_msg void OnBnClickedTriangle();
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedMove();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedFill();
	afx_msg void OnBnClickedColor();
	afx_msg void OnBnClickedRedo();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	BOOL isFill;
	BOOL isThin;
	
	CButton ChangePic;
};

#endif