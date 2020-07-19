# Accept the name of a HOUSE as a Command line arugment
# Query the student database
# Print to screen the FULL NAME, and Birth Year
# e.g. "Luna Lovegood, born 1981"
# 1 student per line
# ordered by last name in alphabetical order.
# if students share a last name, then order by first name

# sample command: python roster.py Gryffindor

import sys
from cs50 import SQL

# connecting the database for use in the app
db = SQL("sqlite:///students.db")

def main():
    # confirm command line argument, prompt use.
    if len(sys.argv) != 2:
        print ("Error. Usage: python roster.py <House Name>")
        exit(1)

    # set the variables, SQL query to take only the relevant data, set order by last name, then first name.
    # db.execute stores values in a list by default.
    house = sys.argv[1]
    house_list = db.execute("SELECT first, middle, last, birth FROM students WHERE house =? ORDER BY last, first", (house,))

    # print by looping through rows, making sure not to print the null middle name.
    for row in house_list:
        if row["middle"] == None:
            print (f'{row["first"]} {row["last"]} born {row["birth"]}')
        elif row["middle"] != None:
            print (f'{row["first"]} {row["middle"]} {row["last"]} born {row["birth"]}')

main()
