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
	/*  *****计算字符串长度**** 开始 */
	short lenth;
	for (lenth = 0; zi_fu_c[lenth]; lenth++)
	{
	}
	lenth = (lenth + 1) * 2;//*2s 因为wchar_t是双字节,+1是字符串以0结尾,wchar_t是00结尾
	/*  *****计算字符串长度**** 结束 */
#else
	TCHAR  aa[260];
	int ii = 0;
	for (int i = 260 - 1; aa[i] != L'.'; i--)//字符串从后到前比较,如果不为'.'就将aa[i]赋值为0,为'.'时循环终止
	{
		aa[i] = 0;
		ii++;
	}
	aa[260 - 1 - ii] = 0;//将'.'消除
#endif
	return 0;
}

int TiHuan::zui_qian_h(CString path, CString xiu_gai, CString kuo_zhan)
{
	/*PathFindExtension*/
	/*rename(oldName.c_str(), newName.c_str())   修改文件名*/
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

	long long handle;                 /*用于查找的句柄*/	
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	/*_findfirst 
	参数1: 支持通配符,*.c表示当前路径下所有的后缀为.c的文件
	参数2: 这里就是用来存放文件信息的结构体的指针。这个结构体必须在调用此函数前声明
	*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			len++;
		}
	}
	
	CString xiu_gai_j;
	while (!_findnext(handle,&fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			//kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
			//if (kuo_zhan_ming_j == kuo_zhan)
			if(kuo_zhan_ming_j.CollateNoCase(kuo_zhan)==0) /*比较字符串,不区分大小写*/
			{
				xiu_gai_j = path + L"\\" + xiu_gai + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				/*移动目录或者文件,修改目录或者文件名
				* 参数1: 要修改目录或文件的路径与名字
				* 参数2: 文件或目录的新名称。新名称不得已存在
				* 返回值: 失败返回0
				*/
				//MoveFile(wen_jian_ming_j, xiu_gai_j);
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;
				} 
				len++;
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
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

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//第一次查找
	if (-1 == handle)
	{
		return FALSE;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
		if (kuo_zhan_ming_j == kuo_zhan)
		{
			len++;
		}
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
			if (kuo_zhan_ming_j == kuo_zhan)
			{
				len++;
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
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

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			len++;
		}
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);

			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
			{
				xiu_gai_j.Format(_T("%u_", shu_zhi)); /*整数转换为字符,%u无符号十进制整数*/
				xiu_gai_j = path + L"\\" + xiu_gai_j + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;
				}
				len++;
				shu_zhi++;
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
	return len;
}

int TiHuan::zui_hou_h(CString path, CString xiu_gai, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*获取到的文件扩展名*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*拼接通配符,*是全部;还可以.jpg,这样只搜索后缀为.jpg的文件*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*转换后的文件路径*/
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo); //获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	CString xiu_gai_j;/*修改后的含完整路径的文件名*/
	int xia_biao_j = 0;/*查找字符串指定字符的下标,从0开始*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
		xiu_gai_j = wen_jian_ming_j;
		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
		xiu_gai_j.Insert(xia_biao_j, xiu_gai);      /*在查找到的下标处插入字符*/

		xiu_gai_j = path + L"\\" + xiu_gai_j;
		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
		/*修改文件名*/
		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
		{
			_findclose(handle); /*关闭句柄*/
			return -2;
		}
		len++;
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
			xiu_gai_j = wen_jian_ming_j;
			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
			xiu_gai_j.Insert(xia_biao_j, xiu_gai);      /*在查找到的下标处插入字符*/

			xiu_gai_j = path + L"\\" + xiu_gai_j;
			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
			/*修改文件名*/
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*关闭句柄*/
				return -2;
			}
			len++;
		}
	}
	_findclose(handle); /*关闭句柄*/
	return len;
}

