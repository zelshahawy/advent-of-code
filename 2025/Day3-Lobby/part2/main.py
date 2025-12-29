def max_voltage(bank: str, to_keep: int) -> int:
    bank = bank.strip()
    n = len(bank)
    to_remove = n - to_keep
    if to_remove <= 0:
        return int(bank) if bank else 0

    stack: list[int] = []
    for ch in bank:
        volt: int = int(ch)
        while to_remove > 0 and stack and volt > stack[-1]:
            _ = stack.pop()
            to_remove -= 1
        stack.append(volt)

    if to_remove > 0:
        stack = stack[:-to_remove]

    stack = stack[:to_keep]

    return int("".join([str(d) for d in stack]))


def main():
    sum: int = 0
    with open("inputs.txt", "r") as file:
        for line in file:
            sum += max_voltage(line, 12)
    print(sum)


if __name__ == "__main__":
    main()
