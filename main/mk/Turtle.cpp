#include "StdAfx.h"
#include "Turtle.h"
#include "math.h"




Turtle::Turtle(void)
{
}


Turtle::~Turtle(void)
{
}


void Turtle::drop_firstTR(TR *t)
{
	while(t->front!=NULL)
		t=t->front;
	t->next->front=NULL;  //����һλ��Ϊ��ͷ
	delete t;
}
void Turtle::drop_allTR(TR *t)
{
	TR *tn;                //tnΪ��ʱ����
	while(t->front!=NULL)
	{
		tn=t;
		t=t->front;
		delete tn;
	}
		delete t; //��ͷ������
}

/*
TR* Turtle::find_lastTR(TR *n)
{
	while(n->next!=NULL)
		n=n->next;
	return n;
}
*/

/*
double Turtle::calculate_TR(data *ppmydata)
{
	double d1=fabs(ppmydata->Loprc - pmydata->Hiprc);   //1.��ǰ�����յ���߼�����ͼۼ�Ĳ���
	double d2=fabs((ppmydata-1)->Clsprc - pmydata->Hiprc);   //2.�������߼ۺ���������̼�֮��ľ���
	double d3=fabs((ppmydata-1)->Clsprc - pmydata->Loprc);   //3.�������ͼۺ���������̼�֮��ľ���
	if(d2<d3)
		d2=d3;
	if(d1<d2)
		d1=d2;
	return d1;
}


void Turtle::set_TR_unfull(TR *n,double dn)
{
		TR *tn=new TR;   //tn����ʱ����
		tn->front=n;
		n=tn;
		n->value=dn;
}
*/

TR *Turtle::calculate_TR(int num,TR *t) //��ַ����ָ�룬ָ���ָ��ᷢ���ı䣬�ܻ�ָ����β
{

	 double d1=fabs((pmydata-1)->Loprc - (pmydata-1)->Hiprc);   //1.��ǰ�����յ���߼�����ͼۼ�Ĳ���
	 double d2=fabs((pmydata-2)->Clsprc - (pmydata-1)->Hiprc);   //2.�������߼ۺ���������̼�֮��ľ���
	 double d3=fabs((pmydata-2)->Clsprc - (pmydata-1)->Loprc);   //3.�������ͼۺ���������̼�֮��ľ���
	 if(d2<d3)
		 d2=d3;
	 if(d1<d2)
		 d1=d2;
	
	TR *tn=new TR;   //tn����ʱ����
	tn->value=d1;
	tn->front=t;
	t->next=tn;

	return tn;

}

double Turtle::get_N(TR *t)
{
    double aver=0;
	do
	{
		aver+=t->value;
	}while((t=t->front)!=NULL);
	aver/=15;
	return aver;

}

/*���ٶ�Ҫ�󲻸ߣ����ڴ�Ҫ����*/
void Turtle::run_market(char *pcode,int num/*����*/,int period/*����*/,report_var *preport_var)
{
	if(pmydata==NULL)
		return;
	//��һ�쵥����N���ڶ��첻��N����������������
	TR *tr=new TR;
	tr->front=NULL;
	tr->value=fabs(pmydata->Loprc - pmydata->Hiprc);  //��һ���N�õ�ǰ�����յ���߼�����ͼۼ�Ĳ���
	pmydata+=2;

	//�ӵ����쿪ʼ
	double N;
	for(int t=3;t<=num;t++)
	{
		tr=calculate_TR(t, tr);
		if(t>15)      //��16��ſ�ʼ���ף���Ϊ��ʱ�ż���15��tr����N
		{

			N=get_N(tr);

			refresh_holding_data();//ˢ�³��й�Ʊ�����ݣ���Ҫ����û�д���ֹ��/ӯ

			if(can_buy())     //û�г��й�Ʊ
			{
						if(is_highest(t,period,pmydata)/* && not_SST(pmydata)*/)
						{
							/*
							ac.stock.N=N;
							int n=(ac.cash*0.05)/N;   //���ڴ˴���ȫ�ֲ�������������д������ʵӦ���������������NΪ��λ
							ac.stock.Nnum=n;
							*/
			               
			 				buy(pmydata);

						}
			}
			else
			{
						if(is_lowest(t,period,pmydata) /*|| stop_lossing()|| stop_winning()*/) //�����ź������еģ����ͷ���
						{
							sell(pmydata);   //���������������ź�ac.sign_sellprice
						}
			}

		    drop_firstTR(tr);   //һ������ӵ���һ��N

		}
		pmydata++;   //����λ�ñ��ƶ�ָ�룬ֻ�������ƶ�
	 }
	 drop_allTR(tr);
	 report(pcode,period,preport_var);

	 pmydata=pmydata_old;
}




