#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>

/**
 * @class BST
 * @brief A template class providing a Binary search Tree (BST) implementation.
 *
 * This BST allows for efficient data storage and retrieval. It supports:
 * - insertion of elements of any type specified by the template parameter T
 * - Deletion of the entire tree or specific elements
 * - inOrder, preOrder, and  traversals
 * - Deep copy construction and assignment
 * - searching for specific elements within the tree
 *
 * @tparam T The data type of the elements stored in the BST. Type T must support
 *           comparison operators for the BST to function correctly.
 *
 * @note The implementation provided is recursive and does not self-balance. It may
 *       be less efficient for unbalanced data sets.
 *
 * @version 3.2
 *
 * @date 02-11-2023, Initial implementation
 * @date 03-11-2023, Added recursive deletion
 * @date 04-11-2023, Implemented copy constructor and assignment operator. Extended traversal methods to include const versions
 * @date 05-11-2023, Added search functionality
 * @date 06-11-2023, Optimized insertion and memory management
 * @date 09-11-2023, Improved search function and implemented function pointers for transversal methods
 *
 * @author Siyeshen Govender
 */


/** @brief Node structure for Binary search Tree.
 *
 * This structure represents a single node within a Binary search Tree.
 * It contains the data and pointers to the left and right child nodes.
 *
 * @tparam T The data type of the elements stored in the node.
 */
template <class T>
struct Node{
    T data; ///< The data stored in the node.
    Node* left = NULL; ///< Pointer to the left child node.
    Node* right = NULL; ///< Pointer to the right child node.
};

template <class T>
class BST
{
    public:

        typedef void (*NodeFunction)(Node<T>*);


        /** @brief Default constructor.
        *
        * Initializes the root of the BST to NULL.
        */
        BST() : root(NULL) {}

        /** @brief copy constructor.
        *
        * Creates a deep copy of the given BST.
        * @param initializer The BST to be copied.
        */
        BST(const BST<T> &initializer);

        /** @brief Destructor. It is virtual making it abstraction too.
        *
        * Recursively deletes all the nodes in the BST.
        */
        virtual ~BST();

        /** @brief inserts a new element into the BST.
        *
        * @param 'data' is the data to insert into the tree.
        * @return True if the insertion is successful, false otherwise.
        */
        bool insert(const T &data);


        /**
        * @brief Performs a search for a given value within the binary search tree.
        *
        * This function searches the tree for the node containing the specified data.
        * It operates recursively, narrowing down the search space by comparing the
        * value to be found with the value at the current node, then choosing the
        * appropriate subtree to continue the search.
        *
        * @param data The data value to search for within the tree.
        * @return A pointer to the node containing the data, or NULL if not found.
        */
        bool search(const T &data) const;


        /** @brief Empties the entire BST.
        *
        * @return True if the tree is successfully emptied, false otherwise.
        */
        bool deleteTree();

        /** @brief Performs an in-order traversal of the BST.
        */
        void inOrder(NodeFunction fn) const;

        /** @brief Performs a pre-order traversal of the BST.
        */
        void preOrder(NodeFunction fn) const;


        /** @brief Performs a post-order traversal of the BST.
        */
        void postOrder(NodeFunction fn) const;


        /** @brief Overloads the assignment operator for BST.
        *
        * @param 'rhs' meaning the right-hand side BST to assign from.
        * @return A reference to the current BST after assignment.
        */
        BST<T>& operator = (const BST<T> &rhs);

    private:

        Node<T>* root; ///< Pointer to the root node of the BST.

        /**
        * @brief Recursive helper function to search for a value starting from a given node.
        *
        * This method is used internally by the public search method and works recursively to find the specified value in the tree.
        *
        * @param 'parent' The node to start searching from.
        * @param 'data' The value to search for.
        * @return 'Node<T>*' A pointer to the node containing the data, or NULL if not found.
        */
        Node<T>* search(Node<T>* parent, const T &data) const;

        /**
        * @brief Helper method to insert a new element into the BST.
        * This recursive function inserts the data into the subtree rooted at the parent node.
        *
        * @param 'parent' The root node of the subtree into which the data will be inserted.
        * @param 'data' The data to insert into the tree.
        * @return True if the insertion is successful, false otherwise.
        */
        bool insert(Node<T>* parent, const T &data);

        /**
        * @brief Helper method to delete the entire BST.
        * This recursive function deletes all nodes in the subtree rooted at the parent node.
        *
        * @param 'parent' A reference to the root node of the subtree to delete.
        */
        void deleteTree(Node<T>* &parent);

        /**
        * @brief Helper method to copy the contents of another BST.
        *
        * This recursive function copies all nodes from the given BST into this BST.
        *
        * @param rhs The BST from which to copy.
        */
        void copy(const BST<T> &rhs);

        /**
        * @brief Helper method to copy a subtree rooted at a given node.
        *
        * This recursive function copies all nodes in the subtree rooted at the parent node.
        *
        * @param parent The root node of the subtree to copy.
        */
        void copy(const Node<T>* parent);

        /**
        * @brief Helper method for in-order traversal of the BST.
        *
        * This recursive function visits nodes in an in-order sequence starting from the parent node.
        *
        * @param 'parent' The root node of the subtree to traverse.
        */
        void inOrder(Node<T>* parent, NodeFunction fn) const;

