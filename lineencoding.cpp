#include<bits/stdc++.h>
#include <graphics.h>
using namespace std;


string GenerateRandomString(int n);
string NRZL(string s);
string NRZI(string s);
string AMI(string s);
string MANCHESTER(string s);
string DIFFMANCHESTER(string s);
vector<int>Zeropositions(string s, string pattern,int n);
int numofones(string s,int pos);
string HDB3SCRAMBLING(string s);
string B8ZSSCRAMBLING(string s);
string LCS(string s1,string s2);
string LPS(string str);



int main()
{  string code,encode="";
   int N,M;
   cout<<"Do you want Random sequence or Random sequence with some fixed sub sequence ? \nEnter Your Choice (1 / 2)\n";
   cout<<"\n\n1. Random sequence\n\n2. Random sequence with some fixed sub sequence(for scrambling)\n\n  ";
   cin>>N;

   switch(N)
   {  int c;
      case 1:
              cout<<"Enter the number of bits \t ";
              cin>>c;
              code=GenerateRandomString(c);

              break;
      case 2:
              cout<<"Enter the number of bits \t ";
              cin>>c;
              int ncz;
              cout<<"Number of consecutive Zeroes you want : ";
              cin>>ncz;
              cout<<"position at which yo wand to insert it : ( B / E / P )";
              char pos;
              cout<<"   B. Beginning\t\t  E. End\t\t  P.At some position \n  ";
              cin>>pos;
               switch(pos)
               {
                  case 'B':  for(int i=0;i<ncz;i++)
                              code=code+"0";

                            code=code+GenerateRandomString(c-ncz);
                              break;
                  case 'E':   code=code+GenerateRandomString(c-ncz);
                              for(int i=0;i<ncz;i++)
                                 code=code+"0";
                              break;
                  case 'P':  int p;
                            cout<<"Enter the position :    ";
                            cin>>p;
                             code=code+GenerateRandomString(p-1);
                              for(int i=0;i<ncz;i++)
                                 code=code+"0";
                             code=code+GenerateRandomString(c-(ncz+p));
                              break;
                  default:cout<<"Invalid Choice .....!!!!";
               }
              break;
      default:cout<<"Invalid Choice....!!!!";
   }
cout<<"Which Encoding Scheme Do You want to apply ? ( 1 / 2 / 3 / 4 )\n\n";
cout<<"\t1. NRZ-L\t2. NRZ-I\t3. Manchester\t4. Differential Manchester\t5. AMI\n\n  ";
cin>>M;

switch(M)
{
   case 1:  encode=NRZL(code);
            break;
   case 2:  encode=NRZI(code);
            break;
   case 3:  encode=MANCHESTER(code);
            break;
   case 4: encode=DIFFMANCHESTER(code);
            break;
   case 5:  char s;
            cout<<"Do You want to apply SCRAMBLING (Y/N)?\t";
            cin>>s;
            switch(s)
            {case 'Y':int x;
                    cout<<"Select SCRAMBLING Method \n\n\t 1.B8ZS \t 2. HDB3\n  ";
                    cin>>x;
                    if(x==1)
                     encode=B8ZSSCRAMBLING(code);
                    else if(x==2)
                     encode=HDB3SCRAMBLING(code);
                    else cout<<"Invalid choice";

                    break;

            case 'N':encode=AMI(code);
                     break;


            }
            break;
   default :cout<<"Invalid Choice.........!!!!";
}


vector<int>CodeVal;
for(int i=0;i<code.size();i++)
{
        if(code[i]=='0')
      CodeVal.push_back(0);
   else if(code[i]=='1')
      CodeVal.push_back(1);
}

vector<int>EncodeVal;
for(int i=0;i<encode.size();i++)
{
        if(encode[i]=='0')
      EncodeVal.push_back(0);
   else if(encode[i]=='1')
      EncodeVal.push_back(1);
   else if(encode[i]=='2')
      EncodeVal.push_back(-1);
}

cout<<"Given signal was  : ";
for(int i=0;i<code.size();i++)
{
    cout<<code[i]<<" ";
}
cout<<"\n\nEncoded signal is  : ";
for(int i=0;i<EncodeVal.size();i++)
{
    cout<<EncodeVal[i]<<" ";
}

cout<<"\n\n";
cout<<"Longest Palindromic Subsequence for Given signal : "<<LPS(code);
cout<<"\n\n";
cout<<"Longest Palindromic Subsequence for Encoded signal : "<<LPS(encode);

	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	int left, top, right, bottom;
	for(int i=0;i<CodeVal.size();i++)
	{
	    bar(left = (20+20*i), top =200-(30*CodeVal[i]),right =40+(20*i), bottom =200);
	line(40+(20*i),195,40+(20*i),205);}
	// x axis line
	line(10,200,700,200);

    if(EncodeVal.size()>CodeVal.size())
    {
	for(int i=0;i<EncodeVal.size();i++)
	{   setfillstyle(3,9);
	     bar(left = (20+10*i), top =350-(30*EncodeVal[i]),right =30+(10*i), bottom = 350);
	     line(30+(10*i),345,30+(10*i),355);
	}
	}else{
    for(int i=0;i<EncodeVal.size();i++)
    {   setfillstyle(3,9);
       bar(left = (20+20*i), top =350-(30*EncodeVal[i]),right =40+(20*i), bottom = 350);
       line(40+(20*i),345,40+(20*i),355);
    }

	}
	// x axis line
	line(10,350,700,350);
	getch();
	closegraph();


}



