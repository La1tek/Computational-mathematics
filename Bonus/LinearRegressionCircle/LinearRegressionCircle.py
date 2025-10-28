import matplotlib.pyplot as plt
import numpy as np

def main():
    n = int(input("Number of points: "))
    
    x_true = np.random.uniform(-10, 10)
    y_true = np.random.uniform(-10, 10)
    r_true = np.random.uniform(1, 10)

    angles = np.linspace(0, 2 * np.pi, n)
    noise = np.random.normal(loc=0, scale=0.2, size=(n, 2))
    x_i = x_true + r_true * np.cos(angles) + noise[:, 0]
    y_i = y_true + r_true * np.sin(angles) + noise[:, 1]

    f = x_i ** 2 + y_i ** 2
    g_1 = 2 * x_i
    g_2 = 2 * y_i
    g_3 = np.ones(n)

    G = np.column_stack((g_1, g_2, g_3))

    M = G.T @ G
    b = G.T @ f
    a = np.linalg.inv(M) @ b

    x_0 = a[0]
    y_0 = a[1]
    r = np.sqrt(a[2] + x_0 ** 2 + y_0 ** 2)

    t = np.linspace(0, 2 * np.pi, 360)
    circle_x_fit = x_0 + r * np.cos(t)
    circle_y_fit = y_0 + r * np.sin(t)

    circle_x_true = x_true + r_true * np.cos(t)
    circle_y_true = y_true + r_true * np.sin(t)

    plt.figure(figsize=(7, 7))
    plt.scatter(x_i, y_i, color='blue', label="Points", s=20)
    plt.plot(circle_x_fit, circle_y_fit, 'r-', label="Fitted Circle", linewidth=1)
    plt.plot(circle_x_true, circle_y_true, 'g--', label="True Circle", linewidth=1)
    plt.axis('equal')
    plt.legend()
    plt.title(f"Fitted circle: center=({x_0:.2f}, {y_0:.2f}), r={r:.2f} \n True circle: center=({x_true:.2f}, {y_true:.2f}), r={r_true:.2f} \n Number of points: {n}")
    
    plt.show()

if __name__ == "__main__":
    main()
