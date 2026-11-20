# Task B4 – Final Engineering Decision

Compile and run:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
```

Sanitizer test:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g sanitizer_test.cpp -o sanitizer_test
./sanitizer_test
```

Actual sanitizer output observed in this environment:

## AddressSanitizer evidence

```text
Sanitizer bill total: 1700
~OutPatient()
~Bill()
Caught in sanitizer test: exceeds cover
```
