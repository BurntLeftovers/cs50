#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // voting preferrences are to be stored in the preferrences array, with 0 being voter 1-choice 1, and so on.
    // First check the votes of each voter, match the choices to the candidate name and store their preferences in the aray
    // should reject false names, etc. as false
    // next, loop through eachthrough each voter, repeating the above .
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through the preferences table, starting with preference rank 1 for each voter.
    // Check for votes for candidate 0, if there is a vote for that candidate and they are not eliminated, add 1 vote to candidate 0.
    // if that candidate has been eliminated then do nothing, move to next voter.
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // store the value of the majority vote count number in winner
    // Loop through candidate votes to check if any candidate has more than majority
    // If they do, print winner name. If not, return false, move on.
    int win = voter_count / 2;
    for (int i = 0; i <voter_count; i++)
    {
        if (candidates[i].votes > win)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // this function will store the initial lowest vote value in int min.
    // min will start at 0, then check all candidate vote counts if they match min, and not eliminated.
    // If not found, then min will move to 1, check again. 2, repeat until lowest vote is found.
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].eliminated == false && candidates[i].votes < min)
            {
                min = candidates[i].votes;
            }
        }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // tie vote is declared when all candidates have same vote count as min
    // Therefore, if the highest (top) vote and lowest (min) votes are the same, then election is a tie.
    // Set top as 0 for now, then Check the vote total of each candidate.
    // If any candidate has a vote higher than top vote, set that value as top. 
    // Then check the next candidate to see if their votes are higher, if yes, set new value, if not, do nothing.
    int top = 0;
    min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > top)
        {
            top = candidates[i].votes;
        }
    }
    // using similar logic to above function to find the min votes, but in reverse. (starting high, working down to min.)
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes < min && candidates[j].eliminated == false)
        {
            min = candidates[j].votes;
        }
    }
    if (min == top)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // check votes of all candidates who are not eliminated
    // if the votes for a candidate are the same as min, then that candidate should be eliminated.
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
