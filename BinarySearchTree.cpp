#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// tree node including left, right and parent pointers and the key 
struct Node
{
	Node(int value) : key(value), parent(NULL), left(NULL), right(NULL) {}
	int key;
	Node *parent;
	Node *left;
	Node *right;
};

// Binary Search Tree class
class BinarySearchTree
{
	private:
		Node *root;

		void insert(Node *treeNode, int key)
		{
			if (!treeNode)
			{
				treeNode = new Node(key);
				root = treeNode;
			}
			else
			{
				if (key < treeNode->key)
				{
					if (!treeNode->left)
					{
						Node *treeTemp = new Node(key);
						treeTemp->parent = treeNode;
						treeNode->left = treeTemp;
					}
					else
						insert(treeNode->left, key);
				}
				else
				{
					if (!treeNode->right)
					{
						Node *treeTemp = new Node(key);
						treeTemp->parent = treeNode;
						treeNode->right = treeTemp;
					}
					else
						insert(treeNode->right, key);
				}
			}
		}

		Node *deleteNode(Node *treeNode, int key)
		{
			// base case 
			if (treeNode == NULL) return treeNode;

			// If the key to be deleted is smaller than the root's key, 
			// then it lies in left subtree 
			if (key < treeNode->key)
				treeNode->left = deleteNode(treeNode->left, key);

			// If the key to be deleted is greater than the root's key, 
			// then it lies in right subtree 
			else if (key > treeNode->key)
				treeNode->right = deleteNode(treeNode->right, key);

			// If key is same as root's key, then This is the node 
			// to be deleted 
			else
			{
				// node with only one child or no child 
				if (treeNode->left == NULL)
				{
					Node *temp = treeNode->right;
					delete(treeNode);
					return temp;
				}
				else if (treeNode->right == NULL)
				{
					Node *temp = treeNode->left;
					delete(treeNode);
					return temp;
				}

				// node with two children: Get the in-order successor (smallest 
				// in the right subtree) 
				Node *temp = getMinNode(treeNode->right);

				// Copy the in-order successor's content to this node 
				treeNode->key = temp->key;

				// Delete the in-order successor 
				treeNode->right = deleteNode(treeNode->right, temp->key);
			}
			return treeNode;
		}

		Node *search(Node *root, int key)
		{
			// Base Cases: root is null or key is present at root 
			if (root == NULL || root->key == key)
				return root;

			// Key is greater than root's key 
			if (root->key < key)
				return search(root->right, key);

			// Key is smaller than root's key 
			return search(root->left, key);
		}

		Node *getSuccessor(Node *root, Node *treeNode)
		{
			if (treeNode->right != NULL)
				return getMinNode(treeNode->right);

			Node *nodeParent = treeNode->parent;
			while (nodeParent != NULL && treeNode == nodeParent->right)
			{
				treeNode = nodeParent;
				nodeParent = nodeParent->parent;
			}
			return nodeParent;
		}

		Node *getPredecessor(Node *root, Node *treeNode)
		{
			if (treeNode->left != NULL)
				return getMaxNode(treeNode->left);

			Node *nodeParent = treeNode->parent;
			while (nodeParent != NULL && treeNode == nodeParent->left)
			{
				treeNode = nodeParent;
				nodeParent = nodeParent->parent;
			}
			return nodeParent;
		}

		int getHeight(Node *treeNode)
		{
			if (!treeNode)
				return 0;
			return 1 + max(getHeight(treeNode->left), getHeight(treeNode->right));
		}

		Node *getMaxNode(Node *treeNode)
		{
			while (treeNode->right)
				treeNode = treeNode->right;
			return treeNode;
		}
		
		Node *getMinNode(Node *treeNode)
		{
			while (treeNode->left)
				treeNode = treeNode->left;
			return treeNode;
		}

		bool isBalanced(Node *treeNode)
		{
			if (!treeNode)
				return false;
			int leftHeight = getHeight(treeNode->left);
			int rightHeight = getHeight(treeNode->right);

			if (abs(leftHeight - rightHeight) > 1)
				return false;
			return true;
		}

