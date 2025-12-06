def apply_rotation(starting_position: int, rotation: str) -> int:
    direction, distance = rotation[0], int(rotation[1:])
    if direction == "L":
        new_position = (starting_position - distance) % 100
    else:
        new_position = (starting_position + distance) % 100
    
    return new_position


def main() -> int:
    res: int = 0
    starting_position: int = 50

    with open("./input.txt", "r") as input_file:
        curr_start = starting_position
        for rotation in input_file:
            curr_start = apply_rotation(curr_start, rotation.strip())
            if curr_start == 0:
                res += 1

    return res


if __name__ == "__main__":
    print(main())
