#include "global.h"

int pixel_buffer_start; // global variable

// Function prototypes
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void swap(int *a, int *b);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
int main(void);

// Global variables
// int coefficients[6];
// int intersectionArray[8];

int main(){
    coefficients[0] = 1;
    coefficients[1] = 0;
    coefficients[2] = -1;
    coefficients[3] = 1;
    linear_linear_intersection(coefficients);
    return 0;
}

/*Create a fucntion to get the min and max of a quadratic curve

 input - gloabl array of coefficents of the qudratic curve
 output - */

void plot_pixel(int x, int y, short int line_color) // function to draw a pixel on the screen (Works)
{
    volatile short int *one_pixel_address; // Compute address of pixel

        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);

        *one_pixel_address = line_color;
} // call in draw_line()

void clear_screen() // Works
{
    int x, y;
    for (x = 0; x < 320; x++)
        for (y = 0; y < 240; y++)
            plot_pixel(x, y, 0x0);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color)
{
    // if the line is steep, transpose the coordinates
    bool is_steep = abs(y1 - y0) > abs(x1 - x0); 
    if (is_steep)
    {
        swap(&x0, &y0);
        swap(&x1, &y1);
    }

    // always draw from left to right so make sure x0 < x1
    if (x0 > x1)
    {
        swap(&x0, &x1);
        swap(&y0, &y1);
    } 

    // Keep track of the direction of the line
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax / 2);
    int y = y0;

    // Determine the direction of the line for y
    int y_step;
    if (y0 < y1)
        y_step = 1;
    else
        y_step = -1;
    
    for (int x = x0; x <= x1; x++)
    {  
        // Draw the pixel on the flattened coordinate system
        if (is_steep)
            plot_pixel(y, x, line_color);
        else
            plot_pixel(x, y, line_color);
        error = error + deltay;

        // If the error is greater than 0, move to the next pixel in the y direction
        if (error >= 0)
        {
            // Move to the next pixel
            y = y + y_step;
            error = error - deltax;
        }
    }
}
