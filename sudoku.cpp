#include <bits/stdc++.h>
using namespace std;


class Sudoku{

public:
	Sudoku(){
		memset(Solved, false, sizeof Solved);
		memset(sudoku, false, sizeof sudoku);
		cout << endl;
		cout << "==================" << endl;
		cout << "New sudoku created." << endl;
		cout << endl;
	}

	~Sudoku(){
		cout << endl;
		cout << "Bye Bye World!. -_-" << endl;
		cout << "==================" << endl;
		cout << endl;
	}

	void parseSudoku(string prob){
		for(int i=0; i<81; i++)
			write(i/9, i%9, prob[i]-'0');
		printSudoku();
		return;
	}

	// TODO :: Make this Robust.
	void printSudoku(){
		cout << endl << hbar << endl;
		
		for(int i=0; i<9; i++){
			cout << "| ";
			for(int j=0; j<9; j++){
				int T = read(i,j);
				
				if(T==0) cout << "  ";
				else cout << T << " ";
				
				if(j%3==2) cout << "| ";
			}
			cout << endl;
		
			if(i%3==2)
				cout << hbar << endl;
			
		}
		cout << endl;
	}

	// Elements in r the row.
	vector<int> ROW(int r){
		vector<int> row(sudoku[r], sudoku[r] + 9);
		return row;
	}

	// Elements in c th column.
	vector<int> COL(int c){
		vector<int> col;
		for(int r=0; r<9; r++) col.push_back(read(r,c));
		return col;
	}

	// Elements in b th box of the sudoku numbered from top left corner.
	vector<int> BOX(int b){
		vector<int> box;
		int rs = (b-1)/3 * 3, cs = (b-1)%3 * 3;
		for(int r=rs; r<rs+3; r++)
			for(int c=cs; c<cs+3; c++)
				box.push_back(read(r,c));
		return box;
	}

	// Checks whether sudoku is solved.
	bool solved(){
		bool b = true;
		for(int i=0; i<9; i++){
			b = b & uniqueTest(COL(i)) & uniqueTest(ROW(i)) & uniqueTest(BOX(1 + i));
			if (b == false){
				return false;
			}
		}
		return b;
	}

	void solve(){
		cout << "Attempting to solve. ('.')" << endl;
		int iter = 0;

		while(solved() == false){
			int curSolved=0;
			iter++;
			
			// Initialize guess values.
			for(int i=0; i<9; i++){
				for(int j=0; j<9; j++){
					int cv = read(i,j);
					if(cv==0)
						memset(guess[i][j], true, 10);
					else{
						memset(guess[i][j], false, 10);
						guess[i][j][cv] = true;
					}

					// Eliminate obvious guesses.
					// Stage 1 : Solves easy problems. 
					vector<int> r(ROW(i)), c(COL(j)), b(BOX( (i/3*3) + j/3 + 1));
					for(int g=0; g<9; g++){
						guess[i][j][r[g]] = false;
						guess[i][j][c[g]] = false;
						guess[i][j][b[g]] = false;
					} 
				}
			}

			
			
			for(int i=0; i<9; i++){
				for(int j=0; j<9; j++){
					int pv = 0, fv;

					for(int g=0; g<10; g++)
						if(guess[i][j][g])
							pv++, fv=g;
					
					if(pv==1){
						curSolved++;
						write(i, j, fv);
					}
				}
			}
			
			if(curSolved==0){
				cout << "Cannot solve this problem :(" << endl;
				break;
			}
			// printSudoku();
		}

		printf("Solved in %d Iterations. :D\n", iter);
		printSudoku();
		return;
	}

private:
	int sudoku[10][10]; // sudoku table.
	int Solved[10][10]; // solved status of (r,c) position of sudoku.
	bool guess[10][10][10]; // Possibility of (g) at (r,c) position in [r][c][g].
	const string hbar = "+-------+-------+-------+";

	// Writes values to sudoku array safely.
	void write(int r, int c, int f){
		if(Solved[r][c]) 
			return;

		sudoku[r][c] = f;
		Solved[r][c] = (f!=0);
	}

	int read(int r, int c){
		return sudoku[r][c];
	}

	// Tests whether vector has repititive elements or unsolved entries(0's).
	bool uniqueTest(vector<int> v){
		map<int,int> m;
		for(int sz=0; sz<v.size(); sz++) m[v[sz]]++;
		
		if(m[0]>0) 
			return false; // unfilled field

		for(map<int,int>::iterator mit = m.begin(); mit!=m.end(); mit++)
			if(mit->second > 1)
				return false; // multiple entries of same number.
		
		return true;
	}

};

int main(){
	freopen("sdk.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	string T;
	while(cin >> T){
	
		Sudoku s;
		s.parseSudoku(T);
		s.solve();
	
	}
}
