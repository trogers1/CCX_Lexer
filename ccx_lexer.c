/* hw1.c
CCX lexer
Taylor Rogers
Michael Wilder
CS 210
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// #define DEBUG    //Uncomment this to debug

void isComment(char file_text[], int *index);
void isString(char file_text[], int *index);
void isOperator(char file_text[], int *index);
void isKeyword(char file_text[], int *index);
void isCharacterLiteral(char file_text[], int *index);
void isNumericLiteral(char file_text[], int *index);
void isIdentifier(char file_text[], int *index);
void isUnknown(char file_text[], int *index);

bool endOfComment(char file_text[], int *index);
bool endOfWord(char c);
bool legalNumLitChar(char c);
bool legalIdentifierChar(char c);

/*argc (ARGument Count) is int and stores number of command-line arguments passed by the user including the name of the program. So if we pass a value to a program, value of argc would be 2 (one for argument and one for program name)
argv(ARGument Vector) is array of character pointers listing all the arguments.
*/
int main(int argc, char *argv[]) {
    
    FILE *filePtr;


    //check that a CL argument (a file to parse) was given
    if (argc == 1){
        printf("\nNo Command Line Argument Passed Other Than Program Name\n");
        exit(1); //exit with error
    }
    if (!(filePtr = fopen(argv[1], "r")))
    {
        printf("Error encountered when opening file\n");
        perror(argv[1]);
        exit(1);
    }
    
    #ifdef DEBUG
        printf("%s\n", argv[1]);
    #endif

    filePtr = fopen(argv[1], "r");

    //If we opened the file successfully, it's time to deal with it...
    
    

    //character is declared int, not char because EOF has a value that is different from all characters that can be stored in a char
    int character;
    int index = -1;
    while ((character = fgetc(filePtr)) != EOF)
    {
        index++; //starts the index at 0 if the character isn't at the end of the file.
    }
    #ifdef DEBUG
        printf("index: %d\n", index);
    #endif
    const int file_length = index; //because it goes too far by 1 character

    fseek(filePtr, 0, SEEK_SET); //reset filePtr to beginning of file

    #ifdef DEBUG
        printf("file_length: %d\n", file_length);
    #endif

    //Create an array that is the length of the file to contain all characters
    char file_text[file_length];
    //reset index
    index = 0; 
    //Populate the array with characters from the 
    while ((file_text[index] = fgetc(filePtr)) != EOF)
    {
        index++;
    }
    #ifdef DEBUG
        printf("here0\n");
    #endif
    int i = 0;
    //Begin iteration through file
    while(i <= file_length)
    {
        #ifdef DEBUG
            printf("%i: ", i);
            printf("%c\n", file_text[i]);

            if (file_text[i] == '\n')
            {
                printf("newline!\n");
            }
            printf("here1\n");
        #endif
        //ignore spaces
        if (file_text[i] == ' '){
            i++;
            continue;

        }
        //ignore newlines
        else /*Check if newline*/ if (file_text[i] == '\n')
        {
            i++;
            continue;
        }
        else /*check for comment*/ if (file_text[i] == '/' 
                                        && file_text[i+1] == '*')
        {
            #ifdef DEBUG
                printf("Found comment\n");
            #endif
            isComment(file_text, &i);
        }
        else /*check for string*/ if (file_text[i] == '"')
        {
            #ifdef DEBUG
                printf("Found string\n");
            #endif
            isString(file_text, &i);
        }
        else /*Check for operator*/ if (file_text[i] == '(' ||
                                        file_text[i] == ')' ||
                                        file_text[i] == '.' ||
                                        file_text[i] == '<' ||
                                        file_text[i] == '>' ||
                                        file_text[i] == '+' ||
                                        file_text[i] == '-' ||
                                        file_text[i] == '*' ||
                                        file_text[i] == '/' ||
                                        file_text[i] == '|' ||
                                        file_text[i] == '&' ||
                                        file_text[i] == ';' ||
                                        file_text[i] == ',' ||
                                        file_text[i] == ':' ||
                                        file_text[i] == '=' ||
                                        file_text[i] == '!' ||
                                        file_text[i] == '[' ||
                                        file_text[i] == ']' ||
                                        file_text[i] == '{' ||
                                        file_text[i] == '}' ||
                                        file_text[i] == '$' ||
                                        file_text[i] == '@')
        {
            #ifdef DEBUG
                printf("Found operator\n");
            #endif
            isOperator(file_text, &i);
        }
        else /*check for Keywords*/ if (
            /*accessor*/
            (file_text[i] == 'a' && file_text[i + 1] == 'c' && file_text[i + 2] == 'c' && file_text[i + 3] == 'e' && file_text[i + 4] == 's' && file_text[i + 5] == 's' && file_text[i + 6] == 'o' && file_text[i + 7] == 'r' && endOfWord(file_text[i + 8])) ||
            /*and*/
            (file_text[i] == 'a' && file_text[i + 1] == 'n' && file_text[i + 2] == 'd' && endOfWord(file_text[i + 3])) ||
            /*array*/
            (file_text[i] == 'a' && file_text[i + 1] == 'r' && file_text[i + 2] == 'r' && file_text[i + 3] == 'a' && file_text[i + 4] == 'y' && endOfWord(file_text[i + 5])) ||
            /*bool*/
            (file_text[i] == 'b' && file_text[i + 1] == 'o' && file_text[i + 2] == 'o' && file_text[i + 3] == 'l' && endOfWord(file_text[i + 4])) ||
            /*case*/
            (file_text[i] == 'c' && file_text[i + 1] == 'a' && file_text[i + 2] == 's' && file_text[i + 3] == 'e' && endOfWord(file_text[i + 4])) ||
            /*character*/
            (file_text[i] == 'c' && file_text[i + 1] == 'h' && file_text[i + 2] == 'a' && file_text[i + 3] == 'r' && file_text[i + 4] == 'a' && file_text[i + 5] == 'c' && file_text[i + 6] == 't' && file_text[i + 7] == 'e' && file_text[i + 8] == 'r' && endOfWord(file_text[i + 9])) ||
            /*constant*/
            (file_text[i] == 'c' && file_text[i + 1] == 'o' && file_text[i + 2] == 'n' && file_text[i + 3] == 's' && file_text[i + 4] == 't' && file_text[i + 5] == 'a' && file_text[i + 6] == 'n' && file_text[i + 7] == 't' && endOfWord(file_text[i + 8])) ||
            /*else*/
            (file_text[i] == 'e' && file_text[i + 1] == 'l' && file_text[i + 2] == 's' && file_text[i + 3] == 'e' && endOfWord(file_text[i + 4])) ||
            /*elsif*/
            (file_text[i] == 'e' && file_text[i + 1] == 'l' && file_text[i + 2] == 's' && file_text[i + 3] == 'i' && file_text[i + 4] == 'f' && endOfWord(file_text[i + 5])) ||
            /*end*/
            (file_text[i] == 'e' && file_text[i + 1] == 'n' && file_text[i + 2] == 'd' && endOfWord(file_text[i + 3])) ||
            /*exit*/
            (file_text[i] == 'e' && file_text[i + 1] == 'x' && file_text[i + 2] == 'i' && file_text[i + 3] == 't' && endOfWord(file_text[i + 4])) ||
            /*float*/
            (file_text[i] == 'f' && file_text[i + 1] == 'l' && file_text[i + 2] == 'o' && file_text[i + 3] == 'a' && file_text[i + 4] == 't' && endOfWord(file_text[i + 5])) ||
            /*func*/
            (file_text[i] == 'f' && file_text[i + 1] == 'u' && file_text[i + 2] == 'n' && file_text[i + 3] == 'c' && endOfWord(file_text[i + 4])) ||
            /*if*/
            (file_text[i] == 'i' && file_text[i + 1] == 'f' && endOfWord(file_text[i + 2])) ||
            /*ifc*/
            (file_text[i] == 'i' && file_text[i + 1] == 'f' && file_text[i + 2] == 'c' && endOfWord(file_text[i + 3])) ||
            /*in*/
            (file_text[i] == 'i' && file_text[i + 1] == 'n' && endOfWord(file_text[i + 2])) ||
            /*integer*/
            (file_text[i] == 'i' && file_text[i + 1] == 'n' && file_text[i + 2] == 't' && file_text[i + 3] == 'e' && file_text[i + 4] == 'g' && file_text[i + 5] == 'e' && file_text[i + 6] == 'r' && endOfWord(file_text[i + 7])) ||
            /*is*/
            (file_text[i] == 'i' && file_text[i + 1] == 's' && endOfWord(file_text[i + 2])) ||
            /*mutator*/
            (file_text[i] == 'm' && file_text[i + 1] == 'u' && file_text[i + 2] == 't' && file_text[i + 3] == 'a' && file_text[i + 4] == 't' && file_text[i + 5] == 'o' && file_text[i + 6] == 'r' && endOfWord(file_text[i + 7])) ||
            /*natural*/
            (file_text[i] == 'n' && file_text[i + 1] == 'a' && file_text[i + 2] == 't' && file_text[i + 3] == 'u' && file_text[i + 4] == 'r' && file_text[i + 5] == 'a' && file_text[i + 6] == 'l' && endOfWord(file_text[i + 7])) ||
            /*null*/
            (file_text[i] == 'n' && file_text[i + 1] == 'u' && file_text[i + 2] == 'l' && file_text[i + 3] == 'l' && endOfWord(file_text[i + 4])) ||
            /*of*/
            (file_text[i] == 'o' && file_text[i + 1] == 'f' && endOfWord(file_text[i + 2])) ||
            /*or*/
            (file_text[i] == 'o' && file_text[i + 1] == 'r' && endOfWord(file_text[i + 2])) ||
            /*others*/
            (file_text[i] == 'o' && file_text[i + 1] == 't' && file_text[i + 2] == 'h' && file_text[i + 3] == 'e' && file_text[i + 4] == 'r' && file_text[i + 5] == 's' && endOfWord(file_text[i + 6])) ||
            /*out*/
            (file_text[i] == 'o' && file_text[i + 1] == 'u' && file_text[i + 2] == 't' && endOfWord(file_text[i + 3])) ||
            /*pkg*/
            (file_text[i] == 'p' && file_text[i + 1] == 'k' && file_text[i + 2] == 'g' && endOfWord(file_text[i + 3])) ||
            /*positive*/
            (file_text[i] == 'p' && file_text[i + 1] == 'o' && file_text[i + 2] == 's' && file_text[i + 3] == 'i' && file_text[i + 4] == 't' && file_text[i + 5] == 'i' && file_text[i + 6] == 'v' && file_text[i + 7] == 'e' && endOfWord(file_text[i + 8])) ||
            /*proc*/
            (file_text[i] == 'p' && file_text[i + 1] == 'r' && file_text[i + 2] == 'o' && file_text[i + 3] == 'c' && endOfWord(file_text[i + 4])) ||
            /*ptr*/
            (file_text[i] == 'p' && file_text[i + 1] == 't' && file_text[i + 2] == 'r' && endOfWord(file_text[i + 3])) ||
            /*range*/
            (file_text[i] == 'r' && file_text[i + 1] == 'a' && file_text[i + 2] == 'n' && file_text[i + 3] == 'g' && file_text[i + 4] == 'e' && endOfWord(file_text[i + 5])) ||
            /*subtype*/
            (file_text[i] == 's' && file_text[i + 1] == 'u' && file_text[i + 2] == 'b' && file_text[i + 3] == 't' && file_text[i + 4] == 'y' && file_text[i + 5] == 'p' && file_text[i + 6] == 'e' && endOfWord(file_text[i + 7])) ||
            /*then*/
            (file_text[i] == 't' && file_text[i + 1] == 'h' && file_text[i + 2] == 'e' && file_text[i + 3] == 'n' && endOfWord(file_text[i + 4])) ||
            /*type*/
            (file_text[i] == 't' && file_text[i + 1] == 'y' && file_text[i + 2] == 'p' && file_text[i + 3] == 'e' && endOfWord(file_text[i + 4])) ||
            /*when*/
            (file_text[i] == 'w' && file_text[i + 1] == 'h' && file_text[i + 2] == 'e' && file_text[i + 3] == 'n' && endOfWord(file_text[i + 4])) ||
            /*while*/
            (file_text[i] == 'w' && file_text[i + 1] == 'h' && file_text[i + 2] == 'i' && file_text[i + 3] == 'l' && file_text[i + 4] == 'e' && endOfWord(file_text[i + 5]))

        )
        {
            #ifdef DEBUG
                printf("found keyword\n");
            #endif
            isKeyword(file_text, &i);
        }
        else /*Check for character literal*/ if (file_text[i] == '\'' && file_text[i+2] == '\'')
        {
            #ifdef DEBUG
                printf("found character literal\n");
            #endif
            isCharacterLiteral(file_text, &i);
        }
        else /*Check for numeric literal*/ if (file_text[i] == '1' ||
                                               file_text[i] == '2' ||
                                               file_text[i] == '3' ||
                                               file_text[i] == '4' ||
                                               file_text[i] == '5' ||
                                               file_text[i] == '6' ||
                                               file_text[i] == '7' ||
                                               file_text[i] == '8' ||
                                               file_text[i] == '9' ||
                                               file_text[i] == '0' )
        {
            #ifdef DEBUG
                printf("found numeric literal\n");
            #endif
            isNumericLiteral(file_text, &i);
        }
        else /*Check for identifier*/ if (
        file_text[i] == 'A' || file_text[i] == 'B' || file_text[i] == 'C' || 
        file_text[i] == 'D' || file_text[i] == 'E' ||
        file_text[i] == 'F' || file_text[i] == 'G' || file_text[i] == 'H' || 
        file_text[i] == 'I' ||
        file_text[i] == 'J' || file_text[i] == 'K' || file_text[i] == 'L' || 
        file_text[i] == 'M' || 
        file_text[i] == 'N' || file_text[i] == 'O' || file_text[i] == 'P' || 
        file_text[i] == 'Q' || 
        file_text[i] == 'R' || file_text[i] == 'S' || file_text[i] == 'T' || 
        file_text[i] == 'U' ||
        file_text[i] == 'V' || file_text[i] == 'W' || file_text[i] == 'X' || 
        file_text[i] == 'Y' ||
        file_text[i] == 'Z' || file_text[i] == 'a' || file_text[i] == 'b' || 
        file_text[i] == 'c' ||
        file_text[i] == 'd' || file_text[i] == 'e' || file_text[i] == 'f' || 
        file_text[i] == 'g' ||
        file_text[i] == 'h' || file_text[i] == 'i' || file_text[i] == 'j' || 
        file_text[i] == 'k' ||
        file_text[i] == 'l' || file_text[i] == 'm' || file_text[i] == 'n' || 
        file_text[i] == 'o' ||
        file_text[i] == 'p' || file_text[i] == 'q' || file_text[i] == 'r' || 
        file_text[i] == 's' ||
        file_text[i] == 't' || file_text[i] == 'u' || file_text[i] == 'v' || 
        file_text[i] == 'w' ||
        file_text[i] == 'x' || file_text[i] == 'y' || file_text[i] == 'z')
        {
            #ifdef DEBUG
                printf("found identifier\n");
            #endif
            isIdentifier(file_text, &i);
        }
        else //if not any of the above categories, it's UNK
        {
            #ifdef DEBUG
                printf("found unknown\n");
            #endif
            isUnknown(file_text, &i);
        }
    }

    //close the file
    fclose(filePtr);
    return 0;
}

