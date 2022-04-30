#include "dateManager.hpp"

/**
 * @brief Computes how quickly the user is spending the budget. 
 * It computes average total expense in the day of expense and
 * then it gives 20%+- range, within which actuall total expense
 * that day should be.
 * @param startDate start date of budget
 * @param endDate end date of budget
 * @param expenseDate date of the expense
 * @param category category of expense
 */
void DateManager::SignalSpendingSpeed(const dataNS::DateStruct & startDate, const dataNS::DateStruct & endDate, const dataNS::DateStruct & expenseDate, const dataNS::Category & category){
    auto ymdStart = year{startDate.year}/startDate.month/startDate.day;
    auto ymdEnd = year{endDate.year}/endDate.month/endDate.day;
    auto ymdExpense = year{expenseDate.year}/expenseDate.month/expenseDate.day;
    int budgetDuration = (sys_days{ymdEnd} - sys_days{ymdStart}).count();
    double budgeted = category.budgeted;
    double budgetedPerDay = budgeted/budgetDuration;
    double allowedDeflection = 0.2 * budgeted;
    int numDaysFromStart = (sys_days{ymdExpense} - sys_days{ymdStart}).count();
    double averageTotalExpenseOnTheDateOfExpense = budgetedPerDay * numDaysFromStart;
    double lowerBound = averageTotalExpenseOnTheDateOfExpense - allowedDeflection;
    double upperBound = averageTotalExpenseOnTheDateOfExpense + allowedDeflection;

    double expenseInCategory = 0;
    for(const auto & expense : category.expenses){
        expenseInCategory += expense.amount;
    }
    //we are managing to save (we spent 20% less then we should by this time)
    if(expenseInCategory < lowerBound){
        cout << "Good job! You are spending your money wisely and you manage to save. " << endl;
    }
    else if(expenseInCategory > upperBound){
        cout << "WOAH, SLOW DOWN WILL YA. Or else you better find better job if you keep throwing money out of window like this. " << endl;
    }
    else{
        cout << "Your spending habits are within acceptable range, keep it up!" << endl;
    }
    if(expenseInCategory > category.budgeted){
        cout << "You spent more than you budgeted, I am disappointed :[" << endl;
    }
    cout << "You spent " << (100*expenseInCategory)/category.budgeted << " \% of budget in this category" << endl;

}
/**
 * @brief Function to check, whether s date is in between two other dates
 * @param firstDate first date
 * @param middleDate middle date to check
 * @param lastDate last date
 * @return true if the date is in between (can be also equal to side ones)
 * @return false date is outside of the range
 * @throws std::invalid_argument if the date are in wrong format
 */
bool DateManager::DateInBetweenOtherDates(const dataNS::DateStruct & firstDate, const dataNS::DateStruct & middleDate, const dataNS::DateStruct & lastDate){
    auto ymdFirst = year{firstDate.year}/firstDate.month/firstDate.day;
    auto ymdMiddle = year{middleDate.year}/middleDate.month/middleDate.day;
    auto ymdLast = year{lastDate.year}/lastDate.month/lastDate.day;
    if(!ymdFirst.ok() || !ymdMiddle.ok() || !ymdLast.ok()){
        throw std::invalid_argument("parsing error of date");
    }
    return ((ymdFirst <= ymdMiddle) && (ymdMiddle <= ymdLast)); 
}
/**
 * @brief Date parser from string in the form of dd.mm.yyyy
 * @param date string in the form of dd.mm.yyyy
 * @return dataNS::DateStruct structure holding the date
 * @throws std::invalid_argument in a case there are not numbers in the date or another invalid date format
 */
dataNS::DateStruct DateManager::ParseDate(const string & date){
    // parsing segments
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
    // parsing ints from segments
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
    // checking for validity of date
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
}
/**
 * @brief Gets todays date from system clock
 * @return dataNS::DateStruct holding current date
 */
dataNS::DateStruct DateManager::GetTodaysDate(){
    auto ymd = year_month_day{floor<days>(system_clock::now())};
    dataNS::DateStruct date;
    date.year = int(ymd.year());
    date.month = unsigned(ymd.month());
    date.day = unsigned(ymd.day());
    return date;
}