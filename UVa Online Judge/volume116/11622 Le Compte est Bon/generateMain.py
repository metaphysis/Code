import argparse
import itertools
import sys
from collections import Counter
from functools import lru_cache

Numbers = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 50, 75, 100)
TargetMax = 8000
FiveLimit = 800000
ValueLimit = 10 ** 18
Factorial = (1, 1, 2, 6, 24, 120, 720)

sys.setrecursionlimit(1000000)

@lru_cache(maxsize=None)
def makeSplits(state):
    size = len(state)
    result = []
    used = set()
    for mask in range(1, (1 << size) - 1):
        left = tuple(state[i] for i in range(size) if mask & (1 << i))
        right = tuple(state[i] for i in range(size) if not (mask & (1 << i)))
        if left > right:
            left, right = right, left
        pair = (left, right)
        if pair in used:
            continue
        used.add(pair)
        result.append(pair)
    return tuple(result)

def addValue(values, value, limit):
    if 0 < value <= limit:
        values.add(value)

@lru_cache(maxsize=None)
def getValues(state):
    size = len(state)
    if size == 1:
        return frozenset((state[0],))
    limit = FiveLimit if size == 5 else ValueLimit
    values = set()
    for left, right in makeSplits(state):
        leftValues = getValues(left)
        rightValues = getValues(right)
        for first in leftValues:
            for second in rightValues:
                addValue(values, first + second, limit)
                addValue(values, first * second, limit)
                if first > second:
                    addValue(values, first - second, limit)
                elif second > first:
                    addValue(values, second - first, limit)
                if first >= second and first % second == 0:
                    addValue(values, first // second, limit)
                if second > first and second % first == 0:
                    addValue(values, second // first, limit)
    return frozenset(values)

def addExactTargets(state, reachable):
    for left, right in makeSplits(state):
        leftValues = getValues(left)
        rightValues = getValues(right)
        for first in leftValues:
            for second in rightValues:
                value = first + second
                if value <= TargetMax:
                    reachable |= 1 << value
                value = first * second
                if value <= TargetMax:
                    reachable |= 1 << value
                if first > second:
                    value = first - second
                    if value <= TargetMax:
                        reachable |= 1 << value
                elif second > first:
                    value = second - first
                    if value <= TargetMax:
                        reachable |= 1 << value
                if first >= second and first % second == 0:
                    value = first // second
                    if value <= TargetMax:
                        reachable |= 1 << value
                if second > first and second % first == 0:
                    value = second // first
                    if value <= TargetMax:
                        reachable |= 1 << value
    return reachable

@lru_cache(maxsize=None)
def getReachable(state):
    size = len(state)
    reachable = 0
    if size == 1:
        value = state[0]
        if value <= TargetMax:
            reachable |= 1 << value
        return reachable
    used = set()
    for i in range(size):
        if state[i] in used:
            continue
        used.add(state[i])
        subState = state[:i] + state[i + 1:]
        reachable |= getReachable(subState)
    if size < 6:
        values = getValues(state)
        for value in values:
            if value <= TargetMax:
                reachable |= 1 << value
    else:
        reachable = addExactTargets(state, reachable)
    return reachable

def getWeight(state):
    counter = Counter(state)
    divisor = 1
    for count in counter.values():
        divisor *= Factorial[count]
    return Factorial[6] // divisor

def buildAnswers():
    answers = [0] * (TargetMax + 1)
    allStates = itertools.combinations_with_replacement(Numbers, 6)
    total = 0
    for stateIndex, state in enumerate(allStates, 1):
        reachable = getReachable(state)
        weight = getWeight(state)
        for target in range(1, TargetMax + 1):
            if reachable & (1 << target):
                answers[target] += weight
        total += 1
        if stateIndex % 1000 == 0:
            print("processed {}/{} states".format(stateIndex, 27132), file=sys.stderr)
    print("total states: {}".format(total), file=sys.stderr)
    return answers

def writeCpp(outputName, answers):
    with open(outputName, "w", encoding="ascii") as output:
        output.write("#include <bits/stdc++.h>\n")
        output.write("using namespace std;\n\n")
        output.write("const int answers[8001] = {\n")
        for begin in range(0, len(answers), 12):
            end = min(begin + 12, len(answers))
            line = ", ".join(str(value) for value in answers[begin:end])
            if end < len(answers):
                line += ","
            output.write("    " + line + "\n")
        output.write("};\n\n")
        output.write("int main() {\n")
        output.write("    ios::sync_with_stdio(false);\n")
        output.write("    cin.tie(nullptr);\n")
        output.write("    int caseCount, target;\n")
        output.write("    cin >> caseCount;\n")
        output.write("    while (caseCount--) {\n")
        output.write("        cin >> target;\n")
        output.write("        cout << answers[target] << '\\n';\n")
        output.write("    }\n")
        output.write("    return 0;\n")
        output.write("}\n")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", default="solution.cpp")
    args = parser.parse_args()
    answers = buildAnswers()
    if answers[1] != 7529536:
        raise RuntimeError("target 1 result is incorrect: {}".format(answers[1]))
    if answers[8000] != 5838170:
        raise RuntimeError("target 8000 result is incorrect: {}".format(answers[8000]))
    writeCpp(args.output, answers)
    print("generated {}".format(args.output), file=sys.stderr)
    print("answers[1] = {}".format(answers[1]), file=sys.stderr)
    print("answers[8000] = {}".format(answers[8000]), file=sys.stderr)

if __name__ == "__main__":
    main()
