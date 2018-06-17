#include "functions.h"

Pixel **get_res(Pixel **Arr)
{
    if(Arr == NULL) return NULL;
    ResArrayImage = del_arr_pixels(ResArrayImage);
    ResArrayImage = init_arr_pixel();
    Pixel *TempArray = new Pixel [SizePicture*SizePicture];

    NumOfColors=0;
    bool Temp;

    for(int i=0; i<SizePicture; i++)
    {
        for(int j=0; j<SizePicture; j++)
        {
            if(!NumOfColors)
            {
                TempArray[NumOfColors] = ArrayImage[i][j];
                NumOfColors++;
            }
            else
            {
                Temp=0;
                for(int f=0; f<NumOfColors; f++)
                {
                    if(ArrayImage[i][j].Red!=TempArray[f].Red) continue;
                    if(ArrayImage[i][j].Green!=TempArray[f].Green) continue;
                    if(ArrayImage[i][j].Blue!=TempArray[f].Blue) continue;
                    Temp=1;
                    break;
                }
                if(!Temp)
                {
                    TempArray[NumOfColors] = ArrayImage[i][j];
                    NumOfColors++;
                }
            }
        }
    }
    sort_colors(TempArray, NumOfColors);

    for(int i = 0; i < SizePicture; i++)
    {
        for(int j = 0; j < SizePicture; j++)
        {
            ResArrayImage[i][j].Red=ArrayImage[i][j].Red;
            ResArrayImage[i][j].Green=ArrayImage[i][j].Green;
            ResArrayImage[i][j].Blue=ArrayImage[i][j].Blue;
        }
    }

    int IndexColor, Counter;
    for(int i = 0; i < SizePicture; i++)
    {
        for(int j = 0; j < SizePicture; j++)
        {
            for(IndexColor = 0; IndexColor < NumOfColors; IndexColor++)
            {
                if(ArrayImage[i][j].Red == TempArray[IndexColor].Red &&
                   ArrayImage[i][j].Green == TempArray[IndexColor].Green &&
                   ArrayImage[i][j].Blue == TempArray[IndexColor].Blue)
                break;
            }
            if(IndexColor == NumOfColors - 1)
                continue;

            Counter = 0;
            if(i > 0)
            {
                if(j > 0)
                {
                    if(ArrayImage[i - 1][j - 1].Red == TempArray[IndexColor + 1].Red &&
                       ArrayImage[i - 1][j - 1].Green == TempArray[IndexColor + 1].Green &&
                       ArrayImage[i - 1][j - 1].Blue == TempArray[IndexColor + 1].Blue)
                        Counter++;
                }
                if(ArrayImage[i - 1][j].Red == TempArray[IndexColor + 1].Red &&
                   ArrayImage[i - 1][j].Green == TempArray[IndexColor + 1].Green &&
                   ArrayImage[i - 1][j].Blue == TempArray[IndexColor + 1].Blue)
                    Counter++;
                if(j < Size - 1)
                {
                    if(ArrayImage[i - 1][j + 1].Red == TempArray[IndexColor + 1].Red &&
                       ArrayImage[i - 1][j + 1].Green == TempArray[IndexColor + 1].Green &&
                       ArrayImage[i - 1][j + 1].Blue == TempArray[IndexColor + 1].Blue)
                        Counter++;
                }
            }

            if(j < Size - 1)
            {
                if(ArrayImage[i][j + 1].Red == TempArray[IndexColor + 1].Red &&
                   ArrayImage[i][j + 1].Green == TempArray[IndexColor + 1].Green &&
                   ArrayImage[i][j + 1].Blue == TempArray[IndexColor + 1].Blue)
                    Counter++;
            }

            if(i < Size - 1)
            {
                if(j < Size - 1)
                {
                    if(ArrayImage[i + 1][j + 1].Red == TempArray[IndexColor + 1].Red &&
                       ArrayImage[i + 1][j + 1].Green == TempArray[IndexColor + 1].Green &&
                       ArrayImage[i + 1][j + 1].Blue == TempArray[IndexColor + 1].Blue)
                        Counter++;
                }
                if(ArrayImage[i + 1][j].Red == TempArray[IndexColor + 1].Red &&
                   ArrayImage[i + 1][j].Green == TempArray[IndexColor + 1].Green &&
                   ArrayImage[i + 1][j].Blue == TempArray[IndexColor + 1].Blue)
                    Counter++;
                if(j > 0)
                {
                    if(ArrayImage[i + 1][j - 1].Red == TempArray[IndexColor + 1].Red &&
                       ArrayImage[i + 1][j - 1].Green == TempArray[IndexColor + 1].Green &&
                       ArrayImage[i + 1][j - 1].Blue == TempArray[IndexColor + 1].Blue)
                        Counter++;
                }
            }

            if(j > 0)
            {
                if(ArrayImage[i][j - 1].Red == TempArray[IndexColor + 1].Red &&
                   ArrayImage[i][j - 1].Green == TempArray[IndexColor + 1].Green &&
                   ArrayImage[i][j - 1].Blue == TempArray[IndexColor + 1].Blue)
                {
                    Counter++;
                }
            }

            if(Counter >= N)
            {
                ResArrayImage[i][j].Red = TempArray[IndexColor + 1].Red;
                ResArrayImage[i][j].Green = TempArray[IndexColor + 1].Green;
                ResArrayImage[i][j].Blue = TempArray[IndexColor + 1].Blue;
            }
        }
    }

    return ResArrayImage;
}

