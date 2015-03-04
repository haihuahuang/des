
// DESAPPDlg.h : ͷ�ļ�
//

#pragma once

#include "DES.h"

// CDESAPPDlg �Ի���
class CDESAPPDlg : public CDialogEx
{
// ����
public:
	CDESAPPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	DES *des;

	CString m_DESKey;				// ���ı����л�ȡ����Կ
	CString m_plaintextData;		// ����
	CString m_ciphertextData;		// ����
	int        m_radioFlag;				// 1--Hex  2--Bin 3--Nor

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGo();
	afx_msg void OnBnClickedButtonStrEnc();
	afx_msg void OnBnClickedButtonClearPlaint();
	afx_msg void OnBnClickedButtonClearCilphertext();
	afx_msg void OnBnClickedButtonClearAll();
	afx_msg void OnBnClickedButtonStrDec();
	afx_msg void OnBnClickedRadioHex();
	afx_msg void OnBnClickedRadioBin();
	afx_msg void OnBnClickedRadioNor();
	afx_msg void OnBnClickedButtonGetPateSrc();
	afx_msg void OnBnClickedButtonGetPathDest();
	afx_msg void OnBnClickedButtonEncFile();
	afx_msg void OnBnClickedButtonDecFile();
};
