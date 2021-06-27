#include "all.h"
#define weather(b) weather_##b
#define printWeather(a) printf(#a ":%s \n", a)
int32_t main(int32_t argc, char* argv)
{
    char weather_Monday[20] = "Sunny";
    char weather_Tuesday[20] = "Windy";
    char weather_Wednesday[20] = "Cloudy";
    char weather_Thursday[20] = "Rainy";
    char weather_Friday[20] = "snowy";
    printWeather(weather(Monday));
    printWeather(weather(Tuesday));
    printWeather(weather(Wednesday));
    printWeather(weather(Thursday));
    printWeather(weather(Friday));
    
    return 0;
}