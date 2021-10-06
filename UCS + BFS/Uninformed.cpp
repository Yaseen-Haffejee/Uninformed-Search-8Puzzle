#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string>
#include <unordered_set>
using namespace std;

struct Node{
    Node * parent;
    int blankPosition;
    string state;
    // vector<Node *> adjacencies;
    int cost = 0 ;
    Node(string input){
        state = createArray(input);
    }

     string createArray(string input){
        blankPosition = input.find("#");
        return input;
    }

    void PrintMatrix(){
        int i =0;
        for(char x : state){
            if(i < 2){
                cout<< x<<" ";
                i++;
            }
            else if(i=2){
                cout<< x<<endl;
                i = 0;
            }
        }
    }
    void PrintMatrix(string Current){
        int i =0;
        for(char x : Current){
            if(i < 2){
                cout<< x<<" ";
                i++;
            }
            else if(i=2){
                cout<< x<<endl;
                i = 0;
            }
        }
    }
    
    // void Up(){
    //     vector<string> currentState = state;
    //     if(blankPosition!= 0 && blankPosition!= 1 && blankPosition!=2){
    //             swap(currentState[blankPosition], currentState[blankPosition-3]);
    //             adjacencies.push_back(new Node(currentState));
    //     }
        
    // }

    // void Down(){
    //     vector<string> currentState = state;
    //     if(blankPosition!= 6 && blankPosition!= 7 && blankPosition!=8){
    //             swap(currentState[blankPosition], currentState[blankPosition+3]);
    //              adjacencies.push_back(new Node(currentState));
    //     }
    // }

    // void Left(){
    //     vector<string> currentState = state;
    //      if(blankPosition!= 0 && blankPosition!= 3 && blankPosition!=6){
    //             swap(currentState[blankPosition], currentState[blankPosition-1]);
    //             adjacencies.push_back(new Node(currentState));
    //     }
        
    // }

    // void Right(){
    //     vector<string> currentState = state;
    //     if(blankPosition!= 2 && blankPosition!= 5 && blankPosition!=8){
    //             swap(currentState[blankPosition], currentState[blankPosition+1]);
    //             adjacencies.push_back(new Node(currentState));
    //     }
        
    // }

    string makeMove(string move, string currentState){
        if(move == "UP"){
            if(blankPosition!= 0 && blankPosition!= 1 && blankPosition!=2){
                swap(currentState[blankPosition], currentState[blankPosition-3]);
            }
        }
        if(move == "DOWN"){
            if(blankPosition!= 6 && blankPosition!= 7 && blankPosition!=8){
                swap(currentState[blankPosition], currentState[blankPosition+3]);
            }
        }
        if(move == "LEFT"){
            if(blankPosition!= 0 && blankPosition!= 3 && blankPosition!=6){
                swap(currentState[blankPosition], currentState[blankPosition-1]);
            }
        }
        if(move == "RIGHT"){
            if(blankPosition!= 2 && blankPosition!= 5 && blankPosition!=8){
                swap(currentState[blankPosition], currentState[blankPosition+1]);
            }
        }
        return currentState;
    }
     vector<string> possibleMoves(){
        vector<string>availableMoves;
        if(blankPosition == 0){
            availableMoves.push_back("DOWN");
            availableMoves.push_back("RIGHT");
        }
        else if(blankPosition == 1){
            availableMoves.push_back("DOWN");
            availableMoves.push_back("LEFT");
            availableMoves.push_back("RIGHT");
        }
        else if(blankPosition == 2){
            availableMoves.push_back("DOWN");
            availableMoves.push_back("LEFT");
        }
        else if(blankPosition == 3){
            availableMoves.push_back("UP");
            availableMoves.push_back("DOWN");
            availableMoves.push_back("RIGHT");
        }
        else if(blankPosition == 4){
            availableMoves.push_back("UP");
            availableMoves.push_back("DOWN");
            availableMoves.push_back("LEFT");
            availableMoves.push_back("RIGHT");
        }
        else if(blankPosition == 5){
            availableMoves.push_back("UP");
            availableMoves.push_back("DOWN");
            availableMoves.push_back("LEFT");
        }
        else if(blankPosition == 6){
            availableMoves.push_back("UP");
            availableMoves.push_back("RIGHT");
        }
        else if(blankPosition == 7){
            availableMoves.push_back("UP");
            availableMoves.push_back("LEFT");
            availableMoves.push_back("RIGHT");
        }
        else{
            availableMoves.push_back("UP");
            availableMoves.push_back("LEFT");
        }
        return availableMoves;
    }
     bool operator==(const Node& n) const
    {
        return (this->state == n.state);
    }

