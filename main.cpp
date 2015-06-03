#include <stdio.h>
#include <iostream>
#include "cards.h"
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

//total amount of cards available 
const int amountOfCards = 52;

/***********************************************************************************************************************
Name            :   menu(void)
Arguments       :   None
Returns         :   None
Precondition    :   None
Postcondition   :   The menu will be displayed.
Description     :   This function displays the menu.
***********************************************************************************************************************/
void menu();

/***********************************************************************************************************************
Name            :   displayDeck(void)
Arguments       :   oneCard[](cards), amountOfCards(int), cardsDrawn(int)
Returns         :   None
Precondition    :   The newDeck(void) function must have been called prior to calling this function
Postcondition   :   This function will display the remaining cards in the deck.
Description     :   This funcion goes through each card in the deck and displays it but it skips the cards that
                    have already been draw.
***********************************************************************************************************************/
void displayDeck(cards oneCard[], int amountOfCards, int cardsDrawn);

/***********************************************************************************************************************
Name            :   newDeck(void)
Arguments       :   oneCard[](cards)
Returns         :   None
Precondition    :   The parameters must exist.
Postcondition   :   The array oneCard[](cards) will be filled with 52 cards with appropriate values.
Description     :   This function creates a "new deck". It fills the array oneCard[](cards) with 52 cards with
                    the correct corresponding values of real cards in a deck.
***********************************************************************************************************************/
void newDeck(cards oneCard[]);

/***********************************************************************************************************************
Name            :   shuffle(void)
Arguments       :   oneCard[](cards), amountOfCards(int), cardsDrawn(int)
Returns         :   None
Precondition    :   The newDeck(void) function must have been called prior to this function. The parameters must exist.
Postcondition   :   The card values in array oneCard[](cards) will no longer be in the same order. The values will
                    have been mixed.
Description     :   This function switches around the data locations of the cards in array oneCard[](cards). It
                    only shuffles the cards that have not been used.
***********************************************************************************************************************/
void shuffle(cards oneCard[], int amountOfCards, int cardsDrawn);

/***********************************************************************************************************************
Name            :   playGame(void)
Arguments       :   oneCard(cards), cardsDrawn(int&), money(int&), dealerCards[](int), maxDealerCards(int),
                    NumOfDealerCards(int&), playerCards[](int), maxPlayerCards(int), NumOfPlayerCards(int&)
Returns         :   None
Precondition    :   The newDeck(void) function must have been called prior to this function. The shuffle(void) function
                    should be called before this function but is not necessary. The parameters must all exist.
Postcondition   :   The dealer and player will have been dealt two cards. The counters for each player's cards will
                    increase. The drawn cards will be accounted for. The player and user's values will have changed.
Description     :   This function deals two cards each to the user and the dealer. Then it displays the cards drawn
                    for the user and one of the cards drawn for the dealer. The counters will all increase accordingly.
                    Then it will provide the user with the option to keep drawing cards or standing.
***********************************************************************************************************************/
void playGame(cards oneCard[], int & cardsDrawn, int& money, int dealerCards[], int maxDealerCards, int& NumOfDealerCards, int playerCards[], int maxPlayerCards, int& NumOfPlayerCards);

/***********************************************************************************************************************
Name            :   drawCards(void)
Arguments       :   oneCard[](cards), cardsDrawn(int&), dealerValue(int&), playerValue(int&), playerValue2(int&),
                    dealerValue2(int&), playerAceDrawn(int&), dealerAceDrawn(int&), currentCards(int&),
                    dealerCards[](int), maxDealerCards(int), NumOfDealerCards(int&), playerCards[](int),
                    maxPlayerCards(int), NumOfPlayerCards(int&)
Returns         :   None
Precondition    :   The newDeck(void) function must have been called prior to this function. The shuffle(void) function
                    should be called before this function but is not necessary for it to run properly. The
                    playGame(void) function must also have been called before this function. The preconditions for
                    those functions must also have been fulfilled. The parameters must all exist.
Postcondition   :   The player will have drawn another card which increases the playerValues and counters.
Description     :   This function replicates how a person would normally draw a card in blackjack. The player will
                    draw another card and the total is added to the player's total card value. And by drawing cards,
                    the counters will also increase to account for the drawn card.
***********************************************************************************************************************/
void drawCards(cards oneCard[], int& cardsDrawn, int& dealerValue, int& playerValue, int& playerValue2,int& dealerValue2 , int& playerAceDrawn, int dealerAceDrawn , int& currentCards, 
               int dealerCards[], int maxDealerCards, int& NumOfDealerCards, int playerCards[], int maxPlayerCards, int& NumOfPlayerCards);

