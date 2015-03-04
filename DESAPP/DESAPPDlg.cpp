
// DESAPPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DESAPP.h"
#include "DESAPPDlg.h"
#include "afxdialogex.h"
#include "DES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDESAPPDlg 对话框



CDESAPPDlg::CDESAPPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDESAPPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESAPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDESAPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STR_ENC, &CDESAPPDlg::OnBnClickedButtonStrEnc)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_PLAINT, &CDESAPPDlg::OnBnClickedButtonClearPlaint)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_CILPHERTEXT, &CDESAPPDlg::OnBnClickedButtonClearCilphertext)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALL, &CDESAPPDlg::OnBnClickedButtonClearAll)
	ON_BN_CLICKED(IDC_BUTTON_STR_DEC, &CDESAPPDlg::OnBnClickedButtonStrDec)
	ON_BN_CLICKED(IDC_RADIO_HEX, &CDESAPPDlg::OnBnClickedRadioHex)
	ON_BN_CLICKED(IDC_RADIO_BIN, &CDESAPPDlg::OnBnClickedRadioBin)
	ON_BN_CLICKED(IDC_RADIO_NOR, &CDESAPPDlg::OnBnClickedRadioNor)
	ON_BN_CLICKED(IDC_BUTTON_GET_PATE_SRC, &CDESAPPDlg::OnBnClickedButtonGetPateSrc)
	ON_BN_CLICKED(IDC_BUTTON_GET_PATH_DEST_, &CDESAPPDlg::OnBnClickedButtonGetPathDest)
	ON_BN_CLICKED(IDC_BUTTON_ENC_FILE, &CDESAPPDlg::OnBnClickedButtonEncFile)
	ON_BN_CLICKED(IDC_BUTTON_DEC_FILE, &CDESAPPDlg::OnBnClickedButtonDecFile)
END_MESSAGE_MAP()


// CDESAPPDlg 消息处理程序

BOOL CDESAPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	des = new DES();
	if (NULL == des)
	{
		MessageBox(_T("DES Object Init Failed !"), MB_OK);
		exit(1);
	}
	CButton *radio = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	radio->SetCheck(true);
	m_radioFlag = 1;
	CProgressCtrl *progBar = (CProgressCtrl*)GetDlgItem(IDC_PROG);
	progBar->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDESAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDESAPPDlg::OnPaint()
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
HCURSOR CDESAPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDESAPPDlg::OnBnClickedButtonStrEnc()
{
	// TODO: 在此添加控件通知处理程序代码
	//long timeBegin = GetTickCount();
	CEdit *edtKey = (CEdit*)GetDlgItem(IDC_KEY_STR);
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);

	CButton *radioHex = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	CButton *radioBin = (CButton*)GetDlgItem(IDC_RADIO_BIN);
	CButton *radioNor = (CButton*)GetDlgItem(IDC_RADIO_NOR);

	CString strKey = _T("");
	CString strPlaintext = _T("");
	CString strCiphertext = _T("");

	edtKey->GetWindowText(strKey);
	edtPlaintext->GetWindowText(strPlaintext);
	
	m_DESKey = _T("");
	size_t lenKey = strKey.GetLength();
	des->KeyFormat(m_DESKey, strKey, lenKey);
	des->InitKey(m_DESKey);
	edtCiphertext->SetWindowText(_T(""));

	size_t plaintextLen = strPlaintext.GetLength();
	CString curPlaintext = _T("");
	des->ByteToBit(curPlaintext, strPlaintext, plaintextLen);
	
	size_t curPlaintextLen = curPlaintext.GetLength();
	des->Encrypt(curPlaintext, curPlaintextLen);
	m_ciphertextData = _T("");
	if (radioHex->GetCheck())
	{
		des->BitsToHex(m_ciphertextData, des->m_ciphertext, des->m_ciphertext.GetLength());
		m_radioFlag = 1;
	}
	else if (radioBin->GetCheck())
	{
		m_ciphertextData = des->m_ciphertext;
		m_radioFlag = 2;
	}
	else if (radioNor->GetCheck())
	{
		m_radioFlag = 3;
		des->BitToByte(m_ciphertextData, des->m_ciphertext, des->m_ciphertext.GetLength());
		/*
		CString ch = _T("");
		int sum = 0;
		for(int i = 0; i < des->m_ciphertext.GetLength();)
		{
			ch = _T("");
			sum = (des->m_ciphertext[i] == L'0' ? 0 : 1) + (des->m_ciphertext[i + 1] == L'0' ? 0 : 2) 
				   + (des->m_ciphertext[i + 2] == L'0' ? 0 : 4) + (des->m_ciphertext[i + 3] == L'0' ? 0 : 8)
				   + (des->m_ciphertext[i + 4] == L'0' ? 0 : 16) + (des->m_ciphertext[i + 5] == L'0' ? 0 : 32)
				   + (des->m_ciphertext[i + 6] == L'0' ? 0 : 64) + (des->m_ciphertext[i + 7] == L'0' ? 0 : 128);
			ch.Format(_T("%c"), sum);
			m_ciphertextData += ch;
			i += 8;
		}
		*/
	}
	edtCiphertext->SetWindowTextW(m_ciphertextData);
	/*
	long timeEnd = GetTickCount();
	long runTime = timeEnd  - timeBegin;
	CString timeStr = _T("");
	timeStr.Format(_T("time: %dms"), runTime);
	MessageBox(timeStr);
	*/
}

