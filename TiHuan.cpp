#include "pch.h"
#include "TiHuan.h"

#include <iostream>
#include <string>
#include <vector>
#include <io.h>

#include <windows.h>
#include <shlwapi.h> 
//#include <afxpriv.h>//
#pragma comment(lib, "shlwapi.lib")
#pragma warning(disable:4996) 
TiHuan::TiHuan()
{
}

TiHuan::~TiHuan()
{
}

int TiHuan::zi_fu_chuan_chang_du_h(CString zi_fu_c)
{
#if 0
	/*  *****�����ַ�������**** ��ʼ */
	short lenth;
	for (lenth = 0; zi_fu_c[lenth]; lenth++)
	{
	}
	lenth = (lenth + 1) * 2;//*2s ��Ϊwchar_t��˫�ֽ�,+1���ַ�����0��β,wchar_t��00��β
	/*  *****�����ַ�������**** ���� */
#else
	TCHAR  aa[260];
	int ii = 0;
	for (int i = 260 - 1; aa[i] != L'.'; i--)//�ַ����Ӻ�ǰ�Ƚ�,�����Ϊ'.'�ͽ�aa[i]��ֵΪ0,Ϊ'.'ʱѭ����ֹ
	{
		aa[i] = 0;
		ii++;
	}
	aa[260 - 1 - ii] = 0;//��'.'����
#endif
	return 0;
}

