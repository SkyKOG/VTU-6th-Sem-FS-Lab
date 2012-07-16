//LAB PROGRAM 7. Write a C++ program to read two lists of names and then match the names in the two lists using Cosequential Match based on a single loop. Output the names common to both the lists.

//before executing these programs make sure u have 2 files "1.txt" and "2.txt" which contain lists of names... (keep some common names in both lists since that is the objective of the program).

//Program is executed in 3 steps.
// Step 1. Read the lists from the files and store in 2 arrays -> read_list() function
// Step 2. Sort the arrays using any sorting tech(bubble sort used here) -> sort_list() function.
// Step 3. Match the 2 sorted arrays and display common names -> match_list().

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

class coseq
{
	public:
		string list1[100],list2[100];
		int count1, count2;
		void read_lists();
		void sort_lists();
		void match_lists();
};
void error(int);

int main()
{
	system("clear");
	coseq c;
	c.read_lists();
	c.sort_lists();
    cout<<"\n\nCommon Names in Both Lists Are : \n";
	c.match_lists();
	return 0;
}

void coseq::read_lists()
{
	fstream fp;
	string name;

	count1 = 0;		// Initially 0 names in arrays
	fp.open("1.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)
	{
		getline(fp,name);		//read from file
		list1[count1++]=name;		//store in array
	}
	fp.close();

	//Now same thing for the next file.
	count2 = 0;
	fp.open("2.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)
	{
		getline(fp,name);
		list2[count2++]=name;
	}
	fp.close();
}

void coseq::sort_lists()
{
	int i,j;
	string temp;

	for(i=0;i<count1;i++)
	{
		for(j=i+1;j<count1;j++)
		{
			if(list1[i]>list1[j])
			{
				temp=list1[i];
				list1[i]=list1[j];
				list1[j]=temp;
			}
		}
	}
    
    cout<<"\nThe Sorted Contents of List 1 : \n";
    for(i=0;i<=count1;i++)
        cout<<list1[i]<<"\n";

	//Now same thing for the second list.
	for(i=0;i<count2;i++)
	{
		for(j=i+1;j<=count2;j++)
		{
			if(list2[i]>list2[j])
			{
				temp=list2[i];
				list2[i]=list2[j];
				list2[j]=temp;
			}
		}
	}

    cout<<"\nThe Sorted Contents of List 2 : \n";
    for(i=0;i<=count2;i++)
        cout<<list2[i]<<"\n";
}

void coseq::match_lists()
{
	int i=0,j=0;
	while(i<=count1 && j<=count2)
	{
		if(list1[i]==list2[j])
		{
			cout<<list1[i]<<endl;
			i++;
			j++;
		}
		if(list1[i]<list2[j])i++;
		if(list1[i]>list2[j])j++;
	}
}

void error(int error_type)
{
	switch(error_type)
	{
		case 1: cout<<"\nFATAL ERROR!: Unable to open the File(s)\n";
			exit(0);		
	}
}
