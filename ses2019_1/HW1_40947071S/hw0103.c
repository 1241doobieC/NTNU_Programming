#include <stdio.h>
#include <stdint.h>

int main(){

  float gravity;
  float time;
  float velocity;
  float altitude;
  printf("Please enter the acceleration due to gravity: ");
  scanf("%f", &gravity );
  printf("Please enter the time(s): ");
  scanf("%f", &time );

  if (gravity < 0 || time <= 0) {
    printf("Wrong input for gravity or time. \n");
    return 0;
  }
  velocity = gravity * time;
  printf("Final Velocity: %.2f \n", velocity);

  //0.5 * gravity * time * time
  altitude = 0.5 * gravity * time * time;
  printf("The altitude: %.2f \n", altitude );
  return 0;
}
