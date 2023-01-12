
#include "ImageStructsFunctions.h"


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
    return PNG;                               // forces file to PNG if fail
                    
}


//Image Processing

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


const char* filefind() {

    const char* filePath = fl_file_chooser("Select a file", "*", "");

    // Check if a file was selected
    if (filePath != nullptr)
    {
        // Print the file path
        std::cout << "Selected file: " << filePath << std::endl;

        return filePath;

    }
    else
    {
        std::cout << "No file was selected." << std::endl;
        return NULL;
    }

}

void Load_cb(Fl_Widget* w, void* data) {
    Fl_Button* Button = static_cast<Fl_Button*>(w);
    Fl_Box* box = static_cast<Fl_Box*>(data);
    //stolen here
    image = new Fl_JPEG_Image(filefind());
    previewImage = image->copy(380, 180);

    // Set the box's image to the loaded image
    box->image(previewImage);

    // Redraw the box to display the image
    box->redraw();

}

void GreyScale_cb(Fl_Widget* w, void* data) {

    Image GreyScale(filefind());
    GreyScale.grayscale_avg();
    GreyScale.write("Greyscaled image.jpg");

}

void GreyLum_cb(Fl_Widget* w, void* data) {

    Image GreyLum(filefind());
    GreyLum.grayscale_lum();
    GreyLum.write("Greylum image.jpg");

}

void slider_cb(Fl_Widget* w, void* data) {
    Fl_Slider* slider = static_cast<Fl_Slider*>(w);
    Fl_Box* box = static_cast<Fl_Box*>(data);
    // Convert the slider value to a string
    std::stringstream ss;
    ss << "Slider value: " << slider->value();
    std::string value_str = ss.str();

    // Print the value to the terminal, store the value in a global variable 
    if (slider->label() == "Red Slider") {
        r = slider->value();
        std::cout << "red: " << r << std::endl;
    }
    else if (slider->label() == "Green Slider") {

        g = slider->value();
        std::cout << "green: " << g << std::endl;
    }
    else if (slider->label() == "Blue Slider") {

        b = slider->value();
        std::cout << "blue: " << b << std::endl;

    }
    else { std::cout << "alas, there was nothing to be found" << std::endl; }


    // Update the label of the box widget with the new value
    box->copy_label(value_str.c_str());
    box->redraw();

}

void ColorCorrect(Fl_Widget* w, void* data) {

    Fl_Box* box = static_cast<Fl_Box*>(data);
    Image colorMask(filefind());
    colorMask.colorMask(r / 100.0, g / 100.0, b / 100.0);
    colorMask.write("Color_Corrected_Image.jpg");

    previewImage->uncache();

    Fl_JPEG_Image* TEMP = new Fl_JPEG_Image("Color_Corrected_Image.jpg");

    previewImage = TEMP->copy(380, 180);

    TEMP->uncache();
    // Set the box's image to the loaded image
    box->image(previewImage);

    // Redraw the box to display the image
    box->redraw();

}



    PhotoEngine::PhotoEngine(){
       
        //Set the qualities of the individual sliders
        redSlider->type(FL_HOR_SLIDER);
        redSlider->range(0, 100);
        redSlider->step(1);
        redSlider->value(50);
        redSlider->color(FL_RED);
        redSlider->selection_color(FL_BLACK);
        redSlider->callback(slider_cb, (void*)Sliderbox);

        GreenSlider->type(FL_HOR_SLIDER);
        GreenSlider->range(0, 100);
        GreenSlider->step(1);
        GreenSlider->value(50);
        GreenSlider->color(FL_GREEN);
        GreenSlider->callback(slider_cb, (void*)GsliderBox);

        BlueSider->type(FL_HOR_SLIDER);
        BlueSider->range(0, 100);
        BlueSider->step(1);
        BlueSider->value(50);
        BlueSider->color(FL_BLUE);
        BlueSider->callback(slider_cb, (void*)BsliderBox);

        //Intialises the callback function which draws the intial value of the Slider
        slider_cb(redSlider, (void*)Sliderbox);
        slider_cb(GreenSlider, (void*)GsliderBox);
        slider_cb(BlueSider, (void*)BsliderBox);

        //Execute Button
        Execute->callback(ColorCorrect, Image_Container);

        //SliderBox qualities
        Sliderbox->labelfont(FL_HELVETICA_BOLD);
        Sliderbox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        GsliderBox->labelfont(FL_HELVETICA_BOLD);
        BsliderBox->labelfont(FL_HELVETICA_BOLD);

        //Load Image Button
        Load_Image_Button->label("@fileopen");
        Load_Image_Button->callback(Load_cb, Image_Container);

        //GreyScale and lum Buttons
        GreyScale_Button->align(FL_ALIGN_CENTER);
        GreyLum_Button->align(FL_ALIGN_INSIDE);
        GreyScale_Button->callback(GreyScale_cb);
        GreyLum_Button->callback(GreyLum_cb);
    
    }

    PhotoEngine::~PhotoEngine() {


    }
















