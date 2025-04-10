#include "QuadTree.h"
#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;

Point::Point() : x(0), y(0) {}

Point::Point(int x1, int y1) : x(x1), y(y1) {}

Node::Node(Point pont, const char data[], int x) {
    this->coordinate = pont;
    strcpy_s(this->data, data);
    this->x = x;
}

QuadTree::QuadTree() {
    boundary1 = Point(10, 10);
    boundary2 = Point(-10, -10);
    node = new Node(Point(), "N/A", 0);
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
}

QuadTree::QuadTree(Node* n, Point a, Point b) {

    boundary1.x = max(a.x, b.x);
    boundary1.y = max(a.y, b.y);
    boundary2.x = min(a.x, b.x);
    boundary2.y = min(a.y, b.y);

    node = n;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
}

void QuadTree::insert(Node* n) {
    if (n == nullptr || (node->coordinate.x == n->coordinate.x && node->coordinate.y == n->coordinate.y) || !Boundary(n->coordinate)) {
        return;
    }

    // meghatarozza a megfelelo kvadranst a csomopont koordinatai alapjan
    QuadTree** quadrant = nullptr;
    if (node->coordinate.x <= n->coordinate.x) {
        quadrant = (node->coordinate.y <= n->coordinate.y) ? &topRight : &bottomRight;
    }
    else {
        quadrant = (node->coordinate.y <= n->coordinate.y) ? &topLeft : &bottomLeft;
    }

    // Ha a kivalasztott kvadrans nincs inicializalva, hozzon letre egy uj QuadTree-t
    if (*quadrant == nullptr) {
        *quadrant = new QuadTree(n, boundary1, boundary2);
    }
    else {
        (*quadrant)->insert(n);
    }
}


Node* QuadTree::search(Point n) {
    if (!Boundary(n)) {
        return nullptr;
    }

    if (node->coordinate.x == n.x && node->coordinate.y == n.y) {
        return node;
    }

    if (node->coordinate.x <= n.x) {
        if (node->coordinate.y <= n.y) {
            if (topRight == NULL) {
                return nullptr;
            }
            return topRight->search(n);
        }
        else {
            if (bottomRight == NULL) {
                return nullptr;
            }
            return bottomRight->search(n);
        }
    }
    else {
        if (node->coordinate.y <= n.y) {
            if (topLeft == NULL) {
                return nullptr;
            }
            return topLeft->search(n);
        }
        else
        {
            if (bottomLeft == NULL) {
                return nullptr;
            }
            return bottomLeft->search(n);
        }
    }
}

bool QuadTree::Boundary(Point a) const {
    if (a.x <= boundary1.x && a.x >= boundary2.x) {
        if (a.y <= boundary1.y && a.y >= boundary2.y) {
            return true;
        }
    }
    return false;
}

void QuadTree::inOrder(int depth) {
    QuadTree* root = this;
    if (root != NULL) {
        root->topRight->inOrder(depth + 1);
        root->topLeft->inOrder(depth + 1);
        for (int i = 0; i < depth; i++) {
            cout << "\t\t";
        }
        cout << root->node->data << " " << node->x << " --| \n\n";
        root->bottomLeft->inOrder(depth + 1);
        root->bottomRight->inOrder(depth + 1);
    }
}

void QuadTree::deleteNode(Point a) {
    if (search(a) != 0) {
        search(a)->deleted = 1;
        rebuild();
    }
}

void QuadTree::rebuild() {
    Node* n = new Node(searchNotDeleted());
    QuadTree* root = new QuadTree(n, boundary1, boundary2);
    preOrderInsert(root);
    (*this) = (*root);
}

Node QuadTree::searchNotDeleted() {
    if (node->deleted == 0) {
        return *node;
    }
    return topRight->searchNotDeleted();
    return topLeft->searchNotDeleted();
    return bottomLeft->searchNotDeleted();
    return bottomRight->searchNotDeleted();
}

void QuadTree::preOrderInsert(QuadTree* tree) {
    if (this != NULL) {
        if (node->deleted == 0) {
            tree->insert(node);
        }
        topLeft->preOrderInsert(tree);
        topRight->preOrderInsert(tree);
        bottomRight->preOrderInsert(tree);
        bottomLeft->preOrderInsert(tree);
    }
}

QuadTree::~QuadTree() {
    delete topLeft;    
    topLeft = NULL;
    delete topRight;   
    topRight = NULL;
    delete bottomLeft; 
    bottomLeft = NULL;
    delete bottomRight; 
    bottomRight = NULL;
    delete node;       
    node = NULL;
}

void QuadTree::tour(int& x) {
    srand(static_cast<unsigned int>(time(NULL)));
    if (this != NULL) {

        cout << "\n---------------------------------------------------------------\n";
        cout << "Welcome to the galaxy of " << node->data << "!\n";
        int guessRangeLow = rand() % 2 + 1;
        int guessRangeHigh = rand() % 2 + 1;
        cout << "Guess the energy level of the galaxy, ranging from (" << node->x - guessRangeLow << "," << node->x + guessRangeHigh << "):\n";
        cin >> guessRangeLow;  
        if (guessRangeLow == node->x) {
            x += 1;
            cout << "Bingo! You now have " << x << " energy crystals.\n";
        }
        else {
            cout << "Incorrect guess!\n";
        }

        cout << "Where would you like to proceed?\n";
        cout << "1. Northeast ";
        if (topRight != NULL) {
            cout << " ( towards the " << topRight->node->data << " galaxy )\n";
        }
        else {
            cout << " ( this path ends here )\n";
        }

        cout << "2. Northwest ";
        if (topLeft != NULL) {
            cout << " ( towards the " << topLeft->node->data << " galaxy )\n";
        }
        else {
            cout << " ( this path ends here )\n";
        }

        cout << "3. Southwest ";
        if (bottomLeft != NULL) {
            cout << " ( towards the " << bottomLeft->node->data << " galaxy )\n";
        }
        else {
            cout << " ( this path ends here )\n";
        }

        cout << "4. Southeast ";
        if (bottomRight != NULL) {
            cout << " ( towards the " << bottomRight->node->data << " galaxy )\n";
        }
        else {
            cout << " ( this path ends here )\n";
        }
        cin >> guessRangeLow;  

        system("CLS"); 
        switch (guessRangeLow) {
        case 1:
            if (topRight != NULL) topRight->tour(x);
            break;
        case 2:
            if (topLeft != NULL) topLeft->tour(x);
            break;
        case 3:
            if (bottomLeft != NULL) bottomLeft->tour(x);
            break;
        case 4:
            if (bottomRight != NULL) bottomRight->tour(x);
            break;
        default:
            x--; 
            tour(x);  
            break;
        }
    }
}
