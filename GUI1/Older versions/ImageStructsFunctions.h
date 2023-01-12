

enum Imagetype{                     // allows for switch statement and file checking
    PNG, JPG, BMP, TGA
};

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