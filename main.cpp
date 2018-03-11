/*
 * Sam Mullinix
 * Professor Eyles
 * CS 3304
 * 12 November 2017
 *
 */

#include <iostream>

using namespace std;

// Will create a node structure when called. Parameters of the
// structure are the array to hold the location and left and right nodes.
// Pre: None, can be called when needed as a structure type
// Post: defines a 2 dimensional location and a binary tree left right node format
// Structure Idea and implementation influenced from reference [1]

struct Node
{
    int location[2];                // Two dimensional
    Node* left;
    Node* right;
};

// Function to create a new node based off of
// the passed array given the location. Must pass the
// Location of the node.
// Pre: Takes in an integer location array to craft new node
// Post: node will be
// created with the given characteristics.
// NewNode structure given temp array idea influenced from reference [1].

struct Node* newNode(int location[])
{
    struct Node* temp = new Node;   // A temporary node to be used to return a setup node structure.

    temp->location[0] = location[0];
    temp-> location[1] = location[1];
                                    // Temp at it's array node location 0 and 1 are set to
    temp-> left = NULL;             // the passed array values 0 and 1 corresponding the the x and y values.
    temp->right = NULL;             // Since this is a root node, left and right children
    return temp;                    // are set to null and the correct node is returned.
}

// Function to insert a new node into the tree. Takes in the root node of the structure
// and the points corresponding to it as well as the depth. In the case of 2 dimensional
// the depth is only used to take as a mod 2, or mod k in the larger sense. This
// will keep track of whether ot check a y value of an x value to separate the tree at the level
// of the requested node.  This idea was influenced from the article labeled [1].
// Pre: Takes in a root node, and the location to be added as well as the depth integer.
// Post: Point is inserted into the structure from the root node.

Node* insertPoint(Node* root, int location[], int depth)
{
    if(root == NULL)                // If the root is Null then it is currently not an assigned node.
    {                               // Print the node creation statement and call the newNode function.
        cout << "The node (" << location[0] << ", "
             << location[1] << ") has been added." << endl;
        return newNode(location);
    }

    int x_or_y = depth % 2;         // Will alternate between the x and y values for each depth.

                                    // Will compare where to insert the node based off of the root of the tree.
    if(location[x_or_y] < root->location[x_or_y])
    {                               // Recursively traverse tree corresponding to depth until the
                                    // location is less than the value and place it there.
        root->left = insertPoint(root->left, location , depth + 1);
    }
    else
    {                               // Same step as above except for the other coordinate.
        root->right = insertPoint(root->right, location, depth + 1);
    }
    return root;                    // Return the root node.
}

// Helper function to pass initial value 0 to the insertPoint function
// Pre: Takes in the root node and the location to add
// Post: Will call the insertPoint method passing the root location and 0, node will be created after function call
Node* insert(Node* root, int location[])
{
    return insertPoint(root, location, 0);
}

// Function to print out the nodes in a binary tree fashion. Takes in the root node to process and proceeds
// with high values of spaces to properly format the tree.  I had many attempts at printing a binary a tree given the node
// but none of them turned out pretty or extremely function (See my binary tree program in assignment 3).
// I found inspiration for this intuitive solution at the reference marked [2].
// Pre: Takes in the root node and the number of spaces for each time, recursive variable.
// Post: The tree will be printed to the user in a format that is understandable. Console output.

void printNodes(Node *root, int space)
{
                                    // Base case, end of the node path, or no initial node.
    if (root == NULL)
        return;

                                    // Value to properly space out each tree depth.
    space += 8;

                                    // Right most right is printed first because a left to right view of
                                    // the tree would put the right node at the top or first to print.
    printNodes(root->right, space);

                                    // Print out the correct about of spaces for the node.
    cout << endl;
    for (int i = 8; i < space; i++)
        cout << " ";                // Print the node
    cout << "[" << root->location[0] << ", " << root->location[1] << "]" << endl;

                                    // Recursively print the left child. The left child will be processed last since
                                    // it will be at the bottom of the tree when looking at it from left to right.
    printNodes(root->left, space);
}

// Helper function for the print function
// that also passes space value as 0.
// Pre: Takes in the root to begin printing and passes 0 for first space timing
// Post: After the method is called, the tree is printed to the console

void printNodes(Node* root) {
    printNodes(root, 0);
}

// Main testing function
int main() {

    struct Node* root = NULL;       // Initialize the root node to Null. All other nodes will be chained to this node.
    int arraySize;                  // Declare the array size integer value to store how many points will be taken.
    bool errorHandle = false;       // Boolean value for error handling
    string errorAnswer;             // String to hold answer from the user.

                                    // Take input from the user, pre-condition, must be a positive whole number.
                                    // Pre: Must be a positive whole number. Error checking occurs if it is not.
                                    // Post: The arraySize variable holds the size entered.
    cout << "Enter a positive whole number to represent the number of 2 dimensional points to create in the K-Dimensional Tree: ";
    cin >> arraySize;               // Assign the value to arraySize
    cout << endl;

    if(arraySize == 0)              // If the user input is 0, then print that the tree will have no contents.
    {                               // Error Handling for an array of size 0.
        cout << "A K-D tree containing 0 nodes has no contents.";
        return 0;
    }

                                    // If the user input a negative number, handle the error and give the user another attempt to enter
                                    // a number that meets the pre-conditions.
    if(arraySize < 0)
    {
        while(!errorHandle) {       // Continue until a satisfactory number is acquired
            cout << "Error: A positive whole number is required.\nWould you like to try another number? (y/n)";
            cin >> errorAnswer;     // Take in whether or not the user wants to continue
            if(errorAnswer.compare("y") == 0)
            {                       // If the user input a y, then the program continues and will check the new input
                cout << "Enter a positive whole number to represent the number of 2 dimensional points to create in the K-Dimensional Tree: ";
                cin >> arraySize;
                cout << endl;
                if(arraySize > 0)   // Exit condition if the entered number is a positive number
                    errorHandle = true;
            } else
                return 0;           // Else the user does not want to continue and the program exits.

        }
    }

    int locations[arraySize][2];    // Create an array that is 2 dimensional. One dimension represent the number of nodes
                                    // And the other represents the dimension of the tree which will be 2 in this case.

                                    // State precondition to the user.
    cout << "For the following, only enter whole numbers." << endl;

    for(int i = 0; i < arraySize; i++)
    {                               // Nested for loops to go to each dimension and allows the user to input the values at any point
        for(int j = 0; j < 2; j++)  // Any whole number is allowed
        {
            cout << "Enter the value of [" << i << ", " << j << "]:";
            cin >> locations[i][j]; // Assign the entered value to the array locations to hold the inputs.
        }
    }

    cout << endl;                   // Spacing

                                    // Go through the array and insert each of
                                    // the locations into the tree as a node
    for(int i = 0; i < arraySize; i++)
    {
        root = insert(root, locations[i]);
    }

    printNodes(root);               // Call the print tree function to display the tree.
    return 0;
}

// References and resources used
//[1] http://www.geeksforgeeks.org/k-dimensional-tree/
//[2] http://www.geeksforgeeks.org/print-binary-tree-2-dimensions/