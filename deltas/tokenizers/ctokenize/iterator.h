/*
 * Module: Wikitext
 * File: iterator.h
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
typedef struct _generic_iterator {
  struct _generic_iterator *chain;
  /* extra storage goes here */
} GenericIterator;

GenericIterator *iterator_alloc(size_t size);
void iterator_free(GenericIterator *iterator);
unsigned int iterator_is_valid(GenericIterator *iterator);
