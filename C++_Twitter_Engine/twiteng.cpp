#include "twiteng.h"
#include "msort.h"


using namespace std;


//didn't end up using but kept here for reference of how it would be done just in case
struct Node{

  User* value;
  int index;
  int lowlink;
 
  
};


//changed liens 213 check that they work where to find test files?


void TwitEng::parseHashtags( string& text, Tweet* myTweet)
{
  
  stringstream wordStream (text);
  string wordsBeforeTag;
  string tagWord;
  while(getline(wordStream,wordsBeforeTag,'#') )
  {
    wordStream >> tagWord;
    convLower(tagWord);
  
    //if this is a new tagWord we've never seen before
    if(tagWord == "")
    {
    	//cout <<"found empty" << endl;
    	return;
    }

    if (tweetTags.find(tagWord) == tweetTags.end()) 
    {
      set<Tweet*> myNewSet; //default construct an empty set

      TagData old(tagWord,1);
      tweetTags.insert({tagWord,myNewSet}); //insert the tweet and an empty set
      
      trending_.push(old);
     

    }

    tweetTags[tagWord].insert(myTweet); //insert this tweet into the set

    if(tweetTags[tagWord].size() > 1)
    {	
    TagData old(tagWord,tweetTags[tagWord].size()-1);
    TagData newVal(tagWord,tweetTags[tagWord].size()); //every time we see hashtag we're replacing it w/ one
    trending_.decreaseKey(old,newVal);
	}
    
    
    
  }







  //this stuff goes in twiteng, fix syntax
   // trending_.decreaseKey(TagData(bighhas,occ-1,TagData(big_has,occ));) //is the hashtag string in convupper
    //hashmap.insert({big_hash,temp});

}

void TwitEng::trendingTweets(int n)
{
  vector<TagData> mytags;

  if(trending_.empty())
  {
    return;
  }

  if(n > trending_.size())
  {
  	n = trending_.size();
  }

  for(int i = 0; i < n; i++)
  {
  	cout << trending_.top().tag << ": " << trending_.top().num << endl;
    mytags.push_back(trending_.top());
    trending_.pop();
  }

  for(int i = 0; i < n; i++) //order shouldn't matter how we put them back, should be fine
  {
    trending_.push(mytags[i]);
    //cout << "Pushed back " << mytags[i].tag << " " << mytags[i].num << endl;
  }
 //cout << "top is now " << trending_.top().tag << " " << trending_.top().num  << " with size " << trending_.size() << endl;
  
  return;

}



TwitEng::TwitEng():   trending_(2), currUser_(NULL)
{

}


TwitEng::~TwitEng()
{

  for(map<string, User*>::iterator it1 = allUsers.begin(); it1 != 
    allUsers.end(); ++it1)
  {
    delete it1->second; // calls destructor for a user
  }

  //we delete the users, and users delete the tweets
  

}
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */


