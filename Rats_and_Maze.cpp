#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#define LEN 10000
using namespace std;

class Stack;
class Walk{
	public:
		int x;
		int y;
		int director;
		friend class Stack;
		friend ostream & operator<<(ostream &os, const Walk out);
};
ostream & operator<<(ostream &os, const Walk out){
	os << out.x << " " << out.y << " " << out.director;
	return os;
}
class Stack{
	private:
		int top;
		int capacity;			//memory space of array
		Walk *stack;				//array of stack
		void DoubleCapacity();	//double the memory space of array
	public:
		Stack():top(-1),capacity(1){	//constructor
			stack = new Walk[capacity];
		}
		void push(Walk x);
		Walk pop();
		Walk Top();
		int size();
		void print();
		~Stack(){
			delete [] stack;
		}
};
void Stack::DoubleCapacity(){
	capacity *= 2;
	Walk *newstack = new Walk[capacity];		//create a new double space array
	
	for(int i = 0; i < capacity/2; i++){	//copy to new array
		newstack[i] = stack[i];
	}
	
	delete [] stack;						//replace the new array to array
	stack = newstack;
}
void Stack::push(Walk x){							
	if(top == capacity-1){					//check stack is full or not 
		DoubleCapacity();
	}
	stack[++top] = x;
}
Walk Stack::pop(){
	if(top == -1){							//check stack is empty or not
		cout << "Stack is empty." << endl;
		return {0,0,0};
	}
	return stack[top--];
}
Walk Stack::Top(){
	if(top == -1){							//check stack is empty or not
		cout << "Stack is empty." << endl;
		return {0,0,0};
	}
	return stack[top];
}
int Stack::size(){
	return top+1;
}
void Stack::print(){
	for(int i = 0; i < size(); i++){
		cout << stack[i] << endl;
	}
}

int main(){
	ifstream fin;
	
	int row, column;
	bool map[LEN];
	
	fin.open("maze_2.txt");
	if(!fin.is_open())
	{
		cerr << "error" << endl;
		exit(1);
	}
	fin >> row >> column;
	
	bool check[LEN] = {0};
	for(int i = 0; i < row*column; i++){
		fin >> map[i];
	} 
	fin.close();
	
	
	cout << row  << " " << column << endl;
	for(int i = 0; i < row*column; i++){
		cout << map[i] << " ";
		check[i] = map[i];
		if(!((i+1) % column)){
			cout << endl;
		}
	}
	cout << endl;
	Walk temp = {0,0,0};  		//director 0 nothing 1 right 2 down 3 left 4 up
	
	Stack R;
	R.push(temp);
	check[0] = 1;				//position
	do{
		temp = R.pop();
		for(; temp.director < 5; temp.director++){
			if(temp.director == 1){
				if(temp.x*column+temp.y+1 < row*column){
					if(!check[temp.x*column+temp.y+1]){
						check[temp.x*column+temp.y+1] = true;
						R.push(temp);
						temp = {temp.x, temp.y+1, 0};
					}
				}
			}else if(temp.director == 2){
				if((temp.x+1)*column+temp.y < row*column){
					if(!check[(temp.x+1)*column+temp.y]){
						check[(temp.x+1)*column+temp.y] = true;
						R.push(temp);
						temp = {temp.x+1, temp.y, 0};
					}
				}
			}else if(temp.director == 3){
				if(temp.x*column+temp.y-1 < row*column){
					if(!check[temp.x*column+temp.y-1]){
						check[temp.x*column+temp.y-1] = true;
						R.push(temp);
						temp = {temp.x, temp.y-1, 0};
					}
				}
			}else if(temp.director == 2){
				if((temp.x-1)*column+temp.y < row*column){
					if(!check[(temp.x-1)*column+temp.y]){
						check[(temp.x-1)*column+temp.y] = true;
						R.push(temp);
						temp = {temp.x-1, temp.y, 0};
					}
				}
			}
			if(temp.x*column+temp.y == row*column-1){
				R.push(temp);
				break;
			}
			for(int i = 0; i < row*column; i++){
				cout << check[i] << " ";
				if(!((i+1) % column)){
					cout << endl;
				}
			}
			cout << endl;
		}
		if(temp.x*column+temp.y == row*column-1){
			break;
		}
	}while(R.size() != 0);
	
	R.print();
	
	return 0;
}











