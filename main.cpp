/*
    - This file is a c++ file to image processor (Assignment 1) that contains filters who edit the photos with a menu.
    - Student 1 : Youssef Mahrous Abd El-Ghani Abd El-Fattah --> ID : 20240703 --> Section : S31.
    - Student 2 : Ahmed Ayman Fawzy Abbas --> ID : 20240016 --> Section : S31.
    - Student 3 : Mohamed Ayman Fathallah Abd El-Rahman --> ID : 20240478 --> Section : S31.
    - Youssef Mahrous made filter 3 & 6 & 9 & 12 (Invert & Rotation & Frame & Blur).
    - Ahmed Ayman made filter 1 & 7 & 10 & 4 (Grayscale & Darken And Lighten & Edges & Merge).
    - Mohamed Ayman made filter 2 & 5 & 8 & 11 (Black And White & Flip & Crop & Resizing).
    - We all made the menu.
    - Menu has 4 main options (Load / Filters / Save / Exit).
    - Repo Link : https://github.com/yousefmahrous/image_processor/
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

void black_white(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int r = img(i, j, 0);
            unsigned int g = img(i, j, 1);
            unsigned int b = img(i, j, 2);
            unsigned int luminance = 0.299 * r + 0.587 * g + 0.114 * b;
            unsigned int value = (luminance >= 128) ? 255 : 0;
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = value;
                
            }
        }
    }
}

void flip(Image& img) {
    cout << "1 - Horizontal Flip" << endl;
    cout << "2 - Vertical Flip" << endl;
    int choose_flip;
    cin >> choose_flip;
    if (choose_flip == 1) {
        for (int i = 0; i < img.width / 2; i++){
            for (int j = 0; j < img.height; j++){
                for (int k = 0; k < img.channels; k++){
                    unsigned int temp = img(i, j, k);
                    img(i, j, k)= img(img.width-i-1,j,k);
                    img(img.width - i -1, j, k) = temp;
                }
            }
        }
    } else if (choose_flip == 2) {
        for (int i = 0; i < img.width; i++){
            for (int j = 0; j < img.height / 2; j++){
                for (int k = 0; k < img.channels; k++){
                    unsigned int temp = img(i, j, k);
                    img(i, j, k) = img(i,img.height - j - 1, k);
                    img(i, img.height - j - 1, k) = temp;
                }
            }
        }
    }
}

void darken_lighten(Image& img) {
    cout << "1 - Dark" << endl;
    cout << "2 - Light" << endl;
    string choose;
    cin >> choose;
    if (choose == "1") {
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    int x = img(i, j, k) * 0.5;
                    img(i, j, k) = x;
                }
            }
        }
    } else if (choose == "2") {
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    int x = img(i, j, k) * 1.5;
                    if (x > 255) x = 255;
                    img(i, j, k) = x;
                }
            }
        }
    }
}

void gray(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < img.channels; ++k) {
                avg += img(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < img.channels; ++k) {
                img(i, j, k) = avg;
            }
        }
    }
}

void frame(Image& img) {
    Image temp(img.width * 1.1, img.height * 1.1);
    cout << "1 - Simple Frame" << endl;
    cout << "2 - Decorative frame" << endl;
    int frame;
    cin >> frame;
    if (frame == 1) {
        for (int i = 0; i < temp.width; ++i) {
            for (int j = 0; j < temp.height; ++j) {
                temp(i, j, 0) = 26;
                temp(i, j, 1) = 35;
                temp(i, j, 2) = 126;
            }
        }
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    temp(i + ((temp.width - img. width) / 2), j + ((temp.height - img. height) / 2), k) = img(i, j, k);
                }
            }
        }
        img = temp;
    } else if (frame == 2) {
        for (int i = 0; i < temp.width / 2; ++i) {
            for (int j = 0; j < temp.height / 2; ++j) {
                temp(i, j, 0) = 255;
                temp(i, j, 1) = 215;
                temp(i, j, 2) = 0;
            }
        }
        for (int i = temp.width / 2; i < temp.width ; ++i) {
            for (int j = temp.height / 2; j < temp.height; ++j) {
                for (int k = 0; k < temp.channels; ++k) {
                    temp(i, j, k) = 255;
                }
            }
        }
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    temp(i + ((temp.width - img. width) / 2), j + ((temp.height - img. height) / 2), k) = img(i, j, k);
                }
            }
        }
        img = temp;
    }
}

void blur(Image& img) {
    cout << "Please enter the radius : ";
    int radius;
    cin >> radius;
    Image temp = img;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                int sum = 0;
                int cnt = 0;
                for (int x = -radius; x <= radius; x++) {
                    for (int y = -radius; y <= radius; y++) {
                        if (x + i < img.width && x + i >= 0 && y + j < img.height && y + j >= 0) {
                            sum += img(i + x, j + y, k);
                            cnt++;
                        }
                    }
                }

                sum /= cnt;
                temp(i, j, k) = sum;
            }
        }
    }
    img = temp;
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
    cout << "Filter 3 // Black And White" << endl;
    cout << "Filter 4 // Flip" << endl;
    cout << "Filter 5 // Darken_Lighten" << endl;
    cout << "Filter 6 // Gray" << endl;
    cout << "Filter 7 // Frame" << endl;
    cout << "Filter 8 // Blur" << endl;
    string filter;
    cin >> filter;
    if (filter == "1") invert(img);
    else if (filter == "2") rotate(img);
    else if (filter == "3") black_white(img);
    else if (filter == "4") flip(img);
    else if (filter == "5") darken_lighten(img);
    else if (filter == "6") gray(img);
    else if (filter == "7") frame(img);
    else if (filter == "8") blur(img);
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
