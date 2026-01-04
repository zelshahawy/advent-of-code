import math


def read_grid(path: str) -> list[str]:
    with open(path, "r") as f:
        lines = [line.rstrip("\n") for line in f]

    width = max(len(line) for line in lines)
    lines: list[str] = [line.ljust(width) for line in lines]
    print(lines[0])
    return lines


def is_blank_column(grid: list[str], c: int) -> bool:
    return all(row[c] == " " for row in grid)


def split_problems(grid: list[str]) -> list[tuple[int, int]]:
    width = len(grid[0])
    problems: list[tuple[int, int]] = []

    c = 0
    while c < width:
        if is_blank_column(grid, c):
            c += 1
            continue

        start = c
        while c < width and not is_blank_column(grid, c):
            c += 1
        end = c  # [start, end)
        problems.append((start, end))

    return problems


def column_number(grid: list[str], col: int) -> int:
    digits = []
    for r in range(len(grid) - 1):
        ch = grid[r][col]
        if ch.isdigit():
            digits.append(ch)

    return int("".join(digits))


def eval_problem(grid: list[str], start: int, end: int) -> int:
    op_row = grid[-1]

    ops = {op_row[c] for c in range(start, end) if op_row[c] in {"+", "*"}}
    assert len(ops) == 1
    op = next(iter(ops))

    nums: list[int] = []
    for c in range(end - 1, start - 1, -1):
        nums.append(column_number(grid, c))

    if op == "+":
        return sum(nums)
    else:
        return math.prod(nums)


def main():
    grid = read_grid("inputs.txt")
    problems = split_problems(grid)

    total = 0
    for start, end in problems:
        total += eval_problem(grid, start, end)

    print(total)


if __name__ == "__main__":
    main()
