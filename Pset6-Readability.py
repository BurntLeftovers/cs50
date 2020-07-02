# recreate Readability from wk 2
# Algorithm: 0.0588 * L - 0.296 * S - 15.8
# where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

from cs50 import get_string
import re

def main():
    # get text from user
    text = get_string ("Text: ")
    # call the grade function, return score
    score = grade(text)
    # print score based on grade, handle edge cases, etc.
    output(score)

def grade(text):
    # do the calculation using the algorithm
    # setting the variables:
    text_length = len(text)

    count_letters = 0
    for character in text:
        if character.isalnum():
            count_letters += 1

    # need to convert this output from list into an int
    count_words = len(text.split())

    # need to convert this output from list into an int (Had to add  minus 1 to the end because it was adding 1 extra for some reason?)
    count_sentences = len(re.split('[.!?]', text))-1

    average_sentences = count_sentences / (count_words / 100);
    average_letters = count_letters / (count_words / 100);
    grade = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;

    # Commenting out print-tests for debugging.
    # print (f"Length: {text_length}")
    # print (f"Letters: {count_letters}")
    # print (f"Words: {count_words}")
    # print (f"Sentences: {count_sentences}")
    # print (f"Avg Sentences: {average_sentences}")
    # print (f"Avg Letters: {average_letters}")
    # print (f"Grade: {grade}")

    return grade

def output(score):
    #handle all the edge cases, such as 0, -1, 16+, etc.
    if score <1:
        print ("Before Grade 1")
    elif score >1 and score <16:
        print (f"Grade: {round(score)}")
    elif score >16:
        print (f"Grade: 16+")

main()
