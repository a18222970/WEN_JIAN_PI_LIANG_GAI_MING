
// WEN_JIAN_PI_LIANG_GAI_MINGDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "WEN_JIAN_PI_LIANG_GAI_MING.h"
#include "WEN_JIAN_PI_LIANG_GAI_MINGDlg.h"
#include "afxdialogex.h"

#include <windows.h>
#include <shlwapi.h> 
//#include <afxpriv.h>//
#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWENJIANPILIANGGAIMINGDlg 对话框



CWENJIANPILIANGGAIMINGDlg::CWENJIANPILIANGGAIMINGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEN_JIAN_PI_LIANG_GAI_MING_DIALOG, pParent)
	, bjk_Path(_T(""))
	, bjk_YM(_T(""))
	, bjk_GM(_T(""))
	, dxk_GZ(TRUE)
	, dxk_ZDY(FALSE)
	, dxk_BH(FALSE)
	, bjk_GZXG(_T(""))
	, bjk_kuo_zhan_zdy(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWENJIANPILIANGGAIMINGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bjk_Path);
	DDX_Control(pDX, IDC_COMBO1, xlk_GZ);
	DDX_Text(pDX, IDC_EDIT2, bjk_YM);
	DDX_Text(pDX, IDC_EDIT3, bjk_GM);
	DDX_Check(pDX, IDC_CHECK1, dxk_GZ);
	DDX_Check(pDX, IDC_CHECK2, dxk_ZDY);
	DDX_Check(pDX, IDC_CHECK3, dxk_BH);
	DDX_Text(pDX, IDC_EDIT4, bjk_GZXG);
	DDX_Control(pDX, IDC_COMBO2, xlk_KZ);
	DDX_Text(pDX, IDC_EDIT5, bjk_kuo_zhan_zdy);
}

BEGIN_MESSAGE_MAP(CWENJIANPILIANGGAIMINGDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CWENJIANPILIANGGAIMINGDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CWENJIANPILIANGGAIMINGDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &CWENJIANPILIANGGAIMINGDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CWENJIANPILIANGGAIMINGDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CWENJIANPILIANGGAIMINGDlg::OnBnClickedCheck2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CWENJIANPILIANGGAIMINGDlg::OnCbnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CWENJIANPILIANGGAIMINGDlg::OnCbnSelchangeCombo2)
	//ON_CBN_KILLFOCUS(IDC_COMBO1, &CWENJIANPILIANGGAIMINGDlg::OnCbnKillfocusCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT4, &CWENJIANPILIANGGAIMINGDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CWENJIANPILIANGGAIMINGDlg 消息处理程序

BOOL CWENJIANPILIANGGAIMINGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitializeCriticalSection(ljq);//初始化临界区
	xlk_init();
	ZiShenPathL();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWENJIANPILIANGGAIMINGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWENJIANPILIANGGAIMINGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWENJIANPILIANGGAIMINGDlg::OnBnClickedCancel()
{
	// 退出
	CDialogEx::OnCancel();
}



void CWENJIANPILIANGGAIMINGDlg::OnBnClickedOk2()
{
	// 开始
	cThread = AfxBeginThread(ti_huan, this);//建立新线程
}

