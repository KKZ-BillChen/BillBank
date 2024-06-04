// bank-guiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "bank-gui.h"
#include "bank-guiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CbankguiDlg 对话框
HBRUSH CbankguiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH   hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	pDC->SetTextColor(RGB(0, 0, 0));
	CString text;
	if (IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD == pWnd->GetDlgCtrlID() || IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME == pWnd->GetDlgCtrlID() || IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2 == pWnd->GetDlgCtrlID() || IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE == pWnd->GetDlgCtrlID()) {
		if (IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD == pWnd->GetDlgCtrlID()){
			GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD)->GetWindowText(text);
			if (text == Err(Succeed))
				pDC->SetTextColor(RGB(0, 255, 0));
			else
				pDC->SetTextColor(RGB(0, 255, 0));
		}
		if (IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2 == pWnd->GetDlgCtrlID()) {
			GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2)->GetWindowText(text);
			if (text == Err(Succeed))
				pDC->SetTextColor(RGB(0, 255, 0));
			else
				pDC->SetTextColor(RGB(0, 255, 0));
		}
		if (IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME == pWnd->GetDlgCtrlID()) {
			GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME)->GetWindowText(text);
			if (text == Err(Succeed))
				pDC->SetTextColor(RGB(0, 255, 0));
			else
				pDC->SetTextColor(RGB(0, 255, 0));
		}
		if (IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE == pWnd->GetDlgCtrlID()) {
			GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE)->GetWindowText(text);
			if (text == "Legitimate")
				pDC->SetTextColor(RGB(0, 255, 0));
			else
				pDC->SetTextColor(RGB(0, 255, 0));
		}
	}
	else {
		
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hBrush;
}


CbankguiDlg::CbankguiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BANKGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbankguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CbankguiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ENTER, &CbankguiDlg::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_NEW_ACCOUNT, &CbankguiDlg::OnBnClickedButtonNewAccount)
	ON_BN_CLICKED(IDC_CHECK_TO_SEE, &CbankguiDlg::OnBnClickedCheckToSee)
	ON_BN_CLICKED(IDC_CHECK_TO_SEE2, &CbankguiDlg::OnBnClickedCheckToSee2)
	ON_BN_CLICKED(IDC_RADIO_OKRA, &CbankguiDlg::OnBnClickedRadioOkra)
	ON_BN_CLICKED(IDC_RADIO_HOLLYHOCK, &CbankguiDlg::OnBnClickedRadioHollyhock)
	ON_BN_CLICKED(IDC_RADIO_NIGHTSHADE, &CbankguiDlg::OnBnClickedRadioNightshade)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CbankguiDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_NEW_ACCOUNT_NEXT, &CbankguiDlg::OnBnClickedButtonNewAccountNext)
	ON_EN_CHANGE(IDC_EDIT_NEW_ACCOUNT_USERNAME, &CbankguiDlg::OnEnChangeEditNewUserName)
	ON_EN_CHANGE(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD, &CbankguiDlg::OnEnChangeEditNewUserPassword)
	ON_EN_CHANGE(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2, &CbankguiDlg::OnEnChangeEditNewUserPassword2)
	ON_EN_CHANGE(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE, &CbankguiDlg::OnEnChangeEditNewInitialBalance)
END_MESSAGE_MAP()