/***********************************************************************************************************************
Name            :   limitCheck(void)
Arguments       :   playerValue(int), playerValue(int), userInput(char&), money(int&), betAmount(int),
                    NumOfDealerCards(int&), NumOfPlayerCards(int&)
Returns         :   None
Precondition    :   The newDeck(void), playGame(void), and drawCards(void) functions must all have been called prior to
                    calling this function. The parameters must exist. All of the preconditions for each of those
                    functions must be met.
Postcondition   :   The player will lose if the player's total value of cards exceeds 21. Nothing will happen if the
                    total value does not exceed 21.
Description     :   This function checks the player's total value of cards to see if the player busted(exceeded 21). If
                    the player busted then the player will lose. If the player did not bust then nothing will happen.
***********************************************************************************************************************/
void limitCheck(int playerValue, int playerValue2, char & userInput, int& money, int betAmount, int& NumOfDealerCards, int& NumOfPlayerCards);

/***********************************************************************************************************************
Name            :   dealerDraws(void)
Arguments       :   oneCard[](cards), cardsDrawn(int&), dealerValue(int&), playerValue(int), playerValue2(int),
                    dealerValue2(int&), dealerAceDrawn(int&), currentCards(int&), dealerCards[](int), 
                    maxDealerCards(int), NumOfDealerCards(int), playerCards[](int), maxPlayerCards(int),
                    NumOfPlayerCards(int), dealerFinalTotal(int&), playerFinalTotal(int&)
Returns         :   None
Precondition    :   The newDeck(void), playGame(void), drawCards(void), and limitCheck(void) function must all have
                    been called prior to calling this function. The parameters must exist and the precondtions for the
                    required functions to be called must have been met.
Postcondition   :   This function will work like the drawCards(void) function except that the dealer will be drawing
                    cards instead of the player. The dealer will draw cards until he beats the player or is over 17
                    in value. The playerTotalValue and dealerTotalValue will also have been calculated. The counters
                    will increase accordingly.
Description     :   This function draws cards for the dealer until he beats the user and is atleast at a value of 17.
                    This function also finds the playerTotalValue and the dealerTotalValue by comparing both values
                    for the player(playerValue and playerValue2) and the same for the dealer. The counters will
                    increase accordingly.
***********************************************************************************************************************/
void dealerDraws(cards oneCard[], int& cardsDrawn,int&dealerValue , int playerValue, int playerValue2, int& dealerValue2, int& dealerAceDrawn, int& currentCards, int dealerCards[], 
                int maxDealerCards, int NumOfDealerCards, int playerCards[], int maxPlayerCards, int NumOfPlayerCards, int& dealerFinalTotal, int& playerFinalTotal);

/***********************************************************************************************************************
Name            :   whoWins(void)
Arguments       :   playerFinalTotal(int), dealerFinalTotal(int), money(int&), betAmount(int)
Returns         :   None
Precondition    :   The newDeck(void), playGame(void), drawCards(void), limitCheck(void) and dealerDraws(void) functions
                    must have been called prior to calling this function. The parameters must exist and the preconditions
                    for the required functions to be called must have been met.
Postcondition   :   The winner will be determined. The money will be changed accordingly.
Description     :   This function compares the final totals for the dealer and the player and determines the winner.
                    Then the money will be changed accordingly.
***********************************************************************************************************************/        
void whoWins(int playerFinalTotal, int dealerFinalTotal, int& money, int betAmount, int& NumOfDealerCards, int& NumOfPlayerCards, int cardsDrawn);

/***********************************************************************************************************************
Name            :   loadGameData(void)
Arguments       :   money(int&)
Returns         :   None
Precondition    :   None
Postcondition   :   The money will be changed to the amount on the save file.
Description     :   This gets the money from an existing save file. Then it sets the money on that file to 0 to prevent
                    abusing of the save system.
***********************************************************************************************************************/
void loadGameData(int &money);

