//images.c
//Purpose: To finalize and demonstrate a proficient understanding of all concepts learned in CS 135
//Authors: Ian Jameson and Andrew Beltran

#include <stdio.h>

#define STRINGSIZE 100
#define ROWSIZE 500
#define COLUMNSIZE 500

void uploadImage(FILE *stream, int *rowSize, int *columnSize, int twoDarray[][COLUMNSIZE]);
void displayImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]);
void editMenu(int editmenuChoice, int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]);
void brightenImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int outDarray[][COLUMNSIZE]);
void dimImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int outDarray[][COLUMNSIZE]);
void cropImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int *rowCrop, int *columnCrop, int outDarray[][COLUMNSIZE]);
void saveImage(FILE *stream, int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]);

int main() {
    int editmenuChoice, options;
    int originalPhoto[ROWSIZE][COLUMNSIZE];
    char filename[STRINGSIZE];
    int rowSize, columnSize;
    FILE *readfptr, *writefptr;

    do {
        printf("\n**ERINSTAGRAM**\n");
        printf("1. Load Image \n");
        printf("2. Display Image \n");
        printf("3. Edit \n");
        printf("0. Exit \n");
        printf("Enter a number (1-4) to see what happens to your photo: ");
        scanf("%d", &options);

        switch (options) {
            case 1:
                printf("What's the name of the image file? ");
                scanf("%s", filename);
                readfptr = fopen(filename, "r");
                if (readfptr == NULL) {
                    printf("File does not exist. Please try again. \n");
                }
                uploadImage(readfptr, &rowSize, &columnSize, originalPhoto);
                fclose(readfptr);
                break;
            case 2:
                displayImage(rowSize, columnSize, originalPhoto);
                break;
            case 3:
                do {
                    printf("Welcome to the editing menu \n");
                    printf("NOTE: You may only make one edit at a time. \n");
                    printf("If you desire to make multiple edits at a time, please save your photo and reupload it from the main menu. \n");
                    printf("Please enter your choice of edit from the following: \n");
                    printf("1. Brighten the photo \n");
                    printf("2. Dim the photo \n");
                    printf("3. Crop the photo to the desired margins \n");
                    printf("If no edit is desired, select 0 to return to the main menu. \n");
                    scanf("%d", &editmenuChoice);
                    if (editmenuChoice != 0) {
                        editMenu(editmenuChoice, rowSize, columnSize, originalPhoto);
                    }
                } while (editmenuChoice != 0);
                break;
            case 0:
                printf("Have a nice day!\n");
                break;
            default:
                printf("Please enter a valid number (1-4) \n");
                break;
        }
    } while (options != 0);

    return 0;
}

void uploadImage(FILE *stream, int *rowSize, int *columnSize, int twoDarray[][COLUMNSIZE]) {
    int row = 0;
    int col = 0;
    char c;
    while (fscanf(stream, "%c", &c) == 1) {
        if (c == '\n') {
            *columnSize = col;
            row++;
            col = 0;
        } else {
            twoDarray[row][col] = c - '0';
            col++;
        }
    }
    *rowSize = row;
}

void displayImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]) {
    char c;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            if (twoDarray[i][j] == 0) {
                c = ' ';
            } else if (twoDarray[i][j] == 1) {
                c = '.';
            } else if (twoDarray[i][j] == 2) {
                c = 'o';
            } else if (twoDarray[i][j] == 3) {
                c = 'O';
            } else if (twoDarray[i][j] == 4) {
                c = '0';
            }
            printf("%c", c);
        }
        printf("\n");
    }
    printf("\n");
}

void editMenu(int editmenuChoice, int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]) {
    int resultImage[ROWSIZE][COLUMNSIZE];
    int rowResult, columnResult;
    rowResult = rowSize;
    columnResult = columnSize;
    switch (editmenuChoice) {
        case 1:
            brightenImage(rowSize, columnSize, twoDarray, resultImage);
            break;
        case 2:
            dimImage(rowSize, columnSize, twoDarray, resultImage);
            break;
        case 3:
            cropImage(rowSize, columnSize, twoDarray, &rowResult, &columnResult, resultImage);
            break;
        case 0:
            printf("Returning to main menu... \n");
            break;
    }
    displayImage(rowResult, columnResult, resultImage); //PASSING BETWEEN OTHER FUNCTIONS MAY BE OCCURRING HERE!!!
    printf("Save Image? 1 - Yes, 0 - No");
    int option;
    char writtenFilename[STRINGSIZE];
    scanf("%d", &option);
    if (option == 1) {
        printf("Please enter what you would like your filename to be:");
        scanf("%s", writtenFilename);
        FILE *writefptr = fopen(writtenFilename, "w");
        saveImage(writefptr, rowResult, columnResult, resultImage);
        fclose(writefptr);
    }
}

void brightenImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int outDarray[][COLUMNSIZE]) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            if (twoDarray[i][j] >= 0 && twoDarray[i][j] < 4) {
                outDarray[i][j] = twoDarray[i][j] + 1;
            }
        }
    }
}

void dimImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int outDarray[][COLUMNSIZE]) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            if (twoDarray[i][j] > 0 && twoDarray[i][j] <= 4) {
                outDarray[i][j] = twoDarray[i][j] - 1;
            }
        }
    }
}

void cropImage(int rowSize, int columnSize, int twoDarray[][COLUMNSIZE], int *rowCrop, int *columnCrop, int outDarray[][COLUMNSIZE]) {
    int leftMargin, rightMargin, upperMargin, lowerMargin;
    printf("Please enter your desired margins for your cropped photo as follows: \n");
    printf("Left Margin:");
    scanf("%d", &leftMargin);
    printf("Right Margin:");
    scanf("%d", &rightMargin);
    printf("Upper Margin:");
    scanf("%d", &upperMargin);
    printf("Lower Margin:");
    scanf("%d", &lowerMargin);
    for (int i = upperMargin; i < rowSize - lowerMargin; i++) {
        for (int j = leftMargin; j < columnSize - rightMargin; j++) {
            outDarray[i - upperMargin][j - leftMargin] = twoDarray[i][j];
        }
    }
    *rowCrop = rowSize - upperMargin - lowerMargin;
    *columnCrop = columnSize - leftMargin - rightMargin;
}

void saveImage(FILE *stream, int rowSize, int columnSize, int twoDarray[][COLUMNSIZE]) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < columnSize; j++) {
            fprintf(stream, "%d", twoDarray[i][j]);
        }
        fprintf(stream, "\n");
    }
}
