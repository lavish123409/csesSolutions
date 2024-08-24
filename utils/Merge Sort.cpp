#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
    int n, i;
    cin >> n;

    int a[n];

    for(i=0;i<n;i++)
        cin >> a[i];

    mergeSort(a, 0, n-1);
    for(i=0;i<n;i++)
        cout << a[i] << " ";
    cout << "\n";

    return 0;
}