#include<stdio.h>
#include<stdlib.h>
#define s 100
struct Node{
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* GetNode(int x)
{
	struct Node* temp=(struct Node* )malloc(sizeof(struct Node* ));
	temp->data=x;
	temp->left=temp->right=NULL;
	return(temp);
}

struct Node* Bst(int x,struct Node* root){
	if(root==NULL){
		root=GetNode(x);
		return(root);
	}
	if(root->data>=x){
		root->left=Bst(x,root->left);
		return(root);
	}
	else{
		root->right=Bst(x,root->right);
		return(root);
	}
}


struct Node* FindMin(struct Node* root){
	if(root==NULL)return;
	while(root->left!=NULL){
		root=root->left;
	}
	
	return(root);
}
void Print(struct Node* root)
{
	if(root==NULL)return;
	printf("%d ",root->data);
	Print(root->left);
	Print(root->right);
}

struct Node* Delete(struct Node* root, int data)
{
	if(root==NULL)return(root);
	else if(data<root->data){
		root->left=Delete(root->left,data);
	}
	else if(data>root->data){
		root->right=Delete(root->right,data);
	}
	
	else //I found You, get ready to be deleted; 
	{
		if(root->left==NULL&&root->right==NULL)//Case 1:Node with No child.
		{
			free(root);
			root=NULL;
			return(root);
		}
		
		else if(root->left==NULL)//Case 2:Node with 1 child.
		{
			struct Node* temp=root;
			root=root->right;
			free(temp);
			return(root);
		}
		
		else if(root->right==NULL)//Case 2:Node with 1 child.
		{
			struct Node* temp=root;
			root-root->left;
			free(temp);
			return(root);
		}
		
		else {//Case 3: Node with two child.
			struct Node* temp=FindMin(root->right);
			root->data=temp->data;
			root->right=Delete(root->right,temp->data);
		}
		
	}
}


int front=-1;int rear=-1;
struct Node* q[s];

int isFull(){
	return((rear+1)%s==front?1:0);
}
int isEmpty(){
	if(front==-1&&rear==-1)return 1;
	return 0;
}
void enqueue(struct Node* x)//using circular array
{
	if(isFull())return;
	else if(isEmpty())
	{
		front=rear=0;
	}
	else {
		rear=(rear+1)%s;
	}
	q[rear]=x;
}
void Dequeue()
{
	if(isEmpty())return;
	else if(front==rear)rear=front=-1;
	else {
		front=(front+1)%s;
	}
}

struct Node* Front()
{
	return(q[front]);
}
void PrintQueue()
{
	if(front==-1)return;
	int i=0;
	for(i;i<=(rear+1)%s;i++)
	{
		printf("%d ",q[i]);
	}
}

void BreadthFP(struct Node* root)
{
	if(root==NULL)return;
	else enqueue(root);
	while(isEmpty()!=1)
	{
		struct Node* current=Front();
		printf("%d ",current->data);
		if(current->left!=NULL)enqueue(current->left);
		if(current->right!=NULL)enqueue(current->right);
		Dequeue();
	}
}

struct node{
	struct Node* data;
	struct node* next;
};
struct node* top;

void push(struct Node* x)
{
	struct node* temp=(struct node* )malloc(sizeof(struct node));
	temp->data=x;
	temp->next=top;
	top=temp;
}
void pop()
{
	if(isstackempty())return;
	struct node* temp=top;
	if(temp==NULL)return;
	else {
		top=temp->next;
		free(temp);
	}
}
int isstackempty()
{
	if(top==NULL)return 1;
	return 0;
}
struct Node* Top()
{
	struct node* temp=top;
	return(temp->data);
}
void DepthFP(struct Node* root)//There is some serious problem look at here
{
	if(root==NULL)return;
	push(root);
	while(isstackempty()!=1)
	{
		struct Node* current=Top();
		printf("%d ",current->data);pop();///what is the problem I don't know
		if(current->left!=NULL){push(current->left);}
		if(current->right!=NULL){push(current->right);}
		//pop();if I use it here then it's goes on infinitely
	
	}
}



int main()
{
	struct Node* root=NULL;
	root=Bst(8,root);
	root=Bst(4,root);root=Bst(5,root);root=Bst(7,root);root=Bst(15,root);root=Bst(10,root);	
	Print(root);
	printf("\n%d \n",FindMin(root)->data );
	Delete(root,4);
	Print(root);
	printf("\n%d\n",FindMin(root)->data);
	
	BreadthFP(root);
	printf("\n");
	DepthFP(root);
	return 0;
	
}
