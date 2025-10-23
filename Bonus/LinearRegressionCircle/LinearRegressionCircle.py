import matplotlib.pyplot as plt
import numpy as np

def main():
    n = int(input("Number of points: "))
    x_i = np.random.normal(loc=0, scale=2, size=n)
    y_i = np.random.normal(loc=0, scale=2, size=n)

    f = x_i ** 2 + y_i ** 2
    g_1 = 2 * x_i
    g_2 = 2 * y_i
    g_3 = np.array([1] * n)

    G = np.column_stack((g_1, g_2, g_3))

    M = G.T @ G # Получаем матрицу скалярных произведений

    b = G.T @ f # Получаем правую часть

    a = np.linalg.inv(M) @ b

    x_0 = a[0]
    y_0 = a[1]
    r = np.sqrt(a[2] - x_0 ** 2 - y_0 ** 2)

    t = np.linspace(0, 2*np.pi, 360)
    circle_x = x_0 + r * np.cos(t)
    circle_y = y_0 + r * np.sin(t)

    plt.scatter(x_i, y_i, label="Points")
    plt.plot(circle_x, circle_y, color='red', label="Fitted Circle")
    plt.axis('equal')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()