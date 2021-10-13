#pragma once
#include <string>
#include <vector>

#define DIALOG_ID 102
#define MAINFRAME_ID 128


struct Operation
{
	const double number;
	const wchar_t operation;
	double precedingNumber;
};

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialog
{
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor
	~CCalculatorDlg();

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButtonClick(UINT nID);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void InitializeUIComponents();
	void InitializeFonts();

	CButton* CreateNewButton(const CString&, const CRect&, const int);
	CEdit* CreateNewEditBox(const DWORD&, const CRect&, const int);

	void AddCharToOutput(const wchar_t);
	void AddStringToOutput(const std::wstring&);		//Used for trigonometric operations
	void AddNumberToSum(const wchar_t);
	void SetFonts();
	bool IsLastInputANumber();
	bool IsLastInputAnOperation();
	bool IsLastOperationTrigonometric(const wchar_t*);
	void CalculateTotal();

	double FindNumberString(size_t, wchar_t*&);
	inline double FindNumberString(size_t s)
	{
		wchar_t* c = &m_outputText[s];
		return FindNumberString(s, c);
	}


	bool m_decimalActive = false;
	wchar_t m_lastInput;
	double m_lastPrecedingNumber = 1.0;

	std::wstring m_outputText = L"";
	std::wstring m_historyText = L"";
	std::wstring m_totalText = L"";

	std::vector<Operation> m_sum;
	std::vector<CButton*> m_uiButtons;
	std::vector<CEdit*> m_textBoxes;
	std::vector<CFont*> m_fonts;
};
