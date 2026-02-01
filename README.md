## Limit Order Book & Matching Engine (C++)

### Overview
This project implements the core logic of a trading exchange by maintaining a limit order book and matching buy and sell limit orders using price–time priority. It supports partial order fills and efficient real-time order matching.



### Features
- Buy and sell limit orders
- Price priority followed by time priority
- Partial order fills
- Efficient order matching using ordered data structures


### Design Decisions
- **Price Priority:** Implemented using ordered maps to always access the best available price in O(1) time.
- **Time Priority:** FIFO queues are used at each price level to ensure fair execution of orders.
- **Efficiency:** Matching logic ensures logarithmic time complexity for price-level operations.



### Time Complexity
- Order insertion: O(log N)
- Best price lookup: O(1)
- Order matching: Efficient, dependent on number of fills



### How to Run
```bash
g++ order_book.cpp -o order_book
./order_book