        /**
        * @brief Helper method for pre-order traversal of the BST.
        *
        * This recursive function visits nodes in a pre-order sequence starting from the parent node.
        *
        * @param 'parent' The root node of the subtree to traverse.
        */
        void preOrder(Node<T>* parent, NodeFunction fn) const;


        /**
        * @brief Helper method for post-order traversal of the BST.
        *
        * This recursive function visits nodes in a post-order sequence starting from the parent node.
        *
        * @param parent The root node of the subtree to traverse.
        */
        void postOrder(Node<T>* parent, NodeFunction fn) const;

};

//____IMPLEMENTATION BELOW:_______________________________________


template <class T>
bool BST<T>::search(const T& data) const {
    return search(root, data) != NULL;
}

template <class T>
Node<T>* BST<T>::search(Node<T>* node, const T& data) const {
    // Base case: root is null or data is present at root
    if (node == NULL || node->data == data) {
        return node;
    }

    // Value is greater than root's data
    if (node->data < data) {
        return search(node->right, data);
    }

    // Value is smaller than root's data
    return search(node->left, data);
}


template <class T>
BST<T>::BST(const BST<T> &initializer) {
    root = NULL; //empty tree
    if (initializer.root != NULL) {
        copy(initializer.root); //copies nodes recursively
    }
}


//made changes
template<class T>
BST<T>::~BST() {
    std::stack<Node<T>*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node<T>* current = nodeStack.top();
        nodeStack.pop();

        if (current) {
            nodeStack.push(current->left);
            nodeStack.push(current->right);
            delete current;
        }
    }
}


template <class T>
bool BST<T>::insert(const T &data) {
    if (root == NULL) {
        root = new (std::nothrow) Node<T>;  // Use nothrow to avoid std::bad_alloc exception
        if (root == NULL) {
            // Handle memory allocation failure
            return false;
        }
        root->data = data;
        return true;
    } else {
        return insert(root, data);
    }
}


template <class T>
bool BST<T>::insert(Node<T>* parent, const T& data) {
    if (data < parent->data) {
        if (parent->left == NULL) {
            parent->left = new (std::nothrow) Node<T>;
            if (parent->left == NULL) {
                // Handle memory allocation failure
                return false;
            }
            parent->left->data = data;
            return true;
        } else {
            return insert(parent->left, data);
        }
    } else if (data > parent->data) {
        if (parent->right == NULL) {
            parent->right = new (std::nothrow) Node<T>;
            if (parent->right == NULL) {
                // Handle memory allocation failure
                return false;
            }
            parent->right->data = data;
            return true;
        } else {
            return insert(parent->right, data);
        }
    }
    // If data is neither less than nor greater than parent->data, it's a duplicate
    return false; // or handle duplicates as needed
}


template<class T>
void BST<T>::inOrder(NodeFunction fn) const {
    if (root != NULL) {
        inOrder(root, fn);
    }
}


template <class T>
void BST<T>::inOrder(Node<T>* parent, NodeFunction fn) const {
    if (parent != NULL) {
        inOrder(parent->left, fn);
        fn(parent); // Call the function pointer on the current node
        inOrder(parent->right, fn);
    }
}



template <class T>
void BST<T>::preOrder(NodeFunction fn) const {
    preOrder(root, fn);
}

template <class T>
void BST<T>::preOrder(Node<T>* parent, NodeFunction fn) const {
    if (parent != NULL) {
        fn(parent); // Apply the function to the current node
        preOrder(parent->left, fn); // Traverse left subtree
        preOrder(parent->right, fn); // Traverse right subtree
    }
}




template <class T>
void BST<T>::postOrder(NodeFunction fn) const {
    postOrder(root, fn);
}

template <class T>
void BST<T>::postOrder(Node<T>* parent, NodeFunction fn) const {
    if (parent != NULL) {
        postOrder(parent->left, fn); // Traverse left subtree
        postOrder(parent->right, fn); // Traverse right subtree
        fn(parent); // Apply the function to the current node
    }
}



template <class T>
bool BST<T>::deleteTree() {
    if (root != NULL) {
        deleteTree(root);
        root = NULL;  // After deleting, set root to NULL.
        return true;
    }
    return false;  // Nothing to delete.
}


template <class T>
void BST<T>::deleteTree(Node<T>* &parent) {
    if (parent != NULL) {
        deleteTree(parent->left);  // Delete left subtree
        deleteTree(parent->right); // Delete right subtree
        delete parent; // Delete current node
        parent = NULL; // Set deleted node's pointer to NULL
    }
}


template<class T>
void BST<T>::copy(const BST<T> &rhs)
{
    if(rhs.root != NULL)
        copy(rhs.root);
}


template<class T>
void BST<T>::copy(const Node<T>* parent)
{
    if(parent != NULL){
        insert(parent->data);
        copy(parent->left);
        copy(parent->right);
    }
}


template <class T>
BST<T>& BST<T>::operator=(const BST<T> &rhs) {
    if (this != &rhs) {  // Self-assignment check
        deleteTree(root);  // Clear existing tree
        root = NULL; //resetting root to NULL
        if (rhs.root != NULL) {
            copy(rhs.root); //Copies the nodes recursively
        }
    }
    return *this; //returning reference to current object
}


#endif // BST_H