bool Turtle::is_highest(int n/*�ڼ���*/,int period/*����*/,data *ppmydata)
{

	if(n>=period)
	{
		    int i=1;
			double tHiprcp=pmydata->Hiprc/1.02;   //��֤�������߼۱�ǰn-1�����߼۸�2%(��Ҳ���ǹ�����һ���֣�
			while(i<period && tHiprcp > (ppmydata-i)->Hiprc  ) 
				i++;

			if(i==period-1)       
			{
				i=1;               //���۸񳬹�ǰn-1�����߼۵�1%ʱ�����������ź�
				while(i<period)
				{
					if(ac.sign_buyprice<(ppmydata-i)->Hiprc)   
					   ac.sign_buyprice=(ppmydata-i)->Hiprc;
					i++;
				}
				ac.sign_buyprice*=1.02;
			    return true;
			}
	}
		return false;

}


bool Turtle::is_lowest(int n,int period,data *ppmydata)    //periodΪ����
{
	if(n>=period)
	{
		    int i=1;
			while(i<period && ppmydata->Clsprc < (ppmydata-i)->Clsprc)   //�����벻ͬ��һ����ǰn-1����ͼ۷����ź�
               i++;

			if(i==period-1)       
			{
				i=1;  
				ac.sign_sellprice=999999999; //��ʵ�����壬���ɣ����ڱȽ�
				while(i<period)
				{
					if(ac.sign_sellprice>(ppmydata-i)->Hiprc)   
					   ac.sign_sellprice=(ppmydata-i)->Hiprc;
					i++;
				}
			    return true;
			}
	 }
     		return false;
}

bool Turtle::stop_lossing()  //ֹ�𣬻�û�г����źţ��������ѳ����ɳ��������ա�����ʧ�������ʲ���5%����NΪ��λ(�Դ����趨������)
{
	if((ac.stock.price-pmydata->Loprc)>(4*ac.stock.N))   //�̶�ֹ���
	{
		ac.sign_sellprice=ac.stock.price-(4*ac.stock.N);
		return true;
	}
		/*
	if((ac.stock.price-pmydata->Loprc)*ac.stock.quantity > (ac.stock.quantity*ac.stock.price)*0.10)
	{

		ac.sign_sellprice = ac.stock.price*0.9;  //�ݶ�,��Ϊ��ȫ�֣��������ʲ���5%��ʧ��Լ���ڹɼ۵�5%�µ�
		return true;

	}
			*/
	return false;

}

bool Turtle::stop_winning()
{
	if(pmydata->Loprc < ac.stock.Hiprc*0.80 )
	{   
		ac.sign_sellprice = ac.stock.Hiprc*0.80 ; //�ݶ�
		return true;           
	}
		return false;
}



void Turtle::refresh_holding_data()  
{
	if(ac.stock.quantity!=0) 
	{
		if(pmydata->Hiprc > ac.stock.Hiprc)
		 ac.stock.Hiprc=pmydata->Hiprc;

	}
}


bool Turtle::is_goldcross(int n,int small_period,int big_period)
{
	if(n>=big_period)
	{
		    float samll_average=0,big_average=0;
		    
			for(int i=0;i<small_period;i++)             //С��n��ƽ���۸�
			{
				samll_average+=(pmydata-i)->Clsprc;         //�������̼ۺ���̫׼ȷ�����첻Ӧ�������̼ۣ���������߼ۣ���ΪҪ���Ǳ��ն�����
			}
            samll_average/=small_period;

			
			for(int i=0;i<big_period;i++)               //���n��ƽ���۸�
			{
				big_average+=(pmydata-i)->Clsprc;
			}
            big_average/=big_period;


			if(samll_average>big_average)
			{
				strtemp.Format("������\n");
			   //strtemp.Format("\t%d��%d���ƽ���ƶ��߽���(���)��%f��λ����\n",small_period,big_period,pmydata->Clsprc);
	           append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);
			   return true;
			}
	}
		return false;

}


bool Turtle::is_deathcross(int n,int small_period,int big_period)
{
	if(n>=big_period)
	{
		    float samll_average=0,big_average=0;
		    
			for(int i=0;i<small_period;i++)             //С��n��ƽ���۸�
			{
				samll_average+=(pmydata-i)->Clsprc;
			}
            samll_average/=small_period;

			
			for(int i=0;i<big_period;i++)               //���n��ƽ���۸�
			{
				big_average+=(pmydata-i)->Clsprc;
			}
            big_average/=big_period;


			if(samll_average<big_average)
			{
				strtemp.Format("�������\n");
			//strtemp.Format("\t%d��%d���ƽ���ƶ��߽���(����)��%f��λ����\n",small_period,big_period,pmydata->Clsprc);
	        append_text(hedit2,(LPTSTR)(LPCTSTR)strtemp);
			   return true;
			}
	}
		return false;

}