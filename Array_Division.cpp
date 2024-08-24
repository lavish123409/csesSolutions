#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 2 4 1 2 7
/*

    brute force
    recursion
    select an index and take sum till that index
    recurse from next index to partition it for k-1 times
    whatever maximum sum we would get from subproblem, we would take minimum of that and current sum and return it

    we can use dp over it, but it would result in O(n^2) algorithm not ideal for 10^5 constraints

    I approach
    we can observe that ideally every subarray from k subarrays should have sum total_sum / k
    so, we can traverse the array and add current element to current running subarray sum, and if exceeds the limit (total_sum / k), increment the aubarray

    problem - we do not know when should we include some boundary element
    for ex- 
    3 2
    1 2 3

    3 2
    3 7 2

    in first case, 2 should be taken in 1st subarray
    but in second case, 7 should be taken in 2nd subarray

    peeking solution - realised that binary search can be used
    observation
    if we can get maximum sum x after partitioning into k subarrays, we can also get x+1 (maybe, we cannot get x+1, but the idea is that x+constant can become maximum sum if we would add any left or right element to subarray with maximum sum)
    we can binary search on answer value with m, minimum value can be the max of array and maximum value can be total sum
    then, we would traverse the array and increment the subarrays count, if sum would exceed m
    we would check at last whether number of subarrays is <= k
    if it is, then it is a potential answer, and we cna find better answer on left side
    otherwise, we would have to search on the right side
*/

int main()
{

    int i, n, k;
    cin >> n >> k;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    ll l=0, r=0;
    for(i=0;i<n;i++) {
        l = max(l, 1ll * a[i]);
        r += a[i];
    }

    ll ans = 0;
    while(l <= r) {
        ll m = l + (r - l) / 2;
        int subarrays = 1;
        ll currentSum = 0ll;
        for(i=0;i<n;i++) {
            if(currentSum + a[i] > m) {
                currentSum = 0ll;
                subarrays++;
            }
            currentSum += a[i];
        }

        if(subarrays <= k) {
            ans = m;
            r = m-1;
        }
        else {
            l = m+1;
        }
    }

    cout << ans << "\n";
    return 0;
}