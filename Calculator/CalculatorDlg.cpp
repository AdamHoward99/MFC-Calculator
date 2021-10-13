#include "Calculator.h"
#include "CalculatorDlg.h"

CCalculatorDlg::CCalculatorDlg(CWnd* pParent) 
	: CDialog(DIALOG_ID, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(MAINFRAME_ID);
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

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, 10, 30, &CCalculatorDlg::OnButtonClick)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
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
	CDialog::OnSysCommand(nID, lParam);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::AddCharToOutput(const wchar_t txt)
{
	m_outputText += txt;
	m_lastInput = txt;
	m_textBoxes[1]->SetWindowTextW(m_outputText.c_str());
	UpdateData(FALSE);		//FALSE updates window based on new variable value, true takes window value and assigns it to variable
}

void CCalculatorDlg::AddStringToOutput(const std::wstring& str)
{
	m_outputText += str;
	m_lastInput = str[0];
	m_textBoxes[1]->SetWindowTextW(m_outputText.c_str());
	UpdateData(FALSE);
}

void CCalculatorDlg::AddNumberToSum(const wchar_t op)
{
	m_decimalActive = false;

	wchar_t* c = &m_outputText[m_outputText.size() - 1];
	double num = FindNumberString(m_outputText.size(), c);

	//Last operation was a trigonometric operation (sin, cos, tan)
	if (IsLastOperationTrigonometric(c))
	{
		c -= 4;
		m_sum.push_back({ num, *c, m_lastPrecedingNumber });
		m_lastPrecedingNumber = 1.0;
		AddCharToOutput(L')');
		AddCharToOutput(op);
		return;
	}

	m_sum.push_back({ num, *c });
	AddCharToOutput(op);
}

double CCalculatorDlg::FindNumberString(size_t start, wchar_t*& op)
{
	size_t size = 0;

	do
	{
		start--;
		size++;
		op--;
	} while (start > 0 && (*op >= L'0' && *op <= L'9') || *op == L'.');

	return std::stod(m_outputText.substr(start, size));
}

void CCalculatorDlg::OnButtonClick(UINT nID)
{
	if (nID < 20)		//10-19 is number buttons, put this in a bool check function maybe
	{
		AddCharToOutput(L'0' + (nID - 10));
		return;
	}

	if (!(nID > 25 || IsLastInputANumber()))		//Quits the application earlier when no change will be made
		return;

	//Operations
	switch (nID)
	{
	case 20:		//Decimal Point
		if (!m_decimalActive)		//number has to be present, only 1 decimal point allowed
		{
			m_decimalActive = true;
			AddCharToOutput(L'.');
		}
		break;

	case 21:		//Equals
		AddNumberToSum(L'=');
		m_historyText += m_outputText;		//Adds sum to history
		m_outputText.clear();
		m_lastInput = NULL;

		CalculateTotal();

		//Update Text based on total
		m_historyText += m_totalText + L"\r\n";
		m_textBoxes[0]->SetWindowTextW(m_historyText.c_str());
		m_textBoxes[1]->SetWindowTextW(m_totalText.c_str());		//Output total value of sum to output box
		UpdateData(FALSE);
		m_totalText.clear();
		m_sum.clear();
		break;

	case 22:		//Add
		AddNumberToSum(L'+');		//Adds number before operation to sum vector
		break;

	case 23:	//Subtract
		AddNumberToSum(L'-');
		break;

	case 24:	//Multiply
		AddNumberToSum(L'x');
		break;

	case 25:	//Divide
		AddNumberToSum(L'/');
		break;

	case 26:		//Clear
		m_outputText.clear();
		m_lastInput = NULL;
		m_textBoxes[1]->SetWindowTextW(m_outputText.c_str());
		UpdateData(FALSE);
		break;

	case 27:		//Square Root
		if (IsLastInputAnOperation() || m_lastInput == NULL)
			AddCharToOutput(L'√');
		break;

	case 28:		//sine
		TrigonometricOperations(L"sinθ(", L's');
		break;

	case 29:	//cosine
		TrigonometricOperations(L"cosθ(", L'c');
		break;

	case 30:	//tangent
		TrigonometricOperations(L"tanθ(", L't');
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
		case L'-':
			total -= var.number;
			break;

		case L'+':
			total += var.number;
			break;

		case L'x':
			total *= var.number;
			break;

		case L'/':
			total /= var.number;
			break;

		case L'√':
			total += sqrt(var.number);
			break;

		case L's':
			total +=  var.precedingNumber * sin(var.number);
			break;

		case L'c':
			total += var.precedingNumber * cos(var.number);
			break;

		case L't':
			total += var.precedingNumber * tan(var.number);

		case L'=':
			break;

		default:
			total = var.number;
			break;
		}
	}

	//Removes trailing 0's from string equivalent of total
	m_totalText = std::to_wstring(total);
	m_totalText.erase(m_totalText.find_last_not_of(L'0') + 1, std::string::npos);
	m_totalText.erase(m_totalText.find_last_not_of(L'.') + 1, std::string::npos);
}

