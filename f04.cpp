//LAB PROGRAM 4
//Write a C++ program to write student objects with Variable - Length records using any suitable record structure and to read from this file a student record using RRN.
//RRN is the relative record number. i.e RRN of 1st record is 1, 2nd is 2 and so on...

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

class student
{
	string usn, name, sem;
	public:
		void enter_data();
		void display_data();		
		void pack();	
		void unpack(int); // in this prog only the required record is unpacked. the "int" argument is used to specify the position of the required record in the file.
}s1;

int rrn[100], cnt = 0;
fstream fp1;

void find_rrn();
void search();
void error(int);

int main()
{
	int choice;
	
	system("clear");
	fp1.open("record4.txt",ios::out|ios::app);
	fp1.close();	
	find_rrn();
	
	while(1)
	{
		cout<<"\n1. Insert a record\n2. Search for record using RRN\n3. Exit\n\nEnter Choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				s1.enter_data();
				fp1.open("record4.txt",ios::out|ios::app);
				if(!fp1)
					error(1);
				s1.pack();
				fp1.close();
				break;
			case 2:
				search();
				break;
			default: exit(0);
		}
	}		
}

void find_rrn()
{
	int pos;
	string seg;
	fp1.open("record4.txt",ios::in);
	if(!fp1)
		error(1);	
	while(fp1)
	{
		pos = fp1.tellg();
		getline(fp1,seg);
		if(seg.length()==0)
			continue;
		rrn[++cnt] = pos;
	}
	fp1.close();
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
	int pos = fp1.tellg();
	string buf = usn + "|" + name + "|" + sem + "|";	
	fp1<<buf<<endl;
	rrn[++cnt] = pos;
}

void search()
{
	int rrn_srch, pos;
	cout<<"\nEnter the RRN of the record to be found:\n";
	cin>>rrn_srch;
	if(rrn_srch>cnt||rrn_srch<1)
	{	error(2);
		return;
	}
	cout<<"\nRecord Found:\n";
	pos = rrn[rrn_srch];
	fp1.open("record4.txt", ios::in);
	if(!fp1)
		error(1);
	s1.unpack(pos);
	fp1.close();
	s1.display_data();
}

void student::unpack(int pos)
{
	fp1.seekg(pos, ios::beg);
	getline(fp1, usn, '|');
	getline(fp1, name, '|');
	getline(fp1, sem, '|');
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
		case 2:	cout<<"\nInvalid RRN\n";
			return;		
	}
}	
