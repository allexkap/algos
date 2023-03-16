def getTransitions(pattern):
    transitions = []
    stack = []
    prev = 0

    for i, p in enumerate(pattern):
        transitions.append([i+1])

        match p:
            case '(':
                stack.append([i, []])    
            case '|':
                transitions[-1].pop()
                transitions[stack[-1][0]].append(i+1)
                stack[-1][1].append(transitions[-1])
            case '?':
                transitions[-1].append(i)
            case '+':
                transitions[-1].append(prev)
            case '*':
                transitions[-1].append(prev)
                transitions[prev].append(i)
            case ')':
                while stack[-1][1]:
                    stack[-1][1].pop().append(i)
                prev = stack.pop()[0]
                continue
        prev = i

    return transitions


pattern = '(.+AB((C|D*E)F)*G)'
transitions = getTransitions(pattern)
print('\n'.join(f'{i} -> {", ".join(map(str, j))}' for i, j in enumerate(transitions)))
