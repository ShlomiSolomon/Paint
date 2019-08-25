
// PaintBGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PaintBG.h"
#include "PaintBGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CPaintBGDlg dialog

CPaintBGDlg::CPaintBGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaintBGDlg::IDD, pParent)
	, isFill(FALSE), isThin(FALSE)
{
	shapeType=LINE;
	curColor=RGB(25,50,250);
	isPressed=false;
	index=iMax=0;

	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

CPaintBGDlg::~CPaintBGDlg()
{
	int size=myShapes.size();
	for(int i=0;i<size;i++)
		myShapes.erase(myShapes.begin());
}

void CPaintBGDlg::ClearScreen() 
{
	myShapes.clear();
	moves.delAll();
	undoPic.EnableWindow(0);
	redoPic.EnableWindow(0);
	Invalidate();
}

void CPaintBGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK1, isFill);
	DDX_Check(pDX, IDC_CHECK2, isThin);
	DDX_Control(pDX, IDC_Rectangle, RecPic);
	DDX_Control(pDX, IDC_Square, SquarePic);
	DDX_Control(pDX, IDC_Ellipse, ElipPic);
	DDX_Control(pDX, IDC_Circle, CirPic);
	DDX_Control(pDX, IDC_Triangle, TraPic);
	DDX_Control(pDX, IDC_Line, LinePic);
	DDX_Control(pDX, IDC_Move, MovePic);
	DDX_Control(pDX, IDC_Fill, FillPic);
	DDX_Control(pDX, IDC_Color, ColorPic);
	DDX_Control(pDX, IDC_Redo, redoPic);
	DDX_Control(pDX, IDC_Undo, undoPic);
	DDX_Control(pDX, IDC_SAVE, SavePic);
	DDX_Control(pDX, IDC_NEW, NewPic);
	DDX_Control(pDX, IDC_LOAD, LoadPic);
	DDX_Control(pDX, IDC_Change, ChangePic);
}

