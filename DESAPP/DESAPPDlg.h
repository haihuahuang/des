
// DESAPPDlg.h : 头文件
//

#pragma once

#include "DES.h"

// CDESAPPDlg 对话框
class CDESAPPDlg : public CDialogEx
{
// 构造
public:
	CDESAPPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DESAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	DES *des;

	CString m_DESKey;				// 从文本框中获取的密钥
	CString m_plaintextData;		// 明文
	CString m_ciphertextData;		// 密文
	int        m_radioFlag;				// 1--Hex  2--Bin 3--Nor

	// 生成的消息映射函数
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
