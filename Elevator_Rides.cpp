#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 4 10
// 4 8 6 1
/*

    [10, 9] -> size 2

    recurse(a, in, clist):
        if in >= n:
            return clist.size

        ans = n+1
        for ind, current_weight_in_elevator in clist:
            if current_weight_in_elevator + a[in] <= 10:
                clist[ind] = current_weight_in_elevator + a[in]
                ans = min(ans, recurse(a, in+1, clist))

        return ans

    recurse(a, mask, weightInLastRide, totalWeight):
        if(all elements are taken in mask):
            return 0

        for weight in a:
            if weight is not in mask && weightInLastRide + weight <= totalWeight:
                ans = min(ans, recurse(a, mask + currentIndex, weightInLastRide + weight, totalWeight))
            else:
                ans = min(ans, 1 + recurse(a, mask + currentIndex, weight, totalWeight))

        return ans

    // Editorial solution
    - traverse through all subsets
    - if we have to take ith person in subset (ith bit is set in subset)
        - then, check what is minimum rides and last weight, if we are not taking ith person (ith bit is unset) 
        - if, last weight + current person weight <= total weight, then we can add this person in last ride
            - check if minimum rides < current running minimum ride(current ans minimum ride) or if it is equal then it is better than the last weight of other possibility (current ans last weight)
            - current ans minimum ride would be same as last and current ans last weight would be last weight + current person weight <= total weight
        - else, we would have start a new ride from here
            - check if minimum rides + 1 < current running minimum ride(current ans minimum ride) or if it is equal then current weight of person is better than the last weight of other possibility (current ans last weight)
            - current minimum ride would be s1 + last one and current weight would be weight of current person

*/
int solve(int a[], int in, int total_weight, int n, vector<int>& clist) {
    if(in >= n) {
        return clist.size();
    }

    int ans = n+1;
    for(int i=0;i<clist.size();i++) {
        if(clist[i] + a[in] <= total_weight) {
            clist[i] += a[in];
            ans = min(ans, solve(a, in+1, total_weight, n, clist));
            clist[i] -= a[in];
        }
    }
    clist.push_back(a[in]);
    ans = min(ans, solve(a, in+1, total_weight, n, clist));
    clist.pop_back();

    return ans;
}

// pair<int,int> solve(int a[], int mask, int n, int totalWeight) {
//     // ps.push_back('\t');
//     // cout << ps << bitset<20>(mask) << " : " << weightInLastRide;
//     if(mask == int((1 << n) - 1)) {
//         // ps.pop_back();
//         return {0, };
//     }

//     int i;
//     pair<int,int> ans = {n+1, -1};
//     for(i=0;i<n;i++) {
//         if((mask & (1 << i)) == 0) {
//             pair<int, int> cans = solve(a, mask | (1 << i), n, totalWeight);
//             // if(weightInLastRide + a[i] <= totalWeight) {
//             //     // ans = min(ans, solve(a, mask | (1 << i), weightInLastRide + a[i], n, totalWeight));
//             // }
//             // // else {
//             //     ans = min(ans, 1 + solve(a, mask | (1 << i), a[i], n, totalWeight));
//             // // }
//         }
//     }
//     // cout << ps << "ans: " << ans;

//     // ps.pop_back();

//     return ans;
// }

pair<int, int> solve(int a[], int mask, int n, int totalWeight, vector<pair<int,int>>& dp) {
    if(mask == 0) {
        return {1, 0};
    }

    if(dp[mask] != make_pair(-1, -1)) {
        return dp[mask];
    }

    // ps.push_back('\t');
    // cout << ps << bitset<4>(mask) << " : ";
    int i;
    pair<int, int> ans = {n+1, int(1e9+1)};
    for(i=0;i<n;i++) {
        if(mask & (1 << i)) {
            pair<int, int> cans = solve(a, mask ^ (1 << i), n, totalWeight, dp);

            if(cans.second + a[i] <= totalWeight) {

                if(ans.first > cans.first || (ans.first == cans.first && ans.second > cans.second + a[i])) {
                    ans.first = cans.first;
                    ans.second = cans.second + a[i];
                }
                
            }
            else {

                if(ans.first > cans.first+1 || (ans.first == cans.first+1 && ans.second > a[i])) {
                    ans.first = cans.first + 1;
                    ans.second = a[i];
                }

            }
        }
    }

    // cout << ps << "(" << ans.first << " , " << ans.second << ") - ";
    // ps.pop_back();

    return dp[mask] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, x;
    
    cin >> n >> x;
    // cout << n << "\n";

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    // vector<int> clist;
    // cout << solve(a, 0, x, n, clist) << "\n";

    // vector<pair<int,int>> dp(int(1<<n), {-1, -1});

    // cout << solve(a, (1 << n) - 1, n, x, dp).first << "\n";

    vector<pair<int,int>> dp(int(1 << n));
    dp[0] = {1, 0};

    for(int subset = 1; subset < int(1 << n); subset++) {
        dp[subset] = {n+1, int(1e9+1)};
        // cout << bitset<4>(subset) << " : ";
        for(int person = 0; person < n; person++) {
            if(subset & (1 << person)) {
                pair<int, int> cans = dp[subset ^ (1 << person)];

                if(cans.second + a[person] <= x) {

                    if(dp[subset].first > cans.first || (dp[subset].first == cans.first && dp[subset].second > cans.second + a[person])) {
                        dp[subset].first = cans.first;
                        dp[subset].second = cans.second + a[person];
                    }
                    
                }
                else {

                    if(dp[subset].first > cans.first+1 || (dp[subset].first == cans.first+1 && dp[subset].second > a[person])) {
                        dp[subset].first = cans.first + 1;
                        dp[subset].second = a[person];
                    }

                }
            }
        }
        // cout << "(" << dp[subset].first << " , " << dp[subset].second << ")\n";
    }

    cout << dp[(1 << n) - 1].first << "\n";
    return 0;
}