int TiHuan::zui_hou_h(CString path, CString xiu_gai, unsigned int shu_zhi, CString kuo_zhan)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*获取到的文件扩展名*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*拼接通配符,*是全部;还可以.jpg,这样只搜索后缀为.jpg的文件*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*转换后的文件路径*/
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	CString xu_hao_j;
	CString xiu_gai_j;/*修改后的含完整路径的文件名*/
	int xia_biao_j = 0;/*查找字符串指定字符的下标,从0开始*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
		xu_hao_j.Format( _T("_%u"), shu_zhi);
		wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
		xiu_gai_j = wen_jian_ming_j;
		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
		xiu_gai_j.Insert(xia_biao_j, xiu_gai + xu_hao_j);   /*在查找到的下标处插入字符*/

		xiu_gai_j = path + L"\\" + xiu_gai_j;
		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
		/*修改文件名*/
		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
		{
			_findclose(handle); /*关闭句柄*/
			return -2;
		}
		len++;
		shu_zhi++;
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			xu_hao_j.Format(_T("_%u"), shu_zhi);
			wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
			xiu_gai_j = wen_jian_ming_j;
			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
			xiu_gai_j.Insert(xia_biao_j, xiu_gai + xu_hao_j);   /*在查找到的下标处插入字符*/

			xiu_gai_j = path + L"\\" + xiu_gai_j;
			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
			/*修改文件名*/
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*关闭句柄*/
				return -2;
			}
			len++;
			shu_zhi++;
		}
	}
	_findclose(handle); /*关闭句柄*/
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
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			len++;
		}
	}

	CString xiu_gai_j;
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
			{
				if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
				{
					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*关闭句柄*/
						return -2;
					}
					len++;
				}
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
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
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		xiu_gai_j = wen_jian_ming_j;
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
			{
				xuHaoT.Format(_T("_%u"), xu_hao);
				xiu_gai_j = wen_jian_ming_j;
				xiaBiaoU = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
				xiu_gai_j.Insert(xiaBiaoU, xuHaoT);   /*在查找到的下标处插入字符*/

				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;
				}
				len++;
				xu_hao++;
			}
		}
	}
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
			{
				if (xiu_gai_zhong_jian_h(xiu_gai_j, yuan_shi, xiu_gai))
				{
					xuHaoT.Format(_T("_%u"), xu_hao);
					xiu_gai_j = wen_jian_ming_j;
					xiaBiaoU = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
					xiu_gai_j.Insert(xiaBiaoU, xuHaoT);   /*在查找到的下标处插入字符*/

					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*关闭句柄*/
						return -2;
					}
					len++;
					xu_hao++;
				}
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
	return len;
}

int TiHuan::quan_bu_h(CString path, CString xiu_gai, CString kuo_zhan, unsigned int shu_zhi)
{
	int len = 0;
	CString kuo_zhan_ming_j;/*获取到的文件扩展名*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + _T("\\*") + kuo_zhan; /*拼接通配符,*是全部;还可以.jpg,这样只搜索后缀为.jpg的文件*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*转换后的文件路径*/
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	CString xu_hao_j;
	CString xiu_gai_j;/*修改后的含完整路径的文件名*/
	int xia_biao_j = 0;/*查找字符串指定字符的下标,从0开始*/
	if (fileinfo.attrib != _A_SUBDIR)
	{
// 		xu_hao_j.Format(_T("_%u"), shu_zhi);
// 		wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
// 		xiu_gai_j = wen_jian_ming_j;
// 		xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
// 		xiu_gai_j.Delete(0, xia_biao_j);
// 		xiu_gai_j.Insert(0, xiu_gai + xu_hao_j);   /*在查找到的下标处插入字符*/
// 
// 		xiu_gai_j = path + L"\\" + xiu_gai_j;
// 		wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
// 		/*修改文件名*/
// 		if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
// 		{
// 			_findclose(handle); /*关闭句柄*/
// 			return -2;
// 		}
		len++;
		shu_zhi++;
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
// 			xu_hao_j.Format(_T("_%u"), shu_zhi);
// 			wen_jian_ming_j = CString(fileinfo.name);         /*获取带扩展名的文件名*/
// 			xiu_gai_j = wen_jian_ming_j;
// 			xia_biao_j = xiu_gai_j.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
// 			xiu_gai_j.Delete(0, xia_biao_j);              /*从第一个字符开始删除到"."前的所有字符*/
// 			xiu_gai_j.Insert(0, xiu_gai + xu_hao_j);   /*从第一个字符我位置处插入字符*/
// 
// 			xiu_gai_j = path + L"\\" + xiu_gai_j;
// 			wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
// 			/*修改文件名*/
// 			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
// 			{
// 				_findclose(handle); /*关闭句柄*/
// 				return -2;
// 			}
			len++;
			shu_zhi++;
		}
	}
	_findclose(handle); /*关闭句柄*/
	return len;
}

