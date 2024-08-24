#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
int main()
{
    string s;
    char cchar = 0;
 
    cin >> s;
 
    int i, n=s.size();
    int cf=0, ans=0;
    for(i=0;i<=n;i++)
    {
        if(i != n && cchar == s[i])
        {
            cf++;
        }
        else
        {
            ans = max(ans, cf);
            cf = 1;
            cchar = s[i];
        }
    }
 
    cout << ans << "\n";
 
    return 0;
