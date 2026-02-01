#include <iostream>
#include <map>
#include <queue>
using namespace std;

enum class Side { BUY, SELL };

struct Order {
    int id;
    Side side;
    int price;
    int quantity;

    Order(int id, Side side, int price, int quantity)
        : id(id), side(side), price(price), quantity(quantity) {}
};

class OrderBook {
private:
    map<int, queue<Order>, greater<int>> buyBook;
    map<int, queue<Order>> sellBook;

public:
    void addOrder(const Order& incoming) {
        Order order = incoming;

        if (order.side == Side::BUY)
            matchBuy(order);
        else
            matchSell(order);
    }

    void printOrderBook() const {
        cout << "\n===== ORDER BOOK =====\n";

        cout << "\nBUY SIDE (Price Desc):\n";
        for (const auto& [price, q] : buyBook)
            cout << "Price " << price << " | Orders " << q.size() << endl;

        cout << "\nSELL SIDE (Price Asc):\n";
        for (const auto& [price, q] : sellBook)
            cout << "Price " << price << " | Orders " << q.size() << endl;
    }

private:
    void matchBuy(Order& buyOrder) {
        while (buyOrder.quantity > 0 && !sellBook.empty()) {
            auto bestSell = sellBook.begin();

            if (bestSell->first > buyOrder.price)
                break;

            auto& sellQueue = bestSell->second;

            while (!sellQueue.empty() && buyOrder.quantity > 0) {
                Order& sellOrder = sellQueue.front();
                int tradedQty = min(buyOrder.quantity, sellOrder.quantity);

                buyOrder.quantity -= tradedQty;
                sellOrder.quantity -= tradedQty;

                cout << "TRADE | BuyID " << buyOrder.id
                     << " SellID " << sellOrder.id
                     << " Price " << bestSell->first
                     << " Qty " << tradedQty << endl;

                if (sellOrder.quantity == 0)
                    sellQueue.pop();
            }

            if (sellQueue.empty())
                sellBook.erase(bestSell);
        }

        if (buyOrder.quantity > 0)
            buyBook[buyOrder.price].push(buyOrder);
    }

    void matchSell(Order& sellOrder) {
        while (sellOrder.quantity > 0 && !buyBook.empty()) {
            auto bestBuy = buyBook.begin();

            if (bestBuy->first < sellOrder.price)
                break;

            auto& buyQueue = bestBuy->second;

            while (!buyQueue.empty() && sellOrder.quantity > 0) {
                Order& buyOrder = buyQueue.front();
                int tradedQty = min(sellOrder.quantity, buyOrder.quantity);

                sellOrder.quantity -= tradedQty;
                buyOrder.quantity -= tradedQty;

                cout << "TRADE | BuyID " << buyOrder.id
                     << " SellID " << sellOrder.id
                     << " Price " << bestBuy->first
                     << " Qty " << tradedQty << endl;

                if (buyOrder.quantity == 0)
                    buyQueue.pop();
            }

            if (buyQueue.empty())
                buyBook.erase(bestBuy);
        }

        if (sellOrder.quantity > 0)
            sellBook[sellOrder.price].push(sellOrder);
    }
};

int main() {
    OrderBook book;

    cout << "Commands:\n";
    cout << "B id price qty  -> Buy order\n";
    cout << "S id price qty  -> Sell order\n";
    cout << "P              -> Print order book\n";
    cout << "Q              -> Quit\n\n";

    while (true) {
        char cmd;
        cin >> cmd;

        if (cmd == 'Q')
            break;

        if (cmd == 'P') {
            book.printOrderBook();
            continue;
        }

        int id, price, qty;
        cin >> id >> price >> qty;

        if (cmd == 'B')
            book.addOrder(Order(id, Side::BUY, price, qty));
        else if (cmd == 'S')
            book.addOrder(Order(id, Side::SELL, price, qty));
    }

    return 0;
}
