#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <stdio.h>
#include <stdbool.h>
//ALL THE SCREENS USED
typedef enum {
    MAIN_MENU, DIFFICULTY_MENU, WORD_ENTRY_EASY,
    WORD_ENTRY_MED, WORD_ENTRY_HARD, GAMEPLAY_EASY, 
    GAMEPLAY_MED, GAMEPLAY_HARD, CHOOSE_SIZE, GAME_OVER, YOU_WIN
} GameScreen;

char enteredWord[6] = "";   // word entered by the first player
char guessedWord[6] = "_____";  // word guessed by the second player
int wordLength = 0;  // length of the entered word
int incorrectGuesses = 0;  // Track incorrect guesses
int maxIncorrectGuesses = 15;  // maximum incorrect guesses
bool gameOver = false;  // to track if the game is over 
static char size[45] = ""; // to enter the guessed word in the hard mode to translate it to integer
static int charIndex = 0;       // length for the size entered
static int enteredNumber = 0;   // to store the entered size

//the hangman drawing
void DrawHangman(int incorrectGuesses) {
    int hangmanX = 200, hangmanY = 400;
    switch (incorrectGuesses) {
         case 1:  
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
        break;
        case 2:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
        break;
        case 3:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
        break;
        case 4:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);

        break;
        case 5:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
        break;
        case 6:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
        break;
        case 7:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
        break;
        case 8:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
        break;
        case 9:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
        break;
        case 10:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
        break;
        case 11:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 200, hangmanX + 490, hangmanY + 250, BLACK);
        break;
        case 12:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 200, hangmanX + 490, hangmanY + 250, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 460, hangmanY + 220, BLACK);
        break;
        case 13:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 200, hangmanX + 490, hangmanY + 250, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 460, hangmanY + 220, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 520, hangmanY + 220, BLACK);
        break;
        case 14:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 200, hangmanX + 490, hangmanY + 250, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 460, hangmanY + 220, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 520, hangmanY + 220, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 250, hangmanX + 475, hangmanY + 275, BLACK);
        break;
        case 15:
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 440, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 350, hangmanX + 490, hangmanY + 350, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 350, hangmanX + 390 , hangmanY + 300, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 300, hangmanX + 390 , hangmanY + 250, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 250, hangmanX + 390 , hangmanY + 200, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 200, hangmanX + 390 , hangmanY + 150, BLACK);
            DrawLine(hangmanX + 390, hangmanY + 150, hangmanX + 440, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 440, hangmanY + 150, hangmanX + 490, hangmanY + 150, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 150, hangmanX + 490, hangmanY + 200, BLACK);
            DrawCircle(hangmanX + 490, hangmanY + 200, 10, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 200, hangmanX + 490, hangmanY + 250, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 460, hangmanY + 220, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 220, hangmanX + 520, hangmanY + 220, BLACK);
            DrawLine(hangmanX + 490, hangmanY + 250, hangmanX + 505, hangmanY + 275, BLACK);
        break;
}}


