pattern = '(.+AB((C|D*E)F)*G)'

moves = []
stack = []
prev = 0

for i, p in enumerate(pattern):
    moves.append([i+1])

    if p == '(':
        stack.append([i, []])

    if p == '|':
        moves[-1].pop()
        moves[stack[-1][0]].append(i+1)
        stack[-1][1].append(moves[-1])

    if p == '+':
        moves[-1].append(prev)

    if p == '*':
        moves[-1].append(prev)
        moves[prev].append(i)

    if p == ')':
        while stack[-1][1]:
            stack[-1][1].pop().append(i)
        prev = stack.pop()[0]
    else:
        prev = i


print('\n'.join(f'{i} -> {", ".join(map(str, j))}' for i, j in enumerate(moves)))
