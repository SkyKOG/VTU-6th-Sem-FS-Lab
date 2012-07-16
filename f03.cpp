//LAB PROGRAM 3.
//	Write a C++ program to read and write student object with variable length records using any suitable record structure
//	Implement pack(), unpack(), modify(), and search() methods.
//
//	The only diiference from LAB PROG 2 is that we can use variable record structure.
//	Thus no length is required to be fixed(like 45) and no need of padding short records and rejecting long records
//	

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

class student
{
	
	public:	
		string usn, name, sem;
		void enter_data();		//NOTE: all functions except pack() are exactly the same.
		void display_data();		
		void pack();	
		void unpack();	
		void modify();		
}s[100];
fstream fp;
void search();				
void error(int);			

int main()
{
	int choice;
	
	system("clear");	
		
	while(1)
	{
		cout<<"\n1. Insert a Record\n2. Search and modify a record\n3. Exit\nEnter choice: "<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				s[0].enter_data();
				fp.open("in2.txt",ios::out|ios::app);		
				if(!fp)						
					error(1);
				s[0].pack();
				fp.close();
				break;
			case 2:	
				search();
				break;
				default: exit(0);	
		}
	}
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
	string buf = usn + "|" + name + "|" + sem + "|";	//no need of padding and rejecting
	fp<<buf<<endl;
}
void search()
{
	string usn_srch;
	int i=0, srch_flag=-1, modify_flag=-1, count;
	cout<<"\nEnter the USN of the student to be found: ";
	cin>>usn_srch;
	fp.open("in2.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)			
	{
		s[i].unpack();
		i++;
	}
	fp.close();
	count = i-1;
	for(i=0;i<=count;i++)		
	{
		if(s[i].usn==usn_srch)
		{	
			srch_flag=i;
			break;
		}
	}
	if(srch_flag==-1)
	{
		cout<<"\nRecord Not found!\n";
		return;
	}
	cout<<"\nRecord Found!\n";
	s[srch_flag].display_data();
	cout<<"\nDo you wish to modify the Record??\n Press 1. to modify, 0. to Cancel\n";
	cin>>modify_flag;
	if(modify_flag)
	{	s[srch_flag].modify();
		fp.open("in2.txt",ios::out);
		if(!fp)
			error(1);
		for(i=0;i<count;i++)
			s[i].pack();
		fp.close();
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
void student::modify()				
{
	int choice;	
	while(1)
	{	
		cout<<"\nEnter the field to modify:\n 1. name\n 2.usn \n 3.sem \n 4. to exit modification\n";
		cin>>choice;
		switch(choice)
		{
			case 1:	cout<<"\nEnter new name: ";
				cin>>name;
				break;
			case 2:	cout<<"\nEnter new usn: ";
				cin>>usn;
				break;
			case 3: cout<<"\nEnter new sem: ";
				cin>>sem;
				break;
			default: return;
		}
	}
}

void error(int error_type)
{
	switch(error_type)
	{
		case 1: cout<<"\nFATAL ERROR!: Unable to open the record File\n";
			exit(0);		
	}
}
