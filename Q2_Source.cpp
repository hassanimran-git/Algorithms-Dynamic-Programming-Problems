#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Global variables 
int n, m;
vector<int> depots;
vector<vector<int>> value;

//memoize funcition calls
vector<vector<int>> memo;

// Function to compute minimum strategic value
int MinStrategicValue(int bombs, int start, int end){
    //check memo if function call was made before
    if(memo[bombs][start]!= -1 ){return memo[bombs][start];}

    //base case : bombs finised or last depot reached
    if (bombs == 0 || start == end){
        memo[bombs][start] =  value[start][end];
        return memo[bombs][start];
    }

    int minimumValue = __INT_MAX__; //initialize min with infinity

    // iterates over all possible attacks for current problem
    for (int i = start; i < end; ++i) {
	/// Calculate the strategic value for the current attack by combining left and right subproblems
	//right side from pre calculated table
        int strategicValue = value[start][i] + MinStrategicValue(bombs - 1, i + 1, end);
        minimumValue = min(minimumValue, strategicValue);
        // Calculate the strategic value of the right subproblem recursively
        // by using one less bomb and considering the next possible attack position
        // Each iteration considers an attack with the current bomb placed at position i
        // and then makes a recursive call to calculate the strategic value
        // of the remaining depots with one less bomb available. 
        // recursively returning minimum strategic values 
	    //we end up with the most optimal attack 
    }
    memo[bombs][start] = minimumValue;
    return memo[bombs][start];
}

// Function to read input from file and pre-process datasets
void processInputFromFile(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }
    

    while (inputFile >> n >> m && (n != 0 && m != 0)){
        depots.resize(n);
        value.assign(n, vector<int>(n, 0));

        //intialize memo with negitives
        memo.assign(n, vector<int>(n, 0));
        for (int i = 0; i < memo.size(); i++){
            for (int j = 0; j < memo.size(); j++)
                memo[i][j] = -1;
        }

        // Read depot strategic values
        for (int i = 0; i < n; ++i)
            inputFile >> depots[i];

        // Bottom Up dp to poulate the value matrix
        // calulate all possible subproblems

        // Fill diagonal with zeros
        for (int i = 0; i < n; ++i)
            value[i][i] = 0;

        //Fill the rest using formula
        for (int l = 1; l < n; ++l){
            for (int i = 0; i < n - l; ++i){
                int j = i + l;
                value[i][j] = depots[i] * depots[j] + value[i + 1][j] + value[i][j - 1] - value[i + 1][j - 1];
            }
        }
        int minStrategicValue = MinStrategicValue(m, 0, n - 1);
        cout << minStrategicValue << endl;  
    }
    inputFile.close();
}

int main(){
    processInputFromFile("input.txt"); 
    return 0;
}

