/*
 * Module: Wikitext
 * File: wikitext_split.c
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#include <Python.h>
#include <string.h>
#include "wikitext_split.h"
#include "iterator.h"

typedef struct _iterator {
  struct _iterator *do_not_modify; /* reserved for use by GenericIterator */
  unsigned char *text;
  unsigned char *current;
  unsigned char *next;
  unsigned char nextchar;
} Iterator;

static PyObject *wikitext_c_init(PyObject *self, PyObject *args);
static PyObject *wikitext_c_next(PyObject *self, PyObject *args);
static void wikitext_c_create(void);
static int tokenize(Iterator *iterator);

static PyMethodDef WikitextMethods[] = {
            {"init", wikitext_c_init, METH_VARARGS,
             "Initialize a wikitext_c iterator"},
            {"next", wikitext_c_next, METH_VARARGS,
             "Get the next value from a wikitext_c iterator"},
            {NULL, NULL, 0, NULL}
};

/* TODO: use per-interpreter state for iterator list */
static struct PyModuleDef WikitextModule = {
  PyModuleDef_HEAD_INIT,
  "Wikitext",     /* module name */
  NULL,           /* no documentation for now */
  -1,             /* size of per-interpreter state. */
  WikitextMethods /* see above */
};

PyMODINIT_FUNC
PyInit_Wikitext(void)
{
  PyObject *module;

  module = PyModule_Create(&WikitextModule);
  if (module == NULL) {
    return NULL;
  }

  wikitext_c_create(); /* initialize read-only data structures */

  return module;
}

static void
wikitext_c_create(void)
{
  tokenfuns_init();
  tokentypes_init();
}

static PyObject *
wikitext_c_init(PyObject *self, PyObject *args)
{
  const char *text;
  size_t textlen;
  Iterator *iterator;

  if (!PyArg_ParseTuple(args, "s", &text))
    return NULL;

  iterator = (Iterator *)iterator_alloc(sizeof(Iterator));

  /* create a copy of the text */
  textlen = strlen(text);
  iterator->text = (unsigned char *)malloc(textlen + 1);
  iterator->current = iterator->text;
  memcpy(iterator->text, text, textlen + 1);

  /* set up initial conditions */
  iterator->next = iterator->text;
  iterator->nextchar = *(iterator->next);

  /* The original version of this code used PyLong_FromVoidPtr,
   * but the iterator pointer was not properly reconstituted
   * by PyArg_ParseTuple.  Using a signed long should work on
   * most architectures, since the value is opaque to Python code.
   */
  return Py_BuildValue("l", iterator);
}

static void
wikitext_c_free(Iterator *iterator)
{
  free(iterator->text);
  iterator_free((GenericIterator *)iterator);
}

static PyObject *
wikitext_c_next(PyObject *self, PyObject *args)
{
  Iterator *iterator;
  unsigned int type;

  if (!PyArg_ParseTuple(args, "l", &iterator))
    return NULL;

  if (!iterator_is_valid((GenericIterator *)iterator)) {
    return Py_BuildValue("is", -1, NULL);
  }

  if (iterator->nextchar == '\0') {
    wikitext_c_free(iterator);
    return Py_BuildValue("is", -1, NULL);
  }

  type = tokenize(iterator);

  /* TODO: check the assumption that Py_BuildValue creates
     a copy of the string.  Otherwise, the string may no
     longer be valid when the null is removed from end of the
     string on the next iteration. */
  return Py_BuildValue("is", type, iterator->current);
}

static int
tokenize(Iterator *iterator)
{
  int type;

  /* replace the terminator of the last token with the
     beginning of the next token */
  *(iterator->next) = iterator->nextchar;

  /* move the current pointer to this token */
  iterator->current = iterator->next;

  /* Each token function in the tokenfuns array processes
     the token and moves the next pointer to one character
     after the end of the token. */
  type = tokenfuns[iterator->nextchar](&(iterator->next));

  /* remember the beginning of the next token */
  iterator->nextchar = *(iterator->next);

  /* null-terminate the current token */
  *(iterator->next) = '\0';

  return type;
}
