
// WEN_JIAN_PI_LIANG_GAI_MINGDlg.h: 头文件
//

#pragma once
#include "TiHuan.h"

// CWENJIANPILIANGGAIMINGDlg 对话框
class CWENJIANPILIANGGAIMINGDlg : public CDialogEx
{
// 构造
public:
	CWENJIANPILIANGGAIMINGDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEN_JIAN_PI_LIANG_GAI_MING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	
	// 文件夹路径
	CString bjk_Path;
	CString path_L;
	// 下拉框_规则
	CComboBox xlk_GZ;
	unsigned short dang_qian_lie;
	// 下拉框_扩展名
	CComboBox xlk_KZ;
	unsigned short dang_qian_kuo_zhan;
	CString kuo_zhan_ming_L;
	// 编辑框_原始名
	CString bjk_YM;
	// 编辑框_修改的名字
	CString bjk_GM;
	// 单选框_规则替换
	BOOL dxk_GZ;
	// 单选框_自定义替换
	BOOL dxk_ZDY;
	// 单选框_包含子文件夹
	BOOL dxk_BH;
	// 编辑框_规则修改名
	CString bjk_GZXG;
	// //编辑框_扩展自定义
	CString bjk_kuo_zhan_zdy;

	CEdit* bjk_yin_chang_P;        /*对应 编辑框bjk_YM*/
	CEdit* bjk_yin_chang_xu_hao_P; /*对应 编辑框bjk_GZXG*/
	CEdit* bjk_kuo_zhan_zi_ding_yi_P; /*对应 编辑框bjk_kuo_zhan_zdy*/
	CEdit* wbk_ti_huan_P;          /*对应 文本控件 "替换"*/
	CEdit* wbk_xu_hao_P;           /*对应 文本控件 "序号"*/ 

	//TiHuan* ti_huan_LP;
	BOOL xlk_init(); /*初始化下拉框*/
	void ZiShenPathL(); /*获取自身所在文件夹路径*/

	/*多线程*/
	CWinThread* cThread;
	CCriticalSection ljq;//临界区

	int c_tmain(CString m);
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnEnChangeEdit4();
};
/*多线程执行函数*/
UINT _cdecl ti_huan(LPVOID lpParam);