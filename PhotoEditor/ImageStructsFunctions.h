#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define dirent direct

//Windows Directory helper
#include "dirent.h"

//stb
#include "stb_image.h"
#include "Stb_image_write.h"


//FLTK 
#include <FL/Fl.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Fl/FL_Image.H"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_JPEG_Image.H>
#include <Fl/Fl_PNG_Image.H>

//C, C++ packages
#include "iostream"
#include "sstream"
#include <stdint.h>
#include <cstdio>
#include <string>

//global Variables
int r, g, b;
Fl_Image* previewImage;
Fl_JPEG_Image* image;

enum Imagetype{                     // allows for switch statement and file checking
    PNG, JPG, BMP, TGA
};

// The Image struct handles the image processing.

struct Image {

uint8_t* data = NULL;               // unsigned 8-Bit integer (range: 0 through 255): contains picture data
size_t size = 0;                    // unsigned Long, keeps track of the Data

// Width, Height, Channels
int w;
int h;
int channels;

//Constructors
Image(const char* filename);         // calls read function below
Image(int w, int h, int channels);   // allows the creation of a raw picture
Image(const Image& img);             //Copy constructor, constant reference to another image

//Deconstructors
~Image();

//Functions
bool read(const char* filename); 
bool write(const char* filename);

Imagetype getFileType (const char* filename); // A function which returns an enum type. 

// these functions return of type Image
Image& grayscale_avg();
Image& grayscale_lum();
Image& colorMask(float r, float g, float b);



};

//Main Engine, this handles the GUI

struct PhotoEngine {
    //Constructor
    PhotoEngine();

    //Deconstructor
   ~PhotoEngine();

public:
    Fl_Window* MainW = new Fl_Window(800, 400, "PhotoEditor 2023");
    Fl_Box* Image_Container = new Fl_Box(400, 20, 380, 180);
    Fl_Box* Image_LABEL = new Fl_Box(400, 200, 380, 50, "Image Preview");
    Fl_Button* Load_Image_Button = new Fl_Button(400, 250, 50, 50, "Load_Image");
    Fl_Button* GreyScale_Button = new Fl_Button(20, 250, 50, 50, "Greyscale");
    Fl_Button* GreyLum_Button = new Fl_Button(90, 250, 50, 50, "Greylum");
    Fl_Slider* redSlider = new Fl_Slider(20, 20, 350, 50, "Red Slider");
    Fl_Slider* GreenSlider = new Fl_Slider(20, 100, 350, 50, "Green Slider");
    Fl_Slider* BlueSider = new Fl_Slider(20, 180, 350, 50, "Blue Slider");
    Fl_Box* Sliderbox = new Fl_Box(20, 320, 260, 50, "Slider");
    Fl_Box* GsliderBox = new Fl_Box(70, 320, 260, 50, "Slider2");
    Fl_Box* BsliderBox = new Fl_Box(190, 320, 260, 50, "slider3");
    Fl_Button* Execute = new Fl_Button(450, 300, 100, 100, "execute");

};


//Directory Functions

// locates the image the file. 
const char* filefind(); 

// Universal Load Callback
void Load_cb(Fl_Widget* w, void* data); 

//GreyScale Callback
void GreyScale_cb(Fl_Widget* w, void* data);

//GreyScale Lumanisance callback
void GreyLum_cb(Fl_Widget* w, void* data);

void slider_cb(Fl_Widget* w, void* data);

void ColorCorrect(Fl_Widget* w, void* data);