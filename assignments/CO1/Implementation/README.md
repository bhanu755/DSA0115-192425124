# CO1 Metro Smart-Card Fare Logic

This program models a single metro journey, calculates its fare, applies an
eligible passenger concession, and debits a smart card only when at least
Rs.50.00 remains afterward. Amounts are represented as integer paise; rupees
are used only for formatted input and output.

## Fare assumptions

The CO1 assignment document was not available in the repository when this
implementation was prepared. These defaults are therefore explicit and
centralized in `metro_fare_system.cpp`; replace them with the assignment's
specified values if they differ.

| Origin/destination | Base fare |
| --- | ---: |
| Same zone | Rs.20.00 |
| Adjacent zones | Rs.30.00 |
| Zone 1 to Zone 3, or reverse | Rs.40.00 |

Peak periods are 07:00-09:59 and 17:00-19:59. A peak journey adds Rs.10.00
to the base fare. Students and seniors receive a 50% concession on the base
fare plus any peak surcharge. Money calculations use integer paise and round
down if a future policy value produces a fractional paise. Adults receive no
concession. The minimum balance is checked after the entire fare is deducted.
The origin and destination may be the same zone.

## Compile

From this directory, compile with a C++17 compiler:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic metro_fare_system.cpp -o metro_fare_system
```

## Run

```sh
./metro_fare_system
```

Enter the initial card balance in rupees (up to two decimal places), passenger
type (`adult`, `student`, or `senior`), origin and destination zones (`1`-`3`),
and departure time in valid 24-hour `HH:MM` format. Invalid input is rejected
before fare processing. A declined journey does not debit the card.

## Test

```sh
./metro_fare_system --test
```

The built-in checks exercise the fare table, concessions, peak surcharge,
minimum-balance rule, invalid inputs, paise parsing, and peak-window boundaries.
Additional interactive examples and expected outcomes are in `test_cases.txt`.