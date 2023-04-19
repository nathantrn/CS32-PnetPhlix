#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

MovieDatabase::MovieDatabase() //constructor not needed as private member variables are constructored by their own constructors
{
}

bool MovieDatabase::load(const string& filename) //load in movie.txt file
{
    ifstream file(filename);
    if(!file)
    {
        return false;
    }
    string movieID;
    while(getline(file, movieID)) //first line is movieID
    {
        string name;
        float rating;
        string releaseYear;
        vector<string> directors;
        vector<string> actors;
        vector<string> genres;
        getline(file, name); //second line is movie name
        getline(file, releaseYear); //3rd line is movie release year
        string dirLine;
        getline(file, dirLine); //4th line is directors
        string dirName = "";
        
        for(int i =0; i < dirLine.size() ; i++) //must go into line of directors and determine how to seperate directors name from the entire line and add them to a vector of directors
        {
            if(dirLine[i] == ',') //directors seperated by comma
            {
                directors.push_back(dirName); //puts names into vector
                dirName = "";
            }
            else
            {
                dirName.push_back(tolower(dirLine[i])); //builds the name
            }
        }
        directors.push_back(dirName); //gets last name after last comma
        string actLine;
        getline(file, actLine);
        string actorName = "";
        for(int i =0; i < actLine.size() ; i++) //do same for actors
        {
            if(actLine[i] == ',')
            {
                
                actors.push_back(actorName);
                actorName = "";
            }
            else
            {
                actorName.push_back(tolower(actLine[i]));
            }
        }
        actors.push_back(actorName);
        string genLine;
        getline(file, genLine);
        string genName = "";
        for(int i =0; i < genLine.size() ; i++) //do same for genres
        {
            if(genLine[i] == ',')
            {
                genres.push_back(genName);
                genName = "";
            }
            else
            {
                genName.push_back(tolower(genLine[i]));
            }
        }
        genres.push_back(genName);
        file >> rating; //get rating and ignore
        file.ignore(10000, '\n');
        Movie* newMovie = new Movie(movieID, name, releaseYear, directors, actors, genres, rating);
        m_movieIDTree.insert(movieID, *newMovie); //insert movieID as key value and Movie* as datavalue
        for(int i = 0; i < directors.size(); i++) //creates a tree of directors
        {
            m_dirTree.insert(directors[i], *newMovie);
        }
        for(int i = 0; i < actors.size(); i++) //tree of actors
        {
            m_actTree.insert(actors[i], *newMovie);
        }
        for(int i = 0; i < genres.size(); i++) //tree of genres
        {
            m_genTree.insert(genres[i], *newMovie);
        }
        delete newMovie;
        string empty;
        getline(file, empty);
    }
    return true;
}
//get a movie* from their id
Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string,Movie>::Iterator it = m_movieIDTree.find(id); //finds movie in tree and returns its data value
    if(it.is_valid())
    {
        return &(it.get_value());
    }
    else
        return nullptr;
}
//returns a vector of movie* with the same directors
vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    TreeMultimap<string,Movie>::Iterator it = m_dirTree.find(director); //finds director in tree and iterates through its movie vector
    vector<Movie*> dir_vec;
    while(it.is_valid())
    {
        dir_vec.push_back(&(it.get_value()));
        it.advance();
    }
    return dir_vec;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<string,Movie>::Iterator it = m_actTree.find(actor); //finds actor in tree and iterates through its movie vector
    vector<Movie*> act_vec;
    while(it.is_valid())
    {
        act_vec.push_back(&(it.get_value()));
        it.advance();
    }
    return act_vec;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<string,Movie>::Iterator it = m_genTree.find(genre); //finds genre in tree and iterates through its movie vector
    vector<Movie*> gen_vec;
    while(it.is_valid())
    {
        gen_vec.push_back(&(it.get_value()));
        it.advance();
    }
    return gen_vec;
}
