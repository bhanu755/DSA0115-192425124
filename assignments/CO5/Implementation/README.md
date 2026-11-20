# CO5 – Reliable Software with Runtime Polymorphism and Exceptions

**Student Name:** B. Bhanu Sai Prakash Reddy
**Register Number:** 192425124
**Course:** Object-Oriented Programming with C++
**Course Code:** DSA01
**Compiler:** g++
**C++ Standard:** C++17

## Project objective

This project applies runtime polymorphism, virtual destructors, exception
hierarchies, safe dynamic memory, benchmarking and extensible payer/bill
hierarchies to a hospital billing and insurance claims case study.

## Folder structure

```text
assignments/CO5/Implementation/
├── README.md
├── Task_B1/
│   ├── billing.h
│   ├── main.cpp
│   ├── runtime_binding.cpp
│   ├── destructor_test.cpp
│   └── README.md
├── Task_B2/
│   ├── exceptions.h
│   ├── main.cpp
│   ├── exception_tests.cpp
│   └── README.md
├── Task_B3/
│   ├── benchmark.h
│   ├── main.cpp
│   ├── benchmark.cpp
│   └── README.md
└── Task_B4/
    ├── main.cpp
    ├── sanitizer_test.cpp
    └── README.md
```

## Compilation

Normal compilation:

```bash
g++ -std=c++17 -Wall -Wextra
```

Optimized benchmark compilation:

```bash
g++ -std=c++17 -O2 -Wall -Wextra
```

AddressSanitizer:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g
```

## Run each task

```bash
# Task B1
cd assignments/CO5/Implementation/Task_B1
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
g++ -std=c++17 -Wall -Wextra runtime_binding.cpp -o runtime_binding
./runtime_binding
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g destructor_test.cpp -o destructor_test
./destructor_test

# Task B2
cd ../Task_B2
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
g++ -std=c++17 -Wall -Wextra exception_tests.cpp -o exception_tests
./exception_tests

# Task B3
cd ../Task_B3
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main
./main
g++ -std=c++17 -O2 -Wall -Wextra benchmark.cpp -o benchmark
./benchmark

# Task B4
cd ../Task_B4
g++ -std=c++17 -Wall -Wextra main.cpp -o main
./main
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g sanitizer_test.cpp -o sanitizer_test
./sanitizer_test
```

## Results

- B1: run `main` and confirm Ravi is 1700 and Meena is 47500.
- B2: run `main` and `exception_tests` and compare with the expected outputs.
- B3: the first actual benchmark run recorded 17.1742 ms virtual and
  0.936517 ms switch for 1,000,000 bills; 170.468 ms virtual and
  9.44387 ms switch for 10,000,000 bills. The variant run was 37.4737 ms.
- B4: run `main`; only actual successful assertions print PASS.
- Sanitizer: the actual B4 terminal output is recorded in `Task_B4/README.md`.

## Experiments requiring manual execution

1. Run the B1 destructor test with AddressSanitizer.
2. Run B3 benchmarks several times to collect measured timings.
3. Run B4 sanitizer test and paste the actual terminal output.
4. Capture screenshots of successful normal runs and sanitizer evidence.

No timing or sanitizer result should be copied or invented.
