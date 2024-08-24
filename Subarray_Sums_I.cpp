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

    2 pointer
    - as the array contains only positive integers, so the sum would only increase if we add some element
    - we would keep adding elements from right pointer
    - if current sum is greater than target, keep subtracting from left pointer until sum becomes less than or equal to target
    - if current sum is equal to target, increment the counter
    - otherwise, repeat from step 2
    
*/

int main()
{

    int i, n, x;
    cin >> n >> x;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    int l=0, r, ans=0;
    ll sum = 0ll;

    for(r=0;r<n;r++) {
        sum += a[r];
        while(l <= r &&  sum > x) {
            sum -= a[l++];
        }

        if(sum == x) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}