bool TwitEng::parse(char* filename)
{
  ifstream infile;
  infile.open(filename);

  if (infile.fail())
  {
    return true; //i.e. it's true there was an error
  }

  ifstream infileTwo;
  infileTwo.open(filename);

  string line;
  string lineDummy;
  int numUsers;
  getline(infile,line);


  if (infile.fail())
  {
    return true;
  }

  stringstream ss1(line);
  ss1 >> numUsers;

   getline(infileTwo,lineDummy); //just advancing infileTwo to the proper place

  //takes care of the users portion
  //CHECK: could we have a blank line within the users section? continue? how 
  //could pass the tweets into a helper function that can return a tweet* 
   //or null if failed

  // we loop through all the first names on each line first 
  // and instantiate each user before trying to add followers
  for(int i = 0; i < numUsers; i++)

    {
      getline(infile,line);
      if(line == "")
      {
        numUsers++; 
        continue; 
      }

  
      else
      {
      stringstream ssUsers(line);
      string name;
      ssUsers >> name;
      User* myUser = new User(name);
      allUsers.insert( {name, myUser} );
      }

    }


  for(int i = 0; i < numUsers; i++)
    {
      getline(infileTwo, line);

      stringstream ssUsersAgain(line);
      if(line == "")
      {
        numUsers++; //check: does this work? we have to continue right?
        continue; 
      }

      string nameOfSheep; //because he's a follower
      string namesToFollow;

      unsigned long long passHash;
      ssUsersAgain >> nameOfSheep;
        ssUsersAgain >> passHash;
      //cout << "user and password: " << nameOfSheep << passHash << endl;
      passCodes.insert({nameOfSheep,passHash});
      //loop through rest of the line
      while (ssUsersAgain >> namesToFollow )
      {
      addFollowPair(nameOfSheep,namesToFollow);//replace with AddFollowing function:
      }
   
//how many unique tweets contain a given hashtag
    }

    // for(map<string,User*>::iterator it = allUsers.begin();it !=
    // allUsers.end();++it)
    // {
    //   cout << it->first << endl;
    // }
 

  while (getline(infileTwo, line) )
  {
    if (line == "")
    {
      continue;
    }
    else
    {
      stringstream ssTweet(line);
      stringstream ssTweetText(line);
      DateTime mydt;
      string mytweeter;
      string mytext;
      string textline;

       while(ssTweet >> mydt) //because we defined this for DateTimes
      {

        DateTime currTime;
        // if (!(currTime < mydt) && !(mydt < currTime)) //isn't same exact time?
        // {
        //   break;
        // }

        if (ssTweet.fail()) //how will this know if we failed?
        {
          break;
        }

        string temp;
        ssTweetText>>temp;
        ssTweetText>>temp;
        ssTweetText >> mytweeter;

        string textlineCopy;
        
        //could I do ss >> std::ws
        //getline(ss,question);
        getline(ssTweetText,textline); 
        textlineCopy = textline;


      
      
        map<string,User*>::iterator itTweeter; 
        itTweeter = allUsers.find(mytweeter);
       if(itTweeter == allUsers.end()){
        cout << "ERROR " << endl; //check
       }
       
        Tweet* myNewTweet = new Tweet(itTweeter->second,mydt,textline); 
      
        (itTweeter->second)->addTweet(myNewTweet);

        parseHashtags(textline, myNewTweet);
       
        parseMentions(textlineCopy, myNewTweet);


      }

    }
  }

  // for(map<string,set<Tweet*>:;iterator myit = tweetTags.begin(); myit != 
  //   tweetTags.end(); ++myit)
  // {
      
  // }
    

return false; //returning false if we reached end with no error
}

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
void TwitEng::addTweet( string& username,  DateTime& time, string& text)
{
   //if it's a new user tweeting, add it
 
  

  map<string,User*>::iterator it;
  it = allUsers.find(username); 

  if (it == allUsers.end())
  {
   cout << "Error: User not stored in database" << endl;
   return;
  }

  if (it != allUsers.end())
  {
    Tweet* myNewTweet = new Tweet(it->second,time,text);
    (it->second)->addTweet(myNewTweet); //calls the user::addTweet
    parseHashtags(text, myNewTweet);

  }

   //it knows which addTweet to call based off the object?
   //need dynamic allocation so that it doesn't go out of scope


}

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{

 vector<Tweet*> resultVec;

 if(terms.size() == 0) //so we don't seg fault if they just put "and   "
 {
  return resultVec;
 }


 for(unsigned int i = 0; i < terms.size(); i++)
 {
  convLower(terms[i]);
 }

 string firstWord = terms[0];
 map<string, set<Tweet*> >::iterator it1 = tweetTags.find(firstWord);

 bool wordsNotFoundIntersection = false;

 set<Tweet*> myIntersection;
 set<Tweet*> myUnion;

 if(it1 == tweetTags.end() )
 {
  
    if(strategy == 0) //***need to nest it so that else block triggers properly
    {
    wordsNotFoundIntersection = true;
    return resultVec;  
    }

 }
 else
 {
  myIntersection = it1->second; 
  //why was having set<Tweet*> myIntersection = it1->second causing an error?
  //what happened when it was being redefined?
 }

 
 
 //myIntersection is now Tweet* set for first word, i.e. T1*,T2*,T3* for cs104

//just compare tweet* in set myIntersection
  if (strategy == 0)
  {
    
    for(unsigned int i = 1; i < terms.size(); i++) 
    
    {
      
      string nextWord = terms[i];
      map<string,set<Tweet*> >::iterator it1 = tweetTags.find(nextWord);

      if (it1 == tweetTags.end())
      {
        wordsNotFoundIntersection = true; //need this in case we get "football cat pac12"
        break; //CHECK

      }

      set<Tweet*> compareSet = it1->second;
      //compareSet is the set we want to compare with

      //myIntersection is the myIntersection we update
      for(set<Tweet*>::iterator it2 = myIntersection.begin(); it2 !=
      myIntersection.end(); ++it2)
      {
        if(compareSet.find(*it2) == compareSet.end())
        {
          myIntersection.erase(*it2);
          //it2--; CHECK
        }
      }


     }

    
  }
  
  else if(strategy == 1)
  {


    for(unsigned int i = 0; i < terms.size(); i++)
    {
      string nextWord = terms[i];
      map<string,set<Tweet*> >::iterator it1 = tweetTags.find(nextWord);
      if(it1 == tweetTags.end())
      {
        continue;
      }
      set<Tweet*> compareSet = it1->second;

      for(set<Tweet*>::iterator myit = compareSet.begin(); myit != 
        compareSet.end(); ++myit)
      {
        myUnion.insert(*myit); 
        //looping over the set, insert takes care of repeats
      }

    }


  }

   if (wordsNotFoundIntersection)
   //used for if a hashtag with no tweets is given to intersection
  {
    vector<Tweet*> emptyVec;
    return emptyVec;
  }

  if (strategy == 0)
  {
     for(set<Tweet*>::iterator it3 = myIntersection.begin(); it3 !=
      myIntersection.end(); ++it3)
     {
      resultVec.push_back(*it3);
     }
   }

  else if (strategy == 1)
  {
    for(set<Tweet*>::iterator it3 = myUnion.begin(); it3 !=
      myUnion.end(); ++it3)
     {
      resultVec.push_back(*it3);
     }
  }

  return resultVec;

}


  /**
   * Dump feeds of each user to their own file
   */
