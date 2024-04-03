#include "global.h"

void linear_linear_intersection(int coef[6]);
void linear_quadratic_intersection(int coef[6]);

void linear_linear_intersection(int coef[6]) {  // tested and working
  int m1 = coef[0];
  int c1 = coef[1];
  int m2 = coef[2];
  int c2 = coef[3];

  // Calculate the intersection point
  int denominator = m1 - m2;

  if (denominator == 0) {
    printf("The lines are parallel and do not intersect.\n");
    return;
  }

  double x = (double)(c2 - c1) / denominator;
  double y = m1 * x + c1;

  // Store the intersection point in the array
  intersectionArray[0] = x;
  intersectionArray[1] = y;

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
  }
}