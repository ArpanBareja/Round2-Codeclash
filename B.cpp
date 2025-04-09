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

void createSieve(){
   isPrime[0]=0 , isPrime[1] = 0 ;
   for(ll i = 2 ; i*i <= exp ; i++){
       if(isPrime[i])
       {
          for(ll j = i*i ; j<=exp ; j+=i)
            isPrime[j] = 0 ;
       }
   }
}

vector<ll> zFunction(string &str) {
    ll n = str.length();
    vector<ll> z(n, 0);

    ll l = 0, r = 0;
    for (ll i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }

        while (str[z[i]] == str[z[i] + i]) {
            z[i]++;
        }

        if (z[i] + i - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
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

    ll profit_today = 0;
    set<pair<ll, ll>> remStores = stores;

    for (ll robot_pos : robots) {
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
            profit_today += max_profit;
            remStores.erase(best_it);
        }
    }

    cout << profit_today << endl;


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
