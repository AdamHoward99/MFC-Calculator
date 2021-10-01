
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
	std::vector<CButton> m_uiButtons;
	CButton num0;
	CButton num1;
	CButton num2;
	CButton num3;
	CButton num4;
	CButton num5;
	CButton num6;
	CButton num7;
	CButton num8;
	CButton num9;
	CButton clearButton;
	CButton decimalButton;
	CButton divideButton;
	CButton equalsButton;
	CButton minusButton;
	CButton multiplyButton;
	CButton addButton;

	CEdit historyBox;
	CEdit outputBox;

	char m_lastInput;

	std::vector<Operation> m_sum;

	void AddCharToOutput(const char);
	void AddNumberToSum(const char);

public:
	afx_msg void OnButtonClick(UINT nID);
};
