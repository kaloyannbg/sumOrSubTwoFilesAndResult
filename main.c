// 2. Задача за събиране и изваждане

// Напишете програма за събиране и изваждане на произволно големи числа.
// операцията ( + или - ) и имената на три файла. В първите два файла са записани числата, които ще събираме
// или изваждаме, в третия файл е резултата. Примерно:

// 1. Да прочета числата от файловете

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

char *cpyFirstLineFromFileToArr(char *fileNameWithExt)
{
    FILE *fp = fopen(fileNameWithExt, "r");

    char buffer[512] = {0};

    fgets(buffer, 512, fp);

    char *arr = (char *)calloc(strlen(buffer), sizeof(char));

    strcpy(arr, buffer);

    fclose(fp);

    return arr;
}

// float *
float *fromStringToFloatArr(char *arr, char separator, int *floatCnt)
{

    char currStr[64] = {0};
    int currCnt = 0;
    int k = 0;
    float *floatsArr = (float *)calloc(64, sizeof(float));
    int floatCounter = 0;
    for (int i = 0; arr[i] != '\n'; i++)
    {
        memset(currStr, 0, 64);

        for (k = i; arr[k] != separator; k++)
        {
            currStr[currCnt++] = arr[k];
        }

        floatsArr[floatCounter++] = atof(currStr);

        currCnt = 0;
        i = k;
    }

    *floatCnt = floatCounter;

    return floatsArr;
}

void sumOrSubArrays(float *arr1, int arrSize1, float *arr2, int arrSize2, int sumOrSub, char *resFile)
{


    float res = 0.0;
    if(sumOrSub != '-' && sumOrSub != '+')
    {
        printf(" -- Invalid sumOrSub symbol (only - or +) \n");
        return;
    }
    if(arrSize1 != arrSize2)
    {
        printf(" -- Sorry, The numbers in file 1 and file 2 are not the same number -- ");
        return;
    }

    FILE *fp = fopen(resFile, "w");

    system("cls");

    for (int i = 0; i < arrSize1; i++)
    {
        res = arr1[i] + arr2[i];
        printf("%.2f + %.2f = %.2f \n", arr1[i], arr2[i], res);
        fprintf(fp, "%.2f + %.2f = %.2f \n", arr1[i], arr2[i], res);
    }
    if(fp)
    {
        printf(" \n -- The results is saved to file: %s -- \n ", resFile);
    }
    fclose(fp);



}

int main(int argc, char const *argv[])
{

    char *file1 = cpyFirstLineFromFileToArr("num1.txt");
    char *file2 = cpyFirstLineFromFileToArr("num2.txt");

    int arrSize1 = 0;
    int arrSize2 = 0;

    float *arrWithFloat1 = fromStringToFloatArr(file1, ',', &arrSize1);
    float *arrWithFloat2 = fromStringToFloatArr(file2, ',', &arrSize2);

    sumOrSubArrays(arrWithFloat1, arrSize1, arrWithFloat2, arrSize2, '+', "resFile.txt");

    free(file1);
    free(file2);

    return 0;
}
