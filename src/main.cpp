/*=========================
         PlatySim2
  Written by Jordan Doose
       Happy flying!
=========================*/

#include <iostream>
#include <cmath>
#include "core/Vector3.hpp"
#include "core/Quaternion.hpp"

int main()
{
    Vector3 test = Vector3::unitX();

    std::cout << Quaternion::fromEuler(0., 90. * (M_PI / 180.), 0.).rotate(test) << std::endl;
}