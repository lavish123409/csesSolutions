#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;

/*

    there is no need of lower bound
    we can follow this greedy strategy
    we can directly traverse the requirements array 
    and find the lowest apartment which fulfills the condition
    and assign it to that person
    in this way we are leaving lot of apartments to be taken by other persons

*/
 
void mergeArray(int* a, int l, int r, int m)
{
    int tmp[r - l + 1];
    int lp = l;
    int rp = m+1;
    int tap = 0;
 
    while(lp <= m && rp <= r)
    {
        if(a[lp] <= a[rp])
            tmp[tap++] = a[lp++];
        else
            tmp[tap++] = a[rp++];
    }
 
    while(lp <= m)
        tmp[tap++] = a[lp++];
    
    while(rp <= r)
        tmp[tap++] = a[rp++];
 
    for(int i=l;i<=r;i++)
        a[i] = tmp[i - l];
}
 
void mergeSort(int* a, int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        // cout << l << " , " << r << " : " << m << "\n";
        // cout << "lpart : ";
        // for(int i=l;i<=m;i++)
        //     cout << a[i] << " , ";
        // cout << "\n";
        
        // cout << "rpart : ";
        // for(int i=m+1;i<=r;i++)
        //     cout << a[i] << " , ";
        // cout << "\n";
 
        mergeArray(a, l, r, m);
        // cout << "lpart : ";
        // for(int i=l;i<=m;i++)
        //     cout << a[i] << " , ";
        // cout << "\n";
        
        // cout << "rpart : ";
        // for(int i=m+1;i<=r;i++)
        //     cout << a[i] << " , ";
        // cout << "\n";
    }
}
 
int main()
{
    int i, n, m, k;
    cin >> n >> m >> k;
 
    int a[n], b[m];
 
    for(i=0;i<n;i++)
        cin >> a[i];
    
    for(i=0;i<m;i++)
        cin >> b[i];
 
    sort(a, a+n);
    sort(b, b+m);

    // for(i=0;i<n;i++) {
    //     cout << a[i] << " ";
    // }
    // cout << "\n";
    // for(i=0;i<m;i++) {
    //     cout << b[i] << " ";
    // }
    // cout << "\n";
 
    int ans=0, lat=-1;
    // for(i=0;i<n;i++)
    // {
    //     int gva = lower_bound(b+lat+1, b+m, a[i] - k) - b;
 
    //     if(gva >= m)
    //         break;
 
    //     if(b[gva] >= a[i] - k && b[gva] <= a[i] + k)
    //     {
    //         ans++;
    //         lat = gva;
    //     }
    // }
    int j=0;
    for(i=0;i<m;i++) {
        while(j < n && a[j] < b[i] - k) {
            j++;
        }

        if(j < n && b[i] - k <= a[j] && a[j] <= b[i] + k) {
            ans++;
            j++;
        }
    }
 
    cout << ans << "\n";
 
    return 0;
}