void change_N()
{
    do
    {
        cout << "Enter N (from 1 to 8): ";
        cin >> N;
        system("CLS");
    }while(N<1||N>8);
}

void change_num_colors()
{
    int NumOfColors_tmp;
    do
    {
        system("CLS");
        cout << "Enter the number of colors: ";
        cin >> NumOfColors_tmp;
    }while (NumOfColors_tmp < 2);
    NumOfColors = NumOfColors_tmp;
}

int **init_arr_numb()
{
    int **Arr = new int *[Size];
    for(int i = 0; i < Size; i++)
        Arr[i] = new int [Size];
    return Arr;
}

Pixel **init_arr_pixel()
{
    Pixel **Arr = new Pixel *[SizePicture];
    for(int i = 0; i < Size; i++)
        Arr[i] = new Pixel [SizePicture];
    return Arr;
}

void fill_arr(int **Arr)
{
    srand(time(0));

    for(int i = 0; i < Size; i++)
        for(int j = 0; j < Size; j++)
            Arr[i][j] = rand() % NumOfColors + 1;
}

int **del_arr(int** Arr)
{
    if(Arr == NULL)
        return NULL;
    for(int i = 0; i < Size; i++)
        delete [] Arr[i];

    delete [] Arr;
    return NULL;
}

Pixel **del_arr_pixels(Pixel** Arr)
{
    if(Arr == NULL)
        return NULL;
    for(int i = 0; i < SizePicture; i++)
        delete [] Arr[i];

    delete [] Arr;
    return NULL;
}

int **get_res(int **Arr)
{
    if(Arr == NULL) return NULL;
    ResArray = del_arr(ResArray);
    int **ResArray_tmp = init_arr_numb();

    int Counter = 0;
    for(int i = 0; i < Size; i++)
    {
        for(int j = 0; j < Size; j++)
        {
            Counter = 0;
            if(i > 0)
            {
                if(j > 0)
                {
                    if(Arr[i - 1][j - 1] == Arr[i][j] + 1)
                        Counter++;
                }
                if(Arr[i - 1][j] == Arr[i][j] + 1)
                    Counter++;
                if(j < Size - 1)
                {
                    if(Arr[i - 1][j + 1] == Arr[i][j] + 1)
                        Counter++;
                }
            }

            if(j < Size - 1)
            {
                if(Arr[i][j + 1] == Arr[i][j] + 1)
                    Counter++;
            }

            if(i < Size - 1)
            {
                if(j < Size - 1)
                {
                    if(Arr[i + 1][j + 1] == Arr[i][j] + 1)
                        Counter++;
                }
                if(Arr[i + 1][j] == Arr[i][j] + 1)
                    Counter++;
                if(j > 0)
                {
                    if(Arr[i + 1][j - 1] == Arr[i][j] + 1)
                        Counter++;
                }
            }

            if(j > 0)
            {
                if(Arr[i][j - 1] == Arr[i][j] + 1)
                {
                    Counter++;
                }
            }

            if(Counter >= N)
            {
                ResArray_tmp[i][j]=Arr[i][j]+1;
            }
            else
            {
                ResArray_tmp[i][j]=Arr[i][j];
            }
        }
    }

    return ResArray_tmp;
}
