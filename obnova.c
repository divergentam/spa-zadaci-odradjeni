#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* left, * right;
}Node;


Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}


Node* addInUnordered(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (rand() % 2)
		root->left = addInUnordered(root->left, value);
	else
		root->right = addInUnordered(root->right, value);
	return root;
}

Node* addInOrdered(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (root->value > value) {
		root->left = addInOrdered(root->left, value);
	}
	else if (root->value < value) {
		root->right = addInOrdered(root->right, value);
	}
	else if (rand() % 2)
		root->left = addInOrdered(root->left, value);
	return root;
}

Node* deleteInUnordered(Node* root, int value) {
	// base case when we don't have root 
	if (!root)
		return NULL;

	// base case when root->value is a same as value that we pass
	if (root->value == value) {
		// when we find value that we need to remove from tree we need to see if that concrete node has left or right node
		//if we have left we will update root->value on root->left->value and then we need to remove that value from the rest of subtree
		//if that root->left returns null that means that node is leaf and we will set root->left to null
		if (root->left) {
			root->value = root->left->value;
			root->left = deleteInUnordered(root->left, root->value);
		}
		//we do the sam when we dont't have left but we have right
		else if (root->right) {
			root->value = root->right->value;
			root->right = deleteInUnordered(root->right, root->value);
		}
		//if we dont have right and left that means that our value is in leaf and all we have to do is to delete leaf;
		else {
			free(root);
			return NULL;
		}
	}
	//what will hapen if root->vale != value
	//we need to search left subtree and right
	root->left = deleteInUnordered(root->left, value);
	root->right = deleteInUnordered(root->right, value);
	
	return root;
}

int minimal(Node* root) {
	return root->left ? minimal(root->left) : root->value;
}
int maximal(Node* root) {
	return root->right ? maximal(root->right) : root->value;
}

Node* deleteInOrdered(Node* root, int value) {
	if (!root)
		return NULL;
	if (root->value > value) {
		root->left = deleteInOrdered(root->left, value);
	}
	else if (root->value < value)
		root->right = deleteInOrdered(root->right, value);
	// now we find root with value
	else if(root->left) {
		int maxi =  maximal(root->left);
		root->value = maxi;
		root->left = deleteInOrdered(root->left, root->value);
	}
	else if (root->right) {
		int mini = minimal(root->right);
		root->value = mini;
		root->right = deleteInOrdered(root->right, root->value);
	}
	else {
		free(root);
		return NULL;
	}
	return root;
}

#define SPACE 5

void print2D(Node* root, int space) {
	if (!root)
		return;
	space += SPACE;
	print2D(root->right, space);
	printf("\n");
	for (int i = SPACE; i < space; i++)
		printf(" ");
	printf("%d ", root->value);
	print2D(root->left, space);
}

#define X 15

int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

Node* generate10Unordered(Node* root) {
	while (size(root) != 10) {
		root = addInUnordered(root, rand() % X);
	}
	return root;
}

Node* generate10Ordered(Node* root) {
	while (size(root) != 10) {
		root = addInOrdered(root, rand() % X);
	}
	return root;
}

int main() {
	srand(time(NULL));
	int n = rand() % X;

	Node* root = NULL;
	printf("Tree1 before deleting node %d:\n\n", n);
	root = generate10Unordered(root);
	print2D(root, 1);
	printf("\n\n\n");
	printf("Tree1 afrer deleting node %d:\n\n", n);
	root = deleteInUnordered(root, n);
	print2D(root, 1);

	printf("\n\n\n");

	int n2 = rand() % X;


	Node* root2 = NULL;
	root2 = generate10Ordered(root2);
	printf("Tree2 before deleting node %d:\n\n", n2);
	print2D(root2, 1);
	printf("\n\n\n");

	root2 = deleteInOrdered(root2, n2);
	printf("Tree2 after deleting node %d: \n\n", n2);
	print2D(root2, 1);


	printf("\n\n\n");
	return 0;
}