#include "maze.hpp"
#include <queue>
#include<stack>
#include <ctime>
queue<Map> que;

void solve() {
	if (que.size() == 0) { cout << "size==0" << endl;; }
	int ceng = 0;
	clock_t t1 = 0, t2 = 0;
	while (que.size() > 0) {
		Map nm = que.front();
		Map::state.insert(nm.panel);
		
		
		if (ceng < nm.layer) {
			t1 = clock();
			ceng = nm.layer;
			cout << "layer >>" << nm.layer <<" : " <<t1-t2<< endl;
			t2 = t1;
		}
		
		//nm.show();
		if (nm.win()) {
			cout << "\nwin\n" << endl;
			cout << nm.str << endl;
			return;
		}
		que.pop();
		for (int i = 0; i < nm.row; ++i) {
			for (int j = 0; j < nm.col; ++j) {
				if (nm.bs[i][j].type == none) {
					for (int k = 0; k < 4; ++k) {
						int newx = i + nm.dir[k].first;
						int newy = j + nm.dir[k].second;
						//cout << newx << "," << newy << " <-- " << i << "," << j << endl;
						if (nm.inArea(newx, newy) && nm.bs[newx][newy].movable &&nm.bs[newx][newy].type != none) {
							Map temp(nm);
							Block tb = temp.bs[i][j];
							temp.bs[i][j] = temp.bs[newx][newy];
							temp.bs[newx][newy] = tb;
							temp.panel[i][j] = temp.bs[i][j].type;
							temp.panel[newx][newy] = temp.bs[newx][newy].type;
							if (Map::state.find(temp.panel) == Map::state.end()) {
								temp.str += to_string(i) + "," + to_string(j) + "<--" + to_string(newx) + "," + to_string(newy)+"\n";
								temp.layer++;
								que.push(temp);
							}
							Map::state.insert(temp.panel);
						}
					}
				}
			}
		}
	}
	cout << "can't solve..." << endl;
	return;
}
set<vector<vector<direction>>> Map::state;
int main() {
	Map m;
//	cout << m.start.x << "," << m.start.y << endl;
//	cout << m.end.x << "," << m.end.y << endl;
//	for (int i = 0; i < 4; ++i) { cout << m.start.link[i]; }cout << endl;
	m.show();
	
	cout << m.win() << endl;;
	que.push(m);
	solve();
	getchar();
}