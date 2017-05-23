#include "StdAfx.h"
#include "Moving_Average.h"
#include "workthread.h"
#include "math.h"


bool days20=false,days55=false;   //����Ƿ�ﵽָ��ʱ��



Moving_Average::Moving_Average(void)
{
}


Moving_Average::~Moving_Average(void)
{
}


/*���ٶ�Ҫ�󲻸ߣ����ڴ�Ҫ����*/
void Moving_Average::run_market(int num,char *code_str)
{
	if(pmydata==NULL)
		return;
	//��һ�쵥����
	//N *n1=new N;         //�ֱ��Ӧ20�죬55��
	//N *n2=new N;
	//n1->front=n1->next=n2->front=n2->next=NULL;
	//n1->value=n2->value=fabs(pmydata->Loprc - pmydata->Hiprc);  //��һ���N�õ�ǰ�����յ���߼�����ͼۼ�Ĳ���
	pmydata++;
	//�ӵڶ��쿪ʼ
	for(int t=2;t<=num;t++)
	{
		//double dn=calculate_N(pmydata);
		//set_N_full(n1,dn);
		//set_N_full(n2,dn);
		if(can_buy())            //û�г��й�Ʊ
		{
					if(is_goldcross(t,5,20))
					{

			 			buy(pmydata);

					}
		}
		else
		{
					if(is_deathcross(t,5,20))
					{
						sell(pmydata);

					}
			}

		pmydata++;
	 }
	 //report(code_str);

}



bool Moving_Average::is_goldcross(int n,int small_period,int big_period)
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


bool Moving_Average::is_deathcross(int n,int small_period,int big_period)
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