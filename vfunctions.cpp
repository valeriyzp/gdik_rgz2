#include "functions.h"

void init_from_image()
{
    char Directory[SizeOfFile];
    cout<<"Enter the address of the file: ";
    cin.ignore();
    cin.getline(Directory, SizeOfFile);

    ifstream FromFile(Directory, ios::in|ios::binary);
    if(!FromFile.is_open())
    {
        cout << "File could not be opened\n";
        cout << "\nPress Enter to continue...\n";
        cin.get();

        return;
    }
    char Format[2];
    FromFile.read((char*)Format, 2);
    if(Format[0]!='B'||Format[1]!='M')
    {
        cout << "Not a valid file extension\n";
        cout << "\nPress Enter to continue...\n";
        cin.get();

        return;
    }
    short int BitToPixel;
    FromFile.seekg(28, FromFile.beg);
    FromFile.read((char*)&BitToPixel, 2);
    if(BitToPixel!=24)
    {
        cout << "Bits per pixel not 24\n";
        cout << "\nPress Enter to continue...\n";
        cin.get();

        return;
    }
    int SizePixel[2];
    FromFile.seekg(18, FromFile.beg);
    FromFile.read((char*)SizePixel, 8);
    if(SizePixel[0]!=SizePicture||SizePixel[1]!=SizePicture)
    {
        cout << "Resolution of picture is not supported\n";
        cout << "Supported resolution: ";
        cout << SizePicture << 'x' << SizePicture << " pixels\n";
        cout << "\nPress Enter to continue...\n";
        cin.get();

        return;
    }

    strcpy(DirectoryOfImage, Directory);
    ArrayImage = del_arr_pixels(ArrayImage);
    ArrayImage = init_arr_pixel();

    int AdresStartImage;
    FromFile.seekg(10, FromFile.beg);
    FromFile.read((char*)&AdresStartImage, 4);
    FromFile.seekg(AdresStartImage, FromFile.beg);

    int Fill;
    Fill = 4-((3*SizePicture)%4);
    if(Fill == 4) Fill = 0;
    char Temp;
    for(int i=SizePicture-1; i>=0; i--)
    {
        for(int j=0; j<SizePicture; j++)
        {
            FromFile.read((char*)&ArrayImage[i][j], 3);
        }
        FromFile.read((char*)&Temp, Fill);
    }
}


void sort_colors(Pixel *mas, int n)
{
    double test1, test2;
    for(int d=n/2; d>0; d/=2)
        for(int i=d;i<n;i++)
            for(int j=i; j>=d;j-=d)
            {
                test2=0.3*mas[j].Red+0.59*mas[j].Green+0.11*mas[j].Blue;
                test1=0.3*mas[j-d].Red+0.59*mas[j-d].Green+0.11*mas[j-d].Blue;
                if(!(test1<test2)||!((test2-test1)>0.00001)) break;
                swap(mas[j],mas[j-d]);
            }
}

int menu()
{
    int ResMenu;
    do
    {
        system("CLS");
        cout << "Menu:\n";
        cout << "1 - Initialize a new array with numbers\n";
        cout << "2 - Initialize a new array from the image\n";
        cout << "3 - Change the number of adjacent cells and recount the result\n";
        cout << "4 - Print the result on the screen\n";
        cout << "5 - Output the result to a file\n";
        cout << "0 - Quit\n\n";
        cout << "Make you choice: ";
        cin >> ResMenu;
    }while(ResMenu < 0 || ResMenu > 5);
    system("CLS");
    return ResMenu;
}


void change_size_of_array()
{
    Array = del_arr(Array);
    ResArray = del_arr(ResArray);
    int SizeOfArray;
    do
    {
        system("CLS");
        cout << "Select the size of the array you want to create:\n";
        cout << "1 - Small size\n";
        cout << "2 - Medium size\n";
        cout << "3 - Big size\n\n";
        cout << "Make your choice: ";
        cin >> SizeOfArray;
    } while(SizeOfArray < 1 || SizeOfArray > 3);
    cout<<"\n";

    switch(SizeOfArray)
    {
        case 1:
        {
            Size = SmallArr;
            break;
        }
        case 2:
        {
            Size = MediumArr;
            break;
        }
        case 3:
        {
            Size = BigArr;
            break;
        }
    }
}

void print_on_screen()
{
    if(Array == NULL || ResArray == NULL) return;
    cout << "The entered array:\n\n";
    print_arr_on_screen(Array);
    cout << "\nResult array (where N = " << N << ") :\n\n";
    print_arr_on_screen(ResArray);
    cout << "\nPress Enter to continue...\n";
    cin.get();
    cin.get();
}

void print_arr_on_screen(int **Arr)
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
            cout << Arr[i][j] << ' ';
        cout << endl;
    }
}

void write_image_to_file()
{
    if(ArrayImage == NULL || ResArrayImage == NULL)
        return;
    char Directory[SizeOfFile];
    cout << "Enter the address of the file: ";
    cin.ignore();
    cin.getline(Directory, SizeOfFile);
    ofstream OutFile(Directory, ios::out|ios::binary);
    if(!OutFile.is_open())
    {
        cout << "File could not be opened\n";
        return;
    }
    ifstream FromFile(DirectoryOfImage, ios::binary);
    if(!FromFile.is_open())
    {
        cout << "File could not be written\n";
        return;
    }
    for(int i=0; i<54; i++)
    {
        char ch;
        FromFile.read((char*)&ch, 1);
        OutFile.write((char*)&ch, 1);
    }

    int Fill;
    Fill = 4-((3*SizePicture)%4);
    if(Fill == 4) Fill = 0;
    char ch=0;

    for(int i=SizePicture-1; i>=0; i--)
    {
        for(int j=0; j<SizePicture; j++)
        {
            OutFile.write((char*)&ResArrayImage[i][j], 3);
        }
        OutFile.write((char*)&ch, Fill);
    }
    return;
}

void write_to_file()
{
    if(Array == NULL || ResArray == NULL)
        return;
    char Directory[SizeOfFile];
    cout << "Enter the address of the file: ";
    cin.ignore();
    cin.getline(Directory, SizeOfFile);
    ofstream OutFile(Directory, ios::app);
    if(!OutFile.is_open())
    {
        cout << "File could not be opened\n";
        return;
    }
    OutFile << "\nThe entered array:\n\n";
    write_arr_to_file(OutFile, Array);
    OutFile << "\nResult array (where N = " << N << ") :\n\n";
    write_arr_to_file(OutFile, ResArray);
}

void write_arr_to_file(ofstream &OFile, int **Arr)
{
    for(int i = 0; i < Size; i++)
    {
        for(int j = 0; j < Size; j++)
            OFile << Arr[i][j] << ' ';
        OFile << endl;
    }
}
