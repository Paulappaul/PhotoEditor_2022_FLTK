#include "iostream"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "Stb_image_write.h"
#include "Image.h"
#include <stdint.h>
#include <cstdio>

Image::Image(const char* filename) {
if (read(filename))
    {std::cout << "The Following was read successfully: " << filename << std::endl;
     size = w*h*channels; /*Because its one byte per channel*/}
else{std::cout << "Failed to Read: " << filename << std::endl;}
                                    }        

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size]; 
} 


Image::Image(const Image& img) : Image(img.w, img.h, img.channels)
{ 
    memcpy(data, img.data, size);
}    

Image::~Image(){
    stbi_image_free(data);                      // see Basic Usage in Stb_Image.h
}

bool Image::read(const char* filename){

    data = stbi_load(filename, &w, &h, &channels, 0);
  if (data == NULL) {
    std::cerr << "Error: Failed to read image file " << filename << std::endl;
    return false;
  }
    return data !=NULL;
                                        }

bool Image::write(const char* filename){

    Imagetype type = getFileType(filename);
    int success; // a successful read will return an int: see stb.image.h
    switch(type){
        case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w*channels);
        break;
        case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100); // 100 determines quality
        break;
        case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
        case TGA: 
        success= stbi_write_tga(filename, w, h, channels, data);
        break;
                }
    if(success != 0) {
    printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return true;
                     }
    else {
    printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, w, h, channels, size);
    return false;
         }
}

Imagetype Image::getFileType (const char* filename){

    const char* ext = strrchr(filename, '.'); // gets the extention first,
    if(ext != nullptr){                       // checks for valid file extention, returns a nullptr if not
        if(strcmp(ext, ".png") == 0){         // if it equals zero, its matching, returns filetype
            return PNG;
        }
        else if (strcmp(ext, ".jpg") == 0){
            return JPG;
        }
        else if(strcmp(ext, ".bmp") == 0){
            return BMP;
        }
        else if(strcmp(ext, ".tga") == 0){
            return TGA;
        }
                      }
    return PNG;                               // forces file to PNG
                                                    }
Image& Image::grayscale_avg(){
                                             
    if(channels <3){
        std::cout << "Image has less than three channels, are you sure this image isn't greyscale?" << std::endl;
                   }
    else{ for(int i = 0; i < size; i+=channels){      
            int gray = (data[i] + data[i+1] + data[i+2])/3;                 //collects, sums and averages -> r+g+b/3 channels
            memset(data+i, gray, 3);
                                       }
                   }
        std::cout << "\e[30mgrayscale complete!\e[0m" << std::endl;
        return *this;
                            }

Image& Image::grayscale_lum(){
if(channels <3){
        std::cout << "Image has less than three channels, are you sure this image isn't greyscale?" << std::endl;
                   }
    else{ for(int i = 0; i < size; i+=channels){      
            int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2]; // grayscale relative to the way humans perceive color, rather then abolsute
            memset(data+i, gray, 3);
                                       }
                   }
        std::cout << "\e[30mgraylum complete!\e[0m" << std::endl;
        return *this;
                            }

Image& Image::colorMask(float r, float g, float b){
    if(channels < 3){
        std::cout << "Error: Color Mask requires at least 3 channels" << std::endl;
                    }
    else{
        for(int i= 0; i< size; i+=channels){
            data[i] *= r;
            data[i+1] *= g;
            data[i+2] *= b;
                                           }
        }
        return *this;
                                                  }

















