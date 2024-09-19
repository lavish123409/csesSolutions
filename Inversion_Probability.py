import decimal

n = int(input())
r = list(map(int, input().split()))
ans = decimal.Decimal(0.0)

for i in range(n):
    for j in range(i):
        cans = decimal.Decimal(0.0)
        if r[j] <= r[i]:
            # cans += (r[j] * (r[j] - 1)) / 2
            pairs = decimal.Decimal(r[j])
            rjm1 = r[j] - 1
            pairs.fma(rjm1, 0.0)
            pairs.fma(0.5, 0.0)
            cans.fma(1.0, pairs)
        else:
            # cans += (r[i] * (r[i] - 1)) / 2
            # cans += ((r[j] - r[i]) * r[i])
            cans.fma(1.0, (r[i] * (r[i] - 1)) / 2)
            cans.fma(1.0, ((r[j] - r[i]) * r[i]))

        # ans += ((cans / r[i]) / r[j])
        cans.fma(1.0 / r[i], 0.0)
        cans.fma(1.0 / r[j], 0.0)
        ans = ans.fma(1, cans)

print(round(ans, 6))
print("{:.6f}".format(ans))