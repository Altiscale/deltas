/*
 * Module: Wikitext
 * File: wikitext_split_types.h
 *
 * Copyright (C) 2016 Altiscale, Inc.
 * Licensed under the Apache License, Version 2.0
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 */

/* These values are indexes into the LEXICON in wikitext_split.py.
   If wikitext_split.py changes, this enum must also change.
*/
typedef enum {
        TOKEN_COMMENT_START,
        TOKEN_COMMENT_END,
        TOKEN_URL,
        TOKEN_ENTITY,
        TOKEN_CJK,
        TOKEN_TAG,
        TOKEN_NUMBER,
        TOKEN_JAPAN_PUNCT,
        TOKEN_DANDA,
        TOKEN_WORD,
        TOKEN_PERIOD,
        TOKEN_QMARK,
        TOKEN_EPOINT,
        TOKEN_COMMA,
        TOKEN_COLON,
        TOKEN_SCOLON,
        TOKEN_BREAK,
        TOKEN_WHITESPACE,
        TOKEN_DBRACK_OPEN,
        TOKEN_DBRACK_CLOSE,
        TOKEN_BRACK_OPEN,
        TOKEN_BRACK_CLOSE,
        TOKEN_TAB_OPEN,
        TOKEN_TAB_CLOSE,
        TOKEN_DCURLY_OPEN,
        TOKEN_DCURLY_CLOSE,
        TOKEN_CURLY_OPEN,
        TOKEN_CURLY_CLOSE,
        TOKEN_BOLD,
        TOKEN_ITALIC,
        TOKEN_EQUALS,
        TOKEN_BAR,
        TOKEN_ETC
} token_types;
