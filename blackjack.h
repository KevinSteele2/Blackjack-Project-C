#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int rank;
    int suit;
} Card;

typedef struct{
    Card *cards;
    int num_cards;
} Hand;

typedef struct{
    Card *deck[52];
    Card top_card;
} Deck;

void init_deck(Deck *deck);
void shuffle_deck(Deck *deck);
void init_hand(Hand *hand);
void add_card(Hand *hand, Card card);
void print_hand(Hand *hand, int dealer);
void print_card(Card card);
Card draw_card(Deck *deck);
void print_deck(Deck *deck);
int calculate_hand(Hand *hand);

#endif // BLACKJACK_H