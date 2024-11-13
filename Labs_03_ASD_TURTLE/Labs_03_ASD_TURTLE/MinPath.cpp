#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

vector<vector<int>> FillVectorFromFile(string& filename) {
	vector<vector<int>> initialPathes;
	ifstream file(filename);

	if (file.is_open()) {
		string line;
		// Reading lines from a file
		while (getline(file, line)) {
			vector<int> row;
			// Splitting a string into numbers
			istringstream row_iss(line);
			int num;

			// Reading numbers from a string
			while (row_iss >> num) {
				row.push_back(num);
			}

			initialPathes.push_back(row);
		}

		file.close();
	}
	else {
		cerr << "Error: The file could not be opened " << filename << '\n';
		return {};
	}

	return initialPathes;
}
void fillVectorWithZero(vector<vector<int>>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			vec[i][j] = 0;
		}
	}
}
void printVector(vector<vector<int>>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			cout << vec[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n' << '\n' << '\n';
}
//--------------------------------------------------------------------------------------------
// Function for calculating the minimum sums of paths
// to the point (i, j), taking into account only horizontal and vertical movements

void Solver(vector<vector<int>>& initialPathes, vector<vector<int>>& result) {
	for (int i = 0; i < result.size(); i++) {
		for (int j = result[i].size() - 1; j >= 0; j--) {
			// Processing of horizontal movement
			if (j > 0) {
				result[i][j - 1] = result[i][j] + initialPathes[2 * i][j - 1];
			}
			// Vertical movement processing
			if (i < result.size() - 1) {
				result[i + 1][j] = result[i][j] + initialPathes[2 * i + 1][j];
			}
		}
	}          
}
// Function for calculating the minimum sums of paths
// to the point (i, j) taking into account diagonal movements

void SolverHelp(vector<vector<int>>& initialPathes, vector<vector<int>>& result) {
	for (int i = 0; i < result.size(); i++) {
		for (int j = result[i].size() - 1; j >= 0; j--) {
			if (i < result.size() - 1 && j > 0) {
				result[i + 1][j - 1] = min(result[i][j - 1] + initialPathes[2 * i + 1][j - 1], result[i + 1][j] + initialPathes[2 * i + 2][j - 1]);
			}
		}
	}
}
// Function for finding the optimal path

vector<int> FinderPath(vector<vector<int>>& result) {
	vector<int> path;
	int i = result.size() - 1;
	int j = 0;
	// Moving through the matrix by choosing the minimum path
	while(i > 0 && j < result[i].size() - 1) {
		if (result[i][j + 1] < result[i - 1][j]) {
			j++;
			path.push_back(j);
		}
		else if (result[i - 1][j] < result[i][j + 1]) {
			i--;
			path.push_back(j);
		}
	}
	// Have reached the right edge of the matrix
	while (j < result[i].size() - 1) {
		j++;
		path.push_back(j);
	}
	// Have reached the top row of the matrix
	while (i > 0) {
		i--;
		path.push_back(j);
	}
	return path;
}
//--------------------------------------------------------------------------------------------
int main() {
	int n;

	cout << "Enter the dimension of the matrix (an integer greater than 0): ";
	while (!(cin >> n) || n <= 0) {
		cout << "Error: Incorrect input. Enter an integer greater than 0:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string filename = "initialData.txt";
	vector<vector<int>> result(n, vector<int>(n));
	vector<vector<int>> initialPathes = FillVectorFromFile(filename);

	// Checking for file opening error
	if (initialPathes.empty()) { 
		return 1; 
	}
	cout << "initial data of loads on the edges of the graph: " << '\n' << '\n';
	printVector(initialPathes);

	fillVectorWithZero(result);

	Solver(initialPathes, result);
	SolverHelp(initialPathes, result);

	cout << "the matrix of the graph after passing through the minimum paths: " << '\n' << '\n';
	printVector(result);

	cout << "Min Sum of the Path = " << result[result.size() - 1][0] << '\n';
	cout << "Path: ";

	vector<int> path = FinderPath(result);

	for (auto element : path) {
		cout << element << " ";
	}
	cout << '\n' << '\n' << '\n';
	return 0;
}