# Task B2 – Exception Engineering

## Compile

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o main
g++ -std=c++17 -Wall -Wextra exception_tests.cpp -o exception_tests
```

Run:

```bash
./main
./exception_tests
```

The predicted output for `main.cpp` is:

```text
ok done caught negative [log too large] caught too large
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```