/*选择文件夹_按钮*/
void CWENJIANPILIANGGAIMINGDlg::OnBnClickedOk()
{
	CString m_saveFilePath;
	//打开文件，获取文件路径名
	TCHAR szPath[_MAX_PATH] = { 0 };
	BROWSEINFO bi;
	bi.hwndOwner = GetSafeHwnd();/*对话框的所有者窗口句柄; GetSafeHwnd() : 返回窗口的窗口句柄*/
	bi.pidlRoot = NULL; /*一个 PIDL，它指定开始浏览的根文件夹的位置;可以为NULL,使用默认位置*/
	bi.lpszTitle = L"选择文件所在文件夹"; /*指向显示在对话框中树视图控件上方的以空字符结尾的字符串的指针*/
	bi.pszDisplayName = szPath; /*指向缓冲区的指针，用于接收用户选择的文件夹的显示名称*/
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//BIF_BROWSEFILEJUNCTIONS;// BIF_NEWDIALOGSTYLE;//BIF_RETURNONLYFSDIRS; /*指定对话框选项的标志*/
	bi.lpfn = NULL;/*指向应用程序定义函数的指针，当事件发生时对话框调用该函数,该成员可以是NULL。*/
	bi.lParam = NULL;/*初始化打开目录的回调函数; (long)(m_cSisDes.GetBuffer(m_cSisDes.GetLength()));//初始化路径，形如(_T("c:\\Symbian"));*/
	/*LPITEMIDLIST 包含项目标识符列表*/
	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);/*显示一个对话框，使用户能够选择 Shell 文件夹。*/
	if (pItemIDList)
	{
		/*SHGetPathFromIDList
		* 将项目标识符列表转换为文件系统路径
		* 参数1:项目标识符列表的地址，它指定相对于命名空间根（桌面）的文件或目录位置
		* 参数2:接收文件系统路径的缓冲区地址。此缓冲区的大小必须至少为 MAX_PATH 个字符。
		*/
		if (SHGetPathFromIDList(pItemIDList, szPath))/*将项目标识符列表转换为文件系统路径。*/
		{
			m_saveFilePath = szPath;
			//m_saveFilePath = m_saveFilePath + L"\\";
		}

		//use IMalloc interface for avoiding memory leak  
		IMalloc* pMalloc = NULL; /*分配、释放和管理内存*/
		if (SUCCEEDED(SHGetMalloc(&pMalloc)))/*检索指向 Shell 的IMalloc接口的指针。*/
		{
			pMalloc->Free(pItemIDList);/*释放先前分配的内存块*/
			pMalloc->Release();/*释放指针*/
		}
		bjk_Path = m_saveFilePath;
		UpdateData(FALSE);
	}
}


void CWENJIANPILIANGGAIMINGDlg::OnBnClickedCheck1()
{
	// 规则替换
	UpdateData(TRUE);//刷新控件
	if (dxk_GZ)
	{
		dxk_ZDY = FALSE;
	} 
	else
	{
		dxk_ZDY = TRUE;
	}
	UpdateData(FALSE);//刷新控件
}


void CWENJIANPILIANGGAIMINGDlg::OnBnClickedCheck2()
{
	// 自定义替换
	UpdateData(TRUE);
	if (dxk_ZDY)
	{
		dxk_GZ = FALSE;
	} 
	else
	{
		dxk_GZ = TRUE;
	}
	UpdateData(FALSE);
}

