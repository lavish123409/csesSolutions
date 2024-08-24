import random as rd
import string

# for i in range(2, int(1e5)):
#     print("1 ", i, " 1")
#     print(i, "100000 1")

# for i in range(1, int(1e5)+1):
#     print(int(1e9), end=' ')

# for i in range(1, 1001):
#     if rd.choice([0, 1]):
#         print("1 " + str(rd.randrange(1, int(1e5))) + " " + str(rd.randrange(1, int(1e9))))
#     else:
#         print("2 " + str(rd.randrange(1, int(1e5))))

# generating all possible pairs
# for i in range(1, 6):
#     for j in range(1, i+1):
#         print(j, i)

# generating random strings
# for i in range(1000):
#         ls = rd.randrange(1, 1000, 1)
#         print(''.join(rd.choices(string.ascii_lowercase, k=ls)))

for i in range(int(1e5)):
    print("a", end='')