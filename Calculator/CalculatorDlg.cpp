
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
	, m_outputText(_T(""))
	, m_historyText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, 10, 26, &CCalculatorDlg::OnButtonClick)
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
	num1.Create(_T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 271, 112, 325), this, 11);
	num2.Create(_T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 271, 194, 325), this, 12);
	num3.Create(_T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 271, 277, 325), this, 13);
	num4.Create(_T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 200, 112, 254), this, 14);
	num5.Create(_T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 200, 194, 254), this, 15);
	num6.Create(_T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 200, 277, 254), this, 16);
	num7.Create(_T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(50, 128, 112, 182), this, 17);
	num8.Create(_T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 128, 194, 182), this, 18);
	num9.Create(_T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 128, 277, 182), this, 19);

	decimalButton.Create(_T("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(132, 345, 194, 395), this, 20);
	equalsButton.Create(_T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(215, 345, 277, 395), this, 21);
	addButton.Create(_T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(294, 354, 366, 395), this, 22);
	minusButton.Create(_T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(294, 299, 366, 340), this, 23);
	multiplyButton.Create(_T("x"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(294, 242, 366, 283), this, 24);
	divideButton.Create(_T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(294, 185, 366, 226), this, 25);
	clearButton.Create(_T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, CRect(294, 128, 366, 169), this, 26);

	historyBox.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL | ES_READONLY | ES_MULTILINE | WS_VSCROLL, CRect(11, 414, 421, 468), this, 27);
	outputBox.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY | ES_RIGHT, CRect(11, 28, 421, 83), this, 28);

	font.CreateFontA(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Digital-7"));

	outputBox.SetFont(&font);
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

void CCalculatorDlg::AddCharToOutput(const char txt)
{
	m_outputText += txt;
	m_lastInput = txt;
	outputBox.SetWindowTextA(m_outputText.c_str());
	UpdateData(FALSE);		//FALSE updates window based on new variable value, true takes window value and assigns it to variable
}

void CCalculatorDlg::AddNumberToSum(const char op)
{
	size_t start, size = 0;

	start = m_outputText.size();
	char* c = &m_outputText[m_outputText.size() - 1];

	do
	{
		start--;
		size++;
		c--;
	} while (start >= 0 && (*c > 47 && *c < 58) || *c == '.');

	std::string te = m_outputText.substr(start, size);

	m_sum.push_back({ std::stod(m_outputText.substr(start, size)), *c });
}

void CCalculatorDlg::OnButtonClick(UINT nID)
{
	if (nID < 20)		//10-19 is number buttons, put this in a bool check function maybe
	{
		AddCharToOutput('0' + (nID - 10));
		return;
	}

	switch (nID)
	{
	case 20:		//Decimal Point
		if(m_outputText.length() > 0 && m_outputText.find('.') == -1)		//number has to be present, only 1 decimal point allowed
			AddCharToOutput('.');
		break;

	case 21:		//Equals
		if (m_outputText.length() > 0)
		{

			if (!(m_lastInput > 47 && m_lastInput < 58))
				m_outputText.pop_back();

			AddNumberToSum('=');
			AddCharToOutput('=');

			double total = 0.0f;
			//Do the sum and clear the text
			for (Operation &var : m_sum)
			{
				switch (var.operation)
				{
				case '-':
					total -= var.number;
					break;

				case '+':
					total += var.number;
					break;

				case 'x':
					total *= var.number;
					break;

				case '/':
					total /= var.number;
					break;

				case '=':
					break;

				default:
					total = var.number;
					break;
				}
			}

			m_outputText.clear();
			outputBox.SetWindowTextA(m_outputText.c_str());
			UpdateData(FALSE);

			outputBox.SetWindowTextA(std::to_string(total).c_str());

		}

		break;

	case 22:		//Add
		//needs to have number in front of it, if - is before replace with +, add number before sign into a vector
		if (m_lastInput > 47 && m_lastInput < 58 && m_outputText.length() > 0)		//TODO IMPROVE
		{
			AddNumberToSum('+');		//Adds number before operation to sum vector
			AddCharToOutput('+');
		}
		break;

	case 23:	//Subtract
		if (m_lastInput > 47 && m_lastInput < 58)		//TODO IMPROVE
		{
			AddNumberToSum('-');
			AddCharToOutput('-');
		}
		break;

	case 24:	//Multiply
		if (m_lastInput > 47 && m_lastInput < 58 && m_outputText.length() > 0)
		{
			AddNumberToSum('x');
			AddCharToOutput('x');
		}
		break;

	case 25:	//Divide
		if (m_lastInput > 47 && m_lastInput < 58 && m_outputText.length() > 0)
		{
			AddNumberToSum('/');
			AddCharToOutput('/');
		}
		break;


	case 26:		//Clear
		m_outputText.clear();
		outputBox.SetWindowTextA(m_outputText.c_str());
		break;
	}
	//else
	//{
	//	CRect x;
	//	GetDlgItem(IDC_EDIT_OUTPUT)->GetWindowRect(x);
	//	ScreenToClient(&x);
	//	int tr = 0;
	//}

	//if (nID == 1)
	//	AfxMessageBox(_T("Number 0 has been pressed"));
}
