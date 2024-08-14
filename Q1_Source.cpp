#include <iostream>
#include <vector>
using namespace std;


// COMPLEXITY N^2

int countStructures(int n){
    vector<int> dp(n + 1, 0);
    //asumming an empty sturcure is a valid one for now to use as subproblem
    dp[0] = 1;
    // iterate all possible heights of the max Tower
    for (int maxTower = 1; maxTower <= n; maxTower++){
    	// update running total of possible structures 
       // considering the current maxTowers height is not exceeded 
        for (int blocks = n; blocks >= maxTower; blocks--){
            dp[blocks] += dp[blocks - maxTower]; 
            // max tower made and subproblem called for remaining blocks
          // fill the list backward so bigger problems use the subproblem 
         //b4 subproblem gets updated for current maxTower height
        // since we fill backwards, the subproblems are not yet updated for the current max height
       // so wen we use them their state is for a lower maxTower height then the current one - hence valid
      // loop only updates backward to (blocks >= maxTower) and not full because 
      // its not possible to make the maxTower , with blocks less than it requires 
      //(combinations with lower maxTowers have already been counted by then)
        }
    }
    return dp[n] - 1; // empty stucuture subtracted
}

int main()
{
    int n;
    for (n = 1; n <= 20; n++)
        cout << n << " : " << countStructures(n) << endl;
    cout << endl;
    
    n = 10;     cout << n << " : " << countStructures(n) << endl;
    n = 100;    cout << n << " : " << countStructures(n) << endl;
    n = 150;    cout << n << " : " << countStructures(n) << endl;
    n = 180;    cout << n << " : " << countStructures(n) << endl;
    n = 200;    cout << n << " : " << countStructures(n) << endl;

    return 0;
}

