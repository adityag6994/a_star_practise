//1. bfs
//2. get path
//3. add obstacles 
//4. use cost to get around


#include<iostream>
#include<stdio.h>
#include<vector>
#include <queue>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

// node class for saving location and parent
class Node{
	public:
	vector<int> _position={};
	Node* _parent=nullptr;
	int _cost=0;
	
	Node(vector<int> position, Node* parent, int cost){
		_position=position;
		_parent=parent;			
		_cost = cost;
	}
	
	Node* getParent(){
		return _parent;
	}
	
	vector<int> getPosition(){
		return _position;
	}
	
	int getCost(){
		return _cost;
	}
	
	void printPostion(){
		cout << "[" << _position[0] << "," << _position[1] << "] " ;
	}


};

// define maze
void fillMaze(vector<vector<int>>& maze){
	maze={{100,100,100,100,100,100,100,100,100,100},
	      {100,222,222,222,222,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,100,100,100,100,222,100,100,100,100},
	      {100,222,222,222,222,222,100,100,100,100},
	      {100,222,100,100,100,100,100,100,100,100}};

	return;		
}

// get valid neibhors
void getValidMoves(vector<vector<int>>& moves){
	moves = {{-1,0},{1,0},{0,-1},{0,1}};
	return;
}

void printMaze(vector<vector<int>>& maze){
	cout << "===========" << endl;
	for(int i=0; i<maze.size(); i++){
		for(int j=0; j<maze[i].size(); j++){
			cout << std::setw(4) << maze[i][j] << " | ";
		}
		cout << endl;
		cout <<"---------------------------------------------------------------------" << endl;
	}
	cout << "===========" << endl;
}

//check if within boundary and no obstacles
bool checkValid(const int r, const int c, const vector<vector<int>>& maze){
	if(r >=0 && r<maze.size() && c>=0 && c< maze[0].size() && maze[r][c]==100)
		return true;
	return false;
}

void printCurrentMove(const vector<int>& moves){
	for(int i=0; i<moves.size(); i++){
		cout << moves[i] << " ";
	}
	cout << endl;
	return;
}


//print path to start if goal is found
void printPath(Node* goal, vector<vector<int>>& maze){ 
	Node* current=goal;
	int count=0;
	while(current){
		current->printPostion();
		maze[current->getPosition()[0]][current->getPosition()[1]]=-99;
		current=current->getParent();
		count++;
	}
	return;
}

bool checkInVisited(const int r, const int c, map<pair<int,int>,int>& visited, const int newCost){
	auto it = visited.find({r,c});
	//cout << "[" <<  it->first.first << "," << it->first.second << "|" << it->second << "]" << "-" << newCost << endl;
	if(it!=visited.end()){
		if(it->second > newCost){
			it->second = newCost;
			return true;
		}
	}
	return false;
}

//operator for priority queue
bool operator<(const Node& p1, const Node& p2)
{
    return p1._cost < p2._cost;
}

//manhatten distance
int heuristicCost(const int r, const int c, const vector<int>& goal){
	return abs(goal[0]-r)+abs(goal[1]-c);
} 


void applyBFSuntilGoal(Node* start,
			const vector<int>& goal,
			vector<vector<int>>& maze,  
			const vector<vector<int>>& moves,
			int& totalMoves){
			
				//priority queue to save nodes
				priority_queue<Node*> list;
				//visited list
				map<pair<int,int>,int> visitedList;
				list.push(start);
				int found=0;
				
				while(!list.empty()){
					//===|get top element
					totalMoves++;
					Node* currentNodePtr = list.top();
					vector<int> currentPos=currentNodePtr->getPosition();
					int currentCost = currentNodePtr->getCost();
					maze[currentPos[0]][currentPos[1]]=currentCost;
					visitedList.insert({{currentPos[0], currentPos[1]},currentCost});
					list.pop();
					
					//===|early exit
					if(currentPos[0]==goal[0] && currentPos[1]==goal[1]){
						printPath(currentNodePtr, maze);
						cout << "Goal Reached!" << endl;
						found=1;
						break;
					}
				
					//===|add neibhors
					for(int i=0; i<moves.size(); i++){
						int r=currentPos[0]+moves[i][0];
						int c=currentPos[1]+moves[i][1];
						int newCost = currentCost+1;
						//add neibhor if
						//- within limits and not previously visited or
						//- new cost is less than previous cost
						if(checkValid(r,c,maze) || checkInVisited(r, c, visitedList, newCost)){
							//add heuristic to cost
							newCost += heuristicCost(r,c,goal);
							Node* temp=new Node({r,c},currentNodePtr,newCost);
							list.push(temp);
							maze[r][c]=currentCost+1;
						}
					}
				}
				if(!found)
					cout << "Goal not reached!" << endl;
					
				cout << "Total Moves : " << totalMoves << endl;
				return;
				
			}

int main(){
	std::cout << "Implimentation of A*" << std::endl;
	// 0 : initial
	// 9 : goal
	vector<vector<int>> maze, moves;
	Node* start = new Node({8,1},nullptr,0);
	vector<int> goal={2,8};
	int totalMoves=0;
	fillMaze(maze);
	getValidMoves(moves);
	cout << "Initial Maze : " << endl;
	printMaze(maze);           	
	applyBFSuntilGoal(start,goal,maze,moves,totalMoves);
	printMaze(maze);           	
		
	return 0;
}	
