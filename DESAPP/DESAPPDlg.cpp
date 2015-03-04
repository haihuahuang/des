
// DESAPPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DESAPP.h"
#include "DESAPPDlg.h"
#include "afxdialogex.h"
#include "DES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDESAPPDlg �Ի���



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


// CDESAPPDlg ��Ϣ�������

BOOL CDESAPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDESAPPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDESAPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDESAPPDlg::OnBnClickedButtonStrEnc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonClearCilphertext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonClearAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit *edt = (CEdit*)GetDlgItem(IDC_STR_PLAINTEXT);
	edt->SetWindowTextW(_T(""));
	edt = (CEdit*)GetDlgItem(IDC_STR_CIPHERTEXT);
	edt->SetWindowTextW(_T(""));
	edt = (CEdit*)GetDlgItem(IDC_KEY_STR);
	edt->SetWindowTextW(_T(""));
}

void CDESAPPDlg::OnBnClickedButtonStrDec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filePath;
	CFileDialog dlg(TRUE);// TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal() == IDOK)
	{
		filePath = dlg.GetPathName();
		CEdit *edt = (CEdit*)GetDlgItem(IDC_PATH_SRC);
		edt->SetWindowTextW(filePath);
	}
}

void CDESAPPDlg::OnBnClickedButtonGetPathDest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox(_T("��Դ�ļ�ʧ�ܣ���ѡ����ȷ�ļ�������"));
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
			MessageBox(_T("��Ŀ���ļ�ʧ�ܣ���ѡ����ȷ�ļ�������"));
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
	MessageBox(_T("������ɣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox(_T("��Դ�ļ�ʧ�ܣ���ѡ����ȷ�ļ�������"));
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
			MessageBox(_T("��Ŀ���ļ�ʧ�ܣ���ѡ����ȷ�ļ�������"));
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
