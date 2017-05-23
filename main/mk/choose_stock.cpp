// choose_stock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mk.h"
#include "choose_stock.h"
#include "afxdialogex.h"
#include "ADOConn.h"


extern bool is_set_parameter;
extern char **pstr_code;  
extern int pstr_code_size;  
extern char pstr_start_time[11],pstr_end_time[11];


// choose_stock �Ի���

IMPLEMENT_DYNAMIC(choose_stock, CDialog)

choose_stock::choose_stock(CWnd* pParent /*=NULL*/)
	: CDialog(choose_stock::IDD, pParent)
{



}

choose_stock::~choose_stock()
{
}

void choose_stock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON1, CButton1);
	//  DDX_Control(pDX, IDC_BUTTON2, CButton2);
	//  DDX_Control(pDX, IDC_BUTTON3, CButton3);
	//  DDX_Control(pDX, IDC_BUTTON4, CButton4);
}


BEGIN_MESSAGE_MAP(choose_stock, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &choose_stock::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &choose_stock::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &choose_stock::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &choose_stock::OnBnClickedButton4)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &choose_stock::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDOK, &choose_stock::OnBnClickedOk)
END_MESSAGE_MAP()


// choose_stock ��Ϣ�������


BOOL choose_stock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��  -----���������Ҫ��������
	/*��Ϊ�ؼ�������ֵ*/
	CTab=(CTabCtrl*)GetDlgItem(IDC_TAB1);
	CList1=(CListBox*)GetDlgItem(IDC_LIST1);
	CList2=(CListBox*)GetDlgItem(IDC_LIST2);

	CEdit2=(CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit3=(CEdit*)GetDlgItem(IDC_EDIT3);
	/*��ӱ�ǩҳ*/
	CTab->InsertItem(0,"Ʒ��");
	CTab->InsertItem(1,"ʱ��");

	/*��ſؼ�ָ�뵽��Ӧ�����飬���ڱ�ǩ����ʾ*/
		//��һ��ǩҳ
		pTab1_group[0]=CList1;
		pTab1_group[1]=CList2;
		pTab1_group[2]=GetDlgItem(IDC_BUTTON1);
		pTab1_group[3]=GetDlgItem(IDC_BUTTON2);
		pTab1_group[4]=GetDlgItem(IDC_BUTTON3);
		pTab1_group[5]=GetDlgItem(IDC_BUTTON4);
		//�ڶ���ǩҳ
		pTab2_group[0]=CEdit2;
		pTab2_group[1]=CEdit3;
		pTab2_group[2]=GetDlgItem(IDC_STATIC);
		pTab2_group[3]=GetDlgItem(IDC_STATIC1);
		Tab_hide_show(*pTab2_group,4,SW_HIDE);  //������

	/*��Ӵ��뵽listbox*/
	ADOConn a;
	_bstr_t bstrSQL;
	a.OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	bstrSQL="select code from code";
	m_pRecordset=a.GetRecordSet(bstrSQL);


		for(m_pRecordset->MoveFirst();!m_pRecordset->adoEOF;m_pRecordset->MoveNext())  //�������е�֤ȯ����
		{
			CList1->AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("code"));
		}

	a.ExitConnect();



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void choose_stock::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCount;

	CArray<int,int> aryListBoxSel;
	nCount=CList1->GetSelCount();

    aryListBoxSel.SetSize(nCount);
    CList1->GetSelItems(nCount, aryListBoxSel.GetData());

    CString strTmp;

	for(int i=0; i<aryListBoxSel.GetCount();i++)
   {
    CList1->GetText(aryListBoxSel[i], strTmp);

	CList2->AddString(strTmp);
	} 

	for(int i=aryListBoxSel.GetCount()-1; i>=0;i--)     //�ӵײ���ʼɾ������Ӱ��indexֵ
   {
	CList1->DeleteString(aryListBoxSel[i]);

	} 

 

}


