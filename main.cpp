// Program    : Final Project - Pokedex
// Authors    : Minh Ngo, Melanie Ruiz, Sitie Cai, Diego Martinez, Enrique Cabrera,                  
//              Adan Cabrera
// Course     : CISP 360 Online/Xu
// Section    : 25324
// Description: A program that organizes the first 31 Pokemon in a specific
//              order

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

// prototype section
void sort_hp(string names[], string type[], int hp[], int SIZE);
void sort_type(string names[], string type[], int hp[], int SIZE);
void pick_random(const int SIZE, string names[], string type[], int hp[], int& randomnum);
void sort_name(ostream& stream, string names[], string type[], int hp[], int SIZE);
void search_poke(string array[], string type[], int hp[], const int);
int* sort_lowest(int hp[], int SIZE);
//

int main() {
    // definitions
    ifstream infile;
    ofstream outfile;
    const int SIZE = 30;

    vector<int> random_num(1);

    string names[SIZE];
    string type[SIZE];
    int hp[SIZE];
    int choice;
    int randomnum;
    int i = 0;
    int* ptrlowest;

    // infile section
    infile.open("pokedex.txt");
    if (!infile.is_open()) {
        cout << "Cannot open input file, please make sure the file is correctly "
            "named and is under the right address"
            << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cout << "Successfully read file under 'c:\\temp\\names.txt'." << endl;
    }

    // data input
    while (!infile.eof()) {
        for (int i = 0; i < SIZE; i++) {
            infile >> names[i] >> type[i] >> hp[i];
        }
    }


    // outfile section
    outfile.open("report.txt");
    if (!outfile.is_open()) {
        cout << "Cannot open output file" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cout << "Successfully outputted file under 'c:\\temp\\report.txt'." << endl;
    }

    cout << endl << endl << "*--------------------------------*" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "|            Pokedex             |" << endl;
    cout << "|                                |" << endl;
    cout << "|                                |" << endl;
    cout << "*--------------------------------*" << endl << endl << endl;

    //welcome message
    cout << "Welcome Trainer! Introducing the Pokedex!" << endl;

    do {
        cout << "Please select on of the following fuctions." << endl << endl;

        do {
            cout << "1. Sort Pokemons by types." << endl;
            cout << "2. Sort Pokemons by HP." << endl;
            cout << "3. Search a Pokemon by name." << endl;
            cout << "4. Pokemon randomizer!" << endl;
            cout << "5. Show Pokemon with lowest HP." << endl;
            cout << "6. Exit Program." << endl << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if ((choice < 1) || (choice > 6)) {
                cout << "Only input 1, 2, 3, 4, 5 and 6 are accepted. Please try again."
                    << endl
                    << endl;
            }
        } while ((choice < 1) || (choice > 6));

        if (choice == 1) {
            sort_type(names, type, hp, SIZE); // Enrique
        }
        else if (choice == 2) {
            sort_hp(names, type, hp, SIZE); // Sitie, highest to lowest
        }
        else if (choice == 3) {
            search_poke(names, type, hp, SIZE); //Diego
        }
        else if (choice == 4) {
            pick_random(SIZE, names, type, hp, randomnum); // Adan
            random_num[i] = randomnum;
            random_num.push_back(1);
            i = i + 1;
        }
        else if (choice == 5) {
            ptrlowest = sort_lowest(hp, SIZE);

            int index = *ptrlowest;
            cout << endl << "The Pokemon with the lowest HP is: " << names[index] << endl;
            cout << "With the HP of: " << hp[index] << endl;
        }
        else if (choice == 6) {
            //data output
            outfile << endl << left;
            outfile << setw(15) << "Name" << setw(15) << "Type" << setw(15) << "HP" << endl
                << "================================" << endl;
            for (int t = 0; t < i; t++)
            {
                outfile << left;
                outfile << setw(15) << names[random_num[t]] << setw(15) << type[random_num[t]] << setw(15) << hp[random_num[t]] << endl;
            }

            sort_name(outfile, names, type, hp, SIZE);

            cout << "Thank you for using our program!" << endl;
            exit(EXIT_FAILURE);
        }
        cout << endl << endl;
    } while (choice != 6);

    

    infile.close();
    outfile.close();
}

