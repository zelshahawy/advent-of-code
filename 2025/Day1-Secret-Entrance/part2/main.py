def count_zero_hits(starting_position: int, direction: str, distance: int) -> int:
    p: int = starting_position

    if direction == "R":
        k0: int = (100 - p) % 100
    else:
        k0: int = p % 100

    if k0 == 0:
        k0 = 100

    if distance < k0:
        return 0

    return 1 + (distance - k0) // 100


def apply_rotation(starting_position: int, rotation: str) -> tuple[int, int]:
    direction, distance = rotation[0], int(rotation[1:])

    number_of_times_zero_ticked: int = count_zero_hits(starting_position, direction, distance)

    if direction == "R":
        new_position: int = (starting_position + distance) % 100
    else:
        new_position: int = (starting_position - distance) % 100

    return new_position, number_of_times_zero_ticked


def main() -> int:
    res: int = 0
    starting_position: int = 50

    with open("./input.txt", "r") as input_file:
        curr_start: int = starting_position
        for rotation in input_file:
            rotation = rotation.strip()
            if not rotation:
                continue

            curr_start, number_of_times_zero_ticked = apply_rotation(curr_start, rotation)
            res += number_of_times_zero_ticked

    return res


if __name__ == "__main__":
    print(main())