//------------------------------------------------------
//                functions used
//------------------------------------------------------

// for generation of random string
string GenerateRandomString(int n)
{  char zo[]={'0','1'};
   string Res="";
   for(int i=0;i<n;i++)
   { Res=Res+zo[rand()%2];
   }
  return Res;
}


//                 NRZL scheme
//.......................................................
string NRZL(string s)
{  string str="";
   for(int i=0;i<s.size();i++)
      {      if(s[i]=='1')
               str=str+"2";
            if(s[i]=='0')
               str=str+"1";
      }
return str;
}
//.......................................................

//                NRZI scheme
//.......................................................
string NRZI(string s)
{
   string str="";
   if(s[0]=='0')
      str=str+'1';
   else if(s[0]=='1')
      str=str+'2';

for(int i=1;i<s.size();i++)
 {  if(s[i]=='1'&&str[i-1]=='2')
      str=str+'1';
   else if(s[i]=='1' && str[i-1]=='1')
      str=str+'2';
   else
      str=str+str[i-1];
 }

   return str;
}

//.......................................................

//              Manchester scheme
//.......................................................
string MANCHESTER(string s)
{  string str="";
   for(int i=0;i<s.size();i++)
        {    if(s[i]=='1')
                { str=str+"21";
                }
            if(s[i]=='0')
                { str=str+"12";
                }
         }

   return str;
}

//......................................................

//          Differential manchester
//......................................................

string DIFFMANCHESTER(string s)
{
   string str="";
   if(s[0]=='0')
     { str=str+"21";
     }
   else if(s[0]=='1')
     { str=str+"12";
     }

for(int i=1;i<s.size();i++)
 {  if(s[i]=='0' && str[2*i-1]=='1')
     { str=str+"12";
     }
   else if(s[i]=='0' && str[2*i-1]=='2')
     { str=str+"21";
      }
   else if(s[i]=='1' && str[2*i-1]=='1')
     { str=str+"21";
     }
   else if(s[i]=='1' && str[2*i-1]=='2')
     { str=str+"12";
     }
 }

   return str;
}
//.....................................................


vector<int>Zeropositions(string s, string pattern,int n)
{     vector<int>T;
    int found = s.find(pattern);
    while (found != string::npos) {
         if(T.size()==0||T.back()+n<=found)
              T.push_back(found);
        found = s.find(pattern, found + 1);
    }
    return T;
}