void CDESAPPDlg::OnBnClickedButtonClearPlaint()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonClearCilphertext()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonClearAll()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	edt->SetWindowTextW(_T(""));
	edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	edt->SetWindowTextW(_T(""));
	edt = (CEdit*)GetDlgItem(IDC_KEY_STR);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonStrDec()
{
	// TODO: 在此添加控件通知处理程序代码
	//long timeBegin = GetTickCount();
	CEdit *edtKey = (CEdit*)GetDlgItem(IDC_KEY_STR);
	CEdit *edtPlaintext = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	CEdit *edtCiphertext = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);

	CButton *radioHex = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	CButton *radioBin = (CButton*)GetDlgItem(IDC_RADIO_BIN);
	CButton *radioNor = (CButton*)GetDlgItem(IDC_RADIO_NOR);

	CString strKey = _T("");
	CString strPlaintext = _T("");
	CString strCiphertext = _T("");

	edtKey->GetWindowText(strKey);
	edtCiphertext->GetWindowText(strCiphertext);

	m_DESKey = _T("");
	edtPlaintext->SetWindowTextW(_T(""));
	
	size_t lenKey = strKey.GetLength();
	des->KeyFormat(m_DESKey, strKey, lenKey);
	des->InitKey(m_DESKey);
	
	size_t ciphertextLen = strCiphertext.GetLength();
	CString curCiphertext = _T("");

	if (radioHex->GetCheck())
	{
		des->HexToBits(curCiphertext, strCiphertext, ciphertextLen);
		m_radioFlag = 1;
	}
	else if (radioBin->GetCheck())
	{
		curCiphertext = strCiphertext;
		m_radioFlag = 2;
	}
	else if (radioNor->GetCheck())
	{
		des->ByteToBit(curCiphertext, strCiphertext, ciphertextLen);
		m_radioFlag = 3;
	}
	size_t curCiphertextLen = curCiphertext.GetLength();
	des->Decrypt(curCiphertext, curCiphertextLen);
	m_plaintextData = _T("");
	des->BitToByte(m_plaintextData, des->m_plaintext, des->m_plaintext.GetLength());
	edtPlaintext->SetWindowTextW(m_plaintextData);
	//long timeEnd = GetTickCount();
	//long runTime = timeEnd - timeBegin;
	//CString timeStr = _T("");
	//timeStr.Format(_T("runtime : %dms"), runTime);
	//MessageBox(timeStr);
}

