
// mkDlg.h : ͷ�ļ�
//

#pragma once

class CmkDlgAutoProxy;


// CmkDlg �Ի���
class CmkDlg : public CDHtmlDialog
{
	DECLARE_DYNAMIC(CmkDlg);
	friend class CmkDlgAutoProxy;

// ����
public:
	CmkDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CmkDlg();


	
	//�����߳̾����ID
	HANDLE hWorkThread;
    unsigned WorkThreadID;
	bool is_suspend; //������ͣ������



// �Ի�������
	enum { IDD = IDD_MK_DIALOG, IDH = IDR_HTML_MK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CmkDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
//	afx_msg void OnEnChangeEdit3();
};
