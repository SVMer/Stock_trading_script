#pragma once


// choose_stock �Ի���

class choose_stock : public CDialog
{
	DECLARE_DYNAMIC(choose_stock)

public:
	/*����ؼ�����*/
	CTabCtrl *CTab;
	/*��һ����Ĳ��ֿؼ�*/
	CWnd *pTab1_group[6];   //��ָ����������ŵ�һ��������пؼ�
	CListBox *CList1;
	CListBox *CList2;
	/*�ڶ�����Ĳ��ֿؼ�*/
	CWnd *pTab2_group[4]; 
	CEdit *CEdit2;
	CEdit *CEdit3;




	choose_stock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~choose_stock();

// �Ի�������
	enum { IDD = IDD_CHOOSE_STOCK };

protected:
	void Tab_hide_show(CWnd *pWnd,int nSize,int nState);  //tabҳ�ؼ�����ʾ������

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedOk();
};