/***********************************************************************************************************************
Name            :   saveGame(void)
Arguments       :   money(int)
Returns         :   None
Precondition    :   The game must end.
Postcondition   :   The value of money(int) will be written to an existing file.
Description     :   This function will save the current amount of money to an existing file.
***********************************************************************************************************************/
void saveGame(int money);


int main ()
{
        char userInput = 'N';
        int cardsDrawn = 0;
        int money = 10;
        int NumOfPlayerCards = 0;
        int NumOfDealerCards = 0;
        int maxDealerCards = 15;
        int maxPlayerCards = 15;
        int playerCards[maxPlayerCards];
        int dealerCards[maxDealerCards];
        
        
        
        //creates 52 objects of cards
        cards oneCard[amountOfCards];
      
     do   
     {   
        //prints menu
        menu();
        
        //the user enters what option they want to do
        cin >> userInput;
       
        //switch statement that runs the case based on what number the user enters
        switch(userInput)
        {
            
            //case 1 should create the new deck
            case '1':
                newDeck(oneCard);
                //resets the amount of cardsDrawn to zero so it would be like making an a new deck
                cardsDrawn = 0;
                break;
                
            //case 2 should shuffle the card objects
            case '2':
                shuffle(oneCard, amountOfCards, cardsDrawn);
                break;
                
            //case 3 should display all remaining cards objects in the deck
            case '3':
                displayDeck(oneCard, amountOfCards, cardsDrawn);
                break;
                
            //case 4 should start the game of blackjack
            case '4':
                playGame(oneCard, cardsDrawn, money, dealerCards, maxDealerCards, NumOfDealerCards, playerCards, maxPlayerCards, NumOfPlayerCards);
                break;
            //Display Remaining Money
            case '5':
                cout << "You have " << money << " dollars remaining\n";
                break;
            
            case '6':
                loadGameData(money);
                break;
            //reprints the menu and user input option since the user did not enter a correct
            default:
                break;
        }
        
            
    }while(userInput != '7');


    cout << "Do you want to save your money? Y or N. " << endl;
    cin >> userInput;
    
    if(userInput == 'Y' || userInput == 'y')
    {
        saveGame(money);
    }
    

    return 0;
}





//This function will print out the menu for the user to see when called
void menu()
{
    cout << "1. New Deck\n";
    cout << "2. Shuffle cards\n";
    cout << "3. Display all cards remaining in the deck\n";
    cout << "4. Play BlackJack\n";
    cout << "5. Display Remaining Money\n";
    cout << "6. Contine from saved game\n";
    cout << "7. Close Program\n";
    
}


//displays all cards
void displayDeck(cards oneCard[], int amountOfCards, int cardsDrawn)
{
    for(int j = 0; j < 13; j++)
    {
        for(int k = 0; k < 4 && cardsDrawn < amountOfCards; k++ )
        {
            oneCard[cardsDrawn].printCardNoEndl();
            cout << "\t\t";
            cardsDrawn++;
        }
        cout << endl;
    }
}


//creates new deck
void newDeck(cards oneCard[])
{

    
    //starting array element value
    int objectNumber = 0;
    
    //populates each array element 
    for(int i = 0; i < 13; i++)
    {
        
        for(int k = 0; k < 4; k++)
        {
            //sets one object of cards to the value of the temp card, so whatever values of face and suit that the 
            //temp files had the oneCard array element will have too.
            cards tempCards(i,k);
            oneCard[objectNumber] = tempCards;
           
           //adds 1 to the object number so that the next element of the array can also have values.
           if (objectNumber < amountOfCards)
           {
            objectNumber++;
            
           }
            
        }
        
    }
    cout << "\n";
}





//shufffles deck
void shuffle(cards oneCard[], int amountOfCards, int cardsDrawn)
{
    const int NUM_OF_SHUFFLE = 100;
    int randNum1 = 0;
    int randNum2 = 0;
    srand(time(0));



    
    for(int i = 0; i < NUM_OF_SHUFFLE; i++)
    {
        
        randNum1 = rand() % 52;
        randNum1 += cardsDrawn;
        randNum2 = (rand() % 52);
        randNum2 += cardsDrawn;

        //checks so that the element cannot be more than 51, so segmentation error does not occur
         while (randNum1 > 51)
         {
            randNum1 = rand() % 52;
            randNum1 += cardsDrawn;
         }
         //checks so that the element of the oneCard object cannot be more than 51, so segmentation error does not occur
         while(randNum2 > 51)
         {
              randNum2 = (rand() % 52);
              randNum2 += cardsDrawn;
         }
       
     
    
    //copies the face, suit, and value from object Onecard into temp card    
    cards tempCard(oneCard[randNum1]);
    oneCard[randNum1] = oneCard[randNum2];
    oneCard[randNum2] = tempCard;
    }
    
    cout << "Deck has been shuffled" << endl;
}


