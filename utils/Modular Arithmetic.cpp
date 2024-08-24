#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int powerMod(int a, int b, int mod) {
    if(b == 0) {
        return 1;
    }

    int halfPowerMod = powerMod(a, b >> 1, mod);
    if(b & 1) {
        return (1ll * a * halfPowerMod * halfPowerMod) % mod;
    }
    else {
        return (1ll * halfPowerMod * halfPowerMod) % mod;
    }
}

int divmod(int a, int b, int mod) {
    return (1ll * a * powerMod(b, mod-2, mod)) % mod;
}


int main()
{
    int a, b;
    cout << divmod(a, b, 2) << "\n";

    return 0;
}