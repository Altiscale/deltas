#
# Module: Wikitext
# File: quicktest.py
#
# Copyright (C) 2016 Altiscale, Inc.
# Licensed under the Apache License, Version 2.0
#   http://www.apache.org/licenses/LICENSE-2.0
#
import Wikitext

iterator = Wikitext.init('hello, world!!')

while True:
    type, literal = Wikitext.next(iterator)
    if (type < 0):
        break
    print(type, literal)
