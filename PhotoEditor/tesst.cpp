#include "MasterImageHeader.h"


void Load_cb(Fl_Widget* w, void* data){

	Fl_Button* Button = static_cast<Fl_Button*>(w);
	Fl_Box* box = static_cast<Fl_Box*>(data);

	Fl_JPEG_Image* image = new Fl_JPEG_Image(filefind());
	Fl_Image* image2 = image->copy(380, 180);

	// Set the box's image to the loaded image
	box->image(image2);

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

	// Print the value to the terminal
	std::cout << value_str << std::endl;

	// Update the label of the box widget with the new value
	box->copy_label(value_str.c_str());
	box->redraw();


}


int main(int argc, char** argv)
{

	Fl_Window* MainW = new Fl_Window(800, 600, "PhotoEditor 2023");
	Fl_Box* Image_Container = new Fl_Box(400, 20, 380, 180);
	Fl_Box* Image_LABEL = new Fl_Box(400, 200, 380, 50, "Image Preview");
	Fl_Button* Load_Image_Button = new Fl_Button(400, 250, 50, 50, "Load_Image");
	Fl_Button* GreyScale_Button = new Fl_Button(20, 250,50, 50, "Greyscale");
	Fl_Button* GreyLum_Button = new Fl_Button(90, 250, 50, 50, "Greylum");
	Fl_Slider* redSlider = new Fl_Slider(20, 20, 350, 50, "Red Slider");
	Fl_Slider* GreenSlider = new Fl_Slider(20, 100, 350, 50, "Green Slider");
	Fl_Slider* BlueSider = new Fl_Slider(20, 180, 350, 50, "Blue Slider");
	Fl_Box* Sliderbox = new Fl_Box(200, 250, 77, 50, "Slider");

	redSlider->type(FL_HOR_SLIDER);
	redSlider->range(0, 100);
	redSlider->step(1);
	redSlider->value(25);
	redSlider->color(FL_RED);
	redSlider->selection_color(FL_BLACK);
	redSlider->callback(slider_cb, (void*)Sliderbox);

	GreenSlider->type(FL_HOR_SLIDER);
	GreenSlider->range(0, 100);
	GreenSlider->step(1);
	GreenSlider->value(50);
	GreenSlider->color(FL_GREEN);
	//GreenSlider->callback(slider_cb, (void*)Sliderbox);

	BlueSider->type(FL_HOR_SLIDER);
	BlueSider->range(0, 100);
	BlueSider->step(1);
	BlueSider->value(50);
	BlueSider->color(FL_BLUE);
	//BlueSider->callback(slider_cb,(void*)Sliderbox);

	//Intialises the callback function which draws the intial value of the Slider
	slider_cb(redSlider, (void*)Sliderbox);

	Sliderbox->labelfont(FL_HELVETICA_BOLD);
	Sliderbox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);




	Load_Image_Button->label("@fileopen");
	Load_Image_Button->callback(Load_cb, Image_Container);

	GreyScale_Button->align(FL_ALIGN_CENTER);
	GreyLum_Button->align(FL_ALIGN_INSIDE);
	GreyScale_Button->callback(GreyScale_cb);

	GreyLum_Button->callback(GreyLum_cb);



	MainW->show(argc, argv);
	return Fl::run();

}