#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase() //empty constructor because private member variables have their own constructor
{
}

bool UserDatabase::load(const string& filename) //load in user.txt
{
    ifstream userFile(filename);
    if(!userFile)
    {
        return false;
    }
    string name;
    while(getline(userFile, name)) //first line is name
    {
        string email;
        getline(userFile, email); //second is email
        int numMovies;
        userFile >> numMovies; //third is numMovies watched
        userFile.ignore(10000, '\n');
        vector<string> watch_hist;
        string movieID;
        for(int i = 0; i< numMovies; i++) //iterate through lines putting movieIDs into a watch history vector
        {
            getline(userFile,movieID);
            watch_hist.push_back(movieID);
        }
        User* newUser = new User(name, email, watch_hist);
        m_userTree.insert(email, *newUser); //create a userTree
        string empty;
        getline(userFile, empty);
        delete newUser;
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const //search tree for email and return the user
{
    TreeMultimap<string,User>::Iterator it = m_userTree.find(email);
    if(it.is_valid())
    {
        return &(it.get_value());
        
    }
    else
        return nullptr;
}