//plays game
void playGame(cards oneCard[], int& cardsDrawn, int& money, int dealerCards[], int maxDealerCards, int& NumOfDealerCards, int playerCards[], int maxPlayerCards, int& NumOfPlayerCards)
{
    int dealerValue = 0;
    int playerValue = 0;
    int playerValue2 = 0;
    int dealerValue2= 0;
    int betAmount = 0;
    int currentCards = 0;
    int playerFinalTotal;
    int dealerFinalTotal;
    int playerAceDrawn = 0;
    int dealerAceDrawn = 0;
    char userInput;

    
    //Only play game if cardsDrawn is less than or equal to 51
    if(cardsDrawn <= 51)
    {
    
        //User places bet
        do
        {
            cout << "You have " << money << " dollars. How much would you like to bet?: ";
            cin >> betAmount;
            
            //if the user is betting more than he has this will print out
            if(betAmount > money)
            {
                cout << "You do not have that much money\n";
            }
            
        }while(betAmount > money);
        
        //Initial Card drawing to start the game      
        currentCards = cardsDrawn;  
        
        
            //prints out the first two cards for the dealer when the game starts 
        while(currentCards <= cardsDrawn + 1 && cardsDrawn <= 51)
        {
            //adds the first and second value to the first and second dealer value amount
            dealerValue += oneCard[currentCards].getValue1();
            dealerValue2 += oneCard[currentCards].getValue2(); 
            
        
            //Store the value of current cards into an Array for dealerCards to be used later
            //when displaying the cards drawn while playing the game
            //NumOfDealerCards initial amount is 0
            dealerCards[NumOfDealerCards] = currentCards;
        
            //checks if user draws an Ace
            if(oneCard[currentCards].getValue1() == 1)
            {
                //if the user draws an ace it will add one to the AceDrawn counter
                dealerAceDrawn++;
            }
        
            //This will display the first 2 cards drawn by the dealer. (First card is ???????????)
            if(currentCards == cardsDrawn)
            {
                cout << "Dealer\t:\t";
                cout << "?? of ???????\n";
            }
            //prints the second card out
            else
            {
                cout << "\t" << "\t";
                oneCard[currentCards].printCard();
                cout << endl;
            }
            
            //Increase currentCards value to move to next card in the deck
            currentCards++;
            
            //Increase the value of NumOfDealerCards. This moves to the next slot in the array.
            NumOfDealerCards++;

        }
    
        //sets the new amount of cardsDrawn for the player
        cardsDrawn = currentCards;
        
         //gets the values of the player cards
         while(currentCards < cardsDrawn + 2 && cardsDrawn <= 51)
         {
            playerValue += oneCard[currentCards].getValue1();
            playerValue2 += oneCard[currentCards].getValue2();
            
            //Same logic as above but for player instead of dealer
            playerCards[NumOfPlayerCards] = currentCards;
            
            //This will print the first two cards drawn by the user
            if(currentCards < cardsDrawn + 1)
            {
                cout << "Player";  
                cout << "\t:" << "\t";
                oneCard[currentCards].printCard();
            }
            else
            {
                cout << "\t" << "\t";
                oneCard[currentCards].printCard();
                cout << endl;
            }
            
            //checks if player has drawn an ACE 
            if(oneCard[currentCards].getValue1() == 1)
            {
            playerAceDrawn++;
            }
            
            //will subtract 10 from playValue two if there are two aces or more
            while(playerAceDrawn > 1)
            {
                playerValue2 -= 10;
                playerAceDrawn--;
            }
            
            //adds one more cards to current cards counter
            currentCards++;
            
            //Same logic as above but for player
            NumOfPlayerCards++;
        }
         
        if(cardsDrawn <= 51)
            {
                cout << "Your Total: " << playerValue << endl;
                if(playerAceDrawn > 0)
                {
                    cout << "Total(Ace = 11): " << playerValue2 << endl << endl;
                }
            }
            
            cardsDrawn = currentCards;
         
         
         //This part has to be a Do-While Loop. We have to ask for userInput before being able to run the loop.
         //A while-loop won't work because we would have to initialize userInput to something and we can only
         //initialize it to userInput = 'Y'. But then this will automatically draw a card for the user
         //without the user selecting to do so.
        do
        {
            //Only allow game if the cardsDrawn <= 51 (If there are enough cards to play the game)
            if(cardsDrawn <= 51)
            {
                   //Continue Drawing Cards
                    cout << "Draw another card?(Y/N): ";
                    cin >> userInput;
                
                    switch(userInput)
                {
                    case 'y':
                        userInput = 'Y';
                        
                    case 'Y':
                        //Draw a card and check if it busted or not
                        drawCards(oneCard, cardsDrawn, dealerValue, playerValue, playerValue2, dealerValue2, playerAceDrawn, dealerAceDrawn, currentCards, 
                                    dealerCards, maxDealerCards, NumOfDealerCards, playerCards, maxPlayerCards, NumOfPlayerCards);
                        limitCheck(playerValue, playerValue2, userInput, money ,betAmount, NumOfDealerCards, NumOfPlayerCards);
                    break;
                        
                    case 'n':
                    case 'N':
                        //After user chooses to stand, the dealer will begin drawing cards. N
                        dealerDraws(oneCard, cardsDrawn, dealerValue, playerValue, playerValue2, dealerValue2, dealerAceDrawn, currentCards, 
                                    dealerCards, maxDealerCards, NumOfDealerCards, playerCards, maxPlayerCards, NumOfPlayerCards, dealerFinalTotal, playerFinalTotal);
                        whoWins(playerFinalTotal, dealerFinalTotal,money, betAmount, NumOfDealerCards, NumOfPlayerCards, cardsDrawn);
                    break;
                    
                    default:
                        cout << "Invalid Input\n";
                        userInput = 'Y';
                    break;
                    
                }
            }
            else
            {
                cout << "There are no more cards to be drawn. Please create a new deck and shuffle to play another game.\n";
                userInput == 'N';
            }
            
        }while(userInput == 'Y' && playerValue <= 21);
    }
    else
    {
        cout << "There are no more cards to be drawn. Please create a new deck and shuffle to play another game.\n";
    }
    
}


