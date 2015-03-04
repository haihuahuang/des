/****************************************************************************
**
** Copyright (C) 2014, 黄海华 Corporation
** All rights reserved.  
** 
** @file   DES.h
** @brief  DES加密算法工具类头文件
**  
** Details.  
**  
** @version	1.0
** @author	黄海华
** @date	2014-4-26
**  
** 修订说明：	最初版本 
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

	@param    out : dest  转换后序列集存储
	@param     in : src  转换前序列集存储
	@param     in : size  源序列集所占字节数

	@return void
	*/
	void ByteToBit(CString &dest, CString &src, size_t size);

	/*
	@brief 将输入的倒置二进制序列集转换为字节序列集

	@param    out : dest  转换后序列集存储
	@param     in : src  转换前序列集存储
	@param     in : size  源序列集所占二进制位数

	@return void
	*/
	void BitToByte(CString &dest, CString &src, size_t size);

	/*
	@brief 将输入的倒置十六进制序列集转换为倒置二进制序列集

	@param   out : dest  转换后序列集存储
	@param    in : src  转换前序列集存储
	@param    in : size  源序列集所占十六进制位数

	@return void
	*/
	void HexToBits(CString &dest, CString &src, size_t size);

	/*
	@breif 将输入的倒置二进制序列集转换为倒置十六进制序列集

	@param    out : dest  转换后序列集存储
	@param     in : src  转换前序列集存储

	@return void
	*/
	void BitsToHex(CString &dest, CString &src, size_t size);

	/*
	@brief 初始化密钥生成子密钥组

	@param   in : src  经过输入格式化的8字节密钥序列集

	@return void
	*/
	void InitKey(CString &src);

	/*
	@brief 格式化从主程序界面文本款中获取的密钥为统一的8字节

	@param   out : dest  格式化后的密钥序列集
	@param    in : src 从文本框中得到的密钥序列集
	@param    in : sizeBit  src所占的字节数

	@return void
	*/
	void KeyFormat(CString &dest, CString &src, size_t sizeBit);

	/*
	@brief 加密明文，8字节明文分组格式化等问题处理，最后密文二进制序列集存储于m_cliphertext

	@param  in : src  读入的原始明文序列集
	@param  in : sizeBit  原始明文所占字节数

	@return void
	*/
	void Encrypt(CString &src, size_t sizeBit);

	/*
	@brief 解密密文，8字节密文分组等问题处理，最后明文二进制序列集存储于m_plaintext

	@param  in : src  读入的原始密文序列集
	@param  in : sizeBit  原始密文所占字节数

	return void
	*/
	void Decrypt(CString &src, size_t sizeBit);

private:

	/*
	@brief 初始64位明文经过初始置换IP

	@param   in : src  原64位明文序列集
	@param  out : dest  打乱重排后的明文序列集

	@return void
	*/
	void InitPermuteData(CString &dest, CString &src);

	/*
	@brief 一次加密8个字节的明文临时存储于m_curBinPlaintext

	@param  in : src  64位格式化后的明文序列集

	@return void
	*/
	void Encrypt8Byte(CString &src);

	/*
	@brief 一次解密8个字节的密文临时存储于m_curBinCiphertext

	@param  in : src  64位格式化后的密文序列集

	@return void
	*/
	void Decrypt8Byte(CString &src);

	/*
	@breif 计算子密钥组存储在m_DESSubkey数组中

	@param  in : src  经过PC_1选择置换的密钥序列集

	@return void
	*/
	void CreateSubkey(CString &src);

	/*
	@brief F函数

	@param  in : loopKey  迭代计数器
	@param  in : srcL  明文分组左半部分
	@param  in : srcR  明文分组右半部分

	@return void
	*/
	void FunF(CString &srcL, CString &srcR, unsigned int loopKey);

	/*
	@brief F函数中的S盒

	@param   in : src  6位输入二进制序列集
	@param  out : dest  4位输出二进制序列集

	@return void
	*/
	void SBOX(CString &dest, CString &src);

	/*
	@brief 将int转换为二进制序列集

	@param   in :  src  源int值
	@param  out : dest  转换后的二进制序列集

	@return void
	*/
	void IntToBit(CString &dest, int src);

	/*
	@brief 根据S盒的6位输入获取4位输出的行与列

	@param    in ： temp 6位输入二进制序列集
	@param   out ：row  4位输出序列集行号
	@param   out : col  4位输出序列集列号

	@return void
	*/
	void GetRowAndCol(int &row, int &col, CString &temp);

public:
	
	CString m_DESSubkey[16];				// 子密钥
	CString m_curBinPlaintext;				// 当前处理64的明文
	CString m_ciphertext;					// 最终密文
	CString m_curBinCiphertext;				// 当前处理64位密文
	CString m_plaintext;					// 最终明文
};

#endif
