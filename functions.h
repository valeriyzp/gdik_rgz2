#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

struct Pixel
{
    unsigned char Blue, Green, Red;
};

extern enum Sizes{SmallArr = 9, SizePicture = 9, MediumArr = 18, BigArr = 27} Size;
extern int N;
extern int NumOfColors;
extern int **Array, **ResArray;
extern Pixel **ArrayImage, **ResArrayImage;
extern const int SizeOfFile;
extern char DirectoryOfImage[];
extern bool Image0_Num1;

int menu();
int **init_arr_numb();
Pixel **init_arr_pixel();
int **del_arr(int **Arr);
Pixel **del_arr_pixels(Pixel** Arr);
int **get_res(int **Arr);
Pixel **get_res(Pixel **Arr);
void change_size_of_array();
void change_N();
void change_num_colors();
void fill_arr(int **Arr);
void print_on_screen();
void print_arr_on_screen(int **Arr);
void write_to_file();
void write_arr_to_file(ofstream &OFile, int **Arr);
void write_image_to_file();
void init_from_image();
void sort_colors(Pixel *mas, int n);


#endif // FUNCTIONS_H
