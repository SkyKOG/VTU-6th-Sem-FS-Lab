//LAB PROGRAM 11. Write a C++ program to store and retrieve student data from file using hashing. Use any collision resolution technique.

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>		
using namespace std;

class student
{
	public:
		string usn, name, sem;
		void enter_data();	
		void display_data();	
		void pack();		
		void unpack();			
}s;
fstream fp;
int hash(string);
void search();
void error(int);

int main()
{
	int choice;
	system("clear");
	fp.open("record11.txt", ios::out|ios::app);
	fp.close();		
	while(1)
	{
		cout<<"\n1. Insert a Record\n2. Search for a record\n3. Exit\n\nEnter choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				s.enter_data();
				s.pack();
				break;
			case 2:	
				search();
				break;
				default: exit(0);	
		}
	}
}

int hash(string usn)
{
	int t;
	t=(((usn[0]-48)*100)+((usn[1]-48)*10)+(usn[2]-48))%9;
	return t*142;
}

void student::enter_data()
{
	cout<<"\nEnter usn: ";
	cin>>usn;
	cout<<"\nEnter name: ";
	cin>>name;
	cout<<"\nEnter sem: ";
	cin>>sem;
}

void student::pack()
{
	int cnt,pos;
	string temp;
	string buf = usn + "|" + name + "|" + sem + "|";
	if(buf.length() > 45)			
	{	error(2);
		return;
	}
	while(buf.length()<46)			
		buf += '_';

	pos = hash(usn);
	fp.open("record11.txt",ios::in);		
	if(!fp)						
		error(1);
	fp.seekg(pos,ios::beg);
	getline(fp,temp);
	fp.close();
	cnt = temp[0]-48;
	if(cnt == 3)
	{	
		error(3);
		return;
	}
	fp.open("record11.txt",ios::out|ios::in);
	if(!fp)
		error(1);
	if(cnt<0)
	{
		fp.seekp(pos,ios::beg);
		fp.put('1');
		pos=pos+1;
		
	}
	else if(cnt==1)
	{
		fp.seekp(pos,ios::beg);
		fp.put('2');
		pos=pos+48;
	}
	else if(cnt==2)
	{
		fp.seekp(pos,ios::beg);
		fp.put('3');
		pos=pos+95;
	}

	cout<<"inserting at :"<<pos;
	fp.seekp(pos,ios::beg);
	fp<<buf<<endl;
	fp.close();
}

void search()
{
	string usn_srch,temp;
	int cnt, flag =0, pos, i;
	cout<<"\nEnter the USN of the student to be found: ";
	cin>>usn_srch;
	pos = hash(usn_srch);
	fp.open("record11.txt",ios::in);
	fp.seekg(pos,ios::beg);
	getline(fp,temp);
	cnt = temp[0]-48;
	fp.seekg(pos+1,ios::beg);
	for(i=1;i<=cnt;i++)
	{
		s.unpack();
		if(usn_srch == s.usn)
		{
			flag=1;
			break;
		}
	}
	fp.close();
	if(!flag)
	{
		cout<<"Record Not Found!\n";
		return;
	}
	else
	{
		cout<<"Record Found\n";
		s.display_data();
	}		
}

void student::unpack()
{
		string seg;
		getline(fp,usn,'|');
		getline(fp,name,'|');
		getline(fp,sem,'|');
		getline(fp,seg);			
}

void student::display_data()
{
	cout<<"\nName: "<<name<<"\nusn: "<<usn<<"\nsem: "<<sem<<endl;
} 

void error(int error_type)
{
	switch(error_type)
	{
		case 1: cout<<"\nFATAL ERROR!: Unable to open the record File\n";
			exit(0);
		case 2:	cout<<"\n ERROR!: Data exceeds record length\n";
			return;
		case 3:	cout<<"\n ERROR!: Cannot insert!: Maximum no of collisions allowed = 3";
			return;
	}
}
