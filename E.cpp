#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;


double dp[1001][2];
bool visited[1001][2];

double x, p;
double winProbab, loseProbab;

double helper(int i, bool insure) {
    if (i == 0) return 0.0;
    if (visited[i][insure]) return dp[i][insure];
    visited[i][insure] = true;

    double result = 0.0;

    if (!insure) {
        double stayUninsure = winProbab * (helper(i - 1, false) + 1.0) 
                             + loseProbab * (helper(i - 1, false) - 1.0);

        double startInsurance = winProbab * (helper(i - 1, true) + 1.0)
                              + loseProbab * (helper(i - 1, true) - (1.0 - x / 100.0));

        result = max(stayUninsure, startInsurance);
    } else {
        result = winProbab * (helper(i - 1, true) + 1.0)
               + loseProbab * (helper(i - 1, true) - (1.0 - x / 100.0));
    }

    return dp[i][insure] = result;
}

int main() {
    cin >> x >> p;
    winProbab = p / 100.0;
    loseProbab = 1.0 - winProbab;

    memset(visited, false, sizeof(visited));

    double maxProfit = 0.0;
    for (int i = 1; i <= 1000; ++i) {
        maxProfit = max(maxProfit, helper(i, false));
    }

    cout << fixed << setprecision(8) << max(0.0, maxProfit) << endl;
}
