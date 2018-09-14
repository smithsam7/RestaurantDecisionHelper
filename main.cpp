/*
 Sam Smith, sec 2, smittysport7@gmail.com
 Purpose: 
 Inputs:
 Outputs:
 Test Cases: 
    Test 1:
        Input:  
        Output:
    Test 2:
        Input:
        Output:
    Test 3:
        Input:
        Output:
*/

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>


using namespace std;

const int NOT_FOUND = -1;

void PrintMenu()
{
    cout << "0 - Quit the tournament" << endl << endl;
    cout << "1 - Display all restaurants" << endl << endl;
    cout << "2 - Add a restaurant" << endl << endl;
    cout << "3 - Remove a restaurant" << endl << endl;
    cout << "4 - Shuffle the vector" << endl << endl;
    cout << "5 - Load a File" << endl << endl;
    cout << "6 - Begin the tournament" << endl << endl;
    cout << "Please pick one: ";
}

bool new_list_from_file(vector<string>& restaurants)
{
    string file_name;
    string restaurant_name;
    ifstream in_file;
    cout << "Enter file name: ";
    cin >> file_name;
    cout << endl;
    in_file.open("/Users/Samuel/Documents/BYU/Winter '17/CS 142/CS Labs/Lab 7 Restaurants/Lab 7 Restaurants/" + file_name);
    if(in_file.fail()){
        cout << "File does not exist" << endl;
        return false;
    }
    restaurants.clear();
    while(!in_file.eof())
    {
        getline(in_file, restaurant_name);
        restaurants.push_back(restaurant_name);
    }
    in_file.close();
    cout << "Opening " << file_name;
    return true;
}

void StartingRestaurantNames(vector<string>& restaurantNames)
{
    restaurantNames.clear();
    restaurantNames.push_back("Cafe Rio");
    restaurantNames.push_back("Zupas");
    restaurantNames.push_back("Sushi Burrito");
    restaurantNames.push_back("J Dawgs");
    restaurantNames.push_back("Cup Bop");
    restaurantNames.push_back("JCWs");
    restaurantNames.push_back("Wendys");
    restaurantNames.push_back("Jamba Juice");
}

