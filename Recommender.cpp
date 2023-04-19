#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
//#include <chrono>
#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

bool cmp(const pair<Movie*, int>& left, const pair<Movie*, int>& right) //cmp func compares pairs of movie* and compatibility scores to determine sort order
{
    if (left.second > right.second) //first compare compatibility score
    {
        return true;
    }
    else if (left.second < right.second)
    {
        return false;
    }
    if (left.first->get_rating() > right.first->get_rating()) //then compare rating
    {
        return true;
    }
    else if (left.first->get_rating() < right.first->get_rating())
    {
        return false;
    }
    if (left.first->get_title() < right.first->get_title()) //then compare alphabetical order
    {
        return true;
    }
    return false;
}

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_userDB = &user_database;
    m_movieDB = &movie_database;
}


vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
//    auto start = chrono::steady_clock::now();
    if(movie_count <= 0)
    {
        vector<MovieAndRank> empty; //if movie count zero or negative return empty vec
        return empty;
    }
    unordered_map<string, int> possible_Movies_to_Rec; //unordered map contains all possible movies to reccommend
    User* currUser = m_userDB->get_user_from_email(user_email); //get user's watch history
    vector<string> user_watchHIST;
    user_watchHIST = currUser->get_watch_history();
    for(int i = 0; i < user_watchHIST.size(); i++)
    {
        Movie* currMovie = m_movieDB->get_movie_from_id(user_watchHIST[i]);
        for(int j = 0; j < currMovie->get_directors().size(); j++) //from watch history all movies with the same directors that are contained in users watch history are added to the possible movies to reccommend and their compatibility scores are +20.
        {
            vector<Movie*> dirMovies;
            dirMovies = m_movieDB->get_movies_with_director(currMovie->get_directors()[j]);
            for(int k=0; k<dirMovies.size(); k++)
            {
                possible_Movies_to_Rec[dirMovies[k]->get_id()] += 20;
            }
        }
        for(int m=0;m < currMovie->get_actors().size(); m++) //all movies with same actors from user watch history are added and their compatibility scores are +30
        {
            vector<Movie*> actMovies;
            actMovies = m_movieDB->get_movies_with_actor(currMovie->get_actors()[m]);
            for(int n =0; n < actMovies.size(); n++)
            {
                possible_Movies_to_Rec[actMovies[n]->get_id()] += 30;
            }
        }
        for(int z=0;z < currMovie->get_genres().size(); z++) //all movies with same genre from user watch history are added and compatibility score are +1
        {
            vector<Movie*> genMovies;
            genMovies = m_movieDB->get_movies_with_genre(currMovie->get_genres()[z]);
            for(int x =0; x< genMovies.size(); x++)
            {
                possible_Movies_to_Rec[genMovies[x]->get_id()] += 1;
            }
        }
        
    }
    for(int y = 0; y < user_watchHIST.size(); y++) //delete movies from Possible moves to rec that has already been watched by user
    {
        possible_Movies_to_Rec.erase(user_watchHIST[y]);
    }
    
    vector<pair<Movie*, int>> MoviePairs; //a vector of pairs of Movie* and compatibility score
    unordered_map<string, int>::iterator c;
    for(c = possible_Movies_to_Rec.begin(); c!=possible_Movies_to_Rec.end();c++) //converts unordered map to vector of pairs
    {
        MoviePairs.push_back(make_pair(m_movieDB->get_movie_from_id(c->first),c->second));
    }
    

    sort(MoviePairs.begin(), MoviePairs.end(), cmp); //sorts vector of pairs using the cmp func
    

    vector<MovieAndRank> final;
    for (int u = 0; u < movie_count && u < MoviePairs.size(); u++) //final vector that is returned is converted from Movie* to just their IDs
        final.push_back(MovieAndRank(MoviePairs.at(u).first->get_id(), MoviePairs.at(u).second));
//    auto stop = chrono::steady_clock::now();
//    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
    return final;
    
}
