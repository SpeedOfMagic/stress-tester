#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	
	cout << "Enter compiler flags (Generator/Test solution/Correct solution): ";
	string raw;
	cin >> raw;
	string compil;
	for (char i : raw)
		if (i == '1' || i == '0')
			compil += i;
	
	
	if (compil[0] == '1') {
		cout << "Compiling generator..." << endl;
		system("g++ -std=c++17 -o gen gen.cpp");
		cout << "Compilation is finished." << endl;
	}
	
	if (compil[1] == '1') {
		cout << "Compiling test solution..." << endl;
		system("g++ -std=c++17 -o test test.cpp");
		cout << "Compilation is finished." << endl;
	}
	
	if (compil[2] == '1') {
		cout << "Compiling correct solution..." << endl;
		system("g++ -std=c++17 -o solve solve.cpp");
		cout << "Compilation is finished." << endl;
	}
	
	cout << "Amount of tests: ";
	int n;
	cin >> n;
	for (int test = 1; test <= n; test++) {
		system("./gen > input.txt");
		system("./test < input.txt > output.txt");
		system("./solve < input.txt > answer.txt");
		
		ifstream fout("output.txt");
		vector<string> output, answer;
		string cur;
		while (fout >> cur) 
			output.push_back(cur);
		fout.close();
		
		ifstream fans("answer.txt");
		while (fans >> cur)
			answer.push_back(cur);
		fans.close();
		
		if (output == answer) {
			cout << "Test #" << test << ": OK" << endl;
		} else {
			cout << "Test #" << test << ": WA" << endl;
			cout << "Input:" << endl;
			ifstream fin("input.txt");
			while (getline(fin, cur))
				cout << cur << endl;
			fin.close();
			
			cout << "Got:" << endl;
			ifstream fout("output.txt");
			while (getline(fout, cur))
				cout << cur << endl;
			fout.close();
			
			cout << "Expected:" << endl;
			ifstream fans("answer.txt");
			while (getline(fans, cur))
				cout << cur << endl;
			fans.close();
			cout << "Enter anything to exit." << endl;
			cin.get();
			return 0;
		}
	}
	
	cout << "All tests are passed." << endl;
	cout << "Enter anything to exit." << endl;
	cin >> raw;
	return 0;
}
