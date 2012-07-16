//LAB PROGRAM 12. Write a C++ program to reclaim the free space resulting from the deletion of records using linked lists. 

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

struct node
{
	int addr;
	struct node * link;
};

typedef struct node * NODE;
NODE first = NULL;

fstream fp;
void del();
void error(int);

int main()
{
	int choice,i;
	system("clear");
	student s;
	
	while(1)
	{
		cout<<"\n1. Insert a Record\n2. Delete a record\n3.Display Records\n4. Exit\n\nEnter Choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				s.enter_data();
				s.pack();
				break;
			case 2:	
				del();
				break;
			case 3: 
				fp.open("record12.txt", ios::in);
				if(!fp)
					error(1);
				i=0;
				while(fp)
				{
					s.unpack();
					if(s.usn.length()==0)
						break;
					if(s.usn[0]=='*')
						continue;	
					cout<<"\nRecord "<< ++i;
					s.display_data();
				}
				fp.close();
				break;
			default:
				exit(0);
		}
	}
}

void student::enter_data()
{
	cout<<"\nEnter Usn : ";
	cin>>usn;
	cout<<"\nEnter Name : ";
	cin>>name;
	cout<<"\nEnter Sem: ";
	cin>>sem;
}

void student::display_data()
{
	cout<<"\nName : "<<name<<"\nUSN : "<<usn<<"\nSem : "<<sem<<endl;
} 

void student::pack()
{
	string buf = usn + "|" + name + "|" + sem + "|";
	if(buf.length() > 45)			
	{	error(2);
		return;
	}
	while(buf.length()<46)			
		buf += '_';
	if(first != NULL)
	{
		fp.open("record12.txt",ios::out|ios::in);
		if(!fp)
			error(1);
		fp.seekp(first->addr, ios::beg);
		cout<<"Reusing deleted space at position : "<<first->addr<<endl;
		NODE temp = first;
		first = temp->link;
        delete temp;
	}
	else
		fp.open("record12.txt",ios::out|ios::app);
	fp<<buf<<endl;
	fp.close();
}

void student::unpack()
{
		string seg;
		getline(fp,usn,'|');
		getline(fp,name,'|');
		getline(fp,sem,'|');
		getline(fp,seg);			
}

void del()
{
	string usn_srch;
	int pos, flag=0;
	cout<<"\nEnter the USN of the student to be deleted : ";
	cin>>usn_srch;
	fp.open("record12.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)
	{
		pos = fp.tellg();		
		s.unpack();
		if(usn_srch == s.usn)
		{
			flag=1;			
			cout<<"\nThe Following Record is Deleted at position :"<<pos<<endl;
			s.display_data();
			break;
		}	
	}
	if(!flag)
	{
		cout<<"\nRecord Not Found\n";
		return;
	}
	fp.close();
	fp.open("record12.txt",ios::out|ios::in);
	if(!fp)
		error(1);
	fp.seekp(pos,ios::beg);
	fp.put('*');
	NODE temp = new struct node;
	temp->addr = pos;
	temp->link = first;
	first = temp;
	fp.close();
}

void error(int error_type)
{
	switch(error_type)
	{
		case 1: cout<<"\nFATAL ERROR!: Unable to open the record File\n";
			exit(0);
		case 2:	cout<<"\n ERROR!: Data exceeds record length\n";
			return;
	}
}
