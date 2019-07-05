/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : <Tamang Steve Dexter B.>
 * Student ID    : <1155124868>
 * Class/Section : <ENGG1110D>
 * Date          : <23/11/2018>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros */
#define MAX_GRID 30
#define MAX_WORDLIST 32
#define MAX_WORD 30
#define MAX_FILENAME 260

int readLetterGridFromConsole(char letterGrid[MAX_GRID][MAX_GRID])
{
    int row, col;
    int gridSize;

    printf("Enter the size of the letter grid:\n");
    scanf("%d", &gridSize);
    printf("Enter the letter grid:\n");

    for(row = 0; row < gridSize; row++)
    {
        for(col = 0; col < gridSize; col++)
        {
            scanf(" %c", &letterGrid[row][col]);
        }
    }

    return gridSize;
}
int readWordListFromConsole(char wordList[MAX_WORDLIST][MAX_WORD])
{
    int i;
    int listSize;

    printf("Enter the size of the word list:\n");
    scanf("%d", &listSize);
    printf("Enter the word list:\n");
    for(i = 0; i < listSize; i++)
    {
        scanf("%s", wordList[i]);
    }

    return listSize;
}
int readLetterGridFromFile(char letterGrid[MAX_GRID][MAX_GRID])
{
    FILE *fptr;
    int row, column, gridSize ;
    char filename[MAX_FILENAME];
    printf("Enter filename of the letter grid:\n");
    scanf("%s",filename);
    fptr = fopen(filename,"r");
    if(fptr == 0)
    {
        printf("Error in reading the letter grid file '%s'.The program has been terminated.\n",filename);
        exit(1);
    }
    fscanf(fptr,"%d",&gridSize);
    for(row = 0; row < gridSize ; row++)
    {
        for(column=0; column<gridSize; column++)
        {
            fscanf(fptr," %c",&letterGrid[row][column]);
        }
    }
    fclose(fptr);
    return gridSize ;

}
int readWordListFromFile(char wordList[MAX_WORDLIST][MAX_WORD])
{
    FILE *file;
    int i,listSize ;
    char fileName[FILENAME_MAX];
    printf("Enter filename of the word list:\n");
    scanf("%s",fileName);
    file = fopen(fileName,"r");
    if(file == NULL)
    {
        printf("Error in reading the word list file '%s'.The program has been terminated.\n",fileName);
        exit(1);
    }
    fscanf(file,"%d",&listSize);
    for(i=0; i<listSize; i++)
    {
        fscanf(file,"%s",wordList[i]);
    }
    fclose(file);
    return listSize;

}

/* Display the letter grid, assume gridSize <= 10 */
void printLetterGrid(char letterGrid[MAX_GRID][MAX_GRID], int gridSize)
{
    int row, col=0;
    int i = 0;
    int num =0;
    if(gridSize < 2 || gridSize > MAX_GRID)
    {
        printf("DEBUG: gridSize is %d but not between 2 and %d\n", gridSize, MAX_GRID);
        printf("Program terminates.\n");
        exit(1);
    }

    printf("### %d x %d Letter Grid ###\n", gridSize, gridSize);
    printf("  +");
    for(i=0; i<gridSize; i++)
    {
        printf(" %d",num + i);
    }
    printf("\n");
    for(i=0; i<gridSize+2; i++)
    {
        printf("+ ");
    }
    printf("\n");
    for(row=0; row<gridSize; row++)
    {
        printf("%d +",row);
        for(col=0;col<gridSize;col++){
           printf(" %c",letterGrid[row][col]);
        }
        printf("\n");

    }

}


/* Display the word list stored in wordList of size listSize with the matching status for each word */
void printWordList(char wordList[MAX_WORDLIST][MAX_WORD], int listSize, int matchingStatus[MAX_WORDLIST])
{
    int i;
    /* For debugging */
    if(listSize < 1 || listSize > MAX_WORDLIST)
    {
        printf("DEBUG: listSize is %d but not between 1 and %d\n", listSize, MAX_WORDLIST);
        printf("Program terminates.\n");
        exit(1);
    }

    printf("### Word List of Size %d ###\n", listSize);
    /* TODO: Print the word list with matching status */
    for(i=0; i<listSize; i++)
    {
        if(matchingStatus[i]==0)
        {
            printf("[ ] %s\n",wordList[i]);
        }
        else if(matchingStatus[i]==1)
        {
            printf("[X] %s\n",wordList[i]);
        }
    }
}

int checkWordList(char wordList[MAX_WORDLIST][MAX_WORD], int listSize, int matchingStatus[MAX_WORDLIST], char inputWord[MAX_WORD])
{
    /* TODO: Complete the function */
    int i;
    for(i=0; i<listSize; i++)
    {
        if(strcmp(inputWord,wordList[i])==0)
        {
            if (matchingStatus[i]!= 1)
                return i;
            else
                return listSize;

        }
        else if(strcmp(inputWord,"SECTBL")==0)
        {
            return 100;
        }
    }
    return -1;

}