int TiHuan::zui_qian_h(CString path, CString xiu_gai, CString kuo_zhan)
{
	/*PathFindExtension*/
	/*rename(oldName.c_str(), newName.c_str())   �޸��ļ���*/
#if 1
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	if (path==L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/	
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	/*_findfirst 
	����1: ֧��ͨ���,*.c��ʾ��ǰ·�������еĺ�׺Ϊ.c���ļ�
	����2: ���������������ļ���Ϣ�Ľṹ���ָ�롣����ṹ������ڵ��ô˺���ǰ����
	*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			len++;
		}
	}
	
	CString xiu_gai_j;
	while (!_findnext(handle,&fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			//kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
			//if (kuo_zhan_ming_j == kuo_zhan)
			if(kuo_zhan_ming_j.CollateNoCase(kuo_zhan)==0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				xiu_gai_j = path + L"\\" + xiu_gai + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				/*�ƶ�Ŀ¼�����ļ�,�޸�Ŀ¼�����ļ���
				* ����1: Ҫ�޸�Ŀ¼���ļ���·��������
				* ����2: �ļ���Ŀ¼�������ơ������Ʋ����Ѵ���
				* ����ֵ: ʧ�ܷ���0
				*/
				//MoveFile(wen_jian_ming_j, xiu_gai_j);
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;
				} 
				len++;
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
#endif

#if 0
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return FALSE;
	}
	USES_CONVERSION;
	const char* path_jp = T2A(path);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��һ�β���
	if (-1 == handle)
	{
		return FALSE;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
		if (kuo_zhan_ming_j == kuo_zhan)
		{
			len++;
		}
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
			if (kuo_zhan_ming_j == kuo_zhan)
			{
				len++;
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
#endif
}

int TiHuan::zui_qian_h(CString path, unsigned int shu_zhi, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			len++;
		}
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);

			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				xiu_gai_j.Format(_T("%u_", shu_zhi)); /*����ת��Ϊ�ַ�,%u�޷���ʮ��������*/
				xiu_gai_j = path + L"\\" + xiu_gai_j + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;
				}
				len++;
				shu_zhi++;
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::zui_hou_h(CString path, CString xiu_gai, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*��ȡ�����ļ���չ��*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*ƴ��ͨ���,*��ȫ��;������.jpg,����ֻ������׺Ϊ.jpg���ļ�*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*ת������ļ�·��*/
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo); //��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	CString xiu_gai_j;/*�޸ĺ�ĺ�����·�����ļ���*/
	int xia_biao_j = 0;/*�����ַ���ָ���ַ����±�,��0��ʼ*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
		xiu_gai_j = wen_jian_ming_j;
		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
		xiu_gai_j.Insert(xia_biao_j, xiu_gai);      /*�ڲ��ҵ����±괦�����ַ�*/

		xiu_gai_j = path + L"\\" + xiu_gai_j;
		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
		/*�޸��ļ���*/
		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
		{
			_findclose(handle); /*�رվ��*/
			return -2;
		}
		len++;
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
			xiu_gai_j = wen_jian_ming_j;
			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
			xiu_gai_j.Insert(xia_biao_j, xiu_gai);      /*�ڲ��ҵ����±괦�����ַ�*/

			xiu_gai_j = path + L"\\" + xiu_gai_j;
			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
			/*�޸��ļ���*/
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;
			}
			len++;
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::zui_hou_h(CString path, CString xiu_gai, unsigned int shu_zhi, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*��ȡ�����ļ���չ��*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*ƴ��ͨ���,*��ȫ��;������.jpg,����ֻ������׺Ϊ.jpg���ļ�*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*ת������ļ�·��*/
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	CString xu_hao_j;
	CString xiu_gai_j;/*�޸ĺ�ĺ�����·�����ļ���*/
	int xia_biao_j = 0;/*�����ַ���ָ���ַ����±�,��0��ʼ*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
		xu_hao_j.Format( _T("_%u"), shu_zhi);
		wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
		xiu_gai_j = wen_jian_ming_j;
		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
		xiu_gai_j.Insert(xia_biao_j, xiu_gai + xu_hao_j);   /*�ڲ��ҵ����±괦�����ַ�*/

		xiu_gai_j = path + L"\\" + xiu_gai_j;
		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
		/*�޸��ļ���*/
		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
		{
			_findclose(handle); /*�رվ��*/
			return -2;
		}
		len++;
		shu_zhi++;
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			xu_hao_j.Format(_T("_%u"), shu_zhi);
			wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
			xiu_gai_j = wen_jian_ming_j;
			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
			xiu_gai_j.Insert(xia_biao_j, xiu_gai + xu_hao_j);   /*�ڲ��ҵ����±괦�����ַ�*/

			xiu_gai_j = path + L"\\" + xiu_gai_j;
			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
			/*�޸��ļ���*/
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;
			}
			len++;
			shu_zhi++;
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::zhong_jian_h(CString path, CString yuan_shi, CString xiu_gai, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			len++;
		}
	}

	CString xiu_gai_j;
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
				{
					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*�رվ��*/
						return -2;
					}
					len++;
				}
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::zhong_jian_h(CString path, CString yuan_shi, CString xiu_gai, unsigned int xu_hao, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	CString xuHaoT;
	unsigned short xiaBiaoU;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		xiu_gai_j = wen_jian_ming_j;
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
			{
				xuHaoT.Format(_T("_%u"), xu_hao);
				xiu_gai_j = wen_jian_ming_j;
				xiaBiaoU = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
				xiu_gai_j.Insert(xiaBiaoU, xuHaoT);   /*�ڲ��ҵ����±괦�����ַ�*/

				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;
				}
				len++;
				xu_hao++;
			}
		}
	}
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
				{
					xuHaoT.Format(_T("_%u"), xu_hao);
					xiu_gai_j = wen_jian_ming_j;
					xiaBiaoU = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
					xiu_gai_j.Insert(xiaBiaoU, xuHaoT);   /*�ڲ��ҵ����±괦�����ַ�*/

					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*�رվ��*/
						return -2;
					}
					len++;
					xu_hao++;
				}
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::quan_bu_h(CString path, CString xiu_gai, CString kuo_zhan, unsigned int shu_zhi)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*��ȡ�����ļ���չ��*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*ƴ��ͨ���,*��ȫ��;������.jpg,����ֻ������׺Ϊ.jpg���ļ�*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*ת������ļ�·��*/
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	CString xu_hao_j;
	CString xiu_gai_j;/*�޸ĺ�ĺ�����·�����ļ���*/
	int xia_biao_j = 0;/*�����ַ���ָ���ַ����±�,��0��ʼ*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
// 		xu_hao_j.Format(_T("_%u"), shu_zhi);
// 		wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
// 		xiu_gai_j = wen_jian_ming_j;
// 		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
// 		xiu_gai_j.Delete(0, xia_biao_j);
// 		xiu_gai_j.Insert(0, xiu_gai + xu_hao_j);   /*�ڲ��ҵ����±괦�����ַ�*/
// 
// 		xiu_gai_j = path + L"\\" + xiu_gai_j;
// 		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
// 		/*�޸��ļ���*/
// 		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
// 		{
// 			_findclose(handle); /*�رվ��*/
// 			return -2;
// 		}
		len++;
		shu_zhi++;
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
// 			xu_hao_j.Format(_T("_%u"), shu_zhi);
// 			wen_jian_ming_j = CString(fileinfo.name);         /*��ȡ����չ�����ļ���*/
// 			xiu_gai_j = wen_jian_ming_j;
// 			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
// 			xiu_gai_j.Delete(0, xia_biao_j);              /*�ӵ�һ���ַ���ʼɾ����"."ǰ�������ַ�*/
// 			xiu_gai_j.Insert(0, xiu_gai + xu_hao_j);   /*�ӵ�һ���ַ���λ�ô������ַ�*/
// 
// 			xiu_gai_j = path + L"\\" + xiu_gai_j;
// 			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
// 			/*�޸��ļ���*/
// 			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
// 			{
// 				_findclose(handle); /*�رվ��*/
// 				return -2;
// 			}
			len++;
			shu_zhi++;
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::ShanChuH(CString path, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou)
{
	if (xia_biao <= 0 || xia_biao > 260)
	{
		return -5; /*Ҫɾ�����ַ���������߹���*/
	}
	int len = 0;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	unsigned short dianXiaoBiaoU = 0; /*��չ��"."���±�*/
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	path = path + _T("\\");
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (qian_hou)
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
			if (xia_biao >= dianXiaoBiaoU+1)
			{
				_findclose(handle); /*�رվ��*/
				return -4;  /*Ҫɾ�����ַ��������ļ����ַ���*/
			}
			else
			{
				xiu_gai_j.Delete(0, xia_biao);
			}
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;   /*����������*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
				if (xia_biao >= dianXiaoBiaoU + 1)
				{
					_findclose(handle); /*�رվ��*/
					return -4;  /*Ҫɾ�����ַ��������ļ����ַ���*/
				}
				else
				{
					xiu_gai_j.Delete(0, xia_biao);
				}
				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;  /*����������*/
				}
				len++;
			}
		}
		_findclose(handle); /*�رվ��*/
	} 
	else /*��*/
	{
		unsigned int xiaBiaoU = 1;
		CString XuHaoT;
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			XuHaoT.Format(_T("_%u"), xiaBiaoU);
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
			if (xia_biao >= dianXiaoBiaoU+1)
			{
				_findclose(handle); /*�رվ��*/
				return -4;  /*Ҫɾ�����ַ��������ļ����ַ���*/
			}
			else
			{
				/*�Ӹ������������ַ���ʼ���ַ�����ɾ��һ�������ַ�
				* ����1: Ҫɾ�� �Ķ����е�һ���ַ��Ĵ��㿪ʼ��������
				* ����2: Ҫɾ�����ַ���
				* ����:  ɾ�����ַ�������
				*/
				xiu_gai_j.Delete(dianXiaoBiaoU - xia_biao, xia_biao);
				/*���ַ����ĸ������������뵥���ַ������ַ���
				* ����1: ������֮ǰ���в�����ַ�������
				* ����2:ָ��Ҫ��������ַ�����ָ��
				* ����: ���ĺ��ַ�������
				*/
				xiu_gai_j.Insert(dianXiaoBiaoU - xia_biao, XuHaoT);
			}
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;  /*����������*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				XuHaoT.Format(_T("_%u"), xiaBiaoU);
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
				if (xia_biao >= dianXiaoBiaoU+1)
				{
					_findclose(handle); /*�رվ��*/
					return -4;  /*Ҫɾ�����ַ��������ļ����ַ���*/
				}
				else
				{
					/*�Ӹ������������ַ���ʼ���ַ�����ɾ��һ�������ַ�
					* ����1: Ҫɾ�� �Ķ����е�һ���ַ��Ĵ��㿪ʼ��������
					* ����2: Ҫɾ�����ַ���
					* ����:  ɾ�����ַ�������
					*/
					xiu_gai_j.Delete(dianXiaoBiaoU - xia_biao, xia_biao);
					/*���ַ����ĸ������������뵥���ַ������ַ���
					* ����1: ������֮ǰ���в�����ַ�������
					* ����2:ָ��Ҫ��������ַ�����ָ��
					* ����: ���ĺ��ַ�������
					*/
					xiu_gai_j.Insert(dianXiaoBiaoU - xia_biao, XuHaoT);
					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*�رվ��*/
						return -2;  /*����������*/
					}
					len++;
				}
			}
		}/*dfgeru52���_3  geru52���_14*/
		_findclose(handle); /*�رվ��*/
	}
	return len;
}