//                            HDB3
//..................................................
string HDB3SCRAMBLING(string str)
{   vector<int>K; int t=0,count=0,i=0;
   K=Zeropositions(str,"0000",4);

while(i<str.size())
 {
   if(i==K[t])
   {  if(i==0)
            {str[i]='1';str[i+3]='1'; count++;}
      else
           {   if(numofones(str,i)==0)
                {  if(str[i-1]=='1')
                  {str[i]='2';str[i+3]='2';}
                else if(str[i-1]=='2')
                  {str[i]='1';str[i+3]='1';}
                }
                else
                {str[i+3]=str[i-1];

                }
           }
      i=i+4;
      t++;
   }
   else
   {
         if(str[i]=='1')
          {    count++;                   //here 2 represents -1
           if(count%2!=0)
             str[i]='1';
           else
             str[i]='2';
          }
            i++;
         }
   }
   return str;
 }

 //.........................................................


//B8ZS scrambling scheme
//.....................................................................................

string B8ZSSCRAMBLING(string str)
{  vector<int>K;
   K=Zeropositions(str,"00000000",8);
   // for(int i=0;i<K.size();i++)
   //    {int p=K[i];
   //       str[p+3]='V';str[p+4]='B';str[p+6]='V';str[p+7]='B';
   //    }
int i=0,t=0,count=0;

while(i<str.size())
{
   if(i==K[t])
   {
      if(i==0)                      //here 2 represents -1
         {str[3]='1';str[4]='2';str[6]='2';str[7]='1';         count++;}
      else if(str[i-1]=='2')
         {str[i+3]='2';str[i+4]='1';str[i+6]='1';str[i+7]='2'; }
      else if(str[i-1]=='1')
         {str[i+3]='1';str[i+4]='2';str[i+6]='2';str[i+7]='1'; count++;}
       i=i+8; t++;
   }
   else
   {  if(str[i]=='1')
      {
         count++;                   //here 2 represents -1
         if(count%2!=0)
            str[i]='1';
         else
            str[i]='2';

      }
         i++;
   }
}
return str;
}
//.................................................................................

// AMI encoding scheme
//...........................................................
string AMI(string s)
{   string res;  int count=0,t=0;
   for(int i=0;i<s.size();i++)
   {       if(s[i]=='0')
         res=res+'0';
      else if(s[i]=='1')
      {  count++;                   //here 2 represents -1
         if(count%2!=0)
            res=res+'1';
         else
            res=res+'2';
       }
    }
   return res;
}
//...........................................................

int numofones(string s,int pos)
{     int count=0;
   for(int i=0;i<=pos;i++)
   {
      if(s[i]!='0')
         count++;
   }
   return count%2;
}

//............................................................
//      For longest PalindromicSubsequence
//............................................................
string LCS(string C1, string C2)
{
   int m = C1.length();
   int n = C2.length();
   int L[m+1][n+1];
   for (int i=0; i<=m; i++)
   {
      for (int j=0; j<=n; j++)
      {
         if (i == 0 || j == 0)
            L[i][j] = 0;
         else if (C1[i-1] == C2[j-1])
            L[i][j] = L[i-1][j-1] + 1;
         else
            L[i][j] = max(L[i-1][j],L[i][j-1]);
      }
   }
   int index = L[m][n];
   string lcs(index+1, '\0');
   int i = m, j = n;
   while (i > 0 && j > 0)
   {
      if (C1[i-1] == C2[j-1])
      {
         lcs[index-1] = C1[i-1];
         i--;
         j--;
         index--;
      }
      else if (L[i-1][j] > L[i][j-1])
         i--;
      else
         j--;
   }
   return lcs;
}

string LPS(string str)
{
   string rev = str;
   reverse(rev.begin(), rev.end());
   return LCS(str, rev);
}


//---------------------------------------   END -----------------------------------------


