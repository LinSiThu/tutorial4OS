#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>

#define MAX_LEN 256
#define NUM_CATEGORIES 3
#define NUM_QUESTIONS 12

typedef struct {
    char category[MAX_LEN];
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
} question;

extern char categories[NUM_CATEGORIES][MAX_LEN];
extern question questions[NUM_QUESTIONS];

void initialize_game(void);
void display_categories(void);
void display_question(char *category, int value);
bool valid_answer(char *category, int value, char *answer);
bool already_answered(char *category, int value);
bool all_questions_answered(void);
bool valid_category(char *category);
int find_question_index(const char *category, int value);

#endif /* QUESTIONS_H_ */
