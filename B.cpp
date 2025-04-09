#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000000LL
#define exp -1
#define vll vector<ll>
#define vi vector<ll>
#define vc vector<char>
#define vvll vector<vector<ll>>
#define vvc vector<vector<char>>
vll isPrime(exp+1,1);

vector<ll> robots;
set<pair<ll, ll>> stores;

ll matchRobot(int idx, set<pair<ll, ll>>& remStores) {
    if (idx >= robots.size()) return 0;

    ll robot_pos = robots[idx];
    ll max_profit = 0;
    auto best_it = remStores.end();

    auto it = remStores.lower_bound({robot_pos, 0});

    if (it != remStores.end()) {
        ll dist = abs(it->first - robot_pos);
        ll profit = it->second - dist;
        if (profit > max_profit) {
            max_profit = profit;
            best_it = it;
        }
    }

    if (it != remStores.begin()) {
        auto prev_it = prev(it);
        ll dist = abs(prev_it->first - robot_pos);
        ll profit = prev_it->second - dist;
        if (profit > max_profit) {
            max_profit = profit;
            best_it = prev_it;
        }
    }

    if (best_it != remStores.end() && max_profit > 0) {
        remStores.erase(best_it);
        return max_profit + matchRobot(idx + 1, remStores);
    }

    return matchRobot(idx + 1, remStores);
}

void solve() {
    ll t, x, c = 0;
    cin >> t >> x;
    if (t == 1) {
        robots.push_back(x);
    } else {
        cin >> c;
        stores.insert({x, c});
    }

    set<pair<ll, ll>> remStores = stores;
    ll total_profit = matchRobot(0, remStores);
    cout << total_profit << endl ;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
