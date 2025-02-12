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

    def __init__(self, name: str, args: list[Expression]):
        super().__init__()
        self.name = name
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

    Example: `some_variable`
    '''

    @property
    def name(self) -> str:
        return self.children[0]

    @name.setter
    def name(self, value: str):
        self.children[0] = value

    def __init__(self, name: str):
        super().__init__()
        self.children.append(None)
        self.name = str(name)


class DeclareVariableExpression(VariableExpression):
    '''
    A variable declaration expression.

    Example: `declare set {x} to 10`
    '''

    def __init__(self, name: str):
        super().__init__(name)
        self.children.append(None)
        self.name = str(name)


# Math Expressions

class MathExpression(Expression):
    '''
    An math expression.
    '''

    def __init__(self):
        super().__init__()


class UnaryMathExpression(MathExpression):
    '''
    An unary math expression.
    '''

    @property
    def expression(self) -> Expression:
        return self._children[0]

    @property
    def expression(self, value: Expression):
        self._children[0] = value

    def __init__(self, expression):
        super().__init__()
        self.children.append(None)
        self.expression = expression


class BinaryMathExpression(MathExpression):
    '''
    An binary math expression.
    '''

    @property
    def left_expression(self) -> Expression:
        return self.children[0]

    @left_expression.setter
    def left_expression(self, value: Expression):
        self.children[0] = value

    @property
    def right_expression(self) -> Expression:
        return self.children[1]

    @right_expression.setter
    def right_expression(self, value: Expression):
        self.children[1] = value

    def __init__(self, left_expression, right_expression):
        super().__init__()
        # Set the left expression.
        self.children.append(None)
        self.left_expression = left_expression
        # Set the right expression.
        self.children.append(None)
        self.right_expression = right_expression


class AssignExpression(BinaryMathExpression):
    '''
    An assignment expression.

    Example:

    ```
    {x} = 42
    ```
    or
    ```
    set {x} to 42
    ```
    '''

    @property
    def assignment(self) -> Expression:
        '''
        The expression to be evaluated with its result assigned to the variable.
        '''
        return self.right_expression

    @assignment.setter
    def assignment(self, value: Expression):
        self.right_expression = value

    @property
    def variable(self) -> VariableExpression:
        '''
        The variable having a value assigned to it.
        '''
        return self.left_expression

    @variable.setter
    def variable(self, value: VariableExpression):
        self.left_expression = value

    def __init__(self, variable: VariableExpression, assignment: Expression):
        super().__init__(variable, assignment)


class AddExpression(BinaryMathExpression):
    '''
    An addition expression.

    Example: `{x} + 42`
    '''

    def __init__(self, left_expression: Expression, right_expression: Expression):
        super().__init__(left_expression, right_expression)


class SubtractExpression(BinaryMathExpression):
    '''
    A subtraction expression.

    Example: `{x} - 42`
    '''

    def __init__(self, left_expression: Expression, right_expression: Expression):
        super().__init__(left_expression, right_expression)


class MultiplyExpression(BinaryMathExpression):
    '''
    A multiplication expression.

    Example: `{x} * 42`
    '''

    def __init__(self, left_expression: Expression, right_expression: Expression):
        super().__init__(left_expression, right_expression)


class DivideExpression(BinaryMathExpression):
    '''
    A division expression.

    Example: `{x} / 42`
    '''

    def __init__(self, left_expression: Expression, right_expression: Expression):
        super().__init__(left_expression, right_expression)


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
    def id(self) -> int:
        if self._id is None:
            return id(self)
        return self._id

    @id.setter
    def id(self, value: int):
        self._id = value

    @property
    def local_variable_declarations(self) -> list[DeclareVariableExpression]:
        local_variable_declarations: list[DeclareVariableExpression] = []
        # Get the list of local variables to declare.
        local_variable_names = self.local_variable_names
        # Loop the local variable names:
        for local_variable_name in local_variable_names:
            # Create the variable declaration.
            local_variable_declaration = DeclareVariableExpression(local_variable_name)
            # Add the variable declaration to the list.
            local_variable_declarations.append(local_variable_declaration)
        # Return the list of local variable declarations.
        return local_variable_declarations

    @property
    def local_variable_names(self) -> list[str]:
        return self._local_variable_names

    @local_variable_names.setter
    def local_variable_names(self, value: list[str]):
        self._local_variable_names = value

    @property
    def local_variables(self) -> list[VariableExpression]:
        return self._local_variables

    @local_variables.setter
    def local_variables(self, value: list[VariableExpression]):
        self._local_variables = value

    @property
    def statements(self) -> list[Expression]:
        return self.children

    @statements.setter
    def statements(self, value: list[Expression]):
        self._children = value
        self._refresh_variables()

    def __init__(self, statements: list[Expression] = []):
        super().__init__()
        self._id = None
        self._reset_local_variables()
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
        self._refresh_variables()

    def _add_local_variable(self, variable: VariableExpression):
        # Add the variable to the list of local variables.
        self.local_variables.append(variable)
        # Get the variable's name.
        variable_name = variable.name
        # Add the variable name to the list of local variable names.
        self.local_variable_names.append(variable_name)

    def _inject_local_variable_declarations(self):
        # Get the list of local variable declarations.
        local_variable_declarations = self.local_variable_declarations()
        # Loop the local variable declarations.
        for local_variable_declaration in local_variable_declarations:
            # Inject a local variable declaration expression.
            self.statements.insert(0, local_variable_declaration)

    def _refresh_variables(self):
        # Reset the list of local variables and other related lists.
        self._reset_local_variables()
        # Get the list of statements.
        statements = self.statements
        # Loop statements:
        for statement in statements:
            # If the statement is an assignment expression:
            if isinstance(statement, AssignExpression):
                # Get the variable assigned to in the statement.
                local_variable = statement.variable
                self._add_local_variable(local_variable)

    def _reset_local_variables(self):
        self.local_variable_names = []
        self.local_variables = []


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
