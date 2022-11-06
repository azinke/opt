/**
 * @file test_commands.c
 * @author AMOUSSOU Zinsou Kenneth (www.gitlab.com/azinke)
 * @brief Test CLI commands
 * @version 0.0.1
 * @date 2022-11-05
 *
 * @copyright Copyright (c) 2022
 */

# include <stdio.h>
#include "../opt.h"

#define VERSION   "0.0.1"

void print_version() {
  printf("test commands v" VERSION "\n");
}

int main (int argc, char* argv[]) {
  parser_t parser = init_parser("test_commands", "CLI parser test with CRUD commands");
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

  option_t help = {
    .args = "-h",
    .argl = "--help",
    .help = "Print this help message.",
    .type = OPT_BOOL,
  };
  add_arg(&parser, &help);

  option_t id = {
    .args = "-id",
    .help = "Item idenfification number",
    .type = OPT_STR,
  };
  add_arg(&parser, &id);

  option_t user = {
    .args = "user",
    .help = "Refer to a user. Can be combined with CRUD commands",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &user);

  option_t username = {
    .args = "-u",
    .argl = "--username",
    .help = "Screen name of the user",
    .type = OPT_STR,
  };
  add_arg(&parser, &username);

  option_t password = {
    .args = "-p",
    .argl = "--password",
    .help = "Password or secret token to access resources",
    .type = OPT_STR,
  };
  add_arg(&parser, &password);

  option_t group = {
    .args = "group",
    .help = "Refer to a group. Can be combined with CRUD commands",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &group);
  option_t name = {
    .args = "-n",
    .argl = "--name",
    .help = "Screen name of the group",
    .type = OPT_STR,
  };
  add_arg(&parser, &name);

  option_t create = {
    .args = "create",
    .help = "Create an new item",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &create);

  option_t read = {
    .args = "read",
    .help = "Read an item",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &read);

  option_t update = {
    .args = "update",
    .help = "Update an item",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &update);

  option_t delete = {
    .args = "delete",
    .help = "Delete an item",
    .type = OPT_BOOL,
    .default_value = &vdefault,
  };
  add_arg(&parser, &delete);

  parse(&parser, argc, argv);

  char* vhelp = (char*)get_option(&parser, "-h");

  if (*vhelp) print_help(&parser);

  free_parser(&parser);
}
