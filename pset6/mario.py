from cs50 import get_int
lines = 10
# get the lines argument
while lines <= 0 or lines > 8:
    lines = get_int("How many Lines (1 - 8)\n")

lin = 1
# loop of the number of lines
while lin < (lines + 1):
    col = 1
    # print the initials spaces
    while col <= (lines - lin):
        print(" ", end="")
        col = col + 1
    # Print initial #
    while col <= lines:
        print("#", end="")
        col = col + 1
    print("  ", end="")
    col = 1
    # Print the finals #
    while col < (lin + 1):
        print("#", end="")
        col = col + 1
    print()
    lin = lin + 1