
// CalculatorDlg.h : header file
//

#pragma once
#include <unordered_map>
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
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor
	~CCalculatorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

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
private:
	std::string m_outputText;
	CString m_historyText;

	CFont font;
	//std::unordered_map<std::string, CButton> m_uiButtons;
	std::vector<CButton*> m_uiButtons;
	std::vector<CEdit*> m_textBoxes;

	//CEdit historyBox;
	//CEdit outputBox;

	char m_lastInput;
	bool m_decimalActive = false;

	std::vector<Operation> m_sum;

	void AddCharToOutput(const char);
	void AddNumberToSum(const char);
	CButton* CreateNewButton(const CString&, const CRect&, const int);
	CEdit* CreateNewEditBox(const DWORD&, const CRect&, const int);
public:
	afx_msg void OnButtonClick(UINT nID);
};
