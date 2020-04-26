#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int i, n, p, text_length, count_letters, count_sentences;
float average_letters, average_sentences, grade;

int main(void)
{
    string text = get_string("Text: ");
    text_length = strlen(text);
    int count_words = 1;
    // goal of program is to output the reading grade of the text provided by the user using the below forumula.
    // index = 0.0588 * L - 0.296 * S - 15.8.
    // L = average number of letters per 100 words.
    // S = aveage number of sentences per 100 words.
    // Need to be able to perform the following:
    // Count number of readable characters in a text.
    // Identify and count individual words (i.e. identify where spaces are)
    // Count the number of sentences (i.e. identify full stops)

    // This loop will cycle through each character of the array and return the count of letters.
    for (p = 0; p < text_length; p++)
    {
        if ((text[p] >= 'a' && text[p] <= 'z') || (text[p] >= 'A' && text[p] <= 'Z'))
        {
            count_letters ++;
        }
    }
    // This loop is the same as above, will return word count based on spaces
    for (i = 0; i < text_length; i++)
    {
        if (text[i] == ' ')
        {
            count_words ++;
        }
    }
    // This loop is the same as above, will return sentence count based on full stops and other characters
    for (n = 0; n < text_length; n++)
    {
        if (text[n] == '.' || text[n] == '!' || text[n] == '?')
        {
            count_sentences ++;
        }
    }
    // Setting the average values
    average_sentences = (float)count_sentences / ((float)count_words / 100);
    average_letters = (float)count_letters / ((float)count_words / 100);

    // This will process the readability score.
    // index = 0.0588 * L - 0.296 * S - 15.8.
    grade = (0.0588 * average_letters) - (0.296 * average_sentences) - 15.8;
    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade <= 16)
    {
        printf("Grade %.0f\n", grade);
    }
    else if (grade > 17)
    {
        printf("Grade 16+\n");
    }
    // commenting out the below confirmation steps and moving to bottom.
    // printf ("Letters: %i\nWords:   %i\nSentences: %i\n", count_letters, count_words, count_sentences);
    // printf ("%.2f\n%.2f\n", average_sentences, average_letters);
}