int TiHuan::ShanChuH(CString path, CString xiu_gai, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou)
{
	int len = 0;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	unsigned short dianXiaoBiaoU = 0; /*��չ��"."���±�*/
	short FindXiaBiaoU = 0;   /*find���ص��±�*/
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	path = path + _T("\\");
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (qian_hou)
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
			FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
			for (unsigned short i = 0; i < dianXiaoBiaoU; i++)
			{
				FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
				xiu_gai_j.Delete(FindXiaBiaoU, 1);
			}
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;   /*����������*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
				FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
				for (unsigned short i = 0; i < dianXiaoBiaoU; i++)
				{
					FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
					xiu_gai_j.Delete(FindXiaBiaoU, 1);
				}
				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;  /*����������*/
				}
				len++;
			}
		}
		_findclose(handle); /*�رվ��*/\
		return len;
	}
	else /*��*/
	{
		CString XuHaoT;
		unsigned short i = 0;
		unsigned short XiuGaiCiShuU = 0;
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			XuHaoT.Format(_T("_%u"), xia_biao);
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
			for (i = 0; i < dianXiaoBiaoU; i++)
			{
				/*����
				* Ҫ���ҵ�����""��Ҫ�����ĵ����ַ�''
				* ��ʼ�������ַ������ַ������������ͷ��ʼ������ 0
				* ����:ʧ�ܷ���-1,�ɹ�����ƥ��ĵ�һ���ַ��Ĵ��㿪ʼ������
				*/
				FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
				/*�Ӹ������������ַ���ʼ���ַ�����ɾ��һ�������ַ�
				* ����1: Ҫɾ�� �Ķ����е�һ���ַ��Ĵ��㿪ʼ��������
				* ����2: Ҫɾ�����ַ���
				* ����:  ɾ�����ַ�������
				*/
				if (-1 != FindXiaBiaoU)
				{
					xiu_gai_j.Delete(FindXiaBiaoU, 1);
					XiuGaiCiShuU++;
				}

			}
			/*���ַ����ĸ������������뵥���ַ������ַ���
				* ����1: ������֮ǰ���в�����ַ�������
				* ����2:ָ��Ҫ��������ַ�����ָ��
				* ����: ���ĺ��ַ�������
				*/
			xiu_gai_j.Insert(dianXiaoBiaoU - XiuGaiCiShuU, XuHaoT);
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*�رվ��*/
				return -2;  /*����������*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				XuHaoT.Format(_T("_%u"), xia_biao);
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
				for (i = 0; i < dianXiaoBiaoU; i++)
				{
					/*����
					* Ҫ���ҵ�����""��Ҫ�����ĵ����ַ�''
					* ��ʼ�������ַ������ַ������������ͷ��ʼ������ 0
					* ����:ʧ�ܷ���-1,�ɹ�����ƥ��ĵ�һ���ַ��Ĵ��㿪ʼ������
					*/
					FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
					/*�Ӹ������������ַ���ʼ���ַ�����ɾ��һ�������ַ�
					* ����1: Ҫɾ�� �Ķ����е�һ���ַ��Ĵ��㿪ʼ��������
					* ����2: Ҫɾ�����ַ���
					* ����:  ɾ�����ַ�������
					*/
					if (-1 != FindXiaBiaoU)
					{
						xiu_gai_j.Delete(FindXiaBiaoU, 1);
						XiuGaiCiShuU++;
					}

				}
				/*���ַ����ĸ������������뵥���ַ������ַ���
					* ����1: ������֮ǰ���в�����ַ�������
					* ����2:ָ��Ҫ��������ַ�����ָ��
					* ����: ���ĺ��ַ�������
					*/
				xiu_gai_j.Insert(dianXiaoBiaoU - XiuGaiCiShuU, XuHaoT);
				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;  /*����������*/
				}
				len++;
			}/*dfgeru52���_3  geru52���_14*/
			_findclose(handle); /*�رվ��*/
		}
		return len;
	}
}