BOOL CWENJIANPILIANGGAIMINGDlg::xlk_init()
{
	/*设置下拉框*/
	xlk_GZ.InsertString(0, _T("在最前面添加"));
	xlk_GZ.InsertString(1, _T("在最前面添加 \"1_\"数字排序,可指定开始数字"));
	xlk_GZ.InsertString(2, _T("在最后面添加"));
	xlk_GZ.InsertString(3, _T("在最后面添加字符并用 \"_1\"数字排序,可指定开始数字"));
	xlk_GZ.InsertString(4, _T("某段字符替换"));
	xlk_GZ.InsertString(5, _T("某段字符替换并在最后面添加 \"_1\"数字排序,可指定开始数字"));
	xlk_GZ.InsertString(6, _T("删除单个同一字符"));
	xlk_GZ.InsertString(7, _T("删除单个同一字符并在最后面添加 \"_1\"数字排序,可指定开始数字"));
	xlk_GZ.InsertString(8, _T("全部重命名并数字排序  \"_1\"开始"));
	xlk_GZ.InsertString(9, _T("删除文件名中的前几位"));
	xlk_GZ.InsertString(10, _T("删除文件名中的后几位,并以格式 \"_1\"开始排序"));
	xlk_GZ.SetCurSel(0);           //初始显示第几项的内容
	dang_qian_lie = 0;  
	xlk_KZ.InsertString(0, _T(".jpg"));
	xlk_KZ.InsertString(1, _T(".gif"));
	xlk_KZ.InsertString(2, _T(".txt"));
	xlk_KZ.InsertString(3, _T(".pdf"));
	xlk_KZ.InsertString(4, _T(".mp4"));
	xlk_KZ.InsertString(5, _T("自定义"));
	xlk_KZ.SetCurSel(0);

	dang_qian_kuo_zhan = 0;
	xlk_KZ.GetLBText(dang_qian_kuo_zhan, kuo_zhan_ming_L);
	bjk_yin_chang_P        = (CEdit*)GetDlgItem(IDC_EDIT2);//编辑框_原始字符指针
	bjk_yin_chang_xu_hao_P = (CEdit*)GetDlgItem(IDC_EDIT4);//编辑框_规则修改名(序号)指针
	bjk_kuo_zhan_zi_ding_yi_P= (CEdit*)GetDlgItem(IDC_EDIT5);//编辑框_扩展自定义指针
	wbk_ti_huan_P          = (CEdit*)GetDlgItem(IDC_STATIC_02);//文本控件"替换"
	wbk_xu_hao_P           = (CEdit*)GetDlgItem(IDC_STATIC_01);//文本控件"序号"
	bjk_yin_chang_P->ShowWindow(FALSE);//隐藏控件
	bjk_yin_chang_xu_hao_P->ShowWindow(FALSE);//隐藏控件
	wbk_ti_huan_P->ShowWindow(FALSE);//隐藏控件
	wbk_xu_hao_P->ShowWindow(FALSE); //隐藏控件
	bjk_kuo_zhan_zi_ding_yi_P->ShowWindow(FALSE); //隐藏控件

	/*在控件显示了的情况下*/
// 	bjk_yin_chang_P->EnableWindow(FALSE);//控件不可用,颜色变灰色
// 	bjk_yin_chang_P->EnableWindow(TRUE); //控件可用,颜色正常
	return 0;
}

void CWENJIANPILIANGGAIMINGDlg::ZiShenPathL()
{
	/*获取程序自身所在文件夹*/
	TCHAR  FileModule[260]{};//保存程序自身路径缓冲区
	/*函数:GetModuleFileName
	* 作用: 检索包含指定模块的文件的完全限定路径。该模块必须已被当前进程加载。
	* 参数1:正在请求其路径的已加载模块的句柄。如果此参数为NULL，则 GetModuleFileName检索当前进程的可执行文件的路径。
	* 参数2:指向接收模块完全限定路径的缓冲区的指针,用来保存获取到的路径
	* 参数3:缓冲区(保存路径)的大小,以TCHARs 为单位。
	*/
	GetModuleFileName(NULL, FileModule, 0x100);
	/*计算字符串长度*/
	int ii = 0;
	for (int i = 260 - 1; FileModule[i] != L'\\'; i--)//字符串从后到前比较,如果不为'\'就将FileModule[i]赋值为0,为'\'时循环终止
	{
		FileModule[i] = 0;
		ii++;
	}
	FileModule[260 - 1 - ii] = 0;//消除斜杠'\'
	bjk_Path.Format(L"%s", FileModule);//图片完整路径
	UpdateData(FALSE);
}