void choose_stock::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nCount;

	CArray<int,int> aryListBoxSel;
	nCount=CList2->GetSelCount();

    aryListBoxSel.SetSize(nCount);
    CList2->GetSelItems(nCount, aryListBoxSel.GetData());

    CString strTmp;

	for(int i=0; i<aryListBoxSel.GetCount();i++)
   {
    CList2->GetText(aryListBoxSel[i], strTmp);

	CList1->AddString(strTmp);
	} 

	for(int i=aryListBoxSel.GetCount()-1; i>=0;i--)     //�ӵײ���ʼɾ������Ӱ��indexֵ
   {
	CList2->DeleteString(aryListBoxSel[i]);

	} 

}


//void choose_stock::OnLbnSelchangeList1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void choose_stock::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int nCount;

	nCount=CList1->GetCount();

    CString strTmp;

	for(int i=0; i<nCount;i++)
   {
    CList1->GetText(i, strTmp);

	CList2->AddString(strTmp);
	} 

	for(int i=nCount-1; i>=0;i--)     //�ӵײ���ʼɾ������Ӱ��indexֵ
   {
	CList1->DeleteString(i);

	} 

}


void choose_stock::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
			int nCount;

	nCount=CList2->GetCount();

    CString strTmp;

	for(int i=0; i<nCount;i++)
   {
    CList2->GetText(i, strTmp);

	CList1->AddString(strTmp);
	} 

	for(int i=nCount-1; i>=0;i--)     //�ӵײ���ʼɾ������Ӱ��indexֵ
   {
	CList2->DeleteString(i);

	} 

}


void choose_stock::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int sel = CTab->GetCurSel();

	int n;

	switch(sel)
			{

			case 0:
            /*��Ȼ���벻�����ۼ�࣬������ĺ��Ĳ����ڴ�*/
			n=sizeof(pTab1_group)/sizeof(CWnd*);
			Tab_hide_show(*pTab1_group,n,SW_SHOW);

			n=sizeof(pTab2_group)/sizeof(CWnd*);
			Tab_hide_show(*pTab2_group,n,SW_HIDE);

			break;

			case 1:
            n=sizeof(pTab1_group)/sizeof(CWnd*);
			Tab_hide_show(*pTab1_group,n,SW_HIDE);

			n=sizeof(pTab2_group)/sizeof(CWnd*);
			Tab_hide_show(*pTab2_group,n,SW_SHOW);
			break;

			}

	*pResult = 0;

}


void choose_stock::Tab_hide_show(CWnd *pWnd,int nSize,int nState)
{

	for(int i=0;i<nSize;i++,pWnd++)
	{
		pWnd->ShowWindow(nState);

	}
}

void choose_stock::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*����һ��ǩҳ����Ʒ��*/
	int nCount=CList2->GetCount();
	if(nCount!=0)
	{
		if(pstr_code!=NULL)    //��ɾ���ϴη�����ڴ�
		{
			for(int i=0;i<pstr_code_size;i++)
                   delete[] pstr_code[i];         
			delete[] pstr_code;

		}
		pstr_code=new char*[nCount];  //�����ά������Щ�鷳,deleteʱҲҪע�⣬���ڴ�leak
		pstr_code_size=nCount;     //ͬʱ��ס��С

		for(int i=0;i<nCount;i++)
		 {
			 pstr_code[i]=new char[6]; 

		 }
			CString strtemp;  //����д�Ĳ�Ư�������þͺ���
		for(int i=0; i<nCount;i++)
	   {
		   CList2->GetText(i,strtemp);
		   strcpy(pstr_code[i],strtemp.GetBuffer()); // pstr_code[i]=strtemp.GetBuffer();����д�Ǵ�ģ��Ὣpstr_code[i]ָ��strtemp���ڴ��ַ����strtemp�Ǿֲ�����
		   //MessageBox(pstr_code[i]);
		} 
	 }

	/*���ڶ���ǩҳ����ʱ��*/
	if((CEdit2->GetWindowTextLength())!=0)
	{
		CEdit2->GetWindowTextA(pstr_start_time,11);

	}
	if((CEdit3->GetWindowTextLength())!=0)
	{
		CEdit3->GetWindowTextA(pstr_end_time,11);
	}


	CDialog::OnOK(); 

}
