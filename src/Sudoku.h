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
		rawSudoku = prob;
		for(int i=0; i<81; i++)
			write(i/9, i%9, prob[i]-'0');
		printSudoku();
		return;
	}

	// Returns 81 character long string of initial state of sudoku.
	string rawProblem(){
		return rawSudoku;
	}

	// Returns 81 character long string of current state of sudoku.
	string curState(){
		string s = "";
		char n[10] = {'0','1','2','3','4','5','6','7','8','9'};
		for(int i=0; i<9; i++)
			for(int j=0; j<9; j++)
				s += n[read(i,j)];
		
		return s;
	}

	// Copy raw sudoku problem
	void copyRaw(Sudoku* F){
		memset(Solved, false, sizeof Solved);
		memset(sudoku, false, sizeof sudoku);
		parseSudoku(F->rawProblem());
		return;
	}

	// Copy current state of sudoku
	void copyCurState(Sudoku* F){
		memset(Solved, false, sizeof Solved);
		memset(sudoku, false, sizeof sudoku);
		parseSudoku(F->curState());
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

	// Returns co-ordinates of every element in xth row
	vector<pair<int, int> > RowIterator(int r){
		vector<pair<int, int> > rowIt;
		for(int f=0; f<9; f++)
			rowIt.push_back(make_pair(r,f));
		return rowIt;
	}

	// Returns co-ordinates of every element in xth column
	vector<pair<int, int> > ColIterator(int c){
		vector<pair<int, int> > colIt;
		for(int f=0; f<9; f++)
			colIt.push_back(make_pair(f,c));
		return colIt;
	} 

	// Returns co-ordinates of every element in xth box
	vector<pair<int, int> > BoxIterator(int b){
		vector<pair<int, int> > boxIt;
		int rs = (b-1)/3 * 3, cs = (b-1)%3 * 3;
		for(int r=rs; r<rs+3; r++)
			for(int c=cs; c<cs+3; c++)
				boxIt.push_back(make_pair(r,c));
		return boxIt;
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
		vector< pair<int,int> > boxIt(BoxIterator(b));
		for(int f=0; f<9; f++)
			box.push_back(read(boxIt[f].first, boxIt[f].second));
		return box;
	}

	// Checks whether sudoku is solved.
	bool solved(){
		bool b = true;
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++)
				b = b && Solved[i][j];
			b = b && uniqueTest(COL(i)) && uniqueTest(ROW(i)) && uniqueTest(BOX(1 + i));
			if (b == false)
				return false;
		}
		return b;
	}

	void buildGuesses(){
		// Initialize guess array.
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				int cv = read(i,j);
				if(cv==0)
					memset(guess[i][j], true, 10);
				else{
					memset(guess[i][j], false, 10);
					guess[i][j][cv] = true;
				}

				// Remove elements in same row, column, box.
				vector<int> r(ROW(i)), c(COL(j)), b(BOX( (i/3*3) + j/3 + 1));
				for(int g=0; g<9; g++){
					guess[i][j][r[g]] = false;
					guess[i][j][c[g]] = false;
					guess[i][j][b[g]] = false;
				}
			}
		}

		return;
	}

	// Strategy 1 :: If an element has single guess, assign it.
	int SolveElementsWithSingleGuesses(){
		int curSolved = 0;
		buildGuesses();
		for(int i=0; i<9; i++)
			for(int j=0; j<9; j++){
				int pv = 0, fv;

				for(int g=1; g<10; g++)
					if(guess[i][j][g])
						pv++, fv=g;
				
				if(pv==1)
					curSolved += write(i, j, fv);
				
			}
		
		return curSolved;
	}

	int SolveSingleGuessInRow(int r){
		int curSolved = 0;
		for(int v=1; v<10; v++){
			int pp = 0, pv;
			
			for(int c=0; c<9; c++)
				if(guess[r][c][v])
					pp++, pv = c;
			
			if(pp==1)
				curSolved += write(r,pv,v);
			
		}
			
		return curSolved;
	}

	int SolveSingleGuessInCol(int c){
		int curSolved = 0;
		for(int v=1; v<10; v++){
			int pp=0, pv;

			for(int r=0; r<9; r++)
				if(guess[r][c][v])
					pp++, pv = r;
			
			if(pp==1)
				curSolved += write(pv,c,v);
			
		}

		return curSolved;
	}

	int SolveSingleGuessInBox(int b){
		int curSolved = 0;
		for(int v=1; v<10; v++){
			int pp=0, pr, pc;
			vector< pair<int,int> > boxIt(BoxIterator(b));
			for(auto it=boxIt.begin(); it!=boxIt.end(); it++){
				int r = it->first, c = it->second;
				if(guess[r][c][v])
					pp++, pr = r, pc = c;
			}

			if(pp==1)
				curSolved += write(pr,pc,v);
		}

		return curSolved;
	}

	int SolveSinglePositionValues(){

		buildGuesses();
		int Row = 0;
		for(int i=0; i<9; i++)
			Row += SolveSingleGuessInRow(i);
		
		buildGuesses();
		int Col = 0;
		for(int i=0; i<9; i++)
			Col += SolveSingleGuessInCol(i);
		
		buildGuesses();
		int Box = 0;
		for(int i=1; i<10; i++)
			Box += SolveSingleGuessInBox(i);
		
		return Row + Col + Box;
	}

	void solve(){
		cout << "Attempting to solve. ('.')" << endl;
		int iter = 0, curSolved=1, t;

		while (curSolved!=0) {
			curSolved = 0;
		
			do{
				t = SolveElementsWithSingleGuesses();
				iter++; curSolved += t;
			}while(solved()==false && t>0);
		
			do{
				t = SolveSinglePositionValues();
				iter++; curSolved += t;
			}while(solved()==false && t>0);
		}
		
		printf("Solved in %d Iterations. :D\n", iter);
		printSudoku();
		return;
	}

private:
	string rawSudoku;	// Initial state of sudoku.
	int sudoku[10][10]; // sudoku table.
	int Solved[10][10]; // solved status of (r,c) position of sudoku.
	bool guess[10][10][10]; // Possibility of (g) at (r,c) position in [r][c][g].
	const string hbar = "+-------+-------+-------+";

	// Writes values to sudoku array safely.
	bool write(int r, int c, int f, bool overwrite=false){
		if(Solved[r][c]) 
			return false;

		sudoku[r][c] = f;

		// TODO :: remove f from guesses in r row and c column and (r,c) box. EFFICIENT WRITE.

		return Solved[r][c] = (f!=0);
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