bool CCalculatorDlg::IsLastInputANumber()
{
	return m_lastInput > 47 && m_lastInput < 58;
}

bool CCalculatorDlg::IsLastInputAnOperation()
{
	return m_lastInput == L'+' || m_lastInput == L'-' || m_lastInput == L'x' || m_lastInput == L'/';
}

void CCalculatorDlg::InitializeUIComponents()
{
	//Number buttons
	{
		m_uiButtons.push_back(CreateNewButton(_T("0"), CRect(25, 345, 87, 395), 10));
		m_uiButtons.push_back(CreateNewButton(_T("1"), CRect(25, 271, 87, 325), 11));
		m_uiButtons.push_back(CreateNewButton(_T("2"), CRect(107, 271, 169, 325), 12));
		m_uiButtons.push_back(CreateNewButton(_T("3"), CRect(190, 271, 252, 325), 13));
		m_uiButtons.push_back(CreateNewButton(_T("4"), CRect(25, 200, 87, 254), 14));
		m_uiButtons.push_back(CreateNewButton(_T("5"), CRect(107, 200, 169, 254), 15));
		m_uiButtons.push_back(CreateNewButton(_T("6"), CRect(190, 200, 252, 254), 16));
		m_uiButtons.push_back(CreateNewButton(_T("7"), CRect(25, 128, 87, 182), 17));
		m_uiButtons.push_back(CreateNewButton(_T("8"), CRect(107, 128, 169, 182), 18));
		m_uiButtons.push_back(CreateNewButton(_T("9"), CRect(190, 128, 252, 182), 19));
	}

	//Operation Buttons
	{
		m_uiButtons.push_back(CreateNewButton(_T("."), CRect(107, 345, 169, 395), 20));
		m_uiButtons.push_back(CreateNewButton(_T("="), CRect(190, 345, 252, 395), 21));
		m_uiButtons.push_back(CreateNewButton(_T("+"), CRect(269, 354, 341, 395), 22));
		m_uiButtons.push_back(CreateNewButton(_T("-"), CRect(269, 299, 341, 340), 23));
		m_uiButtons.push_back(CreateNewButton(_T("x"), CRect(269, 242, 341, 283), 24));
		m_uiButtons.push_back(CreateNewButton(_T("/"), CRect(269, 185, 341, 226), 25));
		m_uiButtons.push_back(CreateNewButton(_T("C"), CRect(269, 128, 341, 169), 26));
		m_uiButtons.push_back(CreateNewButton(_T("√"), CRect(350, 128, 422, 169), 27));
		m_uiButtons.push_back(CreateNewButton(_T("sin"), CRect(350, 185, 422, 226), 28));
		m_uiButtons.push_back(CreateNewButton(_T("cos"), CRect(350, 242, 422, 283), 29));
		m_uiButtons.push_back(CreateNewButton(_T("tan"), CRect(350, 299, 422, 340), 30));
	}

	//Calculation History Edit Box
	m_textBoxes.push_back(CreateNewEditBox(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOVSCROLL | ES_READONLY | ES_MULTILINE | WS_VSCROLL,
		CRect(11, 414, 421, 468), 31));

	//Output Edit Box
	m_textBoxes.push_back(CreateNewEditBox(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY | ES_RIGHT, CRect(11, 28, 421, 83), 32));
}

void CCalculatorDlg::InitializeFonts()
{
	CFont* buttonFont = new CFont;
	buttonFont->CreateFontW(26, 0, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Calibri"));

	CFont* outputFont = new CFont;
	outputFont->CreateFontW(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
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

bool CCalculatorDlg::IsLastOperationTrigonometric(const wchar_t* c)
{
	return *c == L'(';
}

void CCalculatorDlg::TrigonometricOperations(const std::wstring& str, const wchar_t& c)
{
	if (m_lastInput == NULL || IsLastInputAnOperation())
		AddStringToOutput(str);

	//Numbers before the operation
	if (IsLastInputANumber())
	{
		AddStringToOutput(str);
		m_lastPrecedingNumber = FindNumberString(m_outputText.find_first_of(c));
	}
}
