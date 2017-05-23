#include "StdAfx.h"    //����
#include "ADOConn.h"
#include <string>
#include <fstream>
#include "workthread.h"
#include "Turtle.h"

using namespace std;

#define filepath "" 

/*ȫ�ֱ����������ã��Ͼ�����ά������ռ�ڴ�*/
HWND hedit1=NULL,hedit2=NULL,hedit3=NULL;         //��Ϊ�ⲿ��������������������ɼ�

char **pstr_code=NULL;
int pstr_code_size=0;    //Ϊ�˷���ɾ����̬����,���벻��������ȡ��̬��ά�����С
char pstr_start_time[11]={' '};  //��ֵΪһ���ո��ַ������ǿ��ַ���
char pstr_end_time[11]={' '};

report_var *preport_var=NULL,*preport_var_old=NULL;          


void write_in_db(ADOConn *pa);
void calculate(ADOConn *pa);


unsigned int __stdcall WorkThrd(void * pParam)  //�����ǶԻ��򴰿���
{


	ADOConn a;
	a.OnInitADOConn();

	//write_in_db(&a);
	calculate(&a);
	

	AfxMessageBox("�������");
    return 0;
}

/*
void write_in_db(ADOConn *pa)
{
	char tstr[18][17]={'0'};                 //����ν�ٶȡ��ٶ�������һ���Զ�ȡ���ݣ�Ȼ��д�롣
	string s;   //string�����ء�+��,���Ӷ���ַ���ʱ����
	_bstr_t bstrSQL;

	int icount=0;



	FILE* pfile;
	pfile=fopen(filepath,"r");
    //��֪Ϊʲô���ܻ���һ�У����Լ�ȥ1
    while(fscanf(pfile,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n",&tstr[1],&tstr[2],&tstr[3],&tstr[4],&tstr[5],&tstr[6],&tstr[7],&tstr[8],&tstr[9],&tstr[10],&tstr[11],&tstr[12],&tstr[13],&tstr[14],&tstr[15],&tstr[16],&tstr[17])==17)     //����ֵΪ�ɹ����ݵĲ�������      %ld���У�Ҫ%lld����
	{

	//s=s+tstr[1]+"'"+tstr[1]+"','"+tstr[2]+"','"+tstr[3]+"','"+tstr[4]+"','"+tstr[5]+"','"+tstr[6]+"','"+tstr[7]+"','"+tstr[8]+"','"+tstr[9]+"','"+tstr[10]+"','"+tstr[11]+"','"+tstr[12]+"','"+tstr[13]+"','"+tstr[14]+"','"+tstr[15]+"','"+tstr[16]+"','"+tstr[17]+"')";
	//AfxMessageBox(s.c_str());


	//�µ�֤ȯ���룬�������±�,������Ѿ����ڣ���Ȼ�ܹ�������ȥ��
	if(strcmp(tstr[0],tstr[1])!=0)   //�ַ�����Ĳ���Ҫ�ú�������st1=st2��������0��st1<st2���-1��st1>st2���1
	{
	bstrSQL="CREATE TABLE [";         //�Դ��������������Ӹ������žͺ��ˣ���֪Ϊʲô
	bstrSQL+=tstr[1];
	bstrSQL+="](Stkcd varchar(7),Trddt date,Opnprc decimal(7,3),Hiprc decimal(7,3),Loprc decimal(7,3),Clsprc decimal(7,3),Dnshrtrd numeric(12, 0),Dnvaltrd money,Dsmvosd money,Dsmvtll money,Dretwd varchar(12),Dretnd varchar(12),Adjprcwd decimal(10,3),Adjprcnd decimal(10,3),Markettype tinyint,Capchgdt date,Trdsta tinyint)";
	//AfxMessageBox(bstrSQL);
	pa->ExecuteSQL(bstrSQL);
	memcpy(tstr[0],tstr[1],6);   //copyǰ6���ַ�
	}

	
	s="INSERT INTO [";
	s=s+tstr[1]+"] VALUES ('"+tstr[1]+"','"+tstr[2]+"','"+tstr[3]+"','"+tstr[4]+"','"+tstr[5]+"','"+tstr[6]+"','"+tstr[7]+"','"+tstr[8]+"','"+tstr[9]+"','"+tstr[10]+"','"+tstr[11]+"','"+tstr[12]+"','"+tstr[13]+"','"+tstr[14]+"','"+tstr[15]+"','"+tstr[16]+"','"+tstr[17]+"')";
	//AfxMessageBox(s.c_str());
	bstrSQL=s.c_str();
	pa->ExecuteSQL(bstrSQL);

	}

	icount++;
}

*/

