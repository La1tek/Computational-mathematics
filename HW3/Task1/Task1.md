# Task1 - Среднеквадратичная линейная аппроксимация функции.

> Все расчеты находятся в файле [Task1.ipynb](/HW3/Task1/Task1.ipynb)

## Цель

- Построить наилучшую среднеквадратическую линейную аппроксимацию для функции $f(x)=e^x$ при $x \in [0,1]$

## Реализация

### Скалярное произведение для функций

Реализуется как $\langle f, g \rangle = \int_0^1 f(x)\, g(x)\, dx$

```python
def dot_product(f, g, x):
    return np.trapezoid(f * g, x)
```

### Построение системы линейных уравнений

- `basis` — список функций-базисов для аппроксимации.
    - Для данной задачи это $g_1(x)=1$ и $g_2(x)=x$
    - Аппроксимируем $f(x) \approx \alpha_1 g_1(x) + \alpha_2 g_2(x)$

```python
f = lambda x: np.exp(x)  # f(x) = e^x

basis = [
    lambda x: np.ones_like(x),  # g_1(x) = 1
    lambda x: x                 # g_2(x) = x
]
```
- `M` — матрица скалярных произведений: элементы $M[i,j] = \langle g_i, g_j \rangle$.
- `b` — вектор правой части: элементы $b[i] = \langle g_i, f \rangle$.

```python
def build_system(basis, f, x):
    n = len(basis)
    M = np.zeros((n, n))
    b = np.zeros(n)

    for i in range(n):
        g_i = basis[i](x)
        b[i] = dot_product(g_i, f, x)
        for j in range(n):
            g_j = basis[j](x)
            M[i, j] = dot_product(g_i, g_j, x)
    return M, b
```

### Решение системы линейных уравнений
$M \alpha = b \Rightarrow \alpha = M^{-1}b$

Таким способом находятся коэффициенты $\alpha_1,\alpha_2$

```python
M, b = build_system(basis, f(x), x)
alpha = np.linalg.solve(M, b)
a, b_coef = alpha
```

### Построение аппроксимации

- Аппроксимация функции в виде $f(x) = \alpha_1 + \alpha_2 x$.
- Cреднеквадратичную ошибку найдем как корень из интеграла квадрата разности между исходной функцией и аппроксимацией $\sqrt{\int_0^1 \big(f(x) - p(x)\big)^2 \, dx}$

Получаем $\alpha_1 \approx 0.87$,  $\alpha_2 \approx 1.69$.
Среднеквадратичная ошибка $\approx 6.27 \cdot 10^{-2}$.

### График функции и её аппроксимации

![График функции и её аппроксимации](/HW3/Task1/img/aprroxEx.png)