/****************************************************************************
**
** Copyright (C) 2014, 黄海华 Corporation
** All rights reserved.  
** 
** @file    DES.h
** @brief  DES加密算法工具类实现文件
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

#include "stdafx.h"
#include "DES.h"

// 8字节占有64位二进制位
const int EIGHT_BYTE_BIN = 64;

// 1个字节所占有8个二进制位
const int ONE_BYTE_BIN = 8;

// 初始置换矩阵IP
static const int IP[64] = 
{
	 58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12, 4,
	 62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16, 8,
	 57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	 61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15, 7
};
// 逆初始置换矩阵IP¯¹
static const int IPR[64] = 
{
	 40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	 38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	 36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	 34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,   9, 49, 17, 57, 25
};
// 产生子密钥置换选择矩阵1
static const int PC_1[56] = 
{
	 57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 10,  2,
	 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,63, 55, 47, 39, 
	 31, 23, 15,  7, 62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 
	 29, 21, 13,  5, 28, 20, 12,  4
};
// 产生子密钥置换选择矩阵2
static const int PC_2[48] = 
{
	 14, 17, 11, 24,  1,  5,  3, 28, 15,    6, 21, 10, 23, 19, 12,  4,
	 26,   8, 16,  7, 27, 20, 13,  2, 41, 52, 31, 37, 47, 55, 30, 40,
	 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29,32
};
// 产生子密钥左移表
static const int LOOP[16] = 
{
	  1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1
};
// F函数中的S盒
static const int S[8][4][16] = 
{
	// S1
	 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	  0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	  4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// S2 
	 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3,  13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0,  14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// S3 
	 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1,  10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// S4 
	 7,  13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3,  15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// S5 
	 2,  12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,   1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// S6 
	 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9,  14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15,  10, 11, 14,  1,  7,  6,  0,  8, 13,
	// S7 
	 4, 11,   2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4,  11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11,  13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// S8 
	 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1,  15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9,  12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8,  13,  15, 12,  9,  0,  3,  5,  6, 11
};
// 对Right32位的扩充置换矩阵
static const int E[48] = 
{
	 32,   1,   2,  3,   4,   5,  4,   5,  6,   7,   8,  9,   8,   9, 10,  11,
	 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
	 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,   1
};
// 与Left32位做异或操作前的置换函数矩阵
static const int P[32] = 
{
	 16, 7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,   5,  18, 31, 10,
	  2,  8, 24, 14, 32, 27,   3,  9,  19, 13, 30, 6,   22, 11,  4,  25
};

void DES::ByteToBit(CString &dest, CString &src, size_t size)
{
	
	dest = _T("");
	size *= ONE_BYTE_BIN;
	for(unsigned int i = 0; i < size; ++i)
	{
		dest += src[i>>3] & (1<<(i % 8)) ? L'1' : L'0';
	}
}

void DES::BitToByte(CString &dest, CString &src, size_t size)
{
	dest = _T("");
	CString ch;
	for(unsigned int i = 0; i < size;)
	{
		ch.Format(_T("%c"), ((src[i] == L'0' ? 0 : 1)+(src[i+1] == L'0' ? 0 : 2)+(src[i+2] == L'0' ? 0 : 4)+(src[i+3] == L'0' ? 0 : 8)+(src[i+4] == L'0' ? 0 : 16)+(src[i+5] == L'0' ? 0 : 32)+(src[i+6] == L'0' ? 0 : 64)+(src[i+7] == L'0' ? 0 : 128)));
		dest += ch;
		i += ONE_BYTE_BIN;
	}
}

void DES::HexToBits(CString &dest, CString &src, size_t size)
{
	dest = _T("");
	CString ch = _T("");
	size *= (ONE_BYTE_BIN / 2);
	for(unsigned int i = 0; i < size;)
	{
		if (src[i>>2] < L'A')
		{
			ch = src[i>>2];
			int x = _ttoi(ch);
			dest += (x /(1<<(i%4)))%2 == 0 ? _T("0") : _T("1");
			++i;
		}
		else
		{
			if (src[i>>2] == L'A')
			{
				dest +=_T("0101"); 
			}
			if (src[i>>2] == L'B')
			{
				dest +=_T("1101");
			}
			if (src[i>>2] == L'C')
			{
				dest +=_T("0011");
			}
			if (src[i>>2] == L'D')
			{
				dest +=_T("1011");
			}
			if (src[i>>2] == L'E')
			{
				dest +=_T("0111");
			}
			if (src[i>>2] == L'F')
			{
				dest +=_T("1111");
			}
			i += (ONE_BYTE_BIN / 2);
		}
	}
}

void DES::BitsToHex(CString &dest, CString &src, size_t size)
{
	dest = _T("");
	CString chL = _T("");
	for(unsigned int i = 0; i < size;)
	{
		int sumL = (src[i] == L'0' ? 0 : 1)+(src[i+1] == L'0' ? 0 : 2)+(src[i+2] == L'0' ? 0 : 4)+(src[i+3] == L'0' ? 0 : 8);
		if (sumL < 10)
		{
			chL.Format(_T("%c"), (src[i] == L'0' ? 0 : 1)+(src[i+1] == L'0' ? 0 : 2)+(src[i+2] == L'0' ? 0 : 4)+(src[i+3] == L'0' ? 0 : 8) + 48);
		}else{
			chL.Format(_T("%c"), (src[i] == L'0' ? 0 : 1)+(src[i+1] == L'0' ? 0 : 2)+(src[i+2] == L'0' ? 0 : 4)+(src[i+3] == L'0' ? 0 : 8) - 9 + 64);
		}
		dest += chL;
		i += (ONE_BYTE_BIN / 2);
	}
}

void DES::InitPermuteData(CString &dest, CString &src)
{
	dest = _T("");
	for(int i = 0; i < EIGHT_BYTE_BIN; ++i)
	{
		dest += src[IP[i] - 1];
	}
}

void DES::InitKey(CString &src)
{
	CString key64 = _T("");
	size_t sLen = src.GetLength();
	ByteToBit(key64, src, sLen);
	CString key56 = _T("");
	for(int i = 0; i < 56; ++i)
	{
		key56 += key64[PC_1[i] - 1];
	}
	CreateSubkey(key56);
}

void DES::KeyFormat(CString &dest, CString &src, size_t lenKey)
{
	if (lenKey == 8)
	{
		dest = src;
	}
	else if (lenKey < 8)
	{
		dest += src; 
		for(int i = 0; i < (8 - lenKey); ++i)
		{
			dest += L'0';
		}
	}
	else
	{
		for(int i = 0; i < 8; ++i)
		{
			dest += src;
		}
	}
}

void DES::CreateSubkey(CString &src)
{
	CString keyL = _T("");
	CString keyR = _T("");
	// 左右分割个28位
	for (int i = 0; i < 28; ++i)
	{
		keyL += src[i];
		keyR += src[28 + i];
	}

	CString chL = _T("");
	CString chR = _T("");
	CString keyLR = _T("");
	
	for (int i = 0; i < 16; ++i)
	{
		chL = _T("");
		chR = _T("");
		keyLR = _T("");
		// 循环左移LOOP表
		for (int j = 0; j < 28; ++j)
		{
			chL += keyL[(LOOP[i] + j)%28];
			chR += keyR[(LOOP[i] + j)%28];
		}
		// 使用PC_2生成子密钥
		keyLR += chL;
		keyLR += chR;
		m_DESSubkey[i] = _T("");
		for(int k = 0; k < 48; ++k)
		{
			m_DESSubkey[i] += keyLR[PC_2[k] - 1];
		}
		keyL = chL;
		keyR = chR;
	}
}

void DES::FunF(CString &srcL, CString &srcR, unsigned int loopKey)
{
	// 扩充置换E
	CString eR = _T("");
	for(int i = 0; i < 48; ++i)
	{
		eR += srcR[E[i] - 1];
	}
	
	// 与第loopKey个子密钥模二相加即是异或
	CString str = _T("");
	for(int i = 0; i < 48; ++i)
	{
		str += (m_DESSubkey[loopKey][i] == eR[i] ? L'0' : L'1');
	}

	// S盒
	CString sOut = _T("");
	SBOX(sOut, str);

	// P变换
	CString pOut = _T("");
	for(int i = 0; i < (EIGHT_BYTE_BIN / 2); ++i)
	{
		pOut += sOut[P[i] - 1];
	}

	// 与"明文"的左半部分异或
	CString result = _T("");
	for(int i = 0; i < (EIGHT_BYTE_BIN / 2); ++i)
	{
		result += (srcL[i] == pOut[i] ? L'0' : L'1');
	}

	srcL = _T("");
	srcL = srcR;
	srcR = _T("");
	srcR = result;
}

void DES::SBOX(CString &dest, CString &src)
{
	CString temp = _T("");
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			temp += src[i * 6 + j];
		}
		int x = 0;
		int y = 0;
		GetRowAndCol(x, y, temp);
		IntToBit(temp, S[i][x][y]);
		dest += temp;
		temp = _T("");
	}
}

void DES::GetRowAndCol(int &row, int &col, CString &temp)
{
	if (temp[0] == L'0' && temp[5] == L'1')
	{
		row = 1;
	}
	if (temp[0] == L'1' && temp[5] == L'0')
	{
		row = 2;
	}
	if (temp[0] == L'1' && temp[5] == L'1')
	{
		row = 3;
	}

	if (temp[1] == L'0' && temp[2] == L'0' && temp[3] == L'0' && temp[4] == L'1')
	{
		col = 1;
	}
	if (temp[1] == L'0' && temp[2] == L'0' && temp[3] == L'1' && temp[4] == L'0')
	{
		col = 2;
	}
	if (temp[1] == L'0' && temp[2] == L'0' && temp[3] == L'1' && temp[4] == L'1')
	{
		col = 3;
	}
	if (temp[1] == L'0' && temp[2] == L'1' && temp[3] == L'0' && temp[4] == L'0')
	{
		col = 4;
	}
	if (temp[1] == L'0' && temp[2] == L'1' && temp[3] == L'0' && temp[4] == L'1')
	{
		col = 5;
	}
	if (temp[1] == L'0' && temp[2] == L'1' && temp[3] == L'1' && temp[4] == L'0')
	{
		col = 6;
	}
	if (temp[1] == L'0' && temp[2] == L'1' && temp[3] == L'1' && temp[4] == L'1')
	{
		col = 7;
	}
	if (temp[1] == L'1' && temp[2] == L'0' && temp[3] == L'0' && temp[4] == L'0')
	{
		col = 8;
	}
	if (temp[1] == L'1' && temp[2] == L'0' && temp[3] == L'0' && temp[4] == L'1')
	{
		col = 9;
	}
	if (temp[1] == L'1' && temp[2] == L'0' && temp[3] == L'1' && temp[4] == L'0')
	{
		col = 10;
	}
	if (temp[1] == L'1' && temp[2] == L'0' && temp[3] == L'1' && temp[4] == L'1')
	{
		col = 11;
	}
	if (temp[1] == L'1' && temp[2] == L'1' && temp[3] == L'0' && temp[4] == L'0')
	{
		col = 12;
	}
	if (temp[1] == L'1' && temp[2] == L'1' && temp[3] == L'0' && temp[4] == L'1')
	{
		col = 13;
	}
	if (temp[1] == L'1' && temp[2] == L'1' && temp[3] == L'1' && temp[4] == L'0')
	{
		col = 14;
	}
	if (temp[1] == L'1' && temp[2] == L'1' && temp[3] == L'1' && temp[4] == L'1')
	{
		col = 15;
	}
}

void DES::IntToBit(CString &dest, int src)
{
	for(int i = 0; i < 4; ++i)
	{
		dest += (src / (1<<i)) % 2 ? L'1' : L'0';
	}
}

void DES::Encrypt(CString &src, size_t sizeBit)
{
	m_ciphertext = _T("");
	if (sizeBit == EIGHT_BYTE_BIN)
	{
		Encrypt8Byte(src);
		m_ciphertext = m_curBinPlaintext;
	}
	else if (sizeBit < EIGHT_BYTE_BIN)
	{
		// 不足八个字节是以0填充
		CString curStr = _T("");
		curStr += src;
		for(int i = 0; i < (EIGHT_BYTE_BIN - sizeBit); ++i)
		{
			curStr += L'0';
		}
		Encrypt8Byte(curStr);
		m_ciphertext = m_curBinPlaintext;
	}
	else
	{
		int blockCount = sizeBit>>6;
		int rest = sizeBit % EIGHT_BYTE_BIN;
		CString curStr;
		for(int i = 0; i < blockCount; ++i)
		{
			curStr =_T("");
			m_curBinPlaintext = _T("");
			for(int j = 0; j < EIGHT_BYTE_BIN; ++j)
			{
				curStr += src[i * EIGHT_BYTE_BIN + j];
			}
			Encrypt8Byte(curStr);
			m_ciphertext += m_curBinPlaintext;
		}
		// 尾部
		curStr = _T("");
		m_curBinPlaintext = _T("");
		for(int i = 0; i < rest; ++i)
		{
			curStr += src[blockCount * EIGHT_BYTE_BIN + i];
		}
		for(int i = 0; i < (EIGHT_BYTE_BIN - rest); ++i)
		{
			curStr += L'0';
		}
		Encrypt8Byte(curStr);
		m_ciphertext += m_curBinPlaintext;
	}
}

void DES::Encrypt8Byte(CString &src)
{
	InitPermuteData(m_curBinPlaintext, src);
	CString plaintextL = _T("");
	CString plaintextR = _T("");
	for(int i = 0; i < (EIGHT_BYTE_BIN / 2); ++i)
	{
		plaintextL += m_curBinPlaintext[i];
		plaintextR += m_curBinPlaintext[EIGHT_BYTE_BIN / 2 + i];
	}
	for(int i = 0; i < 16; ++i)
	{
		FunF(plaintextL, plaintextR, i);
	}
	CString final64 = _T("");
	final64 += plaintextR;
	final64 += plaintextL;

	// 逆初始置换
	m_curBinPlaintext = _T("");
	for(int i = 0; i < EIGHT_BYTE_BIN; ++i)
	{
		m_curBinPlaintext += final64[IPR[i] - 1];
	}
}

void DES::Decrypt(CString &src, size_t sizeBit)
{
	m_plaintext = _T("");
	int blockCount = sizeBit >> 6;
	CString curStr;
	for(int i = 0; i < blockCount; ++i)
	{
		curStr = _T("");
		for(int j = 0; j < EIGHT_BYTE_BIN; ++j)
		{
			curStr += src[i * EIGHT_BYTE_BIN + j];
		}
		Decrypt8Byte(curStr);
		m_plaintext += m_curBinCiphertext;
	}
}

void DES::Decrypt8Byte(CString &src)
{
	InitPermuteData(m_curBinCiphertext, src);
	CString ciphertextL = _T("");
	CString ciphertextR = _T("");
	for(int i = 0; i < (EIGHT_BYTE_BIN / 2); ++i)
	{
		ciphertextL += m_curBinCiphertext[i];
		ciphertextR += m_curBinCiphertext[EIGHT_BYTE_BIN / 2 + i];
	}
	// 解密时子密钥与加密时相反
	for(int i = 0; i < 16; ++i)
	{
		FunF(ciphertextL, ciphertextR, 15 - i);
	}
	CString final64 = _T("");
	final64 += ciphertextR;
	final64 += ciphertextL;

	// 逆初始置换
	m_curBinCiphertext = _T("");
	for(int i = 0; i < EIGHT_BYTE_BIN; ++i)
	{
		m_curBinCiphertext += final64[IPR[i] - 1];
	}
}
