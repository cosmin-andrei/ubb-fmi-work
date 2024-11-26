import re

# Regex patterns for identifiers, constants, keywords, and operators
identifier_pattern = re.compile(r'^[a-zA-Z_][a-zA-Z0-9_]*$')
constant_pattern = re.compile(r'^\d+(\.\d+)?$')
keywords_pattern = re.compile(r'\b(int|cin|cout|while|if|else)\b')
operator_pattern = re.compile(r'(\+|-|\*|/|==|!=|<=|>=|<|>|=|>>|<<)')
separator_pattern = re.compile(r'[{}();]')

# Tokenizer function
def tokenize(code: str) -> list[str]:
    # Find all tokens in code
    tokens = re.findall(r'\b\d+(\.\d+)?\b|\b[a-zA-Z_][a-zA-Z0-9_]*\b|>>|<<|==|!=|<=|>=|[+\-*/=<>;(){}]', code)
    return tokens

# Check if atom is an identifier
def is_identifier(atom: str) -> bool:
    return re.match(identifier_pattern, atom) is not None and not re.match(keywords_pattern, atom)

# Check if atom is a constant
def is_constant(atom: str) -> bool:
    return re.match(constant_pattern, atom) is not None

# Check if atom is a keyword
def is_keyword(atom: str) -> bool:
    return re.match(keywords_pattern, atom) is not None

# Check if atom is an operator
def is_operator(atom: str) -> bool:
    return re.match(operator_pattern, atom) is not None

# Check if atom is a separator
def is_separator(atom: str) -> bool:
    return re.match(separator_pattern, atom) is not None