void drawCards(cards oneCard[], int& cardsDrawn,int&dealerValue , int& playerValue, int& playerValue2, int& dealerValue2,  int& playerAceDrawn, int dealerAceDrawn,
                int&  currentCards, int dealerCards[], int maxDealerCards, int& NumOfDealerCards, int playerCards[], int maxPlayerCards, int& NumOfPlayerCards)
{
    //Draw card and add to the total
    currentCards = cardsDrawn;
    playerValue += oneCard[currentCards].getValue1();
    playerValue2 += oneCard[currentCards].getValue2();
    
    //Check if the dealer drew an Ace
    if(oneCard[currentCards].getValue1() == 1)
        {
            playerAceDrawn++;
        }
        
    //If player drew more than 1 ace, it will account for it.    
    while(playerAceDrawn > 1)
    {
        playerValue2 -= 10;
        playerAceDrawn--;
    }
    

    
    
    //Display Dealer Cards
    cout << "Dealer\t:\t";
    cout << "?? of ???????\n";
    for(int i = 1; i < NumOfDealerCards; i++)
    {
        int temp = dealerCards[i];
        cout << "\t" << "\t";
        oneCard[temp].printCard();
    }
    cout << "\n";
    
    
    //Display Player Cards
    cout << "Player\t:\t";
    for(int i = 0; i < NumOfPlayerCards; i++)
    {
        int temp = playerCards[i];
        oneCard[temp].printCard();
        cout << "\t" << "\t";
    }
    cout << "\n";
    
    //Recalculate and Display total and cards drawn by user
    cout << "Player Takes Card: ";
    oneCard[currentCards].printCard();
    cout << endl;
    cout << "Your Total: " << playerValue << endl;
    
    
    //Also display the second value if ace was drawn and second value is not over 21
    if(playerAceDrawn > 0 && playerValue2 <= 21)
    {
        cout << "Total(Ace = 11): " << playerValue2 << endl << endl;
    }
    
    if(currentCards < 51)
    {
        //same logic as used in the playGame(...) function
        playerCards[NumOfPlayerCards] = currentCards;
        NumOfPlayerCards++;
        currentCards++;
        cardsDrawn = currentCards;
    }
    
}

