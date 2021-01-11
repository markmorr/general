#include "datetime.h"


using namespace std;
/**
 * Models a timestamp in format YYYY-MM-DD HH:MM:SS 
 */
  

  //int CheckFormat(std::istream& ischeck, std::string piece, int length); 
  //had to prototype it because it's called in a function that occurs above


  /**
   * Default constructor for current system time/date
   */
  DateTime::DateTime()
  {

  time_t rawtime;
  struct tm* timeinfo;

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  year = timeinfo->tm_year + 1900;
  month = timeinfo->tm_mon + 1; //it does months since january
  day = timeinfo->tm_mday;
  hour = timeinfo->tm_hour;
  minute = timeinfo->tm_min;
  sec = timeinfo->tm_sec;

  // Use timeinfo pointer to access fields of the tm struct
  }

  /**
   * Alternative constructor 
   */
  DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
  {

  this->year = year;
  this->month = month;
  this->day = day;
  this->hour = hh;
  this->minute = mm;
  this->sec = ss;

  }
  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp



   */

   int DateTime::CheckFormat(istream& ischeck, string piece, int length) //what if they put in "201a"?
   {
    //note: ischeck is ss

    
    
    if(ischeck.fail()) //failed to read properly into a string?
    {
          return -1;
    } 

    int myint;
    stringstream ss2(piece);
    ss2 >> myint;

      if (ss2.fail()) //if it wasn't an int whatsoever
    {
      return -1;
    }

    if ((int)piece.length() != length) //wrong length
    {
      return -1;
    }

    for(int i = 0; i < length; i++) 
    //not a digit, still checking in case a char appeared after the first digit i.e."12dd"
    {
      if (!isdigit(piece[i]))
      {
        return -1;
      }
    }

 

   
  
    
    return myint;

    //if there's no tweet after the timestamp


   }

  bool DateTime::operator<(const DateTime& other) const
  {
      //turn it into an int?
      //concatenate into a string. then ss(numberstr)-> read it into an int and then compare ints.
      if (year < other.year)
        return true;

      else if (year > other.year)
        return false;

      else
      {
        if (month < other.month)
          return true;

        else if (month > other.month)
          return false;
        
        else
        {
          if (day < other.day)
        return true;

          else if (day > other.day)
        return false;

          else
          {
            if (hour < other.hour)
            return true;

            else if (hour > other.hour)
            return false;

            else
            {
              if (minute < other.minute)
              return true;

              else if (minute > other.minute)
              return false;

              else
              {
                if (sec < other.sec)
                  return true;
                else if (sec > other.sec)
                  return false;
                else
                {
                  return true;
                }

              }
     
            }
      
          }
        }
      }
  }

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS
   *
   * @return the ostream passed in as an argument
   */
   std::ostream& operator<<(std::ostream& os, const DateTime& other)
  {
     //define it for the datetime
    //output properly 
    os << setfill('0') << setw(4) << other.year;
    os << "-";
    os << setfill('0') << setw(2) << other.month;
    os << "-";
    os << setfill('0') << setw(2) << other.day;
    os << " ";
    os << setfill('0') << setw(2) << other.hour;
    os << ":";
    os << setfill('0') << setw(2) << other.minute;
    os << ":";
    os << setfill('0') << setw(2) << other.sec;

    return os;

  }

  /**
   * Inputs the timestamp to the given istream expecting the format:
   *   YYYY-MM-DD HH::MM::SS
   *  Returns if an error in the format with the DateTime set to the
   *   current system time/date
   *   
   *
   * @return the istream passed in as an argument
   */
   istream& operator>>(istream& is, DateTime& dt)
  {

    //istream: a tweet in the form of a stream
    //if time incorrect, delete tweet and replace it with the current time on your vm with the prewritten code
   //we are implementing ss.operator>>(dt);
    //check for validity, if not return
   

   string line = "";
   getline(is,line); //should always work? the whole line is an istream
   stringstream ss(line);

   //YYYY-MM-DD HH::MM::SS

   DateTime currentTime; //this calls the default constructor, which sets it to current time

   string yearstr;
   int yearint = -1;
   getline(ss,yearstr,'-');
   yearint = currentTime.CheckFormat(is,yearstr,4); 

   //just needed a datetime object on which to call CheckFormat (it should never change currentTime)


   if ( !(0 <= yearint && yearint <= 9999) ) 
   //checking if it fails the check
   //checkFormat sets yearint to 0 if it fails any check
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   else
   {
    dt.year = yearint; 
   }
   //everything after follows the pattern seen above for year
   //(admittedly should probably have been in a helper function), I'm not proud

   string monthstr;
   int monthint = -1;
   getline(ss,monthstr,'-');
   monthint = currentTime.CheckFormat(is,monthstr,2);

   if ( !(1 <= monthint && monthint <= 12) )
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   
   else
   {
    dt.month = monthint;

   }

   string daystr;
   int dayint = -1;
   getline(ss,daystr,' '); // will this work?
   dayint = currentTime.CheckFormat(is,daystr,2);

   if (ss.fail())
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   if ( !(1 <= dayint && dayint <= 365) )
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   else
   {
    dt.day = dayint;
   }

   string hourstr;
   int hourint = -1;
   getline(ss,hourstr,':'); 
   hourint = currentTime.CheckFormat(is,hourstr,2);
   if ( !(0 <= hourint && hourint <= 23) )
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   else
   {
    dt.hour = hourint;
   }

   string minutestr;
   int minuteint = -1;
   getline(ss,minutestr,':');
   // stringstream ss2(minutestr);
   // ss2 >> minuteint;
   minuteint = currentTime.CheckFormat(is,minutestr,2);
   if ( !(0 <= minuteint && minuteint < 60) )
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }

   else
   {
    dt.minute = minuteint;
   }


   string secondstr;
   int secondint = -1;
   getline(ss,secondstr, ' '); 
   //ss >> secondint;
   secondint = currentTime.CheckFormat(is,secondstr,2);

   if ( !(0 <= secondint && secondint < 60) )
   {
    dt = currentTime;
    is.setstate(std::ios::failbit);
    return is;
   }
   else
   {
    dt.sec = secondint;
   }

   
   return is;

}


   //ends with cout << dt;
   //os << other.time << " " << t.text;
  

  /* Data members -- they can all be public 
   * which is why we've made this a struct */
 



