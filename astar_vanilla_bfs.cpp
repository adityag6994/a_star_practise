#include<iostream>
#include<stdio.h>
#include<vector>
#include <queue>

using namespace std;

void fillMaze(vector<vector<int>>& maze){
	maze={{0,0,0,0,0,0},{0,0,0,0,0,0},
	      {0,0,0,0,0,0},{0,0,0,0,0,0},
	      {0,0,0,0,0,0},{0,0,0,0,0,0}};

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
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===========" << endl;
}

bool checkValid(const int r, const int c, const vector<vector<int>>& maze){
	if(r >=0 && r<maze.size() && c>=0 && c< maze[0].size() && maze[r][c]==0)
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

void applyBFSuntilGoal(const vector<int>& start,
			const vector<int>& goal,
			vector<vector<int>>& maze,  
			const vector<vector<int>>& moves,
			int& totalMoves){
				queue<vector<int>> list;
				list.push(start);
				int flag=0;
				
				while(!list.empty()){
					totalMoves++;
					vector<int> current=list.front();
					maze[current[0]][current[1]]=current[2];
					list.pop();
					if(current[0]==goal[0] && current[1]==goal[1]){
						//printCurrentMove(current);
						cout << "Goal Reached!" << endl;
						break;
					}
					//printCurrentMove(current);
					for(int i=0; i<moves.size(); i++){
						int r=current[0]+moves[i][0];
						int c=current[1]+moves[i][1];
						if(checkValid(r,c,maze)){
							list.push({r,c,current[2]+1});
							maze[r][c]=current[2]+1;
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
	vector<int> start={1,1,1};
	vector<int> goal={4,4,9};
	int totalMoves=0;
	
	
	fillMaze(maze);
	getValidMoves(moves);
	printMaze(maze);           	
	applyBFSuntilGoal(start,goal,maze,moves,totalMoves);
	printMaze(maze);           	
		
	return 0;
}	
