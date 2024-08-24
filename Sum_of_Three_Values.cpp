#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 6 10
// 8 15
// 5 12
/*

    extension of two sum problem
    - for each element in array, take target - element and find 2 sum for this amount in remaining elements on right side

    2sum(array, l, r, target):
        while l < r:
            if array[l] + array[r] == target:
                return l, r
            else if array[l] + array[r] < target:
                l++
            else
                r--

        return -1, -1

    for index, element in array:
        if 2sum(array, index+1, size-1, target - element):
            print index, l, r

    print Impossible
    
*/

bool is2SumPossible(array<int,2> a[], int l, int r, int target, pair<int,int>& ans) {
    while(l < r) {
        ll sum = 1ll * a[l][0] + a[r][0];
        if(sum == target) {
            // cout << sum << " : " << a[l][0] << " , " << a[r][0] << "\n";
            // cout << a[l][1] << " , " << a[r][1] << "\n";
            ans.first = a[l][1];
            ans.second = a[r][1];
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

    pair<int,int> ans = {-1, -1};
    for(i=0;i<n-2;i++) {
        if(is2SumPossible(a, i+1, n-1, x - a[i][0], ans)) {
            cout << a[i][1] << " ";
            cout << ans.first << " ";
            cout << ans.second << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}