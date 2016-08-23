//Anter Aaron M. Custodio
//Machine Problem: Red Black Trees
//UP - Manila Cs 21

#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

using namespace std;
struct tree
{
    int key;
    int color;//0 if black, 1 if red.
    tree* left;
    tree* right;
    tree* parent;
    tree* root;
};

tree* minimum(tree* x) // tree minimum. to be used in getting tree successor
{
    while(x->left!=NULL)
    {
        x=x->left;
    }
 return x;
}

tree* successor(tree*x)
{
tree* y = new tree;

if(x->right!=NULL)
{
    return minimum(x->right);
}

y=x->parent;
while(y!=NULL&&x==y->right)
{
    x=y;
    y=y->parent;
}
return y;
}
void leftrotate(tree* T, tree* x)
{
tree* y = new tree;
y = x->right;
x->right = y->left;

if(y->left!=NULL)
{
    y->left->parent = x;
}
y->parent = x->parent;

if(x->parent ==NULL)
{
    T->root = y;
}
else
{
    if(x==x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
}
y->left = x;
x->parent = y;

}

void rightrotate(tree* T, tree* x)
{
tree* y = new tree;
y = x->left;
x->left = y->right;

if(y->right!=NULL)
{
    y->right->parent = x;
}
y->parent = x->parent;

if(x->parent ==NULL)
{
    T->root = y;
}
else
{
    if(x==x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
}
y->right = x;
x->parent = y;
}

void delFixup(tree* T, tree*x)
{
 tree* w = new tree;

while(x!=T->root&&x->color==0)
{
    if(x=x->parent->left)
    {
        w=x->parent->right;
        if(w->color==1)
        {
            w->color=0;
            x->parent->color=1;
            leftrotate(T,x->parent);
            w=x->parent->right;
        }
        if(w->color==0&&w->right->color==0)
        {
            w->color==1;
            x->parent=x;
        }
        else
        {
            if(w->right->color==0)
            {
                w->left->color=0;
                w->color=1;
                rightrotate(T,w);
                w=x->parent->right;
            }
            w->color=x->parent->color;
            x->parent->color=0;
            w->right->color=0;
            leftrotate(T,x->parent);
            x=T->root;
        }
}
else
{

if(x=x->parent->right)
    {
        w=x->parent->left;
        if(w->color==1)
        {
            w->color=0;
            x->parent->color=1;
            rightrotate(T,x->parent);
            w=x->parent->left;
        }
        if(w->color==0&&w->left->color==0)
        {
            w->color==1;
            x->parent=x;
        }
        else
        {
            if(w->left->color==0)
            {
                w->right->color=0;
                w->color=1;
                leftrotate(T,w);
                w=x->parent->left;
            }
            w->color=x->parent->color;
            x->parent->color=0;
            w->left->color=0;
            rightrotate(T,x->parent);
            x=T->root;
        }
}

}
x->color=0;
}


}


tree* del(tree* T, tree* z)
{
tree* y = new tree;
tree* x = new tree;
tree* s = new tree;
s=T->root;
while(s)
{

    if(s->key==z->key)
    {
        z=s;
        break;
    }
    if(z->key>s->key)
    {
        s=s->right;
    }
    else
    {
        s=s->left;
    }

}
if(s==NULL)
{
    cout<<"\nNo nodes matched the inputted number!\n";
    return T;
}

if(z->left==NULL||z->right==NULL)
{
    y=z;
}
else
{
    y=successor(z);
    if(y==NULL)
    cout<<"jehaha";
}

if(y->left!=NULL)
{
    x=y->left;
}
else
{
    x=y->right;
}
if(x!=NULL)
{
    x->parent=y->parent;
}

if(y->parent==NULL)
{
    T->root=x;
}
else
{
    if(y==y->parent->left)
    {
        y->parent->left=x;
    }
    else
    {
        y->parent->right=x;
    }

}

if(y!=z)
{
    z->key=y->key;
}
if(y->color==0)
{

delFixup(T,x);

}
system("CLS");
cout<<"Node Successfully deleted!\n";
return y;
}

int height(tree* node) /* Compute the "height" of a tree -- the number ofnodes along the longest path from the root node down to the farthest leaf node.*/
{
    if(node==NULL)
    {
        return 0;
    }
    else
    {
        int lheight= height(node->left); //computes the height of each subtree
        int rheight= height(node->right);

        if(lheight>rheight) //use the large one
            return(lheight+1);
        else return (rheight+1);
    }
}


void printGivenLevel(tree* root, int level) //prints  nodes at a given level
{
    int i;
    if(root==NULL)
    {
        cout<<"  ";
        return;
    }
    if(level==1)
    {
    HANDLE  hColor;
    hColor = GetStdHandle (STD_OUTPUT_HANDLE);
    if(root->color==1)
    {
    SetConsoleTextAttribute(hColor, 28);
    }
    else
    {
    SetConsoleTextAttribute(hColor, 16);
    }
        cout<<"("<<root->key<<")";
    }
    else if(level>1)
    {

        printGivenLevel(root->left,level-1);
        for(i=level;i>0;i--)
        cout<<"   ";
        for(i=level;i>0;i--)
        cout<<"\b\b\b";
        printGivenLevel(root->right,level-1);


    }

}

void display(tree* T) //function to print level order traversal
{

int z;
tree* root = new tree;
root = T;
int h = height(root);
int i,n;
while(z!=0)
{

for(i=1;i<=h;i++)
{
    for(n=h-i;n>0;n--)
    {
        cout<<"  ";
    }
    printGivenLevel(root,i);
    cout<<"\n\n";
}

cout<<"Input 0 to continue:  ";
cin>>z;
if(cin.fail())
{
    cin.clear();
    cin.ignore();
cout<<"Invalid input!\n"<<endl;
}
system("CLS");

}

}




void InOrder(tree* T)
{
 if (!T ) return;
  InOrder(T->left);
  cout<<T->key<<",";
  InOrder(T->right);
}



void fixup(tree* T, tree* z)
{
tree* y = new tree;
y=NULL;


while(z->parent!=NULL&&z->parent->color==1)
{
    if(z->parent==z->parent->parent->left)
    {
        y=z->parent->parent->right;
        if(y!=NULL&&y->color==1)
        {
            z->parent->color = 0;
            y->color = 0;
            z->parent->parent->color = 1;
            z=z->parent->parent;
        }
        else
        {
            if(z==z->parent->right)
            {
                z=z->parent;
                leftrotate(T,z);
            }
            z->parent->color = 0;
            z->parent->parent->color = 1;
            rightrotate(T,z->parent->parent);
        }
    }
    else
    {
         y=z->parent->parent->left;

        if(y!=NULL&&y->color==1)
        {
            z->parent->color = 0;
            y->color = 0;
            z->parent->parent->color = 1;
            z=z->parent->parent;
        }
        else
        {
            if(z==z->parent->left)
            {
                z=z->parent;
                rightrotate(T,z);
            }
            z->parent->color = 0;
            z->parent->parent->color = 1;
                leftrotate(T,z->parent->parent);
        }
    }
}

T->root->color = 0;
}

void insert(tree* T, tree* z)
{
tree* y = new tree;
y= NULL;
tree* x = new tree;
x=NULL;
x = T->root;

while(x)
{

if(z->key==x->key) //to avoid duplicate numbers in the tree
{
    cout<<"\nNumber already in tree!\n";
    return;
}
    y=x;
    if(z->key<x->key)
    {
        x=x->left;
    }
    else
    {
        x=x->right;
    }
}

z->parent = y;

if(y==NULL)
{
    T->root = z;
}
else
{
    if(z->key<y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
}

z->left = NULL;
z->right = NULL;
z->color = 1;
fixup(T,z);
system("CLS");
cout<<"Integer Successfully inserted!\n";
}

void initialize(tree* T, tree* z) //set all to null
{
    T->left=NULL;
    T->right=NULL;
    T->parent=NULL;
    T->root=NULL;
    z->left=NULL;
    z->right=NULL;
    z->parent=NULL;
    z->root=NULL;
    T->color = 0;
    z->color = 0;
}

int main()
{
int choice;
tree* T = new tree;
tree* z = new tree;

initialize(T,z); //set all to null


while(choice!=5)
{
system("color 17");
cout<<"--------------------------------------------------";
cout<<"\n                    M E N U                        \n";
cout<<"--------------------------------------------------\n";
cout<<"Choose which operation to perform:\n\n";
cout<<"[1]. Insert\n[2]. Delete \n[3]. InOrder Traversal\n[4]. Display\n[5]. Exit";
cout<<"\n\nYour Choice: ";
cin>>choice;
system("CLS");
if(cin.fail())
{
    cin.clear();
    cin.ignore();
cout<<"Invalid input! Choose only from 1 - 5. Thank you.\n"<<endl; //to avoid invalid input
}
tree* z = new tree;
switch(choice)
{
    case 1:
            cout<< "\nPlease Enter the integer you want to insert...\n"<<endl;
            cin>>z->key;
            if(cin.fail())
            {
            cin.clear();
            cin.ignore();
            cout<<"Invalid input! Insert an integer!\n"<<endl; //to avoid invalid input
            }
            insert(T,z);
            break;
    case 2:
      if(T->root==NULL)
            {
                cout<<"The Tree is empty!\n\n";
                break;
            }
      else
            {
            cout<< "\nPlease Enter the integer you want to delete...\n"<<endl;
            cin>>z->key;
            del(T,z);
            break;
            }
    case 3:
            if(T->root==NULL)
            {
                cout<<"The Tree is empty!\n\n";
                break;
            }
            else
            {
            cout<<"InOrder Tree Traversal:\n\n\n";
            InOrder(T->root);
            cout<<"\n\n\n";
            break;
            }
    case 4:
            display(T->root);
            system("CLS");
            break;
    case 5:
    cout<<"\n\n#############################################################"<<endl;
	cout<<"#                    _                 THANK YOU            #"<<endl;
	cout<<"#                  -=\\`\\                  FOR USING         #"<<endl;
	cout<<"#              |\\ ____\\_\\__                 THE PROGRAM     #"<<endl;
	cout<<"#            -=\\c`\"\"\"\"\"\"\" \"`)                               #"<<endl;
	cout<<"#               `~~~~~/ /~~`\                                #"<<endl;
	cout<<"#                 -==/ /                                    #"<<endl;
	cout<<"#                   '-'                  HAVE A NICE DAY!   #"<<endl;
	cout<<"#                  _  _                                     #"<<endl;
	cout<<"#                 ( `   )_                                  #"<<endl;
	cout<<"#                (    )    `)                               #"<<endl;
	cout<<"#              (_   (_ .  _) _)                             #"<<endl;
	cout<<"#                                             _             #"<<endl;
	cout<<"#                                            (  )           #"<<endl;
	cout<<"#             _ .                         ( `  ) . )        #"<<endl;
	cout<<"#           (  _ )_                      (_, _(  ,_)_)      #"<<endl;
	cout<<"#         (_  _(_ ,)                                        #"<<endl;
	cout<<"#############################################################\n"<<endl;
    break;
    default:
    cout<<"There's no such choice in the menu!\nInput Again!\n\n";
}

}
} //end of main
