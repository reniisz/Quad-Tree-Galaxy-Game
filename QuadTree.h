#ifndef QUADTREE_H
#define QUADTREE_H

class Point {
public:
    int x, y;
    Point();
    Point(int, int);
    ~Point() {};
};

class Node {
public:
    Point coordinate;
    char data[50];
    int x;
    bool deleted = 0;
    Node(Point, const char[], int);
    ~Node() {};
};

class QuadTree {
private:
    Point boundary1, boundary2;
    Node* node;
    QuadTree* topLeft;
    QuadTree* topRight;
    QuadTree* bottomLeft;
    QuadTree* bottomRight;
    Node searchNotDeleted();
    void preOrderInsert(QuadTree*);
    void rebuild();

public:
    QuadTree();
    QuadTree(Node*, Point, Point);
    void insert(Node*);
    Node* search(Point);
    bool Boundary(Point) const;
    void inOrder(int);
    void deleteNode(Point);
    void tour(int&);
    ~QuadTree();
};

#endif QUADTREE_H
