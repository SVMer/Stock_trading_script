#pragma once


struct data{				
   double Opnprc;
   double Hiprc;
   double Loprc;
   double Clsprc;
   int Trdsta;
};        // ͷ�ļ�����ñ�����ȫ�ֱ���,��.h�ļ���������һ��ȫ�ֳ������ڱ���ʱ.cpp�ļ�������һ������include .h����һcpp����������һ����ɴ��󡣸��Ǹ�ȫ�ֱ�������static����const���ֱ���

struct hold_data{
   char code[6];
   unsigned long long quantity;     //��Ʊ����,���Գ��Լ۸�ó���Ʊ����ֵ 
   double N; 
   double Nnum;
   double price;  //���й�Ʊ�ĳɽ��ۣ����룩 
   double Hiprc;  //�����뿪ʼ�����߼ۣ����붯ֹ̬ӯ

}; 


class account        
{
public: //����ģ��ѵ�����Ĭ����private��
	/*�ʲ�*/
	hold_data stock;                       //���еĹ�Ʊ�����ݣ�����ֻ��ע�۸�
	unsigned long long cash;   //������μ��㣬���cash��total_assets��Щ��ƫ���������ģ����Բ��û���
    unsigned long long total_assets;          //���ʲ�
    unsigned long long initial_assets;  //��ʼ�ʲ�
	/*ҵ��*/
	int profit_times;
	int loss_times;
	int no_loss_win_times;					 //��Ȼ�����Ժ��٣������ǽ��˿��ǽ�ȥ

	int continuous_profit;			 //����ӯ������������
	int continuous_loss;  
	int continuous_profit_temp;      //�м���������ڱȽ�
	int continuous_loss_temp;     

	unsigned long long profit;				 //��ӯ���ľ��Զ
	unsigned long long loss;
	unsigned long long max_profit;			 //���ӯ����
	unsigned long long max_loss;

	double fee_rat;    //�����м���ü������ı���(�޼۽��ף�
	                    //�� 1�룭3�루���Ӷ�𣩣�1�룭3�루����Ӷ�𣩣�1�루����ӡ��˰��1�루�Ϻ���Ʊ�����ѣ�

    double sign_buyprice;   //���������ź�ʱ�ļ۸� �������ڳɽ��ۣ�Ҫ���Ƿ��ã��Ͳ��ܼ�ʱ����
    double sign_sellprice;   //���������ź�ʱ�ļ۸� �������ڳɽ���


	account::account();


};   //��Ҫ���˼ӷֺ�


