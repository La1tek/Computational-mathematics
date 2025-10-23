import numpy as np

def get_error(n: int):
    A = np.array([[1 / (i + j) for j in range(1, n + 1)] for i in range(1, n + 1)], dtype=float)
    b = np.ones(n)
    x = np.linalg.solve(A, b)

    cond = np.linalg.cond(A)

    error = 0
    for _ in range(100):
        err = np.random.uniform(-1e-6, 1e-6, size=n)
        b_err = b + err

        x_err = np.linalg.solve(A, b_err)
        error += np.linalg.norm(x - x_err) / np.linalg.norm(x)

    return (error / 100, cond)

n = int(input())

for i in range(1, n + 1):
    error, cond = get_error(i)
    print(f"{i} - m(A) = {cond:.2f}, dx/x = {error:.8f}")