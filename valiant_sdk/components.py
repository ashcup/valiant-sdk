# AST nodes

class ASTNode:
    '''
    A node within an Abstract Syntax Tree (AST).
    '''

    _children = []
    '''
    A list of nodes connected above this node in the tree.
    '''

    def __str__(self) -> str:
        return ""


# Expressions

class Expression(ASTNode):
    '''
    An expression which can evaluate to a value at runtime.
    '''
    pass


# Literals

class Literal(Expression):
    '''
    A literal value which is known at compile time.
    '''
    @property
    def value(self) -> object:
        '''
        The value of the literal.
        '''
        return self._children[0]

    @value.setter
    def value(self, value: object):
        self._children[0] = value

    def __init__(self):
        self._children.append(None)

    def __str__(self) -> str:
        return str(self.value)


class IntegerLiteral(Literal):
    '''
    A literal integer value which is known at compile time.
    '''
    @property
    def value(self) -> int:
        return self._children[0]

    @value.setter
    def value(self, value: int):
        self._children[0] = value


class NumberLiteral(Literal):
    '''
    A literal number value which is known at compile time.
    '''
    @property
    def value(self) -> float:
        return self._children[0]

    @value.setter
    def value(self, value: float):
        self._children[0] = value


class StringLiteral(Literal):
    '''
    A literal string value which is known at compile time.
    '''
    @property
    def value(self) -> str:
        return self._children[0]

    @value.setter
    def value(self, value: str):
        self._children[0] = value


# Statements

class PrintExpression(Expression):
    @property
    def message(self) -> Expression:
        return self._message

    def __init__(self, message: Expression):
        self._message = message

    def __str__(self) -> str:
        return "print " + str(self.message)