int TiHuan::ShanChuH(CString path, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou)
{
	if (xia_biao <= 0 || xia_biao > 260)
	{
		return -5; /*要删除的字符数过多或者过少*/
	}
	int len = 0;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	unsigned short dianXiaoBiaoU = 0; /*扩展名"."的下标*/
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	path = path + _T("\\");
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
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
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
			if (xia_biao >= dianXiaoBiaoU+1)
			{
				_findclose(handle); /*关闭句柄*/
				return -4;  /*要删除的字符数大于文件名字符数*/
			}
			else
			{
				xiu_gai_j.Delete(0, xia_biao);
			}
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*关闭句柄*/
				return -2;   /*重命名出错*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
				if (xia_biao >= dianXiaoBiaoU + 1)
				{
					_findclose(handle); /*关闭句柄*/
					return -4;  /*要删除的字符数大于文件名字符数*/
				}
				else
				{
					xiu_gai_j.Delete(0, xia_biao);
				}
				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;  /*重命名出错*/
				}
				len++;
			}
		}
		_findclose(handle); /*关闭句柄*/
	} 
	else /*后*/
	{
		unsigned int xiaBiaoU = 1;
		CString XuHaoT;
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			XuHaoT.Format(_T("_%u"), xiaBiaoU);
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
			if (xia_biao >= dianXiaoBiaoU+1)
			{
				_findclose(handle); /*关闭句柄*/
				return -4;  /*要删除的字符数大于文件名字符数*/
			}
			else
			{
				/*从给定索引处的字符开始的字符串中删除一个或多个字符
				* 参数1: 要删除 的对象中第一个字符的从零开始的索引。
				* 参数2: 要删除的字符数
				* 返回:  删除后字符串长度
				*/
				xiu_gai_j.Delete(dianXiaoBiaoU - xia_biao, xia_biao);
				/*在字符串的给定索引处插入单个字符或子字符串
				* 参数1: 将在其之前进行插入的字符的索引
				* 参数2:指向要插入的子字符串的指针
				* 返回: 更改后字符串长度
				*/
				xiu_gai_j.Insert(dianXiaoBiaoU - xia_biao, XuHaoT);
			}
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*关闭句柄*/
				return -2;  /*重命名出错*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				XuHaoT.Format(_T("_%u"), xiaBiaoU);
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
				if (xia_biao >= dianXiaoBiaoU+1)
				{
					_findclose(handle); /*关闭句柄*/
					return -4;  /*要删除的字符数大于文件名字符数*/
				}
				else
				{
					/*从给定索引处的字符开始的字符串中删除一个或多个字符
					* 参数1: 要删除 的对象中第一个字符的从零开始的索引。
					* 参数2: 要删除的字符数
					* 返回:  删除后字符串长度
					*/
					xiu_gai_j.Delete(dianXiaoBiaoU - xia_biao, xia_biao);
					/*在字符串的给定索引处插入单个字符或子字符串
					* 参数1: 将在其之前进行插入的字符的索引
					* 参数2:指向要插入的子字符串的指针
					* 返回: 更改后字符串长度
					*/
					xiu_gai_j.Insert(dianXiaoBiaoU - xia_biao, XuHaoT);
					xiu_gai_j = path + xiu_gai_j;
					wen_jian_ming_j = path + wen_jian_ming_j;
					if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
					{
						_findclose(handle); /*关闭句柄*/
						return -2;  /*重命名出错*/
					}
					len++;
				}
			}
		}/*dfgeru52你好_3  geru52你好_14*/
		_findclose(handle); /*关闭句柄*/
	}
	return len;
}

