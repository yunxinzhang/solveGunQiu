#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
using namespace std;
enum direction {
	u2d, l2r, u2l, u2r, d2r, d2l, none,block, l,r,u,d
};
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
class Block {
public:
	int x, y;
	direction type;
	bool link[4];
	bool movable;
	bool operator<(const Block &p)const {
		if (x <p.x || (x==p.x && y>p.y))
			return true;
		else
			return false;
	}
	bool operator==(const Block &p)const {
		if (x==p.x && y==p.y)
			return true;
		else
			return false;
	}
	Block() {
		link[UP] = false;
		link[DOWN] = false;
		link[LEFT] = false;
		link[RIGHT] = false;
	}
	Block(int x, int y, direction c, bool t) :x(x), y(y), type(c),movable(t) {
		link[UP] = false;
		link[DOWN] = false;
		link[LEFT] = false;
		link[RIGHT] = false;
	}
};
class Map {
public:
	static set<vector<vector<direction>>> state;
	pair<int, int> dir[4] = { { 1,0 } ,{ -1,0 },{ 0,1 },{ 0,-1 } };
	Block start;
	Block end;
	int row;
	int col;
	vector<vector<direction>> panel;
	vector<vector<Block>> bs;
	int layer;
	string str;
	
	
	Map() {
		str = "";
		layer = 0;
		ifstream fin("map.txt");
		if (!fin) { cout << " read map failed ."; }
		string str; string c;
		fin >> str;
		fin >> row >> col;
		for (int i = 0; i < row; ++i) {
			vector<direction> v;
			for (int j = 0; j < col; ++j) {
				v.push_back(none);
			}
			panel.push_back(v);
		}
		for (int i = 0; i < row; ++i) {
			vector<Block> v;
			for (int j = 0; j < col; ++j) {
				v.push_back(Block());
			}
			bs.push_back(v);
		}
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				fin >> c;
				//cout << c << endl;
				Block b; 

				b.x = i; 
				b.y = j;
				/*if (c == "^d") {
					for (int i = 0; i < 4; ++i) { cout << b.link[i]; }cout << endl;
				}*/
				analysis(c, b);
				bs[i][j] = b;
				panel[i][j] = b.type;
			}
		}
		fin.close();
		
	}
	void analysis(string str, Block & b) {
		/*if (str == "^d") {
			for (int i = 0; i < 4; ++i) { cout << b.link[i]; }cout << endl;
		}*/
		if (str.find("z") != string::npos) {
			b.movable = false;
			str = str.substr(1);
		}
		else {
			b.movable = true;
		}
		int flag = 0;
		if (str.find("^") != string::npos) {
			// start
			flag = 1;
			b.movable = false;
			str = str.substr(1);
		}
		if (str.find("$") != string::npos) {
			//end
			flag = 2;
			b.movable = false;
			str = str.substr(1);
		}
		if (str == "u2l") {
			b.type = u2l;
			b.link[UP] = 1;
			b.link[LEFT] = 1;
		}
		else if (str == "u2r") {
			b.type = u2r;
			b.link[UP] = 1;
			b.link[RIGHT] = 1;
		}
		else if (str == "n") {
			b.type = none;
		}
		else if (str == "b") {
			b.type = block;
		}
		else if (str == "u2d") {
			b.type = u2d;
			b.link[UP] = 1;
			b.link[DOWN] = 1;
		}
		else if (str == "l2r") {
			b.type = l2r;
			b.link[LEFT] = 1;
			b.link[RIGHT] = 1;
		}
		else if (str == "d2r") {
			b.type = d2r;
			b.link[DOWN] = 1;
			b.link[RIGHT] = 1;
		}
		else if (str == "d2l") {
			b.type = d2l;
			b.link[DOWN] = 1;
			b.link[LEFT] = 1;
		}
		else if (str == "l") {
			b.type = l;
			b.link[LEFT] = 1;
		}
		else if (str == "r") {
			b.type = r;
			b.link[RIGHT] = 1;
		}
		else if (str == "u") {
			b.type = u;
			b.link[UP] = 1;
		}
		else if (str == "d") {
			b.type = d;
			b.link[DOWN] = 1;
			//for (int i = 0; i < 4; ++i) { cout << b.link[i]; }cout << endl;
			//for (int i = 0; i < 4; ++i) { cout << start.link[i]; }cout << endl;
		}
		if (flag == 1) {
			start = b;
			//for (int i = 0; i < 4; ++i) { cout << start.link[i]; }cout << endl;
		}
		if (flag == 2) end = b;
	}
	void show() {
		cout << "=======================" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				string mv = bs[i][j].movable ? "" : "z";
				switch (panel[i][j]) {
				case l: cout << mv+"l"; break;
				case r: cout << mv + "r"; break;
				case u:cout << mv + "u"; break;
				case d:cout << mv + "d"; break;
				case u2l:cout << mv + "u2l"; break;
				case u2r:cout << mv + "u2r"; break;
				case d2l:cout << mv + "d2l"; break;
				case d2r:cout << mv + "d2r"; break;
				case u2d:cout << mv + "u2d"; break;
				case l2r:cout << mv + "l2r"; break;
				case none:cout << mv + "n"; break;
				case block:cout << mv + "b"; break;
				}
				cout << "\t";
			}
			cout <<endl;
		}
	}
	
	
	// 应该是可以 moves的size 为0
	bool toEnd(int x, int y, int dir) {
//		cout << x << "," << y <<":"<<dir<< endl;
		if (x == end.x && y == end.y)return true;
		int newx=x, newy=y;
		int acc;
		switch (dir)
		{
		case UP:--newx; acc = DOWN; break;
		case DOWN:++newx; acc = UP; break;
		case LEFT:--newy; acc = RIGHT; break;
		case RIGHT:++newy; acc = LEFT;
		default:
			break;
		}
		if (newx == end.x && newy == end.y && bs[newx][newy].link[acc])return true;
		if (!inArea(newx, newy)||!bs[newx][newy].link[acc])return false;
		int newdir;
		for (int i = 0 ; i < 4 ; ++i) {
			if (i == acc)continue;
			if (bs[newx][newy].link[i]) {
				newdir = i;
				if (toEnd(newx, newy, newdir))return true;
			}
		}
		return false;
	}
	bool inArea(int x, int y) {
		if (x >= 0 && x < row && y >= 0 && y < col)return true;
		return false;
	}
	bool win() {
		int dir;
		for (int i = 0; i < 4 ; ++i) {
			if (start.link[i]) {
				dir = i;
			}
		}
		return toEnd(start.x, start.y,dir );
	}

};