void limitCheck(int playerValue, int playerValue2, char& userInput, int& money, int betAmount, int& NumOfDealerCards, int& NumOfPlayerCards)
{
    if (playerValue > 21)
    {
        if (playerValue2 > 21)
        {
            cout << "Player Busted" << endl;
            cout << "You lose pal" << endl << endl;
            userInput = 'N';
            money = money - betAmount;
            
            //Reset these counters for the next game
            NumOfDealerCards = 0;
            NumOfPlayerCards = 0;
            
            //Boot if the user has no money left
            if(money == 0)
            {
                cout << "You are out of money. Get out of here\n";
                exit(1);
            }
        }
        
    }
    
    
}

void dealerDraws(cards oneCard[], int& cardsDrawn,int&dealerValue , int playerValue, int playerValue2, int& dealerValue2, int& dealerAceDrawn, int& currentCards, int dealerCards[],
                int maxDealerCards, int NumOfDealerCards, int playerCards[], int maxPlayerCards, int NumOfPlayerCards , int& dealerFinalTotal, int& playerFinalTotal)
{
    
    //Find playerFinalTotal
    if(playerValue2 >= playerValue && playerValue2 <= 21)
    {
        playerFinalTotal = playerValue2;
    }
    else
    {
        playerFinalTotal = playerValue;
    }
    
    //Display Dealer's Hand
    cout << "Dealer\t:\t";
    for(int i = 0; i < NumOfDealerCards; i++)
    {
        int temp = dealerCards[i];
        oneCard[temp].printCard();
        cout << "\t" << "\t";
    }
    cout << "\n";
    
    //Display Player's Hand
    cout << "Player\t:\t";
    for(int i = 0; i < NumOfPlayerCards; i++)
    {
        int temp = playerCards[i];
        oneCard[temp].printCard();
        cout << "\t" << "\t";
    }
    cout << "\n";
    
    
        //Dealer Draws Card. Do this if the dealer has an Ace
        if(dealerAceDrawn > 0)
        {
            currentCards = cardsDrawn;
            
            while(dealerValue < 17 && dealerValue2 < 17 && currentCards <= 51)
            {
                //Dealer will draw a card. The logic is the same as for the player.
                dealerValue += oneCard[currentCards].getValue1();
                dealerValue2 += oneCard[currentCards].getValue2();
                dealerCards[NumOfDealerCards] = currentCards;
                
                if(oneCard[currentCards].getValue1() == 1)
                {
                    dealerAceDrawn++;
                }
                
                //Display Cards as dealer draws
                cout << "Dealer takes a card: ";
                oneCard[currentCards].printCard();
                
                currentCards++;
                NumOfDealerCards++;
                
            }
            while(dealerValue < 17 && dealerValue2 > 21 && currentCards <= 51)
            {
                //Dealer will draw a card. The logic is the same as for the player.
                dealerValue += oneCard[currentCards].getValue1();
                dealerValue2 += oneCard[currentCards].getValue2();
                dealerCards[NumOfDealerCards] = currentCards; 
                
                if(oneCard[currentCards].getValue1() == 1)
                {
                    dealerAceDrawn++;
                }

                //Display Cards as dealer draws
                cout << "Dealer takes a card: ";
                oneCard[currentCards].printCard();
            
                currentCards++;
                NumOfDealerCards++;
            }
            while(dealerValue < 17 && dealerValue2 >= 17 && dealerValue2 <= 21 && dealerValue2 < playerFinalTotal && currentCards <= 51)
            {
                //Dealer will draw a card. The logic is the same as for the player.
                dealerValue += oneCard[currentCards].getValue1();
                dealerValue2 += oneCard[currentCards].getValue2();
                dealerCards[NumOfDealerCards] = currentCards;
                
                if(oneCard[currentCards].getValue1() == 1)
                {
                    dealerAceDrawn++;
                }

                //Display Cards as dealer draws
                cout << "Dealer takes a card: ";
                oneCard[currentCards].printCard();
            
                currentCards++;
                NumOfDealerCards++;
            }
        }
        //Do this if the dealer does not have an Ace
        else
        {
            currentCards = cardsDrawn;
            
            while(dealerValue < 17 && currentCards <= 51)
            {
                //Dealer will draw a card. The logic is the same as for the player.
                dealerValue += oneCard[currentCards].getValue1();
                dealerValue2 += oneCard[currentCards].getValue2();
                dealerCards[NumOfDealerCards] = currentCards;
                
                if(oneCard[currentCards].getValue1() == 1)
                {
                    dealerAceDrawn++;
                }

                //Display Cards as dealer draws
                cout << "Dealer takes a card: ";
                oneCard[currentCards].printCard();
            
                currentCards++;
                NumOfDealerCards++;
            }
            while(dealerValue > 17 && currentCards <= 51 && dealerValue < playerValue2)
            {
                //Dealer will draw a card. The logic is the same as for the player.
                dealerValue += oneCard[currentCards].getValue1();
                dealerValue2 += oneCard[currentCards].getValue2();
                dealerCards[NumOfDealerCards] = currentCards;
                
                if(oneCard[currentCards].getValue1() == 1)
                {
                    dealerAceDrawn++;
                }

                //Display Cards as dealer draws
                cout << "Dealer takes a card: ";
                oneCard[currentCards].printCard();
            
                currentCards++;
                NumOfDealerCards++;
            }
        }
        
    //Sets the new amount of cardsDrawn
    cardsDrawn = currentCards;
    
    if(dealerAceDrawn > 0)
    {
        for(int i = 1; i < dealerAceDrawn; i++)
        {
            dealerValue2 - 10;
        }
    }
    
    //Find dealerFinalTotal
    if(dealerValue2 >= dealerValue && dealerValue2 <= 21)
    {
        dealerFinalTotal = dealerValue2;
    }
    else if(dealerValue <= 21)
    {
        dealerFinalTotal = dealerValue;
    }
    else if(dealerValue > 21 && dealerValue2 > 21)
    {
        dealerFinalTotal = 0;
    }
    
    //Display Dealer Total
    if(dealerFinalTotal == 0 && cardsDrawn <= 51)
    {
        cout << "Dealer Total: Bust" << endl;
    }
    else
    {
        cout << "Dealer Total: " << dealerFinalTotal << endl;

    }
    
    if(cardsDrawn > 51)
    {
        cout << "There are no more cards to be drawn. Please create a new deck and shuffle to play another game.\n";
    }
}

