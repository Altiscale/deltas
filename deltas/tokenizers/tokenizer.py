import re
from collections import namedtuple

import yamlconf

from .token import Token

import Wikitext

class Tokenizer:
    """
    Constructs a tokenizaton strategy.
    """
    def tokenize(self, text, token_class=Token):
        """
        Tokenizes a text.
        """
        raise NotImplementedError()

    @classmethod
    def from_config(cls, config, name, section_key="tokenizers"):
        section = config[section_key][name]
        if 'module' in section:
            return yamlconf.import_module(section['module'])
        else:
            Tokenizer = yamlconf.import_module(section['class'])
            return Tokenizer.from_config(config, name, section_key)


class RegexTokenizer(Tokenizer):
    """
    Uses a lexicon of regular expressions and names to tokenize a text string.
    """
    def __init__(self, lexicon):
        self.lexicon = lexicon
        self.regex = re.compile('|'.join('(?P<{0}>{1})'.format(name, pattern)
                                         for name, pattern in lexicon))

    def tokenize(self, text, token_class=None):
        return [t for t in self._tokenize(text, token_class=token_class)]

    def _tokenize(self, text, token_class=None):
        """
        Tokenizes a text

        :Returns:
            A `list` of tokens
        """
        token_class = token_class or Token
        tokens = {}

        for i, match in enumerate(self.regex.finditer(text)):
            value = match.group(0)

            try:
                token = tokens[value]
            except KeyError:
                type = match.lastgroup
                token = token_class(value, type=type)
                tokens[value] = token

            yield token

    def _ctokenize(self, text, token_class=None):
        """
        Uses C instead of Python to tokenize the text.  For now the
        C code is hand-optimized for the wikitext_split lexicon, and
        must be modified by hand if the lexicon changes.

        After calling Wikitext.init, Wikitext.next must be called with
        the iterator until Wikitext.new returns a negative type_index.
        Violating this assumption will cause a memory leak.

        :Returns:
            A `list` of tokens
        """
        token_class = token_class or Token
        tokens = {}

        iterator = Wikitext.init(text)

        while True :
            type_index, value = Wikitext.next(iterator)
            if (type_index < 0):
              break

            try:
                token = tokens[value]
            except KeyError:
                type = self.lexicon[type_index][0]
                token = token_class(value, type=type)
                tokens[value] = token

            yield token
