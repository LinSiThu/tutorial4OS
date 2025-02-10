#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Tokenizes the user's input answer
void tokenize(char *input, char **tokens)
{
    input[strcspn(input, "\n")] = 0; // Remove newline

    // Skip "what is" or "who is" and extract the actual answer
    if (strncmp(input, "what is ", 8) == 0) {
        tokens[2] = input + 8;
    } else if (strncmp(input, "who is ", 7) == 0) {
        tokens[2] = input + 7;
    } else {
        tokens[2] = input; // Default to entire input if format is wrong
    }
}

// Displays the game results for each player, ranked by score
void show_results(player *players, int num_players)
{
    // Simple sorting to rank players by score
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("\nFinal Scores:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}


// Main game loop
int main()
{
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN] = { 0 };
    char category[MAX_LEN];
    int value;
    char answer[MAX_LEN];

    initialize_game(); // Initialize questions

    // Prompt for player names
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter player %d name: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = 0; // Remove newline
        players[i].score = 0;
    }

    // Start game loop
    while (true) {
        display_categories();

        // Ask for player's name until valid
        while (true) {
            printf("\nEnter the player's name who is selecting: ");
            fgets(buffer, BUFFER_LEN, stdin);
            buffer[strcspn(buffer, "\n")] = 0; // Remove newline

            if (player_exists(players, NUM_PLAYERS, buffer)) {
                break; // Valid player name
            } else {
                printf("Player not found. Try again.\n");
            }
        }

        // Ask for category until valid
        while (true) {
            printf("Enter category: ");
            fgets(category, MAX_LEN, stdin);
            category[strcspn(category, "\n")] = 0;

            bool valid_category = false;
            for (int i = 0; i < NUM_CATEGORIES; i++) {
                if (strcasecmp(category, categories[i]) == 0) {
                    valid_category = true;
                    break;
                }
            }

            if (valid_category) {
                break; // Valid category
            } else {
                printf("Invalid category. Please choose from the displayed categories.\n");
            }
        }

        // Ask for question value until valid
        while (true) {
            printf("Enter question value ($100 or $200): ");
            if (scanf("%d", &value) != 1) {
                printf("Invalid input. Please enter a numerical value.\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }
            getchar(); // Consume newline

            if (value == 100 || value == 200) {
                break; // Valid value
            } else {
                printf("Invalid value. Choose either $100 or $200.\n");
            }
        }

        display_question(category, value);

        // Ask for answer
        printf("Enter answer (format: 'what is X' or 'who is X'): ");
        fgets(answer, MAX_LEN, stdin);
        answer[strcspn(answer, "\n")] = 0; // Remove newline

        char *tokens[3] = { NULL };
        tokenize(answer, tokens);

        // Validate the answer
        if (valid_answer(category, value, tokens[2])) {
            update_score(players, NUM_PLAYERS, buffer, value);
            printf("Correct!\n");
        } else {
            for (int i = 0; i < NUM_QUESTIONS; i++) {
                if (strcasecmp(questions[i].category, category) == 0 && questions[i].value == value) {
                    printf("Incorrect. The correct answer was: %s\n", questions[i].answer);
                    break;
                }
            }
        }

        // Check if all questions are answered
        bool all_answered = true;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                all_answered = false;
                break;
            }
        }
        if (all_answered) break;
    }

    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;
}

