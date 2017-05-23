
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mk.h"
#include "DlgProxy.h"
#include "mkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmkDlgAutoProxy

IMPLEMENT_DYNCREATE(CmkDlgAutoProxy, CCmdTarget)

CmkDlgAutoProxy::CmkDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CmkDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CmkDlg)))
		{
			m_pDialog = reinterpret_cast<CmkDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CmkDlgAutoProxy::~CmkDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CmkDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CmkDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CmkDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_Imk ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {71A97981-2CD6-4F8D-BEE2-8599A58725DA}
static const IID IID_Imk =
{ 0x71A97981, 0x2CD6, 0x4F8D, { 0xBE, 0xE2, 0x85, 0x99, 0xA5, 0x87, 0x25, 0xDA } };

BEGIN_INTERFACE_MAP(CmkDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CmkDlgAutoProxy, IID_Imk, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {52E15AFB-9124-4592-8253-BB7D67DB6CC6}
IMPLEMENT_OLECREATE2(CmkDlgAutoProxy, "mk.Application", 0x52e15afb, 0x9124, 0x4592, 0x82, 0x53, 0xbb, 0x7d, 0x67, 0xdb, 0x6c, 0xc6)


// CmkDlgAutoProxy ��Ϣ�������
