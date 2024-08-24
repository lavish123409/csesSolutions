#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 2 4 1 2 7
/*

    brute force
    for every element
    - start from that index and traverse right, adding every element to sum
    - if at any point sum % n is equal to 0, increment the counter

    O(n*n)

    we can use previous question strategy
    make a sum variable and add the element at every index making it a prefix sum
    at every index, check whether the remainder for current prefix sum matches with the remainder of any other prefix sum which came before, increment the answer with number of remainder of prefix sums matched
    because we can subtract those prefix sum from current sum and on dividing that with n we would get remainder 0
    _ _ _ _ _ x_ _ _ _ _ y
    sum(0,x) % n = a
    sum(0,y) % n = a
    (sum(0,x) - sum(0,y)) % n = a - a = 0 [(a + b) % n = ((a % n) + (b % n)) % n]

    
*/

int main()
{

    int i, n;
    cin >> n;

    int mapRem[n] = {0};
    mapRem[0] = 1;
    int sum=0;
    ll ans=0;

    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        sum = (sum + x) % n;
        sum = (sum + n) % n;
        // cout << sum << " : " << mapRem[sum] << "\n";
        ans += mapRem[sum];
        mapRem[sum]++;
    }

    cout << ans << "\n";
    return 0;
}