BOOL TiHuan::xiu_gai_kuo_zhan_ming_h(CString path, CString kuo_zhan, CString xiu_gai)
{
	CString kuo_zhan_ming_j; /*��չ��*/
	CString wen_jian_ming_j; /*�ļ���,�ļ�·��*/
	if (path == _T(""))
	{
		return FALSE;
	}
	wen_jian_ming_j = path + L"\\*";
	/*��CStringת��Ϊchar*����*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	/*_findfirst
	����1: ֧��ͨ���,*.c��ʾ��ǰ·�������еĺ�׺Ϊ.c���ļ�
	����2: ���������������ļ���Ϣ�Ľṹ���ָ�롣����ṹ������ڵ��ô˺���ǰ����
	*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)/*��������ļ�������*/
	{
		
	}

	CString xiu_gai_j; /*Ҫ�޸ĵ��ַ�*/
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);/*�ҵ����ļ���,������չ��*/

			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				/*������չ������*/
				/*���ҿ�ʼɾ����Ӧ���ȵ��ַ�*/
				/*���¼�����չ��*/
				xiu_gai_j = path + L"\\" + xiu_gai_j + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				/*�ƶ�Ŀ¼�����ļ�,�޸�Ŀ¼�����ļ���
				* ����1: Ҫ�޸�Ŀ¼���ļ���·��������
				* ����2: �ļ���Ŀ¼�������ơ������Ʋ����Ѵ���
				* ����ֵ: ʧ�ܷ���0
				*/
				//MoveFile(wen_jian_ming_j, xiu_gai_j);
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*�رվ��*/
					return -2;
				}
			}
		}
	}
	_findclose(handle); /*�رվ��*/

	//FindFirstFile


	return TRUE;
}

