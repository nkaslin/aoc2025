import re

import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp

from time import time

# Precompile regex for performance and clarity.
LINE_RE = re.compile(
    r"^\[([.#]+)\]\s*"  # pattern of . and #
    r"((?:\(\d+(?:,\d+)*\)\s*)+)"  # all (...) groups together
    r"\{(\d+(?:,\d+)*)\}\s*$"  # { ... }
)

# Regex to parse each individual (...) group
GROUP_RE = re.compile(r"\((\d+(?:,\d+)*)\)")


def parse_line(line: str):
    m = LINE_RE.match(line)
    if not m:
        return None

    lights = m.group(1)

    all_groups_raw = m.group(2)
    buttons = []
    for g in GROUP_RE.findall(all_groups_raw):
        buttons.append([int(x) for x in g.split(",")])

    joltages = [int(x) for x in m.group(3).split(",")]

    return {
        "lights": lights,
        "buttons": buttons,
        "joltages": joltages,
    }


def process_file(path):
    results = []
    with open(path, "r", encoding="utf-8") as f:
        for raw_line in f:
            line = raw_line.rstrip("\n")
            parsed = parse_line(line)
            if parsed is None:
                continue
            results.append(parsed)
    return results


def solve(buttons, joltages):
    n = len(joltages)
    m = len(buttons)

    c = np.ones(m, dtype=int)
    integrality = np.ones(m, dtype=int)
    bounds = Bounds([0 for _ in range(m)], [np.inf for _ in range(m)])

    A = []
    for button in buttons:
        Ai = [0 for i in range(n)]
        for x in button:
            Ai[x] = 1
        A.append(Ai)

    A = np.array(A).T
    b = np.array(joltages)

    constraints = LinearConstraint(A, lb=b, ub=b)

    sol = milp(
        c=c,
        integrality=integrality,
        bounds=bounds,
        constraints=constraints,
    )
    return int(sol.fun)


if __name__ == "__main__":
    data = process_file("in.txt")
    res = 0
    start = time()
    for processed_line in data:
        res += solve(processed_line["buttons"], processed_line["joltages"])
    print(f"time taken: {(time() - start) * 1000:.0f} ms")
    print(res)
