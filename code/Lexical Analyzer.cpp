

// LIBRARIES USED

#include <iostream>
#include <stack>
#include <string.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

// GLOBAL VARIABLES

stack<string>  PDA;
string input[100];
string output[100];
int input_length=-1;
int i=0,j=0 ;
string Non_Terminal[]={"NP","VP","Nominal","pp"};
string Terminal[]={"pronoun","propernoun","det","noun","verb","preposition"};

// GLOBAL FUNCTIONS

void NP();
void VP();
void Nominal();
void pp();
bool Checking_Word(string path,string str);

// MAIN FUNCTION

int main()
{
	string word , stack_ret ;
    cout<<"\n \xDB Lexical Analyzer\n\n";
    cout<<" \xDB Enter Sentence: ";
    string str;
    getline(cin,str);

	stringstream iss(str);
	while (iss >> word)
    {
	    input_length++;
		input[input_length]=word;
    }

	PDA.push("VP");
	PDA.push("NP");
    output[j]="NP";
    j++;
    output[j]="VP";
    int count=0;
    cout<<"\n \xDB Parser Demonstration:\n\nS "<<endl;
    while (!PDA.empty())
    {

    	stack_ret=PDA.top();

    	PDA.pop();
    	if(stack_ret.compare(Non_Terminal[0])==0)
		{
			if(count==0)
				cout<<output[0]<<" "<<output[1]<<endl;
			count++;
			NP();
	    }
    	else if(stack_ret.compare(Non_Terminal[1])==0)
		{
			VP();
		}
    	else if(stack_ret.compare(Non_Terminal[2])==0)
			Nominal();

    	else
    	{
    		if(stack_ret.compare(Non_Terminal[3])==0)
    			pp();
		}

	}
	cout<<"\n\n \xDB Sentence is VALID\n\n";
	return 0;
}

// STRING MATCHING FUNCTION

bool Checking_Word(string path,string str)
{
	ifstream Obj(path.c_str());
	int offset=str.length();
	char str_array[offset+1];
	strcpy(str_array,str.c_str());
	string word;
	bool ret=false;
    while (Obj >> word)
    {
        int n=word.length();
        char str_word[n+1];
        strcpy(str_word,word.c_str());
        if(strcmp(str_word,str_array)==0)
        {
        	i++;
        	ret=true;
        	break;
		}
    }
    Obj.close();
	return ret;
}

// NOMINAL PRODUCTION

void Nominal()
{
	string str=input[i];
	bool flag=false;
	string path="noun.txt";
	flag=Checking_Word(path,str);
	if(flag==true && str.length()>0)
	{
		int k;
		for(k=0; k<=j ; k++)
		{
			if(output[k]=="Nominal")
			{
				output[k]="noun";
				break;
			}
	    }
	    path="noun.txt";
	    string str2=input[i];
	    bool flag2=false;
	    flag2=Checking_Word(path,str2);

	    if(flag2==true && str2.length()>0)
	    {
		    i--;
		    for(int p=j+1 ; p>k+1 ; p--)
			{
				output[p]=output[p-1];
		    }
		    int r=k;
			output[r+1]="Nominal";
			j++;
			PDA.push(Non_Terminal[2]);
	    }

		for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;

		output[k]=str;
		for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;
    }
}

// PP PRODUCTION

void pp()
{
	string str=input[i];
	bool flag=false;
	string path="preposition.txt";
	flag=Checking_Word(path,str);
	if(flag==true && 	str.length()>0)
	{
		int k;
		for(k=0; k<=j ; k++)
		{
			if(output[k]=="PP")
			{
				output[k]="preposition";
				break;
			}
	    }

	    for(int p=j+1 ; p>k+1 ; p--)
		{
			output[p]=output[p-1];
	    }
		output[k+1]="NP";
		j++;

		for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;

		output[k]=str;
		for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;
		PDA.push(Non_Terminal[0]);
	}
	else
    {
        cout<<"\n INVALID STRUCTURE \n Exiting...";
        exit(0);
    }
}

