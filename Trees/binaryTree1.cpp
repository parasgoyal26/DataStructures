#include <iostream>
#include<queue>
#include<map>

using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;

	Node(int data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}


};

//it returns root node of the created tree
Node* createTree() {
	cout << "enter the dataue for Node: " << endl;
	int data;
	cin >> data;

	if (data == -1) {
		return NULL;
	}
	//Step1: create Node
	Node* root = new Node(data);
	//Step2: Create left subtree
	//cout << "left of Node: " << root->data << endl;
	root->left = createTree();
	//Step3: Craete right subtree
	//cout << "right of Node: " << root->data << endl;
	root->right = createTree();
	return root;

}

void preOrderTraversal(Node* root) {
	//base case
	if (root == NULL) {
		return;
	}
	// N L R
	//N 
	cout << root->data << " ";
	// L
	preOrderTraversal(root->left);
	// R
	preOrderTraversal(root->right);
}

void inorderTraversal(Node* root) {
	//LNR
	//base case
	if (root == NULL) {
		return;
	}
	//L
	inorderTraversal(root->left);
	// N
	cout << root->data << " ";
	// R
	inorderTraversal(root->right);
}

void postOrderTraversal(Node* root) {
	//LRN
	//base case
	if (root == NULL) {
		return;
	}
	//L
	postOrderTraversal(root->left);
	//R
	postOrderTraversal(root->right);
	//N
	cout << root->data << " ";
}

void levelOrderTraversal(Node* root) {
	queue<Node*> q;
	q.push(root);
	q.push(NULL);

	//asli traversal start krete h 

	while (!q.empty()) {
		Node* front = q.front();
		q.pop();

		if (front == NULL) {
			cout << endl;
			if (!q.empty()) {
				q.push(NULL);
			}
		}
		else {
			//dataid node wala case
			cout << front->data << " ";

			if (front->left != NULL) {
				q.push(front->left);
			}
			if (front->right != NULL) {
				q.push(front->right);
			}
		}
	}
}

int maxDepth(Node* root) {

	// IMP Galti
	if (root == NULL)
		return 0;

	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	int count = 1;

	//asli traversal start krete h 

	while (!q.empty()) {
		Node* front = q.front();
		q.pop();

		if (front == NULL) {
			cout << endl;
			if (!q.empty()) {
				count++;
				q.push(NULL);
			}
		}
		else {
			//dataid node wala case
			//cout << front->data << " ";

			if (front->left != NULL) {
				q.push(front->left);
			}
			if (front->right != NULL) {
				q.push(front->right);
			}
		}
	}
	return count;


	// //base case
	// if(root == NULL ) {
	//     return 0;
	// }

	// int leftHeight = maxDepth(root->left);
	// int rightHeight = maxDepth(root->right);
	// int height = max(leftHeight, rightHeight) + 1;
	// return height;

}

int height(Node* root) {
	//base case
	if (root == NULL) {
		return 0;
	}
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);
	int height = max(leftHeight, rightHeight) + 1;
	return height;
}

int diameterOfBinaryTree(Node* root) {
	//base case
	if (root == NULL) {
		return 0;
	}
	int option1 = diameterOfBinaryTree(root->left);
	int option2 = diameterOfBinaryTree(root->right);
	int option3 = height(root->left) + height(root->right);
	int diameter = max(option1, max(option2, option3));
	return diameter;
}

bool isBalanced(Node* root) {
	//base case
	if (root == NULL) {
		return true;
	}

	//currNode - solve
	int leftHeight = height(root->left);
	int rightHeight = height(root->right);
	int diff = abs(leftHeight - rightHeight);

	bool currNodeAns = (diff <= 1);

	bool leftAns = isBalanced(root->left);
	bool rightAns = isBalanced(root->right);

	if (currNodeAns && leftAns && rightAns) {
		return true;
	}
	else {
		return false;
	}

}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
	if (root == NULL)
		return NULL;
	if (root->data == p->data) {
		return p;
	}
	if (root->data == q->data) {
		return q;
	}

	Node* leftAns = lowestCommonAncestor(root->left, p, q);
	Node* rightAns = lowestCommonAncestor(root->right, p, q);

	if (leftAns == NULL && rightAns == NULL)
		return NULL;
	else if (leftAns != NULL && rightAns == NULL)
		return leftAns;
	else if (leftAns == NULL && rightAns != NULL)
		return rightAns;
	else
		return root;




}


