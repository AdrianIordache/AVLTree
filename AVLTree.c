#include <stdio.h>
#include <stdlib.h>

typedef struct AvlNode{

	int key, height;
	struct AvlNode* left, *right;

}AvlNode, Avl, Node, node;

int max(int a, int b)
{
	if (a > b) 
	 return a ;
	 else return b ;

}

int height(Node* root)
{
	if(root == NULL)
		return 0 ;
	return root -> height;

}

node* createNode(int x)
{
	node* temp = (node*)malloc(sizeof(node));
	temp -> key = x;
	temp -> left = NULL;
	temp -> right = NULL;
	temp -> height = 1;

	return temp;
}

int getBalanced(node* root)
{
	if(root == NULL)
		return 0;
	return height(root -> left) - height(root -> right);
}
node* rightRotate(node* root)
{
	node* newRoot = root -> left;
	root -> left = newRoot -> right;
	newRoot -> right = root;
	root->height = max(height(root->left), height(root->right))+1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right))+1;

	return newRoot;
}

node* leftRotate(node* root)
{
	node* newRoot = root -> right;
	root -> right = newRoot -> left;
	newRoot -> left = root;
	root->height = max(height(root->left), height(root->right))+1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right))+1;

	return newRoot;
}


/*Node* rightRotate(Node *root)
{
    Node *newRoot = root->left;
    Node *temp = newRoot -> right;
 
    
    newRoot->right = root;
    root -> left = temp;
 
    root->height = max(height(root->left), height(root->right))+1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right))+1;
 
    
    return newRoot;
}
 
Node* leftRotate(Node *root)
{
   Node *newRoot = root->right;
   Node *temp = newRoot->left;
 
    newRoot -> left = root;
    root -> right = temp;
 
    root->height = max(height(root->left), height(root->right))+1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right))+1;
 
    return newRoot;
}*/

Node* Insert(Node* root, int x)
{
	if(root == NULL)
	{
		root = createNode(x);
	}
	else if( x == root -> key)
	{
		printf("Elementul a mai fost odata adaugat\n");
		return root;
	}
	else if( x < root -> key)
	{
		root -> left = Insert(root -> left, x);
	}
	else if( x > root -> key)
	{
		root -> right = Insert(root -> right, x);
	}
	
	root -> height = 1 + max(height(root->left),height(root->right));

	int balance = getBalanced(root);

	if(balance < -1 && x > root -> right -> key)
		return leftRotate(root);
	if(balance > 1 	&& x < root -> left -> key)
		return rightRotate(root);
	if(balance < -1 && x < root -> right -> key)
	{
		root -> right = rightRotate(root -> right);
		return leftRotate(root);
	}
	if(balance > 1 && x > root -> left -> key)
	{
		root -> left = leftRotate(root -> left);
		return rightRotate(root);
	}

	return root;

}

bool Search(Node* root, int x)
{
	if(root == NULL) return false;
		else
			if(root -> key == x) return true;
				else
					if(x <= root -> key) return Search(root -> left, x);
						else
							return Search(root -> right, x);

}

int FindMax(Node* root)
{
	if(root -> right == NULL)
		return root -> key;
	else FindMax(root -> right);
}

