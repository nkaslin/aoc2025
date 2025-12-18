from shapely import Polygon, intersection
from time import time

def read_input(path):
    points = []
    with open(path, "r", encoding="utf-8") as f:
        for raw_line in f:
            line = raw_line.rstrip("\n")
            x, y = line.split(",")
            points.append((int(x), int(y)))
    return points


def solve(points):
    n = len(points)

    poly = Polygon(shell=points)

    res = 0

    for i in range(n):
        for j in range(i+1, n):
            c1 = (points[i][0], points[i][1])
            c2 = (points[i][0], points[j][1])
            c3 = (points[j][0], points[i][1])
            c4 = (points[j][0], points[j][1])
            square = Polygon(shell=[c1, c2, c4, c3])
            area = square.area
            if abs(area - intersection(poly, square).area) < 1e-6:
                res = max(res, (abs(points[i][0] - points[j][0]) + 1) * (abs(points[i][1] - points[j][1]) + 1))

    print(res)

if __name__ == "__main__":
    points = read_input("../in.txt")
    start = time()
    solve(points)
    print(f"time taken: {(time() - start) * 1000:.0f} ms")