BOOL TiHuan::xiu_gai_zhong_jian_h(CString& wen_jian_ming, CString yuan_zi_fu, CString xiu_gai_zi_fu)
{
	int aa = wen_jian_ming.GetLength();/*�����ַ�������,����ҲΪ1,ʵ����������2*/
	//int abc = a.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
	/*����
	* Ҫ���ҵ�����""��Ҫ�����ĵ����ַ�''
	* ��ʼ�������ַ������ַ������������ͷ��ʼ������ 0
	* ����:ʧ�ܷ���-1,�ɹ�����ƥ��ĵ�һ���ַ��Ĵ��㿪ʼ������
	*/
	int aad = wen_jian_ming.Find(yuan_zi_fu);
	if (-1==aad)
	{
		return FALSE;
	}
	int aae = yuan_zi_fu.GetLength();
	/*�Ӹ������������ַ���ʼ���ַ�����ɾ��һ�������ַ�
	* ����1: Ҫɾ�� �Ķ����е�һ���ַ��Ĵ��㿪ʼ��������
	* ����2: Ҫɾ�����ַ���
	* ����:  ɾ�����ַ�������
	*/
	int aag = wen_jian_ming.Delete(aad, aae);
	if (aag <= 0)
	{
		return FALSE;
	}
	/*���ַ����ĸ������������뵥���ַ������ַ���
	* ����1: ������֮ǰ���в�����ַ�������
	* ����2:ָ��Ҫ��������ַ�����ָ��
	* ����: ���ĺ��ַ�������
	*/
	int aaf = wen_jian_ming.Insert(aad, xiu_gai_zi_fu);
	if (aaf <= 0)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL TiHuan::XiuGaiWenJianMingH(CString path, CString& wen_jian_ming, CString& yuan_zi_fu, CString xiu_gai_zi_fu, unsigned short lei_xing, unsigned int xu_hao)
{
	CString ls;//�ֲ�����
	switch (lei_xing)
	{
	case 0:/*����ǰ�����*/
		xiu_gai_zi_fu = path + _T("\\") + xiu_gai_zi_fu + yuan_zi_fu;
		yuan_zi_fu = path + _T("\\") + yuan_zi_fu;
		break;
	case 1:/*����ǰ����� \"1_\"��������,��ָ����ʼ����*/
		xiu_gai_zi_fu.Format(_T("%u_", xu_hao)); /*����ת��Ϊ�ַ�,%u�޷���ʮ��������*/
		xiu_gai_zi_fu = path + L"\\" + xiu_gai_zi_fu + yuan_zi_fu;
		yuan_zi_fu = path + L"\\" + yuan_zi_fu;
		break;
	case 2:/*����������*/
		wen_jian_ming = yuan_zi_fu;
		lei_xing = wen_jian_ming.ReverseFind(_T('.'));/*��������ʼ���� '.'*/
		wen_jian_ming.Insert(lei_xing, xiu_gai_zi_fu);      /*�ڲ��ҵ����±괦�����ַ�*/

		wen_jian_ming = path + L"\\" + wen_jian_ming;
		yuan_zi_fu = path + L"\\" + yuan_zi_fu;
		break;
	case 3:/*�����������ַ����� \"_1\"��������,��ָ����ʼ����*/
		xiu_gai_zi_fu.Format(xiu_gai_zi_fu + _T("_%u"), xu_hao);
		wen_jian_ming = yuan_zi_fu;
		lei_xing = wen_jian_ming.ReverseFind(_T('.'));       /*��������ʼ���� '.'*/
		wen_jian_ming.Insert(lei_xing, xiu_gai_zi_fu);   /*�ڲ��ҵ����±괦�����ַ�*/

		wen_jian_ming = path + L"\\" + wen_jian_ming;
		yuan_zi_fu = path + L"\\" + yuan_zi_fu;
		break;
	default:
		break;
	}
	return 0;
}

int TiHuan::wen_jian_gai_ming_h(
	CString path, 
	CString kuo_zhan, 
	CString yuan_zi_fu, 
	CString xiu_gai_zi_fu, 
	unsigned int shu_zi_xu_hao, 
	unsigned short gui_ze_xu_hao = 1)
{
	int len = 0;
	CString kuo_zhan_ming_j;
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*" + kuo_zhan;
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��һ�β���
	/*_findfirst
	����1: ֧��ͨ���,*.c��ʾ��ǰ·�������еĺ�׺Ϊ.c���ļ�
	����2: ���������������ļ���Ϣ�Ľṹ���ָ�롣����ṹ������ڵ��ô˺���ǰ����
	*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			len++;
		}
	}

	CString xiu_gai_j;
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			//kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*����չ��ת��ΪСд��ĸ*/
			//if (kuo_zhan_ming_j == kuo_zhan)
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				switch (gui_ze_xu_hao)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_zi_fu, xiu_gai_zi_fu))
					{
						xiu_gai_j = path + xiu_gai_j;
						wen_jian_ming_j = path + wen_jian_ming_j;
						/*�ƶ�Ŀ¼�����ļ�,�޸�Ŀ¼�����ļ���
						* ����1: Ҫ�޸�Ŀ¼���ļ���·��������
						* ����2: �ļ���Ŀ¼�������ơ������Ʋ����Ѵ���
						* ����ֵ: ʧ�ܷ���0
						*/
						//MoveFile(wen_jian_ming_j, xiu_gai_j);
						if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
						{
							_findclose(handle); /*�رվ��*/
							return -2;
						}
						len++;
					}
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				default:
					break;
				}	
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}

