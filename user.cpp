#include "user.h"
#include "tweet.h"
#include <string>
#include <set>
#include <list>
#include "msort.h"
using namespace std;


//xml class design
/* Forward Declaration to avoid #include dependencies */

//when you have two headers that reference each other, we would have a circular dependency. 
//so you don't #include in the .h but you do include in the .cpp 
//the forward declaration just says, there is such a class tweet ant tweet* exist.
//(we can't use the data members or anything though)

//is circular declaration my problem or something else?

class Tweet;
 
  /**
   * Constructor 
   */
  User::User(string name)
  {
    this->name_ = name;
     index = -1;
     lowlink = -1;
     onStack = false;
  }

  /**
   * Destructor
   */
  User::~User()
  {
    for(list<Tweet*>::iterator it = userTweets_.begin(); it != 
      userTweets_.end(); ++it)
    {
      delete *it;
    }
  }  

  /**
   * Gets the name of the user 
   * 
   * @return name of the user 
   */
  string User::name() const 
  {
    return name_;
  }
  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  set<User*> User::followers() const
  {
    // cout << this->name_ << " has these followers:   ";
    // for(set<User*>::iterator myit = followers_.begin(); myit !=
    //   followers_.end(); ++myit)
    // {
    //   cout << (*myit)->name_ << " ";
    // }
    // cout << endl;
    return followers_;
  }
  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  set<User*> User::following() const
  {
    // cout << this->name_ << " is following these:   ";
    // for(set<User*>::iterator myit = following_.begin(); myit !=
    //   following_.end(); ++myit)
    // {
    //   cout << (*myit)->name_ << " ";
    // }
    // cout << endl;
    return following_;
  }
  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  list<Tweet*> User::tweets() const //your own tweets
  {
    return userTweets_;
  }
  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  void User::addFollower(User* u)
  {
    followers_.insert(u); //cuz it's a set
  }
  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  void User::addFollowing(User* u)
  {
    following_.insert(u);
  }
  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void User::addTweet(Tweet* t)
  {
    
    userTweets_.push_back(t);
  }


  int User::getIndex()
  {
    return index;
  }

  int User::getLowLink()
  {
    return lowlink;
  }

  bool User::getOnStack()
  {
    return onStack;
  }

  void User::setIndex(int id)
  {
    index = id;
  }

  void User::setLowLink(int ll)
  {
    lowlink = ll;
  }

 void User::setOnStack(bool flag)
  {
    onStack = flag;
  }

  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  vector<Tweet*> User::getFeed() //all the tweets in your feed
  {

    //have to merge stuff before you can do bubble sort? since pulling from multiple userTweets_;
    //fix this syntax

    //need iterators to iterate over lists and sets?

    //add the users own tweets to the feed
    //CHECK: fix this function it's got bad syntax
    vector<Tweet*> myfeedvec;
    //cout << "Loading my tweets " << endl;
  for (list<Tweet*>::iterator it1 = userTweets_.begin(); it1 !=  userTweets_.end(); ++it1)
  {
   // cout << "it1: " << **it1 << endl;
  myfeedvec.push_back(*it1); //this work? tweet*s
  }

   ///add all the tweets of the people this user is following
  for(set<User*>::iterator it2 = following_.begin(); it2!= following_.end(); ++it2) 
 
  {
    list<Tweet*> tempFollowing_ = (*it2)->userTweets_; //tweets()??
    for(list<Tweet*>::iterator it3 = tempFollowing_.begin(); it3!= tempFollowing_.end(); ++it3)
    {
     // cout << "it3: " << **it3 << endl;

      myfeedvec.push_back((*it3));
    }
    
  }

    //sort the feed by time
    //sort(myfeedvec.begin(), myfeedvec.end(),TweetComp());
    TweetComp mycomp;
    mergeSort(myfeedvec,mycomp);

    return myfeedvec;

    //TweetComp comp;
    //mergeSort();


  
  }
  /* You may add other member functions */

  /* Add any other data members or helper functions here  */




