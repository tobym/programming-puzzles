#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define KSIZE 6
static int KARMAS[KSIZE] = {2, 3, 17, 23, 42, 98};
int *memo = NULL;

// Returns the minimum from an int array a of size n.
int min(int *a, int n) {
  if (NULL == a) return NULL;
  int m = a[0];
  for (int i = 0; i < n; i++) {
    if (a[i] < m) m = a[i];
  }
  return m;
}

//
// Returns the minimum number of tasks required to get to the given point total.
//
int numTasks(int points) {
  // Valid point value is 0, or anything >= 2.
  if (!(points == 0 || points >= 2)) {
    fprintf(stderr, "invalid point value %d: ", points);
    assert(points == 0 || points >= 2);
  }

  // Return pre-calculated value if we have it.
  if (memo[points] > -1) return memo[points];

  // Set the base cases, where points corresponds exactly to one task.
  switch(points) {
    case 0: memo[points] = 0;
            return 0;
    case 2:
    case 3:
    case 17:
    case 23:
    case 42:
    case 98: memo[points] = 1;
             return 1;
  }

  // Set up array for values of each "i - 1" subproblem.
  // Alternatively, use std::vector<int> and never add invalid intermediates.
  int intermediate[KSIZE];
  for (int i = 0; i < KSIZE; i++) {
    int diff = points - KARMAS[i];
    if (diff == 1 || diff < 0) {
      // If subproblem is invalid, save a high value so it won't be the min.
      intermediate[i] = INT_MAX;
    } else {
      // Otherwise, the value is 1 (for this task) plus the remaining tasks.
      intermediate[i] = 1 + numTasks(diff);
    }
  }

  // Find the smallest result, memoize it, and return it.
  int num = min(intermediate, KSIZE);
  memo[points] = num;
  return num;
}

int main(void) {
  int points[4] = { 2349, 2102, 2001, 1747 };
  int max = 2349;

  // Initialize global memoization array to -1.
  memo = (int*)malloc((max + 1) * sizeof(int));
  if (!memo) return 1;
  for (int i = 0; i <= max; i++) {
    memo[i] = -1;
  }

  int ans;
  for (int i = 0; i < 4; i++) {
    int karma = points[i];
    int num = numTasks(karma);
    printf("Minimum number of tasks for %d points: %d\n", karma, num);

    // Multiply all answers together for total answer.
    if (i == 0) {
      ans = num;
    } else {
      ans = ans * num;
    }
  }

  printf("\nChallenge answer is: %d\n", ans);

  return 0;
}
