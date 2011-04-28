//
// C/C++ solution to the User Influence problem
//
// Define NUSERS to number of users, and INPUT_FILE for the input file.
//
// The output is a pair of numbers per line; the first number is the influence
// and the second number is the user ID. Pipe the output of this program through
// sort to get the order.
//
//    g++ solution.cc      # (or just "make")
//    ./a.out | sort -n -r # sort biggest to smallest, numerically.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>

// #define NUSERS 4
// #define INPUT_FILE "miniinput.txt"
#define NUSERS 100
#define INPUT_FILE "challenge2input.txt"

// #define VISUAL_DEBUG

int influence(int user, char data[NUSERS][NUSERS], int memo[NUSERS]) {
  // If value is already calculated for this user, use that.
  if (memo[user] >= 0) return memo[user];

  // Calculate influence.
  int sum = 0;
  for (int i = 0; i < NUSERS; i++) {
    if (data[user][i] == 'X') {
      // For each friend, add 1 (for invitation) plus friend's influence score.
      sum += 1 + influence(i, data, memo);
    }
  }

  // Memoize freshly calculated score so we don't need to calculate it again.
  memo[user] = sum;

  return sum;
}

int main(void) {
  // The invitation table. First dimension is a user, second dimension is
  // relationship to the other user (X if user invited other -- see README).
  char data[NUSERS][NUSERS];

  // Read the input file into the data array.
  FILE* f = fopen(INPUT_FILE,"r");
  if (!f) {
    printf("\nERROR: failed to open file\n");
    return 1;
  };

  char buffer[NUSERS];
  for (int i = 0; i < NUSERS; i++) {
    fgets(buffer, 255, f);
    for(int j = 0; j < NUSERS; j++) {
      data[i][j] = buffer[j];
    }
  }

  fclose(f);

#ifdef VISUAL_DEBUG
  // Visual sanity check of the input data file.
  for (int i = 0; i < NUSERS; i++) {
    for (int j = 0; j < NUSERS; j++) {
      printf("%c", data[i][j]);
    }
    printf("\n");
  }
#endif

  // Array to store computed influence scores for each user (initialized to -1
  // because a valid influence score is >= 0).
  int memo[NUSERS];
  for (int i = 0; i < NUSERS; i++) {
    memo[i] = -1;
  }

  // Calculate influence for each user. And print influence results in user ID
  // order, in the format "INFLUENCE USER_ID"
  for (int i = 0; i < NUSERS; i++) {
    printf("%d %d\n", influence(i, data, memo), i);
  }

  return 0;
}
