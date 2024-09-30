#include <iostream>

//Intializing global variables
int nums[] = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};
int count = 0;
int result = 0;

//Making node struct with data and two pointers to the next two nodes
struct Node {
	int data;
	Node* rightNode;
	Node* leftNode;
};

//Function to make new Node with NULL left and right nodes
Node* newNode(int data) {
	Node* node = new Node(); //MAking new node object
	node->data = data;  //Assigning the data
	node->leftNode = NULL; //Making left and right nodes NULL
	node->rightNode = NULL;
	return node;
}

//Function to print out tree in infix order
void inFixPrintTree(Node *root) {
	if (root == NULL) {
		std::cout << " "; //Printing a space if node is NULL
	}
	else {
		inFixPrintTree(root->leftNode);
		std::cout << " ";
		std::cout << root->data;
		std::cout << " ";
		inFixPrintTree(root->rightNode);
	}
}

//Function that fills a tree with the contents of an array and balances it
Node* fillTree(int start, int end) {
	if(start > end) {   //Base case to end recurssion
		return NULL;
	}
	int mid = (start + end)/2; //Using mid index as the root of the array 
	Node* root = newNode(nums[mid]);
	root->leftNode = fillTree(start, mid-1); //calling the function on left subtree and setting new start and end to represent the subarray
	root->rightNode = fillTree(mid+1, end); //Calling function on right subtree and setting new start and end to represent the subarray
	return root;
}

//Function that finds Kth smallest element in a tree
int kThSmallest(Node* root, int k) {
	if (root == NULL) {   //Returning -1 if no node can be found
		return -1;
	}
	int leftResult = kThSmallest(root->leftNode, k);  //Calling function on left subtree
	if (leftResult != -1) {   
		return leftResult;
	}
	count++;   //Incrementing counter
	if (count == k) {   //Checking if count equals k
		result = root->data;
		return result; //returning th kth smallest element
	}
	int rightResult = kThSmallest(root->rightNode, k);  //Checking right subtree
	return rightResult;
}

//Deleting tree elements to avoid memory leak
void deleteTree(Node* root){
   if (root == NULL) {
        return;
    }
    deleteTree(root->leftNode);
    deleteTree(root->rightNode);

    delete root;
}

int main()
{

	Node* root = NULL;
	root = fillTree(0, sizeof(nums)/sizeof(nums[0]) - 1);
	inFixPrintTree(root);
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	int k;
	std::cout << "Please enter a K to find K smallest number in BST:";  //Getting input
	std::cin >> k;
	
	std::cout << std::endl;
	result = kThSmallest(root, k);
	
	if(result == -1) {
		std::cout << k << " is out of bounds of the tree.";
	} else {
		std::cout << result;
	}
	
	std::cout << std::endl;
	deleteTree(root);

	return 0;
}