UINT _cdecl ti_huan(LPVOID lpParam)
{
	CWENJIANPILIANGGAIMINGDlg* gai_ming_LP = (CWENJIANPILIANGGAIMINGDlg*)lpParam;
	TiHuan ti_huan_LP;  /*修改文件名的类*/
	//gai_ming_LP->dang_qian_lie;
	CString path;
	int len = 0;    /*修改的文件总数*/
	int xu_hao = 1; /*要添加的数字序号*/
	char ai = 0;
	//gai_ming_LP->path_L = L"L:\\收到";
	switch (gai_ming_LP->dang_qian_lie)
	{
	case 0:/*在最前面添加*/
		len = ti_huan_LP.zui_qian_h(gai_ming_LP->path_L, gai_ming_LP->bjk_GM,gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 1:/*在最前面添加 \"1_\"数字排序,可指定开始数字*/
		if (gai_ming_LP->bjk_GZXG==_T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GZXG);
		}	
		len = ti_huan_LP.zui_qian_h(gai_ming_LP->path_L, xu_hao, gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 2:/*在最后面添加*/
		len = ti_huan_LP.zui_hou_h(gai_ming_LP->path_L, gai_ming_LP->bjk_GM, gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 3:/*在最后面添加字符并用 \"_1\"数字排序,可指定开始数字*/
		if (gai_ming_LP->bjk_GZXG == _T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GZXG);
		}
		len = ti_huan_LP.zui_hou_h(gai_ming_LP->path_L, gai_ming_LP->bjk_GM, xu_hao, gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 4:/*某段字符替换*/
		len = ti_huan_LP.zhong_jian_h(gai_ming_LP->path_L, gai_ming_LP->bjk_YM, gai_ming_LP->bjk_GM, gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 5:/*某段字符替换并在最后面添加 \"_1\"数字排序,可指定开始数字*/
		if (gai_ming_LP->bjk_GZXG == _T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GZXG);
		}
		len = ti_huan_LP.zhong_jian_h(gai_ming_LP->path_L, gai_ming_LP->bjk_YM, gai_ming_LP->bjk_GM, xu_hao,gai_ming_LP->kuo_zhan_ming_L);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 6:/*删除指定字符*/
		ai = gai_ming_LP->bjk_GM.GetLength();/*计算字符串长度,中文也为1,实际上中文是2*/
		if (ai != 1)
		{
			AfxMessageBox(_T("请输入单个字符"));
			break;
		}
		xu_hao = 0;
		len = ti_huan_LP.ShanChuH(gai_ming_LP->path_L, gai_ming_LP->bjk_GM, xu_hao, gai_ming_LP->kuo_zhan_ming_L, TRUE);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 7:/*删除指定字符并在最后面添加 \"_1\"数字排序,可指定开始数字*/
		ai = gai_ming_LP->bjk_GM.GetLength();/*计算字符串长度,中文也为1,实际上中文是2*/
		if (ai != 1)
		{
			AfxMessageBox(_T("请输入单个字符"));
			break;
		}
		if (gai_ming_LP->bjk_GZXG == _T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GZXG);
		}
		len = ti_huan_LP.ShanChuH(gai_ming_LP->path_L, gai_ming_LP->bjk_GM, xu_hao, gai_ming_LP->kuo_zhan_ming_L, FALSE);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 8:/*全部重命名并数字排序  \"_1\"开始*/
		len = ti_huan_LP.quan_bu_h(gai_ming_LP->path_L, gai_ming_LP->bjk_GM, gai_ming_LP->kuo_zhan_ming_L,1);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 9:/*删除文件名中的前几位*/
		if (gai_ming_LP->bjk_GM == _T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GM);
		}
		len = ti_huan_LP.ShanChuH(gai_ming_LP->path_L, xu_hao, gai_ming_LP->kuo_zhan_ming_L,TRUE);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	case 10:/*删除文件名中的后几位,并以格式 \"_1\"开始排序*/
		if (gai_ming_LP->bjk_GM == _T(""))
		{
			xu_hao = 1;
		}
		else
		{
			xu_hao = _ttoi(gai_ming_LP->bjk_GM);
		}
		len = ti_huan_LP.ShanChuH(gai_ming_LP->path_L, xu_hao, gai_ming_LP->kuo_zhan_ming_L,FALSE);
		path.Format(L"一共修改了 %d 个文件", len);
		AfxMessageBox(path);
		break;
	default:
		break;
	}



	return 0;
}

