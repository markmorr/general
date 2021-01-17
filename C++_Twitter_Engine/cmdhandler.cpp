#include "cmdhandler.h"
#include "util.h"
#include "twiteng.h"
#include "datetime.h"
using namespace std;


QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}
//dump feeds by this point should be including any tweets that were added through
//the user interface


///////////////////////////////////////////////////////



AndHandler::AndHandler() //leave as is
{
	
}

AndHandler::AndHandler(Handler* next) //leave as is ?
  : Handler(next)
{

}


bool AndHandler::canHandle(const std::string& cmd) const //leave as is ?
{
	return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	
	string word;
	vector<string> wordsToSearch;
	while (instr >> word)
	{
		wordsToSearch.push_back(word);
	}

	vector <Tweet*> tweetResults = eng->search(wordsToSearch,0);
	
	/*for(unsigned int i = 0; i < tweetResults.size(); i++)
	{
		cout << tweetResults[i] << endl;
	}*/
	displayHits(tweetResults);
	
	return HANDLER_OK;
}



/////////////////////////////////////////////////////////



OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	string word;
	vector<string> wordsToSearch;
	while (instr >> word)
	{
		wordsToSearch.push_back(word);
	}

	vector <Tweet*> tweetResults = eng->search(wordsToSearch,1);
	displayHits(tweetResults);
	return HANDLER_OK;
}



//////////////////////////////////////////////////////



TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";

}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	//string name;
	string text;
	//instr >> name;
	getline(instr,text);
	DateTime currtime;
	User* currentUser = eng->getCurrentUser();
	if(currentUser == NULL)
	{
		cout << "Currently no user is logged in" << endl;
		return HANDLER_OK;
	}
	string name = currentUser->name();
	eng->addTweet(name,currtime,text);
	return HANDLER_OK;
}


///////////////////////////////////////




FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
  : Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW"; //because it always does convolve upper in twitter

}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	//string name_of_follower;
	string name_to_follow;
	//instr >> name_of_follower;
	instr >> name_to_follow;
	User* currentUser = eng->getCurrentUser();
	if(currentUser == NULL)
	{
		cout << "Currently no user is logged in" << endl;
		return HANDLER_OK;
	}
	string name = currentUser->name();
	eng->addFollowPair(name, name_to_follow);


	return HANDLER_OK;
}


///////////////////////////////////




SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
  : Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";

}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	//filename += ".dat"; (twitter_sol doesn't do this)
	ofstream ofile;
	ofile.open(filename);
	eng->produceDatabase(ofile);

	return HANDLER_OK;
}




//////////////////////////////////////////////////////



SCCHandler::SCCHandler()
{

}

SCCHandler::SCCHandler(Handler* next)
  : Handler(next)
{

}

bool SCCHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SCC";

}

Handler::HANDLER_STATUS_T SCCHandler::process(TwitEng* eng, std::istream& instr) const
{
	
	string filename;
	instr >> filename;
	//filename += ".dat"; (twitter_sol doesn't do this)
	ofstream ofile;
	ofile.open(filename);
	eng->tarjan(ofile);
	return HANDLER_OK;
}





//////////////////////////////////////////////////////



TrendingHandler::TrendingHandler()
{

}

TrendingHandler::TrendingHandler(Handler* next)
  : Handler(next)
{

}

bool TrendingHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TRENDING";

}

Handler::HANDLER_STATUS_T TrendingHandler::process(TwitEng* eng, std::istream& instr) const
{
	
	int n;
	instr >> n;
	 eng->trendingTweets(n);
	//for(int i = 0; )
	return HANDLER_OK;
}



//////////////////////////////////////////////////////



LoginHandler::LoginHandler()
{

}

LoginHandler::LoginHandler(Handler* next)
  : Handler(next)
{

}

bool LoginHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGIN";

}

Handler::HANDLER_STATUS_T LoginHandler::process(TwitEng* eng, std::istream& instr) const
{
	string username;
	string password;
	instr >> username;
	instr >> password;
	// if(!(eng->validUser(username)))
	// {
	// 	cout << "username wrong" << endl;
	// 	return HANDLER_ERROR;
	// }

	if(!(eng->Login(username,password)))
	{
		cout << "Invalid username/password." << endl;
		return HANDLER_ERROR;
	}

	cout << "Login successful." << endl;
	 //validUser should return a bool

	return HANDLER_OK;
}




//////////////////////////////////////////////////////



LogoutHandler::LogoutHandler()
{

}

LogoutHandler::LogoutHandler(Handler* next)
  : Handler(next)
{

}

bool LogoutHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGOUT";

}

Handler::HANDLER_STATUS_T LogoutHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->Logout();
	
	return HANDLER_OK;
}








