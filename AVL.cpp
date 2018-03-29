/*
AVL Tree implementation in C++:
** To compile : g++ -std=c++11 <filename.cpp> -o <outputname>
** To run     : ./<outputname>

** Functions defined:
1- LL Rotation
2- RR Rotation
3- Create Node
4- Find parent node
5- Find Node pointer of value 
6- Insertion
7- Deletion
8- Search a value
9- Calculate Height of the node
10-Pre order traversal
11-In order traversal
12-Post order traversal
13-check balance factor
14-max of two values
15-update height of all nodes

*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<vector>

using namespace std;

//Declare a node structure
struct Node
{
  int value;
  struct Node * left;
  struct Node * right;
  int height;
};

//Root pointer 
struct Node * root_ptr=NULL;

//List to read nodes from the .txt file
std::vector<string> node_list_fp;

//Create node by passing value of the node
struct Node * create_node(int value)
{
  //Allocate memory dynamically for the new node of size (struct Node)
  struct Node * ptr= (struct Node *)malloc(sizeof(struct Node));
  // Assign value to node value 
  ptr->value=value;
  // Assign left child of node to NULL
  ptr->left=NULL;
  // Assign right child of node to NULL
  ptr->right=NULL;
  // Assign height of the node to 0
  ptr->height=0;
  return ptr;
}

//Search for a value
int search_node(int value)
{
  //Initially result 0 : means value not found
  int res=0;
  //Initialize a node pointer to the root pointer of the tree
  struct Node * rp=root_ptr;
  //If root pointer is NULL means no root, means no tree, return 0
  if(rp==NULL)return res;
  while(rp!=NULL)
    {
      //if value == rp->value, return true, value found
      if(rp->value==value)
	{
	  res=1;
	  break;
	}
      //if value< rp->value, move to left subtree and search
      if(rp->value>value)
	rp=rp->left;
      else
	//else move to right subtree and search
	rp=rp->right;
    }
  //return res
  return res;
}

//LL Rotation
struct Node * ll_rotation(struct Node * y)
{
  // y- node with the balancing factor problem
  // assign x to left child of y
  struct Node * x=y->left;
  struct Node * t2=x->right;
  //Rotate
  x->right=y;
  y->left=t2;
  //Return root of rotated subtree, which is x
  return x;
}

//RR Rotation
struct Node * rr_rotation(struct Node * y)
{
  // y- node with the balancing factor problem
  // assign x to right child of y
  struct Node *x=y->right;
  struct Node * t2=x->left;
  //Rotate
  x->left=y;
  y->right=t2;
  //Reeturn root of rotated subtree, which is x
  return x;
}

//Check balancing factor of the node
int check_b_factor(struct Node * node_ptr)
{
      // left and right subtrees are null, b-factor =0
      if((node_ptr->left==NULL) && (node_ptr->right==NULL))return 0;
      // If left subtree only is NULL, then return value of -(RST+1)
      else if((node_ptr->left==NULL) && (node_ptr->right!=NULL))return -(1+node_ptr->right->height);
      // if right subtree only is NULL, then return value of +(LST+1) 
      else  if((node_ptr->left!=NULL) && (node_ptr->right==NULL))return 1+node_ptr->left->height;
      //Else return value of (height(LST)-height(RST))
      else  if((node_ptr->left!=NULL) && (node_ptr->right!=NULL))
  return (node_ptr->left->height-node_ptr->right->height);
}

//Print tree in Inorder traversal format
void print_tree_in(struct Node * root_ptr)
{
  if(root_ptr)
    {
      //Visit LST
      print_tree_in(root_ptr->left);
      //Print value
      cout<<root_ptr->value<<" ";
      //Visit RST
      print_tree_in(root_ptr->right);
    }
}

//Print tree in Preorder traversal format
void print_tree_pre(struct Node * root_ptr)
{
  if(root_ptr)
    {
      //Print value
      cout<<root_ptr->value<<" ";
      //Visit LST
      print_tree_pre(root_ptr->left);
      //visit RST
      print_tree_pre(root_ptr->right);
    }
}

//Print tree in Postorder traversal format
void print_tree_post(struct Node * root_ptr)
{
  if(root_ptr)
    {
      //visit LST
      print_tree_post(root_ptr->left);
      //visit RST
      print_tree_post(root_ptr->right);
      //Print value
      cout<<root_ptr->value<<" ";
    }
}

//Find the parent of node pointer
struct Node * find_parent(struct Node * ptr)
{
  struct Node * rp=root_ptr, *y=NULL;
  while(rp!=ptr)
    {
      if(rp->value > ptr->value)
	{
	  y=rp;
	  rp=rp->left;
	}
      else
	{
	  y=rp;
	  rp=rp->right;
	}
    }
  return y;
}

//Find the node pointer by passing node value
struct Node * find_NodePtr(int value)
{
  struct Node *rp=root_ptr;
  while((rp->value!=value) && (rp!=NULL))
    {
      if(rp->value > value)
	rp=rp->left;
      else
	rp=rp->right;
    }
  return rp;
}

//Returns Max of two values a, b
int max(int a, int b)
{
  return (a>b)?a:b;
}

//Find the height of the node in the tree: starting from 0 of root node
int height_node(struct Node * node_ptr)
{
  if((node_ptr->left==NULL)&&(node_ptr->right==NULL))return 0;
  else if((node_ptr->left!=NULL)&&(node_ptr->right==NULL))
    return 1+height_node(node_ptr->left);
  else if((node_ptr->left==NULL)&&(node_ptr->right!=NULL))
    return 1+height_node(node_ptr->right);
  else
    return 1+max(height_node(node_ptr->left),height_node(node_ptr->right));
}

//Update height of all nodes in post order manner
void update_height_all(struct Node * ptr)
{
  if(ptr)
    {
      update_height_all(ptr->left);
      update_height_all(ptr->right);
      ptr->height=height_node(ptr);
    }
}

//Insert node by passing node pointer and return root pointer
struct Node * insert_node(struct Node *node_ptr)
{
      int key=node_ptr->value;
      struct Node * y=NULL;
      struct Node * x= root_ptr;
      while(x!=NULL)
	{
	  y=x;
	  if(node_ptr->value < x->value)
	    x=x->left;
	  else
	    x=x->right;
	}
      if (y==NULL)
	root_ptr=node_ptr;
      else if (node_ptr->value < y->value)//y acts as parent of newly inserted node
	y->left=node_ptr;
      else
	y->right=node_ptr;

      cout<<"Node inserted.\n";
      //Update heights on all the nodes in the path from newly inserted node to the root node
      struct Node * p,*temp,*p2;
      int b_f=0;
      p=find_parent(node_ptr);
      while((p!=NULL))
	{
	  //Update height
	  p->height=height_node(p);
	  // cout<<"Height of "<<p->value<<" updated as "<<p->height<<endl;
	  //Check balance factor
	  b_f=check_b_factor(p);
	  // cout<<"Balance Factor of "<<p->value<<" is "<<b_f<<endl;
	  //LL Case
	  if((b_f >1) && (p->left->value>key))
	    {
	      p2=find_parent(p);
	      if(p2)
		{
		  (p2->left==p)?p2->left=ll_rotation(p):p2->right=ll_rotation(p);
		  p=p2;
		}
	      else root_ptr=ll_rotation(p);
	      cout<<"LL Rotated"<<endl;
	      update_height_all(root_ptr);
	    }
	  else if((b_f < -1) && (p->right->value < key))
	    {
	      //RR Case
	      p2=find_parent(p);
	      if(p2)
		{
		  (p2->left==p)?p2->left=rr_rotation(p):p2->right=rr_rotation(p);
		  p=p2;
		}
	      else root_ptr=rr_rotation(p);
	      cout<<"RR Rotated"<<endl;
	      update_height_all(root_ptr);
	    }
	  else if((b_f >1) && (p->left->value < key))
	    {
	      //LR Case
	      p2=find_parent(p);
	      if(p2)
		{
		  p->left=rr_rotation(p->left);
		  p2->left=ll_rotation(p);
		  p=p2;
		}
	      else
		{
		  p->left=rr_rotation(p->left);
		  root_ptr=ll_rotation(p);
		}
	      cout<<"LR Rotated"<<endl;
	      update_height_all(root_ptr);
	    }
	  else if((b_f < -1) && (p->right->value > key))
	    {
	      //RL Case
	      p2=find_parent(p);
	      if(p2)
		{
		  p->right=ll_rotation(p->right);
		  p2->right=rr_rotation(p);
		  p=p2;
		}
	      else
		{
		  p->right=ll_rotation(p->right);
		  root_ptr=rr_rotation(p);
		}
	      cout<<"RL Rotated"<<endl;
	      update_height_all(root_ptr);
	    }
	  else
	    p=find_parent(p);
	}
      //Return root node
      
      return root_ptr;
}

//Delete the node by passing root pointer and value
struct Node * deletion(struct Node * root, int key)
{
  if(root==NULL) return root;
  else
    {
      struct Node * node_ptr= find_NodePtr(key);
      struct Node * parent=find_parent(node_ptr);
      if(((node_ptr->left!=NULL) && (node_ptr->right!=NULL)))
       {
	 struct Node *p=NULL,*y=NULL;
	 y=node_ptr->left;
	 p=node_ptr;
	 while(y->right!=NULL)
	   {
	     p=y;
	     y=y->right;
	   }
	 node_ptr->value=y->value;
	 node_ptr=y;
	 parent=p;
       }
      if((node_ptr->left==NULL) && (node_ptr->right==NULL))
	{
	  if(parent==NULL)return NULL;
	  if(parent->left==node_ptr)parent->left=NULL;
	  else
	    parent->right=NULL;
	}
      if(((node_ptr->left!=NULL) && (node_ptr->right==NULL)))
	{
	  if(parent==NULL)
	      root= node_ptr->left;
	  if(parent->left==node_ptr)
	    parent->left=node_ptr->left;
	  else
	    parent->right=node_ptr->left;
	}
      if(((node_ptr->left==NULL) && (node_ptr->right!=NULL)))
	{
	  if(parent==NULL)
	      root= node_ptr->right;
	  if(parent->left==node_ptr)
	    parent->left=node_ptr->right;
	  else
	    parent->right=node_ptr->right;
	}
       //Update heights on all the nodes in the path from newly deleted node to the root node
      struct Node * pp=parent,*p2;
      cout<<"Next parent "<<pp->value<<endl;
      int b_f=0;
      while(pp!=NULL)
	{
	  pp->height=height_node(pp);
	  //cout<<"Height of "<<pp->value<<" updated as "<<pp->height<<endl;
	  //Check balance factor
	  b_f=check_b_factor(pp);
	  //cout<<"Balance Factor of "<<pp->value<<" is "<<b_f<<endl;
	  //LL Case
	  if((b_f >1) && (check_b_factor(pp->left)>=0))
	    {
	      p2=find_parent(pp);
	      if(p2)
		{
		  (p2->left==pp)?p2->left=ll_rotation(pp):p2->right=ll_rotation(pp);
		  pp=p2;
		}
	      else root=ll_rotation(pp);
	      cout<<"LL Rotated"<<endl;
	      update_height_all(root);
	    }
	  
	  else if((b_f < -1) && (check_b_factor(pp->right)<=0))
	    {
	      //RR Case
	      p2=find_parent(pp);
	      if(p2)
		{
		  (p2->left==pp)?p2->left=rr_rotation(pp):p2->right=rr_rotation(pp);
		  pp=p2;
		}
	      else root=rr_rotation(pp);
	      cout<<"RR Rotated"<<endl;
	      update_height_all(root);
	    }
	  
	  else if((b_f > 1) && (check_b_factor(pp->left)<=0))
	    {
	      //LR Case
	      p2=find_parent(pp);
	      if(p2)
		{
		  pp->left=rr_rotation(pp->left);
		  p2->left=ll_rotation(pp);
		  pp=p2;
		}
	      else
		{
		  pp->left=rr_rotation(pp->left);
		  root=ll_rotation(pp);
		}
	      cout<<"LR Rotated"<<endl;
	      update_height_all(root);
	    }
 
	  else if((b_f < -1) && (check_b_factor(pp->right)>=0))
	    {
	      //RL Case
	      p2=find_parent(pp);
	      if(p2)
		{
		  pp->right=ll_rotation(pp->right);
		  p2->right=rr_rotation(pp);
		  pp=p2;
		}
	      else
		{
		  pp->right=ll_rotation(pp->right);
		  root=rr_rotation(pp);
		}
	      cout<<"RL Rotated"<<endl;
	      update_height_all(root);
	    }
	 
	  else
	    pp=find_parent(pp);
	} 
    }
  return root;
}

//Main function
int main(int argc, char *argv[])
{
  struct Node * node_ptr;
  cout<<"Choose one of the options below\n1-Enter a node\n2-Delete a node\n3-Print the tree in L D R format\n4-Height of the node\n5-Search a node\n6-Quit\n";
  int option;
  cin>>option;
  int val;
  while(option!=6)
    {
      switch(option)
	{
	   case 1: //Insertion
	     cout<<"Enter the value to be insert\n";
	     cin>>val;
	     node_ptr=create_node(val);
	     root_ptr=insert_node(node_ptr);
	     break;
	   case 2: //Delete
	     cout<<"Enter the value to be deleted\n";
	     cin>>val;
	     root_ptr=deletion(root_ptr,val);
	     break;
	   case 3: //print
	     cout<<"\nPre order: ";
	     print_tree_pre(root_ptr);
	     cout<<"\nIn order: ";
	     print_tree_in(root_ptr);
	     cout<<"\nPost order: ";
	     print_tree_post(root_ptr);
	     break;
	   case 4: //height of the node
	     cout<<"Enter the value whose height is to be calculated\n";
	     cin>>val;
	     node_ptr=find_NodePtr(val);
	     cout<<"\nHeight of the node is "<<height_node(node_ptr);
	     break;
	   case 5: //search
	     cout<<"\nEnter a vlaue to search"<<endl;
	     cin>>val;
	     (search_node(val)==1)?cout<<"\nValue present in tree\n":cout<<"\nValue not present in the tree\n"<<endl;
	     break;
	   case 6: //Quit
	     break;
	}
      cout<<"\nEnter an option again\n";
      cin>>option;
    }
  return 0;
}

