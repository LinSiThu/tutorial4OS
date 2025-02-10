#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "questions.h"

// Define categories and questions ONLY in this file
char categories[NUM_CATEGORIES][MAX_LEN] = {
    "history", 
    "geography", 
    "pop culture"
    
    
};

struct question questions[NUM_QUESTIONS];  // Defined only once

// Converts a string to lowercase and removes trailing newline
void clean_input(char *str) {
    int len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0'; // Remove newline
    }
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]); // Convert to lowercase
    }
}

// Initializes the array of questions for the game
// Initializes the array of questions for the game
void initialize_game(void)
{
    // History Questions
    strcpy(questions[0].category, "history");
    strcpy(questions[0].question, "What year did WW2 End?");
    strcpy(questions[0].answer, "1945");
    questions[0].value = 100;
    questions[0].answered = false;

    strcpy(questions[1].category, "history");
    strcpy(questions[1].question, "Who killed JFK?");
    strcpy(questions[1].answer, "Lee Harvey Oswald");
    questions[1].value = 200;
    questions[1].answered = false;

    // geography Questions
    strcpy(questions[2].category, "geography");
    strcpy(questions[2].question, "What is the capital of Sweden?");
    strcpy(questions[2].answer, "Stockholm");
    questions[2].value = 100;
    questions[2].answered = false;

    strcpy(questions[3].category, "geography");
    strcpy(questions[3].question, "Which country has the well known museum called Hermitage ?");
    strcpy(questions[3].answer, "Russia");
    questions[3].value = 200;
    questions[3].answered = false;

    // pop culture Questions
    strcpy(questions[4].category, "pop culture");
    strcpy(questions[4].question, "Which famous actor played the main role in Top Gun?");
    strcpy(questions[4].answer, "Tom Cruise");
    questions[4].value = 100;
    questions[4].answered = false;

    strcpy(questions[5].category, "pop culture");
    strcpy(questions[5].question, "Which movie won the Oscar in 2020?");
    strcpy(questions[5].answer, "The Parasite");
    questions[5].value = 200;
    questions[5].answered = false;

}


// Displays available categories and unanswered question values
// Displays available categories and question values ($100 and $200)
// Displays all categories with their available $100 and $200 questions
void display_categories(void)
{
    printf("\nCategories and Available Questions:\n");

    // Define possible question values
    int values[] = {100, 200};
    int num_values = sizeof(values) / sizeof(values[0]);

    // Iterate over all categories
    for (int c = 0; c < NUM_CATEGORIES; c++) {
        printf("%s: ", categories[c]);  // Print category name

        // Ensure each category is printed with $100 and $200 values
        for (int v = 0; v < num_values; v++) {
            bool available = false;

            // Iterate over all questions to check if this value exists for the category
            for (int i = 0; i < NUM_QUESTIONS; i++) {
                if (strcasecmp(questions[i].category, categories[c]) == 0 && 
                    questions[i].value == values[v] && 
                    !questions[i].answered) {
                    available = true;
                    break;
                }
            }

            // Print the value as available or unavailable
            if (available) {
                printf("$%d  ", values[v]);  // Question is available
            } else {
                printf("X    ");  // Mark as unavailable
            }
        }
        printf("\n"); // Move to the next line for the next category
    }
}



// Displays the question for the selected category and value
void display_question(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value) {
            if (questions[i].answered) {
                printf("This question has already been answered.\n");
                return;
            }
            printf("\nQuestion: %s\n", questions[i].question);
            return;
        }
    }
    printf("Invalid category or value.\n");
}

// Checks if the answer is correct
bool valid_answer(char *category, int value, char *answer)
{
    clean_input(answer);  // Standardize user input

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcasecmp(questions[i].category, category) == 0 && 
            questions[i].value == value && 
            !questions[i].answered) {

            char correct_answer[MAX_LEN];
            strcpy(correct_answer, questions[i].answer);
            clean_input(correct_answer); // Clean correct answer

            if (strcmp(correct_answer, answer) == 0) {
                questions[i].answered = true;
                return true;
            }
        }
    }
    return false;
}

// Checks if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
