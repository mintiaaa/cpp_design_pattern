#include "brake.h"

int main()
{
    const int offset = 3;
    NormalBrake normal_brake(offset);
    BrakeWithABS abs_brake(offset);
    Car normal_car(&normal_brake);
    Car abs_car(&abs_brake);

    normal_car.applyBrake();
    abs_car.applyBrake();

    return 0;
}
