// slide_viewer.cpp. Created with C++ standard 2017 by David Boe
/* A simple program to show which pixel on a slide to retrieve and display in 
a viewer pixel after a rotation of the slide with respect to the viewer

Here the operation is applied to one display pixel, but to get all of the 
pixels to display, this same operation is applied to every pixel. This
operation is embarrassingly parallel and so is amenable to GPU implementation.

For information on rotation matrices: https://mathworld.wolfram.com/RotationMatrix.html */

#include <stdio.h>
#include <math.h>
#include <memory>
#include <vector>

using namespace std;

constexpr double pi = 3.14159265358979323846;

struct motion {
    double theta = 0; // rotation angle (radians)
    int x, y = 0;     // Translation (pixels)
};

class Display {
    const int V_x, V_y; // Viewer coordinate (pixels), x = horizontal axis, y = vertical axis
    double S_x, S_y;    // Slide coordinate displayed in the viewer coordinate (pixels), x = horizontal axis, y = vertical axis
    // Can also include data members for translation of slide
    Display(const Display &); // Disable copy constructor
public: 
    Display(int a, int b, double c, double d) : V_x(a), V_y(b), S_x(c), S_y(d) {};
    Display( int a, int b) : V_x(a), V_y(b), S_x(double(a)), S_y(double(b)) {}; 
    ~Display(){};
    void Sx(double c) {S_x = c;};
    void Sy(double d) {S_y = d;};
    int Vx() const {return V_x;};
    int Vy() const {return V_y;};
    double Sx() const {return S_x;};
    double Sy() const {return S_y;}; 
    vector<double> rotate_slide(unique_ptr<motion> & R);
    // Translation function
};

/* Rotation - Updates the slide coordinates to display in viewer coordinate V
after a rotation of the slide around the center. */
vector<double> Display::rotate_slide(unique_ptr<motion> & R) {
    double c = cos(R->theta) * Sx() + sin(R->theta) * Sy();
    double d = -sin(R->theta) * Sx() + cos(R->theta) * Sy();
    Sx(c);
    Sy(d);
    return vector<double> {c, d};
};

int main() {
    /* Initialize the Display object for viewer pixel (1,0).
    Initially, the viewer and slide coordinate frames are aligned with each other.*/ 
    class Display V1(1, 0, 1, 0);

    // Output display on initial loading
    printf("\nOn initially loading the slide into the viewer:");
    printf("\nViewer pixel (%d,%d) displays slide pixel (%.2f, %.2f)", V1.Vx(), V1.Vy(), V1.Sx(), V1.Sy());
    
    // Rotation of the slide counter-clockwise with respect to the viewer
    double angle = 90; // Try angle = 45;
    double theta = angle*pi/180;
    auto r = make_unique<motion>(motion{theta});

    // Slide pixel to display in viewer pixel V after rotation theta around the center
    vector<double> slide_pixel_rot_1 = V1.rotate_slide(r);

    // Output display after slide rotation 
    printf("\n\nAfter %f degree rotation of the slide by the user:", angle);
    printf("\nViewer pixel (%d,%d) displays slide pixel (%.2f, %.2f)", V1.Vx(), V1.Vy(), slide_pixel_rot_1[0], slide_pixel_rot_1[1]);
    
    // Rotation of the slide clockwise with respect to the viewer
    angle = -angle; 
    theta = -theta;
    r->theta = theta;

    // Slide pixel to display in viewer pixel V after rotation theta around the center
    vector<double> slide_pixel_rot_2 = V1.rotate_slide(r);

    // Output display after slide rotation 
    printf("\n\nAfter %f degree rotation of the slide by the user:", angle);
    printf("\nViewer pixel (%d,%d) displays slide pixel (%.2f, %.2f)\n\n", V1.Vx(), V1.Vy(), slide_pixel_rot_2[0], slide_pixel_rot_2[1]);

    return 0;
};
