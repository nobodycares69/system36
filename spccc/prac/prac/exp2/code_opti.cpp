
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct store{
	char opr,opd1,opd2,result;
};

struct store input[20];

void same_lines(int);
void up(int);
void dead_code(int);
void display(int);
void display_after(int);

void code_optimization(int no_of_lines)
{
	cout<<endl<<"Displaying before optimization:\n";
	display(no_of_lines);
	cout<<endl;
	same_lines(no_of_lines);
	up(no_of_lines);
	dead_code(no_of_lines);
	cout<<endl<<"Displaying after optimization:\n";
	display_after(no_of_lines);
	cout<<endl;
}

void same_lines(int no_of_lines)
{
	char result;
	int flag=0;
	//Eleminating repetation
	for(int i=0;i<no_of_lines;i++)
		{
			for(int j=1;j<no_of_lines;j++)
			{
				if(i==j||(input[i].opr=='x'))
				{
					continue;
				}					
				else if((input[i].opr)==(input[j].opr)&&(input[i].opd1==input[j].opd1)&&(input[i].opd2==input[i].opd2))
				{
					flag=1;
					input[j].opr='x';
					result=input[j].result;
				}
				if(flag==1)
				{
				if((input[j].opd1)==result)
				{
					input[j].opd1=input[i].result;		
				}
				else if((input[j].opd2)==result)
				{
					input[j].opd2=input[i].result;
				}			
			}
		
		}
		}


}

void up(int no_of_lines)
{
	char result,temp;
	int flag=0;
	//Eleminating unnecessary multiplication
	for(int i=0;i<no_of_lines;i++)
		{
		
			if(input[i].opr=='x')
			{
				continue;
			}					
			else if((input[i].opr)==('*'))
			{
				if((input[i].opd1==('1'))||(input[i].opd2==('1')))
				{
					flag=1;
					input[i].opr='x';
					if((input[i].opd1==('1')))
					{
						temp=input[i].opd2;
						result=input[i].result;
						
					}
					else
					{
						temp=input[i].opd1;
						result=input[i].result;
					}
				}
				
				for(int j=i;j<no_of_lines;j++)
				{
					if((input[j].opd1==(result)))
					{
						input[j].opd1=temp;
					}
					else if(input[j].opd2==(result))
					{
						input[j].opd2==temp;
					}
					
				}
			}
			if((input[i].opr)==('+'))
			{
				if((input[i].opd1==('0'))||(input[i].opd2==('0')))
				{
					flag=1;
					input[i].opr='x';
					if((input[i].opd1==('0')))
					{
						temp=input[i].opd2;
						result=input[i].result;
						
					}
					else
					{
						temp=input[i].opd1;
						result=input[i].result;
					}
					
					for(int j=i;j<no_of_lines;j++)
					{
						if((input[j].opd1==(result)))
						{
							input[j].opd1=temp;
						}
						else if(input[j].opd2==(result))
						{
							input[j].opd2==temp;
						}
					
					}
				}
				
			}
		}


}

void dead_code(int no_of_lines)
{
	char temp;
	int flag=0;
	//Dead code elemination
	for(int i=0;i<no_of_lines;i++)
	{
		temp=input[i].result;
		//cout<<"Result in temp: "<<temp;
		for(int j=1;j<no_of_lines;j++)
		{
			if(i==j)
			{
			continue;
			}
			else if((input[j].opd1)==temp||(input[j].opd2)==temp)
			{
				flag++;
				//cout<<"Matching condition for: "<<temp<<endl;
			}
				
		}
		if(flag==0)
			{
				//cout<<"In flag\n";
				input[i].opr='x';
				flag=0;
			}
		
	}
}

void display(int no_of_lines)
{

	for(int i=0;i<no_of_lines;i++)
		{
			cout<<endl<<input[i].opr<<"\t"<<input[i].opd1<<"\t"<<input[i].opd2<<"\t"<<input[i].result;
		}
}


void display_after(int no_of_lines)
{
	for(int i=0;i<no_of_lines;i++)
		{
			if(input[i].opr=='x')
			{
				continue;
			}
			else
			{
				cout<<endl<<input[i].opr<<"\t"<<input[i].opd1<<"\t"<<input[i].opd2<<"\t"<<input[i].result;
			}
		}
}
int main()
{
	int n,no_of_lines,flag=0;
	cout<<"Enter number of three address codes to take: ";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Enter Operator: ";
		cin>>input[i].opr;
		cout<<"\nEnter first Operand: ";
		cin>>input[i].opd1;
		cout<<"\nEnter second Operand: ";
		cin>>input[i].opd2;		
		cout<<"\nEnter Result: ";
		cin>>input[i].result;	
		cout<<endl;	
		
	}

	code_optimization(n);
	
	return 0;
}
