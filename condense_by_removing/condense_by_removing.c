#include <stdio.h>

/*
 * See http://news.ycombinator.com/item?id=1383169
 *
 *    cc condense_by_removing.c
 *    ./a.out   # should pass
 */

/*
  Write a C routine with the
  following prototype:
*/

void condense_by_removing(
  char *z_terminated ,
  char char_to_remove
);

/*
    Your routine should modify
    the given zero-terminated
    string in place, removing
    all instances of the given
    char.
*/

void condense_by_removing( char *z_terminated , char char_to_remove )
{
  char terminal_character = '\0';
  int reader = 0;
  int writer = 0;

  for ( ; z_terminated[reader] != terminal_character; reader++)
  {
    if ( z_terminated[reader] != char_to_remove )
    {
      z_terminated[writer++] = z_terminated[reader];
    }
  }

  z_terminated[writer] = terminal_character;
}


int main()
{
  char easy[] = "foo bar baz";
  const char *easy_a = "foo br bz";
  const char *easy_X = "foo bar baz";

  char front[] = "blah";
  const char *front_b = "lah";

  char back[] = "testing";
  const char *back_g = "testin";

  char small[] = "a";
  const char *small_a = "";

  printf("before  : '%s'  (remove 'X')\n", easy);
  condense_by_removing(easy, 'X');
  printf("after   : '%s'\n", easy);
  printf("expected: '%s'\n", easy_X);
  int test_no_change = (*easy == *easy_X);
  printf("===> %s\n\n", test_no_change ? "PASS" : "FAIL" );

  printf("before  : '%s'  (remove 'a')\n", easy);
  condense_by_removing(easy, 'a');
  printf("after   : '%s'\n", easy);
  printf("expected: '%s'\n", easy_a);
  int test_remove_char = (*easy == *easy_a);
  printf("===> %s\n\n", test_remove_char ? "PASS" : "FAIL" );

  printf("before  : '%s'  (remove 'b')\n", front);
  condense_by_removing(front, 'b');
  printf("after   : '%s'\n", front);
  printf("expected: '%s'\n", front_b);
  int test_remove_front_char = (*front == *front_b);
  printf("===> %s\n\n", test_remove_front_char ? "PASS" : "FAIL" );

  printf("before  : '%s'  (remove 'g')\n", back);
  condense_by_removing(back, 'g');
  printf("after   : '%s'\n", back);
  printf("expected: '%s'\n", back_g);
  int test_remove_back_char = (*back == *back_g);
  printf("===> %s\n\n", test_remove_back_char ? "PASS" : "FAIL" );

  printf("before  : '%s'  (remove 'a')\n", small);
  condense_by_removing(small, 'a');
  printf("after   : '%s'\n", small);
  printf("expected: '%s'\n", small_a);
  int test_single_char = (*small == *small_a);
  printf("===> %s\n", test_single_char ? "PASS" : "FAIL" );

  return (test_no_change && test_remove_char && test_remove_front_char && test_remove_back_char && test_single_char) ? 0 : 1;
}
