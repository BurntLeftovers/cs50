# IMPORT the data from characters.csv as a command line argument
# Store the data in the students DB after doing some basic processing
# DB should have 5 header fields:
# First name, Middle Name, Last Name, House, Birth
# If the student has no middle name, set as NULL
import csv
import sys
import re
from cs50 import SQL

# setting global variables for use in the app
db = SQL("sqlite:///students.db")

def main():
    if len(sys.argv) != 2:
        print ("Error. Usage: python import.py characters.csv")
        exit(1)

# open characters.csv in read mode
    with open (sys.argv[1], "r") as file:
        chars_dict = csv.DictReader(file)
        count = 0
# read the file line-by-line
        for row in chars_dict:
            # set name variables, and split up the name into a list for adding to the DB
            name = row["name"]
            name_list = name.split()

            # set insert to db based on the presence of middle name or not. In this case, no middle name
            if len(name_list) == 2:
                first_name = name_list[0]
                last_name = name_list[1]
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first_name, None, last_name, row["house"], row["birth"])

            # adding middle name-having people with their middlenames.
            elif len(name_list) == 3:
                first_name = name_list[0]
                middle_name = name_list[1]
                last_name = name_list[2]
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first_name, middle_name, last_name, row["house"], row["birth"])
main()