void isComment(char file_text[], int *index)
{
    #ifdef DEBUG
        printf("here6\n");
        printf("%c\n", file_text[*index]);
    #endif
    printf("%c%c", file_text[*index], file_text[*index + 1]);
    (*index) += 2;
    while (!endOfComment(file_text, index))
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf("%c%c (comment)\n", file_text[*index], file_text[*index + 1]);
    (*index) += 2;
}

void isString(char file_text[], int *index)
{
    #ifdef DEBUG
        printf("here: string function\n");
        printf("%c\n", file_text[*index]);
    #endif
    printf("%c", file_text[*index]);
    (*index)++;
    while (file_text[*index] != '"')
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf("%c (string)\n", file_text[*index]);
    (*index)++;
}

void isOperator(char file_text[], int *index){
    //Check for double character operators:
    if (file_text[*index] == ':' && file_text[*index+1] == '=')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '.' && file_text[*index + 1] == '.')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '<' && file_text[*index + 1] == '<')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '>' && file_text[*index + 1] == '>')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '<' && file_text[*index + 1] == '>')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '<' && file_text[*index + 1] == '=')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '>' && file_text[*index + 1] == '=')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '*' && file_text[*index + 1] == '*')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '!' && file_text[*index + 1] == '=')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '=' && file_text[*index + 1] == '>')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '{' && file_text[*index + 1] == ':')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else if (file_text[*index] == '}' && file_text[*index + 1] == ':')
    {
        printf("%c%c", file_text[*index], file_text[*index + 1]);
        (*index) += 2;
    }
    else { //Not a double character operator
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf(" (operator)\n");
}

