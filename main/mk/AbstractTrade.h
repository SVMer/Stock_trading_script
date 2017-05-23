#pragma once
#include "account.h"
#include "workthread.h"

class AbstractTrade     //����
{
public:
	account ac;
	AbstractTrade(void);
	~AbstractTrade(void);
	 
	bool can_buy();      // ����Ĳ���ʵ���Ƿ������
	bool can_sell();     // ����Ĳ���ʵ���Ƿ������
	void buy(data* ppdata);
	void sell(data* ppdata);

	

    /*
	void GetMaxAmount();  // �õ���������������
	void GetBuyPrice();   // �õ�����ļ۸�
	void GetSellPrice();  // �õ������ļ۸�
	void GetAvailableAmount();  // �õ���ǰ���������ĵĹ�Ʊ��
	void GetAmount();    // �õ��ܵ�����
	void IsHaveStockToSell();   // �Ƿ��й�Ʊ������
	void IsHaveTheStockAlready();  // �Ƿ��Ѿ��������Ʊ�� (����������)
	*/

	CString strtemp;

	void report(char *pcode,int period,report_var *preport_var);   //������

	void report_new(char *code_str);

	void clear_holdingstock();   //����˻�����
	bool not_SST(data* ppdata);   //�����Ƿ�st��Ʊ
}; 


extern  data *pmydata_old;   //����ֱ��������������̬��������Ȼ�������ļ�Ҳ�����ɾ�̬�����������ж����
extern  data *pmydata;       //��һ��Դ�����ɶ��Դ�ļ����ʱ���Ǿ�̬��ȫ�ֱ����ڸ���Դ�ļ��ж�����Ч�ġ� ����̬ȫ�ֱ������������������� ��ֻ�ڶ���ñ�����Դ�ļ�����Ч

