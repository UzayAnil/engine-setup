#include <math.h>

float lerp(float a, float b, float t) 
{
    return a + (b - a) * t;
}

float lerp_dt(float current, float target, float decay_rate, float dt) 
{
    float adjusted_t = 1.0f - expf(-decay_rate * dt);
    return lerp(current, target, adjusted_t);
}