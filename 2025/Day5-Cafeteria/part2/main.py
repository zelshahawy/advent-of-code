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


def main():
    sum: int = 0
    intervals: list[tuple[int, int]] = []
    with open("intervals.txt", "r") as file:
        for line in file:
            curr_l_and_r: list[str] = line.strip().split("-")
            intervals.append((int(curr_l_and_r[0]), int(curr_l_and_r[1])))

    merged_intervals: list[tuple[int, int]] = merge_intervals(intervals)
    for interval in merged_intervals:
        l, r = interval
        sum += r - l + 1
    print(sum)


if __name__ == "__main__":
    main()
