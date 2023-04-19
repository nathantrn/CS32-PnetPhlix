#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//constructor
Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    m_id = id;
    m_title = title;
    m_release_year = release_year;
    m_rating = rating;
    m_directors = directors;
    m_actors = actors;
    m_genres = genres;
    
}
//return id
string Movie::get_id() const
{
    return m_id;
}
//return title
string Movie::get_title() const
{
    return m_title;
}
//return release year
string Movie::get_release_year() const
{
    return m_release_year;
}
//return rating
float Movie::get_rating() const
{
    return m_rating;
}
//return vector of directors
vector<string> Movie::get_directors() const
{
    return m_directors;
}
//return vector of actors
vector<string> Movie::get_actors() const
{
    return m_actors;
}
//return vector of genres
vector<string> Movie::get_genres() const
{
    return m_genres;
}