void calculate(ADOConn *pa)
{
	_RecordsetPtr m_pRecordset;  //֤ȯ����
	_RecordsetPtr m_pRecordset2;   //�ս�������
	_bstr_t bstrSQL;

	if(pstr_code==NULL) //û������Ʒ�ַ�Χ,��Ĭ������Ϊ����Ʒ��
	{
		bstrSQL="select code from code";
		m_pRecordset=pa->GetRecordSet(bstrSQL);

		pstr_code=new char*[m_pRecordset->RecordCount];        //�����ά�����Ŵ���
		pstr_code_size=m_pRecordset->RecordCount;              //ͬʱ��ס��ά�����С

		int i=0;
		for(m_pRecordset->MoveFirst();!m_pRecordset->adoEOF;m_pRecordset->MoveNext(),i++)  //�������е�֤ȯ����
		{
				pstr_code[i]=new char[6]; 
				strcpy(pstr_code[i],(_bstr_t)m_pRecordset->GetCollect("code"));
				//AfxMessageBox(pstr_code[i]);
		}
		m_pRecordset->Close();
		m_pRecordset=NULL;
	}


	preport_var=preport_var_old=new report_var[10]; //������������report���
	initial_report_var();

	for(int i=0;i<pstr_code_size;i++)    //����ÿһֻ��Ʊ
	{
		bstrSQL="select [Opnprc],[Hiprc],[Loprc],[Clsprc],[Adjprcnd],[Trdsta] from [";         //����ѡ��Ҫ�õ����ֶΡ� ������ֻ��ע�۸�
		bstrSQL+=pstr_code[i];
		bstrSQL+="]";      //������������

		if(pstr_start_time[0]!=' ' || pstr_end_time[0]!=' ')   //û������ʱ�䷶Χ��������0��ո��ansi���벻ͬ����
		{
			bstrSQL+=" WHERE ";
			if(pstr_start_time[0]!=' ' && pstr_end_time[0]!=' ')
			{
				bstrSQL+="Trddt>='";
				bstrSQL+=pstr_start_time;
				bstrSQL+="' AND Trddt<='";
				bstrSQL+=pstr_end_time;
				bstrSQL+="'";
				goto s; //��������
			}

			if(pstr_start_time[0]!=' ')
			{
				bstrSQL+="Trddt>='";
				bstrSQL+=pstr_start_time;
				bstrSQL+="'";
			}

			if(pstr_end_time[0]!=' ')
			{
				bstrSQL+="Trddt<='";
				bstrSQL+=pstr_end_time;
				bstrSQL+="'";
			}

		}

		s:
		//AfxMessageBox(bstrSQL); 
		m_pRecordset2=pa->GetRecordSet(bstrSQL);  
		
		long num=m_pRecordset2->RecordCount;

		if(num!=0)  //û��ѡ���Ʊ�������ƨ�ڴ氡��
		{
				pmydata_old=new data[num];    //���RecordCountΪ-1�Ͳ���; pmydata_oldһֱָ���ڴ��ַ����
				pmydata=pmydata_old;
						//recordset���ʺϷ������ݣ���ת���ڴ���Ȼ����Ƿ�����
				double Clsprc,percent;
				for(m_pRecordset2->MoveFirst();!m_pRecordset2->adoEOF;m_pRecordset2->MoveNext(),pmydata++)
				{
					pmydata->Clsprc =atof((_bstr_t)m_pRecordset2->GetCollect("Adjprcnd")); 	
					/*�۸����*/
					Clsprc=atof((_bstr_t)m_pRecordset2->GetCollect("Clsprc"));
					percent=pmydata->Clsprc/Clsprc;

					pmydata->Opnprc=atof((_bstr_t)m_pRecordset2->GetCollect("Opnprc"))*percent;
					pmydata->Hiprc=atof((_bstr_t)m_pRecordset2->GetCollect("Opnprc"))*percent;
					pmydata->Loprc=atof((_bstr_t)m_pRecordset2->GetCollect("Loprc"))*percent;
					pmydata->Trdsta=atoi((_bstr_t)m_pRecordset2->GetCollect("Trdsta"));
				}

		}

		m_pRecordset2->Close();   //�������ݼ�����������
		m_pRecordset2=NULL;

		pmydata=pmydata_old;

		SetWindowText(hedit3," ");
		/*����׼�����ģ���г�����,�����������*/
		for(int l=0;l<10;l++)
		{
			  Turtle *tt=new Turtle;
		      tt->run_market(pstr_code[i],num,(l+1)*5,(preport_var+l));
		      delete tt;
		}

		if(pmydata_old!=NULL)     //�ȼ����ͷš�
		delete [] pmydata_old;    //�ǵ��������Ȼ���ڴ�й¶
		pmydata=pmydata_old=NULL;
	}

	report();  //report in edit3


	delete [] preport_var_old;        //����preport_var�Ѿ�ָ������Ǹ�Ԫ�أ����Բ���ֱ��delete [] preport_var;
	preport_var=preport_var_old=NULL;
	pa->ExitConnect();       //�����ݿ����ӶϿ�

	//pstr_code���ڴ�ռ䲻���ͷţ������´���
}



		/*
		_bstr_t bstrSQL="select code from code";
		m_pRecordset=pa->GetRecordSet(bstrSQL);
		preport_var=new report_var[m_pRecordset->RecordCount];
		for(m_pRecordset->MoveFirst();!m_pRecordset->adoEOF;m_pRecordset->MoveNext())  //�������е�֤ȯ����
		{

		bstrSQL="select [Adjprcnd] from [";         //����ѡ��Ҫ�õ����ֶΡ� ������ֻ��һ�����������ֽ���������̼۵Ŀɱȼ۸�
		bstrSQL+=(_bstr_t)m_pRecordset->GetCollect("code");
		bstrSQL+="]";      //������������
		//AfxMessageBox(bstrSQL);
		m_pRecordset2=pa->GetRecordSet(bstrSQL);   



		long num=m_pRecordset2->RecordCount;
		pmydata_old=new data[num];    //���RecordCountΪ-1�Ͳ���
		pmydata=pmydata_old;

						//recordset���ʺϷ������ݣ���ת���ڴ���Ȼ����Ƿ�����
		for(m_pRecordset2->MoveFirst();!m_pRecordset2->adoEOF;m_pRecordset2->MoveNext(),pmydata++)
		{
					bstrSQL=(_bstr_t)m_pRecordset2->GetCollect("Adjprcnd");
					pmydata->Clsprc = atof(bstrSQL); 

		}

		m_pRecordset2->Close();
		m_pRecordset2=NULL;

		pmydata=pmydata_old;

		Moving_Average ma;
		ma.run_market(num,(char *)(_bstr_t)m_pRecordset->GetCollect("code"));


		delete [] pmydata_old;    //�ǵ��������Ȼ���ڴ�й¶
		pmydata=pmydata_old=NULL;

		}
	
		delete [] preport_var;
		m_pRecordset->Close();
		m_pRecordset=NULL;
		pa->ExitConnect();
	}
	*/



