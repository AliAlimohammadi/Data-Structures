#include <iostream>

using namespace std;

struct node
{
	int value;
	node *left;
	node *right;
};

class BinaryTree
{
    private:
	    void destroyTree(node *leaf)
	    {
	        if(leaf != NULL)
	        {
	            destroyTree(leaf->left);
		        destroyTree(leaf->right);
		        delete leaf;
	        }
	    }
	    
	    void insert(int key, node *leaf)
	    {
	        if(key < leaf->value)
	        {
		        if(leaf->left != NULL)
			        insert(key, leaf->left);
		        else
		        {
			        leaf->left = new node;
			        leaf->left->value = key;
			        leaf->left->left = NULL;
			        leaf->left->right = NULL;
		        }
	            
	        }
	        else if(key >= leaf->value)
	        {
	            if(leaf->right != NULL)
	                insert(key, leaf->right);
	            else
	            {
	                leaf->right = new node;
	                leaf->right->value = key;
	                leaf->right->right = NULL;
	                leaf->right->left = NULL;
	            }
	        }
	    }
	    
	    node *search(int key, node *leaf)
	    {
	        if(leaf != NULL)
	        {
	            if(key == leaf->value)
	                return leaf;
	            else if(key < leaf->value)
	                return search(key, leaf->left);
	            else
	                return search(key, leaf->right);
	        }
	        
	        return NULL;
	    }
	    
	    void inOrderPrint(node *leaf)
	    {
	        if(leaf != NULL)
	        {
	            inOrderPrint(leaf->left);
	            cout << leaf->value << ',';
	            inOrderPrint(leaf->right);
	        }
	    }
	    
	    void postOrderPrint(node *leaf)
	    {
	        if(leaf != NULL)
	        {
	            inOrderPrint(leaf->left);
	            inOrderPrint(leaf->right);
	            cout << leaf->value << ',';
	        }
	    }
	    
	    void preOrderPrint(node *leaf)
	    {
	        if(leaf != NULL)
	        {
	            cout << leaf->value << ',';
	            inOrderPrint(leaf->left);
	            inOrderPrint(leaf->right);
	        }
	    }
	    
	    node *root;
	
	public:
	    BinaryTree() { root = NULL; }
	    ~BinaryTree() { destroyTree(); }

	    void insert(int key)
	    {
	        if(root != NULL)
		        insert(key, root);
	        else
	        {
	            root = new node;
	            root->value = key;
	            root->left = NULL;
	            root->right = NULL;
	        }
	    }
	    
	    node *search(int key) { return search(key, root); }
	    
	    void destroyTree() { destroyTree(root); }
	    
	    void inOrderPrint()
	    {
	        inOrderPrint(root);
	        cout << endl;
	    }
	    
	    void postOrderPrint()
	    {
	        postOrderPrint(root);
	        cout << "\n";
	    }
	    
	    void preOrderPrint()
	    {
	        preOrderPrint(root);
	        cout << endl;
	    }
};

int main()
{

	BinaryTree *tree = new BinaryTree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);

	tree->preOrderPrint();
	tree->inOrderPrint();
	tree->postOrderPrint();

	delete tree;
	
    return 0;
}