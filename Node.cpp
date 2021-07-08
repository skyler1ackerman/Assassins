#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

#include "Node.hpp"

template<typename T>
T random(vector<T> const &v){
    int r = rand() % v.size();
    return v[r];
}

int main(){
    // The number of "players"
    int numNodes = 47;
    // The number of trials
    int numTrials = 100000;
    int maxCircles = 11;
    // Seed the random at start
    srand (time(NULL));
    // Create a new graph (game) with a number of players
    NodeGraph graph;
    graph.createGraph(numNodes);
    // Run numTrials number of randomly assigned games
    vector<double> numCircleArr = graph.getNumCirclesArray(numTrials, maxCircles);
    cout << graph.percentCircle(numCircleArr, numTrials) << endl;
    //cout << graph.expectedPercentOneCircle() << endl;
    //cout << graph.histogram(numCircleArr, numTrials) << endl;
}

NodeGraph::NodeGraph(){}

vector<double> NodeGraph::getNumCirclesArray(int numTrials, int maxCircles){
    vector<double> numCircleArr(maxCircles, 0);
    int circles;
    for(int i=0;i<numTrials;i++){
        // Assign names randomly
        assignNames();
        // Find out the number of circles from our random assignments
        circles = numCircles();
        // Increment our maxCircles+ field if larger or equal to maxCircles
        if(circles >= maxCircles){
            numCircleArr.back()++;
            continue;
        }
        // Increment the numCircles for that array slot
        numCircleArr[circles-1]++;
    }
    return numCircleArr;
}

string NodeGraph::percentCircle(vector<double> numCircleArr, int numTrials){
    string percentString;
    int circles;
    // Create output string
    for(int j=0;j<numCircleArr.size()-1;j++){
        percentString += (to_string(j+1) + " circles: " + to_string(100*(numCircleArr[j]/numTrials)));
        percentString.push_back('\n');
    }
    percentString += (to_string(numCircleArr.size()) + "+ circles: " + to_string(100*(numCircleArr.back()/numTrials)));
    percentString.push_back('\n');
    return percentString;
}

string NodeGraph::histogram(vector<double> numCircleArr, int numTrials){
    string percentString;
    int circles;
    // Create output string
    for(int j=0;j<numCircleArr.size()-1;j++){
        percentString += (to_string(j+1) + ":  " +  string(round(200*numCircleArr[j]/numTrials), '#'));
        percentString.push_back('\n');
    }
    percentString += (to_string(numCircleArr.size()) + "+: " +  string(round(200*numCircleArr.back()/numTrials), '#'));
    percentString.push_back('\n');
    return percentString;
}

void NodeGraph::createGraph(int numNodes){
    // Create numNodes number of nodes labeled starting at A
    for(int i=0;i<numNodes;i++){
        Node* newNode = new Node(char(65+i));
        allNodes.push_back(newNode);
    }
    // Init unpicked nodes
    unpickedNodes = allNodes.size();;
}

void NodeGraph::unpickNames(){
    // Set all nodes to false
    for(auto x: allNodes){ x->picked=false; }
    // Reset unpicked nodes
    unpickedNodes = allNodes.size();
}
void NodeGraph::unassignNames(){
    // Reset all targets
    for(auto x: allNodes){ x->target=nullptr; }
}

void NodeGraph::assignNames() {
    // Unassign/ Unpick names first
    unassignNames();
    unpickNames();
    // Check for zero
    if(allNodes.size()==0){ 
        cout << "No names to assign";
        return;
    }
    // Pick a target for all players
    for(auto x: allNodes){
        // Set the target randomly
        x->target = random(allNodes);
        // If the player pulled his own name or a target that was already picked, repick
        while(x->target->picked || x->target == x){
            x->target = random(allNodes);
            // If the only target left is the players own name, redraw names
            if(x->target == x && unpickedNodes == 1){ return assignNames(); }
        }
        // When the player picks a valid target, mark as picked and deincrement unpicked nodes
        x->target->picked=true;
        unpickedNodes--;
    }
}

string NodeGraph::printCircles(){
    string circleString;
    // Start with the first player
    Node* curNode = allNodes[0];
    Node* startNode;
    // Unpick the names 
    unpickNames();
    for( auto curNode: allNodes){
        // If the player is already part of a circle, skip them
        if(curNode->picked){ continue; }
        // Otherwise, mark them as visited and record them
        curNode->picked=true;
        circleString += curNode->name;
        unpickedNodes--;
        startNode = curNode;
        // Iterate through the current circle
        while(curNode->target!=startNode){
            // Move to next player in circle and record them
            curNode = curNode->target;
            curNode->picked=true;
            circleString += " -> ";
            circleString.push_back(curNode->name);
            unpickedNodes--;
        }
        circleString += '\n';
    }
    return(circleString);
}
int NodeGraph::numCircles(){
    // numCircles starts at zero
    int numCircles = 0;
    // Start with the first player
    Node* curNode = allNodes[0];
    Node* startNode;
    // Unpick the names 
    unpickNames();
    for( auto curNode: allNodes){
        // If the player is already part of a circle, skip them
        if(curNode->picked){ continue; }
        // Otherwise, mark them as visited and record them
        curNode->picked=true;
        unpickedNodes--;
        startNode = curNode;
        // Iterate through the current circle
        while(curNode->target!=startNode){
            // Move to next player in circle and record them
            curNode = curNode->target;
            curNode->picked=true;
            unpickedNodes--;
        }
        // Iterate numCircles
        numCircles++;
    }
    return(numCircles);
}

double NodeGraph::expectedPercentOneCircle(){
    double denom = 0;
    for(int i=0;i<=allNodes.size();i++){
        denom += pow(-1,i)/tgamma(i+1);
    }
    return 100/(allNodes.size()*denom);
}

NodeGraph::~NodeGraph(){
    for(auto x: allNodes){
        delete(x);
    }
}