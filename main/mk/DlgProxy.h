
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CmkDlg;


// CmkDlgAutoProxy ����Ŀ��

class CmkDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CmkDlgAutoProxy)

	CmkDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CmkDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CmkDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CmkDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