void CDESAPPDlg::OnBnClickedRadioHex()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	CString cipherFrom;
	CString cipherTo = _T("");
	edt->GetWindowTextW(cipherFrom);
	if (m_radioFlag == 2)
	{
		des->BitsToHex(cipherTo, cipherFrom, cipherFrom.GetLength());
	}
	else if (m_radioFlag == 3)
	{
		des->ByteToBit(cipherTo, cipherFrom, cipherFrom.GetLength());
		cipherFrom = _T("");
		des->BitsToHex(cipherFrom, cipherTo, cipherTo.GetLength());
		cipherTo = _T("");
		cipherTo = cipherFrom;
	}
	edt->SetWindowTextW(cipherTo);
	m_radioFlag = 1;
}

void CDESAPPDlg::OnBnClickedRadioBin()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	CString cipherFrom;
	CString cipherTo = _T("");
	edt->GetWindowTextW(cipherFrom);
	if (m_radioFlag == 1)
	{
		des->HexToBits(cipherTo, cipherFrom, cipherFrom.GetLength());
	}
	else if (m_radioFlag == 3)
	{
		des->ByteToBit(cipherTo, cipherFrom, cipherFrom.GetLength());
	}
	edt->SetWindowTextW(cipherTo);
	m_radioFlag = 2;
}

void CDESAPPDlg::OnBnClickedRadioNor()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	CString cipherFrom;
	CString cipherTo = _T("");
	edt->GetWindowTextW(cipherFrom);
	if (m_radioFlag == 1)
	{
		des->HexToBits(cipherTo, cipherFrom, cipherFrom.GetLength());
		cipherFrom = _T("");
		des->BitToByte(cipherFrom, cipherTo, cipherTo.GetLength());
		cipherTo = _T("");
		cipherTo = cipherFrom;
	}
	else if (m_radioFlag == 2)
	{
		des->BitToByte(cipherTo, cipherFrom, cipherFrom.GetLength());
	}
	edt->SetWindowTextW(cipherTo);
	m_radioFlag = 3;
}

void CDESAPPDlg::OnBnClickedButtonGetPateSrc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	CFileDialog dlg(TRUE);// TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal() == IDOK)
	{
		filePath = dlg.GetPathName();
		CEdit *edt = (CEdit*)GetDlgItem(IDC_PATH_SRC);
		edt->SetWindowTextW(filePath);
	}
}

void CDESAPPDlg::OnBnClickedButtonGetPathDest()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath;
	CFileDialog dlg(TRUE);
	if(dlg.DoModal() == IDOK)
	{
		filePath = dlg.GetPathName();
		CEdit *edt = (CEdit*)GetDlgItem(IDC_PATH_DEST);
		edt->SetWindowTextW(filePath);
	}
}

void CDESAPPDlg::OnBnClickedButtonEncFile()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flagFileOPen = true;
	CEdit *edt = (CEdit*)GetDlgItem(IDC_PATH_SRC);
	CString str;
	CFile file;
	while(flagFileOPen)
	{
		
		edt->GetWindowTextW(str);
		file.Open(str,CFile::modeRead);
		if(file == NULL)
		{
			MessageBox(_T("打开源文件失败，请选择正确文件后重试"));
			flagFileOPen = true;
		}
		else
		{
			flagFileOPen = false;
		}
	}
	//long timeBegin  = GetTickCount();
	char *pBuf;
	DWORD dwFileLen;
    dwFileLen=file.GetLength();
    pBuf=new char[dwFileLen+1];
    pBuf[dwFileLen]=0;
	file.Read(pBuf, dwFileLen);
    file.Close();

	edt = (CEdit*)GetDlgItem(IDC_KEY_FILE);
	CString strKey;
	edt->GetWindowTextW(strKey);
	
	m_DESKey = _T("");
	size_t lenKey = strKey.GetLength();
	des->KeyFormat(m_DESKey, strKey, lenKey);
	des->InitKey(m_DESKey);

	CString strPlaintext = _T("");
	char *temp = pBuf;
	size_t size = strlen(pBuf);
	CString ch;
	for(int i = 0; i < size; ++i)
	{
		ch = _T("");
		ch.Format(_T("%c"), temp[i]);
		strPlaintext += ch;
	}
	size_t plaintextLen = strPlaintext.GetLength();

	CString curPlaintext = _T("");
	des->ByteToBit(curPlaintext, strPlaintext, plaintextLen);
	size_t curPlaintextLen = curPlaintext.GetLength();
	des->Encrypt(curPlaintext, curPlaintextLen);
	m_ciphertextData = _T("");
	m_ciphertextData = des->m_ciphertext;
	flagFileOPen = true;
	CString destPath = _T("");
	edt = (CEdit*)GetDlgItem(IDC_PATH_DEST);
	while (flagFileOPen)
	{
		edt->GetWindowTextW(destPath);
		file.Open(destPath, CFile::modeWrite);
		if(file == NULL)
		{
			MessageBox(_T("打开目的文件失败，请选择正确文件后重试"));
			flagFileOPen = true;
		}
		else
		{
			flagFileOPen = false;
		}
	}
	file.Write(m_ciphertextData.GetBuffer(m_ciphertextData.GetLength()), m_ciphertextData.GetLength()*2);
	m_ciphertextData.ReleaseBuffer();
	file.Close();
	MessageBox(_T("加密完成！"));
	delete []pBuf;
	pBuf = NULL;
	//long timeEnd = GetTickCount();
	//long runTime = timeEnd - timeBegin;
	//CString timeStr = _T("");
	//timeStr.Format(_T("runtime : %dms"), runTime);
	//MessageBox(timeStr);
}