int TiHuan::ShanChuH(CString path, CString xiu_gai, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou)
{
	int len = 0;
	CString wen_jian_ming_j;
	CString xiu_gai_j;
	unsigned short dianXiaoBiaoU = 0; /*扩展名"."的下标*/
	short FindXiaBiaoU = 0;   /*find返回的下标*/
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*";
	path = path + _T("\\");
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
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
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
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
				_findclose(handle); /*关闭句柄*/
				return -2;   /*重命名出错*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
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
					_findclose(handle); /*关闭句柄*/
					return -2;  /*重命名出错*/
				}
				len++;
			}
		}
		_findclose(handle); /*关闭句柄*/\
		return len;
	}
	else /*后*/
	{
		CString XuHaoT;
		unsigned short i = 0;
		unsigned short XiuGaiCiShuU = 0;
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			XuHaoT.Format(_T("_%u"), xia_biao);
			dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
			for (i = 0; i < dianXiaoBiaoU; i++)
			{
				/*查找
				* 要查找的内容""或要搜索的单个字符''
				* 开始搜索的字符串中字符的索引，或从头开始搜索的 0
				* 返回:失败返回-1,成功返回匹配的第一个字符的从零开始的索引
				*/
				FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
				/*从给定索引处的字符开始的字符串中删除一个或多个字符
				* 参数1: 要删除 的对象中第一个字符的从零开始的索引。
				* 参数2: 要删除的字符数
				* 返回:  删除后字符串长度
				*/
				if (-1 != FindXiaBiaoU)
				{
					xiu_gai_j.Delete(FindXiaBiaoU, 1);
					XiuGaiCiShuU++;
				}

			}
			/*在字符串的给定索引处插入单个字符或子字符串
				* 参数1: 将在其之前进行插入的字符的索引
				* 参数2:指向要插入的子字符串的指针
				* 返回: 更改后字符串长度
				*/
			xiu_gai_j.Insert(dianXiaoBiaoU - XiuGaiCiShuU, XuHaoT);
			xiu_gai_j = path + xiu_gai_j;
			wen_jian_ming_j = path + wen_jian_ming_j;
			if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
			{
				_findclose(handle); /*关闭句柄*/
				return -2;  /*重命名出错*/
			}
			len++;
		}
		while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
		{
			if (fileinfo.attrib != _A_SUBDIR)
			{
				wen_jian_ming_j = CString(fileinfo.name);
				xiu_gai_j = wen_jian_ming_j;
				XuHaoT.Format(_T("_%u"), xia_biao);
				dianXiaoBiaoU = xiu_gai_j.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
				for (i = 0; i < dianXiaoBiaoU; i++)
				{
					/*查找
					* 要查找的内容""或要搜索的单个字符''
					* 开始搜索的字符串中字符的索引，或从头开始搜索的 0
					* 返回:失败返回-1,成功返回匹配的第一个字符的从零开始的索引
					*/
					FindXiaBiaoU = xiu_gai_j.Find(xiu_gai);
					/*从给定索引处的字符开始的字符串中删除一个或多个字符
					* 参数1: 要删除 的对象中第一个字符的从零开始的索引。
					* 参数2: 要删除的字符数
					* 返回:  删除后字符串长度
					*/
					if (-1 != FindXiaBiaoU)
					{
						xiu_gai_j.Delete(FindXiaBiaoU, 1);
						XiuGaiCiShuU++;
					}

				}
				/*在字符串的给定索引处插入单个字符或子字符串
					* 参数1: 将在其之前进行插入的字符的索引
					* 参数2:指向要插入的子字符串的指针
					* 返回: 更改后字符串长度
					*/
				xiu_gai_j.Insert(dianXiaoBiaoU - XiuGaiCiShuU, XuHaoT);
				xiu_gai_j = path + xiu_gai_j;
				wen_jian_ming_j = path + wen_jian_ming_j;
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;  /*重命名出错*/
				}
				len++;
			}/*dfgeru52你好_3  geru52你好_14*/
			_findclose(handle); /*关闭句柄*/
		}
		return len;
	}
}

