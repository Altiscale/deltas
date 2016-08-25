/*
 * Module: Wikitext
 * File: wikitext_split.h
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
typedef unsigned int (*TokenFun)(unsigned char **next);

extern TokenFun tokenfuns[];
extern void tokenfuns_init(void);

extern unsigned int tokentypes[];
extern void tokentypes_init(void);
