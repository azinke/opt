/**
 * @file test.c
 * @author AMOUSSOU Zinsou Kenneth (www.gitlab.com/azinke)
 * @brief Testing the CLI option parsing library
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include "opt.h"

#define VERSION   "0.01"

void print_version() {
  printf("test v" VERSION "\n");
}


int main (int argc, char* argv[]) {
  parser_t parser = init_parser("test", "Test program for command line argument parser");
  char vdefault = 0;
  option_t version = {
    .args = "-v",
    .argl = "--version",
    .help = "Print out the version of the program",
    .type = OPT_BOOL,
    .default_value = &vdefault,
    .callback = print_version,
  };
  add_arg(&parser, &version);

  option_t name = {
    .argl = "--name",
    .help = "Print the name of the user",
    .type = OPT_STR,
    .default_value=NULL,
  };
  add_arg(&parser, &name);

  float def_gpa = 5.0;
  option_t grade = {
    .argl = "--gpa",
    .help = "The global grade of the user",
    .type = OPT_FLOAT,
    .default_value = &def_gpa,
  };
  add_arg(&parser, &grade);

  parse(&parser, argc, argv);

  char v = *(char*)get_option(&parser, "-v");
  char *vname = (char*) get_option(&parser, "--name");
  float *gpa = (float*) get_option(&parser, "--gpa");
  if (vname != NULL) {
    printf("ok!\n");
    printf("Name: %s\n\n", vname);
  }
  if (gpa != NULL) {
    printf("GPA: %.8f\n", *gpa);
  }


  print_help(&parser);
  free_parser(&parser);
  return 0;
}
