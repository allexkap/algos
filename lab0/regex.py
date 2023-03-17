def getTransitions(pattern):
    transitions = []
    stack = []
    prev = 0

    for i, p in enumerate(pattern):
        transitions.append([-1, i+1])

        match p:
            case '(':
                stack.append([i, []])
            case '|':
                transitions[-1].pop()
                transitions[stack[-1][0]].append(i+1)
                stack[-1][1].append(transitions[-1])
            case '?':
                transitions[-2].append(i)
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
            case p if p.isalpha() or p == '.':
                transitions[-1].pop(0)
        prev = i

    return transitions


def setState(i, states, transitions):
    if i in states:
        return
    states.add(i)
    if i >= len(transitions):
        return
    for j in transitions[i][1:]:
        setState(j, states, transitions)


def match(pattern, string):
    transitions = getTransitions(pattern)
    states = set()

    eps = {i for i, t in enumerate(transitions) if t[0] < 0}
    end = {len(pattern)}

    setState(0, states, transitions)
    states -= eps

    for ch in string:
        prev = states - end
        states = set()
        for i in prev:
            if ch == pattern[i] or pattern[i] == '.':
                setState(transitions[i][0], states, transitions)
        states -= eps
        print(ch, ' ->', *(p if i in states else ' ' for i, p in enumerate(pattern)), sep='')

    return not states.isdisjoint(end)



pattern = '(.?AB((C|D*E)F)*G)'
transitions = getTransitions(pattern)
print('\n'.join(f'{i} -> {", ".join(map(str, j))}' for i, j in enumerate(transitions)))

result = match(pattern, 'QABCFDDEFG')
print(result)
