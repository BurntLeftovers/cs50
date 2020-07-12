import csv
import sys
import re
import collections

def main():
    # get instructions from Command-Line Arguments using sys
    # usage: python dna.py databases/small.csv sequences/1.txt (should output "Bob")
    # Throw error message and exit if args not valid    
    if len(sys.argv) != 3:
        print ("Error. Usage: python dna.py database/x.csv sequences/x.txt")
        exit(1)
        
    # Setting variable for printing "No Match" by default here for access within for loop
    match_check = False

    # Read the csv file into memory, CSV is basically a table Also open the TXT file and read the data to memory.
    # CSV Top line shows headers: Name, then the different types of STRs (sequences) in the file, Rows below show name, then count of those STRs
    dbFile = open (sys.argv[1], "r")
    with open (sys.argv[2], "r") as txtFile:
        sequence = txtFile.read()

    # Read the first line of the csv, store each item as a separate variable. For loop is there to remove the whitespace at the end. Probably not very efficient but it works.
    temp = re.split(",", dbFile.readline())
    header = []
    for element in temp:
        header.append(element.strip())
    # print (header)

    # Open the CSV file, read the number of STR columns and store that value in STRs, that will help is identify the bad guy.
    # couldn't figure out how to run the lines function without blocking the rest of the function, so we're reading twice, boys! #efficiency.
    with open (sys.argv[1], "r") as file:
        dna_dict = csv.DictReader(file)
        STRs = len(dna_dict.fieldnames)-1
        # print (f"STR count: {STRs}")

    # Read the file into a dict. Actually a Sequence of Dicts. Each row is it's own dictionary. Bit confusing, but it just means an extra layer of looping...
    with open (sys.argv[1], "r") as file:
        dna_dict = csv.DictReader(file)
        
        # Loop through each item in the dicitonary and put those values into the re.search function.
        # Check each DNA match, if successful keep going. If all DNA sequences match then that's the person.
        for row in dna_dict:
            # Setting variable defaults to 0 for clean results
            count = 0
            check = 0
            for key, value in row.items():
                # Setting variables, skipping the first line of the file from the scan function.
                count = count + 1
                if count == 1:
                    name = value
                    continue
                # print (key, value, name, count)
                # setting pattern for checking if the longest STR string matches any STR string in the sequence file.
                pattern = "(%s){%s}" % (key, value)
                # check function to eliminate false-positives where STR count is actually higher than in main search-match function.
                value_check = int(value) + 1
                pattern_check = "(%s){%s}" % (key, value_check)
                match_check = re.search(pattern_check, sequence)
                if match_check:
                    # print (f"{name} Not matched")
                    break
                # Check if STR sequence length and individual maxes match, if yes, continue loop.
                match = re.search(pattern, sequence)
                # print (match)
                if match:
                    check = check + 1
                    # if all STRs have been checked, this must be the bad guy.
                    if check == STRs:
                        match_check = True
                        print (f"DNA Matches {name}")
                #Need to keep this else function at the end otherwise it seems to break the above if statements
                else:
                    # print (f"Not Matched")
                    break
        # Print function at the end for if we complete the loop and there was no match.
        if match_check == False:
            print ("No Match")
        else:
            exit
main()
