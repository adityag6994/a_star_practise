//1. bfs
//2. get path
	

#include<iostream>
#include<stdio.h>
#include<vector>
#include <queue>

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
		cout << "[" << _position[0] << "," << _position[1] << "]" << endl;
	}
	
};


void fillMaze(vector<vector<int>>& maze){
	maze={{100,100,100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100,100,100	},
	      {100,100,100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100,100,100},
	      {100,100,100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100,100,100},
	      {100,100,100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100,100,100},
	      {100,100,100,100,100,100,100,100,100,100},{100,100,100,100,100,100,100,100,100,100}};

	return;		
}

void getValidMoves(vector<vector<int>>& moves){
	moves = {{-1,0},{1,0},{0,-1},{0,1}};
	return;
}

void printMaze(vector<vector<int>>& maze){
	cout << "===========" << endl;
	for(int i=0; i<maze.size(); i++){
		for(int j=0; j<maze[i].size(); j++){
			cout << maze[i][j] << " | ";
		}
		cout << endl;
		cout <<"--------------------------" << endl;
	}
	cout << "===========" << endl;
}

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


void printPath(Node* goal, vector<vector<int>>& maze){ 
	Node* current=goal;
	//current->printPostion();
	//current->getParent()->printPostion();
	//current->getParent()->getParent()->printPostion();
	int count=0;
	while(current){
		current->printPostion();
		maze[current->getPosition()[0]][current->getPosition()[1]]=-99;
		current=current->getParent();
		count++;
	}
	return;
}

void applyBFSuntilGoal(Node* start,
			const vector<int>& goal,
			vector<vector<int>>& maze,  
			const vector<vector<int>>& moves,
			int& totalMoves){
				queue<Node*> list;
				list.push(start);
				int flag=0;
				
				while(!list.empty()){
					totalMoves++;
					Node* currentNodePtr = list.front();
					vector<int> currentPos=currentNodePtr->getPosition();
					int currentCost = currentNodePtr->getCost();
					maze[currentPos[0]][currentPos[1]]=currentCost;
					//currentNodePtr->printPostion();
					list.pop();
					//currentNodePtr->printPostion();
					if(currentPos[0]==goal[0] && currentPos[1]==goal[1]){
						printPath(currentNodePtr, maze);
						cout << "Goal Reached!" << endl;
						break;
					}
					//printCurrentMove(current);
					for(int i=0; i<moves.size(); i++){
						int r=currentPos[0]+moves[i][0];
						int c=currentPos[1]+moves[i][1];
						if(checkValid(r,c,maze)){
							Node* temp=new Node({r,c},currentNodePtr,currentCost+1);
							list.push(temp);
							maze[r][c]=currentCost+1;
						}
					}
				}
				cout << "Total Moves : " << totalMoves << endl;
				return;
				
			}

int main(){
	std::cout << "Implimentation of A*" << std::endl;
	// 0 : initial
	// 9 : goal
	// 
	vector<vector<int>> maze, moves;
	Node* start = new Node({2,1},nullptr,0);
	vector<int> goal={7,8};
	int totalMoves=0;
	
	
	fillMaze(maze);
	getValidMoves(moves);
	printMaze(maze);           	
	applyBFSuntilGoal(start,goal,maze,moves,totalMoves);
	printMaze(maze);           	
		
	return 0;
}	