void DisplayRestaurants(const vector<string>& restraurants)
{
    for(int i = 0; i < restraurants.size(); i++)
    {
        cout << restraurants[i];
        if(i < restraurants.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl << endl;
}

int FindRestaurant(const vector<string>& restaurants, string restaurantsearch)
{
    for(int i = 0; i < restaurants.size(); i++)
    {
        if(restaurants[i] == restaurantsearch)
        {
            return i;
        }
    }
    return NOT_FOUND;
}

bool AddRestaurants(vector<string>& restaurants, string new_restaurant)
{
    int restaurantFindings = FindRestaurant(restaurants, new_restaurant);
    if(restaurantFindings == NOT_FOUND)
    {
        restaurants.push_back(new_restaurant);
        return true;
    }
    return false;
}

bool RemoveRestuarant(vector<string>& restaurants, string wanted_restaurant)
{
    int found_at = FindRestaurant(restaurants, wanted_restaurant);
    if(found_at == NOT_FOUND)
    {
        return false;
    }
    restaurants.erase(restaurants.begin() + found_at);
    return true;
}

void ShuffleRestaurants(vector<string>& restaurants)
{
    string temp_position;
    for(int i = 0; i < restaurants.size(); i++)
    {
    int rand1 = rand() % restaurants.size();
    temp_position = restaurants[rand1];
    restaurants[rand1] = restaurants[i];
    restaurants[i] = temp_position;
    }
}

bool CheckPowerOfTwo(vector<string> restaurants)
{
    double temp_power = 0;
    int check_power = 0;
    temp_power = log2(restaurants.size());
    check_power = temp_power;
    if(temp_power != (double)check_power)
    {
        cout << "Invalid number of restaurants" << endl << endl;
        return false;
    }
    return true;
}

void PrintMatchInfo(vector<string> restaurants, int total_rounds, int current_round, int total_matches, int current_match)
{
    cout << "Match " << current_match << "/" << total_matches;
    cout << ", Round " << current_round << "/" << total_rounds << "---";
    
}

void Round(vector<string> restaurants, vector<string>& winners, int total_rounds, int current_round)
{
    string match_loser;
    int match_winner = 0;
    int current_match = 1;
    const int HALF_RESTAURANTS = 2;
    int total_matches = 0;
    total_matches = restaurants.size() / HALF_RESTAURANTS;

    
    for(int i = 0; i < restaurants.size(); i += 2)
    {
        do {
            PrintMatchInfo(restaurants, total_rounds, current_round, total_matches, current_match);
            cout << " 1: " << restaurants[i] << " or 2: " << restaurants[i + 1] << "? ";
            cin >> match_winner;
            if(match_winner < 1 || match_winner > 2)
            {
                cout << "Invalid response(" << match_winner << ")" << endl;
                continue;
            }
            if(match_winner == 1)
            {
                winners.push_back(restaurants[i]);
            }
            else if(match_winner == 2)
            {
                winners.push_back(restaurants[i + 1]);
            }
        } while(match_winner < 1 || match_winner > 2);
        current_match++;
    }
}

void RunTournament(vector<string>& restaurant_list)
{
    vector<string> winner_list;
    int round_total = 0;
    round_total = log2(restaurant_list.size());
    for(int round = 1; round <= round_total; round++)
    {
        Round(restaurant_list, winner_list, round_total, round);
        restaurant_list.resize(winner_list.size());
        for(int i = 0; i < restaurant_list.size(); i++)
        {
            restaurant_list[i] = winner_list[i];
        }
        winner_list.clear();
    }
    cout << restaurant_list[0] << " is the Winner!" << endl;
    
    
    
}




int main()
{
    const int EXIT_OPTION = 0;
    const int DISPLAY_OPTION = 1;
    const int ADD_RESTAURANT = 2;
    const int REMOVE_RESTAURANT = 3;
    const int SHUFFLE_RESTAURANTS = 4;
    const int LOAD_FILE = 5;
    const int BEGIN_TOURNAMENT = 6;
    int optionChoice = 0;
    vector<string> restaurantNames;
    string restaurantName;
    srand(time(0));


    StartingRestaurantNames(restaurantNames);
    
    do {
        PrintMenu();
        cin >> optionChoice;
        cin.ignore(UCHAR_MAX, '\n');
        cout << endl;
        if(optionChoice == DISPLAY_OPTION)
        {
            DisplayRestaurants(restaurantNames);
        }
        else if(optionChoice == ADD_RESTAURANT)
        {
            cout << "Please enter Restaurant Name: ";
            getline(cin, restaurantName);
            cout << endl;
            if(AddRestaurants(restaurantNames, restaurantName))
            {
                cout << "Restaurant was added" << endl << endl;
            }
            else
            {
                cout << "Restaurant already exists" << endl << endl;
            }
            
        }
        else if(optionChoice == REMOVE_RESTAURANT)
        {
            cout << "Please enter Restaurant Name: ";
            getline(cin, restaurantName);
            cout << endl;
            if(RemoveRestuarant(restaurantNames, restaurantName))
            {
                cout << "Restaurant was removed" << endl << endl;
            }
            else
            {
                cout << "Restaurant not found" << endl << endl;
            }
        }
        else if(optionChoice == SHUFFLE_RESTAURANTS)
        {
            ShuffleRestaurants(restaurantNames);
            cout << "Restaurants are shuffled" << endl << endl;
        }
        else if(optionChoice == LOAD_FILE)
        {
            new_list_from_file(restaurantNames);
            cout << endl;
        }
        else if(optionChoice == BEGIN_TOURNAMENT)
        {
            if(CheckPowerOfTwo(restaurantNames) != true)
            {
                continue;
            }
            RunTournament(restaurantNames);
            break;
        }
        
    }while(optionChoice != EXIT_OPTION);
    
    
    
    return 0;
}
