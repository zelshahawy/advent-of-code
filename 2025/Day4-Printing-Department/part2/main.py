def max_rolls_removed(grid: list[list[str]]) -> int:
    R = len(grid)
    C = len(grid[0]) if R else 0

    dirs = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    already_removed: set[tuple[int, int]] = set()

    while True:
        being_removed: set[tuple[int, int]] = set()
        for i in range(R):
            for j in range(C):
                cell = grid[i][j]
                if cell != "@" or (i, j) in already_removed:
                    continue
                adjacent: int = 0
                for dr, dc in dirs:
                    rr, cc = i + dr, j + dc
                    if (
                        0 <= rr < R
                        and 0 <= cc < C
                        and grid[rr][cc] == "@"
                        and (rr, cc) not in already_removed
                    ):
                        adjacent += 1

                if adjacent < 4:
                    being_removed.add((i, j))

        if len(being_removed) == 0:
            break
        already_removed = already_removed.union(being_removed)
    return len(already_removed)


def main():
    input_grid: list[list[str]] = []
    with open("inputs.txt", "r") as file:
        for line in file:
            input_grid.append(list(line.strip()))
    print(max_rolls_removed(input_grid))


if __name__ == "__main__":
    main()