//checks who wins at the end of all the drawing from both the dealer and the player
void whoWins(int playerFinalTotal, int dealerFinalTotal, int& money, int betAmount, int& NumOfDealerCards, int& NumOfPlayerCards, int cardsDrawn)
{
    if(cardsDrawn <= 51)
    {
        if(playerFinalTotal == dealerFinalTotal)
        {
            cout << "It's a tie" << endl;
            cout << "You win pal" << endl << endl;
            money = money + betAmount;
    
        }
        else if(playerFinalTotal > dealerFinalTotal)
        {
            cout << "You win pal" << endl << endl;
            money = money + betAmount;
        }
        
        else if(playerFinalTotal < dealerFinalTotal)
        {
            cout << "You lose pal" << endl << endl;
            money = money - betAmount;

        }
        
        //Reset each person's card counters
        NumOfDealerCards = 0;
        NumOfPlayerCards = 0;
        
        //Boot if user runs out of money
        if(money == 0)
        {
            cout << "You are out of money. Get out of here\n";
            exit(1);
        }
    }
}

//loads the game 
void loadGameData(int &money)
{
    if(money != 0)
    {
        int savedData = 0;
        ifstream inFile;
        ofstream outFile;
        
        inFile.open("gamelog.txt");
        if(inFile.fail())
        {
            cout << "error opening file\n";
                exit(1);
        }
        
        inFile >> savedData;
        money = savedData;
        
        inFile.close();
        
        outFile.open("gamelog.txt");
        if(outFile.fail())
        {
            cout << "error opening file\n";
            exit(1);        
        }
        outFile << 0;
        outFile.close();
    }
    else
    {
        cout << "Error: Already using a saved game\n";
    }
    
    
}


// saves the amount of money the user has
void saveGame(int money)
{
    ofstream outFile;
    
    outFile.open("gamelog.txt");
    if(outFile.fail())
    {
        cout << "error opening file";
        exit(1);        
    }
    
    outFile << money;
    outFile.close();
    
}