int main(){

    InitWindow(1300, 800, "HANG MAN");   //window dimensions and the title

    GameScreen currentScreen = MAIN_MENU;   //main menu screen

    int wordLength = 0;

    SetTargetFPS(60);   //frames per second or speed of displaying

    //buttons needed and their sizes 

    Rectangle startbutton = {550, 500, 200, 50 };//to go to the difficulty menu
    Rectangle easybutton = {550, 300, 200, 50};//to choose the easy mode
    Rectangle mediumbutton = {550, 400, 200, 50};//to choose the medium mode
    Rectangle hardbutton = { 550, 500, 200, 50};//to choose the hard mode
    Rectangle confirmButton = {550, 600, 200, 50};//to go to the gameplay screen
    Rectangle resetbutton = {550, 600, 200, 50};//to reset when loosing to the main menu
    Rectangle wordBox = {400, 300, 360, 50};//used to draw the box 
      while(!WindowShouldClose()){   //to keep the code running while the window

        BeginDrawing();   //to start displaying
        ClearBackground(WHITE);   //background color 
        
        if (currentScreen == MAIN_MENU){
            int fontSize = 100;
       
            int textWidth = MeasureText("HANG MAN", fontSize);
            int textHeight = fontSize;

              
            int x = (GetScreenWidth() - textWidth) / 2; 
            int y = (GetScreenHeight() - textHeight) / 2 - 250;

        

            ClearBackground(WHITE);  

            DrawText("HANG MAN", x, y, fontSize, BLACK);// to draw the title

            if (GuiButton(startbutton, "START")){
            currentScreen = DIFFICULTY_MENU;   
            }
        }

        else if (currentScreen == DIFFICULTY_MENU){
            DrawText("CHOSE THE DIFFICULTY!", 460, 200, 30, BLACK);
// section that lets us choose the difficulty
            if (GuiButton(easybutton, "EASY")){
                currentScreen = WORD_ENTRY_EASY;  
            }

            if (GuiButton(mediumbutton, "MEDIUM")){
                currentScreen = WORD_ENTRY_MED;   
            }

            if (GuiButton(hardbutton, "HARD")){
                currentScreen = CHOOSE_SIZE;   
            }
        }
// section that lets us enter the guessing word
        else if (currentScreen == WORD_ENTRY_EASY){
            DrawText("ENTER THE GUESSING WORLD:", 410, 200, 30, BLACK);   
            
             int key = GetCharPressed();
            
            if (key >= 'a' && key <= 'z' && wordLength < 5 ) {
            enteredWord[wordLength] = (char)key;  
            wordLength++;}
            
            if (IsKeyPressed(KEY_BACKSPACE) && wordLength>0){
                enteredWord[wordLength] = '\0';
                wordLength--;}
            
// to display the guessing word inside a box but unkown*
            for (int i = 0; i < wordLength; i++) {
                
               DrawText("*", 500 + 10 + (i * 60), wordBox.y + (wordBox.height / 4), 30, BLACK);}

               DrawRectangleLines(460,wordBox.y, wordBox.width, wordBox.height, BLACK);  // Border of the box

            if (GuiButton(confirmButton, "Confirm")){ currentScreen = GAMEPLAY_EASY;}
            }
// gameplay section
else if (currentScreen == GAMEPLAY_EASY) {
    DrawText("Guess The Word", 440, 100, 50, BLACK);
    DrawText("Enter a character:", 455, 200, 40, BLACK);

// display current guessed word
    DrawText(guessedWord, 590, 300, 40, BLACK);

// display error counter
    char errorCountText[50];
    sprintf( errorCountText , "Errors: %d/%d", incorrectGuesses, maxIncorrectGuesses);
    DrawText(errorCountText, 550, 350, 30, RED);

// draw the hangman
    DrawHangman(incorrectGuesses);

// to test the entered letter
    int key = GetCharPressed();
    if (key >= 'a' && key <= 'z' && !gameOver) {
        bool correctGuess = false;

        for (int i = 0; i < wordLength; i++) {
            if (enteredWord[i] == key && guessedWord[i] == '_') {
                guessedWord[i] = key;  // Replace underscore with guessed letter
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses++;
        }
    }

// check if the word is completely guessed
    bool wordGuessed = true;
    for (int i = 0; i < wordLength; i++) {
        if (guessedWord[i] == '_') {
            wordGuessed = false;
            break;
        }
    }

    if (wordGuessed) {
        currentScreen = YOU_WIN;
    } else if (incorrectGuesses >= maxIncorrectGuesses) {
        gameOver = true;
        currentScreen = GAME_OVER;
    }
}

// winning screen
else if (currentScreen == YOU_WIN) {
    DrawText("YOU WON!", 475, 300, 75, GREEN);
    if (GuiButton(resetbutton, "REPLAY")) {
//reset
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';
        gameOver = false;
    }
}

// loosing screen
else if (currentScreen == GAME_OVER) {
    DrawText("GAME OVER", 425, 300, 75, RED);
    DrawText("The word was: ", 502, 440, 30, BLACK);
    DrawText(enteredWord, 725, 440, 30, BLACK);
    if (GuiButton(resetbutton, "REPLAY")) {
// reset
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';
        gameOver = false;  }
}
// medium section
else if (currentScreen == WORD_ENTRY_MED){
            DrawText("ENTER THE GUESSING WORLD:", 410, 200, 30, BLACK);   
            
             int key = GetCharPressed();
            
            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ) && wordLength < 5 ) {
            enteredWord[wordLength] = (char)key;  
            wordLength++;}
            
            if (IsKeyPressed(KEY_BACKSPACE) && wordLength>0){
                enteredWord[wordLength] = '\0';
                wordLength--;}
            
        
            for (int i = 0; i < wordLength; i++) {
                
               DrawText("*", 500 + 10 + (i * 60), wordBox.y + (wordBox.height / 4), 30, BLACK);}

               DrawRectangleLines(460,wordBox.y, wordBox.width, wordBox.height, BLACK);  // Border of the box

            if (GuiButton(confirmButton, "Confirm")){ currentScreen = GAMEPLAY_MED;}
            }
// gameplay section
else if (currentScreen == GAMEPLAY_MED) {
    DrawText("Guess The Word", 440, 100, 50, BLACK);
    DrawText("Enter a character:", 455, 200, 40, BLACK);

    DrawText(guessedWord, 590, 300, 40, BLACK);

    char errorCountText[50];
    sprintf( errorCountText , "Errors: %d/%d", incorrectGuesses, maxIncorrectGuesses);
    DrawText(errorCountText, 550, 350, 30, RED);

    DrawHangman(incorrectGuesses);

    int key = GetCharPressed();
    if (((key >= 'a' && key <= 'z' )|| (key >= 'A' && key <= 'Z' ) )&& !gameOver) {// the only change here is the added upper case letters
        bool correctGuess = false;

        for (int i = 0; i < wordLength; i++) {
            if (enteredWord[i] == key && guessedWord[i] == '_') {
                guessedWord[i] = key; 
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses++;
        }
    }

    bool wordGuessed = true;
    for (int i = 0; i < wordLength; i++) {
        if (guessedWord[i] == '_') {
            wordGuessed = false;
            break;
        }
    }

    if (wordGuessed) {
        currentScreen = YOU_WIN;
    } else if (incorrectGuesses >= maxIncorrectGuesses) {
        gameOver = true;
        currentScreen = GAME_OVER;
    }
}

else if (currentScreen == YOU_WIN) {
    DrawText("YOU WON!", 475, 300, 75, GREEN);
    if (GuiButton(resetbutton, "REPLAY")) {
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';
        gameOver = false;
    }
}

else if (currentScreen == GAME_OVER) {
    DrawText("GAME OVER", 425, 300, 75, RED);
    DrawText("The word was: ", 502, 440, 30, BLACK);
    DrawText(enteredWord, 725, 440, 30, BLACK);
    if (GuiButton(resetbutton, "REPLAY")) {
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';
        gameOver = false;  }
}
//hard section
else if (currentScreen == CHOOSE_SIZE) {//lets the player choose the size of the guessing word
   
    DrawText("Choose the word size:", 430, 200, 40, BLACK);
    int key = GetCharPressed();
    if (key >= '0' && key <= '9' && charIndex < 2) {
        size[charIndex++] = (char)key;
        size[charIndex] = '\0';
    }
    if (IsKeyPressed(KEY_BACKSPACE) && charIndex > 0) {
        size[--charIndex] = '\0';
    }

    DrawText(size, 640, 375, 30, BLACK);

    // confirm size
    if (GuiButton(confirmButton, "Confirm")) {
        enteredNumber = atoi(size);
        if (enteredNumber >= 2 && enteredNumber <= 45) {
            wordLength = enteredNumber;
            memset(guessedWord, '_', wordLength);
           guessedWord[wordLength] = '\0';  
            currentScreen = WORD_ENTRY_HARD;
        }
    }
}
// gameplay
            else if (currentScreen == WORD_ENTRY_HARD) {
    DrawText("ENTER THE GUESSING WORD:", 425, 200, 30, BLACK);  

    int key = GetCharPressed();
    
    // this variable is used instead of wordlength because the word length is specific to the easy and medium mode
    static int enteredCharCount = 0;

    if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') )  && enteredCharCount < enteredNumber) {
        enteredWord[enteredCharCount] = (char)key;  
        enteredCharCount++;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && enteredCharCount > 0) {
        enteredCharCount--; 
        enteredWord[enteredCharCount] = '\0';
    }

    for (int i = 0; i < enteredCharCount; i++) {
        DrawText("*", 200 + 10 + (i * 60), wordBox.y + (wordBox.height / 4), 30, BLACK);
    }

    if (GuiButton(confirmButton, "Confirm")) {
        currentScreen = GAMEPLAY_HARD;
    }
}

else if (currentScreen == GAMEPLAY_HARD) {
    DrawText("Guess The Word", 440, 100, 50, BLACK);
    DrawText("Enter a character:", 455, 200, 40, BLACK);

    DrawText(guessedWord, 590, 300, 40, BLACK);

    char errorCountText[50];
    sprintf( errorCountText , "Errors: %d/%d", incorrectGuesses, maxIncorrectGuesses);
    DrawText(errorCountText, 550, 350, 30, RED);

    DrawHangman(incorrectGuesses);

    int key = GetCharPressed();
    if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ) && !gameOver) {
        bool correctGuess = false;

        for (int i = 0; i < wordLength; i++) {
            if (enteredWord[i] == key && guessedWord[i] == '_') {
                guessedWord[i] = key; 
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses++;
        }
    }

    bool wordGuessed = true;
    for (int i = 0; i < wordLength; i++) {
        if (guessedWord[i] == '_') {
            wordGuessed = false;
            break;
        }
    }

    if (wordGuessed) {
        currentScreen = YOU_WIN;
    } else if (incorrectGuesses >= maxIncorrectGuesses) {
        gameOver = true;
        currentScreen = GAME_OVER;
    }
}

else if (currentScreen == YOU_WIN) {
    DrawText("YOU WON!", 475, 300, 50, GREEN);
    if (GuiButton(resetbutton, "REPLAY")) {
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';
        gameOver = false;

    }
}

else if (currentScreen == GAME_OVER) {
    DrawText("GAME OVER", 425, 300, 75, RED);
    DrawText("The word was: ", 502, 440, 30, BLACK);
    DrawText(enteredWord, 725, 440, 30, BLACK);
    if (GuiButton(resetbutton, "REPLAY")) {
        currentScreen = MAIN_MENU;
        incorrectGuesses = 0;
        wordLength = 0;
        memset(enteredWord, 0, sizeof(enteredWord));
        memset(guessedWord, '_', sizeof(guessedWord) - 1);
        guessedWord[5] = '\0';  
        gameOver = false; 
         }
}

 EndDrawing(); //to stop displaying  
}
 CloseWindow(); //to free the RAM memory  
return 0 ;
} 