bool solve(Node* root, int targetSum, int sum) {
	//base case
	if (root == NULL) {
		return false;
	}
	sum += root->data;
	if (root->left == NULL && root->right == NULL) {
		//i m currently standing on a leaf node
		//verify
		if (sum == targetSum)
			return true;
		else
			return false;
	}
	bool leftAns = solve(root->left, targetSum, sum);
	bool rightAns = solve(root->right, targetSum, sum);
	return leftAns || rightAns;
}
bool hasPathSum(Node* root, int targetSum) {
	int sum = 0;
	bool ans = solve(root, targetSum, sum);
	return ans;
}


void solve(Node* root, int targetSum, vector<vector<int>>& ans, vector<int> temp, int sum) {
	//base case
	if (root == NULL) {
		return;
	}
	//1 casE SOLVE KRNA H 
	sum += root->data;
	temp.push_back(root->data);

	//extra case
	if (root->left == NULL && root->right == NULL) {
		//verify
		if (sum == targetSum) {
			//store temp path in final ans array
			ans.push_back(temp);
		}
		else {
			return;
		}
	}

	//baaki recursion sambhal lega
	solve(root->left, targetSum, ans, temp, sum);
	solve(root->right, targetSum, ans, temp, sum);
}
vector<vector<int>> pathSum(Node* root, int targetSum) {
	vector<vector<int>> ans;
	vector<int> temp;
	int sum = 0;
	solve(root, targetSum, ans, temp, sum);
	return ans;
}


//------------------------------------------------------
int searchInorder(int inorder[], int size, int target) {
	for (int i = 0; i < size; i++) {
		if (inorder[i] == target) {
			return i;
		}
	}
	return -1;
}

void createMapping(int inorder[], int size, map<int, int>& dataueToIndexMap) {

	for (int i = 0; i < size; i++) {
		int element = inorder[i];
		int index = i;
		dataueToIndexMap[element] = index;
	}

}

Node* constructTreeFromPreAndInorderTraversal(map<int, int>& dataueToIndexMap, int preOrder[], int inOrder[], int& preIndex, int inOrderStart, int inOrderEnd, int size) {
	//base case
	if (preIndex >= size || inOrderStart > inOrderEnd) {
		return NULL;
	}

	//1 case main solve krta hu
	int element = preOrder[preIndex];
	preIndex++;
	Node* root = new Node(element);
	//element search krna padega  inorder me 
	//int position = searchInorder(inOrder, size, element);
	int position = dataueToIndexMap[element];
	//baaaki recursion sambhal lega
	root->left = constructTreeFromPreAndInorderTraversal(dataueToIndexMap, preOrder, inOrder, preIndex, inOrderStart, position - 1, size);

	root->right = constructTreeFromPreAndInorderTraversal(dataueToIndexMap, preOrder, inOrder, preIndex, position + 1, inOrderEnd, size);

	return root;

}

Node* constructTreeFromPostAndInorderTraversal(map<int, int>& dataueToIndexMap, int postorder[], int inorder[], int& postIndex, int inorderStart, int inorderEnd, int size) {

	if (postIndex < 0 || inorderStart > inorderEnd) {
		return NULL;
	}

	//1 case main solve krunga
	int element = postorder[postIndex];
	postIndex--;
	Node* root = new Node(element);
	//search karo inorder me 
	int position = dataueToIndexMap[element];
	//baaki recursion sambhal lega
	//right ki call pehle lagegi
	root->right = constructTreeFromPostAndInorderTraversal(dataueToIndexMap, postorder, inorder, postIndex, position + 1, inorderEnd, size);

	root->left = constructTreeFromPostAndInorderTraversal(dataueToIndexMap, postorder, inorder, postIndex, inorderStart, position - 1, size);

	return root;


}


int main() {

	Node* root = createTree();
	//cout << root->data << endl;
	cout << "Printing Preorder: ";
	preOrderTraversal(root);
	cout << endl;

	cout << "Printing Inorder: ";
	inorderTraversal(root);
	cout << endl;

	cout << "Printing PostOrder: ";
	postOrderTraversal(root);
	cout << endl;

	cout << "Level Order : ";
	levelOrderTraversal(root);
	cout << endl;

	return 0;
}