void isKeyword(char file_text[], int *index){
    #ifdef DEBUG
        printf("Keyword Function\n");
    #endif
    while (!endOfWord(file_text[*index]))
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf(" (keyword)\n");
}

void isCharacterLiteral(char file_text[], int *index){
    #ifdef DEBUG
        printf("Char Lit Function\n");
        printf("%c\n", file_text[*index]);
    #endif
    printf("%c%c%c", file_text[*index], file_text[*index+1], file_text[*index+2]);
    (*index) += 3;
    printf(" (character literal)\n");
}

void isNumericLiteral(char file_text[], int *index){
    #ifdef DEBUG
        printf("Num Lit Function\n");
        printf("%c\n", file_text[*index]);
    #endif
    while (legalNumLitChar(file_text[*index]))
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf(" (numeric literal)\n");
}

void isIdentifier(char file_text[], int *index){
    #ifdef DEBUG
        printf("Identifier function\n");
        printf("%c\n", file_text[*index]);
    #endif
    while (legalIdentifierChar(file_text[*index]))
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }
    printf(" (identifier)\n");
}

void isUnknown(char file_text[], int *index)
{
    #ifdef DEBUG
        printf("Unknown Function\n");
        printf("%c\n", file_text[*index]);
    #endif
    while (!endOfWord(file_text[*index]))
    {
        printf("%c", file_text[*index]);
        (*index)++;
    }

    printf(" (UNK)\n");
    // (*index)++;
}