int TiHuan::h_wen_jian_shu_liang(const char* path)
{
	int len = 0;
	long long handle;

	struct _finddata_t fileinfo;
	handle = _findfirst(path, &fileinfo);//��һ�β���
	if (-1 == handle)
	{
		return FALSE;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		len++;
	}
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			len++;
		}
	}
	_findclose(handle);
	return len;
}

int TiHuan::tong_pei_fu_h(CString path, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*��ȡ�����ļ���չ��*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*" + kuo_zhan; /*ƴ��"\"��ͨ���,*���滹����ָ����ʽ.jpg,����ֻ������׺Ϊ.jpg���ļ�*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*ת������ļ�·��*/
	long long handle;                 /*���ڲ��ҵľ��*/
	struct _finddata_t fileinfo;      /*�ļ���Ϣ�Ľṹ��*/
	handle = _findfirst(path_jp, &fileinfo);//��ȡ���
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
		{
			len++;
		}
	}
	CString xiu_gai_j;/*�޸ĺ�ĺ�����·�����ļ���*/
	int xia_biao_j = 0;/*�����ַ���ָ���ַ����±�,��0��ʼ*/
	while (!_findnext(handle, &fileinfo))//ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*��ȡ�ļ���չ��*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*�Ƚ��ַ���,�����ִ�Сд*/
			{
				len++;
			}
		}
	}
	_findclose(handle); /*�رվ��*/
	return len;
}


