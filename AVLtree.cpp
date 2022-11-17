
#include <iostream>
#include<string.h>
using namespace std;

// Node AVL
class Node {
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int max(int a, int b);

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

// calculate Balance
int calcBalance(Node *node) {
    if (node == NULL)
		return 0;
    return height(node->left) - height(node->right);
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

// Perform Right rotation
Node *rightRotation(Node *y) {
    Node *x = y->left;
    Node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // return new root
}

// Perform Left rotation
Node *leftRotation(Node *x) {
    Node *y = x->right;
    Node *z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // return new root
}

Node* insert(Node* node, int key) {

    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

	// update the height
    node->height = 1 + max(height(node->left), height(node->right));

	// calc balance
    int balance = calcBalance(node);



    if (balance > 1 && key < node->left->key)
        return rightRotation(node);


    if (balance < -1 && key > node->right->key)
        return leftRotation(node);


    if (balance > 1 && key > node->left->key) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }


    if (balance < -1 && key < node->right->key) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }


    return node;
}

// search largest value smaller than the root
Node * valueNode(Node* node) {
    Node* value = node;

    while (value->right != NULL)
        value = value->right;

    return value;
}


Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if(key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            // no child
            if (temp == NULL) {
                root = NULL;
            }
            else // one child
                *root = *temp;
                free(temp);
        } else {
            Node* temp = valueNode(root->left);

            root->key = temp->key;

            root->left = deleteNode(root->left, temp->key);
        }
    }

    if (root == NULL)
    	return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = calcBalance(root);

    if (balance > 1 && calcBalance(root->left) >= 0)
        return rightRotation(root);

    if (balance > 1 && calcBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (balance < -1 && calcBalance(root->right) <= 0)
        return leftRotation(root);

    if (balance < -1 && calcBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
	}

    return root;
}

void preOrder(Node *root) {
    if (root != NULL) {
        cout << root->key << " ";
    	preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root){
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

void PostOrder(Node *root) {
    if (root != NULL) {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key << " ";
    }
}

int main(){

    Node *root = NULL;

    int i=0,j=-1;
    char a[1000];
    int temp=0;

    cin.getline(a,1000);

    for(i=0; a[i]!='\0'; i++){
		j++;

    	if(a[i]==' '){
        	if(a[i-j]=='A'){
                j--;
            	while (j>0) {
                    temp = temp * 10 + (a[i-j] - '0');
                    j--;
                 }
                 root = insert(root, temp);
            } else if (a[i-j]=='D') {
                j--;
                while (j>0) {
                	temp = temp * 10 + (a[i-j] - '0');
                    j--;
                 }
                 root = deleteNode(root, temp);
            }
	        j=-1;
	        temp=0;
        } else {
            if(a[i]=='E'){
            	preOrder(root);
            } else if (a[i]=='T') {
            	PostOrder(root);
            } else if (a[i]=='N') {
            	inOrder(root);
            }
        }
    }

	if (root == NULL) {
		cout << "EMPTY";
	}
}