// NP PRODUCTION

void NP()
{
	string str=input[i];
	bool flag=false;
	string path="pronouns.txt";
	flag=Checking_Word(path,str);
	if(flag)
	{

		int k;
		for(k=0; k<=j ; k++)
		{
			if(output[k]=="NP")
			{
				output[k]="pronoun";
				break;
			}
	    }

		for(int l=0; l<=j+1 ; l++)
			cout<<output[l]<<" ";
		cout<<endl;

		output[k]=str;
		for(int l=0; l<=j+1 ; l++)
			cout<<output[l]<<" ";
		cout<<endl;
	}
	else
	{
		string path="noun.txt";
		flag=Checking_Word(path,str);
		if(flag)
		{
	    	int k;
			for(k=0; k<=j ; k++)
			{
			if(output[k]=="NP")
			{
			output[k]="Noun";
			break;}
		    }

			for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
			cout<<endl;

			output[k]=str;
			for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
			cout<<endl;
		}
		else
		{
			string path="determiners.txt";
			flag=Checking_Word(path,str);
			if(flag)
			{
				int k;
				for(k=0; k<=j ; k++)
				{
					if(output[k]=="NP")
					{
						output[k]="Det";
						break;
					}
				}

				for(int p=j+1 ; p>k+1 ; p--)
				{
					output[p]=output[p-1];
			    }

				output[k+1]="Nominal";
				j++;
				for(int l=0; l<=j ; l++)
					cout<<output[l]<<" ";
				cout<<endl;

				output[k]=str;
				for(int l=0; l<=j ; l++)
					cout<<output[l]<<" ";
				cout<<endl;
			    PDA.push(Non_Terminal[2]);
			}
			else
		    {
		        cout<<"\n INVALID STRUCTURE \n Exiting...";
		        exit(0);
		    }
	    }
	}
}

// VP PRODUCTION

void VP()
{
	string str=input[i];
	bool flag=false;
	string path="verb.txt";
	flag=Checking_Word(path,str);
	if(flag==true && str.length()>0)
	{
		int k;
		for(k=0; k<=j ; k++)
		{
			if(output[k]=="VP")
			{
				output[k]="Verb";
				break;
			}
	    }
	    string str2=input[i];
	    if(Checking_Word("preposition.txt",str2)==true && str2.length()>0)
	    {
			i--;
		    for(int p=j+1 ; p>k+1 ; p--)
			{
				output[p]=output[p-1];
		    }
			output[k+1]="PP";
			j++;
			PDA.push(Non_Terminal[3]);
		}
		else
		{
		    bool flag2=false;
			if(Checking_Word("noun.txt",str2)==true && str2.length()>0)
				flag2=true;
			else if(Checking_Word("pronouns.txt",str2)==true && str2.length()>0)
				flag2=true;
			else if(Checking_Word("determiners.txt",str2)==true && str2.length()>0)
				flag2=true;
			else
				flag2=false;

			if(flag2)
			{
				i--;
		        for(int p=j+1 ; p>k+1 ; p--)
			    {
			    	output[p]=output[p-1];
		        }
			    output[k+1]="NP";
			    j++;

			    int q=i;
			    q++;
			    int r=k+1;
			    while(input[q]!="\0")
			    {
				    if(Checking_Word("preposition.txt",input[q]))
				    {
						i--;
					    for(int p=j+1 ; p>r+1 ; p--)
					    {
					    	output[p]=output[p-1];
				        }
					    output[r+1]="PP";
					    j++;
					    PDA.push(Non_Terminal[3]);
					    break;
					}
					q++;
				}
		    	PDA.push(Non_Terminal[0]);
			}
		}

	    for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;

		output[k]=str;
		for(int l=0; l<=j ; l++)
			cout<<output[l]<<" ";
		cout<<endl;
	}
    else
    {
        cout<<"\n INVALID STRUCTURE \n Exiting...";
        exit(0);
    }
}
// PROGRAM ENDED