		void inOrder(Node *treeNode)
		{
			if (!treeNode)
				return;
			inOrder(treeNode->left);
			cout << treeNode->key << ' ';
			inOrder(treeNode->right);
		}

		void preOrder(Node *treeNode)
		{
			if (!treeNode)
				return;
			cout << treeNode->key << ' ';
			preOrder(treeNode->left);
			preOrder(treeNode->right);
		}

		void postOrder(Node *treeNode)
		{
			if (!treeNode)
				return;
			postOrder(treeNode->left);
			postOrder(treeNode->right);
			cout << treeNode->key << ' ';
		}

		struct Trunk
		{
			Trunk *prev;
			string arrows;
			Trunk(Trunk *prev, string arrows) : prev(prev), arrows(arrows) {}
		};

		void showTrunks(Trunk *parent)
		{
			if (!parent)
				return;
			showTrunks(parent->prev);
			cout << parent->arrows;
		}

		void showBST(Node *root, Trunk *prev, bool isRightChild)
		{
			if (!root)
				return;
			string arrows = "    ";
			Trunk *trunk = new Trunk(prev, arrows);
			showBST(root->right, trunk, true);

			if (!prev)
				trunk->arrows = "---";
			else if (isRightChild)
			{
				trunk->arrows = ".---";
				arrows = "   |";
			}
			else
			{
				trunk->arrows = "`---";
				prev->arrows = arrows;
			}

			showTrunks(trunk);
			cout << root->key << endl;
			if (prev)
				prev->arrows = arrows;
			trunk->arrows = "   |";
			showBST(root->left, trunk, false);
		}

		void deleteBST(Node *treeNode)
		{
			if (!treeNode)
				return;

			Node *curTreeNode = treeNode;
			Node *leftTreeNode = treeNode->left;
			Node *rightTreeNode = treeNode->right;
			delete(curTreeNode);
			deleteBST(leftTreeNode);
			deleteBST(rightTreeNode);
		}

		/* This function traverse the skewed binary tree and
		stores its nodes pointers in vector nodes[] */
		void storeBSTNodes(Node* root, vector<Node*> &nodes)
		{
			// Base case 
			if (root == NULL)
				return;

			// Store nodes in in-order (which is sorted order for BST) 
			storeBSTNodes(root->left, nodes);
			nodes.push_back(root);
			storeBSTNodes(root->right, nodes);
		}

		// Recursive function to construct binary tree
		Node *buildTreeUtil(vector<Node*> &nodes, int start, int end)
		{
			// base case 
			if (start > end)
				return NULL;

			// Get the middle element and make it root
			int mid = (start + end) / 2;
			Node *root = nodes[mid];

			/* Using index in in-order traversal, construct
			left and right subtress */
			root->left = buildTreeUtil(nodes, start, mid - 1);
			if (root->left)
				root->left->parent = root;
			root->right = buildTreeUtil(nodes, mid + 1, end);
			if (root->right)
				root->right->parent = root;

			return root;
		}

		// This functions converts an unbalanced BST to a balanced BST
		Node *buildTree(Node *root)
		{
			// Store nodes of given BST in sorted order
			vector<Node*> nodes;
			storeBSTNodes(root, nodes);

			// Constucts BST from nodes[]
			return buildTreeUtil(nodes, 0, nodes.size() - 1);
		}

	public:

		BinarySearchTree() { root = NULL; }		// constructor     
		~BinarySearchTree() { deleteBST(); }	// destructor

		void insert(int key) { insert(root, key); }
		void deleteNode(int key) { deleteNode(root, key); }

		Node *getRoot() { return root; }

		Node *search(int key) { return search(root, key); }

		Node *getSuccessor(int key) { return getSuccessor(root, search(root, key)); }
		Node *getPredecessor(int key) { return getPredecessor(root, search(root, key)); }

