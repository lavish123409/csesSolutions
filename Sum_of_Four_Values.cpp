#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 6 10
// 8 15
// 5 12
/*

    extension of two sum problem
    so, instead of writing loops 2 times, one for 3 and then for 4, we would write the solution for k-sum and pass the value 4 to it

    2sumIsPossible(array, l, r, target, ans):
        while l < r:
            if array[l] + array[r] == target:
                ans = [l, r]
                return 1
            else if array[l] + array[r] < target:
                l++
            else:
                r--

        return 0

    k-sumIsPossible(n, l, r, target, array, ans):
        if n == 2:
            2sumIsPossible(array, l, r)

        for index, element in array till r - n:
            cans = []
            if k-sumIsPossible(n-1, index+1, r, target - element, array, cans):
                ans = cans + index
                return 1

        return 0
    
*/

bool is2SumPossible(array<int,2> arr[], int l, int r, int target, vector<int>& ans) {
    while(l < r) {
        ll sum = 1ll * arr[l][0] + arr[r][0];
        if(sum == target) {
            // cout << sum << " = "; 
            // cout << l << " - ";
            // cout << arr[l][0] << " : "; 
            // cout << arr[l][1] << " , "; 
            // cout << r << " - ";
            // cout << arr[r][0] << " : "; 
            // cout << arr[r][1] << "\n"; 
            ans.push_back(arr[r][1]);
            ans.push_back(arr[l][1]);
            return 1;
        }
        else if(sum < target) {
            l++;
        }
        else {
            r--;
        }
    }

    return 0;
}

bool isKSumPossible(array<int,2> arr[], int l, int r, int target, int k, vector<int>& ans) {
    // if(target < 0) {
    //     return 0;
    // }
    if(k == 2) {
        if(is2SumPossible(arr, l, r, target, ans)) {
            return 1;
        }
        return 0;
    }

    int i;
    for(i=l;i<=r-k+1;i++) {
        if(isKSumPossible(arr, i+1, r, target - arr[i][0], k-1, ans)) {
            // cout << k << " - " << i << " : " << arr[i][0] << " , " << arr[i][1] << "\n";
            ans.push_back(arr[i][1]);
            return 1;
        }
    }
    return 0;
}

int main()
{

    int i, n, x;
    cin >> n >> x;

    array<int,2> a[n];
    for(i=0;i<n;i++) {
        cin >> a[i][0];
        a[i][1] = i+1;
    }

    sort(a, a+n);

    // for(i=0;i<n;i++) {
    //     cout << a[i][0] << "," << a[i][1] << " - ";
    // }
    // cout << "\n";

    vector<int> ans;
    if(isKSumPossible(a, 0, n-1, x, 4, ans)) {
        for(int it : ans) {
            cout << it << " ";
        }
        cout << "\n";
        return 0;
    }   

    cout << "IMPOSSIBLE\n";
    return 0;
}