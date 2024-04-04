#include "global.h"

void linear_linear_intersection(int coef[6]);
void linear_quadratic_intersection(int coef[6]);
void disp_intersections(double intersections[8]);
void maxMinOfQuadratic(int coef[6]);
void linear_axis_intersection(int coef[6]);
void quadratic_axis_intersection(int coef[6]);
int get_hex(int num);

void linear_axis_intersection(int coef[6]){
  double m = coef[0];
  double c = coef[1];

  if (m == 0) { // The line is horizontal
    // Intersection with x-axis (y = 0)
    if (c == 0) {
      printf("The line intersects the x-axis at any point where y = 0.\n");
    } else {
      printf("The line does not intersect the x-axis.\n");
    }
    // Intersection with y-axis (x = 0)
    intersectionWithAxis[2] = 0;
    intersectionWithAxis[3] = c;
    printf("The line intersects the y-axis at (0, %.2f).\n", c);
  } else { // The line is neither vertical nor horizontal
    // Intersection with x-axis (y = 0)
    double x_intersect = -c / m;
    intersectionWithAxis[0] = x_intersect;
    intersectionWithAxis[1] = 0;
    printf("The line intersects the x-axis at (%.2f, 0).\n", x_intersect);

    // Intersection with y-axis (x = 0)
    intersectionWithAxis[2] = 0;
    intersectionWithAxis[3] = c;
    printf("The line intersects the y-axis at (0, %.2f).\n", c);
  }
}


void quadratic_axis_intersection(int coef[6]){
  double a = coef[0];
  double b = coef[1];
  double c = coef[2];

  // Calculate the roots of the quadratic function (intersection with x-axis)
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    // The quadratic function does not intersect the x-axis
    intersectionWithAxis[0] = -1;
    intersectionWithAxis[1] = -1;
    intersectionWithAxis[2] = -1;
    intersectionWithAxis[3] = -1;
    printf("The quadratic function does not intersect the x-axis.\n");
  } else {
    double sqrt_discriminant = sqrt(discriminant);
    double x1 = (-b - sqrt_discriminant) / (2 * a);
    double x2 = (-b + sqrt_discriminant) / (2 * a);
    intersectionWithAxis[0] = x1;
    intersectionWithAxis[1] = 0;
    intersectionWithAxis[2] = x2;
    intersectionWithAxis[3] = 0;
    printf("The quadratic function intersects the x-axis at (%.2f, 0) and (%.2f, 0).\n", x1, x2);
  }

  // Intersection with y-axis (x = 0)
  intersectionWithAxis[4] = 0;
  intersectionWithAxis[5] = c;
  printf("The quadratic function intersects the y-axis at (0, %.2f).\n", c);
}


void linear_linear_intersection(int coef[6]) {  // tested and working
  int m1 = coef[0];
  int c1 = coef[1];
  int m2 = coef[2];
  int c2 = coef[3];

  // Calculate the intersection point
  int denominator = m1 - m2;

  // Display nothing on the HEX displays
  intersectionArray[2] = -1; 
  intersectionArray[3] = -1;
  intersectionArray[2] = -1; 
  intersectionArray[3] = -1;

  disp_intersections(intersectionArray);

  if (denominator == 0) {
    printf("The lines are parallel and do not intersect.\n");
    return;
  }

  double x = (double)(c2 - c1) / denominator;
  double y = m1 * x + c1;

  // Store the intersection point in the array
  intersectionArray[0] = x;
  intersectionArray[1] = y;

  // The other 2 HEX displays are set to display a dash
  intersectionArray[2] = -1; 
  intersectionArray[3] = -1;

  disp_intersections(intersectionArray);
  printf("The lines intersect at (%.2f, %.2f).\n", x, y);
}

void linear_quadratic_intersection(int coef[6]) {  // tested and working
  double m = coef[0];
  double c = coef[1];
  double a = coef[2];
  double b = coef[3];
  double d = coef[4];

  // Calculate the coefficients of the quadratic equation
  double A = a;
  double B = b - m;
  double C = c - d;

  // Calculate the discriminant
  double discriminant = (B * B) - (4 * A * C);

  if (discriminant < 0) {
    printf("The linear line and quadratic curve do not intersect.\n");
    return;
  } else if (discriminant == 0) {
    // Calculate the intersection point
    double x = (double)(-B) / (2 * A);
    double y = m * x + c;
    // Store the intersection point in the array
    intersectionArray[0] = x;
    intersectionArray[1] = y;

    // The other 2 HEX displays are set to display a dash
    intersectionArray[2] = -1; 
    intersectionArray[3] = -1;
    disp_intersections(intersectionArray);

    printf("The linear line and quadratic curve intersect at (%.2f, %.2f).\n",
           x, y);
  } else {
    // Calculate the two intersection points
    double x1 = (double)(-B + sqrt(discriminant)) / (2 * A);
    double y1 = m * x1 + c;
    double x2 = (double)(-B - sqrt(discriminant)) / (2 * A);
    double y2 = m * x2 + c;

    // Store the intersection points in the array
    intersectionArray[0] = x1;
    intersectionArray[1] = y1;
    intersectionArray[2] = x2;
    intersectionArray[3] = y2;

    printf(
        "The linear line and quadratic curve intersect at (%.2f, %.2f) and "
        "(%.2f, %.2f).\n",
        x1, y1, x2, y2);

    disp_intersections(intersectionArray);
  }
}

void disp_intersections(double intersections[8]){
	//int intersections[8] = {1,9,1,0,41,11,1};
	volatile int *HEX1 = (int *) 0xff200020;
	volatile int *HEX2 = (int*) 0xFF200030;

  int intersection[8] = {(int)intersections[0], (int)intersections[1], (int)intersections[2], (int)intersections[3], (int)intersections[4], (int)intersections[5], (int)intersections[6], (int)intersections[7]};
  
  // check if the contents of the intersections array are single digits
  for(int i = 0; i < 8; i++){

    if(intersection[i] != -1){
      if(intersection[i] < 0 || intersection[i] > 9){
        printf("Invalid intersection point. Please enter single digit numbers.\n");
        return;
      }
    }
  }

    *HEX1 = (get_hex(intersection[0]) << 24) | // HEX3
           (get_hex(intersection[1]) << 16) | // HEX2
           (get_hex(intersection[2]) << 8) |  // HEX1
           get_hex(intersection[3]);           // HEX0
  	*HEX2 =(get_hex(intersection[7]) << 8);  // HEX5 (Display which function is being used)
}

int get_hex(int num) {
    switch(num) {
        case 0: return 0x3F; // Display 0
        case 1: return 0x06; // Display 1
        case 2: return 0x5B; // Display 2
        case 3: return 0x4F; // Display 3
        case 4: return 0x66; // Display 4
        case 5: return 0x6D; // Display 5
        case 6: return 0x7D; // Display 6
        case 7: return 0x07; // Display 7
        case 8: return 0x7F; // Display 8
        case 9: return 0x6F; // Display 9
        case -1: return 0x8; // Display -
        default: return 0x00; // Turn off display for non-digit numbers
    }
}

void maxMinOfQuadratic(int coef[6]){
  double a = coef[2];
  double b = coef[3];
  double c = coef[4];

  // Calculate the vertex of the quadratic function
  double x = -b / (2 * a);
  double y = a * x * x + b * x + c;

  printf("The quadratic curve has a vertex at (%.2f, %.2f).\n", x, y);
}