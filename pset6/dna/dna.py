from sys import argv, exit
import csv

# Count the max number of reptetions


def solve_max_repeat(cursor_str, str):
    array_max_rep = [0] * len(cursor_str)
    for i in range(len(cursor_str) - len(str), -1, -1):
        if cursor_str[i: i + len(str)] == str:
            if i + len(str) > len(cursor_str) - 1:
                array_max_rep[i] = 1
            else:
                array_max_rep[i] = 1 + array_max_rep[i + len(str)]
    return max(array_max_rep)


def main():
    # get a csv file information
    if len(argv) != 3:
        print("You must Enter: Ex: python dna.py databases/large.csv sequences/19.tx")
        exit(1)
    # open a data Base CSV
    csv_data_base_dna = argv[1]
    with open(csv_data_base_dna) as dna_data:

        cursor_data = csv.reader(dna_data)
        strs_line = next(cursor_data)[1:]  # get lines of strs sequence

        # get information from txt
        txt_str_data = argv[2]
        with open(txt_str_data) as txt_str:
            cursor_str = txt_str.read()
            max_repeat = []
            for str in strs_line:
                max_repeat.append(solve_max_repeat(cursor_str, str))

        # check if match and return the of person
        values = []
        for tupla in cursor_data:
            values = []
            name = tupla[0]
            # get a line in data base csv
            for value in tupla[1:]:
                values.append(int(value))

            if values == max_repeat:
                print(name)
                return

        print("No match")


main()
