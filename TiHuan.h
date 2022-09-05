#pragma once
#include <string>
using namespace std;
class TiHuan
{

public:
	TiHuan();
	~TiHuan();


protected:
	/*************************************************
	 函数名称:
	 函数功能:
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/

private:
	/*************************************************
	 函数名称:
	 函数功能:
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/
	int zi_fu_chuan_chang_du_h(CString zi_fu_c);

public:
	

	/*************************************************
	 函数名称:zui_qian_h
	 函数功能:在文件名的最前面添加字符
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 path:     文件的当前文件夹路径
	 xiu_gai:  要添加的字符
	 kuo_zhan: 文件类型,扩展名; .txt
	 输出参数说明:
	 返回值的说明:
	 成功: 返回修改的文件数量
	 失败:
	 -1 : 获取文件句柄失败
	 -2 : 重命名文件失败
	 -3 : 文件路径为空
	 其它说明:无
	*************************************************/
	int zui_qian_h(CString path,CString xiu_gai,CString kuo_zhan);

	/*************************************************
	 函数名称:zui_qian_h
	 函数功能:在文件名的最前面添加"1_"类型的数字编号
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 path:     文件的当前文件夹路径
	 shu_zhi:  要添加的起始数字
	 kuo_zhan: 文件类型,扩展名; .txt
	 输出参数说明:
	 返回值的说明:
	 成功: 返回修改的文件数量
	 失败:
	 -1 : 获取文件句柄失败
	 -2 : 重命名文件失败
	 -3 : 文件路径为空
	 其它说明:无
	*************************************************/
	int zui_qian_h(CString path, unsigned int shu_zhi, CString kuo_zhan);

	/*************************************************
	 函数名称:zui_qian_h
	 函数功能:在文件名的最后(不包括扩展名)添加字符,并且只搜索与扩展名一致的文件,不区分大小写
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 path:     文件的当前文件夹路径
	 xiu_gai:  要添加的字符
	 kuo_zhan: 要查找修改的文件类型,扩展名; .txt
	 输出参数说明:
	 返回值的说明:
	 成功: 返回修改的文件数量
	 失败:
	 -1 : 获取文件句柄失败
	 -2 : 重命名文件失败
	 -3 : 文件路径为空
	 其它说明:值功能不会对里面包含的子文件夹起作用
	*************************************************/
	int zui_hou_h(CString path, CString xiu_gai, CString kuo_zhan);

	/*************************************************
	 函数名称:zui_qian_h
	 函数功能:在文件名的最后(不包括扩展名)添加"_1"类型的数字编号
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 path:     文件的当前文件夹路径
	 shu_zhi:  要添加的起始数字
	 kuo_zhan: 文件类型,扩展名; .txt
	 输出参数说明:
	 返回值的说明:
	 成功: 返回修改的文件数量
	 失败:
	 -1 : 获取文件句柄失败
	 -2 : 重命名文件失败
	 -3 : 文件路径为空
	 其它说明:无
	*************************************************/
	int zui_hou_h(CString path, CString xiu_gai, unsigned int shu_zhi, CString kuo_zhan);

	/*************************************************
	 函数名称: zhong_jian_h
	 函数功能: 修改替换文件字符
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/
	int zhong_jian_h(CString path, CString yuan_shi, CString xiu_gai, CString kuo_zhan);

	int zhong_jian_h(CString path, CString yuan_shi, CString xiu_gai, unsigned int xu_hao, CString kuo_zhan);

	/*************************************************
	 函数名称: quan_bu_h
	 函数功能: 全部重命名文件名,并以"_1"的格式排序
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:
	 如果全部为中文,可能存在序号与文件修改数量计数+1的情况,就是while循环会多循环一次;
	 但是名字里只要有1个英文就能避免这个问题,目前还未解决,目前知道的是,不修改文件名,
	 全中文名 _findnext函数查找是没问题的,只有一边查找,一边修改为全中文名会这样
	*************************************************/
	int quan_bu_h(CString path, CString xiu_gai, CString kuo_zhan, unsigned int shu_zhi=0);

	int ShanChuH(CString path, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou = TRUE);

	int ShanChuH(CString path, CString xiu_gai, unsigned short xia_biao, CString kuo_zhan, BOOL qian_hou = TRUE);



	/*************************************************
	 函数名称: xiu_gai_kuo_zhan_ming_h
	 函数功能: 修改扩展名
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/
	BOOL xiu_gai_kuo_zhan_ming_h(CString path, CString kuo_zhan, CString xiu_gai);

	/*************************************************
	 函数名称:xiu_gai_zhong_jian_h
	 函数功能:修改文件名中间字符串
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 wen_jian_ming : 文件名
	 yuan_zi_fu :    要修改的字符
	 xiu_gai_zi_fu : 修改后的字符
	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/
	BOOL xiu_gai_zhong_jian_h(CString &wen_jian_ming, CString yuan_zi_fu, CString xiu_gai_zi_fu);

	BOOL XiuGaiWenJianMingH(CString path, CString& wen_jian_ming, CString& yuan_zi_fu, CString xiu_gai_zi_fu, unsigned short lei_xing, unsigned int xu_hao);

	/*************************************************
	 函数名称: wen_jian_gai_ming_h
	 函数功能: 未定
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:

	 输出参数说明:
	 返回值的说明:

	 其它说明:无
	*************************************************/
	int wen_jian_gai_ming_h(CString path, CString kuo_zhan, CString yuan_zi_fu, CString xiu_gai_zi_fu, unsigned int shu_zi_xu_hao, unsigned short gui_ze_xu_hao);


	/*************************************************
	 函数名称:h_wen_jian_shu_liang
	 函数功能:计算要修改文件名的文件数量
	 被本函数调用的函数清单:
	 调用本函数的函数清单:
	 输入参数说明:
	 path : 保存文件的路径
	 输出参数说明:
	 返回值的说明: 文件数量
	 其它说明:无
	*************************************************/
	int h_wen_jian_shu_liang(const char* path);

	int tong_pei_fu_h(CString path, CString kuo_zhan);

	
};