    bool operator<(const Node& n) const{
        // for min priority_queue we use > below
        return (this->cost > n.cost);
    }
};
class MyHashFunction {
public:
    // state is returned as hash function
    size_t operator()(const Node& t) const
    {
        return (hash<string>()(t.state));
    }
};


class Graph{
    public:
    Node * root;
    Node * goal;
    Graph(string initial,string goalConfig){
        root = new Node(initial);
        goal = new Node(goalConfig);
    }

    bool contains(unordered_set<Node ,MyHashFunction>&s,Node * curr){
        if(s.find(*curr) != s.end()){
            return true;
        }
        return false;
    }
    bool contains(set<Node>&s,Node * curr){
        if(s.find(*curr) != s.end()){
            return true;
        }
        return false;
    }

    int Cost(Node solution){
        Node curr = solution;
        int cost = 0;
        while(curr.parent != NULL){
            curr = (*curr.parent);
            cost ++;
        }
        return cost;
    }
    int getNodeCost(unordered_set<Node,MyHashFunction>&s,Node * curr){
       auto n =  s.find(*curr);
       return n->cost;
    }
   
    int bfs(){
        queue< Node * > frontier1;
        unordered_set<  Node ,MyHashFunction > frontier2;
        unordered_set< Node ,MyHashFunction >visited;
        frontier1.push(root);
        frontier2.insert(*root);
        if(root->state == goal->state){
                return true;
        }
        while(!frontier1.empty()){
            Node * current = frontier1.front();
            frontier1.pop();
            frontier2.erase(*current);
            visited.insert(*current);
            vector<string> actions = current->possibleMoves();
            for (string move : actions){
                Node * child = new Node(current->makeMove(move,current->state));
                if(!contains(frontier2,child) && !contains(visited,child)){
                    child->parent = current;
                    if(child->state == goal->state){
                        return Cost(*child);
                        //return true;
                    }
                    frontier1.push(child);
                    frontier2.insert(*child);
                }
            }
        }
        //return false;
        return 0;
    }
    
    int Uniform_Cost_Search(){
        priority_queue<Node >frontier1;
        unordered_set<Node, MyHashFunction>frontier2;
        unordered_set<Node,MyHashFunction>visited;
        frontier1.push(*root);
        frontier2.insert(*root);
        if(root->state == goal->state){
                return true;
        }
        while(!frontier1.empty()){
            Node  current = frontier1.top();
            frontier1.pop();
            frontier2.erase(current);
            if(contains(visited, &current)){
                continue;
            }
            if(current.state == goal->state){
                    return current.cost;
            }
            visited.insert(current);
            vector<string> actions = current.possibleMoves();
            for (string move : actions){
                Node * child = new Node(current.makeMove(move,current.state));
                child -> cost += current.cost;
                if(move == "UP"){
                    child -> cost +=5;
                }
                else{
                    child -> cost +=1;
                }
                
                if(!contains(frontier2,child) && !contains(visited,child)){
                    child->parent = &current;
                    frontier1.push(*child);
                    frontier2.insert(*child);
                }
                else if(contains(frontier2,child) ){
                    if(getNodeCost(frontier2,child)> child->cost){
                        frontier2.erase(*child);
                        frontier2.insert(*child);
                        frontier1.push(*child);
                    }
                }
            }
        }
        return false;
    }
};

int main(){

    vector<string> inputs;
    string input;
    int i = 2;
    while(i > 0){
        getline(cin, input);
        inputs.push_back(input);
        i --;
    }
    //Submission 1
    // Node n = Node(inputs[0]);
    //n.PrintMatrix();
    
    //Submission 2
    // cout<<n.cost<<endl;
    // n.PrintMatrix(n.makeMove(inputs[1],n.state));

    //Submission 3
    // vector<string>moves = n.possibleMoves();
    // for (string v : moves){
    //     cout<<v<<endl;
    // }

    Graph g = Graph(inputs[0],inputs[1]);
    //Submission 4
    //cout<<g.bfs()<<endl;

    //Submission 5

    cout<<g.Uniform_Cost_Search()<<endl;
    return 0;
}