void TwitEng::dumpFeeds()
{
  //loop over every user 
  //if we don't officially quit, this doesn't get called
  //stuff's being overwritten each time?



   

  


  for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != allUsers.end(); ++it1)
  {

    ofstream outfile;
    string name = it1->first; //name is private, compiler doesn't like this
    string filename = name + ".feed";
    outfile.open(filename);

    ofstream outfileMention;
    string filenameTwo = name + ".mentions";
    outfileMention.open(filenameTwo);


    outfile << name << endl; 
    outfileMention << name << endl;
    vector<Tweet*> myFeed = it1->second->getFeed();

    for(unsigned int i = 0; i < myFeed.size(); i++) 
    {
      //cout << "the getFeed: " << *(myFeed[i]) << endl;
      
     bool startFlag = false;
//map<username, feedstring>
      for(map<string,set<Tweet*> >::iterator it2 = startMentions.begin(); it2 !=
        startMentions.end(); ++it2)
      {
      
         

        if ( it2->second.find(myFeed[i]) != it2->second.end() ) //if tweet was found in the map containing set
        {
          startFlag = true;
          string nameOfMentioned = it2->first;
          //cout << "nameOfMentioned: " << nameOfMentioned << endl; 
           
          if (mutuallyFollowing( findUser(nameOfMentioned), myFeed[i]->user()) ) //it2->first
          {
            //outfile << *(myFeed[i]) << endl; 

            
          }
          
        }
      }

      if(!startFlag ) //if it did not start with a mention
      {
        //cout << "not in start mentions: " << *(myFeed[i]) << endl;
        outfile << *(myFeed[i]) << endl;
      }
      outfileMention.close();


    // if((it1 + 1) == allUsers.end())
    // {

    // }
 }
      

     //////////////middleMentions////////////////
   

 }



  //////////startMentions//////////////

      map<string, vector<Tweet*> > mentionVectors;

      for(map<string,set<Tweet*> >::iterator it5 = startMentions.begin(); it5 !=
        startMentions.end(); ++it5)
      {
          set<Tweet*> currFeed;
          vector<Tweet*> vecFeed;
        mentionVectors.insert( {it5->first, vecFeed} );
        // cout << it5->first << endl;

        //ofstream outfileMention;
        // string myName = it5->first + ".mentions";
        // outfileMention.open(myName, ofstream::app);
        set<Tweet*> currSet = it5->second;

        for(set<Tweet*>::iterator it6 = currSet.begin(); it6 !=
          currSet.end(); ++it6)
        {
          currFeed.insert(*it6);
          //outfileMention << **it6 << endl;
        }

        //outfileMention.close();

        for(set<Tweet*>::iterator myit = currFeed.begin(); myit !=
          currFeed.end(); ++myit)
        {
          //vecFeed.push_back(*myit);
          // cout << **myit << endl;
          mentionVectors[it5->first].push_back(*myit);
        }

        TweetComp mycomp;
        //vector<Tweet*> temp = mentionVectors[it5->first];
        mergeSort(mentionVectors[it5->first], mycomp);

        // for(unsigned int i = 0; i < vecFeed.size(); i++)
        // {
        //   outfileMention << *(vecFeed[i]) << endl;
        // }


      }



     

      for (map<string,set<Tweet*> >::iterator it3 = middleMentions.begin(); it3 !=
        middleMentions.end(); ++it3)
      {
            set<Tweet*> currFeed;
            vector<Tweet*> vecFeed;
            if(mentionVectors.find(it3->first) == mentionVectors.end()){
              mentionVectors.insert( {it3->first, vecFeed} );
            }
            // cout << it3->first << endl;
        // ofstream outfileMention;
        // string myName = it3->first + ".mentions";
        // outfileMention.open(myName,ofstream::app);
        set<Tweet*> currSet = it3->second;

        for(set<Tweet*>::iterator it4 = currSet.begin(); it4 !=
          currSet.end(); ++it4)
        {
          //cout << "these are the middle tweets: " << **it4 << endl;
          //outfileMention << **it4 << endl;
          currFeed.insert(*it4);
        }


        for(set<Tweet*>::iterator myit = currFeed.begin(); myit !=
          currFeed.end(); ++myit)
        {
          // vecFeed.push_back(*myit);
          mentionVectors[it3->first].push_back(*myit);
          // cout << **myit << endl;
        }

        TweetComp mycomp;
        //vector<Tweet*> temp = mentionVectors[it3->first];
        mergeSort(mentionVectors[it3->first], mycomp);

        // for(unsigned int i = 0; i < temp.size(); i++)
        // {
        //   outfileMention << *(temp[i]) << endl;
        // }

        // outfileMention.close();

        }

        //to outfile
        for(map<string, vector<Tweet*> >::iterator it7 = mentionVectors.begin();
          it7 != mentionVectors.end(); ++it7){
          ofstream outfileMention;
          string myName = it7->first + ".mentions";
          outfileMention.open(myName, ofstream::app);
          for(unsigned int i = 0; i < it7->second.size(); i++){
            outfileMention << *((it7->second)[i]) << endl;
          }
        }




 // for(set<Tweet*>::iterator myit = currFeed.begin(); myit !=
 //      currFeed.end(); ++myit)
 //    {
 //      vecFeed.push_back(*myit);
 //    }

 //    TweetComp mycomp;
 //    mergeSort(vecFeed, TweetComp);

 //    for(int i = 0; i < vecFeed.size(); i++)
 //    {
 //      outfileMention << *(vecFeed[i]) << endl;
 //    }


}




