def merge_intervals(intervals: list[tuple[int, int]]) -> list[tuple[int, int]]:
    if not intervals:
        return []

    intervals.sort(key=lambda x: x[0])

    merged: list[tuple[int, int]] = []
    cur_l, cur_r = intervals[0]

    for li, r in intervals[1:]:
        if li <= cur_r:
            cur_r = max(cur_r, r)
        else:
            merged.append((cur_l, cur_r))
            cur_l, cur_r = li, r

    merged.append((cur_l, cur_r))
    return merged


def in_intervals(intervals: list[tuple[int, int]], val: int) -> bool:
    for interval in intervals:
        left, right = interval
        if left <= val <= right:
            return True
    return False


def main():
    fresh_count: int = 0
    intervals: list[tuple[int, int]] = []
    with open("intervals.txt", "r") as file:
        for line in file:
            curr_l_and_r: list[str] = line.strip().split("-")
            intervals.append((int(curr_l_and_r[0]), int(curr_l_and_r[1])))

    merged_intervals = merge_intervals(intervals)
    with open("inputs.txt", "r") as file:
        for line in file:
            curr_number: int = int(line.strip())
            if in_intervals(merged_intervals, curr_number):
                fresh_count += 1
    print(fresh_count)


if __name__ == "__main__":
    main()
