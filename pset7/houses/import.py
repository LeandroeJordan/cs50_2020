# TODO
from cs50 import SQL
from sys import argv, exit
import csv
db = SQL("sqlite:///students.db")


def main():
    # get a csv file information
    if len(argv) != 2:
        print("You must Enter: Ex: python import.py houses/characters.csv")
        exit(1)
    # open the csv file
    csv_students_data = argv[1]
    with open(csv_students_data) as student_data:
        cursor_stu = csv.DictReader(student_data)
        # read etch line in csv file
        for row in cursor_stu:
            stu_name = str(row["name"])
            print(stu_name.count(" "))
            stu_fname = stu_name.split(" ", 1)[0]
            # test middle name
            if stu_name.count(" ") == 2:
                stu_mname = stu_name.split(" ", 3)[1]
                stu_lname = stu_name.split(" ", 3)[2]
            else:
                stu_lname = stu_name.split(" ", 3)[1]
                stu_mname = None
            stu_house = stu_name = str(row["house"])
            stu_birth = stu_name = str(row["birth"])
            # persist data into students
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       stu_fname, stu_mname, stu_lname, stu_house, stu_birth)


main()

