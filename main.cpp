#include "functions.h"

Sizes Size = SmallArr;
int N = 1;
int NumOfColors = 2;
int **Array = NULL, **ResArray = NULL;
Pixel **ArrayImage = NULL, **ResArrayImage = NULL;
const int SizeOfFile = 32;
char DirectoryOfImage[SizeOfFile];
bool Image0_Num1 = 1;

int main()
{
    int Choice;
    do
    {
        Choice = menu();
        switch(Choice)
        {
            case 1:
            {
                change_size_of_array();
                change_num_colors();
                Array = init_arr_numb();
                fill_arr(Array);
                ResArray = get_res(Array);
                Image0_Num1=1;

                break;
            }
            case 2:
            {
            	change_N();
                init_from_image();
                ResArrayImage=get_res(ArrayImage);
                Image0_Num1=0;

                break;
            }
            case 3:
            {
                change_N();
                if(Image0_Num1)
                {
                    ResArray = get_res(Array);
                    print_on_screen();
                }
                else
                {
                    ResArrayImage=get_res(ArrayImage);
                }

                break;
            }
            case 4:
            {
                if(Image0_Num1) print_on_screen();

                break;
            }
            case 5:
            {
                if(Image0_Num1)
                {
                    write_to_file();
                }
                else
                {
                    write_image_to_file();
                }

                break;
            }
            case 0:
            {
                cout << "Program completed...\n";
                cin.get();
                return 0;
            }
        }
    }while(Choice != 0);
}
