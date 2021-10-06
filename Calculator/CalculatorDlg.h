#pragma once
#include "framework.h"
#include <string>
#include <vector>

struct Operation
{
	const double number;
	const char operation;
};

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
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

	void AddCharToOutput(const char);
	void AddNumberToSum(const char);
	void SetFonts();
	bool IsLastInputANumber();
	void CalculateTotal();
	
	
	bool m_decimalActive = false;
	char m_lastInput;

	std::string m_outputText = "";
	std::string m_historyText = "";
	std::string m_totalText = "";

	std::vector<Operation> m_sum;
	std::vector<CButton*> m_uiButtons;
	std::vector<CEdit*> m_textBoxes;
	std::vector<CFont*> m_fonts;
};
