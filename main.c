#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_SESSION_TIME 40
#define DEFAULT_S_BREAK_TIME 5
#define DEFAULT_L_BREAK_TIME 15
#define DEFAULT_ANIMATION_SIZE 63

char DEFAULT_ANIMATION[63] = "[                                                            ]";
char WELCOME_TEXT[] = "Work in progress...\n";
char WELCOME_HEADER[] =
    "\n"
    "\n"
    "    ____   __   _  _   __  ____   __  ____   __  \n"
    "   (  _ \\ /  \\ ( \\/ ) /  \\(    \\ /  \\(  _ \\ /  \\ \n"
    "    ) __/(  O )/ \\/ \\(  O )) D ((  O ))   /(  O )\n"
    "   (__)   \\__/ \\_)(_/ \\__/(____/ \\__/(__\\_) \\__/ \n"
    "\n"
    "\n";



typedef struct Animation
{
    char animationArr[DEFAULT_ANIMATION_SIZE];
    unsigned int loaded;
    unsigned int animationSize;
} Animation;

void welcome()
{
    printf("%s", WELCOME_HEADER);
    printf("%s", WELCOME_TEXT);
    puts("");
}

unsigned int getSessionTime()
{
    unsigned int sessionTime = DEFAULT_SESSION_TIME;
    int c;
    printf("INPUT SESSION TIME: \n");

    while (1) {
        if (scanf("%u", &sessionTime) != 1 && (c = getchar() != '\n')) {
            puts("Invalid time.");
            puts("");
            while (c != EOF) {}
            printf("INPUT SESSION TIME: \n");
        }
        else if (c == '\n' && c != EOF) {
            puts("");
            return DEFAULT_SESSION_TIME;
        }
        else {
            puts("");
            return sessionTime;
        }
    }
}

unsigned int getShortBreakTime()
{
    unsigned int sBreakTime = DEFAULT_S_BREAK_TIME;
    int c;
    printf("INPUT SHORT BREAK TIME: \n");

    while (1) {
        if (scanf("%u", &sBreakTime) != 1) {
            puts("Invalid time.");
            puts("");
            while (c = getchar() != '\n' && c != EOF) {}
            printf("INPUT SHORT BREAK TIME: \n");
        }
        else {
            puts("");
            return sBreakTime;
        }
    }
}

unsigned int getLongBreakTime()
{
    unsigned int lBreakTime = DEFAULT_L_BREAK_TIME;
    int c;
    printf("INPUT LONG BREAK TIME: \n");

    while (1) {
        if (scanf("%u", &lBreakTime) != 1) {
            puts("Invalid time.");
            puts("");
            while (c = getchar() != '\n' && c != EOF) {}
            printf("INPUT LONG BREAK TIME: \n");
        }
        else {
            puts("");
            return lBreakTime;
        }
    }
}

void updateTimeAnimation(Animation* animation, unsigned int timePassed, unsigned int totalTimeSeconds)
{
    size_t i;
    unsigned int progress = (timePassed * animation->animationSize) / totalTimeSeconds;

    for (i = 0; i < animation->animationSize - 3; i++) {
        if (i < progress) {
            animation->animationArr[i + 1] = '#';
        }
        else {
            animation->animationArr[i + 1] = ' ';
        }
    }

    // Clear the current line and move cursor to start
    printf("\033[2K\r");
    printf("%s", animation->animationArr);
    fflush(stdout);
}

// Start loading animation.
void startTime(Animation* animation, unsigned int time)
{
    unsigned int timeInSeconds = time * 60;
    unsigned int timePassed = 0;

    for (timePassed = 0; timePassed < timeInSeconds; timePassed++) {
        updateTimeAnimation(animation, timePassed, timeInSeconds);
        sleep(1);
    }
    puts("");
    puts("SESSION FINISHED");
}

Animation* initAnimation(Animation* animation)
{   
    // Ensure the string length of DEFAULT_ANIMATION does not exceed the size of animationArr
    if (strlen(DEFAULT_ANIMATION) < sizeof(animation->animationArr)) {
        strcpy(animation->animationArr, DEFAULT_ANIMATION);
    } else {
        // Handle the case where the default animation is too large
        strncpy(animation->animationArr, DEFAULT_ANIMATION, sizeof(animation->animationArr) - 1);
        animation->animationArr[sizeof(animation->animationArr) - 1] = '\0';
    }
    animation->animationSize = DEFAULT_ANIMATION_SIZE;
    animation->loaded = 0;
    return animation;
}

int main(int argc, char const *argv[])
{
    unsigned int sTime = DEFAULT_SESSION_TIME;
    unsigned int sBreakTime = DEFAULT_S_BREAK_TIME; 
    unsigned int lBreakTime = DEFAULT_L_BREAK_TIME;
    Animation *animation = (Animation *)malloc(sizeof(Animation));

    welcome();
    sTime = getSessionTime();
    sBreakTime = getShortBreakTime();
    lBreakTime = getLongBreakTime();
    animation = initAnimation(animation);
    startTime(animation, sTime);

    free(animation);

    return 0;
}
