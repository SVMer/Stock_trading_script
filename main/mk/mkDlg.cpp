
// mkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mk.h"
#include "mkDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <process.h>
#include "workthread.h"
#include "choose_stock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();



// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmkDlg �Ի���

BEGIN_DHTML_EVENT_MAP(CmkDlg)

END_DHTML_EVENT_MAP()



IMPLEMENT_DYNAMIC(CmkDlg, CDHtmlDialog);

CmkDlg::CmkDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CmkDlg::IDD, CmkDlg::IDH, pParent)
{

	is_suspend=false;

	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CmkDlg::~CmkDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;




}

void CmkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmkDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT2, &CmkDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CmkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CmkDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CmkDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CmkDlg ��Ϣ�������


unsigned __stdcall ReceivingThrd(void * pParam);

BOOL CmkDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ȫ�ֵľ����ֵ����ʵҲ���Բ���ȫ�־�������ǽ�������������߳�
	
	hedit1=GetDlgItem(IDC_EDIT1)->GetSafeHwnd();
	hedit2=GetDlgItem(IDC_EDIT2)->GetSafeHwnd();
	hedit3=GetDlgItem(IDC_EDIT3)->GetSafeHwnd();


    GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);   //�ť���ɲ���





	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



void CmkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������





BOOL CmkDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CmkDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDHtmlDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmkDlg::OnBnClickedButton1()
{
	//SuspendThread(hWorkThread);  //����SuspendThreadʱ����С�ģ���Ϊ��֪����ͣ�߳�����ʱ���ڽ���ʲô������

	if(is_suspend==false)
	{      
		SuspendThread(hWorkThread); 
		is_suspend=true;
		SetDlgItemText(IDC_BUTTON1,"�����߳�");
	}
	else
	{
		ResumeThread(hWorkThread);
		is_suspend=false;
		SetDlgItemText(IDC_BUTTON1,"��ͣ�߳�");
	}


}


//void CmkDlg::OnEnChangeEdit1()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDHtmlDialog::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CmkDlg::OnBnClickedButton3()
{


				//���������߳�,Ҳ������Ҫ�Ĺ����̡߳�
			hWorkThread = (HANDLE)_beginthreadex( NULL, 0, &WorkThrd,(void *)0, 0, &WorkThreadID );   

			if(hWorkThread == NULL)
			AfxMessageBox("�޷����������߳�");

			if((SetThreadPriority(hWorkThread,THREAD_PRIORITY_TIME_CRITICAL)!=0) && (GetThreadPriority(hWorkThread) != THREAD_PRIORITY_TIME_CRITICAL))  //���㣬����������гɹ�;����Ϊ0�� 
			{
					 AfxMessageBox("�޷����ù����߳����ȼ����˳��߳�");
			 
			}


	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);   //�ť���ɲ���
    GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);   //�ť���ɲ���


}


void CmkDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	choose_stock  dlg;
	int nRet=dlg.DoModal();
	if(nRet==IDOK)  //ֻ�ڰ�ȷ����ť���غ��do something
	{
	}
}


//void CmkDlg::OnEnChangeEdit3()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDHtmlDialog::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}
