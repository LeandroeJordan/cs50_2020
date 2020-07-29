# TODO
from cs50 import SQL
from sys import argv, exit
import csv
db = SQL("sqlite:///students.db")


def main():
    if len(argv) != 2:
        print("You must Enter: Ex: python import.py 'student House'")
        exit(1)
    # select in the dabta base
    input_house = argv[1]
    cursor_stu = db.execute("select first, middle , last, birth from students where house=? order by last, first ", input_house)
    # read the cursor
    for row in cursor_stu:
        stu_first, stu_middle, stu_last, stu_birth = row['first'], row['middle'], row['last'], row['birth']
        print(f"{stu_first} {stu_middle + ' ' if stu_middle else ''}{stu_last}, born {stu_birth}")


main()