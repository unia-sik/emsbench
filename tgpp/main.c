/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * $Id: main.c 502 2015-11-05 14:18:19Z klugeflo $
 * @file main.c
 * @brief Main function and parsing of arguments for trace generator
 * preprocessor.
 * @author Florian Kluge <kluge@informatik.uni-augsburg.de>
 */

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cr.h"
#include "kvfile.h"
#include "transformer.h"

/**
 * @name Argument parsing
 * Argument parsing is based on the example from
 * http://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html
 * @{
 */
/** Program version */
const char *argp_program_version = "tgpp 0.1";
/** Contact address */
const char *argp_program_bug_address = "<kluge@informatik.uni-augsburg.de>";

/** Program documentation. */
static char doc[] = "Preprocessor for trace generator";

/** A description of the arguments we accept. */
static char args_doc[] = "CARPARM_FILE CYCLE_FILE";

/** The options we understand. */
static struct argp_option options[] = {
  {
    "output",   'o', "FILE", 0,
    "Output to FILE instead of standard output (if FILE already exist, it will be truncated)"
  },
  { 0 }
};

/** Used by main to communicate with parse_opt. */
struct arguments {
  char *args[2];                /* arg1 & arg2 */
  int silent, verbose;
  char *parameter_file;
  char *cycle_file;
  char *output_file;

};

/** Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state);

/** Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

/**
 * @}
 */


/** File with car parameters */
FILE* carparmFile = NULL;
/** File with driving cycle */
FILE* cycleFile = NULL;
/** Output file */
FILE* outputFile = NULL;


int main (int argc, char **argv) {
  struct arguments arguments;
  //drivecycle_t* cd = NULL;

  cycle_t *cycle = NULL;

  // Default values
  arguments.silent = 0;
  arguments.verbose = 0;
  arguments.output_file = "-";

  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  /*
  printf("PARAMETER_FILE = %s\nCYCLE_FILE = %s\nOUTPUT_FILE = %s\n"
   "VERBOSE = %s\nSILENT = %s\n",
   arguments.args[0], arguments.args[1], arguments.output_file,
   arguments.verbose ? "yes" : "no",
   arguments.silent ? "yes" : "no");
  */

  carparmFile = fopen(arguments.args[0], "r");
  if (carparmFile == NULL) {
    fprintf(stderr, "Opening car parameter file %s failed: %d\n",
            arguments.args[0], errno);
    goto cleanup;
  }

  cycleFile = fopen(arguments.args[1], "r");
  if (cycleFile == NULL) {
    fprintf(stderr, "Opening driving cycle file %s failed: %d\n",
            arguments.args[1], errno);
    goto cleanup;
  }

  if (strcmp(arguments.output_file, "-") == 0) {
    outputFile = stdout;
  }
  else {
    outputFile = fopen(arguments.output_file, "w");
    if (outputFile == NULL) {
      fprintf(stderr, "Opening output file %s failed: %d\n",
              arguments.output_file, errno);
      goto cleanup;
    }
  }

  // if we get here, the parameters are valid so far
  // => go on, read input files

  kv_file_t *kv;
  kv_read_file(&kv, carparmFile);

  cycle = read_cycle(cycleFile);

  transform(kv, cycle, outputFile);

cleanup:
  free_cycle(cycle);
  kv_cleanup(kv);
  if (carparmFile != NULL) {
    fclose(carparmFile);
    carparmFile = NULL;
  }
  if (cycleFile != NULL) {
    fclose(cycleFile);
    cycleFile = NULL;
  }
  if (outputFile != stdout) {
    fclose(outputFile);
    outputFile = NULL;
  }
  exit (0);
}


static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  switch (key) {
  case 'p':
    arguments->parameter_file = arg;
    break;
  case 'c':
    arguments->cycle_file = arg;
    break;
  case 'o':
    arguments->output_file = arg;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= 2)
      // Too many arguments.
    {
      argp_usage (state);
    }
    arguments->args[state->arg_num] = arg;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 2)
      // Not enough arguments.
    {
      argp_usage (state);
    }
    break;


  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
