/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Sep 13, 2020!!
Description: Compute the number of times the beam is reflected of an internal surface of the white cell before exiting. Init and exit ponits resolution are selected based on my discussion with the TA.
General idea is that the beam starts its traveling from a point outside the white cell: `(0.0,10.1)` and hit the mirror at (1.4,-9.6). Then, it is reflected with with 
the angel equal to comming beam following law of reflection. More details that I followed are here: https://www.fabrizioduroni.it/2017/08/25/how-to-calculate-reflection-vector.html & http://paulbourke.net/geometry/reflected/

So, we have source, destination(incident point) and line equation. Follwing the rules we need to compute the new source, destination and line equation for each new reflection.
The laser goes out when -0.01<=x<=0.0.1 and y >= 9.9. The accuracy of the y can be changed and accordingly the fine value is changed.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std; 
  


class Beam{
public:
    Beam(double _x, double _y){x = _x;y = _y;}
    double getX(){return x;} 
    double getY(){return y;}
    void setX(double _x){ x = _x;} 
    void setY(double _y){ y = _y;}

    double getLength(){return sqrt(x*x + y*y);}
    double dotoperation(Beam& ray){return x * ray.x + y * ray.y;}

private:
    double x;
    double y;
};





int main(){
    Beam laser(0.0, 10.1); // Coming beam. The name of this object of type beam is laser. Init and exit ponits resolution are selected based on my discussion with the TA.
    unsigned int counter = 0; //counting number of reflections

    // initialize source and destination of the incoming ray. Accuray can be changed!
    Beam source (0.0, 10.1);
    Beam destination (1.4, -9.6);

    while (true){ 
        if( destination.getX()>= -0.01 && destination.getX()<= 0.01 && destination.getY() >= 9.9){ //when the laser goes out! Due to the curve equation y cannot be 10; however we can increase the accuracy by increasing number of digits 9.99999.....!
            break;
        }
   
     
        // finding normal line at at incident of laser beam:Details https://www.fabrizioduroni.it/2017/08/25/how-to-calculate-reflection-vector.html & http://paulbourke.net/geometry/reflected/
        Beam normalLine(-4 * destination.getX(), -destination.getY());
        // normalize Beam length
        double length = normalLine.getLength();
        normalLine.setX(normalLine.getX()/length);
        normalLine.setY(normalLine.getY()/length);;

        // current cordinate of the ray
        Beam cordinate(destination.getX() - source.getX(), destination.getY() - source.getY());
  
        // reflect ray at intersection considering the normal line
        // finding reflection beam at at incident of laser neam :Details https://www.fabrizioduroni.it/2017/08/25/how-to-calculate-reflection-vector.html & http://paulbourke.net/geometry/reflected/
        Beam reflection(0, 0);
        reflection.setX( cordinate.getX() - 2 * cordinate.dotoperation(normalLine) * normalLine.getX());
        reflection.setY( cordinate.getY() - 2 * cordinate.dotoperation(normalLine) * normalLine.getY());

        //slope of a line is y/x.
        double slope = reflection.getY() / reflection.getX();

        // destinaion point of old laser is becoming source point of a new one.
        source.setX(destination.getX());
        source.setY(destination.getY());

        // To find the corrdinates of next intersection, I used the famous linear line equation " y-y1=m(x-x1)" and replace the defined source and destion points in it. X and Y can be obtaned from eliptic curve equation. 
        destination.setX(( (- (slope * slope) * source.getX()) + 4 * source.getX() + 2 * slope * source.getY()) / ( - (slope * slope) -4 ));
        destination.setY( slope * (destination.getX() - source.getX()) + source.getY());

    counter++;

  }

    //write the results in  file
    //cout<< counter <<endl;
    ofstream myfile;
    myfile.open ("output4.txt");
    myfile << counter;
    myfile.close(); 
    return 0;
}





    
  
    
