def find_sum_rolls(grid: list[list[str]]) -> int:
    R = len(grid)
    C = len(grid[0]) if R else 0
    sum: int = 0

    dirs = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    for i in range(R):
        for j in range(C):
            cell = grid[i][j]
            if cell != "@":
                continue
            adjacent: int = 0
            for dr, dc in dirs:
                rr, cc = i + dr, j + dc
                if 0 <= rr < R and 0 <= cc < C and grid[rr][cc] == "@":
                    adjacent += 1

            if adjacent < 4:
                sum += 1
    return sum


def main():
    input_grid: list[list[str]] = []
    with open("inputs.txt", "r") as file:
        for line in file:
            input_grid.append(list(line.strip()))
    print(find_sum_rolls(input_grid))


if __name__ == "__main__":
    main()
