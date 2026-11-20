# Task B1 – Polymorphic Billing

## Compile

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o main
g++ -std=c++17 -Wall -Wextra runtime_binding.cpp -o runtime_binding
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g destructor_test.cpp -o destructor_test
```

Run:

```bash
./main
./runtime_binding
./destructor_test
```

The required validation values are:

- Ravi: `500 + 1200 = 1700`
- Meena: `3 * 2500 + 40000 = 47500`
- Day care: `18000`
- Emergency: `3000 + 2500 = 5500`
