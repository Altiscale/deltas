/*
 * Module: Wikitext
 * File: wikitext_split_tokenfuns.c
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#include "wikitext_split.h"
#include "wikitext_split_types.h"
#include "wikitext_split_tokenfuns.h"

unsigned int tf_etc(unsigned char **next)
{
  /* trival token: just move the next pointer by one */
  (*next)++;

  return TOKEN_ETC;
}

unsigned int tf_bar(unsigned char **next)
{

  if (*(*next + 1) != '}') /* check for tab_close */
    return tf_one_or_more(next);

  (*next) += 2; /* 2 character token */

  return TOKEN_TAB_CLOSE;
}

unsigned int tf_one_or_more(unsigned char **next)
{
  unsigned char *cursor = *next;
  unsigned char first = *cursor; /* the first character in the set */

  /* preincrement: always have at least one instance of the literal */
  while (*(++cursor) == first);

  *next = cursor; /* update the pointer to the end of the token */
  return tokentypes[first];
}
