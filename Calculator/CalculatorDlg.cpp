
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

CCalculatorDlg::~CCalculatorDlg()
{
	for (CButton* btn : m_uiButtons)
	{
		delete btn;
		btn = NULL;
	}

	for (CEdit* box : m_textBoxes)
	{
		delete box;
		box = NULL;
	}
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
	InitializeUIComponents();

	font.CreateFontA(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Digital-7"));

	m_textBoxes[1]->SetFont(&font);

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
	m_textBoxes[1]->SetWindowTextA(m_outputText.c_str());
	UpdateData(FALSE);		//FALSE updates window based on new variable value, true takes window value and assigns it to variable
}

void CCalculatorDlg::AddNumberToSum(const char op)
{
	m_decimalActive = false;
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
	AddCharToOutput(op);
}

void CCalculatorDlg::OnButtonClick(UINT nID)
{
	if (nID < 20)		//10-19 is number buttons, put this in a bool check function maybe
	{
		AddCharToOutput('0' + (nID - 10));
		return;
	}

	if (!(nID == 26 || IsLastInputANumber()))		//Quits the application earlier when no change will be made
		return;

	//Operations
	switch (nID)
	{
	case 20:		//Decimal Point
		if (!m_decimalActive)		//number has to be present, only 1 decimal point allowed
		{
			m_decimalActive = true;
			AddCharToOutput('.');
		}
		break;

	case 21:		//Equals
		AddNumberToSum('=');
		m_outputText.clear();
		m_lastInput = NULL;
		m_textBoxes[1]->SetWindowTextA(std::to_string(CalculateTotal()).c_str());
		UpdateData(FALSE);
		break;

	case 22:		//Add
		AddNumberToSum('+');		//Adds number before operation to sum vector
		break;

	case 23:	//Subtract
		AddNumberToSum('-');
		break;

	case 24:	//Multiply
		AddNumberToSum('x');
		break;

	case 25:	//Divide
		AddNumberToSum('/');
		break;

	case 26:		//Clear
		m_outputText.clear();
		m_lastInput = NULL;
		m_textBoxes[1]->SetWindowTextA(m_outputText.c_str());
		UpdateData(FALSE);
		break;
	}
}

CButton* CCalculatorDlg::CreateNewButton(const CString& btnName, const CRect& pos, const int ID)
{
	CButton* btn = new CButton;
	if (btn->Create(btnName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, pos, this, ID))
		return btn;
	else
		assert("CreateNewButton() : Button not created");
}

CEdit* CCalculatorDlg::CreateNewEditBox(const DWORD& styles, const CRect& pos, const int ID)
{
	CEdit* box = new CEdit;
	if (box->Create(styles, pos, this, ID))
		return box;
	else
		assert("CreateNewEditBox() : CEdit not created");
}

double CCalculatorDlg::CalculateTotal()
{
	double total = 0.0f;

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

	return total;
}

bool CCalculatorDlg::IsLastInputANumber()
{
	return m_lastInput > 47 && m_lastInput < 58;
}

void CCalculatorDlg::InitializeUIComponents()
{
	//Number buttons
	{
		m_uiButtons.push_back(CreateNewButton(_T("0"), CRect(50, 345, 112, 395), 10));
		m_uiButtons.push_back(CreateNewButton(_T("1"), CRect(50, 271, 112, 325), 11));
		m_uiButtons.push_back(CreateNewButton(_T("2"), CRect(132, 271, 194, 325), 12));
		m_uiButtons.push_back(CreateNewButton(_T("3"), CRect(215, 271, 277, 325), 13));
		m_uiButtons.push_back(CreateNewButton(_T("4"), CRect(50, 200, 112, 254), 14));
		m_uiButtons.push_back(CreateNewButton(_T("5"), CRect(132, 200, 194, 254), 15));
		m_uiButtons.push_back(CreateNewButton(_T("6"), CRect(215, 200, 277, 254), 16));
		m_uiButtons.push_back(CreateNewButton(_T("7"), CRect(50, 128, 112, 182), 17));
		m_uiButtons.push_back(CreateNewButton(_T("8"), CRect(132, 128, 194, 182), 18));
		m_uiButtons.push_back(CreateNewButton(_T("9"), CRect(215, 128, 277, 182), 19));
	}

	//Operation Buttons
	{
		m_uiButtons.push_back(CreateNewButton(_T("."), CRect(132, 345, 194, 395), 20));
		m_uiButtons.push_back(CreateNewButton(_T("="), CRect(215, 345, 277, 395), 21));
		m_uiButtons.push_back(CreateNewButton(_T("+"), CRect(294, 354, 366, 395), 22));
		m_uiButtons.push_back(CreateNewButton(_T("-"), CRect(294, 299, 366, 340), 23));
		m_uiButtons.push_back(CreateNewButton(_T("x"), CRect(294, 242, 366, 283), 24));
		m_uiButtons.push_back(CreateNewButton(_T("/"), CRect(294, 185, 366, 226), 25));
		m_uiButtons.push_back(CreateNewButton(_T("C"), CRect(294, 128, 366, 169), 26));
	}

	//Calculation History Edit Box
	m_textBoxes.push_back(CreateNewEditBox(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL | ES_READONLY | ES_MULTILINE | WS_VSCROLL,
		CRect(11, 414, 421, 468), 27));

	//Output Edit Box
	m_textBoxes.push_back(CreateNewEditBox(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY | ES_RIGHT, CRect(11, 28, 421, 83), 28));
}
