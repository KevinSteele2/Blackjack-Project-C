#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "blackjack.h"


int play_blackjack(){
// Setup
    char input[10];
    Deck deck;
    Hand player;
    Hand dealer;
    init_deck(&deck);
    shuffle_deck(&deck);
    init_hand(&player);
    init_hand(&dealer);
    add_card(&player, draw_card(&deck));
    add_card(&player, draw_card(&deck));
    add_card(&dealer, draw_card(&deck));
    add_card(&dealer, draw_card(&deck));
    print_hand(&player, 0);
    printf("\n");
    print_hand(&dealer, 1);
    int player_total = calculate_hand(&player);
    int dealer_total = calculate_hand(&dealer);

// Player's turn
    while(1){
        Sleep(1000);
        printf("Do you want to hit or stand? ");
        scanf("%s", input);

        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        if (strcmp(input, "hit") == 0) {
            add_card(&player, draw_card(&deck));
            printf("\n");
            print_hand(&player, 0);
            player_total = calculate_hand(&player);
            if (player_total > 21) {
                printf("\nYou bust!\n");
                break;
            }
            if (player_total == 21) {
                printf("\nYou got 21! Dealer's turn.\n");
                break;
            }
        } else if (strcmp(input, "stand") == 0) {
            break;
        } else {
            printf("Invalid input. Please type \"hit\" or \"stand.\"\n");
        }
    }

// Dealer's turn
    printf("\n");
    print_hand(&dealer, 2);
    while(1){
        Sleep(1000);
        dealer_total = calculate_hand(&dealer);
        if (player_total > 21) {
            break;
        }
        if(dealer_total >= 17){
            break;
        }
        printf("\nDealer hits.\n");
        add_card(&dealer, draw_card(&deck));
        print_hand(&dealer, 2);
    }

// Determine winner
    if(dealer_total > 21 && player_total <= 21){
        printf("\nDealer busts! You win!\n");
    }else if(dealer_total == player_total && dealer_total <= 21){
        printf("\nIt's a draw!\n");
    }else if(player_total > dealer_total && player_total <= 21){
        printf("\nYou win!\n");
    }else if(dealer_total > player_total && dealer_total <= 21){
        printf("\nDealer wins!\n");
    }else if(player_total > 21){
        printf("\nYou bust! Dealer wins.\n");
    }


    for(int i = 0; i < 52; i++){
        free(deck.deck[i]);
    }
    return 0;
}
int main(){
    printf("Welcome to Blackjack\nHere is how to play:\n");
    printf("You will be dealt two cards, and the dealer will be dealt two cards.\n");
    printf("The goal is to get closer to 21 than the dealer, without going over.\n");
    printf("If you go over 21, you bust and lose the game.\n");
    printf("At the start, you will be asked if you want to hit or stand.\n");
    printf("If you hit, you will be dealt another card.\n");
    printf("If you stand, you will keep your current hand, and the dealer will go.\n");
    printf("The dealer will hit until they reach 17 or higher.\n");
    printf("When it is your turn, type either \"hit\" or \"stand.\"\n");
    printf("Good luck!\n\n");

    play_blackjack();
    int play = 0;
    char input[10];
    while(play == 0) {
        printf("Do you want to play again? (yes or no) \n");
        scanf("%s", input);
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }
        if (strcmp(input, "yes") == 0) {
            printf("\n");
            play_blackjack();
        } else if (strcmp(input, "no") == 0) {
            break;
        } else {
            printf("Invalid input. Please type \"yes\" or \"no.\"\n");
        }
    }
}
