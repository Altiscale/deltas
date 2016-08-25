/*
 * Module: Wikitext
 * File: iterator.c
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#include <Python.h>
#include "iterator.h"

/* This file implements the GenericIterator, so refer to the
   GenericIterator as an Iterator for convenience. */
typedef GenericIterator Iterator;

/* TODO: Verify thread safety by making sure that these two
   variables are local to each thread.
 */
static Iterator *iterators = NULL;
static Iterator *mri = NULL; /* most recent iterator */

Iterator *
iterator_alloc(size_t size)
{
  Iterator *iterator;

  iterator = (Iterator *)malloc(size);

  /* push onto head of iterators list */
  iterator->chain = iterators;
  iterators = iterator;

  mri = iterator; /* set most recent iterator */
  return iterator;
}

void
iterator_free(Iterator *iterator)
{
  Iterator **splice;

  /* remove most recent iterator, if appropriate */
  if (mri == iterator)
    mri = NULL;

  for (splice = &iterators; *splice; splice = &((*splice)->chain)) {
    if (*splice == iterator) { /* splice the iterator out of the chain */
      *splice = (*splice)->chain;

      /* free the storage only if the iterator is still managed */
      free((void *)iterator);

      return; /* that's all folks */
    }
  }
}

unsigned int
iterator_is_valid(Iterator *iterator)
{
  Iterator *valid;

  if (mri == iterator) { /* common case: there is just one iterator */
    return 1;
  }

  for (valid = iterators; valid; valid = valid->chain) {
    if (valid == iterator) {
      mri = iterator;
      return 1;
    }
  }

  return 0;
}