//This function checks for the end of the comment ('*/' in order)
bool endOfComment(char file_text[], int *index)
{
    if(file_text[*index] == '*')
    {
        if (file_text[*index + 1] == '/')
        {
            return true;
        }
        else {
            return false;
        }
    } else {
        return false;
    }
}
//We use this function to check if the character that is passed is the end of the word that preceeded it (meaning that it is a space, an operator, a newline, the end of the file, etc)
bool endOfWord(char c){
    if (c == ' ' ||
        c == '\n' ||
        c == '(' ||
        c == ')' ||
        c == '.' ||
        c == '<' ||
        c == '>' ||
        c == '+' ||
        // c == '_' ||
        c == '*' ||
        c == '/' ||
        c == '|' ||
        c == '&' ||
        c == ';' ||
        c == ',' ||
        c == ':' ||
        c == '=' ||
        c == '!' ||
        c == '[' ||
        c == ']' ||
        c == '{' ||
        c == '}' ||
        c == '$' ||
        c == '@' ||
        c == EOF
        ){
            return true;
        } else {
            return false;
        }
}

//Use this for checking if the character is a legal numeric literal character
bool legalNumLitChar(char c)
{
    if (c == '1' ||
        c == '2' ||
        c == '3' ||
        c == '4' ||
        c == '5' ||
        c == '6' ||
        c == '7' ||
        c == '8' ||
        c == '9' ||
        c == '0' ||
        c == 'A' ||
        c == 'B' ||
        c == 'C' ||
        c == 'D' ||
        c == 'E' ||
        c == 'F' ||
        c == 'a' ||
        c == 'b' ||
        c == 'c' ||
        c == 'd' ||
        c == 'e' ||
        c == 'f' ||
        c == '_' ||
        c == '.' ||
        c == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Use this for checking if the character is a legal identifier character
bool legalIdentifierChar(char c)
{
    if (c == '_' || c == '1' || c == '2' || c == '3' ||
        c == '4' || c == '5' || c == '6' || c == '7' ||
        c == '8' || c == '9' || c == '0' || c == 'A' ||
        c == 'B' || c == 'C' || c == 'D' || c == 'E' ||
        c == 'F' || c == 'G' || c == 'H' || c == 'I' ||
        c == 'J' || c == 'K' || c == 'L' || c == 'M' || 
        c == 'N' || c == 'O' || c == 'P' || c == 'Q' || 
        c == 'R' || c == 'S' || c == 'T' || c == 'U' ||
        c == 'V' || c == 'W' || c == 'X' || c == 'Y' ||
        c == 'Z' || c == 'a' || c == 'b' || c == 'c' ||
        c == 'd' || c == 'e' || c == 'f' || c == 'g' ||
        c == 'h' || c == 'i' || c == 'j' || c == 'k' ||
        c == 'l' || c == 'm' || c == 'n' || c == 'o' ||
        c == 'p' || c == 'q' || c == 'r' || c == 's' ||
        c == 't' || c == 'u' || c == 'v' || c == 'w' ||
        c == 'x' || c == 'y' || c == 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}