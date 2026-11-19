# CO4 – Designing Reusable Class Hierarchies

Student: B. Bhanu Sai Prakash Reddy
Register number: 192425124
Course: DSA01 – Object-Oriented Programming with C++

## Files

- `Q1_Class_Design_Review.cpp`
- `Q2_Virtual_Base_Hierarchy.cpp`
- `Q3_Constructors_Member_Classes.cpp`
- `Q4_Polymorphism_Forensics.cpp`
- `Q5_Cart_This_Pointer.cpp`
- `Q6_Vehicle_Rental_Fleet.cpp`

## Compile and run

```bash
g++ -std=c++17 -Wall -Wextra Q1_Class_Design_Review.cpp -o q1
./q1

g++ -std=c++17 -Wall -Wextra Q2_Virtual_Base_Hierarchy.cpp -o q2
./q2

g++ -std=c++17 -Wall -Wextra Q3_Constructors_Member_Classes.cpp -o q3
./q3

g++ -std=c++17 -Wall -Wextra Q4_Polymorphism_Forensics.cpp -o q4
./q4

g++ -std=c++17 -Wall -Wextra Q5_Cart_This_Pointer.cpp -o q5
./q5

g++ -std=c++17 -Wall -Wextra Q6_Vehicle_Rental_Fleet.cpp -o q6
./q6
```

Task 4 AddressSanitizer command:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g Q4_Polymorphism_Forensics.cpp -o q4
./q4
```

## Notes

- No sample screenshot or measurement should be claimed unless obtained from an actual run.
- AddressSanitizer output is platform dependent and must be captured during execution.
- `sizeof` values are platform and compiler dependent.
