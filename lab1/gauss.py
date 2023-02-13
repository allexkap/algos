import sys
sys.stdin = open(f'{__file__.split("/")[-1].split(".")[0]}.in')

n, m = map(int, input().split())
Matrix = list(list(map(int, input().split())) for _ in range(n))

for k in range(n):
    for i in range(k+1, n):
        f = Matrix[i][k]/Matrix[k][k]
        for j, e in enumerate(Matrix[k]):
            Matrix[i][j] -= e*f
for i in range(n-1, -1, -1):
    for j in range(i+1, n):
        Matrix[i][m-1] -= Matrix[j][m-1]*Matrix[i][j]
    Matrix[i][m-1] /= Matrix[i][i]

print(*(Matrix[i][-1] for i in range(n)), sep=' ')
