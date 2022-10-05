/*=========================
         PlatySim2
  Written by Jordan Doose
       Happy flying!
=========================*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "core/Vector3.hpp"
#include "core/Quaternion.hpp"

int main()
{
    Vector3 test = Vector3::unitX();

    std::cout << std::setprecision(3);
    std::cout << std::fixed;

    for(int i = 0; i <= 9; i++)
    {
        double angle = (double)(i * 10) * (M_PI / 180.);

        std::cout << Quaternion::fromAxisAngle(Vector3(0, 1, 0), angle).rotate(test) << std::endl;
    }
}