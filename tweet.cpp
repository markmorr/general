#include "tweet.h"
#include "datetime.h"
#include "user.h"
// #include "util.h"


using namespace std;


/* Forward declaration */
class User;

/**
 * Models a tweet and provide comparison and output operators
 */

  /**
   * Default constructor 
   */
  Tweet::Tweet() //do we do anything here?
  {
    text_ = "";

  }

  /**
   * Constructor 
   */
  
  Tweet::Tweet(User* user, const DateTime& time, const string& text)
  {
  	tweeter_ = user; //yo implicit copy constructor???
  	this->time_ = time;
  	this->text_ = text;
  }
  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & Tweet::time() const
  {
  	return time_;
  }
  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  string const & Tweet::text() const
  {
  	return text_;
  }
  /**
   * Returns the hashtagged words without the '#' sign
   *
   */
  set<string> Tweet::hashTags() const //how to implemenet this??
  {
    
  	set<string> hashWords;
    //add check for if text is empty
    stringstream ss(text_);
    string word;
    while( ss >> word)
    {
      // int hashtagPos = -1;
      // hashtagPos = temp.find('#');

      bool hashFlag = false;
      if (word.find('#') == 0) //str.find() returns the position of the character
      {
        hashFlag = true;
      }
      if (hashFlag)
      {
        hashWords.insert(word.substr(1)); 
        //check: not using convLower here, is that okay?  
        //i.e. preserving uniqueness of capitalization
      }

      
    }

    return hashWords;

  }
  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
  bool Tweet::operator<(const Tweet& other) const  //checks is less than
  {
    return (this->time_.operator<(other.time_)); //checks if it's member variable time is < other's time)
  }

    
  
  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
  ostream& operator<<(ostream& os, const Tweet& t) //friend only needed in .h
  //it was a friend of the tweet class
  {
    
    os << t.time_ << " " << t.tweeter_->name() << t.text_; //don't want to add the endl 
    // CHECK: change to the funcs?
    //uninitialized objects just gives the memory address

    return os;

  }
  /* Create any other public or private helper functions you deem 
     necessary */

  User* Tweet::user() const
  {
  	//return &User; //this pointer was mutable? (not const) so it failed
    //try to avoid passing &something in a function?
    //primary-expression means you are probably returning improperly
    return tweeter_;
  }


  /* You may add other member functions */

  /* Add any other data members or helper functions here  */
