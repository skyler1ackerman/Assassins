#include <iostream>
#include <vector>

using namespace std;

class Node {
    public:
    char name;
    Node* target;
    bool picked;
    Node(char name) : name(name) { picked = false; }
};

class NodeGraph {
    public:
    NodeGraph();
    vector<Node*> allNodes;
    int unpickedNodes;
    void assignNames();
    void unassignNames();
    void unpickNames();
    int numCircles();
    string printCircles();
    string percentCircle(vector<double> numCircleArr, int numTrials);
    string histogram(vector<double> numCircleArr, int numTrials);
    double expectedPercentOneCircle();
    vector<double> getNumCirclesArray(int numTrials, int maxCircles);
    void createGraph(int numNodes);
    ~NodeGraph();
};