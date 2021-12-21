/* Test a command line program with input file and arguments.
 * Copyright Nick "nupa" Lamicela, 2021.
 * 
 * 'test' takes a test file over stdin, Each line in the input should
 * be blank, or start with one of the symbols -, $, <, >, or #, each
 * corresponding to part of a test.
 * - indicates the title of a new test.
 * $ indicates something that should be typed on the command line.
 * > indicates something that should be passed over stdin.
 * < indicates something that should be expected in stdout.
 * # indicates a comment.
 * 
 * So, for instance:
 * 
 * - it should reverse a single line
 * $ reverse
 * > abcdefg
 * < gfedcba
 * 
 * - it should reverse multiple lines
 * $ reverse
 * > the quick brown fox jumps
 * > over the lazy dog
 * < god yzal eht revo
 * < spmuj xof nworb kciuq eht
 */
