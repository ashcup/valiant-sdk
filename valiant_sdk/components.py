# AST nodes

class ASTNode:
    '''
    A node within an Abstract Syntax Tree (AST).
    '''

    _children: list = []
    '''
    A list of nodes connected above this node in the tree.
    '''

    @property
    def child_count(self) -> int:
        return len(self._children)

    @property
    def children(self) -> list:
        return self._children

    @property
    def first_child(self) -> object:
        return self._children[0]

    @property
    def last_child(self) -> object:
        return self._children[self.child_count - 1]

    def __str__(self) -> str:
        return ""


# Expressions

class Expression(ASTNode):
    '''
    An expression which can evaluate to a value at runtime.

    Example:
    ```
    x = round(exp(3.74))
    ```
    '''
    pass


# Statements

class PrintExpression(Expression):
    '''
    A `print` expression.

    Example:
    ```
    print "Hello, world!"
    ```
    '''
    @property
    def message(self) -> Expression:
        return self._message

    def __init__(self, message: Expression):
        self._message = message

    def __str__(self) -> str:
        return "print " + str(self.message)


# Functions

class FunctionBody(ASTNode):
    '''
    A collection of statements to be executed when a function is called.

    Example:
    ```
    {
        x = 10
        y = 20
        z = x + y

        print "z: " + z
    }
    ```
    '''

    @property
    def statements(self) -> list[Expression]:
        return self._children

    @statements.setter
    def statements(self, value: list[Expression]):
        self._children = value

    def __init__(self, statements: list[Expression] = []):
        if statements is None or not isinstance(statements, list):
            statements = []
        self.statements = statements

    def __iter__(self):
        self._i = 0
        return self

    def __next__(self):
        # If the end of the iterable has been reached:
        if self._i >= len(self.statements):
            # End the iteration.
            raise StopIteration
        # Get the current statement.
        statement = self.statements[self._i]
        # Increment the index.
        self._i += 1
        # Return the statement.
        return statement

    def append(self, statement: Expression):
        self.statements.append(statement)


# Top-level definitions

class TopLevelDefinition(ASTNode):
    '''
    A top-level definition.
    '''
    pass

class EventHandler(TopLevelDefinition):
    '''
    An event handler.
    '''

    _name: str = "start"
    '''
    The name of the event this handler is for.
    '''

    @property
    def body(self) -> list[Expression]:
        return self._children

    @body.setter
    def body(self, value: list[Expression]):
        self._children = value

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str):
        # If the value is invalid:
        if type(value) is not str:
            # Normalize the value.
            value = str(value)
        self._name = value

    def __init__(self, event_name: str, body: FunctionBody = None):
        # If body is not a valid function body:
        if body is None or not isinstance(body, FunctionBody):
            # Create a new function body.
            body = FunctionBody()
        # Set the properties of this event handler.
        self.name = str(event_name)
        self.body = body

    def add_statement(self, statement: Expression):
        self.body.statements.append(statement)

    def remove_all_statements(self):
        self.body.statements.clear()
