#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "questions.h"

char categories[NUM_CATEGORIES][MAX_LEN] = {"history", "geography", "pop culture"};
question questions[NUM_QUESTIONS] = {
    {"history", "What year did WW2 end?", "1945", 100, false},
    {"history", "What year did the North American Free Trade Agreement (NAFTA) go into effect?", "1994", 200, false},
    {"geography", "What is the capital of Sweden?", "Stockholm", 100, false},
    {"geography", "Which country has the well-known museum called Hermitage?", "Russia", 200, false},
    {"pop culture", "Which famous actor played the main role in Top Gun?", "Tom Cruise", 100, false},
    {"pop culture", "Which movie won the Oscar in 2020?", "Parasite", 200, false}
};

void initialize_game(void) {
    // Game initialization logic if needed
}

void display_categories(void) {
    printf("\nAvailable Categories:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%s\n", categories[i]);
    }
}

void display_question(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered) {
            printf("\nQuestion: %s\n", questions[i].question);
            return;
        }
    }
}

bool valid_answer(char *category, int value, char *answer) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered) {
            if (strcasecmp(questions[i].answer, answer) == 0) {
                questions[i].answered = true;
                return true;
            }
        }
    }
    return false;
}

bool already_answered(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}

bool all_questions_answered(void) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            return false;
        }
    }
    return true;
}

bool valid_category(char *category) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (strcmp(categories[i], category) == 0) {
            return true;
        }
    }
    return false;
}

int find_question_index(const char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return i;
        }
    }
    return -1; // Return -1 if no matching question is found
}
