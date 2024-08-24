#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 123 321
/*

    - store numbers in vectors
    - traverse the number vectors recursively
    - we have to use 2 flags to represent
        - if last digit is same as digit in smaller number, then we cannot put digit smaller than the digit in smaller number(a) at current index
        - if last digit is same as digit in larger number, then we cannot put digit larger than the digit in larger number(b) at current index
    - loop through digts for first position
    - if some digit is to be put at current index
        - check whether previous index have same digit as lower number (a) and current given digit is less than digit in lower number(a)
        - check whether previous index have same digit as greater number (b) and current given digit is greater than digit in greater number(b)
        - return 0 for both
        - otherwise recurse
    - loop through all digits from 0 to 9 except current digit, and recurse it for next position
    - if it is last index return 1, we have successfully made a number


    recurse(in, digit, ldesm, ldelg):
        if ldesm and smallerNumber[in] > digit:
            return 0 
        if ldelg and largerNumber[in] < digit:
            return 0

        if in == n:
            return 1

        ans = 0
        for i = 0 to 9:
            if i not equal to digit:
                ans += recurse(in+1, i, ldesm and i == smallerNumber[in], ldelg and i == largerNumber[in])

        return ans


*/

ll dp[19][10][2][2][2];

vector<int> num;
ll solve(vector<int>& a, vector<int>& b, int in, int digit, int n, bool ldesn, bool ldeln, bool isFirst0) {
    // ps.push_back('\t');
    // cout << ps << in << " , " << digit << " : " << ldesn << " , " << ldeln;
    if(ldesn && a[in] > digit) {
        return 0;
    }

    if(ldeln && b[in] < digit) {
        return 0;
    }


    if(in == n-1) {
        // cout << ps;
        // for(int it : num) {
        //     cout << it;
        // }
        // cout << digit;
        return 1;
    }
    if(dp[in][digit][ldesn][ldeln][isFirst0] != -1) {
        return dp[in][digit][ldesn][ldeln][isFirst0];
    }
    // num.push_back(digit);

    int i;
    ll ans = 0;
    for(i=0;i<10;i++) {
        if(i != digit || (isFirst0 && i == 0)) {
            ans = ans + solve(a, b, in+1, i, n, ldesn && digit == a[in], ldeln && digit == b[in], isFirst0 && i == 0);
        }
    }
    // cout << ps << ans;

    // ps.pop_back();
    // num.pop_back();
    return dp[in][digit][ldesn][ldeln][isFirst0] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
    ll n, m;
    cin >> n >> m;

    memset(dp, -1, sizeof(dp));

    if(n == 0 && m == 0) {
        cout << "1\n";
        return 0;
    }

    vector<int> a, b;
    while(n > 0 || m > 0) {
        a.push_back(n%10);
        b.push_back(m%10);

        n /= 10;
        m /= 10;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    // for(int it : a) {
    //     cout << it << " , ";
    // }
    // cout << " <- a\n";
    
    // for(int it : b) {
    //     cout << it << " , ";
    // }
    // cout << " <- b\n";

    ll ans = 0ll;
    for(i = a[0]; i <= b[0]; i++) {
        ans = ans + solve(a, b, 0, i, int(a.size()), i == a[0], i == b[0], i == 0);
        // cout << "\n" << i << " : " << ans << "\n";
    }

    // cout << "fans: " << ans << "\n";
    cout << ans << "\n";

    return 0;
}