void TwitEng::parseMentions(string& text, Tweet* myTweet)
{

  stringstream wordStream(text);
  string wordsBefore;
  string firstWord;
  bool startFlag = false;

  wordStream >> firstWord; //should get first word

  if(firstWord.find('@') == 0) 
  {
    string firstWordBody = firstWord.substr(1);
    startFlag = true;
    if(startMentions.find(firstWordBody) == startMentions.end())
    {
      set<Tweet*> mySet;
      startMentions.insert({firstWordBody,mySet});  
     // cout << "firstWordBody: " << firstWordBody << endl;
    }

    startMentions[firstWordBody].insert(myTweet); //add tweet to the set
    
  }


// 2018-06-10 01:10:49 USCViterbi Machine Learning #Algorithm Mines 16 Billion emails
//  @TechReview features @CSatUSC researchers @Tommy @Jill
//////////now middleMentions ///////////////
  string wordsBeforeMention;
  string mentionName;
  
  if (!startFlag) //we don't want to add tweets that start with a mention to our middleMentions
  {
    //cout << "Entered middleMentions" << endl;
    while(getline(wordStream,wordsBeforeMention,'@')) //it has already passed the first mention
    {
      wordStream >> mentionName;
      if (allUsers.find(mentionName) != allUsers.end()) //only if it's a legit user name
      {
        if (middleMentions.find(mentionName) == middleMentions.end())//if it's the first time this user
          //got mentioned, then create the key value pair
        {
         set<Tweet*> myNewSet;
         middleMentions.insert( {mentionName,myNewSet} );
        }

        middleMentions[mentionName].insert(myTweet);

      }
    }
  }
  //cout << "middleMentions.size" << middleMentions.size() << endl;

  //cout << "1 Start Mentions size " << startMentions.size() << this << endl; 
 

}


