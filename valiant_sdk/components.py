# AST nodes

class ASTNode:
    '''
    A node within an Abstract Syntax Tree (AST).
    '''

    @property
    def child_count(self) -> int:
        return len(self.children)

    @property
    def children(self) -> list:
        '''
        A list of nodes connected above this node in the tree.
        '''
        return self._children

    @property
    def first_child(self) -> object:
        return self.children[0]

    @first_child.setter
    def first_child(self, value: object):
        self.children[0] = value

    @property
    def last_child(self) -> object:
        return self.children[-1]

    @last_child.setter
    def last_child(self, value: object):
        self.children[-1] = value

    def __init__(self):
        self._children = []
        '''
        A list of nodes connected above this node in the tree.
        '''

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

    def __init__(self):
        super().__init__()


class FunctionCallExpression(Expression):
    '''
    A function call expression.

    Example:
    ```
    round(42.1)
    ```
    '''

    def __init__(self, global_id: str, args: list[Expression]):
        super().__init__()
        self.global_id = global_id
        self.args = args


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
        super().__init__()
        self._message = message

    def __str__(self) -> str:
        return "print " + str(self.message)

class VariableExpression(Expression):
    '''
    A variable.
    '''

    @property
    def global_id(self) -> str:
        return self.children[0]

    @global_id.setter
    def global_id(self, value: str):
        self.children[0] = value

    def __init__(self, global_id: str):
        super().__init__()
        self.children.append(None)
        self.global_id = str(global_id)



# Comments

class Comment(ASTNode):
    '''
    A comment that helps explain source code but has no actual effect.
    '''

    @property
    def value(self) -> str:
        return self.first_child

    @value.setter
    def value(self, value: str):
        self.first_child = str(value).strip()

    def __init__(self, value):
        super().__init__()
        self.children.append(None)
        self.value = value

    def __str__(self):
        return self.value

class MultiLineComment(Comment):
    '''
    A multi-line comment that helps explain source code but has no actual effect.
    '''

    def __str__(self):
        return ";;;\n" + self.value + "\n;;;"

class SingleLineComment(Comment):
    '''
    A single-line comment that helps explain source code but has no actual effect.
    '''

    def __str__(self):
        return ";; " + self.value


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
        return self.children

    @statements.setter
    def statements(self, value: list[Expression]):
        self._children = value

    def __init__(self, statements: list[Expression] = []):
        super().__init__()
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

    def __str__(self):
        # Start with empty source code.
        source_code = ""
        # Get the list of statements.
        statements = self.statements
        # Loop each statement:
        for statement in statements:
            # Add the source code for the statement to the source code for the function body.
            source_code += "    " + str(statement) + "\n"
        # Return the source code for the function body.
        return source_code


    def append(self, statement: Expression):
        '''
        Append a statement to the end of the function body.
        '''
        self.statements.append(statement)


# Top-level definitions

class TopLevelDefinition(ASTNode):
    '''
    A top-level definition.
    '''

    def __init__(self):
        super().__init__()

class EventHandler(TopLevelDefinition):
    '''
    An event handler.
    '''

    @property
    def body(self) -> FunctionBody:
        return self._body

    @body.setter
    def body(self, value: FunctionBody):
        self._body = value

    @property
    def name(self) -> str:
        '''
        The name of the event this handler is for.
        '''
        return self._name

    @name.setter
    def name(self, value: str):
        # If the value is invalid:
        if type(value) is not str:
            # Normalize the value.
            value = str(value)
        # Set the value.
        self._name = value

    def __init__(self, event_name: str, body: FunctionBody = None):
        super().__init__()
        self._body = FunctionBody()
        self._name = "start"
        '''
        The name of the event this handler is for.
        '''
        # If body is not a valid function body:
        if body is not None and isinstance(body, FunctionBody):
            # Create a new function body.
            self.body = body
        # Set the properties of this event handler.
        self.name = str(event_name)

    def add_statement(self, statement: Expression):
        self.body.statements.append(statement)

    def remove_all_statements(self):
        self.body.statements.clear()
