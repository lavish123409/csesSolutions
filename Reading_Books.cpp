#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 6 10
// 8 15
// 5 12
/*

    thinking approaches
    think of this problem as filling two columns with length of a_i
    1 - we can fill 1st column with smaller numbers and 2nd column with larger numbers

    problem - when we would meet in the middle, the middle element would be in some column and other column would have to wait for it to get free

    2 - we can fill 1st column with first smallest, then second largest, then third smallest and so on and 2nd column with reverse

    problem - not able to think about the implementation (maybe difficult)

    solution - gfg
    - we can fill first column with smaller numbers, and second column first with largest number and then with smaller numbers, because smaller numbers would be free after larger number finishes
    - only 1 corner case that if largest number is larger than the sum of all n-1 elements, then we would have to wait for largest number to finish and again take largest number time to finish it in first column
    
*/

int main()
{

    int i, n;
    cin >> n;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    sort(a, a+n);

    ll sum = 0ll;
    for(i=0;i<n-1;i++) {
        sum += a[i];
    }

    if(sum < 1ll * a[n-1]) {
        cout << 2ll * a[n-1] << "\n";
    }
    else {
        cout << sum + a[n-1] << "\n";
    }
    
    return 0;
}