#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getguessgame();

int getcomputerchoice();
int getuserchoice();
void checkthewinner(int game1, int computerchioce, int *round, int *score);

int main()
{
    srand(time(NULL));
    int choose1 = 0;

    do{
        printf("\n*** Fun Games ***\n");
        printf("Choose the Game you want to play.\n");
        printf("1.Rock,scissor&paper.\n");
        printf("2.Guess the number.\n");
        printf("0.Exit.");
        printf("Enter your option: ");
        scanf(" %d", &choose1);

        if(choose1 == 1){
            getuserchoice();
        }

        if (choose1 == 2){
            getguessgame();
        }
    }while(choose1 != 0);
    return 0;
}

int getcomputerchoice(){
    return (rand()%3)+1;
}

int getuserchoice(){

    int game1 = 0;
    int score = 0;
    int round = 0;


    printf("*** Rock Scissor Paper\n");
    do{
        int computerchoice = getcomputerchoice();
        printf("Choose the option you want.\n");
        printf("1. Rock\n");
        printf("2. Scissor\n");
        printf("3. Paper\n");
        printf("0. Exit\n");
        printf("\nEnter your option: ");
        scanf(" %d", &game1);
        if((game1>3)||(game1<0)){
            printf("\nInvalid input (choose from 0 to 3)\n");
            continue;
        }

        switch(game1){
        case 1:
            printf("You chose rock\n");
            break;
        case 2:
            printf("You chose scissor\n");
            break;
        case 3:
            printf("You chose paper\n");
            break;
        }

        switch(computerchoice){
        case 1:
            printf("computer chose rock\n");
            break;
        case 2:
            printf("computer chose scissor\n");
            break;
        case 3:
            printf("computer chose paper\n");
            break;
        }

        checkthewinner( game1, computerchoice, &round, &score);

        if(game1 == 0){
            printf("your score is %d out of %d round\n\n",score,round);
        }

    }while(game1 != 0);

}

void checkthewinner(int game1, int computerchioce, int *round, int *score){

    (*round)++;

    if( game1 ==  computerchioce){
        printf("\nit's a tie\n\n");
    }

    else if((game1 == 1 && computerchioce == 2) ||
            (game1 == 2 && computerchioce == 3) ||
            (game1 == 3 && computerchioce == 1)){
        printf("\nyou win\n");
        (*score)++;
    }
    else{
        printf("\nyou lose\n\n");
    }
}


void getguessgame(){

    int number = 0;
    int score = 0;
    int round = 0;
    int computerNumber;

    printf("*** Guess the number ***\n\n");
    printf("Try to guess the number (1 to 5) that computer chose.\n");

    do{
        computerNumber = (rand() % 5) + 1;

        printf("\n0. Exit\n");
        printf("Enter a number: ");
        scanf("%d", &number);

        if(number == 0){
            break;
        }

        round++;

        if(number == computerNumber){
            printf("Correct! You got it right!\n");
            score++;
        }
        else{
            printf("Wrong! The number was %d.\n", computerNumber);
        }

    }while(number != 0);

    printf("\nYour score is %d out of %d rounds\n\n", score, round);
}













