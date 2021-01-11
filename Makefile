CC = g++
CPPFLAGS = -Wall -g -std=c++11 -fmax-errors=2
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread 
ALL = twitter tweet.o user.o datetime.o twiteng.o util.o handler.o cmdhandler.o testheap2 hashmain 

all: $(ALL)

clean:
	rm -rf $(ALL)


tweet.o: tweet.cpp tweet.h user.h datetime.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

user.o: user.cpp user.h tweet.h msort.h
	$(CC) $(CPPFLAGS) -c $< -o $@

datetime.o: datetime.cpp datetime.h
	$(CC) $(CPPFLAGS) -c $< -o $@

twiteng.o: twiteng.cpp twiteng.h datetime.h user.h tweet.h heap.h hash.h hash.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

util.o: util.cpp util.h
	$(CC) $(CPPFLAGS) -c $< -o $@

handler.o: handler.cpp handler.h twiteng.h
	$(CC) $(CPPFLAGS) -c $< -o $@

cmdhandler.o: cmdhandler.cpp cmdhandler.h handler.h util.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

twitter: datetime.o  cmdhandler.o user.o  handler.o \
	tweet.o util.o  hash.o  twiteng.o  twitter.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

hash: hash.cpp hash.h
	$(CC) $(CCPFlAGS) hash.cpp -o hash

testheap2: testheap2.cpp heap.h
	$(CC) $(CPPFLAGS) testheap2.cpp -o testheap2

hashmain: hash.h hash.cpp hashmain.cpp 
	$(CC) $(CPPFLAGS) $^ -o $@



 #.PHONY: clean:
 #	rm -f twitter tweet.o user.o datetime.o twiteng.o util.o handler.o cmdhandler.o testheap2

#have to run make clean to clean up those pesky files

#having twitter.o was doing this: it only looked at the header and was recompiling
#those. so it wasn't recompliling twiteng or something? twiteng was relying on the
#two new maps and assumed they were there. but twitter was using the old version
#and trying to access the maps who were full of garbage?


#copytest lliststr.o setstr.o settest majors.o majors


#do we need to include these all already? how do we start compiling now?
# $^ represents the list of dependencies

# -c means we are making an object file
# < take the first one one the list to
# -o whatever is written after is the name of the output file
# @ means the target


# twitter: 
#twitter.cpp twiteng.o util.o  user.o handler.o tweet.o cmdhandler.o
# 	$(CC) $(CPPFLAGS) twitter.cpp twiteng.o util.o tweet.o cmdhandler.o -o twitter


