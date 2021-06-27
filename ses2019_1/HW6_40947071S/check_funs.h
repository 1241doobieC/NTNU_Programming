#ifndef FUNC
#define FUNC
//HW0602
void show_result();
//HW0603
void rotate(double *a, double *b, double theta);
//HW0604
void show_plane(int32_t, int32_t, int32_t, int32_t);
void project(double *x, double *y, double *z, int32_t a, int32_t b, int32_t c, int32_t d);
//HW0605
int32_t check_valid(const uint8_t player[13]);
void print_card(const uint8_t player[13]);
int32_t sort_card(uint8_t player[13], int32_t ( * compare)( int32_t a, int32_t b ));
int32_t func01(int32_t a,int32_t b);
int32_t func02(int32_t a,int32_t b);
int32_t func03(int32_t a,int32_t b);
#endif
