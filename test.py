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