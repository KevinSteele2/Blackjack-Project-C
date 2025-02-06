#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "blackjack.h"

void init_deck(Deck *deck){
    int i, j;
    deck->top_card.rank = 0;
    deck->top_card.suit = 0;
    for(i = 0; i < 52; i++){
        deck->deck[i] = (Card *)malloc(sizeof(Card));
    }
    for(i = 0; i < 4; i++){
        for(j = 0; j < 13; j++){
            deck->deck[(i * 13) + j]->rank = j;
            deck->deck[(i * 13) + j]->suit = i;
        }
    }
}

void print_deck(Deck *deck){
    int i;
    for(i = 0; i < 52; i++){
        print_card(*deck->deck[i]);
    }
}

void print_card(Card card){
    char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    printf("%s of %s\n", ranks[card.rank], suits[card.suit]);
}

void shuffle_deck(Deck *deck){
    int i, j;
    Card *temp;
    srand(time(NULL));
    for(i = 0; i < 52; i++){
        j = rand() % 52;
        temp = deck->deck[i];
        deck->deck[i] = deck->deck[j];
        deck->deck[j] = temp;
    }
}

void init_hand(Hand *hand){
    hand->cards = (Card *)malloc(sizeof(Card) * 11);
    hand->num_cards = 0;
}

Card draw_card(Deck *deck){
    Card card = *deck->deck[0];
    int i;
    for(i = 0; i < 51; i++){
        deck->deck[i] = deck->deck[i + 1];
    }
    deck->deck[51] = (Card *)malloc(sizeof(Card));
    deck->top_card = *deck->deck[0];
    return card;
}

void add_card(Hand *hand, Card card){
    hand->cards[hand->num_cards] = card;
    hand->num_cards++;
}

void print_hand(Hand *hand, int dealer){
    int i;
    if(dealer == 1){
        printf("Dealer's Hand:\n");
        for (i = 0; i < hand->num_cards; i++){
            if(i == 0){
                printf("Hidden\n");
            }
            else{
                print_card(hand->cards[i]);
            }
        }
    }else if(dealer == 2){
        printf("Dealer's Hand:\n");
        for(i = 0; i < hand->num_cards; i++){
            print_card(hand->cards[i]);
        }
    }
    else{
        printf("Your Hand:\n");
        for(i = 0; i < hand->num_cards; i++){
            print_card(hand->cards[i]);
        }
    }
}

int calculate_hand(Hand *hand){
    int i, total = 0, aces = 0;
    for(i = 0; i < hand->num_cards; i++){
        if(hand->cards[i].rank == 12 && total + 11 <= 21){
            total += 11;
            aces++;
        }else if(hand->cards[i].rank > 8){
            total += 10;
        }else{
            total += hand->cards[i].rank + 2;
        }
    }

    // Adjust for aces
    while(total > 21 && aces > 0){
        total -= 10;
        aces--;
    }
    
    return total;
}
