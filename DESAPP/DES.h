/****************************************************************************
**
** Copyright (C) 2014, �ƺ��� Corporation
** All rights reserved.  
** 
** @file   DES.h
** @brief  DES�����㷨������ͷ�ļ�
**  
** Details.  
**  
** @version	1.0
** @author	�ƺ���
** @date	2014-4-26
**  
** �޶�˵����	����汾 
** 
****************************************************************************/

#ifndef DES_H
#define DES_H

#pragma once
class DES
{
public:

	/*
	@brief 

	@param    out : dest  ת�������м��洢
	@param     in : src  ת��ǰ���м��洢
	@param     in : size  Դ���м���ռ�ֽ���

	@return void
	*/
	void ByteToBit(CString &dest, CString &src, size_t size);

	/*
	@brief ������ĵ��ö��������м�ת��Ϊ�ֽ����м�

	@param    out : dest  ת�������м��洢
	@param     in : src  ת��ǰ���м��洢
	@param     in : size  Դ���м���ռ������λ��

	@return void
	*/
	void BitToByte(CString &dest, CString &src, size_t size);

	/*
	@brief ������ĵ���ʮ���������м�ת��Ϊ���ö��������м�

	@param   out : dest  ת�������м��洢
	@param    in : src  ת��ǰ���м��洢
	@param    in : size  Դ���м���ռʮ������λ��

	@return void
	*/
	void HexToBits(CString &dest, CString &src, size_t size);

	/*
	@breif ������ĵ��ö��������м�ת��Ϊ����ʮ���������м�

	@param    out : dest  ת�������м��洢
	@param     in : src  ת��ǰ���м��洢

	@return void
	*/
	void BitsToHex(CString &dest, CString &src, size_t size);

	/*
	@brief ��ʼ����Կ��������Կ��

	@param   in : src  ���������ʽ����8�ֽ���Կ���м�

	@return void
	*/
	void InitKey(CString &src);

	/*
	@brief ��ʽ��������������ı����л�ȡ����ԿΪͳһ��8�ֽ�

	@param   out : dest  ��ʽ�������Կ���м�
	@param    in : src ���ı����еõ�����Կ���м�
	@param    in : sizeBit  src��ռ���ֽ���

	@return void
	*/
	void KeyFormat(CString &dest, CString &src, size_t sizeBit);

	/*
	@brief �������ģ�8�ֽ����ķ����ʽ�������⴦��������Ķ��������м��洢��m_cliphertext

	@param  in : src  �����ԭʼ�������м�
	@param  in : sizeBit  ԭʼ������ռ�ֽ���

	@return void
	*/
	void Encrypt(CString &src, size_t sizeBit);

	/*
	@brief �������ģ�8�ֽ����ķ�������⴦��������Ķ��������м��洢��m_plaintext

	@param  in : src  �����ԭʼ�������м�
	@param  in : sizeBit  ԭʼ������ռ�ֽ���

	return void
	*/
	void Decrypt(CString &src, size_t sizeBit);

private:

	/*
	@brief ��ʼ64λ���ľ�����ʼ�û�IP

	@param   in : src  ԭ64λ�������м�
	@param  out : dest  �������ź���������м�

	@return void
	*/
	void InitPermuteData(CString &dest, CString &src);

	/*
	@brief һ�μ���8���ֽڵ�������ʱ�洢��m_curBinPlaintext

	@param  in : src  64λ��ʽ������������м�

	@return void
	*/
	void Encrypt8Byte(CString &src);

	/*
	@brief һ�ν���8���ֽڵ�������ʱ�洢��m_curBinCiphertext

	@param  in : src  64λ��ʽ������������м�

	@return void
	*/
	void Decrypt8Byte(CString &src);

	/*
	@breif ��������Կ��洢��m_DESSubkey������

	@param  in : src  ����PC_1ѡ���û�����Կ���м�

	@return void
	*/
	void CreateSubkey(CString &src);

	/*
	@brief F����

	@param  in : loopKey  ����������
	@param  in : srcL  ���ķ�����벿��
	@param  in : srcR  ���ķ����Ұ벿��

	@return void
	*/
	void FunF(CString &srcL, CString &srcR, unsigned int loopKey);

	/*
	@brief F�����е�S��

	@param   in : src  6λ������������м�
	@param  out : dest  4λ������������м�

	@return void
	*/
	void SBOX(CString &dest, CString &src);

	/*
	@brief ��intת��Ϊ���������м�

	@param   in :  src  Դintֵ
	@param  out : dest  ת����Ķ��������м�

	@return void
	*/
	void IntToBit(CString &dest, int src);

	/*
	@brief ����S�е�6λ�����ȡ4λ�����������

	@param    in �� temp 6λ������������м�
	@param   out ��row  4λ������м��к�
	@param   out : col  4λ������м��к�

	@return void
	*/
	void GetRowAndCol(int &row, int &col, CString &temp);

public:
	
	CString m_DESSubkey[16];				// ����Կ
	CString m_curBinPlaintext;				// ��ǰ����64������
	CString m_ciphertext;					// ��������
	CString m_curBinCiphertext;				// ��ǰ����64λ����
	CString m_plaintext;					// ��������
};

#endif