BEGIN_MESSAGE_MAP(CPaintBGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	
	ON_BN_CLICKED(IDC_Rectangle, &CPaintBGDlg::OnBnClickedRectangle)
	ON_BN_CLICKED(IDC_Square, &CPaintBGDlg::OnBnClickedSquare)
	ON_BN_CLICKED(IDC_Ellipse, &CPaintBGDlg::OnBnClickedEllipse)
	ON_BN_CLICKED(IDC_Circle, &CPaintBGDlg::OnBnClickedCircle)
	ON_BN_CLICKED(IDC_Triangle, &CPaintBGDlg::OnBnClickedTriangle)
	ON_BN_CLICKED(IDC_Line, &CPaintBGDlg::OnBnClickedLine)
	ON_BN_CLICKED(IDC_Move, &CPaintBGDlg::OnBnClickedMove)
	ON_BN_CLICKED(IDC_Change, &CPaintBGDlg::OnBnClickedChange)
	ON_BN_CLICKED(IDC_Fill, &CPaintBGDlg::OnBnClickedFill)
	ON_BN_CLICKED(IDC_Color, &CPaintBGDlg::OnBnClickedColor)
	ON_BN_CLICKED(IDC_Redo, &CPaintBGDlg::OnBnClickedRedo)
	ON_BN_CLICKED(IDC_Undo, &CPaintBGDlg::OnBnClickedUndo)
	ON_BN_CLICKED(IDC_NEW, &CPaintBGDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_SAVE, &CPaintBGDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CPaintBGDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_CHECK1, &CPaintBGDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPaintBGDlg::OnBnClickedCheck2)


END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////
// CPaintBGDlg message handlers

BOOL CPaintBGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//BOOL bNameValid;
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	RecPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1)));
	SquarePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP17)));
	ElipPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)));
	CirPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP18)));
	TraPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP3)));
	LinePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP16)));
	MovePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP7)));
	FillPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP8)));
	ColorPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP9)));
	redoPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP10)));
	undoPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP11)));
	SavePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP13)));
	NewPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP20)));
	LoadPic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP15)));
    ChangePic.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP14)));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaintBGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintBGDlg::OnPaint()
{
	int curIndex = myShapes.size();
	CPaintDC dc (this);
	for(int i=0; i<curIndex; i++)
		myShapes[i]->Draw(&dc);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintBGDlg::OnQueryDragIcon()
{
	//return <HCURSOR>(m_hIcon);
	return static_cast<HCURSOR>(m_hIcon);
}


int ExIndex = -1;
void CPaintBGDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int curIndex = myShapes.size();
	endP=startP=point;
	CPaintDC dc(this);
	isPressed=true;
	switch(shapeType)
	{

	case CHANGE_COLOR:
		{
			for (int i=0; i<curIndex; i++)
			if(myShapes[i]->isEx(point))
			{
				myShapes[i]->SetColor(curColor);
				Invalidate();
			}
			CClientDC dc(this);
			COLORREF c=curColor;
		}
		break;

	case MOVE_OBJECT:
	
		for (int i=0; i<curIndex; i++)
			if(myShapes[i]->isEx(point))
			{
				ExIndex = i;
			}
		break;

	case CHANGE_OBJECT:

		for (int i = 0; i<curIndex; i++)
			if (myShapes[i]->isEx(point))
			{
				ExIndex = i;
			}
		break;
	}
	if (curIndex < myShapes.size())
		redoPic.EnableWindow(0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CPaintBGDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(isPressed)
	{
		int curIndex = myShapes.size();
		CClientDC dc(this);
		CBrush myBrush,*oldBrush;
		if (isFill)
		{
			myBrush.CreateSolidBrush(curColor);		// fill figure color
			oldBrush=dc.SelectObject( &myBrush );
		}
		dc.SetROP2(R2_NOTXORPEN);

		CPen myPen1(PS_SOLID, isThin?1:4, curColor);		// outside line figure color
		CPen *oldPen;
		oldPen=dc.SelectObject( &myPen1 ); 

		switch(shapeType)
		{
		case RECTANGLE:
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);
			endP=point;
			dc.Rectangle(startP.x, startP.y,endP.x, endP.y);
			undoPic.EnableWindow(1);
			break;
		case SQUARE:
			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			undoPic.EnableWindow(1);
			break;
		case ELLIPSE:
			dc.Ellipse(startP.x, startP.y,endP.x, endP.y);
			endP=point;
			dc.Ellipse(startP.x, startP.y,endP.x, endP.y);
			undoPic.EnableWindow(1);
			break;
		case CIRCLE:
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			undoPic.EnableWindow(1);
			break;
		case TRIANGLE:
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((startP.x + endP.x)/2,startP.y);
			dc.LineTo(startP.x,endP.y);
			endP=point;
			dc.MoveTo(startP.x,endP.y);
			dc.LineTo(endP.x,endP.y);
			dc.LineTo((startP.x + endP.x)/2,startP.y);
			dc.LineTo(startP.x,endP.y);
			undoPic.EnableWindow(1);
			break;
		case LINE:
			dc.MoveTo(startP.x,startP.y);
			dc.LineTo(endP.x,endP.y);
			endP=point;
			dc.MoveTo(startP.x,startP.y);
			dc.LineTo(endP.x,endP.y);
			undoPic.EnableWindow(1);
			break;
		case MOVE_OBJECT:
			
			if (ExIndex != -1)
			{
				myShapes[ExIndex]->Draw(&dc);
				myShapes[ExIndex]->x2 += endP.x - myShapes[ExIndex]->x1;
				myShapes[ExIndex]->y2 += endP.y - myShapes[ExIndex]->y1;
				myShapes[ExIndex]->x1 = endP.x;
				myShapes[ExIndex]->y1 = endP.y;
				endP=point;
				myShapes[ExIndex]->Draw(&dc);
			}
			break;

		case CHANGE_OBJECT:
			if (ExIndex != -1)
			{
				myShapes[ExIndex]->Draw(&dc);
				myShapes[ExIndex]->x1 = endP.x;
				myShapes[ExIndex]->y1 = endP.y;
				endP = point;
				myShapes[ExIndex]->Draw(&dc);
			}
			break;

		}

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CPaintBGDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	int curIndex = myShapes.size();
	if(isPressed)
	{
		endP=point;
		isPressed=false;
		if (endP != startP)
		{
			switch(shapeType)
			{
			case RECTANGLE:
				myShapes.push_back(new MyRectangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyRectangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case SQUARE:
				myShapes.push_back(new MySquare(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				moves.move(new MySquare(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				Invalidate();
				break;
			case ELLIPSE:
				myShapes.push_back(new MyEllipse(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyEllipse(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case CIRCLE:
				myShapes.push_back(new MyCircle(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				moves.move(new MyCircle(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				Invalidate();
				break;
			case TRIANGLE:
				myShapes.push_back(new MyTriangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				moves.move(new MyTriangle(startP.x,startP.y,endP.x,endP.y,isFill,isThin,curColor));
				Invalidate();
				break;
			case LINE:
				myShapes.push_back(new MyLine(startP.x,startP.y,endP.x,endP.y,isThin,curColor));
				moves.move(new MyLine(startP.x,startP.y,endP.x,endP.y,isThin,curColor));
				Invalidate();
				break;
			case MOVE_OBJECT:
				if (ExIndex != -1)
				{
					ExIndex = -1;
					Invalidate();
				}
				break;
			case CHANGE_OBJECT:
				if (ExIndex != -1)
				{
					ExIndex = -1;
					Invalidate();
				}
				break;
			}
		}
		if (curIndex < myShapes.size())
			redoPic.EnableWindow(0);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CPaintBGDlg::OnBnClickedRectangle()
{
	shapeType=RECTANGLE;
}

void CPaintBGDlg::OnBnClickedSquare()
{
	shapeType = SQUARE;
}

void CPaintBGDlg::OnBnClickedEllipse()
{
	shapeType=ELLIPSE;
}

void CPaintBGDlg::OnBnClickedCircle()
{
	shapeType = CIRCLE;
}

void CPaintBGDlg::OnBnClickedTriangle()
{
	shapeType=TRIANGLE;
}

void CPaintBGDlg::OnBnClickedLine()
{
	shapeType=LINE;
}

void CPaintBGDlg::OnBnClickedMove()
{
	shapeType=MOVE_OBJECT;
}

void CPaintBGDlg::OnBnClickedChange()
{
	shapeType = CHANGE_OBJECT;
}

void CPaintBGDlg::OnBnClickedFill()
{
	shapeType=CHANGE_COLOR;
}

void CPaintBGDlg::OnBnClickedCheck1() //fill
{
	UpdateData(true); 
}

void CPaintBGDlg::OnBnClickedCheck2() //thin
{
	UpdateData(true); 
}

void CPaintBGDlg::OnBnClickedNew()
{
	this->ClearScreen();
}

void CPaintBGDlg::OnBnClickedRedo() //redo
{
	myShapes = moves.Redo();
	undoPic.EnableWindow(1);
	Invalidate();
}

void CPaintBGDlg::OnBnClickedUndo() //undo
{
	myShapes = moves.Undo();
	if(myShapes.empty())
		undoPic.EnableWindow(0);
	redoPic.EnableWindow(1);
	Invalidate();
}

void CPaintBGDlg::OnBnClickedColor() //color
{
	CColorDialog dlg; 
	if (dlg.DoModal() == IDOK) 
		curColor = dlg.GetColor();
}

void CPaintBGDlg::OnBnClickedSave()   //des
{
	CFile file(_T("File.$$"), CFile::modeWrite);
	CArchive ar (&file, CArchive::store);
	int ct=myShapes.size();
	ar<<ct;
	for(int i=0;i<ct;i++)
	{
		ar << myShapes[i]->style;
		ar << myShapes[i]->isFill;
		ar << myShapes[i]->isThin;
		ar << myShapes[i]->bgColor;
		ar << myShapes[i]->x1;
		ar << myShapes[i]->y1;
		ar << myShapes[i]->x2;
		ar << myShapes[i]->y2;
	}
	ar.Close();
	file.Close();
}

void CPaintBGDlg::OnBnClickedLoad()  //ser
{
	CFile file(_T("File.$$"), CFile::modeRead);
	CArchive ar (&file, CArchive::load);
	myShapes.clear(); 
	index = iMax = 0;
	int ct;
	CPen p;
	COLORREF color;
	ar>>ct;
	int x1,x2,y1,y2,Fill,Thin,style;
	for (int i=0; i < ct ; i++)
	{
		ar >> style;
		ar >> Fill;
		ar >> Thin;
		ar >> color;
		ar >> x1;
		ar >> y1;
		ar >> x2;
		ar >> y2;
		switch(style)
		{
		case 0:
			myShapes.push_back(new MyRectangle(x1,y1,x2,y2,Fill,Thin,color));
			break;
		case 1:
			myShapes.push_back(new MySquare(x1, y1, x2, y2, Fill, Thin, color));
			break;
		case 2:
			myShapes.push_back(new MyEllipse(x1, y1, x2, y2, Fill, Thin, color));
			break;
		case 3:
			myShapes.push_back(new MyCircle(x1,y1,x2,y2,Fill,Thin,color));
			break;
		case 4:
			myShapes.push_back(new MyTriangle(x1,y1,x2,y2,Fill,Thin,color)); 
			break;
		case 5:
			myShapes.push_back(new MyLine(x1,y1,x2,y2,Thin,color)); 
			break;
			index++;
		}
	}
	ar.Close();
	file.Close();
	Invalidate();
}