def max_voltage(bank: str) -> int:
    """
    Given a bank of batteries represented by a string of digits,
    find the maximum voltage possible with two batteries
    """
    n = len(bank)
    if n < 2:
        return 0

    def get_suffix_maxes() -> list[int]:
        """
        Given a number, get the the largest digit you can find starting
        at index i and going to the end.
        """

        suff_max: list[int] = [0] * len(bank)
        suff_max[-1] = int(bank[-1])

        for i in range(len(bank) - 2, -1, -1):
            suff_max[i] = max(suff_max[i + 1], int(bank[i]))

        return suff_max

    suff_volts: list[int] = get_suffix_maxes()
    best_tens: int = 0
    result: int = 0
    for i in range(n - 1):
        curr_volt: int = int(bank[i])
        if curr_volt > best_tens:
            best_tens = int(curr_volt)
            result = best_tens * 10 + suff_volts[i + 1]

    return result


def main():
    sum: int = 0
    with open("input.txt", "r") as file:
        for line in file:
            sum += max_voltage(line.strip())
    print(sum)


if __name__ == "__main__":
    main()