/*下拉选择框的选择的项改变时消息处理事件*/
void CWENJIANPILIANGGAIMINGDlg::OnCbnSelchangeCombo1()
{
	UpdateData(TRUE);//用于将屏幕上控件中的数据交换到变量中。
	dang_qian_lie = xlk_GZ.GetCurSel();  //获取当前项的序号
	wbk_ti_huan_P->ShowWindow(FALSE);//隐藏控件
	bjk_yin_chang_P->ShowWindow(FALSE);//隐藏控件
	bjk_yin_chang_xu_hao_P->ShowWindow(FALSE);//隐藏控件
	wbk_xu_hao_P->ShowWindow(FALSE);//隐藏控件
	if (dang_qian_lie == 5)
	{
		bjk_yin_chang_xu_hao_P->ShowWindow(TRUE);//显示控件
		bjk_yin_chang_P->ShowWindow(TRUE);//显示控件
		wbk_xu_hao_P->ShowWindow(TRUE);//显示控件
		wbk_ti_huan_P->ShowWindow(TRUE);//显示控件
		bjk_GZXG = _T("1");
		UpdateData(FALSE);//用于将数据在屏幕中对应控件中显示出来。
	}
	if (dang_qian_lie == 1 || dang_qian_lie == 3 || dang_qian_lie == 7)
	{
		bjk_yin_chang_xu_hao_P->ShowWindow(TRUE);
		wbk_xu_hao_P->ShowWindow(TRUE);
		bjk_GZXG = _T("1");
		UpdateData(FALSE);
	}
	if (dang_qian_lie == 9 || dang_qian_lie == 10)
	{
		bjk_GM = _T("1");
		UpdateData(FALSE);
	}
	if (dang_qian_lie == 4)
	{
		bjk_yin_chang_P->ShowWindow(TRUE);
		wbk_ti_huan_P->ShowWindow(TRUE);
	}
	//xlk_GZ.SetCurSel(dang_qian_lie);
	//UpdateData(FALSE);
}

/*扩展下拉选择框的选择的项改变时消息处理事件*/
void CWENJIANPILIANGGAIMINGDlg::OnCbnSelchangeCombo2()
{
	UpdateData(TRUE);
	dang_qian_kuo_zhan = xlk_KZ.GetCurSel();
	if (dang_qian_kuo_zhan == 5)
	{
		bjk_kuo_zhan_zi_ding_yi_P->ShowWindow(TRUE);
		UpdateData(FALSE);
	}
	else
	{
		/*获取下拉框选中的值*/
		xlk_KZ.GetLBText(dang_qian_kuo_zhan, kuo_zhan_ming_L);
		//GetDlgItem(IDC_COMBO2).GetWindowText(kuo_zhan_ming_L)

		bjk_kuo_zhan_zi_ding_yi_P->ShowWindow(FALSE);
		UpdateData(FALSE);
	}

	

}

/*编辑框_路径 失去焦点事件*/
void CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit1()
{
	// 编辑框_路径
	UpdateData(TRUE);//保存控件数据
	path_L.Format(bjk_Path);
}

/*编辑框_要替换的字符 失去焦点事件*/
void CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit2()
{
	UpdateData(TRUE);//保存控件数据
}

/*编辑框_替换后的字符 失去焦点事件*/
void CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit3()
{
	UpdateData(TRUE);//保存控件数据
}

/*编辑框_数字序号 失去焦点事件*/
void CWENJIANPILIANGGAIMINGDlg::OnEnKillfocusEdit4()
{
	UpdateData(TRUE);//保存控件数据
	
	
}

/*取得文件的后缀名*/
int CWENJIANPILIANGGAIMINGDlg::c_tmain(CString m)
{
// 	CString::MakeUpper(); //全部转化为大写;
// 	CString::MakeLower(); //全部转化为小写;
	TCHAR szEXEPath[2048];
	LPTSTR pszExtension;
	GetModuleFileName(NULL, szEXEPath, 2048);
	pszExtension = PathFindExtension(szEXEPath);//取得文件的后缀名
	if (_tcscmp(pszExtension, _T(".png")) == 0)
	{
		return 1;
	}
	return 0;
}





void CWENJIANPILIANGGAIMINGDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//bjk_GZXG = bjk_GZXG;
}