BOOL TiHuan::xiu_gai_kuo_zhan_ming_h(CString path, CString kuo_zhan, CString xiu_gai)
{
	CString kuo_zhan_ming_j; /*扩展名*/
	CString wen_jian_ming_j; /*文件名,文件路径*/
	if (path == _T(""))
	{
		return FALSE;
	}
	wen_jian_ming_j = path + L"\\*";
	/*将CString转换为char*类型*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	/*_findfirst
	参数1: 支持通配符,*.c表示当前路径下所有的后缀为.c的文件
	参数2: 这里就是用来存放文件信息的结构体的指针。这个结构体必须在调用此函数前声明
	*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)/*如果不是文件夹属性*/
	{
		
	}

	CString xiu_gai_j; /*要修改的字符*/
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);/*找到的文件名,包含扩展名*/

			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
			{
				/*计算扩展名长度*/
				/*从右开始删除对应长度的字符*/
				/*重新加上扩展名*/
				xiu_gai_j = path + L"\\" + xiu_gai_j + wen_jian_ming_j;
				wen_jian_ming_j = path + L"\\" + wen_jian_ming_j;
				/*移动目录或者文件,修改目录或者文件名
				* 参数1: 要修改目录或文件的路径与名字
				* 参数2: 文件或目录的新名称。新名称不得已存在
				* 返回值: 失败返回0
				*/
				//MoveFile(wen_jian_ming_j, xiu_gai_j);
				if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
				{
					_findclose(handle); /*关闭句柄*/
					return -2;
				}
			}
		}
	}
	_findclose(handle); /*关闭句柄*/

	//FindFirstFile


	return TRUE;
}

