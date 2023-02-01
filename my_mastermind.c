#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_ATTEMPTS 10 //constant definition of the maximum tries a user has.
#define CODE_LEN 4 //constant definition of the code length to hold the code inputs.
#define BUFFER_SIZE 5 //buffer size that holds the guesses made by the user.


void generate_code(char *secret_code) { //generates a 4-digit random code. The function takes in a char pointer, "secret_code", which is used to store the generated code.
    for (int i = 0; i < CODE_LEN; i++) { //iterate 4 times.
        secret_code[i] = (rand() % 9) + '0'; //On each iteration, assigns a random number between 0 and 9 to the current index of the "secret_code" char array, and then adds the ASCII value of '0' to it to convert it to the corresponding digit character.
    }
}
//
int guess_check (const char* guess, const char* secret_code, int* well_placed, int* misplaced) {
    *well_placed = 0;
    *misplaced = 0;

    for (int i = 0; i < CODE_LEN; i++) {
        if (guess[i] == secret_code[i]) {
            (*well_placed)++;
        }else {
            for (int j = 0; j < CODE_LEN; j++){
                if (guess[i] == secret_code[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
    return *well_placed == CODE_LEN;
}


int main (int argc, char **argv) {
    char secret_code[CODE_LEN] = {0};  //initialize secret_code char array with zero 
    int attempts = MAX_ATTEMPTS; //initialize attempts 
    srand(time(NULL));
    
    // Check command line arguments for user defined secrete code and attempts
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(secret_code, argv[i + 1], CODE_LEN);
            i++;
        }else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            attempts = atoi(argv[i+1]);
            i++;
        }
    }
    if(secret_code[0] == 0) { //if secret_code is not set
        generate_code(secret_code); //generate secret code
    }
    //send prompt to the console for user inputs
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
        for (int i = 0; i < attempts; i++) { //loop through attempts
        printf("---\nRound %d\n>", i);
        char guess[BUFFER_SIZE] = {0}; //initialize guess char array with 0
        int well_placed = 0;
        int misplaced = 0;
        
        //the read() function reads input from the user and store it in the guess buffer then returns the number of bytes read from the input.
        if (read(0, guess, BUFFER_SIZE) <= 0) { //The if statement checks if the number of bytes read from the input is less than or equal to zero. If it is, it means that the user has entered an EOF (end of file) signal,
            printf("Program is Exiting... Ctrl + D command entered!"); //which is usually generated by pressing the Ctrl + D key combination.
            break;
        }
        //check if the character in the input string(guess) is lowercase or uppercase letter
        if(((guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z'))){
            printf("Program exiting... Invalid character entered!");
            break;
        }
        //chech for invalid inputs in this case alphabetical characters which are not numbers, and to inform the user of the invalid input.
        if(((guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z'))){
            printf("Wrong input!");
            continue;
        }
        //checks if the function guess_check returns true. If it does, then it means that the guess correctly matches the secret code, and it prints a "Congratz! You did it!" message.
        if(guess_check(guess, secret_code, &well_placed, &misplaced)){
            printf("Congratz! You did it!\n");
            break;
        } else {//returns false, which means the guess is not correct.
            printf("Well placed pieces: %d \n Misplaced pieces: %d \n", well_placed, misplaced);
        }
    }
    return 0;
}