void CDESAPPDlg::OnBnClickedButtonDecFile()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flagFileOPen = true;
	CEdit *edt = (CEdit*)GetDlgItem(IDC_PATH_SRC);
	CString str;
	CFile file;
	while(flagFileOPen)
	{
		edt->GetWindowTextW(str);
		file.Open(str,CFile::modeRead);
		if(file == NULL)
		{
			MessageBox(_T("打开源文件失败，请选择正确文件后重试"));
			flagFileOPen = true;
		}
		else
		{
			flagFileOPen = false;
		}
	}
	//long timeBegin = GetTickCount();
	char *pBuf;
	DWORD dwFileLen=file.GetLength();
    pBuf=new char[dwFileLen+1];
    pBuf[dwFileLen] = '\0';

	file.Read(pBuf,dwFileLen);
    file.Close();

	edt = (CEdit*)GetDlgItem(IDC_KEY_FILE);
	CString strKey;
	edt->GetWindowTextW(strKey);
	
	m_DESKey = _T("");
	size_t lenKey = strKey.GetLength();
	des->KeyFormat(m_DESKey, strKey, lenKey);
	des->InitKey(m_DESKey);

	CString curCiphertext = _T("");
	char *temp = pBuf;
	CString ch = _T("");
	for(int i = 0; i < dwFileLen; ++i)
	{
		ch = _T("");
		ch.Format(_T("%c"), temp[i]);
		curCiphertext += ch;
	}
	size_t curCiphertextLen = curCiphertext.GetLength();
	des->Decrypt(curCiphertext, curCiphertextLen);
	m_ciphertextData = _T("");
	des->BitToByte(m_plaintextData, des->m_plaintext, des->m_plaintext.GetLength());

	flagFileOPen = true;
	CString destPath = _T("");
	edt = (CEdit*)GetDlgItem(IDC_PATH_DEST);
	while (flagFileOPen)
	{
		edt->GetWindowTextW(destPath);
		file.Open(destPath, CFile::modeWrite);
		if(file == NULL)
		{
			MessageBox(_T("打开目的文件失败，请选择正确文件后重试"));
			flagFileOPen = true;
		}
		else
		{
			flagFileOPen = false;
		}
	}

	MessageBox(m_plaintextData);

	file.Write(m_plaintextData.GetBuffer(m_plaintextData.GetLength()/2), m_plaintextData.GetLength()*2);
	m_plaintextData.ReleaseBuffer();
	file.Close();

	delete []pBuf;
	pBuf = NULL;

	//long timeEnd = GetTickCount();
	//long runTime = timeEnd - timeBegin;
	//CString timeStr = _T("");
	//timeStr.Format(_T("runtime : %dms"), runTime);
	//MessageBox(timeStr);
}
