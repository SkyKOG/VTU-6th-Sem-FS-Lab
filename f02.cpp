//LAB PROGRAM 2.
//	Write a C++ program to read and write student object with fixed length records and the fields delimited by "|"
//	Implement pack(), unpack(), modify(), and search() methods.
//
//	Assume a "student object" has foll fields: USN, NAME, SEM
//
//	Also we have to use fixed length records. Let us fix the length to 45. Smaller records have to be padded with some "dummy" symbol('_') at the end, Longer records are rejected...

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>		//stlib is a C library, not a C++ library... thus the ".h"
using namespace std;

class student
{
	public:
		string usn, name, sem;
		void enter_data();	//input name usn sem from the user and stores in object
		void display_data();	//displays an object(name,usn, sem) to the user
		void pack();		//converts an object to a string and writes the string to the record file
		void unpack();		//reads 1 line in the record file to a string and converts this string to an object
		void modify();		//accepts new values for name usn and sem from the user
}s[100],temp;
fstream fp;

void search();				//unpacks all records and searches for particular record... if it is modified... all the records are again packed
void error(int);			//displays suitable error messages

int main()
{
	int choice;
	system("clear");		// == clrscr();
		
	while(1)
	{
		cout<<"\n1. Insert a Record\n2. Search and modify a record\n3. Exit\nEnter choice: "<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				temp.enter_data();
				fp.open("in.txt",ios::out|ios::app);		//ios::out -> open file for writing, ios::app -> append i.e. write at the end of the file, (existing matter is not overwritten)
				if(!fp)						//check if file has opened successfully, else display 1st error
					error(1);
				temp.pack();
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
	string buf = usn + "|" + name + "|" + sem + "|";
	if(buf.length() > 45)			//if rec length> 45 then we have to reject the record by displaying 2nde error
	{	error(2);
		return;
	}
	while(buf.length()<46)			//if rec len < 45.. extra bytes is padded
		buf += '_';
	fp<<buf<<endl;
}
void search()
{
	string usn_srch;
	int i=0, srch_flag=-1, modify_flag=-1, count;
	cout<<"\nEnter the USN of the student to be found: ";
	cin>>usn_srch;
	fp.open("in.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)			//unpack all the records in the file and store in objects
	{
		s[i].unpack();
		i++;
	}
	fp.close();
	count = i;
	for(i=0;i<count;i++)		//search each of the objects for required usn
	{
		if(s[i].usn==usn_srch)
		{	
			srch_flag=i;
			break;
		}
	}
	if(srch_flag==-1)
	{
		cout<<"Record Not found!";
		return;
	}
	cout<<"\nRecord Found!\n";
	s[srch_flag].display_data();
	cout<<"\nDo you wish to modify the Record??\n Press 1. to modify, 0. to Cancel\n";
	cin>>modify_flag;
	if(modify_flag)
	{	s[srch_flag].modify();
		fp.open("in.txt",ios::out);
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
		case 2:	cout<<"\n ERROR!: Data exceeds record length\n";
			return;
	}
}
