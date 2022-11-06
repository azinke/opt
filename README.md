# Opt

Simple CLI option parsing library

## Data structures

```c
/**
 * @brief CLI root parser
 * 
 */
typedef struct cli_parser {
  /**
   * @brief Name of the CLI parser
   *
   * Can also be considered as the name of the program
   */
  char *name;

  /**
   * @brief Description of the program and what it's meant to do
   * 
   */
  char *description;

  /**
   * @brief Version of the program
   */
  char *version;
} parser_t

```

```c
/**
 * @brief Definition of the components of a command line argument
 * 
 */
typedef struct cli_option {
  /**
   * @brief Short CLI argument
   *
   * The expected format: -b
   * Normaly a single dash followed by one letter. But a couple more
   * letters are supported
   */
  const char *args;

  /**
   * @brief Long CLI argument
   *
   * The expected is format: --argname
   * The argument can be provided including the double dashes at
   * the beginning
   */
  const char *argl;

  /**
   * @brief Type of the CLI argument.
   *
   * Will help in parsing the argument
   */
  cli_option_type_t type;

  /**
   * @brief Action to do upon the reception of the argument
   *
   * Useful for boolean flags or initiate a callback function
   */
  cli_option_action_t action;

  /**
   * @brief Callbacl function to call when the argument is received
   * 
   */
  void (*callback)(void);

  /**
   * @brief Help message
   *
   * Reasonable length message describing the meaning of the CLI option
   */
  const char *help;

  /**
   * @brief Default value of the option
   *
   * The void pointer would be casted acording to the type of the argument
   */
  void *default_value;

  /**
   * @brief Value of the parameter after parsing
   *
   * Memory will be dynamically allocated to store the value
   */
  unsigned char *value;

} option_t;
```

```c
/**
 * @brief Type definition for parsing the CLI options
 * 
 */
typedef enum cli_option_type {
  OPT_UNKNOWN,
  OPT_BOOL,
  OPT_SHORT,
  OPT_INT,
  OPT_FLOAT,
  OPT_STR
} cli_option_type_t;
```

## API

```c
/** Create the parser */
parser_t init_parser(const char *name, const char *description);

/** Add new CLI option to the parser */
int add_arg(parser_t *parser, option_t *option);

/** Read the value of a CLI argument */
void* get_option(parser_t *parser, char *cli_arg);

/** print help */
void print_help(parser_t* parser);

/** Free all the memory dynamically allocated*/
void free_parser(parser_t *parser);
```


## Example

```c
#include <stdio.h>
#include "opt.h"

int main (int argc, char* argv[]) {
    parser_t parser = init_parser("example", "Example use of Opt library");
    // Definition of the default value of the `version` option
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

    option_t name = {
        .args = "-fn",
        .argl = "--first-name",
        .help = "First name of the user",
        .type = OPT_STR,
    };
    add_arg(&parser, &name);

    int age_default = 10;
    option_t age = {
        .args = "-age",
        .argl = "--age",
        .help = "Age of the user",
        .type = OPT_INT,
        .default_value = &age_default,
    };
    add_arg(&parser, &name);

    // Parse the CLI options
    parse(&parser, argc, argv);

    // char* vname = (char*) get_option(&parser, "-n");
    // or
    char* vname = (char*) get_option(&parser, "--name");

    int* vage = (int*) get_option(&parser, "--age");

    if (vname != NULL) printf("Name: %s\n", vname);
    else printf("CLI option '%s' not provided", name.argl);

    if (vage != NULL) printf("Age: %d\n", *vage);

    // Free parser and dynamically allocated memory
    free_parser(&parser);
    return 0;
}
```

See the `test` folder for more examples.
