#include "StdAfx.h"
#include "AbstractTrade.h"
#include "resource.h"   //Ϊ��ʹ�ÿؼ�id
#include "workthread.h"

data *pmydata_old=NULL,*pmydata=NULL;//����ȫ�ֱ�����������ֵ��


AbstractTrade::AbstractTrade(void)
{


}


AbstractTrade::~AbstractTrade(void)
{
}



bool AbstractTrade::can_buy()
{
	if(ac.stock.quantity==0)   //��Ϊֻ����ȫ�ֽ���
		return true;
	else
	   return false;
 
}

bool AbstractTrade::can_sell()
{
	if(ac.stock.quantity!=0)
		return true;
	else
	   return false;
 
}

void AbstractTrade::buy(data* ppdata)
{
	ac.stock.price=ac.sign_buyprice*ac.fee_rat;
    ac.stock.quantity=ac.cash/ac.stock.price;      //unsigned long long����double,�ȵó��������С��)����ת��Ϊunsigned long long
	ac.stock.quantity/=100;   //�������100��
	ac.stock.quantity*=100; 
       

	#ifdef _DEBUG
	if(ac.cash<(ac.stock.price*ac.stock.quantity))
	{
		AfxMessageBox("����Ǯ��"); //�������Ӧ�ò��ᷢ����һ������������
	}
	#endif

	ac.cash-=(ac.stock.price*ac.stock.quantity);  //����һ��С��λ����ȥ����������cash��ô���������Ժ���

	strtemp.Format("��%lf��λ����%I64u��,�ɽ���%lf\n",ac.stock.price,ac.stock.quantity,ac.stock.price);
	append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);



}

void AbstractTrade::sell(data* ppdata)   //�������źŵļ۸����ɽ��ۣ��ڼ��������м����������
{

	/*����ʱ�������ܽύ�׵�ʧ��*/

	strtemp.Format("��%lf��λ����%I64u��\n\n\n",ac.sign_sellprice,ac.stock.quantity);
	append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);

	if (ac.sign_sellprice>ac.stock.price)
	{ 
        unsigned long long d;
		d=(ac.sign_sellprice-ac.stock.price)*ac.stock.quantity;
		ac.profit+=d;
		ac.total_assets+=d;
        ac.profit_times++;

		/*����ӯ����������*/
		ac.continuous_profit_temp++;
		ac.continuous_loss_temp=0;
		if(ac.continuous_profit<ac.continuous_profit_temp)
		  ac.continuous_profit=ac.continuous_profit_temp;

	    /*��¼���ӯ��*/
		if(ac.max_profit<d)
		  ac.max_profit=d;

		strtemp.Format("����ӯ��%I64u\t�ۼ�ӯ������%d\t�ۼ�ӯ��%I64u\t���ʲ�%I64u\n\n\n",d,ac.profit_times,ac.profit,ac.total_assets);
	    append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);

	}

	/*����*/
	if (ac.sign_sellprice<ac.stock.price)
	{ 
		unsigned long long d;
		d=(ac.stock.price-ac.sign_sellprice)*ac.stock.quantity;
		ac.loss+=d;
		ac.total_assets-=d;
		ac.loss_times++;

		/*���������������*/
		ac.continuous_loss_temp++;
		ac.continuous_profit_temp=0;
		if(ac.continuous_loss<ac.continuous_loss_temp)
		  ac.continuous_loss=ac.continuous_loss_temp;

	    /*��¼������*/
		if(ac.max_loss<d)
		 ac.max_loss=d;

		strtemp.Format("���ο���%I64u\t�ۼƿ������%d\t�ۼƿ���%I64u\t���ʲ�%I64u\n\n\n",d,ac.loss_times,ac.loss,ac.total_assets);
	    append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);


	}
	if(ac.sign_sellprice==ac.stock.price)  /*�޿��������������״̬*/
	{
		ac.no_loss_win_times+=1;

		strtemp.Format("\n\n*********���ν�����ӯ��**********\t���ʲ�%I64u",ac.total_assets);
	    append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);
	}

	append_text(hedit2,"\n\n");

	ac.cash+=ac.sign_sellprice*ac.stock.quantity;   //�����ֽ�

	clear_holdingstock();

}


