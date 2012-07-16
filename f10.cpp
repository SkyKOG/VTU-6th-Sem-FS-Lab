//LAB PROGRAM 10. Write a C++ program to implement B+ Trees for a given set of integers and its operations   insert ( ) and search ( ). Display the tree.
#define MAX 4			
#define MIN 2
#include<iostream>
#include<stdlib.h>
using namespace std;

struct node 
{
	int ele[MAX];				
	struct node * child[MAX];		
	struct node * parent;
	struct node * next_child;
};
typedef struct node * NODE;

class btree
{
	NODE root;
	public:
		btree()					
		{	
			root=create_newnode();	
		}	
		void insert(int);				
		int search(int);				
		void display();					
		int isFull(NODE);				
		NODE create_newnode();				
		NODE find_leaf(NODE,int);			
		void split(NODE);							
		void sort_node(NODE);				
		void update_parent(NODE, int, int);		
};

int main()
{
	btree  b;	
	int ch, key, flag;	

	system("clear");	
	while(1)
	{
		cout<<"\n\nMain Menu\n-------------\n1. to insert an element\n2. to Search for an element\n3. to Display the Tree\n4. to Exit\nEnter Choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:	cout<<"Enter the integer to be inserted: ";
				cin>>key;
				b.insert(key);
				break;
			case 2:	cout<<"Enter the integer to be found: ";
				cin>>key;
				flag=b.search(key);
				if(flag)
					cout<<"Element is present\n";
				else
					cout<<"Element not found\n";
				break;
			case 3: b.display();
				break;
			default:exit(0);
		}
	}
}


void btree::insert(int key)
{
	int i,j, t, max;			
	NODE temp = find_leaf(root,key);	
	if(!temp)				
	{
		cout<<"Error!: Cannot insert: This integer is already present in the tree\n";
		return;		
	}
	if(!isFull(temp))			
	{
		cout<<"Element inserted successfully\n";
		for(i=0;i<MAX;i++)
		{	
			if(temp->ele[i]==-1)
			{	
				temp->ele[i]=key;
				break;
			}
			max=temp->ele[i];
		}
		sort_node(temp);
		if(key>max && temp->parent!=NULL)		
			update_parent(temp->parent,key,max);
		return;
	}	
	if(isFull(temp))			
	{
		split(temp);
		insert(key);			
	}
}

int btree::isFull(NODE x)
{
	return (x->ele[MAX-1]==-1)?0:1;		
}

NODE btree::create_newnode()				
{						
	int i;	
	NODE temp = new struct node;
	if(!temp)
	{
		cout<<"Fatal ERROR: Out of Memory!\n";
		exit(0);
	}
	for(i=0;i<MAX;i++)
	{
		temp->ele[i]=-1;
		temp->child[i]=NULL;
	}
	temp->parent=NULL;
	temp->next_child=NULL;
	return temp;
}

NODE btree::find_leaf(NODE x, int key)
{
	int i;	
	if(x->child[0]==NULL)			
	{						
		for(i=0;i<MAX;i++)
			if(key==x->ele[i])
				return NULL;	
		return x;
	}
	for(i=0;i<MAX;i++)				
	{
		if(x->ele[i] >= key)
			return find_leaf(x->child[i],key);
		if(x->ele[i]==-1)			
			return find_leaf(x->child[i-1],key);
	}
	return find_leaf(x->child[MAX-1],key);
}

void btree::sort_node(NODE x)			
{
	int i,j;
	int temp_ele;
	NODE temp_child;
	for(i=0;i<MAX && x->ele[i]!=-1;i++)
	{
		for(j=i+1;j<MAX && x->ele[j]!=-1;j++)
		{
			if(x->ele[i]>x->ele[j])
			{
				temp_ele = x->ele[i];
				temp_child = x->child[i];
		
				x->ele[i] = x->ele[j];
				x->child[i] = x->child[j];
		
				x->ele[j] = temp_ele;
				x->child[j]= temp_child;
			}
		}
	}
}
				
void btree::split(NODE x)
{
	int i;
	NODE temp;
	if(x->parent==NULL)				
	{
		temp = create_newnode();
		root = create_newnode();
		
		root->ele[0] = x->ele[MIN-1];		
		root->child[0] = x;
		root->ele[1] = x->ele[MAX-1];
		root->child[1] = temp;

		x->parent = root;
		temp->parent = x->parent;					
	}
	else
	{
		if(isFull(x->parent))				
			split(x->parent);
	
		temp = create_newnode();			
		temp->parent = x->parent;
		for(i=0;i<MAX;i++)				
		{
			if(x->parent->ele[i]==x->ele[MAX-1])
				x->parent->child[i]=temp;
			if(x->parent->ele[i]==-1)
			{
				x->parent->ele[i]=x->ele[MIN-1];
				x->parent->child[i]=x;
				break;
			}	
			
		}
	}
	temp->next_child=x->next_child;
	x->next_child=temp;
	for(i=0;i<MIN;i++)				
	{
		temp->ele[i]=x->ele[MIN+i];
		x->ele[MIN+i]=-1;
		temp->child[i]=x->child[MIN+i];
		if(temp->child[i]!=NULL)
			temp->child[i]->parent = temp;
		x->child[MIN+i]=NULL;
	}
	sort_node(x->parent); 
}

void btree::update_parent(NODE x, int key, int max)
{
	int i, new_max;
	for(i=0;i<MAX&&(x->ele[i]!=-1);i++)
	{
		new_max=x->ele[i];
		if(x->ele[i]==max)
			x->ele[i]=key;
	}
	if(key>new_max && x->parent!=NULL)
		update_parent(x->parent,key,max);
}

int btree::search(int key)
{
	NODE temp = find_leaf(root, key);	
	if(temp==NULL)
		return 1;
	return 0;
}
void btree::display()
{
	NODE queue[50];
	int f=0, r=-1, lvl = -1, i;
	queue[++r]=NULL;
	queue[++r]=root;
	while(f<r)
	{
		if(queue[f]==NULL)
		{	
			cout<<"\n\nLevel --> "<<++lvl<<endl;
			if(queue[r]!=NULL)
				queue[++r]=NULL;
			f++;		
		}
		else
		{
			for(i=0;i<MAX;i++)
			{	
				if(queue[f]->ele[i]!=-1)				
					cout<<queue[f]->ele[i]<<" ";
				if(queue[f]->child[i]!=NULL)	
					queue[++r]=queue[f]->child[i];
			}				
			cout<<"       ";
			f++;
		}
	}
}
