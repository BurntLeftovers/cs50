# Program should return Amex, Mastercard, Visa, or Invalid after running checks on a credit card number provided by users
# There are 2 checks - first is the checksum: is it a valid credit card number
# second is validation - does it conform to the pattern of one of the 3 card companies

from cs50 import get_string
from cs50 import get_int
import math
import numpy

def main():
    card = get_int("Number: ")
    checksum(card)

def checksum(card):
# take number and turn it into the pieces that we need, check run the checksum calculation to see that it's OK.
# setting array to put individual card numbers into, and the length of the card
    numbers = []
    string = str(card)
    top = len(string)
    # loop through each number and separate it into an array - Thanks https://stackoverflow.com/a/21270442/13573982
    numbers = [(card//(10**i))%10 for i in range(math.ceil(math.log(card, 10))-1, -1, -1)]
    # funky new notation for printing every second element in the list! Python got cool features.

    # Split the list into 2 based on odds and evens
    # need to take every other element in a list (starting with the second last) and multiply each number by 2, add them up
    # then, add up all the other numbers that were not part of the first loop.
    # If the total ends in 0 then it is a valid number.
    odds = numbers[0::2]
    evens = numbers[1::2]
    # setting checksum to INVALID as default
    check_one = 1
    # find second-to-last character in the string
    decider = top-1
    # branching the addition based on the second-last digit using IF 
    if decider %2 == 0:
        # multiply the digits by 2, then adding the total with the total of the other numbers
        interim = [i * 2 for i in evens]
        # convert it to a string (x), then split it back out into a list (multiple) so we can handle double digits
        x = ''.join(map(str, interim))
        multiple = list(map(int, x))
        # add em together
        total = (numpy.sum(multiple))+numpy.sum(odds)
        
        # print the result
        if total%10 == 0: # VALID NUMBER
            check_one = 0
        elif total%10 != 0:
            print ("INVALID")

    else:
        # multiply the digits by 2, then adding the total with the total of the other numbers
        interim = [i * 2 for i in odds]
        # convert it to a string (x), then split it back out into a list (multiple) so we can handle double digits
        x = ''.join(map(str, interim))
        multiple = list(map(int, x))
        # add em together
        total = (numpy.sum(multiple))+numpy.sum(evens)

        # print the result
        if total%10 == 0:
            check_one = 0 # VALID NUMBER
        elif total%10 != 0:
            print ("INVALID")

    # also need to check the first few digits, and number of digits, to see which type of card it might be.
    # Amex = 15-digits, starts with 34 or 37
    if (check_one == 0) and (top == 15) and (string[0] == '3') and (string[1] == '7' or string[1] == '4'):
        print ("AMEX")
    # Mastercard = 16-digits, starts with 51, 52, 53, 54, or 55
    elif (check_one == 0) and (top == 16) and (string[0] == '5') and (string[1] == '1' or string[1] == '2' or string[1] == '3' or string[1] == '4' or string[1] == '5'):
        print ("MASTERCARD")
    # Visa = 13- and 16-digit numbers
    elif (check_one == 0) and (top == 13 or top == 16) and (string[0] == '4'):
        print ("VISA")
    else:
        print ("INVALID")

main()
