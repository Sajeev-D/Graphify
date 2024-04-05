#include "global.h"

int coefFunc1[4];
int coefFunc2[4]; 
double intersectionArr[10]; // Stores all intersection points
double lf(double m, double c, double x); // y = mx + c
double qf(double a, double b, double c, double x); // y = ax^2 + bx + c
double cf(double a, double b, double c, double d, double x); // y = ax^3 + bx^2 + cx + d
void findIntersection(int func1[4], int func2[4]);

void findIntersection(int func1[4], int func2[4]){
    // Both functions are linear
    if(func1[2] == 0 && func1[3] == 0 && func2[2] == 0 && func2[3] == 0){
        double m1 = (double)func1[0];
        double c1 = (double)func1[1];
        double m2 = (double)func2[0];
        double c2 = (double)func2[1];
        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = lf(m1, c1, i-1) > lf(m2, c2, i-1);
                    bool polarity = lf(m1, c1, i) > lf(m2, c2, i);
                    if(oldPolarity != polarity && lf(m1, c1, i) != lf(m2, c2, i)  && lf(m1, c1, i) < 240 && lf(m2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (lf(m1, c1, i) + lf(m2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(lf(m1, c1, i) == lf(m2, c2, i) && lf(m1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = lf(m1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with linear-linear intersection
    
     else if(func1[2] == 0 && func1[3] == 0 && func2[2] != 0 && func2[3] != 0){
        // Function 1 is linear and function 2 is quadratic
        double m1 = (double)func1[0];
        double c1 = (double)func1[1];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = lf(m1, c1, i-1) > qf(a2, b2, c2, i-1);
                    bool polarity = lf(m1, c1, i) > qf(a2, b2, c2, i);
                    if(oldPolarity != polarity && lf(m1, c1, i) != qf(a2, b2, c2, i) && lf(m1, c1, i) < 240 && qf(a2, b2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (lf(m1, c1, i) + qf(a2, b2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(lf(m1, c1, i) == qf(a2, b2, c2, i) && lf(m1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = lf(m1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with linear-quadratic intersection
    
     else if(func1[2] != 0 && func1[3] != 0 && func2[2] == 0 && func2[3] == 0){
        // Function 1 is quadratic and function 2 is linear
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double m2 = (double)func2[0];
        double c2 = (double)func2[1];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = qf(a1, b1, c1, i-1) > lf(m2, c2, i-1);
                    bool polarity = qf(a1, b1, c1, i) > lf(m2, c2, i);
                    if(oldPolarity != polarity && qf(a1, b1, c1, i) != lf(m2, c2, i) && qf(a1, b1, c1, i) < 240 && lf(m2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (qf(a1, b1, c1, i) + lf(m2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(qf(a1, b1, c1, i) == lf(m2, c2, i) && qf(a1, b1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = qf(a1, b1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with quadratic-linear intersection

    else if(func1[2] != 0 && func1[3] != 0 && func2[2] != 0 && func2[3] != 0){
        // Both functions are quadratic
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = qf(a1, b1, c1, i-1) > qf(a2, b2, c2, i-1);
                    bool polarity = qf(a1, b1, c1, i) > qf(a2, b2, c2, i);
                    if(oldPolarity != polarity && qf(a1, b1, c1, i) != qf(a2, b2, c2, i) && qf(a1, b1, c1, i) < 240 && qf(a2, b2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (qf(a1, b1, c1, i) + qf(a2, b2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(qf(a1, b1, c1, i) == qf(a2, b2, c2, i) && qf(a1, b1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = qf(a1, b1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with quadratic-quadratic intersection
    
    else if (func1[3] == 0 && func1[2] == 0 && func2[3] != 0){
        // Funtion 1 is linear and function 2 is cubic
        double m1 = (double)func1[0];
        double c1 = (double)func1[1];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];
        double d2 = (double)func2[3];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = lf(m1, c1, i-1) > cf(a2, b2, c2, d2, i-1);
                    bool polarity = lf(m1, c1, i) > cf(a2, b2, c2, d2, i);
                    if(oldPolarity != polarity && lf(m1, c1, i) != cf(a2, b2, c2, d2, i) && lf(m1, c1, i) < 240 && cf(a2, b2, c2, d2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (lf(m1, c1, i) + cf(a2, b2, c2, d2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(lf(m1, c1, i) == cf(a2, b2, c2, d2, i) && lf(m1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = lf(m1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with linear-cubic intersection
    
     else if(func1[3] != 0 && func2[3] == 0 && func2[2] == 0){
        // Function 1 is cubic and function 2 is linear
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double d1 = (double)func1[3];
        double m2 = (double)func2[0];
        double c2 = (double)func2[1];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = cf(a1, b1, c1, d1, i-1) > lf(m2, c2, i-1);
                    bool polarity = cf(a1, b1, c1, d1, i) > lf(m2, c2, i);
                    if(oldPolarity != polarity && cf(a1, b1, c1, d1, i) != lf(m2, c2, i) && cf(a1, b1, c1, d1, i) < 240 && lf(m2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (cf(a1, b1, c1, d1, i) + lf(m2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(cf(a1, b1, c1, d1, i) == lf(m2, c2, i) && cf(a1, b1, c1, d1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = cf(a1, b1, c1, d1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with cubic-linear intersection
    
    else if(func1[3] != 0 && func2[3] == 0 && func2[2] != 0){
        // Function 1 is cubic and function 2 is quadratic
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double d1 = (double)func1[3];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = cf(a1, b1, c1, d1, i-1) > qf(a2, b2, c2, i-1);
                    bool polarity = cf(a1, b1, c1, d1, i) > qf(a2, b2, c2, i);
                    if(oldPolarity != polarity && cf(a1, b1, c1, d1, i) != qf(a2, b2, c2, i) && cf(a1, b1, c1, d1, i) < 240 && qf(a2, b2, c2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (cf(a1, b1, c1, d1, i) + qf(a2, b2, c2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(cf(a1, b1, c1, d1, i) == qf(a2, b2, c2, i) && cf(a1, b1, c1, d1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = cf(a1, b1, c1, d1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with cubic-quadratic intersection
    
     else if(func1[3] == 0 && func1[2] != 0 && func2[3] != 0){
        // Function 1 is quadratic and function 2 is cubic
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];
        double d2 = (double)func2[3];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = qf(a1, b1, c1, i-1) > cf(a2, b2, c2, d2, i-1);
                    bool polarity = qf(a1, b1, c1, i) > cf(a2, b2, c2, d2, i);
                    if(oldPolarity != polarity && qf(a1, b1, c1, i) != cf(a2, b2, c2, d2, i) && qf(a1, b1, c1, i) < 240 && cf(a2, b2, c2, d2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (qf(a1, b1, c1, i) + cf(a2, b2, c2, d2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(qf(a1, b1, c1, i) == cf(a2, b2, c2, d2, i) && qf(a1, b1, c1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = qf(a1, b1, c1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    } // Done with quadratic-cubic intersection 
    
    else if(func1[3] != 0 && func2[3] != 0){
        // Both functions are cubic
        double a1 = (double)func1[0];
        double b1 = (double)func1[1];
        double c1 = (double)func1[2];
        double d1 = (double)func1[3];
        double a2 = (double)func2[0];
        double b2 = (double)func2[1];
        double c2 = (double)func2[2];
        double d2 = (double)func2[3];

        int interIndex = 0;
        for(int i = 0; i < 320; i++){
            if(interIndex < 10){ // Only store 5 intersection points
                if(i>0){
                    bool oldPolarity = cf(a1, b1, c1, d1, i-1) > cf(a2, b2, c2, d2, i-1);
                    bool polarity = cf(a1, b1, c1, d1, i) > cf(a2, b2, c2, d2, i);
                    if(oldPolarity != polarity && cf(a1, b1, c1, d1, i) != cf(a2, b2, c2, d2, i) && cf(a1, b1, c1, d1, i) < 240 && cf(a2, b2, c2, d2, i) < 240){
                        // Intersection has happened but not at whole number
                        intersectionArr[interIndex] = i;
                        intersectionArr[interIndex + 1] = (cf(a1, b1, c1, d1, i) + cf(a2, b2, c2, d2, i))/2.0; // Average of the two y values
                        interIndex = interIndex + 2;
                        continue;
                    }
                }
                if(cf(a1, b1, c1, d1, i) == cf(a2, b2, c2, d2, i) && cf(a1, b1, c1, d1, i) < 240){
                    intersectionArr[interIndex] = i;
                    intersectionArr[interIndex+1] = cf(a1, b1, c1, d1, i);
                    interIndex = interIndex + 2;
                }
            }
        }
    }
}

double lf(double m, double c, double x){
    return m * x + c;
}

double qf(double a, double b, double c, double x){
    return a * x * x + b * x + c;
}

double cf(double a, double b, double c, double d, double x){
    return a * x * x * x + b * x * x + c * x + d;
}