void TwitEng::addFollowPair(string name_of_follower, string name_to_follow)
{
  //cout << "In addFollowPair" << endl;

  map<string,User*>::iterator it1 = allUsers.find(name_of_follower);
  map<string,User*>::iterator it2 = allUsers.find(name_to_follow);
  if (it1 == allUsers.end())
  {
    cout << "Error: Follower name invalid" << endl;
    return;
  }

  if(it2 == allUsers.end())
  {
    cout << "Error: name_to_follow is invalid" << endl;
    return;
  }
  (it1->second)->addFollowing(it2->second);
  (it2->second)->addFollower(it1->second); 


}


void TwitEng::produceDatabase(ostream& mydat) //might have to do it like dumpfeeds()--can you pass in an ofstream?
{
  //users
  mydat << allUsers.size() << endl;
  for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != 
    allUsers.end(); it1++)
  {
    mydat << it1->second->name() << " ";
    set<User*> currFollowing = it1->second->following();
    for(set<User*>::iterator it2 = currFollowing.begin(); it2 !=
      currFollowing.end(); it2++)
    {
      mydat << (*it2)->name() << " ";//first * takes care of the iterator part
    }
    mydat << endl;
  }

  //tweets
  //is the inner for loop gonna work as intended?
  for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != 
    allUsers.end(); it1++)
  {
    list<Tweet*> currTweetsList = it1->second->tweets();
    for(list<Tweet*>::iterator it2 = currTweetsList.begin(); it2 !=
      currTweetsList.end(); it2++)
    {
      mydat << **it2 << endl; 
    }
  }


}

bool TwitEng::mutuallyFollowing(User* u1, User* u2)
{
  //why getting//how to fix this warning?
  if (u1 == NULL || u2 == NULL)
  {
    cout << "Error: passed in null users to mutuallyFollowing" << endl;
    return false;
  }

  //cout << "Before: " << u1->name() << " " << u2->name() << endl;
  // u1->following();
  // u1->followers();
  // u2->following();
  // u2->followers();

  // set<User*>::iterator it1 = u1->following().find(u2);
  //  set<User*>::iterator it2 = u1->followers().find(u2);
  //  cout << "it1 " << (*it1)->name() << endl;
  //  cout << "it2 " << (*it2)->name() << endl;
  
  // if ((it1 != u1->following().end()) && (it2 != u1->followers().end())) {
  //   cout << "true" << endl;
  //   return true;
  // }
  // else {
  //   return false;
  //   cout << "false" << endl;
  // }

  //cout << "Before: " << u1->name() << " " << u2->name() << endl;

  //cout << "After: " << u1->name() << " " << u2->name() << endl;
  set<User*> u1following = u1->following();
  set<User*> u1followers = u1->followers();
  //it was passing the set back by value--so weren't comparing the same sets, so of course they were
  //different

  if ( (u1following.find(u2) != u1following.end()) && (u1followers.find(u2) != u1followers.end()) )
  {
    
    // cout << "These users are mutally following: " << u1->name() << " " << u2->name() << endl;
      return true;
    // if (u1->followers().find(u2) != u1->followers().end())
    // {

     
    // }
   // else return false;
  }
  
  else
  {
    return false;
  }
  

}

  User* TwitEng::findUser(std::string name)
 {
  //how to fix this warning?
  for(map<string,User*>::iterator it = allUsers.begin(); it != 
    allUsers.end(); ++it)
  {
    if (name == it->first)
    {
      return it->second;
    }
  }
  return NULL;
 }