		int getHeight() { return getHeight(root); }

		Node *getMaxNode()
		{
			if (!root)
			{
				cout << "The BST is empty!\n";
				return NULL;
			}
			return getMaxNode(root);
		}
		Node *getMinNode()
		{
			if (!root)
			{
				cout << "The BST is empty!\n";
				return NULL;
			}
			return getMinNode(root);
		}

		bool isBalanced() { return isBalanced(root); }

		void inOrder() { inOrder(root); }
		void preOrder() { preOrder(root); }
		void postOrder() { postOrder(root); }

		void showBST() { showBST(root, NULL, false); }

		void deleteBST() { deleteBST(root); }

		void balanceBST() { root = buildTree(root); }
};

int main()
{
	BinarySearchTree bst;

	string command;
	cout << "Binary Search Tree Command Line Interface\nDeveloped by: Ali Alimohammadi\t\thttps://www.github.com/AliAlimohammadi/\n\nBST>>>>> ";
	cin >> command;
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	while (command != "exit")
	{
		if (command == "insert")
		{
			string key;
			cin >> key;
			bst.insert(stoi(key));
		}
		else if (command == "delete")
		{
			string key;
			cin >> key;
			bst.deleteNode(stoi(key));
		}
		else if (command == "getroot" || command == "root")
			cout << bst.getRoot()->key << endl;
		else if (command == "search")
		{
			string key;
			cin >> key;
			Node *result = bst.search(stoi(key));
			if (!result)
				cout << "Key not found in BST!\n";
			else
				cout << "Key exists in BST!\n";
		}
		else if (command == "getsuccessor" || command == "successor")
		{
			string key;
			cin >> key;
			if (!bst.search(stoi(key)))
				cout << "Invalid input! There is no node with key = " << key << " in the BST!\n";
			else
			{
				Node *result = bst.getSuccessor(stoi(key));
				if (!result)
					cout << '<' << key << "> does not have a successor.\n";
				else
					cout << "The successor of <" << key << "> is: " << result->key << endl;
			}
		}
		else if (command == "getpredecessor" || command == "predecessor")
		{
			string key;
			cin >> key;
			if (!bst.search(stoi(key)))
				cout << "Invalid input! There is no node with key = " << key << " in the BST!\n";
			else
			{
				Node *result = bst.getPredecessor(stoi(key));
				if (!result)
					cout << '<' << key << "> does not have a predecessor.\n";
				else
					cout << "The predecessor of <" << key << "> is: " << result->key << endl;
			}
		}
		else if (command == "getheight" || command == "height")
			cout << "The height of this BST is: " << bst.getHeight() << endl;
		else if (command == "getmax" || command == "max")
			cout << "Maximum value: " << bst.getMaxNode()->key << endl;
		else if (command == "getmin" || command == "min")
			cout << "Minimum value: " << bst.getMinNode()->key << endl;
		else if (command == "isbalanced")
			if (bst.isBalanced())
				cout << "BST is balanced!\n";
			else
				cout << "BST is not balanced!\n";
		else if (command == "inorder" || command == "in-order")
		{
			cout << "In-Order traverse is:\n";
			bst.inOrder(); cout << endl;
		}
		else if (command == "preorder" || command == "pre-order")
		{
			cout << "Pre-Order traverse is:\n";
			bst.preOrder(); cout << endl;
		}
		else if (command == "postorder" || command == "post-order")
		{
			cout << "Post-Order traverse is:\n";
			bst.postOrder(); cout << endl;
		}
		else if (command == "showtree" || command == "showbst" || command == "show")
			bst.showBST();
		else if (command == "balanced" || command == "balance")
		{
			bst.balanceBST();
			cout << "The BST was successfully balanced!\n";
		}
		else if (command == "clear" || command == "clearbst" || command == "deletebst")
			bst.deleteBST();
		cout << "\nBST>>>>> ";
		cin >> command;
		transform(command.begin(), command.end(), command.begin(), ::tolower);
	}

	return 0;
}