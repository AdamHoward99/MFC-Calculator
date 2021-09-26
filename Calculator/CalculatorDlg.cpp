
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, historyTxt(_T(""))
	, OutputTxt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HISTORY, historyTxt);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, OutputTxt);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, 10, 20, &CCalculatorDlg::OnButtonClick)

	ON_BN_CLICKED(IDC_BUTTON_NUM_1, &CCalculatorDlg::OnBnClickedButtonNum1)
	ON_BN_CLICKED(IDC_BUTTON_NUM_2, &CCalculatorDlg::OnBnClickedButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_NUM_3, &CCalculatorDlg::OnBnClickedButtonNum3)
	ON_BN_CLICKED(IDC_BUTTON_NUM_4, &CCalculatorDlg::OnBnClickedButtonNum4)
	ON_BN_CLICKED(IDC_BUTTON_NUM_5, &CCalculatorDlg::OnBnClickedButtonNum5)
	ON_BN_CLICKED(IDC_BUTTON_NUM_6, &CCalculatorDlg::OnBnClickedButtonNum6)
	ON_BN_CLICKED(IDC_BUTTON_NUM_7, &CCalculatorDlg::OnBnClickedButtonNum7)
	ON_BN_CLICKED(IDC_BUTTON_NUM_8, &CCalculatorDlg::OnBnClickedButtonNum8)
	ON_BN_CLICKED(IDC_BUTTON_NUM_9, &CCalculatorDlg::OnBnClickedButtonNum9)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	//Function to initialize all calculator buttons
	num0.Create(_T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 345, 112, 395), this, 10);
	num1.Create(_T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 271, 112, 325), this, 20);
	num2.Create(_T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 271, 194, 325), this, 30);
	num3.Create(_T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 271, 277, 325), this, 40);
	num4.Create(_T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 200, 112, 254), this, 50);
	num5.Create(_T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 200, 194, 254), this, 60);
	num6.Create(_T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 200, 277, 254), this, 70);
	num7.Create(_T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 128, 112, 182), this, 80);
	num8.Create(_T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 128, 194, 182), this, 90);
	num9.Create(_T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 128, 277, 182), this, 100);
	

	font.CreateFontW(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::AddDigitToOutput(char num)
{
	OutputTxt += num;
	UpdateData(FALSE);		//FALSE updates window based on new variable value, true takes window value and assigns it to variable
}

void CCalculatorDlg::OnBnClickedButtonNum0()
{
	//Obtains the position on the window of the button
	AddDigitToOutput('0');
}


void CCalculatorDlg::OnBnClickedButtonNum1()
{
	AddDigitToOutput('1');
}

void CCalculatorDlg::OnBnClickedButtonNum2()
{
	AddDigitToOutput('2');
}

void CCalculatorDlg::OnBnClickedButtonNum3()
{
	AddDigitToOutput('3');
}

void CCalculatorDlg::OnBnClickedButtonNum4()
{
	AddDigitToOutput('4');
}

void CCalculatorDlg::OnBnClickedButtonNum5()
{
	AddDigitToOutput('5');
}

void CCalculatorDlg::OnBnClickedButtonNum6()
{
	AddDigitToOutput('6');
}

void CCalculatorDlg::OnBnClickedButtonNum7()
{
	AddDigitToOutput('7');
}

void CCalculatorDlg::OnBnClickedButtonNum8()
{
	AddDigitToOutput('8');
}

void CCalculatorDlg::OnBnClickedButtonNum9()
{
	CRect ex;
	GetDlgItem(IDC_BUTTON_NUM_9)->GetWindowRect(ex);
	ScreenToClient(&ex);
	AddDigitToOutput('9');
}

void CCalculatorDlg::OnButtonClick(UINT nID)
{
	//if (nID == 1)
	//	AfxMessageBox(_T("Number 0 has been pressed"));
}
