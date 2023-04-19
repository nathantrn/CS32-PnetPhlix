#include "User.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;
//constructor
User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    m_name = full_name;
    m_email = email;
    for(int i = 0; i< watch_history.size(); i++)
    {
        m_watch_hist.push_back(watch_history[i]);
    }
}
//return user name
string User::get_full_name() const
{
    return m_name;
}
//return email
string User::get_email() const
{
    return m_email;
}
//return vector of movieIDs that user has watched
vector<string> User::get_watch_history() const
{
    return  m_watch_hist;
}


