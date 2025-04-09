#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    double x, p;
    cin >> x >> p;
    double probWin = p / 100.0;
    double probLose = 1.0 - probWin;
    const int MAX_BETS = 1000;
    vector<vector<double>> dp(MAX_BETS + 1, vector<double>(2, 0.0));
    
    double maxProfit = 0.0;
    for (int i = 1; i <= MAX_BETS; i++) {
        dp[i][0] = probWin * (dp[i - 1][0] + 1.0) 
                 + probLose * (dp[i - 1][0] - 1.0);

        
        dp[i][1] = max(
            dp[i][0],
            probWin * (dp[i - 1][1] + 1.0) 
            + probLose * (dp[i - 1][1] - 1.0 * (1.0 - x / 100.0))
        );

        maxProfit = max(maxProfit, dp[i][1]);
    }
    cout << fixed << setprecision(8) << max(0.0, maxProfit) << endl;
    return 0;
}
