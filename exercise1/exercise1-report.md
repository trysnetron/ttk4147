% TTK4147 Exercise 1
% Nikolai ... and Trym Sneltvedt
% 16. September 2019

# Task A

|        | sleep() | busy_wait() with get_clocktime() | busy_wait() with times() |
| ------ | ------- | -------------------------------- | ------------------------ |
| real   |  1.003s |                           1.003s |                   1.023s |
| user   |  0.002s |                           0.999s |                   1.001s |
| system |  0.001s |                           0.000s |                   0.020s |


# Task B

| function          | average clock cycles |
| ----------------- | -------------------- |
| `__rdtsc()`       | 22.9                 |
| `clock_gettime()` | 60.1                 |
| `times()`         | 692.2                |




# Task C




# Task D

Memory is RAM
Swap is virtual RAM on the harddrive (very slow)

When `x_dim` is 1000 or 10000, the process finishes almost instantly.

When we use `memset` to write to memory, the process takes a lot of time again. Longer time than when we had `x_dim = 100` actually.

When `x_dim` is 100, we allocate a huge block of memory (`y_dim` = 10^9 / 100 = 10^7, we allocate 80MB in one swoop) while when `x_dim` is larger we allocate smaller blocks of memory.

# Task E

We can add stuff to the array even though it is more than the capacity, but when we add -g -fsanitize=address we get an error when running the program. It warns us of a heap-buffer-overflow (the array is in the heap since we allocate it with `malloc`)