#include <cmath>
#include <ctime>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const char DELIM = '|';

struct due_date{
    struct tm date;
    string name;
    int maximum;
};

bool process(due_date test_due, const time_t& today_seconds)
{
    struct tm& test_date = test_due.date;
    double seconds_difference = difftime(mktime(&test_date), today_seconds);
    double days_difference = seconds_difference/60/60/24;

    if(days_difference>test_due.maximum)
        return false;

    if(days_difference>0)
    {
        int days_even = ceil(days_difference);
        cout << days_even << " day" << (days_even==1 ? "" : "s") << " until "
             << test_due.name << endl;
    }
    else
    {
        days_difference *= -1;
        if(days_difference<1)
            cout << test_due.name << "due TODAY!" << endl;
        else
        {
            //floor instead of ceiling due to sign flip
            int days_even = floor(days_difference);

            cout << test_due.name << " is " << days_even
                 << " day" << (days_even==1 ? "" : "s") << " LATE!" << endl;
        }
    }

    return true;
}

bool parse_line(const string& line, const struct tm& today, due_date& due)
{
    //guard number of delimeters
    if(count(line.begin(), line.end(), DELIM) != 2)
        return false;

    stringstream ss(line);
    string temp_name, temp_weekday;
    int temp_maximum, temp_month, temp_day;

    getline(ss, temp_name, DELIM);
    ss.ignore(); //ignore space
    ss >> temp_weekday >> temp_month;
    ss.ignore(); //ignore /
    ss >> temp_day; 
    ss.ignore(3); //ignore " DELIM "
    ss >> temp_maximum >> temp_maximum; //ignore whitespace and DELIM

    //DEBUG
    //cout << "name: "    << temp_name << endl;
    //cout << "weekday: " << temp_weekday << endl;
    //cout << "day: "     << temp_day << endl;
    //cout << "month: "   << temp_month << endl;
    //cout << "max: "     << temp_maximum << endl << endl;

    struct tm temp_date = today;
    temp_date.tm_sec  = 0;
    temp_date.tm_min  = 0;
    temp_date.tm_hour = 0;

    if(1 <= temp_day && temp_day <= 31)
        temp_date.tm_mday = temp_day;
    else
        return false;

    temp_date.tm_wday = 
        temp_weekday=="Sunday"    ? 0 :
        temp_weekday=="Monday"    ? 1 :
        temp_weekday=="Tueday"    ? 2 :
        temp_weekday=="Wednesday" ? 3 :
        temp_weekday=="Thursday"  ? 4 :
        temp_weekday=="Friday"    ? 5 :
        temp_weekday=="Saturday"  ? 6 :
        -1;

    if(temp_date.tm_wday == -1)
        return false;

    if(1 <= temp_month && temp_month <= 12)
        temp_date.tm_mon = temp_month-1; //[1, 12] -> [0, 11]
    else
        return false;

    due.date    = temp_date;
    due.maximum = temp_maximum;
    due.name    = temp_name;

    return true;
}

int main(int argc, char** argv){
    //determine todays date
    time_t today_seconds; time(&today_seconds);
    auto today_date = *localtime(&today_seconds);

    //establish file path
    string file_path = "~/hw.txt";
    if(argc==2)
        file_path = argv[1];

    //attempt to open file
    ifstream file; file.open(file_path);
    if(!file.is_open())
    {
        cout << "couldn't open \"" << file_path << "\" for processing, exiting" << endl;
        return 0;
    }

    //build due list from file
    vector<due_date> due_list;
    string buffer;
    while(getline(file, buffer))
    {
        due_date temp;
        if(parse_line(buffer, today_date, temp))
            due_list.push_back(temp);
    }

    //process list
    int count=0;
    for(auto due : due_list)
        count += process(due, today_seconds);

    if(count==0)
        cout << "nothing due!" << endl;
}
