# Game 1: 4 red, 5 blue, 9 green; 7 green, 7 blue, 3 red; 16 red, 7 blue, 3 green; 11 green, 11 blue, 6 red; 12 red, 14 blue


def parse_maxes(line: str) -> tuple[int, int, int, int]:
    """
    Return (max_red, max_blue, max_green and ID) seen in any single reveal.
    """
    max_red = max_blue = max_green = 0

    colon_position = line.find(":")
    game_id = int(line.split(":")[0].split()[1])
    assert colon_position != -1

    reveals = line[colon_position + 1 :].strip().split(";")
    for reveal in reveals:
        r = b = g = 0
        for part in reveal.strip().split(","):
            num_s, color = part.strip().split()
            num = int(num_s)
            if color == "red":
                r += num
            elif color == "blue":
                b += num
            elif color == "green":
                g += num
        max_red = max(max_red, r)
        max_blue = max(max_blue, b)
        max_green = max(max_green, g)

    return max_red, max_blue, max_green, game_id


def game_id_is_feasible(line: str) -> int:
    """
    returns 0 if unfeasible and game id if feasible
    """
    red, blue, green, game_id = parse_maxes(line)
    if red <= 12 and blue <= 14 and green <= 13:
        return game_id
    return 0


def main():
    sum: int = 0
    with open("inputs.txt", "r") as file:
        for line in file:
            sum += game_id_is_feasible(line)
    print(sum)


if __name__ == "__main__":
    main()