/*
void AbstractTrade::append_text(HWND h,char *pStr)
{
	int nLength =SendMessage(h, WM_GETTEXTLENGTH,0,0); 
	SendMessage(h, EM_SETSEL, nLength, nLength);    //��Ȼpostmessage���죬��postmessage���첽��Ҫ��֤����ֵ�Ĳ��䡣
    //SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
    SendMessage(h, EM_REPLACESEL, TRUE, (LPARAM)pStr);
}

*/
/*
void AbstractTrade::report(char *code_str)
{         //��������
	static int icount=0;

	if(can_sell())
	{   
		ac.sign_sellprice=(pmydata-1)->Clsprc;
		sell((pmydata-1)); 
	}         //С��pmydataԽ��,������������pmydata--,Ϊʲô����


	if(ac.profit_times+ac.loss_times+ac.no_loss_win_times==0)
		       return;                     //û�н��׾Ͳ��û��ܣ������preport_var�ڴ�������ģ���ʱ����
		

	icount++;



	preport_var->total_assets=ac.total_assets;      
	preport_var->profit_times=ac.profit_times;
	preport_var->loss_times=ac.loss_times;
	preport_var->profit=ac.profit;
	preport_var->loss=ac.loss;
	int aver_profit_times=0,aver_loss_times=0;
	unsigned long long aver_total_assets=0,aver_profit=0,aver_loss=0;

	for(int i=0;i<icount;i++)           //С��Խ��
	{
		aver_loss_times+=(preport_var-i)->loss_times;      //��������ȼ���aver_loss_times=aver_loss_times+(preport_var-i)->loss_times;���Ա����ȸ���ֵ
		aver_profit_times+=(preport_var-i)->profit_times;            
		aver_total_assets+=(preport_var-i)->total_assets; 
		aver_profit+=(preport_var-i)->profit; 
		aver_loss+=(preport_var-i)->loss; 
	}

	aver_loss_times/=icount;
	aver_profit_times/=icount;
	aver_total_assets/=icount;
	aver_profit/=icount;
	aver_loss/=icount;


	strtemp.Format("����%s\t�ʲ����%I64u\nӯ������%d\t�������%d\nӯ���ܶ�%I64u\t�����ܶ�%I64u\n���ӯ��%I64u\t������%I64u\n����ӯ����������%d\t���������������%d\n",code_str,ac.total_assets,ac.profit_times,ac.loss_times,ac.profit,ac.loss,ac.max_profit,ac.max_loss,ac.continuous_profit,ac.continuous_loss);      //�������ݣ���̫��
	append_text(hedit1,(LPTSTR)(LPCTSTR)strtemp);


	strtemp.Format("����%dֻ��Ʊ\n\nƽ�����ʲ����%I64u\n\nƽ��ӯ������%d\n\nƽ���������%d\n\nƽ��ӯ���ܶ�%I64u\n\nƽ�������ܶ�%I64u",icount,aver_total_assets,aver_profit_times,aver_loss_times,aver_profit,aver_loss);
	SetWindowText(hedit3,strtemp);

	//SetWindowText(hedit2," ");

	preport_var++;

}
*/


void AbstractTrade::clear_holdingstock()
{
	ac.sign_buyprice=0;
	ac.sign_sellprice=0;
	ac.stock.Hiprc=0;
	ac.stock.price=0;
	ac.stock.quantity=0;
	ac.stock.N=0;
	ac.stock.Nnum=0;
}


bool AbstractTrade::not_SST(data* ppdata)
{
	if(ppdata->Trdsta==3 || ppdata->Trdsta==6)  //sst��Ʊ����
		return false;
	return true;
}



