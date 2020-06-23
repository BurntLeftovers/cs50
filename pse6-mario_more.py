from cs50 import get_int

# ask user to input height of pyramid Must be a positive value 1 - 8

def main():
    while True:
        height = get_int ("Height: ")
        if height > 1 and height < 9:
            break

    spaces = height - 1
    hashes = 1

# print the pyramid
    for i in range (height):
        print_spaces(spaces)
        print_hashes(hashes)
        print("  ", end="")
        print_hashes(hashes)
        print()
        spaces -= 1
        hashes += 1

# print functions
def print_spaces(spaces):
    for i in range(spaces):
        print (" ", end="")

def print_hashes(hashes):
    for i in range(hashes):
        print ("#", end="")

main()
