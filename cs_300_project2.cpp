//============================================================================================
//Name               : CS 300 Project Two
//Author             : @heyitsJanai
//Version            : 1.0
//Description        : Created a binary search tree that reads CSV file & creates ordered BST
//============================================================================================

#include <iostream>

#include "CSVparser.hpp"

using namespace std;


//define structure to hold course information
struct Course {
    string courseId; // unique identifier
    string courseName;
    string preReq1;
    string preReq2;
};

//internal tree node structure
struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with a course
    Node(Course aCourse) :
                  Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // Implement inserting a course into the tree
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and bid using recursion
        this->addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // Implement searching the tree for a course
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseId.compare(courseId) == 0) {
            return current->course;
        }
        // if courseId is a prerequisite for current node then traverse left
        if (current->course.courseId.compare(courseId) < 0) {
            current = current->left;
        }
        // else, course is after current course, so traverse right
        else {
            current = current->right;
        }
    }

    Course course;
    return course;
}

/**
 * Add a course to a node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Implement inserting a course into the tree
    // if node is a prerequisite for the root node then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //inOrder not left
        inOrder(node->left);
        //output courseId and courseName
        cout << node->course.courseId << ", " << node->course.courseName << endl;
        //inOrder right
        inOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.courseName << endl;
    
    if (!course.preReq1.empty()) {
        cout << "Prerequisites: " << course.preReq1;
        if (!course.preReq2.empty()) {
            cout << ", " << course.preReq2 << endl;
        }
        else {
            cout << endl;
        }
    }
    else {
        return;
    }

    return;
}
/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the course tree
            Course course;
            course.courseId = file[i][0];
            course.courseName = file[i][1];
            course.preReq1 = file[i][2];
            course.preReq2 = file[i][3];

            // push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


int main(int argc, char* argv[]) {

    //initializing csv path and courseId
    string csvPath, courseId;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseId = "CSCI101";
        break;
    case 3:
        csvPath = argv[1];
        courseId = argv[2];
        break;
    default:
        csvPath = "courseList.csv";
        courseId = "CSCI101";
    }

    // define binary search tree to hold course info
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    cout << "Welcome to the course planner." << endl;
    cout << endl;

    int choice = 0;
    while (choice != 9) {

        cout << "1. Load Data Structure.       " << endl;
        cout << "2. Print Course List.         " << endl;
        cout << "3. Print Course.              " << endl;
        cout << "9. Exit                       " << endl;
        cout << endl;
        cout << "What would you like to do?    ";
        cin >> choice;

        switch (choice) {

        case 1:

            //complete the method call to load the course list
            loadCourses(csvPath, bst);
            cout << "Course List Loaded Successfully." << endl;
            break;

        case 2:
            //complete the method call to display the courses in order
            bst->InOrder();
            break;


        case 3:
            cout << "What course do you want to know about?";
            cin >> courseId;
            //search the tree for the desired course information
            course = bst->Search(courseId);

            // if course is found, display the information
            if (!course.courseId.empty()) {
                displayCourse(course);
            }
            // course is not found, let user know
            else {
                cout << "Course ID " << courseId << " not found." << endl;
            }

            break;

        default:
            //if menu option is not any of the first three or exit, it is invalid
            cout << choice << " is not a valid option." << endl;
            break;
        }

    }

    cout << "Thank you for using the course planner!" << endl;

    return 0;
}



