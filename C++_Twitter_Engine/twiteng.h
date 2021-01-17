#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <stack>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "user.h"
#include "datetime.h"
#include "tweet.h"
#include "util.h"
#include "tagdata.h"
#include "heap.h"
#include "hash.h"


class TwitEng
{
 public:
  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(  std::string& username,  DateTime& time, std::string& text);

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();
  

  void addUser(std::string& username);

  void parseHashtags( std::string& text, Tweet* myTweet);

  void parseMentions(std::string& text, Tweet* myTweet);

  void addFollowPair(std::string name_of_follower, std::string name_to_follow);

  void produceDatabase(std::ostream& mydat);

  bool mutuallyFollowing(User* u1, User* u2);

  User* findUser(std::string name);

  std::set<std::set<User*> > tarjan(std::ofstream& myfile);

  void strongconnect(User* v, int& index, std::stack<User*>& S);

  void trendingTweets(int n);

  bool validUser(std::string username);

  User* getCurrentUser();

  void setPassword(std::string newPass);

  void Logout();

  bool Login(std::string username, std::string password);

  /* You may add other member functions */
 private:
  /* Add any other data members or helper functions here  */

  std::map<std::string,User*> allUsers;
  std::map< std::string, std::set<Tweet*> > tweetTags; 
  std::map<std::string, std::set<Tweet*> > middleMentions;
  std::map<std::string, std::set<Tweet*> > startMentions;
  std::set<std::set<User*> > SCCset;
  Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> trending_;
  User* currUser_;
  std::map<std::string,unsigned long long> passCodes;


  //each tweet get its set of hashtags
  //may need to change parseHashtags to const as well

};


#endif