// CbankguiDlg 消息处理程序
BOOL CbankguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cfont[0].CreatePointFont(145, _T("Consolas"), NULL);
	cfont[1].CreatePointFont(126, _T("Consolas"), NULL);
	btn[0].Create(_T("Enter"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(655, 465, 735, 495), this, IDC_BUTTON_ENTER);
	btn[1].Create(_T("New Account"), WS_CHILD | BS_PUSHBUTTON, CRect(615, 465, 735, 495), this, IDC_BUTTON_NEW_ACCOUNT);
	btn[2].Create(_T("User Login"), WS_CHILD | BS_PUSHBUTTON, CRect(340, 180, 460, 210), this, IDC_BUTTON_USER_LOGIN);
	btn[3].Create(_T("Manager Login"), WS_CHILD | BS_PUSHBUTTON, CRect(340, 220, 460, 250), this, IDC_BUTTON_MANAGER_LOGIN);
	btn[4].Create(_T("Help"), WS_CHILD | BS_PUSHBUTTON, CRect(740, 465, 820, 495), this, IDC_BUTTON_BANK_DETAILS);
	btn[5].Create(_T("Okra"), WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, CRect(10, 122, 110, 142), this, IDC_RADIO_OKRA);
	btn[6].Create(_T("Hollyhock"), WS_CHILD | BS_AUTORADIOBUTTON, CRect(130, 122, 230, 142), this, IDC_RADIO_HOLLYHOCK);
	btn[7].Create(_T("Nightshade"), WS_CHILD | BS_AUTORADIOBUTTON, CRect(250, 122, 350, 142), this, IDC_RADIO_NIGHTSHADE);
	btn[8].Create(_T("○"), WS_CHILD | BS_AUTOCHECKBOX, CRect(350, 42, 400, 62), this, IDC_CHECK_TO_SEE);
	btn[9].Create(_T("○"), WS_CHILD | BS_AUTOCHECKBOX, CRect(350, 64, 400, 84), this, IDC_CHECK_TO_SEE2);
	btn[10].Create(_T("Choose User Type"), WS_CHILD | BS_GROUPBOX, CRect(5, 105, 355, 150), this, IDC_GROUP_USER_TYPE);
	btn[11].Create(_T("Next"), WS_CHILD | BS_PUSHBUTTON, CRect(655, 465, 735, 495), this, IDC_BUTTON_NEW_ACCOUNT_NEXT);
	btn[12].Create(_T("Help"), WS_CHILD | BS_PUSHBUTTON, CRect(740, 465, 820, 495), this, IDC_BUTTON_NEW_ACCOUNT_HELP);
	btn[13].Create(_T("Cancel"), WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON, CRect(740, 465, 820, 495), this, IDC_BUTTON_CANCEL);
	txt[0].Create(_T("BILL'S BANK\n┏━━━━━━━━━━━━━━━━━━┓\n┃                  ┃\n┃       BIL        ┃\n┃    MANAGEMENT    ┃\n┃      SYSTEM      ┃\n┃                  ┃\n┗━━━━━━━━━━━━━━━━━━┛\nMADE BY : BILL CHEN"), SS_CENTER | WS_CHILD | WS_VISIBLE, CRect(250, 80, 900, 350), this, IDC_STATIC_ENTER);
	txt[1].Create(_T("Enter User Name  : \nEnter Password   : \nConfirm Password : \nInitial Balance  : "), WS_CHILD | SS_LEFT, CRect(10, 20, 195, 400), this, IDC_STATIC_NEW_ACCOUNT);
	txt[2].Create(_T("BIL >= 666"), WS_CHILD | SS_LEFT, CRect(355, 64, 500, 84), this, IDC_STATIC_INITIAL_BALANCE);
	txt[4].Create(_T("--- MAIN MENU ---"), WS_CHILD | SS_LEFT, CRect(10, 30, 500, 115), this, IDC_STATIC_TITLE);
	txt[5].Create(_T(""), WS_CHILD | SS_LEFT, CRect(355, 20, 1000, 40), this, IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME);
	txt[6].Create(_T(""), WS_CHILD | SS_LEFT, CRect(405, 44, 1000, 62), this, IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD);
	txt[7].Create(_T(""), WS_CHILD | SS_LEFT, CRect(405, 66, 1000, 84), this, IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2);
	txt[8].Create(_T(""), WS_CHILD | SS_LEFT, CRect(405, 88, 1000, 106), this, IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE);
	edt[0].Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_TABSTOP, CRect(200, 20, 325, 40), this, IDC_EDIT_NEW_ACCOUNT_USERNAME);
	edt[1].Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_TABSTOP | ES_PASSWORD, CRect(200, 42, 325, 62), this, IDC_EDIT_NEW_ACCOUNT_USERPASSWORD);
	edt[2].Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_CHILD | WS_TABSTOP | ES_PASSWORD, CRect(200, 64, 325, 84), this, IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2);
	edt[3].Create(WS_CHILD | ES_LEFT | ES_AUTOHSCROLL | WS_TABSTOP | WS_BORDER | ES_NUMBER, CRect(200, 86, 350, 106), this, IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE);
	CBitmap btm;
	btm.LoadBitmapW(IDB_BITMAP1);
	BITMAP bitmap;
	btm.GetBitmap(&bitmap);
	txt[3].Create(L"", WS_CHILD | SS_BITMAP | SS_CENTERIMAGE, CRect(0, 0, 420, 520), this, IDC_IMAGE_1);
	//cpp文件
	((CStatic*)GetDlgItem(IDC_IMAGE_1))->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1)));
	GetDlgItem(IDC_IMAGE_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_ENTER)->SetFont(&cfont[0]);
	GetDlgItem(IDC_STATIC_NEW_ACCOUNT)->SetFont(&cfont[1]);	
	//GetDlgItem(IDC_BUTTON_ENTER)->ModifyStyle(0, BST_CHECKED);
	//((CButton*)GetDlgItem(IDC_BUTTON_ENTER))->SetCheck(TRUE);
	//GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_BUTTON_ENTER)->ShowWindow(SW_SHOW);
	//GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);*/
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CbankguiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbankguiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbankguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CbankguiDlg::main_menu() {
	//Invalidate(TRUE);
	GetDlgItem(IDC_BUTTON_ENTER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IMAGE_1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_ENTER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_NEW_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_USER_LOGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_MANAGER_LOGIN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_BANK_DETAILS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_BANK_DETAILS)->ModifyStyle(0, BST_CHECKED);
}
	
