#ifndef __TIME_EXP_H__
#define __TIME_EXP_H__


double randfrom(double min, double max);
int generate_rand_matrix(char *file_name, int row, int col, int percentage);
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);

#endif // __TIME_EXP_H__
