
// bank-guiDlg.h: 头文件
//

#pragma once 

#include "..\proto\bank.pb.h"
#include "..\common\container.h"
#include "..\common\Account.h"
#include "..\common\client\service.h"

#define IDC_BUTTON_ENTER 1000
#define IDC_BUTTON_NEW_ACCOUNT 1001
#define IDC_STATIC_ENTER 1002
#define IDC_BUTTON_USER_LOGIN 1003
#define IDC_BUTTON_MANAGER_LOGIN 1004
#define IDC_BUTTON_BANK_DETAILS 1005
#define IDC_STATIC_NEW_ACCOUNT 1006
#define IDC_EDIT_NEW_ACCOUNT_USERNAME 1007
#define IDC_EDIT_NEW_ACCOUNT_USERPASSWORD 1008
#define IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2 1009
#define IDC_RADIO_OKRA 1010
#define IDC_RADIO_HOLLYHOCK 1011
#define IDC_RADIO_NIGHTSHADE 1012
#define IDC_CHECK_TO_SEE 1020
#define IDC_CHECK_TO_SEE2 1021
#define IDC_GROUP_USER_TYPE 1022
#define IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE 1023
#define IDC_STATIC_INITIAL_BALANCE 1024
#define IDC_BUTTON_NEW_ACCOUNT_NEXT 1025
#define IDC_BUTTON_NEW_ACCOUNT_HELP 1026
#define IDC_IMAGE_1 1027
#define IDC_BUTTON_CANCEL 1028
#define IDC_STATIC_TITLE 1029
#define IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME 1030
#define IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD 1031
#define IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2 1032
#define IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE 1033

// CbankguiDlg 对话框
class CbankguiDlg : public CDialogEx
{
// 构造
public:
	CbankguiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANKGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont cfont[250];
	CButton btn[250];
	CStatic txt[250];
	CEdit edt[250];
	// 生成的消息映射函数
	
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	void main_menu();
	CString Err(BankError err);
	//CButton* NewMyButton(int nID, CRect rect, int nStyle);
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonNewAccount();
	afx_msg void OnBnClickedCheckToSee();
	afx_msg void OnBnClickedCheckToSee2();
	afx_msg void OnBnClickedRadioOkra();
	afx_msg void OnBnClickedRadioHollyhock();
	afx_msg void OnBnClickedRadioNightshade();
	afx_msg void OnBnClickedButtonNewAccountNext();
	afx_msg void OnEnChangeEditNewUserName();
	afx_msg void OnEnChangeEditNewUserPassword();
	afx_msg void OnEnChangeEditNewUserPassword2();
	afx_msg void OnEnChangeEditNewInitialBalance();

};
