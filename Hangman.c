#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_LENGTH 50
#define MAX_TRIES 8
#define MAX_POINTS 100

struct word
{
    char word[MAX_LENGTH];
    char hint[MAX_LENGTH];
    int score;
};

struct fig{
    char figure[20];
    int times;
};

typedef struct word word;
typedef struct fig fig;

void initializeGame(word* game,fig*F);

void random_W(word **G);


void initializeGame(word* game,fig*F) {
    for(int i=0;i<20;i++){
        F->figure[i]=' ';
    }
    F->times=0;
    printf("score: %d\n",game->score);
    printf("The Word is a %s:\n ", game->hint);
    int n, count = 0, cond = 0, check = 0;
    char ch;
    n = strlen(game->word);
    n = n * 2;
    char str[n];
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            str[i] = '_';
        else
            str[i] = ' ';
    }
    str[n] = '\0';

    while (1) {
        cond = 0;
        check = 1;
        if (count == 8) {
            printf("\nyou died\n");
            return;
        }
        for(int i=0; i < n; i++) {
            if (str[i] == '_') {
                check = 0;
                break;
            }
        }
        if (check == 1) {
            cond = 0;
            game->score += 100;
            printf(":::success:::\n");
            printf("wanna continue???\n");
            printf("enter 1 to continue\n");
            scanf("%d", &cond);
            if (cond == 1) {
                printf("__________________________________________________________________________________________________________________________\n");
                random_W(&game);
                initializeGame(game,F);
                return ;
            }
            else {
                printf("thank you for playing\n");
                printf("your score is:-%d\n", game->score);
                return;
            }
        }
        printf("\n\n%s\t%s\r", F->figure,str);
        fflush(stdout);

        scanf(" %c", &ch);

        for (int i = 0; i < n; i += 2) {
            if (ch == str[i]) {
                cond = 1;
                break;
            }
            if (ch == game->word[i / 2]) {
                cond = 1;
                str[i] = ch;
            }
        }

        if (cond != 1) {
            count++;
            F->times++;
            switch(F->times){
                case 1:
                    F->figure[2]='o';
                    F->figure[4]='\n';
                    break;
                case 2:
                    F->figure[7]='|';
                    break;
                case 3:
                    F->figure[6]='\\';
                    break;
                case 4:
                    F->figure[8]='/';
                    F->figure[9]='\n';
                    break;
                case 5:
                    F->figure[12]='|';
                    F->figure[14]='\n';
                    break;
                case 6:
                    F->figure[16]='/';
                    break;
                case 7:
                    F->figure[18]='\\';
                    F->figure[19]='\n';
                    break;
            }

        }
    }
}

void random_W(word **G) {
    char* category[] = {"fruits", "colours", "sports"};
    char* words[][3] = {{"apple", "banana", "orange"}, {"red", "blue", "pink"}, {"cricket", "swimming", "football"}};
    int i;
    time_t t;
    srand((unsigned) time(&t));
    i=rand()%3;
    strcpy((*G)->hint, category[i]);
    strcpy((*G)->word, words[i][rand()%3]);
}

int play() {
    printf("HANGMAN\n");
    struct fig*figure=(struct fig*)malloc(sizeof(struct fig));
    word* random_word = (word*)malloc(sizeof(word));
    random_word->score = 0;
    random_W(&random_word);
    initializeGame(random_word,figure);
    free(random_word); // Free the allocated memory
    return 0;
}

int main() {
    play();
    return 0;
}