BOOL TiHuan::xiu_gai_zhong_jian_h(CString& wen_jian_ming, CString yuan_zi_fu, CString xiu_gai_zi_fu)
{
	int aa = wen_jian_ming.GetLength();/*计算字符串长度,中文也为1,实际上中文是2*/
	//int abc = a.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
	/*查找
	* 要查找的内容""或要搜索的单个字符''
	* 开始搜索的字符串中字符的索引，或从头开始搜索的 0
	* 返回:失败返回-1,成功返回匹配的第一个字符的从零开始的索引
	*/
	int aad = wen_jian_ming.Find(yuan_zi_fu);
	if (-1==aad)
	{
		return FALSE;
	}
	int aae = yuan_zi_fu.GetLength();
	/*从给定索引处的字符开始的字符串中删除一个或多个字符
	* 参数1: 要删除 的对象中第一个字符的从零开始的索引。
	* 参数2: 要删除的字符数
	* 返回:  删除后字符串长度
	*/
	int aag = wen_jian_ming.Delete(aad, aae);
	if (aag <= 0)
	{
		return FALSE;
	}
	/*在字符串的给定索引处插入单个字符或子字符串
	* 参数1: 将在其之前进行插入的字符的索引
	* 参数2:指向要插入的子字符串的指针
	* 返回: 更改后字符串长度
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
	CString ls;//局部变量
	switch (lei_xing)
	{
	case 0:/*在最前面添加*/
		xiu_gai_zi_fu = path + _T("\\") + xiu_gai_zi_fu + yuan_zi_fu;
		yuan_zi_fu = path + _T("\\") + yuan_zi_fu;
		break;
	case 1:/*在最前面添加 \"1_\"数字排序,可指定开始数字*/
		xiu_gai_zi_fu.Format(_T("%u_", xu_hao)); /*整数转换为字符,%u无符号十进制整数*/
		xiu_gai_zi_fu = path + L"\\" + xiu_gai_zi_fu + yuan_zi_fu;
		yuan_zi_fu = path + L"\\" + yuan_zi_fu;
		break;
	case 2:/*在最后面添加*/
		wen_jian_ming = yuan_zi_fu;
		lei_xing = wen_jian_ming.ReverseFind(_T('.'));/*从右往左开始查找 '.'*/
		wen_jian_ming.Insert(lei_xing, xiu_gai_zi_fu);      /*在查找到的下标处插入字符*/

		wen_jian_ming = path + L"\\" + wen_jian_ming;
		yuan_zi_fu = path + L"\\" + yuan_zi_fu;
		break;
	case 3:/*在最后面添加字符并用 \"_1\"数字排序,可指定开始数字*/
		xiu_gai_zi_fu.Format(xiu_gai_zi_fu + _T("_%u"), xu_hao);
		wen_jian_ming = yuan_zi_fu;
		lei_xing = wen_jian_ming.ReverseFind(_T('.'));       /*从右往左开始查找 '.'*/
		wen_jian_ming.Insert(lei_xing, xiu_gai_zi_fu);   /*在查找到的下标处插入字符*/

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

	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//第一次查找
	/*_findfirst
	参数1: 支持通配符,*.c表示当前路径下所有的后缀为.c的文件
	参数2: 这里就是用来存放文件信息的结构体的指针。这个结构体必须在调用此函数前声明
	*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			len++;
		}
	}

	CString xiu_gai_j;
	path = path + _T("\\");
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			xiu_gai_j = wen_jian_ming_j;
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			//kuo_zhan_ming_j = kuo_zhan_ming_j.MakeLower();         /*将扩展名转换为小写字母*/
			//if (kuo_zhan_ming_j == kuo_zhan)
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
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
						/*移动目录或者文件,修改目录或者文件名
						* 参数1: 要修改目录或文件的路径与名字
						* 参数2: 文件或目录的新名称。新名称不得已存在
						* 返回值: 失败返回0
						*/
						//MoveFile(wen_jian_ming_j, xiu_gai_j);
						if (!MoveFile(wen_jian_ming_j, xiu_gai_j))
						{
							_findclose(handle); /*关闭句柄*/
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
	_findclose(handle); /*关闭句柄*/
	return len;
}

int TiHuan::h_wen_jian_shu_liang(const char* path)
{
	int len = 0;
	long long handle;

	struct _finddata_t fileinfo;
	handle = _findfirst(path, &fileinfo);//第一次查找
	if (-1 == handle)
	{
		return FALSE;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		len++;
	}
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
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
	CString kuo_zhan_ming_j;/*获取到的文件扩展名*/
	CString wen_jian_ming_j;
	if (path == L"")
	{
		return -3;
	}
	wen_jian_ming_j = path + L"\\*" + kuo_zhan; /*拼接"\"和通配符,*后面还可以指定格式.jpg,这样只搜索后缀为.jpg的文件*/
	USES_CONVERSION;
	const char* path_jp = T2A(wen_jian_ming_j);/*转换后的文件路径*/
	long long handle;                 /*用于查找的句柄*/
	struct _finddata_t fileinfo;      /*文件信息的结构体*/
	handle = _findfirst(path_jp, &fileinfo);//获取句柄
	if (-1 == handle)
	{
		return -1;
	}
	if (fileinfo.attrib != _A_SUBDIR)
	{
		wen_jian_ming_j = CString(fileinfo.name);
		kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
		if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
		{
			len++;
		}
	}
	CString xiu_gai_j;/*修改后的含完整路径的文件名*/
	int xia_biao_j = 0;/*查找字符串指定字符的下标,从0开始*/
	while (!_findnext(handle, &fileinfo))//循环查找其他符合的文件，知道找不到其他的为止
	{
		if (fileinfo.attrib != _A_SUBDIR)
		{
			wen_jian_ming_j = CString(fileinfo.name);
			kuo_zhan_ming_j.Format(L"%s", PathFindExtension(wen_jian_ming_j));   /*获取文件扩展名*/
			if (kuo_zhan_ming_j.CollateNoCase(kuo_zhan) == 0) /*比较字符串,不区分大小写*/
			{
				len++;
			}
		}
	}
	_findclose(handle); /*关闭句柄*/
	return len;
}


