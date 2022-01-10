#include<bits/stdc++.h>
#include<time.h>
using namespace std;

float GenerateRandomProbability();
string GenerateRandomString(int n);
list<string> Generor(int a,list<string>codes,float prob);
void Display(list<string>codes);
list<string> ExtractData(list<string>codes);
int B2D(string s);
char invert(char a);
list<string> Hamming(list<string>codes);
list<string> Detectioncorrection(list<string>code);
bool Detection(list<string> code);
int B2D(string s);

int main()
{
	srand(time(0));
	list<string>TOKENS,dataword,noise,rdata,receivedwitherror;
	string S,tokn="",tmp="";
	int opt,len; float prob;
	cout<<"\n\tEnter the length of random string to be generated (>=16)  :     ";
	cin>>len;
	S=GenerateRandomString(len);

		if(len%4!=0)
	{	int n=(len/4);
		for(int i=0;i<(((n+1)*4)-len);i++)
		{tokn=tokn+"0";}
		S=tokn+S;
	}
	for(int j=0;j<S.size();j++)
	{ if((j+1)%4==0)
		{ 	tmp=tmp+S[j];
			TOKENS.push_back(tmp);
			tmp="";
		}
		else
			{
				tmp=tmp+S[j];
			}
	}
	int n;
	cout<<"\n\tGenerate 2 bit error or 1 bit error :  ( 1 / 2 )  ";
	cin>>n;
	cout<<"\n\n\tEnter the Crossover Probability    :     ";
	cin>>prob;
	dataword=Hamming(TOKENS);
	cout<<"\n\t Input Data was : ";
	Display(TOKENS);
	cout<<endl<<endl;
	cout<<"\n\t Hamming Code Generated : ";
	Display(dataword);
	cout<<endl<<endl;
	noise=Generor(n,dataword,prob);
	cout<<"\n\t error generated : ";
	Display(noise);
	cout<<endl<<endl;

	switch(n)
	{
		case 1:   	cout<<"\n\n\t Received Data is : (p: position of error   0: no error) \n\t";
						receivedwitherror=Detectioncorrection(noise);
						cout<<endl<<endl;
						cout<<"\n\tThe actual data is : ";
				      rdata=ExtractData(receivedwitherror);
						Display(rdata);
				      break;
		case 2:
					   if(!Detection(noise))
						cout<<"\n\t The received data has error in it..... location cannot be traced!!! \n\n";
					   else
						{
						 cout<<"The actual data is : ";
						 rdata=ExtractData(noise);
						 Display(rdata);
						}
				      break;
	  default: cout<<"Invalid number.......!!!";

	}
}


//-------------To generate random string of 0s and 1s----------------------

string GenerateRandomString(int n)
{  char zo[]={'0','1'};
   string Res="";
   for(int i=0;i<n;i++)
   { Res=Res+zo[rand()%2];
   }
  return Res;
}

//-------------------------------------------------------------------------


//--------To generate random Probability between 0 and 1-------------------

float GenerateRandomProbability()
{
	float Res=(float)rand()/RAND_MAX;
  return Res;

}

//-------------------------------------------------------------------------



//-------------------Generate error--------------------------

list<string> Generor(int a,list<string>codes,float prob)
{	list<string>tempstore;
	int p1,p2,p3;
	if(a==1)
	{	for(auto code:codes)
		{
			if(prob<=GenerateRandomProbability())
			{
				p1=rand()%6;
			code[p1]=invert(code[p1]);
		   }
		tempstore.push_back(code);
		}
	}
	else
	{	for(auto code:codes)
		{
			if(prob<=GenerateRandomProbability())
			{
			p2=rand()%3;
			p3=rand()%6+3;
			code[p2]=invert(code[p2]);
			code[p3]=invert(code[p3]);
		   }
		   tempstore.push_back(code);
	}

	}
	return tempstore;
}

//-----------------------------------------------------------


 //..............................Binary to Decimal-----------------------------------

 int B2D(string s)
 {
 	int dec=0,n[3];
 	for(int i=2;i>=0;i--)
 	{
 		if(s[i]=='1')
 		  n[2-i]=1;
 		else
 		  n[2-i]=0;
 	}

 	for(int i=0;i<3;i++)
 	{
 		dec=dec+(n[i]*pow(2,i));
 	}

 return dec;
 }

 //----------------------------------------------------------------------------------


 //------------------------invert 0 to 1 and vice versa------------------------------

 char invert(char a)
{
	     if(a=='0')
		return '1';
	else
		return'0';
}

//-----------------------------------------------------------------------------------

list<string> Hamming(list<string>codes)
{	list<string>hamcode;
	for(auto code:codes)
	{
	int temp[4]={0,0,0,0};
	for(int i=0;i<4;i++)
	{
		if(code[i]=='1')
			temp[i]=1;
	}
	string s="0000000";

		s[0]=code[0];s[1]=code[1];s[2]=code[2],s[4]=code[3];

if((temp[1]+temp[2]+temp[0])%2==1)
	{s[3]='1';}
if((temp[3]+temp[1]+temp[0])%2==1)
	{s[5]='1';}
if((temp[3]+temp[2]+temp[0])%2==1)
	{s[6]='1';}

	hamcode.push_back(s);
	}
return hamcode;
}


//-------------Detection and correction----------------------------

list<string> Detectioncorrection(list<string>CodeWord)
{	list<string>tsempstore;
	for(auto code:CodeWord)
	{
		string loc="";
int temp[7]={0,0,0,0,0,0,0};
	for(int i=0;i<code.size();i++)
	{
		if(code[i]=='1')
			temp[i]=1;
	}
		if((temp[0]+temp[1]+temp[2]+temp[3])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}

	   if((temp[4]+temp[5]+temp[1]+temp[0])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}

	   if((temp[6]+temp[4]+temp[2]+temp[0])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}

int v=B2D(loc);
cout<<"("<<v<<")"<<code<<" ";
if(v!=0)
{
	code[7-v]=invert(code[7-v]);
}

	tsempstore.push_back(code);
	}

return tsempstore;
}

//------------------------------------------------------------


bool Detection(list<string>CodeWord)
{	bool res=true;
	for(auto code:CodeWord)
	{
		string loc="";
int temp[7]={0,0,0,0,0,0,0};
	for(int i=0;i<7;i++)
	{
		if(code[i]=='1')
			temp[i]=1;
	}
		if((temp[0]+temp[1]+temp[2]+temp[3])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}
	   if((temp[4]+temp[5]+temp[1]+temp[0])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}
	   if((temp[6]+temp[4]+temp[2]+temp[0])%2==1)
		{loc=loc+'1';}
	else
		{loc=loc+'0';}
 int v=B2D(loc);
	if(v!=0)
	{
		res=false;
		break;
	}

	}
	return res;

}


//------------To display codes--------------------------------

void Display(list<string>codes)
{
	for(auto code:codes)
	{
		cout<<code<<" ";
	}
}

//-----------------------------------------------------------



//--------data extraction from hamming code------------------

list<string> ExtractData(list<string>codes)
{	list<string> Res;
	for(auto code:codes)
	{ string temp="";
		temp=temp+code[0]+code[1]+code[2]+code[4];

		Res.push_back(temp);
	}
return Res;
}

//----------------------------------------------------------
