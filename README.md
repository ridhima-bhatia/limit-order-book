## Limit Order Book & Matching Engine (C++)

### Overview
This project implements the core logic of a trading exchange by maintaining a limit order book and matching buy and sell limit orders using price–time priority.  
The matching engine is implemented independently of the input interface; a lightweight CLI is provided to simulate order flow.



### Features
- Buy and sell limit orders
- Price priority followed by time priority
- Partial order fills
- Efficient order matching using ordered data structures



### Design Decisions
- **Price Priority:** Implemented using ordered maps to always access the best available price.
- **Time Priority:** FIFO queues are used at each price level to ensure fair execution of orders.
- **Efficiency:** Logarithmic-time price level access with clean matching logic.



### Time Complexity
- Order insertion: O(log N)
- Best price lookup: O(1)
- Order matching: Efficient, dependent on number of fills



### How to Run
```bash
g++ limit_order_book.cpp -o order_book
./order_book
