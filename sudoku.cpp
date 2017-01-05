#include <bits/stdc++.h>
#include "Sudoku.h"
using namespace std;

int main(){
	freopen("sdk.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string T; int x;
	int solv[2] = {0,0};
	while(cin >> T){
	
		Sudoku s;
		s.parseSudoku(T);
		s.solve();

		solv[s.solved()]++;
	}

	cout << "Solved : " << solv[1] << endl;
	cout << "Unable to solve : " << solv[0] << endl;
}
