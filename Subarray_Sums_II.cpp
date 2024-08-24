#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 2 4 1 2 7
/*

    brute force
    for every element
    - start from that index and traverse right, adding every element to sum
    - if at any point sum is equal to target, increment the counter

    O(n*n)

    we cannot use previous question's solution strategy because in that solution we were having positive elements in the array
    so, we sure that if at point the current running subarray sum is greater than target, we would have to remove starting elements from the subarray, in other words decrease the length of subarray
    but, here even if the current running subarray sum is greater than target, it can decrease by the negative element at next index

    I solution
    suppose, at some index we have sum from starting as 7 and target is 5
    now, at any index before current index if we have sum from starting as 2, then we can subtract all those subarrays from current subarray and we would get sum as 5
    so, number of subarrays having sum 5 would be the number of subarrays whose sum is 2 from starting

    map of sums; mapSums = []
    sum = 0
    for every index, element in array:
        sum += element
        if (sum - target) is in mapSums:
            ans += mapSums[sum - target]

        mapSums[sum]++

    WA1 - didn't realized that ans is number of subarrays whose upper bound can be n * (n+1) / 2, leading to overflow with int datatype

    
*/

int main()
{

    int i, n, x;
    cin >> n >> x;

    map<ll, int> mapSums;
    mapSums[0] = 1;
    ll sum = 0ll;
    ll ans = 0;

    for(i=0;i<n;i++) {
        int ce;
        cin >> ce;

        sum += ce;
        if(mapSums.count(sum - x)) {
            ans += mapSums[sum - x];
        }

        mapSums[sum]++;
        // cout << sum << "\n";
        // for(auto p : mapSums) {
        //     cout << p.first << " , " << p.second << " - ";
        // }
        // cout << "\n";
    }

    cout << ans << "\n";
    return 0;
}