#include "dateManager.hpp"

void DateManager::SignalSpendingSpeed(const dataNS::DateStruct & startDate, const dataNS::DateStruct & endDate, const dataNS::DateStruct & expenseDate, const dataNS::Category & category){

}
bool DateManager::DateInBetweenOtherDates(const dataNS::DateStruct & firstDate, const dataNS::DateStruct & middleDate, const dataNS::DateStruct & lastDate){
    auto ymdFirst = year{firstDate.year}/firstDate.month/firstDate.day;
    auto ymdMiddle = year{middleDate.year}/middleDate.month/middleDate.day;
    auto ymdLast = year{lastDate.year}/lastDate.month/lastDate.day;
    if(!ymdFirst.ok() || !ymdMiddle.ok() || !ymdLast.ok()){
        throw std::invalid_argument("parsing error of date");
    }
    return ((ymdFirst <= ymdMiddle) && (ymdMiddle < ymdLast)); 
}
dataNS::DateStruct DateManager::ParseDate(const string & date){
    stringstream stringStream(date);
    string segment;
    vector<string> stringDateParsed;

    while(getline(stringStream, segment, '.'))
    {
        stringDateParsed.push_back(segment);
    }
    if(stringDateParsed.size() != 3){
        throw std::invalid_argument("invalid date format");
    }
    int yearInt;
    int monthInt;
    int dayInt;
    try{
        dayInt = stoi(stringDateParsed[0]);
        monthInt = stoi(stringDateParsed[1]);
        yearInt = stoi(stringDateParsed[2]);
    }
    catch(...){
        throw std::invalid_argument("invalid date format");
    }
    auto ymd = year{yearInt}/monthInt/dayInt;
    if(ymd.ok()){
        //date is a valid date
        dataNS::DateStruct date;
        date.year = int(ymd.year());
        date.month = unsigned(ymd.month());
        date.day = unsigned(ymd.day());
        return date;
    }
    else{
        throw std::invalid_argument("invalid date format");
    }
    /*auto today = year_month_day{floor<days>(system_clock::now())};
        //auto x = year{x}/1/24;

    auto ymd = year_month_day{floor<days>(system_clock::now())};
    auto y   = int(ymd.year());
    auto m   = unsigned(ymd.month());
    auto d   = unsigned(ymd.day());

    cout << y << "/" << m << '/' << d << endl;
    auto x1 = year{2022}/5/5;
    auto x2 = year{2022}/4/20;
    bool hh = (x1 > ymd) && ( ymd > x2);
    if(hh){
        cout << "tru";
    }
    //cout << (sys_days{x1} - sys_days{ymd}).count();*/
}
dataNS::DateStruct DateManager::GetTodaysDate(){
    auto ymd = year_month_day{floor<days>(system_clock::now())};
    dataNS::DateStruct date;
    date.year = int(ymd.year());
    date.month = unsigned(ymd.month());
    date.day = unsigned(ymd.day());
    return date;
}