void initial_report_var()
{
	for(int l=0;l<10;l++)
	{
		(preport_var+l)->icount=0; 
		(preport_var+l)->total_assets=0;      
		(preport_var+l)->profit_times=0;
		(preport_var+l)->loss_times=0;
		(preport_var+l)->profit=0;
		(preport_var+l)->loss=0;
	}
}

void report()
{
	CString strtemp;
	SetWindowText(hedit3," ");
		for(int l=0;l<10;l++)
	{
		if((preport_var+l)->icount==0)
		{  
			strtemp.Format("����0ֻ��Ʊ\n\n����%d��",(preport_var+l)->icount,(l+1)*5);
			append_text(hedit1,(LPTSTR)(LPCTSTR)strtemp);
			continue;
		}

		int aver_profit_times=0,aver_loss_times=0;
	    unsigned long long aver_total_assets=0,aver_profit=0,aver_loss=0;

		aver_loss_times=(preport_var+l)->loss_times/(preport_var+l)->icount;      //��������ȼ���aver_loss_times=aver_loss_times+(preport_var-i)->loss_times;���Ա����ȸ���ֵ
		aver_profit_times=(preport_var+l)->profit_times/(preport_var+l)->icount;            
		aver_total_assets=(preport_var+l)->total_assets/(preport_var+l)->icount; 
		aver_profit=(preport_var+l)->profit/(preport_var+l)->icount; 
		aver_loss=(preport_var+l)->loss/(preport_var+l)->icount; 


		strtemp.Format("����%dֻ��Ʊ\n\n����%d��\n\nƽ�����ʲ����%I64u\n\nƽ��ӯ������%d\n\nƽ���������%d\n\nƽ��ӯ���ܶ�%I64u\n\nƽ�������ܶ�%I64u",(preport_var+l)->icount,(l+1)*5,aver_total_assets,aver_profit_times,aver_loss_times,aver_profit,aver_loss);
	    append_text(hedit3,(LPTSTR)(LPCTSTR)strtemp);
	}

}



void append_text(HWND h,char *pStr)
{
	int nLength =SendMessage(h, WM_GETTEXTLENGTH,0,0); 
	SendMessage(h, EM_SETSEL, nLength, nLength);    //��Ȼpostmessage���죬��postmessage���첽��Ҫ��֤����ֵ�Ĳ��䡣
    //SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
    SendMessage(h, EM_REPLACESEL, TRUE, (LPARAM)pStr);
}