#include "Cards.h"

CardPile::~CardPile() {
    // Walk through list and delete each node.
    Card* walkthrough = this->getHead();
    Card* follower = walkthrough;
    while (walkthrough != nullptr) {
        walkthrough = walkthrough->getNext();
        delete follower;
        follower = walkthrough;
    }
}

/* updatePile(): Update the depth of each card in the pile and calculate the weight. */
bool CardPile::updatePile() {
    if (!this->getHead()->getNext()) { // Represents and empty list.
        weight = 0;
        return true; // Returns true to denote the player has attained an empty pile.
    }
    else {
        // Update depth of each card
        unsigned int depth = 1;
        this->weight = 0;

        Card* walkthrough = this->getHead()->getNext();
        while (walkthrough->getNext()) {
            walkthrough->setDepth(depth);
            this->weight += walkthrough->getWeight(); // Update weight of pile
            walkthrough = walkthrough->getNext();
            depth++;
        }
        walkthrough->setDepth(depth);
        this->weight += walkthrough->getWeight();
    }
    return false;
}

/* insertAtFront */
void CardPile::insertAtFront(Card*& inCard) {
    inCard->setNext(this->getHead()->getNext()); // Point input card to current top
    if (inCard->getNext()) inCard->getNext()->setBack(inCard);
    inCard->setBack(this->getHead());
    this->getHead()->setNext(inCard);
    this->updatePile();
}

/* deleteFromFront */
Card* CardPile::deleteFromFront() {
    Card* outCard = this->getHead()->getNext();
    this->getHead()->setNext(outCard->getNext());
    if (outCard->getNext()) outCard->getNext()->setBack(this->getHead());
    updatePile();
    return outCard;
}

/* deleteFromBack */
Card* CardPile::deleteFromBack() {
    this->setTail(this->getTail()->getBack());
    Card* outCard = this->getTail()->getNext();
    this->getTail()->setNext(nullptr);
    updatePile();
    return outCard;
}

/* emlaceCard */
void CardPile::emplaceCard(const int& value) {
    // Create a new card and insert it on the top of the pile:
    Card* inCard = new Card(value);
    this->insertAtFront(inCard);
}

/* BubbleSort */
void CardPile::BubbleSort() {
    // Simple bubble sort algorithm
    unsigned int count = this->getCount();
    while (count) {
        // Store the card with the highest value and then swap it with the last card.
        // Every entry is checked, so once the highest card has been swapped, its
        // positions is final.
        Card* endingCard = this->getHead()->getNext(); // top of stack
        unsigned int value = endingCard->getValue();
        Card* highestCard = endingCard;

        // Only traverses the portion of the pile that hasn't been swapped to
        // its final set of positions.
        for (int i = 0; i < count - 1; i++) {
            endingCard = endingCard->getNext();
            if (endingCard->getValue() > value) {
                highestCard = endingCard;
                value = endingCard->getValue();
            }
        }
        // Swap
        // Stored swaps with c
        this->SwapCards(highestCard, endingCard);
        count--; // highest card has been sorted, don't bother checking it again
    }
    this->updatePile();
}

/* SwapCards */
void CardPile::SwapCards(Card*& highestCard, Card*& endingCard) {
    if (highestCard == endingCard) return; // Don't swap card with itself
    Card* tempCard = new Card(0); // temporary card to hold pointers to linked cards

    tempCard->setNext(endingCard->getNext());
    if (highestCard->getNext() == endingCard) { // the cards being consecutive is an edge case
        /* Set the lower value card's back pointer to that previously held by
         * the higher card. Set the lower value card's next pointer to point tothe higher value card.
         */
        tempCard->setBack(highestCard->getBack());
        endingCard->setNext(highestCard);
        endingCard->setBack(tempCard->getBack());
    }
    else {
        /* Set the lower value card's next and back pointers to those previously held by
         * the higher value card. Then set the higher card's next and back pointer
         * to those previously held by the lower card.
         */
        tempCard->setBack(endingCard->getBack());
        endingCard->setNext(highestCard->getNext());
        endingCard->setBack(highestCard->getBack());
        highestCard->setBack(tempCard->getBack());
    }
    endingCard->getNext()->setBack(endingCard);
    endingCard->getBack()->setNext(endingCard);
    highestCard->setNext(tempCard->getNext());
    highestCard->getBack()->setNext(highestCard);
    if (highestCard->getNext()) highestCard->getNext()->setBack(highestCard);
    // Update the tail:
    if (endingCard == this->getTail()) this->setTail(highestCard);
    delete tempCard;
}

/* getCount */
unsigned int CardPile::getCount() const {
    // Walkthrough the pile and increment the count until the end is reached:
    unsigned int count = 0;
    Card* walkthrough = this->getHead()->getNext();
    while (walkthrough) {
        count++;
        walkthrough = walkthrough->getNext();
    }
    return count;
}

/* initializeCardPile */
void Player::initializeCardPile(int numCards) {
    // input: number of total cards the pile should initially contain
    this->cardPile.setHead(new Card(0)); // value in head is arbitary
    this->cardPile.emplaceCard(numCards);
    this->cardPile.setTail(this->cardPile.getHead()->getNext());
    for (int i = numCards - 1; i >= 1; i--)
        this->cardPile.emplaceCard(i);
    // Calculate weight
    cardPile.updatePile();
}