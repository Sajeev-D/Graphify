#include<stdio.h>
#include <stdbool.h>
int pixel_buffer_start; // global variable

// Function prototypes
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void swap(int *a, int *b);
void draw_line(int x0, int y0, int x1, int y1, short int line_color);
void get_intersection_between_two_linear_lines(int x0, int x1, int y0, int y1, int x2, int x3, int y2, int y3);
void get_intersection_between_linear_line_and_quadratic_curve(int x0, int x1, int y0, int y1, int a, int b, int c); // Not tested

// May have to use the gsl library. Check if it is available in the monitor program.
void get_intersection_between_two_quadratic_curves(); // Not implemented
void get_intersection_between_cubic_curve_and_quadratic_curve(); // Not implemented
void get_intersection_between_a_cubic_curve_and_a_linear_line(); // Not implemented
void get_intersection_between_two_cubic_curves(); // Not implemented
// double square_root(int discriminant); // There is a way to use sqrt() function in Monitor Program

int main(){
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();

    // Define the coordinates of the two lines
    int x0 = 0, y0 = 0, x1 = 180, y1 = 150;
    int x2 = 150, y2 = 170, x3 = 319, y3 = 0;

    // Draw the two lines
    draw_line(x0, y0, x1, y1, 0x001F);   // this line is blue
    draw_line(x2, y2, x3, y3, 0x07E0); // this line is green

    get_intersection_between_two_linear_lines(x0, x1, y0, y1, x2, x3, y2, y3);
    
    return 0;
}

// Function definitions
void get_intersection_between_two_linear_lines(int x0, int x1, int y0, int y1, int x2, int x3, int y2, int y3){
    // {x0, y0} and {x1, y1} are the two points on the first line
    // {x2, y2} and {x3, y3} are the two points on the second line

    // Calculate the intersection point
    int dx1 = x1 - x0;
    int dy1 = y1 - y0;
    int dx2 = x3 - x2;
    int dy2 = y3 - y2;

    float denominator = (dy2 * dx1) - (dy1 * dx2);

    if (denominator == 0) {
        printf("The lines are parallel and do not intersect.\n");
        return 0;
    }

    float ua = ((dx2 * (y0 - y2)) - (dy2 * (x0 - x2))) / denominator;
    float ub = ((dx1 * (y0 - y2)) - (dy1 * (x0 - x2))) / denominator;

    if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) {
        // The lines intersect at this point
        int ix = x0 + (ua * dx1);
        int iy = y0 + (ua * dy1);
        printf("The lines intersect at (%d, %d).\n", ix, iy);
    } else {
        printf("The lines do not intersect within the line segments.\n");
    }
}

void get_intersection_between_linear_line_and_quadratic_curve(int x0, int y0, int x1, int y1, int a, int b, int c) {
    /*
    {x0, y0} and {x1, y1} are the two points on the linear line
    a, b, and c are the coefficients of the quadratic equation
    */

    // Calculate the slope and y-intercept of the line
    float m = (float)(y1 - y0) / (x1 - x0);
    float n = y0 - m * x0;

    // Calculate the coefficients of the quadratic equation
    int A = a;
    int B = b - m;
    int C = c - n;

    // Calculate the discriminant
    int discriminant = (B * B) - (4 * A * C);

    if (discriminant < 0) {
        printf("The linear line and quadratic curve do not intersect.\n");
        return;
    } else if (discriminant == 0) {
        // Calculate the intersection point
        int x = -B / (2 * A);
        int y = (a * x * x) + (b * x) + c;
        printf("The linear line and quadratic curve intersect at (%d, %d).\n", x, y);
    } else {
        // Calculate the two intersection points
        int x1 = (-B + sqrt(discriminant)) / (2 * A);
        int x2 = (-B - sqrt(discriminant)) / (2 * A);
        int y1 = (a * x1 * x1) + (b * x1) + c;
        int y2 = (a * x2 * x2) + (b * x2) + c;
        printf("The linear line and quadratic curve intersect at (%d, %d) and (%d, %d).\n", x1, y1, x2, y2);
    }
}


void get_intersection_between_two_quadratic_curves() {
    // To be implemented
}

void get_intersection_between_cubic_curve_and_quadratic_curve() {
    // To be implemented
}

void get_intersection_between_a_cubic_curve_and_a_linear_line() {
    // To be implemented
}

void get_intersection_between_two_cubic_curves() {
    // To be implemented
}

// double square_root(int discriminant) {
//     if (discriminant < 0) {
//         // Handle negative discriminants (impossible to compute square root)
//         return -1.0; // Or you can choose to handle it differently based on your requirements
//     }

//     double guess = discriminant / 2.0; // Initial guess
//     double prev_guess; // Previous guess

//     // Iterate until convergence
//     do {
//         prev_guess = guess;
//         guess = (prev_guess + discriminant / prev_guess) / 2.0;
//     } while (prev_guess != guess);

//     return guess;
// }

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
