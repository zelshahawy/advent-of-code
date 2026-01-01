import math

def parse_columns(input_line, all_columns: list[list[int | str]]):
    numbers = input_line.split(" ")
    filtered_numbers = [number for number in numbers if number]
    if not all_columns:
        for _ in range(len(filtered_numbers)):
            all_columns.append([])

    for target_column in range(len(filtered_numbers)):
        number_or_symbol: int | str = filtered_numbers[target_column]
        if number_or_symbol.isdigit():
            all_columns[target_column].append(int(number_or_symbol))
        else:
            all_columns[target_column].append(number_or_symbol)

def caulcate_total(all_columns: list[list[int]]):
    total: int = 0
    for column in all_columns:
        symbol: str = column[-1]
        column_values: list[int] = column[:-1]
        
        if symbol == "+":
            total += sum(column_values)
        elif symbol == "*":
            total += math.prod(column_values)

    return total

def main():
    all_columns: list[list[int | str]] = []
    with open("inputs.txt", "r") as input_file:
        for input_line in input_file:
            parse_columns(input_line.strip(), all_columns)

    total = caulcate_total(all_columns)
    print(total)


if __name__ == "__main__":
    main()