void CbankguiDlg::OnBnClickedButtonEnter()
{
	// TODO: 在此添加控件通知处理程序代码
	main_menu();
	//((CButton*)GetDlgItem(IDC_BUTTON_BANK_DETAILS))->SetCheck(TRUE);
	
}
//void Invalidate(BOOL bErase = TRUE);
void CbankguiDlg::OnBnClickedButtonNewAccount() {
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_RADIO_OKRA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO_HOLLYHOCK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_RADIO_NIGHTSHADE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_NEW_ACCOUNT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_USER_LOGIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_MANAGER_LOGIN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_BANK_DETAILS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_NEW_ACCOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERNAME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK_TO_SEE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK_TO_SEE2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_GROUP_USER_TYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_NEW_ACCOUNT_NEXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_NEW_ACCOUNT_HELP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_NEW_ACCOUNT_HELP)->ModifyStyle(0, BST_CHECKED);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE)->ShowWindow(SW_SHOW);
}
void CbankguiDlg::OnBnClickedCheckToSee() {
	//UpdateWindow();
	//int state = ((CButton*)GetDlgItem(IDC_CHECK_TO_SEE))->GetCheck();
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_TO_SEE))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD))->SetPasswordChar(0);
		Invalidate(FALSE);
	}
	else // 取消选中
	{
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD))->SetPasswordChar(L'●');
		Invalidate(FALSE);
	}
}
void CbankguiDlg::OnBnClickedCheckToSee2() {
	//UpdateData(TRUE);
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_TO_SEE2))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2))->SetPasswordChar(0);
		Invalidate(FALSE);
	}
	else // 取消选中
	{
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2))->SetPasswordChar(L'●');
		Invalidate(FALSE);
	}
}
void CbankguiDlg::OnBnClickedRadioOkra() { 
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_OKRA)) {
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_STATIC_INITIAL_BALANCE))->SetWindowTextW(L"BIL ( >= 500 )");
		GetDlgItem(IDC_STATIC_INITIAL_BALANCE)->ShowWindow(SW_SHOW);
		Invalidate();
	}
}
void CbankguiDlg::OnBnClickedButtonNewAccountNext() {
	CString user_name;
	CString user_password;
	CString user_password2;
	CString ini_balance;
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE)->GetWindowText(ini_balance);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERNAME)->GetWindowText(user_name);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD)->GetWindowText(user_password);
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2)->GetWindowText(user_password2);
	if ((BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_OKRA) || BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_NIGHTSHADE) || BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_HOLLYHOCK)) && (Account::validate((LPCSTR(user_name.GetBuffer(0)))) && (Account::validate(LPCSTR(user_password.GetBuffer())) && (Account::validate((LPCSTR((user_password2.GetBuffer())))))))) {
		((CEdit*)GetDlgItem(IDC_BUTTON_NEW_ACCOUNT_NEXT))->EnableWindow(TRUE);
	}
}
void CbankguiDlg::OnBnClickedRadioHollyhock() {
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_HOLLYHOCK)) {
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_STATIC_INITIAL_BALANCE))->SetWindowTextW(L"BIL ( >= 50000 )");
		GetDlgItem(IDC_STATIC_INITIAL_BALANCE)->ShowWindow(SW_SHOW);
		Invalidate();
	}
}
void CbankguiDlg::OnBnClickedRadioNightshade() {
	if (BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_NIGHTSHADE)) { 
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_ACCOUNT_INITIALBALANCE))->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_STATIC_INITIAL_BALANCE))->SetWindowTextW(L"BIL ( >= 500000 )");
		GetDlgItem(IDC_STATIC_INITIAL_BALANCE)->ShowWindow(SW_SHOW);
		Invalidate();
	}
}
void CbankguiDlg::OnBnClickedButtonExit() {
	OnOK();
}
void CbankguiDlg::OnEnChangeEditNewUserName(){
	UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME)->ShowWindow(SW_SHOW);
	CString text;
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERNAME)->GetWindowText(text);
	if(!Account::validate(LPCSTR(text.GetBuffer())))
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME)->SetWindowText(Err(Err_Input_Name));
	else
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERNAME)->SetWindowText(Err(Succeed));
}
void CbankguiDlg::OnEnChangeEditNewUserPassword() {
	UpdateData(TRUE);
	CString text;
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD)->GetWindowText(text);
	GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD)->ShowWindow(SW_SHOW);
	if ((text.GetLength() < 6)) {
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD)->SetWindowText(Err(Err_Pswd_Length));
	}
	else if (!Account::validate(LPCSTR(text.GetBuffer()))) {
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD)->SetWindowText(Err(Err_Pswd));
	}
	else
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD)->SetWindowText(Err(Succeed));
}
void CbankguiDlg::OnEnChangeEditNewUserPassword2() {
	UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2)->ShowWindow(SW_SHOW);
	CString text;
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD)->GetWindowText(text);
	CString text2;
	GetDlgItem(IDC_EDIT_NEW_ACCOUNT_USERPASSWORD2)->GetWindowText(text2);
	if(text != text2)
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2)->SetWindowText(Err(Err_Pswd_Unmatched));
	else
		GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_USERPASSWORD2)->SetWindowText(Err(Succeed));
}
void CbankguiDlg::OnEnChangeEditNewInitialBalance() {
	GetDlgItem(IDC_STATIC_NEW_ERR_ACCOUNT_INITIALBALANCE)->ShowWindow(SW_SHOW);
}
CString CbankguiDlg::Err(BankError err) {
	switch (err) {
	case Succeed:
		return L"Legitimate!";
		break;
	case Err_Initial_Balance_Match_Type:
		return L"Err! Unmatched User Type And Initial Balance!";
		break;
	case Err_Input_Name:
		return L"Err! Character '|' In User Name Is Illegal!";
		break;
	case Err_Nofile:
		return L"Err! Failed To Read From File!";
		break;
	case Err_Over_Draft:
		return L"Err! OverDrafted Is Not Allowed!";
		break;
	case Err_Over_Loan:
		return L"Err! OverLoan Is Not Allowed!";
		break;
	case Err_Negative_Loan:
		return L"Err! Negative Loans Is Not Allowed!";
		break;
	case Err_Pswd:
		return L"Err! Character '|' In User Password Is Illegal!";
		break;
	case Err_Pswd_Length:
		return L"Err! Password Length Should > 6!";
		break;
	case Err_Pswd_Unmatched:
		return L"Err! Unmatched Password!";
		break;
		/*case Err_Noid:
			std::cout << "ERROR ! CAN NOT FIND THE ID !" << endl;
			break;
		case Err_lock:
			std::cout << "SORRY ! THE ACCOUNT IS LOCKED NOW !" << endl;
			break;
		case Err_Negative_Amount:
			std::cout << "ERROR ! NEGATIVE BALANCE IS NOT ALLOWED ! " << endl;
			break;
		case Err_Login_User_Pswd:
			std::cout << "ERROR ! FAILED TO LOGIN USER ! " << endl;
			break;
		case Err_NoType:
			std::cout << "ERROR ! NO THIS TYPE ! " << endl;
			break;
		case Err_Manager_Login:
			std::cout << "ERROR ! YOU FAILED TO LOGIN MANGER ! " << endl;
			break;
		case Err_already_lock:
			std::cout << "ERROR ! THA ACCOUNT WAS ALREADY LOCKED ! " << endl;
			break;
		case Err_already_unlock:
			std::cout << "ERROR ! THA ACCOUNT WAS ALREADY UNLOCKED ! " << endl;
			break;
		case Err_seen_used_password:
			std::cout << "ERROR ! PLEASE USE DIFFERENT PASSWORD ! " << endl;
			break;
		case Err_seen_modify_details:
			std::cout << "ERROR ! PLEASE USE DIFFERENT DETAILS ! " << endl;
			break;
		case Err_balance_loan_no_clear:
			std::cout << "ERROR ! LOAN AND BALANCE HAVE NOT BE CLEAND ! " << endl;
			break;
		case Err_FullMessage:
			std::cout << "ERROR ! YOU TARGET IS FULL MESSAGE ! " << endl;
			break;
		case Err_ID_Message:
			std::cout << "ERROR ! YOU CAN NOT SEND MESSAGE TO YOURSELF !" << endl;
			break;
		default:
			std::cout << "UNKNOWN ERROR !" << endl;
			break;
		}*/
	}
}