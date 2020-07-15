#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }


    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }

    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Variable for neater look when all candidates got zero votes
    int zero_votes = 0;

    //Array for storing winners of the election
    string winners[candidate_count];

    //By default 1st entry is a winner of the election if other candidates got less votes
    int cursor = 0;
    int winners_count = 1;
    
    //Variable for correct enumeration of new winner entries 
    int entry_count = 1;

    for (int i = 1; i <= candidate_count; i++)
    {

        if (candidates[cursor].votes < candidates[i].votes)
        {
            
            //Move cursor to the bigger votes candidate and add him to the winners list
            cursor = i;
            winners[entry_count] = candidates[i].name;
            entry_count++;

        }
        else
        {
            if (candidates[cursor].votes == candidates[i].votes)
            {
                //Increase number of winners and adds winner entry into the winners array;
                winners_count++;
                winners[entry_count] = candidates[i].name;
                entry_count++;
            }

            winners[0] = candidates[cursor].name;
        }
    }

    //Checking if all candidates got 0 votes
    for (int i = 0; i < candidate_count ; i++)
    {
        if (candidates[i].votes == 0)
        {
            zero_votes++;
        }
    }

    //More neater look when all candidates got 0 votes
    if (zero_votes != candidate_count)
    {
        for (int i = 0; i < winners_count; i++)
        {
            printf("%s\n", winners[i]);
        }
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