void AbstractTrade::report(char *pcode,int period,report_var *preport_var)
{         //��������

	if(can_sell())
	{   
		ac.sign_sellprice=(pmydata-1)->Clsprc;
		sell((pmydata-1)); 
	}         //С��pmydataԽ��,������������pmydata--,Ϊʲô����


	if(ac.profit_times+ac.loss_times+ac.no_loss_win_times!=0)     //����д����ûgoto�ÿ�
	{       
			preport_var->icount++;
			preport_var->total_assets+=ac.total_assets;      
			preport_var->profit_times+=ac.profit_times;
			preport_var->loss_times+=ac.loss_times;
			preport_var->profit+=ac.profit;
			preport_var->loss+=ac.loss;
	}
	else if(preport_var->icount==0)
	{   
		strtemp.Format("����%s\n\n����%d��\n\n���ʲ����%I64u\n\nӯ������%d\n\n�������ӯ������%d\n\n�������%d\n\n��������������%d\n\nӯ���ܶ�%I64u\n\n���ӯ����%I64u\n\n�����ܶ�%I64u\n\n�������%I64u\n\n",pcode,period,ac.total_assets,ac.profit_times,ac.continuous_profit,ac.loss_times,ac.continuous_loss,ac.profit,ac.max_profit,ac.loss,ac.max_loss);
		append_text(hedit1,(LPTSTR)(LPCTSTR)strtemp);
	    strtemp.Format("����0ֻ��Ʊ\n\n����%d��\n\n",period);
	    append_text(hedit3,(LPTSTR)(LPCTSTR)strtemp);   
		return;
	}

	int aver_profit_times=0,aver_loss_times=0;
	unsigned long long aver_total_assets=0,aver_profit=0,aver_loss=0;

	aver_loss_times=preport_var->loss_times/preport_var->icount;      //��������ȼ���aver_loss_times=aver_loss_times+(preport_var-i)->loss_times;���Ա����ȸ���ֵ
	aver_profit_times=preport_var->profit_times/preport_var->icount;            
	aver_total_assets=preport_var->total_assets/preport_var->icount; 
	aver_profit=preport_var->profit/preport_var->icount; 
	aver_loss=preport_var->loss/preport_var->icount; 

	strtemp.Format("����%s\n\n����%d��\n\n���ʲ����%I64u\n\nӯ������%d\n\n�������ӯ������%d\n\n�������%d\n\n��������������%d\n\nӯ���ܶ�%I64u\n\n���ӯ����%I64u\n\n�����ܶ�%I64u\n\n�������%I64u\n\n",pcode,period,ac.total_assets,ac.profit_times,ac.continuous_profit,ac.loss_times,ac.continuous_loss,ac.profit,ac.max_profit,ac.loss,ac.max_loss);
	append_text(hedit1,(LPTSTR)(LPCTSTR)strtemp);

	strtemp.Format("����%dֻ��Ʊ\n\n����%d��\n\nƽ�����ʲ����%I64u\n\nƽ��ӯ������%d\n\nƽ���������%d\n\nƽ��ӯ���ܶ�%I64u\n\nƽ�������ܶ�%I64u",preport_var->icount,period,aver_total_assets,aver_profit_times,aver_loss_times,aver_profit,aver_loss);
	append_text(hedit3,(LPTSTR)(LPCTSTR)strtemp);

	//strtemp.Format("����%dֻ��Ʊ\n\n����%d��\n\nƽ�����ʲ����%I64u\n\nƽ��ӯ������%d\n\nƽ���������%d\n\nƽ��ӯ���ܶ�%I64u\n\nƽ�������ܶ�%I64u",preport_var->icount,period,aver_total_assets,aver_profit_times,aver_loss_times,aver_profit,aver_loss);
	//append_text(hedit3,(LPTSTR)(LPCTSTR)strtemp);
	//SetWindowText(hedit3,strtemp);

	//SetWindowText(hedit2," ");

}

