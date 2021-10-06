#include "Calculator.h"
#include "CalculatorDlg.h"

CCalculatorDlg::CCalculatorDlg(CWnd* pParent)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCalculatorDlg::~CCalculatorDlg()
{
	for (CButton* btn : m_uiButtons)
	{	delete btn;	btn = NULL;	}

	for (CEdit* box : m_textBoxes)
	{	delete box;	box = NULL;	}

	for(CFont* f : m_fonts)
	{	delete f; f = NULL;	}
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, 10, 26, &CCalculatorDlg::OnButtonClick)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitializeUIComponents();
	InitializeFonts();
	SetFonts();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
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
		m_historyText += m_outputText;		//Adds sum to history
		m_outputText.clear();
		m_lastInput = NULL;

		CalculateTotal();

		//Update Text based on total
		m_historyText += m_totalText + "\r\n";
		m_textBoxes[0]->SetWindowTextA(m_historyText.c_str());
		m_textBoxes[1]->SetWindowTextA(m_totalText.c_str());		//Output total value of sum to output box
		UpdateData(FALSE);
		m_totalText.clear();
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

	return nullptr;
}

CEdit* CCalculatorDlg::CreateNewEditBox(const DWORD& styles, const CRect& pos, const int ID)
{
	CEdit* box = new CEdit;
	if (box->Create(styles, pos, this, ID))
		return box;
		
	return nullptr;
}

void CCalculatorDlg::CalculateTotal()
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

	//Removes trailing 0's from string equivalent of total
	m_totalText = std::to_string(total);
	m_totalText.erase(m_totalText.find_last_not_of('0') + 1, std::string::npos);
	m_totalText.erase(m_totalText.find_last_not_of('.') + 1, std::string::npos);
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

void CCalculatorDlg::InitializeFonts()
{
	CFont* buttonFont = new CFont;
	buttonFont->CreateFontA(26, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Calibri"));

	CFont* outputFont = new CFont;
	outputFont->CreateFontA(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("MS Sans"));

	m_fonts.push_back(buttonFont);
	m_fonts.push_back(outputFont);
}

void CCalculatorDlg::SetFonts()
{
	for (CButton* btn : m_uiButtons)
		btn->SetFont(m_fonts[0]);

	m_textBoxes[1]->SetFont(m_fonts[1]);
}
