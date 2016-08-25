/*
 * Module: Wikitext
 * File: wikitext_split_create.c
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#include "wikitext_split.h"
#include "wikitext_split_types.h"
#include "wikitext_split_tokenfuns.h"

TokenFun tokenfuns[256]; /* array of token functions */
unsigned int tokentypes[256]; /* array of token types */

void tokenfuns_init()
{
        int idx;

        /* default is ETC */
        for (idx = 0; idx < 256; idx++)
                tokenfuns[idx] = tf_etc;

        tokenfuns['.'] = tf_one_or_more;
        tokenfuns['?'] = tf_one_or_more;
        tokenfuns['!'] = tf_one_or_more;
        tokenfuns[','] = tf_one_or_more;
        tokenfuns[':'] = tf_one_or_more;
        tokenfuns[';'] = tf_one_or_more;
        tokenfuns['='] = tf_one_or_more;
        tokenfuns['|'] = tf_bar;
}

void tokentypes_init()
{
        int idx;

        /* default is ETC */
        for (idx = 0; idx < 256; idx++)
                tokentypes[idx] = TOKEN_ETC;

        tokentypes['.'] = TOKEN_PERIOD;
        tokentypes['?'] = TOKEN_QMARK;
        tokentypes['!'] = TOKEN_EPOINT;
        tokentypes[','] = TOKEN_COMMA;
        tokentypes[':'] = TOKEN_COLON;
        tokentypes[';'] = TOKEN_SCOLON;
        tokentypes['='] = TOKEN_EQUALS;
        tokentypes['|'] = TOKEN_BAR;
}
