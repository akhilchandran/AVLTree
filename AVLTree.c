#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	int balancefactor;
	struct node *left;
	struct node *right;
};

int mode(int value)
{
	if(value < 0)
		value *= -1;
	return value;
}
void balancePluseTwo(struct node **avltreeref);
void balanceMinusTwo(struct node **avltreeref);
void minusOnetoPlusOne(struct node **avltreeref);
void plusOnetoMinusOne(struct node **avltreeref);

int insert(struct node **avltreeref, struct node *newnode)
{
	if(*avltreeref == NULL){
		*avltreeref = newnode;
		return 1;
	}
	int hightdiff; 
	if((*avltreeref)->data >= newnode->data){			/*inert left*/
		hightdiff = insert(&(*avltreeref)->left, newnode);
		(*avltreeref)->balancefactor += hightdiff;
		if((*avltreeref)->balancefactor > 1){
			balancePluseTwo(avltreeref);
		}
		return mode((*avltreeref)->balancefactor);
	}else{							/*insert right*/
		hightdiff = insert(&(*avltreeref)->right, newnode);
		(*avltreeref)->balancefactor -= hightdiff;
		if((*avltreeref)->balancefactor < -1){
			balanceMinusTwo(avltreeref);
		}
		return mode((*avltreeref)->balancefactor);
	}
}

void balancePluseTwo(struct node **avltreeref)
{
	struct node *leftnode = (*avltreeref)->left;
	if(leftnode->balancefactor == -1){
		minusOnetoPlusOne(&(*avltreeref)->left);
	}
	leftnode->balancefactor -= 1;
	(*avltreeref)->balancefactor = 0;
	(*avltreeref)->left = leftnode->right;
	leftnode->right = *avltreeref;
	*avltreeref = leftnode;
}

void balanceMinusTwo(struct node **avltreeref)
{
	struct node *rightnode = (*avltreeref)->right;
	if(rightnode->balancefactor == 1){
		plusOnetoMinusOne(&(*avltreeref)->right);
	}
	rightnode->balancefactor += 1;
	(*avltreeref)->balancefactor = 0;
	(*avltreeref)->right = rightnode->left;
	rightnode->left = *avltreeref;
	*avltreeref = rightnode;
}

void minusOnetoPlusOne(struct node **avltreeref)
{

	struct node *rightnode = (*avltreeref)->right;
	//currect lening
	if(rightnode->balancefactor == 0){
		(*avltreeref)->balancefactor = 0;
		rightnode->balancefactor = 1;
	}
	else if(rightnode->balancefactor == 1){
		plusOnetoMinusOne(&rightnode);
	}
	else if(rightnode->balancefactor == -1){
		(*avltreeref)->balancefactor = 1;
		rightnode->balancefactor = 1;
	}
	(*avltreeref)->right = rightnode->left;
	rightnode->left = *avltreeref;
	*avltreeref = rightnode;
	return;
}	
		
void plusOnetoMinusOne(struct node **avltreeref)
{
	struct node *leftnode = (*avltreeref)->left;
	if(leftnode->balancefactor == 0){
		(*avltreeref)->balancefactor = 0;
		leftnode->balancefactor = -1;
	}
	else if(leftnode->balancefactor == -1){
		minusOnetoPlusOne(&leftnode);
	}
	else if(leftnode->balancefactor == -1){
		(*avltreeref)->balancefactor = -1;
		leftnode->balancefactor = -1;
	}
	(*avltreeref)->left = leftnode->right;
	leftnode->right = *avltreeref;
	*avltreeref = leftnode;
	return;
}
struct node *newnode(int data)
{
	struct node *nod = malloc(sizeof(struct node));
	nod->data = data;
	nod->balancefactor = 0;
	nod->left = NULL;
	nod->right = NULL;
}

void printTreeStrct(struct node *tree)
{
	if(tree != NULL){
		printf("{");
		printTreeStrct(tree->left);
		printf("(%d)",tree->data);
		printTreeStrct(tree->right);
		printf("}");
	}
	
}
int main()
{
	struct node *avl = NULL;
	struct node *nod = newnode(64);
	insert(&avl, nod);
	nod = newnode(80);
	insert(&avl, nod);
	nod = newnode(96);
	insert(&avl, nod);
	nod = newnode(100);
	insert(&avl, nod);
	nod = newnode(51);
	insert(&avl, nod);
	nod = newnode(10);
	insert(&avl, nod);
	nod = newnode(150);
	insert(&avl, nod);
	nod = newnode(70);
	insert(&avl, nod);
	nod = newnode(15);
	insert(&avl, nod);
	nod = newnode(9);
	insert(&avl, nod);
	printTreeStrct(avl);
	printf("\n");
}