set<set<User*> > TwitEng::tarjan(ofstream& myfile)
{

  int index = 0; //
  stack<User*> S;
  //ensure it happens for every node
  //CHECK: have to reset it at the start of every call? i.e. data members indexes should always
  //start at one
  
  for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != allUsers.end(); it1++)
  {
    if(it1->second->index == -1)
      strongconnect(it1->second, index, S);
  }


  //print them
  int counter = 0;
  for(set<set<User*> >::iterator it2 = SCCset.begin(); it2 != SCCset.end(); ++it2)
  {
    set<User*> currComponent = *it2;
    counter++;
 
    myfile << "Component " << counter << endl;
    for(set<User*>::iterator it3 = currComponent.begin(); it3 != currComponent.end(); ++it3)
    {
      myfile << (*it3)->name() << endl;
      
    }
    myfile << endl;
   
  }


  return SCCset;
}

void TwitEng::strongconnect(User* v, int& index, stack<User*>& S)  
{
  v->index = index;
  v->lowlink = index;
  index = index + 1;
  S.push(v);
  //myset.push(v);
  v->onStack = true; 
  User* myguy;

  // Consider successors of v
  //for (each (v, w) in E )
  set<User*> currFollowing = v->following(); //HAD TO STORE INTO A TEMP
  //each call to following returns a copy, so doing something like (v->following.begin(); 
  //v->following->end(); ++itw) would have incurred repeated calls producing multiple copies

  for(set<User*>::iterator itw = currFollowing.begin(); itw !=
  currFollowing.end(); ++itw)
  {
    if ((*itw)->index == -1)
    {
      // Successor w has not yet been visited; recurse on it
      strongconnect(*itw, index, S);
      v->lowlink = min(v->lowlink,(*itw)->lowlink);
    }
  
    else if((*itw)->onStack == true) 
    {
        // Successor w is in stack S and hence in the current SCC
        // If w is not on stack, then (v, w) is a cross-edge in the DFS tree and must be ignored
        // Note: The next line may look odd - but is correct.
        // It says w.index not w.lowlink; that is deliberate and from the original paper
        v->lowlink  = min(v->lowlink, (*itw)->index);
    }
  }
  

  // If v is a root node, pop the stack and generate an SCC
  if (v->lowlink == v->index) 
  {
      //start a new strongly connected component
      set<User*> tempSCC;
      //repeat
      do 
      {
      (myguy) = S.top();
      S.pop();
      (myguy)->onStack = false;
      //add w to current strongly connected component //instackset.erase
      tempSCC.insert(myguy);
      }
    while (myguy != v); //comparing two user pointers??
    {
    //output the current strongly connected component
    SCCset.insert(tempSCC);
    }
  }




}



User* TwitEng::getCurrentUser()
{
	
	return currUser_;
}


bool TwitEng::validUser(string username)
{	
	
	if (allUsers.find(username) != allUsers.end())
	{
		return true;
	}
	else
		return false;
}
	

bool TwitEng::Login(string username, string password)//login mark abc123
{
	map<string,unsigned long long>::iterator it;
	map<string, User*>::iterator it2;
	it2 = allUsers.find(username);


	it = passCodes.find(username);
	if (it == passCodes.end())
	{
		//cout << "Bad username" << endl;
		return false;
	}

	if (it->second != calculateHash(password))
	{
		//cout << "Bad password" << endl;
		return false;
	}

	currUser_ = it2->second;
	//cout << "successfully logged in " << username << endl;
	return true;
}


void TwitEng::Logout()
{
	//cout << "successful logout" << endl;
	currUser_ = NULL;
}









  /* You may add other member functions */

 
  //stack<User*> mystack; //seen stack, in set
  //set<User*> myset;

  // for(map<string,User*>::iterator userit = allUsers.begin(); userit !=
  //   allUsers.end(); ++userit)
  //   //does it need dynamic allocation? when to delete?
  //   //CHECK: use the constructor initalization list in heap constructor
  // {
  //   Node* mynode = new Node;
  //   everynode.push_back(mynode);
  //   mynode->value = userit->second;
  //   mynode->index = -1;
  //   mynode->lowlink = -1;
  // }
