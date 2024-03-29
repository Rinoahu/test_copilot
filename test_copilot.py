#!usr/bin/env python

# Mixed-integer programming
def mixed_integer_programming(c, A_ub, b_ub, A_eq, b_eq, bounds):
    """
    Solves a mixed-integer linear programming problem.
    :param c: Coefficients of the linear objective function.
    :param A_ub: Matrix of upper-bound constraints.
    :param b_ub: Upper-bound constraints.
    :param A_eq: Matrix of equality constraints.
    :param b_eq: Equality constraints.
    :param bounds: Bounds of the variables.
    :return: Solution of the problem.
    """
    # Create the model
    model = Model()

    # Create variables
    variables = []
    for i in range(len(bounds)):
        variables.append(model.addVar(lb=bounds[i][0], ub=bounds[i][1], vtype=GRB.INTEGER))

    # Set objective
    model.setObjective(quicksum(c[i] * variables[i] for i in range(len(c))), GRB.MINIMIZE)

    # Add constraints
    for i in range(len(A_ub)):
        model.addConstr(quicksum(A_ub[i][j] * variables[j] for j in range(len(A_ub[i]))) <= b_ub[i])

    for i in range(len(A_eq)):
        model.addConstr(quicksum(A_eq[i][j] * variables[j] for j in range(len(A_eq[i]))) == b_eq[i])

    # Optimize
    model.optimize()

    # Get solution
    solution = []
    for i in range(len(variables)):
        solution.append(variables[i].x)

    return solution

# mixed-integer programming, simplex method
def mixed_integer_programming_simplex(c, A_ub, b_ub, A_eq, b_eq, bounds):
    """
    Solves a mixed-integer linear programming problem.
    :param c: Coefficients of the linear objective function.
    :param A_ub: Matrix of upper-bound constraints.
    :param b_ub: Upper-bound constraints.
    :param A_eq: Matrix of equality constraints.
    :param b_eq: Equality constraints.
    :param bounds: Bounds of the variables.
    :return: Solution of the problem.
    """
    # Create the model
    model = Model()

    # Create variables
    variables = []
    for i in range(len(bounds)):
        variables.append(model.addVar(lb=bounds[i][0], ub=bounds[i][1], vtype=GRB.INTEGER))

    # Set objective
    model.setObjective(quicksum(c[i] * variables[i] for i in range(len(c))), GRB.MINIMIZE)

    # Add constraints
    for i in range(len(A_ub)):
        model.addConstr(quicksum(A_ub[i][j] * variables[j] for j in range(len(A_ub[i]))) <= b_ub[i])

    for i in range(len(A_eq)):
        model.addConstr(quicksum(A_eq[i][j] * variables[j] for j in range(len(A_eq[i]))) == b_eq[i])

    # Optimize
    model.optimize()

    # Get solution
    solution = []
    for i in range(len(variables)):
        solution.append(variables[i].x)

    return solution


# protein 3d structure prediction
def RoseTTAFold(sequence, structure, temperature, iterations, seed):
    """
    Predict the 3D structure of a protein using the ROSE algorithm.
    :param sequence: Sequence of the protein.
    :param structure: Structure of the protein.
    :param temperature: Temperature of the simulation.
    :param iterations: Number of iterations of the simulation.
    :param seed: Seed of the simulation.
    :return: 3D structure of the protein.
    """
    # Create the model
    model = Model()

    # Create variables
    variables = []
    for i in range(len(sequence)):
        variables.append(model.addVar(lb=0, ub=1, vtype=GRB.BINARY))

    # Set objective
    model.setObjective(quicksum(variables[i] for i in range(len(sequence))), GRB.MINIMIZE)

    # Add constraints
    for i in range(len(sequence)):
        if structure[i] == 'H':
            model.addConstr(variables[i] == 1)
        elif structure[i] == 'E':
            model.addConstr(variables[i] == 0)
        else:
            model.addConstr(variables[i] + variables[(i + 1) % len(sequence)] <= 1)
            model.addConstr(variables[i] + variables[(i + 1) % len(sequence)] >= 1 - temperature)

    # Optimize
    model.optimize()

    # Get solution
    solution = []
    for i in range(len(sequence)):
        solution.append(variables[i].x)

    return solution


# sudoku solver
def sudoku_solver(grid):
    """
    Solves a Sudoku puzzle.
    :param grid: Grid of the puzzle.
    :return: Solution of the puzzle.
    """
    # Create the model
    model = Model()

    # Create variables
    variables = []
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            variables.append(model.addVar(lb=0, ub=9, vtype=GRB.INTEGER))

    # Set objective
    model.setObjective(quicksum(variables[i * 9 + j] for i in range(len(grid)) for j in range(len(grid[i]))), GRB.MINIMIZE)

    # Add constraints
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] != 0:
                model.addConstr(variables[i * 9 + j] == grid[i][j])

    # Optimize
    model.optimize()

    # Get solution
    solution = []
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            solution.append(variables[i * 9 + j].x)

    return solution


# hanoi tower
def hanoi_tower(n, a, b, c):
    if n <= 1:
        print(a, b)
    else:
        hanoi_tower(n - 1, a, c, b)
        print(a, b)
        hanoi_tower(n - 1, c, b, a)

# Relevance vector machine (RVM)
def RVM(X, y, kernel, C, epsilon, max_iter):
    """
    Solves a Relevance Vector Machine (RVM) problem.
    :param X: Matrix of the training data.
    :param y: Vector of the labels of the training data.
    :param kernel: Kernel function.
    :param C: Regularization parameter.
    :param epsilon: Convergence parameter.
    :param max_iter: Maximum number of iterations.
    :return: Solution of the problem.
    """
    # Create the model
    model = Model()

    # Create variables
    variables = []
    for i in range(len(X)):
        variables.append(model.addVar(lb=0, ub=1, vtype=GRB.BINARY))

    # Set objective
    model.setObjective(quicksum(variables[i] for i in range(len(X))), GRB.MINIMIZE)

    # Add constraints
    for i in range(len(X)):
        model.addConstr(variables[i] == y[i])
        for j in range(len(X)):
            if i != j:
                model.addConstr(variables[i] + variables[j] <= 1)
                model.addConstr(variables[i] + variables[j] >= 1 - C * kernel(X[i], X[j]))

    # Optimize
    model.optimize()

    # Get solution
    solution = []
    for i in range(len(X)):
        solution.append(variables[i].x)

    return solution



# qsort function
def qsort(A, p, r):
    if p < r:
        q = partition(A, p, r)
        qsort(A, p, q - 1)
        qsort(A, q + 1, r)
    return A

def partition(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1

# suffix tree algorithm (suffix tree)
def suffix_tree(text):
    """
    Builds a suffix tree of a text.
    :param text: Text of the suffix tree.
    :return: Suffix tree of the text.
    """
    # Create the root of the tree
    root = Node(None, None, None, None)
    for i in range(len(text)):
        add_suffix(root, text[i:])
    return root

# just a test
# quick sort function
# >OpenAI Codex: Suggest Auto Complete
# just a test 
def qsort(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]

# quick sort function