Node* Delete(Node* root, int x)
{
	if(root == NULL) return root;
	else
		if(x > root -> key) root -> right = Delete(root -> right, x);
			else
				if(x < root -> key) root -> left = Delete(root -> left, x);
					else
					{

						if(root -> left == NULL && root -> right == NULL)
						{
							free(root);
							root = NULL;
						}
						else if(root -> left == NULL)
						{
							Node *temp = root;
							root = root -> right;
							free(temp);
						}
						else if(root -> right == NULL)
						{
							Node *temp = root;
							root = root -> left;
							free(temp);
						}
						else
						{
							Node *temp = (Node*)malloc(sizeof(Node));
							temp = createNode(FindMax(root -> left));
							root -> key = temp -> key;
							root -> left = Delete(root -> left, temp -> key);
						}
					}

	if(root == NULL) return root;

    root -> height = 1 + max(height(root->left),height(root->right));

	int balance = getBalanced(root);

	if (balance > 1 && getBalanced(root->left) >= 0)
        return rightRotate(root);
 
    if (balance > 1 && getBalanced(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalanced(root->right) <= 0)
        return leftRotate(root);
 
    if (balance < -1 && getBalanced(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

	return root;
}

void AfisareChildren(Node* root)
{
	if(root != NULL)
	{
		printf("\n");
		printf("Nodul parinte este: %d \n", root -> key);
		if(root -> left != NULL)
		printf("Fiul stang al nodului este: %d\n", root -> left -> key);
		else
		printf("Nodul nu are fiu stang \n");

		if(root -> right != NULL)
		printf("Fiul drept al nodului este: %d\n", root -> right -> key);
		else
		printf("Nodul nu are fiu drept \n");
		
		AfisareChildren(root -> left);
		AfisareChildren(root -> right);
	}
}

void AfisarePreOrder(Node* root)
{
	if(root != NULL)
	{
		printf("Nodul %d ", root -> key);
		if(root -> left != NULL) AfisarePreOrder(root -> left);
		if(root -> right != NULL) AfisarePreOrder(root -> right);
	}
	else
		printf("Arborele este gol acum \n");
}
void AfisareInOrder(Node* root)
{
	if(root != NULL)
	{
		if(root -> left != NULL) AfisareInOrder(root -> left);
		printf("Nodul %d ", root -> key);
		if(root -> right != NULL) AfisareInOrder(root -> right);
	}
	else
		printf("Arborele este gol acum \n");
}
void AfisarePostOrder(Node* root)
{
	if(root != NULL)
	{
		if(root -> left != NULL) AfisarePostOrder(root -> left);
		if(root -> right != NULL) AfisarePostOrder(root -> right);
		printf("Nodul %d ", root -> key);
	}
	else
		printf("Arborele este gol acum \n");
}


void AfisareGenerala(Node* root)
{
	printf("\n");
	printf("Afisarea nodurilor dupa relatia Parinte - Fiu\n");
	AfisareChildren(root);

	printf("\n");
	printf("Afisarea nodurilor in ''Inorder''\n");
	AfisareInOrder(root);
	printf("\n");

	printf("\n");
	printf("Afisarea nodurilor in ''Preorder''\n");
	AfisarePreOrder(root);
	printf("\n");

	printf("\n");
	printf("Afisarea nodurilor in ''Postorder''\n");
	AfisarePostOrder(root);
	printf("\n");
}

int main()
{
	int n, index, key, x, sters,max;
	Node* root = NULL;
	FILE *fisier;
	fisier = fopen("AVLTree.in", "r");
	fscanf(fisier, "%d", &n);
	printf("Numarul de noduri ale arborelui este: %d \n", n);
	for(index = 0; index < n; index++)
	{
		fscanf(fisier, "%d", &key);
		printf("Nodul %d are cheia de cautare: %d \n", index+1, key);
				root = Insert(root, key);
			
	}

	
	AfisareChildren(root);
	printf("\n");


	printf("\n");
	fscanf(fisier,"%d", &x);
	printf("Intorduceti cheia ce urmeaza a fi cautata: %d \n", x);
	if(Search(root, x) == true) printf("Elementul cu cheia %d a fost gasit\n", x);
					else printf("Elementul cu cheia %d nu a fost gasit\n", x);

	printf("\n");
	max = FindMax(root);
	printf("Maximul din arbore este: %d", max);
	printf("\n");

	printf("\n");
	fscanf(fisier, "%d", &sters);
	printf("Introduceti elementul ce doriti sa fie eliminat din arbore: %d\n", sters);
	if(Search(root, sters) == false) printf("Acest nod nu se afla in arbore\nAfisarea Arborelui initial: \n");
					else	root = Delete(root, sters);

	AfisareChildren(root);

	fclose(fisier);
	
}

