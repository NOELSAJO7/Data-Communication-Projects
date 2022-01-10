#include<bits/stdc++.h>
#include<time.h>
using namespace std;

float GenerateRandomProbability();
string GenerateRandomString(int n);
string EXOR(string s1,string s2);
string REMAINDER(string LST,string divisor);
list<string> CRC8(list<string>LST,string divisor);
char invert(char a);
list<string> AddNoise(list<string>LST,float prob);
bool ReceiveData(list<string>&LST,string divisor);


int main()
{
	srand(time(0));
	list<string>TOKENS,input,dataword,noise;
	string S,tokn="",tmp="",divisor="100000111";
	int opt,len;
	cout<<"\n\tEnter the length of random string to be generated (>=32)  :     ";
	cin>>len;
	S=GenerateRandomString(len);

// 	To tokenise it to 16 bits

	if(len%16!=0)
	{	int n=(len/16);
		for(int i=0;i<(((n+1)*16)-len);i++)
		{tokn=tokn+"0";}
		S=tokn+S;
	}
for(int j=0;j<S.size();j++)
{ if((j+1)%16==0)
	{ 	tmp=tmp+S[j];
		TOKENS.push_back(tmp);
		tmp="";
	}
	else
		{
			tmp=tmp+S[j];
		}
}

	cout<<"\n\n\t\tNumber of Hops in communication channel ( 1 / 2 )    :     ";
	cin>>opt;
	switch(opt)
	{
		case 1:	float p1;
				cout<<"\n\n\t\tEnter the Crossover Probability    :     ";
				cin>>p1;
				dataword=CRC8(TOKENS,divisor);
				noise=AddNoise(dataword,p1);
				break;
		case 2: float p,q,prob;
				cout<<"\n\n\t\tEnter the Crossover Probabilities of 1st and 2nd Hops    :     ";
				cin>>p>>q;
				prob=(p*(1-q)+q*(1-p));
				dataword=CRC8(TOKENS,divisor);
				noise=AddNoise(dataword,prob);
				break;
		default: cout<<"Invalid Selection........!!!";
	}

	cout<<"\n\n\tInput Data was : ";
	for(auto k:TOKENS)
	{
		cout<<k<<" ";
	}
	cout<<"\n\n\tSend Data was : ";
	for(auto a:dataword)
	{
		cout<<a<<" ";
	}
	cout<<"\n\n\tReceived Data is : ";
	for(auto a:noise)
	{
		cout<<a<<" ";
	}
	if(ReceiveData(noise,divisor))
	{
		cout<<"\n\n\tExtracted Data is : ";
		for(auto t:noise)
	{
		cout<<t.substr(0,16)<<" ";
	}
	}
	else
		cout<<endl<<endl<<"\t\tReceived data is discarded-----------!!!!!!";

cout<<endl<<endl;

return 0;
}


//--------To generate random Probability between 0 and 1------------------

float GenerateRandomProbability()
{
	float Res=(float)rand()/RAND_MAX;
  return Res;
}

//------------------------------------------------------------------------


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


//-------------------- perform exor operation------------------------------

string EXOR(string s1,string s2)
{	string Res="";
	for(int i=1;i<s1.size();i++)
	{
		if(s1[i]==s2[i])
			Res=Res+"0";
		else
			Res=Res+"1";
	}

	return Res;
}

//---------------------------------------------------------------------------------



//-------------------------Codeword generation-------------------------------------

 list<string> CRC8(list<string>LST,string divisor)
{ list<string> Temp;
for(auto lst:LST)
{
	string Augmented=lst+"00000000";		//Generating Augmented Datawords
	string rem;
	rem=REMAINDER(Augmented,divisor);
	Temp.push_back(lst+rem);

}
return Temp;
}

//-----------------------------------------------------------------------------------

//---------------To find the remainde after polinomial division----------------------

string REMAINDER(string LST,string divisor)
{
	string  rem;
	rem=LST.substr(0,9);
	 for(int j=9;j<LST.size();j++)
 {
	 if(rem[0]=='0')
    {
      rem=rem.substr(1,8)+LST[j];
    }
    else if(rem[0]=='1')
    {
            rem=EXOR(rem,divisor)+LST[j];

    }
  }

     if (rem[0] == '1')
		rem=EXOR(divisor,rem);
	else
		rem=EXOR(std::string(9, '0'),rem);

 return rem;
 }

 //------------------------------------------------------------------------------------


//----------------------------To check received data-----------------------------------

 bool ReceiveData(list<string>&LST,string divisor)
 {	bool res=true;
 	for(auto lst:LST)
 	{
 	string rem=REMAINDER(lst,"100000111");
 	if(rem=="00000000")
 	{	lst=lst.substr(0,16);
 	}
 	else
 	{
 		 res=false;
 		 break;
 	}
 	}
 return res;
 }

//-------------------------------------------------------------------------------------

//--------------to change 0 to 1 and vice versa----------------------------------------

char invert(char a)
{
	     if(a=='0')
		return '1';
	else
		return'0';
}

//-----------------noise added-------------------------------------------------------

list<string> AddNoise(list<string>LST,float prob)
 { list<string>noise;
 	for(auto lst:LST)
 	{
 		for(int j=0;j<lst.size();j++)
 		{
 			if(prob>=GenerateRandomProbability())
 			{
 				lst[j]=invert(lst[j]);

 			}
 		}
 		noise.push_back(lst);
 	}
 return noise;
 }

 //----------------------------------------------------------------------------------
