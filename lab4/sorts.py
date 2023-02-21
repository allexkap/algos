import sys
sys.stdout = open(f'{__file__.split("/")[-1].split(".")[0]}.in', 'w')

from random import randint, shuffle
n = 10**6

print(n)
# s = list(randint(10, 99) for _ in range(n))
s = list(range(n));
# s.reverse()
shuffle(s)
print(*s)
