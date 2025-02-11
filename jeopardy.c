#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Function prototypes
void display_categories_with_unanswered(void);
void show_results(player *players, int num_players);

int main() {
    player players[NUM_PLAYERS];
    char buffer[MAX_LEN];
    char category[MAX_LEN];
    int value;
    char answer[MAX_LEN];
    char choice[MAX_LEN];
    bool game_active = true;

    initialize_game();

    // Prompt for player names
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter player %d name: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = 0;  // Remove newline character
        players[i].score = 0;
    }

    // Start game loop
    while (game_active) {
        display_categories_with_unanswered();

        printf("\nEnter the player's name who is selecting or type 'end game' to finish: ");
        fgets(buffer, MAX_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  

        if (strcasecmp(buffer, "end game") == 0) {
            game_active = false;
            continue;
        }

        while (!player_exists(players, NUM_PLAYERS, buffer)) {
            printf("Player does not exist. Please enter a valid player's name or 'end game' to finish: ");
            fgets(buffer, MAX_LEN, stdin);
            buffer[strcspn(buffer, "\n")] = 0;  
            if (strcasecmp(buffer, "end game") == 0) {
                game_active = false;
                break;
            }
        }

        if (!game_active) {
            continue;
        }

        printf("Enter category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = 0;  // Remove newline

        while (!valid_category(category)) {
            printf("Invalid category. Please enter a valid category: ");
            fgets(category, MAX_LEN, stdin);
            category[strcspn(category, "\n")] = 0;  
        }

        printf("Enter question value ($100 or $200): ");
        scanf("%d", &value);
        while (getchar() != '\n'); // Clear the input buffer

        if (already_answered(category, value)) {
            printf("This question has already been answered. Please choose another one.\n");
            continue;
        }

        display_question(category, value);
        printf("Enter answer (format: 'what is X' or 'who is X'): ");
        fgets(answer, MAX_LEN, stdin);
        answer[strcspn(answer, "\n")] = 0;  

        if (valid_answer(category, value, answer)) {
            update_score(players, NUM_PLAYERS, buffer, value);
            printf("Correct!\n");
        } else {
            int idx = find_question_index(category, value);
            printf("Incorrect. The correct answer was: %s\n", questions[idx].answer);
        }
    }

    show_results(players, NUM_PLAYERS);
    printf("\nGame Over! All questions have been answered or the game was ended manually.\nWould you like to 'restart' or 'quit'? ");
    fgets(choice, MAX_LEN, stdin);
    choice[strcspn(choice, "\n")] = 0; 

    if (strcasecmp(choice, "restart") == 0) {
        main(); // Restart the game by recalling main
    }

    return EXIT_SUCCESS;
}

void display_categories_with_unanswered() {
    printf("\nAvailable Categories and their unanswered questions' values:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%s: ", categories[i]);
        bool found = false;
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            if (strcmp(questions[j].category, categories[i]) == 0 && !questions[j].answered) {
                printf("$%d ", questions[j].value);
                found = true;
            }
        }
        if (!found) {
            printf("No unanswered questions");
        }
        printf("\n");
    }
}

void show_results(player *players, int num_players) {
    // Sort the players by score in descending order
    for (int i = 0; i < num_players; i++) {
        for (int j = i + 1; j < num_players; j++) {
            if (players[i].score < players[j].score) {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Display the sorted list of players and their scores
    printf("\nFinal results:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
}
