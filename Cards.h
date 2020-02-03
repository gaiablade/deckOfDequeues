#pragma once
#include <iostream>

/* Card Class: Represents the Node of the LList */
class Card {
    private:
        unsigned int value; // Numerical value of the card.
        unsigned int depth; // Order of card in relation to other cards in pile
        Card* next;
        Card* back;
    public:
        Card(int val)
            : value(val), depth(val)
        {}
        // Get/set functions:
        inline int getWeight() const { return value * depth; }
        inline unsigned int getValue() const { return this->value; }
        inline void setValue(unsigned int value) { this->value = value; }
        inline void setDepth(unsigned int depth) { this->depth = depth; }
        inline Card* getNext() const { return this->next; }
        inline Card* getBack() const { return this->back; }
        inline void setNext(Card* newNext) { this->next = newNext; }
        inline void setBack(Card* newBack) { this->back = newBack; }
};

/* CardPile Class: Represents the LList of Cards */
class CardPile {
    private:
        Card* head;
        Card* tail;
        unsigned int size;
        unsigned int weight;
    public:
        ~CardPile();
        bool updatePile();
        void insertAtFront(Card*& n);
        Card* deleteFromFront();
        Card* deleteFromBack();
        void emplaceCard(const int& value);
        void BubbleSort();
        void SwapCards(Card*& c1, Card*& c2);
        unsigned int getCount() const;
        inline int getWeight() const { return weight; }
        inline Card* getHead() const { return head; }
        inline Card* getTail() const { return tail; }
        inline void setHead(Card* head) { this->head = head; }
        inline void setTail(Card* tail) { this->tail = tail; }
};

/* Player Class: Each player has a pile of cards */
class Player {
    public:
        CardPile cardPile;
    public:
        void initializeCardPile(int numCards);
};