void sort_type(string names[], string type[], int hp[], int SIZE) {
    cout << endl << left;
    cout << setw(15) << "Name" << setw(15) << "Type" << setw(15) << "HP" << endl
        << "================================" << endl;
    int minIndex;
    string minValue;

    for (int start = 0; start < (SIZE - 1); start++) {
        minIndex = start;
        minValue = type[start];
        for (int index = start + 1; index < SIZE; index++) {
            if (type[index] < minValue) {
                minValue = type[index];
                minIndex = index;
            }
        }
        swap(type[minIndex], type[start]);
        swap(hp[minIndex], hp[start]);
        swap(names[minIndex], names[start]);
    }

    for (int i = 0; i < SIZE; i++) {
        cout << left;
        cout << setw(15) << names[i] << setw(15) << type[i] << setw(15) << hp[i]
            << endl;
    }
}

void sort_hp(string names[], string type[], int hp[], int SIZE) {
    cout << endl << left;
    cout << setw(15) << "Name" << setw(15) << "Type" << setw(15) << "HP" << endl
        << "================================" << endl;
    int maxElement;
    int index;

    for (maxElement = SIZE - 1; maxElement > 0; maxElement--) {
        for (index = 0; index < maxElement; index++) {
            if (hp[index] < hp[index + 1]) {
                swap(type[index], type[index + 1]);
                swap(names[index], names[index + 1]);
                swap(hp[index], hp[index + 1]);
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        cout << setw(15) << names[i] << setw(15) << type[i] << setw(15) << hp[i]
            << endl;
    }
}

void pick_random(const int SIZE, string names[], string type[], int hp[], int& randomnum)
{
    int RandomNumber;
    srand(time(0));
    RandomNumber = rand() % SIZE;

    randomnum = RandomNumber;
    

    cout << endl
        << "Name: " << names[RandomNumber] << endl
        << "Type: " << type[RandomNumber] << endl
        << "HP: " << hp[RandomNumber] << endl;
}

void sort_name(ostream& stream, string names[], string type[], int hp[], int SIZE)
{
    stream << endl << left;
    stream << setw(15) << "Name" << setw(15) << "Type" << setw(15) << "HP" << endl
        << "================================" << endl;
    int start, minIndex;
    string minVal;
    for (start = 0; start < (SIZE - 1); start++)
    {
        minIndex = start;
        minVal = names[start];
        for (int i = start + 1; i < SIZE; i++)
        {
            if (names[i] < minVal)
            {
                minVal = names[i];
                minIndex = i;
            }
        }
        swap(names[minIndex], names[start]);
        swap(type[minIndex], type[minIndex]);
        swap(hp[minIndex], hp[start]);
    }
    for (int i = 0; i < SIZE; i++)
    {
        stream << left;
        stream << setw(15) << names[i] << setw(15) << type[i] << setw(15) << hp[i] << endl;
    }
}

void search_poke(string nArray[], string tArray[], int hpArray[],
    const int size) {
    // variables
    string search;
    int index(0);

    // pokemon name search header
    cout << endl << "*-------------------------------*" << endl;
    cout << "|                               |" << endl;
    cout << "|       Who's that Pokemon?     |" << endl;
    cout << "|                               |" << endl;
    cout << "*-------------------------------*" << endl;

    // prompt user to search database
    cout << "Please input Pokemon (case sensitive): ";
    cin >> search;
    cout << endl;

    bool found = false;
    while (index < size && !found) {
        if (nArray[index] == search) {
            found = true;
            cout << "Name: " << nArray[index] << "\n";
            cout << "Type: " << tArray[index] << "\n";
            cout << "HP: " << hpArray[index] << "\n";
        }
        index++;      
    }
}


int* sort_lowest(int hp[], int SIZE)
{
    int* ptrlowest = nullptr;
    int lowest;
    int lowest_index;

    lowest = hp[0];
    for (int i = 1; i < SIZE; i++) {
        if (hp[i] < lowest) {
            lowest = hp[i];
            lowest_index = i;
        }
    }

    ptrlowest = &lowest_index;

    return ptrlowest;
}