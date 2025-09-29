/*
    - This file is a c++ file to image processor (Assignment 1) that contains filters who edit the photos with a menu.
    - Student 1 : Youssef Mahrous Abd El-Ghani Abd El-Fattah --> ID : 20240703 --> Section : S23.
    - Student 2 : Ahmed Ayman Fawzy Abbas --> ID : 20240016 --> Section : S33.
    - Student 3 : Mohamed Ayman Fathallah Abd El-Rahman --> ID : 20240478. --> Section : S23.
    - Youssef Mahrous made filter 3 & 6 (Invert & Rotation).
    - Ahmed Ayman made filter 1 & 7 (Grayscale & Darken And Lighten).
    - Mohamed Ayman made filter 2 & 5 (Black And White & Flip).
    - Menu has 4 main options (Load / Filters / Save / Exit).
    - Rebo Link : 
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "Image_Class.h"

using namespace std;

// Global Variables

Image img;
string open;

// Functions of Filters

void invert(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                img(i, j ,k) = 255 - img(i, j ,k);
            }
        }
    }
}

void rotate(Image& img) {
    cout << "Please choose the angle: 90, 180, 270" << endl;
    int angle;
    cin >> angle;
    if (angle == 270) {
        Image temp(img.height, img.width);
        for (int j = 0; j < img.height; ++j) {
            for (int i = 0; i < img.width; ++i) {
                for (int k = 0; k < img.channels; ++k) {
                    temp(j, img.width - 1 - i, k) = img.getPixel(i, j, k);
                }
            }
        }
        img = temp;
    } else if (angle == 180) {
        Image temp(img.width, img.height);
        for (int j = 0; j < img.height; ++j) {
            for (int i = 0; i < img.width; ++i) {
                for (int k = 0; k < img.channels; ++k) {
                    temp(img.width - 1 - i, img.height - 1 - j, k) = img.getPixel(i, j, k);
                }
            }
        }
        img = temp;
    } else if (angle == 90) {
        Image temp(img.height, img.width);
        for (int j = 0; j < img.height; ++j) {
            for (int i = 0; i < img.width; ++i) {
                for (int k = 0; k < img.channels; ++k) {
                    temp(img.height - 1 - j, i, k) = img.getPixel(i, j, k);
                }
            }
        }
        img = temp;
    }
}

// Functions of Menu

void save_fun(string open, Image& img) {
    if (open.size() == 0) {
        cout << "There is not image loadded to save" << endl;
        return;
    }
    cout << "Do you want to save it on the same name or change? s / c" << endl;
    string name;
    cin >> name;
    if (name == "s") {
        img.saveImage(open);
    } else if (name == "c") {
        cout << "Please write the name and extension of the image to save : " << endl;
        string save;
        cin >> save;
        if(img.saveImage(save));
    }
}

void exit_fun(string open, Image& img) {
    cout << "Do you want to save the image before exit? y / n" << endl;
    string exitSave;
    cin >> exitSave;
    if (exitSave == "y") {
        if (open.size() == 0) {
            cout << "There is not image loadded to save" << endl;
            exit(0);
        }
        cout << "Do you want to save it on the same name or change? s / c" << endl;
        string name;
        cin >> name;
        if (name == "s") {
            img.saveImage(open);
            exit(0);
        } else if (name == "c") {
            cout << "Please write the name and extension of the image to save : " << endl;
            string save;
            cin >> save;
            if(img.saveImage(save));
            exit(0);
        }
    } else if (exitSave == "n") {
        exit(0);
    }
}

void load_fun(string open, Image& img) {
    if (img.loadNewImage(open)) cout << "The image is loadded" << endl;
    else if (open == "save") {
        save_fun(open, img);
    } else if (open == "exit") {
        exit_fun(open, img);
    }
}

void filter_fun(string open, Image& img) {
    cout << "Filter 1 // Invert" << endl;
    cout << "Filter 2 // Rotate" << endl;
    string filter;
    cin >> filter;
    if (filter == "1") invert(img);
    else if (filter == "2") rotate(img);
    else if (filter == "load") {
        cout << "Do you want to save the image before loading a new one? y / n" << endl;
        string saveBeforeLoad;
        cin >> saveBeforeLoad;
        if (saveBeforeLoad == "y") {
            save_fun(open, img);
        }
        cout << "Please, Load the image : " << endl;
        cin >> open;
        load_fun(open, img);
    }
    else if (filter == "save") save_fun(open, img);
    else if (filter == "exit") exit_fun(open, img);
}


int main() {
    while (true) {
        cout << "Please choose, load / filters / save / exit" << endl;
        string option;
        cin >> option;
        if (option == "load") {
            if (open.size() != 0) {
                cout << "Do you want to save the image before loading a new one? y / n" << endl;
                string saveBeforeLoad;
                cin >> saveBeforeLoad;
                if (saveBeforeLoad == "y") {
                    save_fun(open, img);
                }
            }
            cout << "Please, Load the image : " << endl;
            cin >> open;
            load_fun(open, img);
        } else if (option == "filters") {
            filter_fun(open, img);
        } else if (option == "save") {
            save_fun(open, img);
        } else if (option == "exit") {
            exit_fun(open, img);
        }
    }
    return 0;
}