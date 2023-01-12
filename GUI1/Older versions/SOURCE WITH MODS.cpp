/*#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Box.H>
#include "FL/Fl_Button.H"
#include <iostream>

#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_File_Chooser.H>
*/
#include "dirent.h"
#define dirent direct
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <iostream>
#include <FL/Fl_JPEG_Image.H>
#include "Fl/FL_Image.H"

int main(int argc, char** argv) {


	//case JPEG
	Fl_JPEG_Image* image = new Fl_JPEG_Image("image.jpg");
	Fl_Image* image2 = image->copy(200, 200);

	int w = image->w();
	int h = image->h();

	Fl_Window* window = new Fl_Window(w, h);
	Fl_Box* box = new Fl_Box(0, 0, w, h);

	// Set the box's image to the loaded image
	box->image(image);

	// Redraw the box to display the image
	box->redraw();



	window->end();
	window->show(argc, argv);

	return Fl::run();
}

/*
* 
* 
* 
// Callback function for the slider value change event
// The box widget is passed as the data argument via the void* (which is a undefinded pointer)
//This is cast to the FL* and is used in turn to update the label of widget
//The Slider widget is passed through the first variable  and is cast to a ptr. This allows for access to the widgets value function to return the slider value

void slider_cb(Fl_Widget* w, void* data) {
	Fl_Slider* slider = static_cast<Fl_Slider*>(w);
	Fl_Box* box = static_cast<Fl_Box*>(data);

	// Convert the slider value to a string
	std::stringstream ss;
	ss << "Slider value: " << slider->value();
	std::string value_str = ss.str();

	// Update the label of the box widget with the new value
	box->copy_label(value_str.c_str());
	box->redraw();

	// Print the value to the terminal
	std::cout << value_str << std::endl;
}

int main(int argc, char** argv) {

	//creates the objects
	Fl_Window* window = new Fl_Window(800, 600);
	Fl_Box* Sliderbox = new Fl_Box(20, 10, 260, 20);
	Fl_Button* GreyScaleBox = new Fl_Button(20, 400, 100, 100, "Greyscale");
	Fl_Button* GreyLumBox = new Fl_Button(140, 400, 100, 100, "Greyscale Lum");
	Fl_Slider* slider = new Fl_Slider(20, 40, 260, 100, "R");
	Fl_Slider* sliderG = new Fl_Slider(280, 40, 260, 100, "G");
	Fl_Slider* sliderB = new Fl_Slider(560, 40, 260, 100, "Blue");

	//defines slider quality
	slider->type(FL_HOR_SLIDER);
	slider->range(0, 100);
	slider->step(1);
	slider->value(50);
	slider->callback(slider_cb, (void*)Sliderbox);

	sliderG->type(FL_HOR_SLIDER);
	sliderG->range(0, 100);
	sliderG->step(1);
	sliderG->value(50);

	sliderB->type(FL_HOR_SLIDER);
	sliderB->range(0, 100);
	sliderB->step(1);
	sliderB->value(50);
	

	//Intialises the callback function which draws the intial value of the Slider
	slider_cb(slider, (void*)Sliderbox); 

	//box quality
	Sliderbox->labelfont(FL_HELVETICA_BOLD);
	Sliderbox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
	
	GreyLumBox->color(152);

	window->end();
	window->show(argc, argv);
	return Fl::run();
}*/