int checkLetterGrid(char letterGrid[MAX_GRID][MAX_GRID], int gridSize, char inputWord[MAX_WORD], int matchRow, int matchCol, int matchDirection)
{
    int i,l;
    int inputSize = strlen(inputWord);
    int score=0;
    int correct =0;

    switch(matchDirection)
    {
    case 6 :

        if(matchCol + 1 > gridSize-1)
        {
            return -1;
        }
        else if(matchCol + inputSize <= gridSize)
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow][matchCol+i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }

        }
        break;
    case 4:
        if(matchCol -1 < 0)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow][matchCol-i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    case 2:
        if(matchRow +1 >gridSize-1)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow + i][matchCol] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        break;
    case 8:
        if(matchRow -1 < 0)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow-i][matchCol] == inputWord[i])
                {
                    score++;
                }
            }
            if(score == inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        break;
    case 3:
        if(matchRow + 1 > gridSize - 1 || matchCol + 1 > gridSize - 1)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow+i][matchCol+i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score == inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    case 7:
        if(matchRow -1 < 0 || matchCol - 1 < 0)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow-i][matchCol-i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    case 1:
        if(matchRow + 1 > gridSize - 1 || matchCol - 1 < 0)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow+i][matchCol-i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    case 9:
        if(matchRow - 1 < 0 || matchCol + 1 > gridSize-1)
        {
            return -1;
        }
        else
        {
            for(i=0; i<inputSize; i++)
            {
                if(letterGrid[matchRow-i][matchCol+i] == inputWord[i])
                {
                    score++;
                }
            }
            if(score==inputSize)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    }
}

/* Display the secret table */
void printSecretTable(char wordList[MAX_WORDLIST][MAX_WORD],int listSize,int gridSize,char letterGrid[MAX_WORD][MAX_WORD])
{
    int i=0,j=0,k=0,l=0,m=0;
    int row[listSize], col[listSize], dir[listSize];
    for(l=0; l<listSize; l++)
    {
        for(k=1; k!=5,k<=9; k++)
        {
            for(j=0; j<gridSize; j++)
            {
                for(i=0; i<gridSize; i++)
                {
                    int a = checkLetterGrid(letterGrid,gridSize,wordList[l],i,j,k);
                    if(a==1)
                    {
                        row[l]=i;
                        col[l]=j;
                        dir[l]=k;
                    }
                }
            }
        }
    }
    printf("\n### Secret Table ###\n");
    for(m=0; m<listSize; m++)
    {
        printf("%s: R%d C%d D%d \n",wordList[m],row[m],col[m],dir[m]);
    }

}
int main()
{
    int i=0;
    int gridSize;
    char letterGrid[MAX_GRID][MAX_GRID] = {{0},{0}};
    int listSize;
    char wordList[MAX_WORDLIST][MAX_WORD] = {{0},{0}};
    int matchingStatus[MAX_WORDLIST] = {0};
    char inputWord[MAX_WORD][MAX_WORD];
    int matchRow,matchCol,matchDirection;
    for(i=0; i<listSize; i++)
    {
        matchingStatus[i] = 0;
    }
    char YES_OR_NO ;
    printf("Read data from file [Y/N]?\n");
    scanf("%c",&YES_OR_NO);

    if(YES_OR_NO == 'N')
    {
        gridSize = readLetterGridFromConsole(letterGrid);
        listSize = readWordListFromConsole(wordList);
    }
    else if(YES_OR_NO == 'Y')
    {
        gridSize = readLetterGridFromFile(letterGrid);
        listSize = readWordListFromFile(wordList);
    }
    while(1)
    {
        printLetterGrid(letterGrid,gridSize);
        printWordList(wordList,listSize,matchingStatus);
        int a;
        while(1)
        {
            printf("Enter the word:\n");
            scanf("%s",inputWord);
            a = checkWordList(wordList,listSize,matchingStatus,inputWord);
            if(a==-1)
            {
                printf("The input word is not in the word list.\n\n");
                printLetterGrid(letterGrid,gridSize);
                printWordList(wordList,listSize,matchingStatus);
            }
            else if(a==listSize)
            {
                printf("The input word has been matched already.\n\n");
                printLetterGrid(letterGrid,gridSize);
                printWordList(wordList,listSize,matchingStatus);
            }
            else if(a == 100)
            {
                printSecretTable(wordList,listSize,gridSize,letterGrid);
                printf("\n");
            }
            else
            {
                break;
            }
        }

        printf("Enter the row number, the column number, and the direction (1-4 or 6-9)\n");
        scanf("%d%d%d",&matchRow,&matchCol,&matchDirection);
        int answer = checkLetterGrid(letterGrid,gridSize,inputWord,matchRow,matchCol,matchDirection);
        if(answer == 1)
        {
            printf("The word is found!\n");
            matchingStatus[a] = 1;
        }
        if(answer == 0 )
        {
            printf("The input word cannot be found in the given location.\n\n");
        }
        if(answer == -1)
        {
            printf("The search exceeds the boundary of the letter grid.\n\n");

        }

        int j, score =0;
        for(j=0; j<listSize; j++)
        {
            if(matchingStatus[j]==1)
            {
                score++;
            }
        }
        if(score == listSize)
        {
            printLetterGrid(letterGrid,gridSize);
            printWordList(wordList,listSize,matchingStatus);
            printf("You have finished the puzzle.\nCongratulations!");
            break;
        }
    }
    return 0;
}
