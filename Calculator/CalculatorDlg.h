
// CalculatorDlg.h : header file
//

#pragma once
#include <unordered_map>

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
	CString historyTxt;
	CString OutputTxt;

	CFont font;
	//std::unordered_map<std::string, CButton> m_uiButtons;
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

	void AddDigitToOutput(char);
public:
	afx_msg void OnButtonClick(UINT nID);
	afx_msg void OnBnClickedButtonNum0();
	afx_msg void OnBnClickedButtonNum1();
	afx_msg void OnBnClickedButtonNum2();
	afx_msg void OnBnClickedButtonNum3();
	afx_msg void OnBnClickedButtonNum4();
	afx_msg void OnBnClickedButtonNum5();
	afx_msg void OnBnClickedButtonNum6();
	afx_msg void OnBnClickedButtonNum7();
	afx_msg void OnBnClickedButtonNum8();
	afx_msg void OnBnClickedButtonNum9();
};
