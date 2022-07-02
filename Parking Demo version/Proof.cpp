#include "Proof.h"
#include <math.h>
const char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int fin_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
std::vector<Block> block_list;

std::string print_block_type(block_type type)
{
    if(type == Normal)
        return "Normal";

    if (type == Sub_amount_start)
        return "SubStr";

    if (type == Sub_amount_end)
        return "SubEnd";
    return "";
}

std::string print_Relation(Relation rel)
{
    if(rel == Great)
        //return "Great";
        return ">";

    if (rel == GreatOrEqual)
        //return "GreatOrEqual";
        return ">=";

    if (rel == Less)
        //return "Less";
        return "<";

    if (rel == LessOrEqual)
        //return "LessOrEqual";
        return "<=";
    return "";
}

void make_block(Block &block, int sn, block_type _type, int _period, Relation _relation, bool _deduct, int _amount, int _max_amount, int _next, time_t s, time_t e)
{
    block.srNo = sn;
    block.type = _type;
    block.period = _period;
    block.relation = _relation;
    block.deduct = _deduct;
    block.amount = _amount;
    block.max_amount = _max_amount;
    block.next = _next;
    block.startTime = s;
    block.endTime = e;
}


time_t _mktime_slow(struct tm *tm)
{
    static struct tm cache = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    static time_t time_cache = 0;
    static time_t (*mktime_real)(struct tm *tm) = NULL;
    time_t result;
    time_t hmsarg;

    /* Load real mktime once into a static */
    if (!mktime_real)
    {
        void *handle;

        /* To forgive this cast, please see man dlopen(3). */
        dlerror();
        handle = dlsym(RTLD_NEXT, "mktime");
        *(void **) (&mktime_real) = handle;

        if (!mktime_real)
        {
            fprintf(stderr, "loading mktime: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }

    /* the epoch time portion of the request */
    hmsarg = 3600 * tm->tm_hour
            +  60 * tm->tm_min
            +       tm->tm_sec;

    if ( cache.tm_mday    == tm->tm_mday
         && cache.tm_mon  == tm->tm_mon
         && cache.tm_year == tm->tm_year )
    {
        /* cached - just add h,m,s from request to midnight */
        result = time_cache + hmsarg;

        /* Obscure, but documented, return value: only this value in arg struct.         
         * 
         * BUG: dst switchover was computed by mktime_real() for time 00:00:00
         * of arg day. So this return value WILL be wrong for switchover days
         * after the switchover occurs.  There is no clean way to detect this
         * situation in stock glibc.  This bug will be reflected in unit test
         * until fixed.  See also github issues #1 and #2.
         */
        tm->tm_isdst  = cache.tm_isdst;
    }
    else
    {
        /* not cached - recompute midnight on requested day */
        cache.tm_mday = tm->tm_mday;
        cache.tm_mon  = tm->tm_mon;
        cache.tm_year = tm->tm_year;
        time_cache    = mktime_real(&cache);
        tm->tm_isdst  = cache.tm_isdst;

        result = (-1 == time_cache) ? -1 : time_cache + hmsarg;
    }

    return result;
}

block_type get_block_type(int type)
{
    if(type == 0)
    {
        return Normal;
    }
    if(type == 1)
    {
        return Sub_amount_start;
    }
    if(type == 2)
    {
        return Sub_amount_end;
    }
    return Normal;
}
    
Relation get_block_Relation(int relation)
{
    if(relation == 0)
    {
        return Great;
    }
    if(relation == 1)
    {
        return GreatOrEqual;
    }
    if(relation == 2)
    {
        return Less;
    }
    if(relation == 3)
    {
        return LessOrEqual;
    }
    return Great;
}

bool compare(int v1, int v2, Relation rel)
{
    if(rel == Great)
        return (v1 > v2);

    if (rel == GreatOrEqual)
        return (v1 >= v2);

    if (rel == Less)
        return (v1 < v2);

    if (rel == LessOrEqual)
        return (v1 <= v2);

    return false;
}

void extract_day_hours(std::vector<hour_in_day> &all_hours_in_day, time_t entryTime, time_t payappTime, std::string type)
{
    all_hours_in_day.clear();
    bool same_day = false;
    bool same_hour = false;
    tm *a = localtime(&entryTime);
    tm _entryTime;
    _entryTime.tm_year = a->tm_year;
    _entryTime.tm_mon = a->tm_mon;
    _entryTime.tm_mday = a->tm_mday;
    _entryTime.tm_wday = a->tm_wday;
    _entryTime.tm_hour = a->tm_hour;
    _entryTime.tm_min = a->tm_min;
    _entryTime.tm_sec = a->tm_sec;
    
    tm *b = localtime(&payappTime);
    tm _payappTime;
    _payappTime.tm_year = b->tm_year;
    _payappTime.tm_mon = b->tm_mon;
    _payappTime.tm_mday = b->tm_mday;
    _payappTime.tm_wday = b->tm_wday;
    _payappTime.tm_hour = b->tm_hour;
    _payappTime.tm_min = b->tm_min;
    _payappTime.tm_sec = b->tm_sec;
    
    if((_payappTime.tm_year == _entryTime.tm_year) && 
       (_payappTime.tm_mon == _entryTime.tm_mon) && 
       (_payappTime.tm_mday == _entryTime.tm_mday))
    {
        same_day = true;
    }
    if(_payappTime.tm_hour == _entryTime.tm_hour)
    {
        same_hour = true;
    }
    if(type == "enter")
    {
        if(same_day)
        {
            if(same_hour)
            {
                hour_in_day current_hour;
                current_hour.hour = _entryTime.tm_hour;
                if(_payappTime.tm_sec >=  _entryTime.tm_sec)
                {
                    current_hour.minute = _payappTime.tm_min - _entryTime.tm_min;
                    current_hour.second = _payappTime.tm_sec - _entryTime.tm_sec;
                }
                else
                {
                    current_hour.minute = _payappTime.tm_min - _entryTime.tm_min - 1;
                    current_hour.second = 60 + _payappTime.tm_sec - _entryTime.tm_sec;
                }
                all_hours_in_day.push_back(current_hour);
            }
            else
            {
                for(int i = _entryTime.tm_hour; i <= _payappTime.tm_hour; i++)
                {
                    
                    hour_in_day current_hour;
                    if(i == _entryTime.tm_hour)
                    {
                        
                        current_hour.hour = i;
                        if(_entryTime.tm_sec == 0)
                        {
                            current_hour.minute = 60 - _entryTime.tm_min;
                            current_hour.second = 0;
                        }
                        else
                        {
                            current_hour.minute = 60 - _entryTime.tm_min - 1;
                            current_hour.second = 60 - _entryTime.tm_sec;
                        }
                    }
                    else if(i == _payappTime.tm_hour)
                    {
                        current_hour.hour = i;
                        current_hour.minute = _payappTime.tm_min;
                        current_hour.second = _payappTime.tm_sec;
                    }
                    else
                    {
                        current_hour.hour = i;
                        current_hour.minute = 60;
                        current_hour.second = 0;
                    }
                    //std::cout << current_hour.hour << ":" << current_hour.minute << ":" << current_hour.second << "\n";
                    all_hours_in_day.push_back(current_hour);
                }
            }
        }
        else
        {
            for(int i = _entryTime.tm_hour; i < 24; i++)
            {
                hour_in_day current_hour;
                if(i == _entryTime.tm_hour)
                {
                    current_hour.hour = i;
                    if(_entryTime.tm_sec == 0)
                    {
                        current_hour.minute = 60 - _entryTime.tm_min;
                        current_hour.second = 0;
                    }
                    else
                    {
                        current_hour.minute = 60 - _entryTime.tm_min - 1;
                        current_hour.second = 60 - _entryTime.tm_sec;
                    }
                }
                else
                {
                    current_hour.hour = i;
                    current_hour.minute = 60;
                    current_hour.second = 0;
                }
                all_hours_in_day.push_back(current_hour);
            }
        }
    }
    if(type == "exit")
    {
        if(!same_day)
        {
            for(int i = 0; i < _payappTime.tm_hour + 1; i++)
            {
                hour_in_day current_hour;
                if(i == _payappTime.tm_hour)
                {
                    current_hour.hour = i;
                    current_hour.minute = _payappTime.tm_min;
                    current_hour.second = _payappTime.tm_sec;
                }
                else
                {
                    current_hour.hour = i;
                    current_hour.minute = 60;
                    current_hour.second = 0;
                }
                all_hours_in_day.push_back(current_hour);
            }
        }
    }
}

std::vector<hour_in_day> extract_all_day_hours()
{
    std::vector<hour_in_day> all_hour_day;
    for(int i = 0; i < 24; i++)
    {
        hour_in_day hour_day;
        hour_day.hour = i;
        hour_day.minute = 60;
        hour_day.second = 0;
        all_hour_day.push_back(hour_day);
    }
    return all_hour_day;
}

void calculate_every_day_period(parking_period &_parking_period)
{
    int day_period = 0;
    int total_period = 0;
    for(int i = 0; i < _parking_period.parking_days.size(); i++)
    {
        day_period = 0;
        for(int j = 0; j < _parking_period.parking_days[i].all_hour_in_day.size(); j++)
        {
            day_period += ((_parking_period.parking_days[i].all_hour_in_day[j].minute * 60) + (_parking_period.parking_days[i].all_hour_in_day[j].second));
        }
        _parking_period.parking_days[i].day_period = day_period;
        total_period += day_period;
    }
    _parking_period.total_period = total_period;
}

std::vector<time_date_daily> turn_tow_date_into_vector_days(time_t payappTime, time_t entryTime)
{
    std::vector<time_date_daily> _parking_period;
    if(payappTime <= entryTime)
        return _parking_period;
    else
    {
        tm *a = localtime(&entryTime);
        tm _entryTime;
        _entryTime.tm_year = a->tm_year;
        _entryTime.tm_mon = a->tm_mon;
        _entryTime.tm_mday = a->tm_mday;
        _entryTime.tm_wday = a->tm_wday;
        _entryTime.tm_hour = a->tm_hour;
        _entryTime.tm_min = a->tm_min;
        _entryTime.tm_sec = a->tm_sec;
        tm *b = localtime(&payappTime);
        tm _payappTime;
        _payappTime.tm_year = b->tm_year;
        _payappTime.tm_mon = b->tm_mon;
        _payappTime.tm_mday = b->tm_mday;
        _payappTime.tm_wday = b->tm_wday;
        _payappTime.tm_hour = b->tm_hour;
        _payappTime.tm_min = b->tm_min;
        _payappTime.tm_sec = b->tm_sec;
        
        bool b_break = false;
        for(; _entryTime.tm_year <= _payappTime.tm_year; _entryTime.tm_year++)
        {
            mktime(&_entryTime);
            if((((_entryTime.tm_year + 1900) % 4 == 0) && ((_entryTime.tm_year + 1900) % 100 != 0)) || ((_entryTime.tm_year + 1900) % 400 == 0))
            {
                fin_of_month[1] = 29;
            }
            else
            {
                fin_of_month[1] = 28;
            }
            for(;  _entryTime.tm_mon < 12;  _entryTime.tm_mon++)
            {
                if ( _entryTime.tm_mon > _payappTime.tm_mon && _entryTime.tm_year == _payappTime.tm_year) 
                {
                    break;
                }
                if (b_break) 
                {
                    break;
                }
                for(; _entryTime.tm_mday <= fin_of_month[_entryTime.tm_mon]; _entryTime.tm_mday++)
                {
                    if (_entryTime.tm_mday > _payappTime.tm_mday && _entryTime.tm_mon == _payappTime.tm_mon && _entryTime.tm_year == _payappTime.tm_year) 
                    {
                        b_break = true;
                        break;
                    }
                    mktime(&_entryTime);
                    time_date_daily current_day;
                    current_day.year = _entryTime.tm_year;
                    current_day.month = _entryTime.tm_mon;
                    current_day.month_day = _entryTime.tm_mday;
                    current_day.weekday = _entryTime.tm_wday;
                    current_day.week_day = weekday[_entryTime.tm_wday];
                    if(_parking_period.size() == 0)
                    {
                        extract_day_hours(current_day.all_hour_in_day, entryTime, payappTime, "enter");
                    }
                    else
                    {
                        current_day.all_hour_in_day = extract_all_day_hours();
                    }
                    _parking_period.push_back(current_day);
                }
                if(!b_break)
                {
                    _entryTime.tm_mday = 1;
                    mktime(&_entryTime);
                }
            }
            if(!b_break)
            {
                _entryTime.tm_mon = 0;
                mktime(&_entryTime);
            }
        }
    }
    if(_parking_period.size() > 1)
    {
        extract_day_hours(_parking_period[_parking_period.size() - 1].all_hour_in_day, entryTime, payappTime, "exit");
    }
    return _parking_period;
}

void delete_period(parking_period &_parking_period ,int period_in_second)
{ 
    if(_parking_period.total_period > period_in_second)
    {
        _parking_period.total_period -= (period_in_second);
        int new_parking_period_length = 0;
        int hour_period = period_in_second / 3600;
        int minute_period = (period_in_second % 3600) / 60;
        int second_period = (period_in_second % 3600) % 60;
        if(period_in_second < _parking_period.parking_days[0].day_period)
        {
            _parking_period.parking_days[0].day_period -= period_in_second;
            new_parking_period_length = _parking_period.parking_days.size() - (period_in_second / 86400);
            hour_in_day new_entry_hour;
            if(second_period > _parking_period.parking_days[0].all_hour_in_day[0].second)
            {
                _parking_period.parking_days[0].all_hour_in_day[0].second += 60;
                _parking_period.parking_days[0].all_hour_in_day[0].minute--;
                new_entry_hour.second = _parking_period.parking_days[0].all_hour_in_day[0].second - second_period;
            }
            else
            {
                new_entry_hour.second = _parking_period.parking_days[0].all_hour_in_day[0].second - second_period;
            }
            if(minute_period > _parking_period.parking_days[0].all_hour_in_day[0].minute)
            {
                _parking_period.parking_days[0].all_hour_in_day[0].minute += 60;
                hour_period++;
                new_entry_hour.minute = _parking_period.parking_days[0].all_hour_in_day[0].minute - minute_period;
            }
            else
            {
                new_entry_hour.minute = _parking_period.parking_days[0].all_hour_in_day[0].minute - minute_period;
            }
            _parking_period.parking_days[0].all_hour_in_day.erase
            (
                _parking_period.parking_days[0].all_hour_in_day.begin(), 
                _parking_period.parking_days[0].all_hour_in_day.begin() + hour_period
            );
            _parking_period.parking_days[0].all_hour_in_day[0].minute = new_entry_hour.minute;
            _parking_period.parking_days[0].all_hour_in_day[0].second = new_entry_hour.second;
        }
        else
        {
            do
            {
                period_in_second -= _parking_period.parking_days[0].day_period;
                _parking_period.parking_days.erase(_parking_period.parking_days.begin(), _parking_period.parking_days.begin() + 1);
            }
            while(period_in_second >= _parking_period.parking_days[0].day_period);
            if(period_in_second > 0 && period_in_second < _parking_period.parking_days[0].day_period)
            {
                _parking_period.parking_days[0].day_period -= period_in_second;
                int new_parking_period_length = 0;
                int hour_period = period_in_second / 3600;
                int minute_period = (period_in_second % 3600) / 60;
                int second_period = (period_in_second % 3600) % 60;
                new_parking_period_length = _parking_period.parking_days.size() - (period_in_second / 86400);
                hour_in_day new_entry_hour;
                if(second_period > _parking_period.parking_days[0].all_hour_in_day[0].second)
                {
                    _parking_period.parking_days[0].all_hour_in_day[0].second += 60;
                    _parking_period.parking_days[0].all_hour_in_day[0].minute--;
                    new_entry_hour.second = _parking_period.parking_days[0].all_hour_in_day[0].second - second_period;
                }
                else
                {
                    new_entry_hour.second = _parking_period.parking_days[0].all_hour_in_day[0].second - second_period;
                }
                if(minute_period > _parking_period.parking_days[0].all_hour_in_day[0].minute)
                {
                    _parking_period.parking_days[0].all_hour_in_day[0].minute += 60;
                    hour_period++;
                    new_entry_hour.minute = _parking_period.parking_days[0].all_hour_in_day[0].minute - minute_period;
                }
                else
                {
                    new_entry_hour.minute = _parking_period.parking_days[0].all_hour_in_day[0].minute - minute_period;
                }
                _parking_period.parking_days[0].all_hour_in_day.erase
                (
                    _parking_period.parking_days[0].all_hour_in_day.begin(), 
                    _parking_period.parking_days[0].all_hour_in_day.begin() + hour_period
                );
                _parking_period.parking_days[0].all_hour_in_day[0].minute = new_entry_hour.minute;
                _parking_period.parking_days[0].all_hour_in_day[0].second = new_entry_hour.second;
            }
            
            new_parking_period_length = _parking_period.parking_days.size() - (period_in_second / 86400) - 1;
        }
        
        tm _entryTime;
        _entryTime.tm_year = _parking_period.parking_days[0].year;
        _entryTime.tm_mon = _parking_period.parking_days[0].month;
        _entryTime.tm_mday = _parking_period.parking_days[0].month_day;
        _entryTime.tm_hour = _parking_period.parking_days[0].all_hour_in_day[0].hour;
        _entryTime.tm_min = 60 - _parking_period.parking_days[0].all_hour_in_day[0].minute - 1;
        if(_parking_period.parking_days[0].all_hour_in_day[0].second == 0)
        {
            _entryTime.tm_min ++;
            _entryTime.tm_sec = 0;
        }
        else
        {
            _entryTime.tm_sec = 60 - _parking_period.parking_days[0].all_hour_in_day[0].second;
        }
        _parking_period.entryTime = _mktime_slow(&_entryTime);
    }
    else
    {
        _parking_period.parking_days.clear();
        _parking_period.total_period = 0;
    }
}

bool time_t_is_inside_period(time_t entryTime, time_t startTime, time_t endTime)
{    
    tm *a = localtime(&entryTime);
    tm _entryTime;
    _entryTime.tm_year = a->tm_year;
    _entryTime.tm_mon = a->tm_mon;
    _entryTime.tm_mday = a->tm_mday;
    _entryTime.tm_wday = a->tm_wday;
    _entryTime.tm_hour = a->tm_hour;
    _entryTime.tm_min = a->tm_min;
    _entryTime.tm_sec = a->tm_sec;
    
    tm *b = localtime(&startTime);
    tm _startTime;
    _startTime.tm_year = b->tm_year;
    _startTime.tm_mon = b->tm_mon;
    _startTime.tm_mday = b->tm_mday;
    _startTime.tm_wday = b->tm_wday;
    _startTime.tm_hour = b->tm_hour;
    _startTime.tm_min = b->tm_min;
    _startTime.tm_sec = b->tm_sec;
    
    tm *c = localtime(&endTime);
    tm _endTime;
    _endTime.tm_year = c->tm_year;
    _endTime.tm_mon = c->tm_mon;
    _endTime.tm_mday = c->tm_mday;
    _endTime.tm_wday = c->tm_wday;
    _endTime.tm_hour = c->tm_hour;
    _endTime.tm_min = c->tm_min;
    _endTime.tm_sec = c->tm_sec;
    if(_startTime.tm_year > 100 && _endTime.tm_year > 100)
    {
        if(endTime > startTime && entryTime >= startTime && entryTime < endTime)
        {
            return true;
        }
        else if(endTime == startTime && entryTime >= startTime && entryTime < startTime + 86400)
        {
            return true;
        }
        else 
            return false;
    }    
    else if((entryTime >= startTime && entryTime < endTime) || (startTime == endTime && _startTime.tm_year == 100 && _startTime.tm_mon == 0 && _startTime.tm_mday == 1))
    {
        return true;
    }
    else if(_startTime.tm_year == 100 && _startTime.tm_mon == 0 && _startTime.tm_mday == 1 && _endTime.tm_year == 100 && _endTime.tm_mon == 0 && _endTime.tm_mday == 1)
    {
        tm _entry_base_hour;
        _entry_base_hour.tm_year = 100;
        _entry_base_hour.tm_mon = 0;
        _entry_base_hour.tm_mday = 1;
        _entry_base_hour.tm_hour = _entryTime.tm_hour;
        _entry_base_hour.tm_min = _entryTime.tm_min;
        _entry_base_hour.tm_sec = _entryTime.tm_sec;
        time_t entry_base_hour = _mktime_slow(&_entry_base_hour);
        if(entry_base_hour >= startTime && entry_base_hour < endTime && startTime <= endTime)
            return true;
        else if(entry_base_hour >= startTime && !(entry_base_hour < endTime) && startTime > endTime)
            return true;
        else if(!(entry_base_hour >= startTime) && entry_base_hour < endTime && startTime > endTime)
            return true;
        else
            return false;
    }
    else if(_startTime.tm_year == _endTime.tm_year && _startTime.tm_mon == _endTime.tm_mon && _startTime.tm_mday == _endTime.tm_mday)
    {
        tm _entry_base_hour;
        _entry_base_hour.tm_year = _startTime.tm_year;
        _entry_base_hour.tm_mon = _startTime.tm_mon;
        _entry_base_hour.tm_mday = _startTime.tm_mday;
        _entry_base_hour.tm_hour = _entryTime.tm_hour;
        _entry_base_hour.tm_min = _entryTime.tm_min;
        _entry_base_hour.tm_sec = _entryTime.tm_sec;
        time_t entry_base_hour = _mktime_slow(&_entry_base_hour);
        if(entry_base_hour >= startTime && entry_base_hour < endTime && startTime <= endTime)
            return true;
        else if(entry_base_hour >= startTime && !(entry_base_hour < endTime) && startTime > endTime)
            return true;
        else if(!(entry_base_hour >= startTime) && entry_base_hour < endTime && startTime > endTime)
            return true;
        else
            return false;
    }
    else if(_startTime.tm_year == 100 && _startTime.tm_mon == 1 && _endTime.tm_year == 100 && _endTime.tm_mon == 1)
    {
        if(_entryTime.tm_wday == 0)
        {
             if(_entryTime.tm_wday + 7 >= _startTime.tm_mday && _entryTime.tm_wday + 7 <= _endTime.tm_mday)
                {
                    tm _entry_Week_day;
                    _entry_Week_day.tm_year = 100;
                    _entry_Week_day.tm_mon = 1;
                    _entry_Week_day.tm_mday = 1;
                    _entry_Week_day.tm_hour = _entryTime.tm_hour;
                    _entry_Week_day.tm_min = _entryTime.tm_min;
                    _entry_Week_day.tm_sec = _entryTime.tm_sec;
                    time_t entry_base_wday = _mktime_slow(&_entry_Week_day);
                    if(_startTime.tm_hour < _endTime.tm_hour && _entry_Week_day.tm_hour >= _startTime.tm_hour && _entry_Week_day.tm_hour < _endTime.tm_hour)
                    {
                        return true;
                    }
                    else if(_startTime.tm_hour > _endTime.tm_hour && (_entry_Week_day.tm_hour >= _startTime.tm_hour || _entry_Week_day.tm_hour < _endTime.tm_hour))
                    {
                        return true;
                    }
                    else
                        return false;
                }
            else
                return false;
        }
        else
        {
            if(_entryTime.tm_wday >= _startTime.tm_mday && _entryTime.tm_wday <= _endTime.tm_mday)
                {
                    
                    tm _entry_Week_day;
                    _entry_Week_day.tm_year = 100;
                    _entry_Week_day.tm_mon = 1;
                    _entry_Week_day.tm_mday = 1;
                    _entry_Week_day.tm_hour = _entryTime.tm_hour;
                    _entry_Week_day.tm_min = _entryTime.tm_min;
                    _entry_Week_day.tm_sec = _entryTime.tm_sec;
                    time_t entry_base_wday = _mktime_slow(&_entry_Week_day);
                    if(_startTime.tm_hour < _endTime.tm_hour && _entry_Week_day.tm_hour >= _startTime.tm_hour && _entry_Week_day.tm_hour < _endTime.tm_hour)
                    {
                        return true;
                    }
                    else if(_startTime.tm_hour > _endTime.tm_hour && (_entry_Week_day.tm_hour >= _startTime.tm_hour || _entry_Week_day.tm_hour < _endTime.tm_hour))
                    {
                        return true;
                    }
                    else
                        return false;
                }
            else
                return false;
        }
    }
    else
        return false;
}

void delete_week_day(parking_period &_parking_period ,time_t startTime, time_t endTime)
{
    tm *b = localtime(&startTime);
    tm _startTime;
    _startTime.tm_year = b->tm_year;
    _startTime.tm_mon = b->tm_mon;
    _startTime.tm_mday = b->tm_mday;
    _startTime.tm_wday = b->tm_wday;
    _startTime.tm_hour = b->tm_hour;
    _startTime.tm_min = b->tm_min;
    _startTime.tm_sec = b->tm_sec;
    
    tm *c = localtime(&endTime);
    tm _endTime;
    _endTime.tm_year = c->tm_year;
    _endTime.tm_mon = c->tm_mon;
    _endTime.tm_mday = c->tm_mday;
    _endTime.tm_wday = c->tm_wday;
    _endTime.tm_hour = c->tm_hour;
    _endTime.tm_min = c->tm_min;
    _endTime.tm_sec = c->tm_sec;
    
    for(int i = 0; i < _parking_period.parking_days.size(); i++)
    {       
        if(_parking_period.parking_days[i].weekday == 0)
        {
            if(_parking_period.parking_days[i].weekday + 7 >= _startTime.tm_mday && _parking_period.parking_days[i].weekday + 7 <= _endTime.tm_mday)
            {
                _parking_period.total_period -= _parking_period.parking_days[i].day_period;
                _parking_period.parking_days.erase(_parking_period.parking_days.begin() + i);
                i--;
            }
        }
        else
        {
            if(_parking_period.parking_days[i].weekday >= _startTime.tm_mday && _parking_period.parking_days[i].weekday <= _endTime.tm_mday)
            {
                _parking_period.total_period -= _parking_period.parking_days[i].day_period;
                _parking_period.parking_days.erase(_parking_period.parking_days.begin() + i);
                i--;
            }
        }
    }
    tm _entryTime;
    _entryTime.tm_year = _parking_period.parking_days[0].year;
    _entryTime.tm_mon = _parking_period.parking_days[0].month;
    _entryTime.tm_mday = _parking_period.parking_days[0].month_day;
    _entryTime.tm_hour = _parking_period.parking_days[0].all_hour_in_day[0].hour;
    _entryTime.tm_min = 60 - _parking_period.parking_days[0].all_hour_in_day[0].minute - 1;
    if(_parking_period.parking_days[0].all_hour_in_day[0].second == 0)
    {
        _entryTime.tm_min ++;
        _entryTime.tm_sec = 0;
    }
    else
    {
        _entryTime.tm_sec = 60 - _parking_period.parking_days[0].all_hour_in_day[0].second;
    }
    _parking_period.entryTime = _mktime_slow(&_entryTime);
}

int _get_parking_cost(parking_period _parking_period, std::vector<Block> block_list)
{
    int total_period = _parking_period.total_period;
    int total_amount = 0;
    int current_step = 0;
    int max;
    int enter_main_loop = 1;
    bool increase_by_next = false;
    
    std::cout << total_period << "\n";
    std::cout << "block_list.size() = " << block_list.size() << "\n";
    for(int i = 0; i < block_list.size(); i++)
    {
        std::cout << block_list[i].srNo << "\t" << print_block_type(block_list[i].type) << "\t"
                  << block_list[i].startTime << "\t" << block_list[i].endTime << "\t"
                  << block_list[i].period << "\t" << print_Relation(block_list[i].relation) << "\t"
                  << block_list[i].deduct << " \t" << block_list[i].cross_period << " \t" 
                  << block_list[i].amount << " \t"
                 << block_list[i].max_amount << "\t" << block_list[i].next <<"\n";
    }
    do
    {
        increase_by_next = false;
        Block currentBlock = block_list[current_step];
        if(!time_t_is_inside_period(_parking_period.entryTime, currentBlock.startTime, currentBlock.endTime))
        {
            //std::cout << "not between startTime and endTime for block_list[" << current_step << "] \n"; 
            if(currentBlock.type == Normal) 
            {
                tm *b = localtime(&currentBlock.startTime);
                tm _startTime;
                _startTime.tm_year = b->tm_year;
                _startTime.tm_mon = b->tm_mon;
                _startTime.tm_mday = b->tm_mday;
                _startTime.tm_wday = b->tm_wday;
                _startTime.tm_hour = b->tm_hour;
                _startTime.tm_min = b->tm_min;
                _startTime.tm_sec = b->tm_sec;
                
                tm *c = localtime(&currentBlock.endTime);
                tm _endTime;
                _endTime.tm_year = c->tm_year;
                _endTime.tm_mon = c->tm_mon;
                _endTime.tm_mday = c->tm_mday;
                _endTime.tm_wday = c->tm_wday;
                _endTime.tm_hour = c->tm_hour;
                _endTime.tm_min = c->tm_min;
                _endTime.tm_sec = c->tm_sec;
                if(_startTime.tm_year == 100 && _startTime.tm_mon == 1 && _endTime.tm_year == 100 && _endTime.tm_mon == 1)
                {
                    delete_week_day(_parking_period ,currentBlock.startTime, currentBlock.endTime);
                    total_period = _parking_period.total_period;
                }
                current_step++;
            }
            else if(currentBlock.type == Sub_amount_start) 
                current_step = (block_list[currentBlock.next].next == 255) ? currentBlock.next + 1 : block_list[currentBlock.next].next;
            //std::cout << "then we move to block_list[" << current_step << "] \n"; 
        }
        else
        {
            //std::cout << "between startTime and endTime for block_list[" << current_step << "] \n"; 
            if(currentBlock.type == Normal)
            {
                //std::cout << "block_list[" << current_step << "] == Normal \n";
                //std::cout << "compare (total period = " << total_period << ") and " 
                //          << "(block_list[" << current_step << "].period = " << currentBlock.period 
                //          << ") by (relation = " << print_Relation(currentBlock.relation) << ") "
                //          << " is " << compare(total_period, currentBlock.period, currentBlock.relation) <<"\n";
                if(compare(total_period, currentBlock.period, currentBlock.relation))
                {
                    total_amount += currentBlock.amount;
                    tm *b = localtime(&currentBlock.startTime);
                    tm _startTime;
                    _startTime.tm_year = b->tm_year;
                    _startTime.tm_mon = b->tm_mon;
                    _startTime.tm_mday = b->tm_mday;
                    _startTime.tm_wday = b->tm_wday;
                    _startTime.tm_hour = b->tm_hour;
                    _startTime.tm_min = b->tm_min;
                    _startTime.tm_sec = b->tm_sec;
                    
                    tm *c = localtime(&currentBlock.endTime);
                    tm _endTime;
                    _endTime.tm_year = c->tm_year;
                    _endTime.tm_mon = c->tm_mon;
                    _endTime.tm_mday = c->tm_mday;
                    _endTime.tm_wday = c->tm_wday;
                    _endTime.tm_hour = c->tm_hour;
                    _endTime.tm_min = c->tm_min;
                    _endTime.tm_sec = c->tm_sec;
                    if(_startTime.tm_year > 100 && _endTime.tm_year > 100)
                    {
                        delete_period(_parking_period ,_parking_period.parking_days[0].day_period);
                        total_period = _parking_period.total_period;
                        current_step = 0;
                    }
                    else if(_startTime.tm_year == 100 && _startTime.tm_mon == 1 && _endTime.tm_year == 100 && _endTime.tm_mon == 1)
                    {
                        delete_week_day(_parking_period ,currentBlock.startTime, currentBlock.endTime);
                        total_period = _parking_period.total_period;
                        current_step = 0;
                    }
                    else
                    {
                        if(currentBlock.deduct)
                        {
                            tm *a = localtime(&_parking_period.entryTime);
                            tm _entryTime;
                            _entryTime.tm_year = 100;
                            _entryTime.tm_mon = 0;
                            _entryTime.tm_mday = 1;
                            _entryTime.tm_hour = a->tm_hour;
                            _entryTime.tm_min = a->tm_min;
                            _entryTime.tm_sec = a->tm_sec;
                            time_t new_entryTime = _mktime_slow(&_entryTime);
                            if((int)std::difftime(currentBlock.endTime, new_entryTime) > 0)
                            {
                                if(currentBlock.startTime > currentBlock.endTime)
                                {   
                                    total_period -= min(currentBlock.period,(int)std::difftime(currentBlock.endTime, new_entryTime));
                                    delete_period(_parking_period ,min(currentBlock.period,(int)std::difftime(currentBlock.endTime, new_entryTime)));
                                }
                                else
                                {   
                                    total_period -= currentBlock.period;
                                    delete_period(_parking_period ,currentBlock.period);
                                }
                            }
                            else
                            {
                                if(currentBlock.startTime > currentBlock.endTime)
                                {
                                    total_period -= min(currentBlock.period,((int)std::difftime(currentBlock.endTime, new_entryTime) + 86400));
                                    delete_period(_parking_period ,min(currentBlock.period,((int)std::difftime(currentBlock.endTime, new_entryTime) + 86400)));
                                }
                                else
                                {   
                                    total_period -= currentBlock.period;
                                    delete_period(_parking_period ,currentBlock.period);
                                }
                            }

                            //std::cout << "total_period = " << total_period << "\n";
                            //std::cout << "total_amount = " << total_amount << "\n";
                        }
                        current_step = (currentBlock.next == 255) ? current_step + 1 : currentBlock.next;
                        
                    }
                }
                else
                {
                    current_step++;
                }
            }
            else if(currentBlock.type == Sub_amount_start)
            {
                //std::cout << "block_list[" << current_step << "] == Sub_amount_start \n";
                max = block_list[currentBlock.next].max_amount == 0 ? 0x7FFFFFFF : block_list[currentBlock.next].max_amount;
                int maxPeriod = block_list[currentBlock.next].period;
                int subPeriod = 0;
                int i = 1;
                int subAmount = 0;
                //std::cout << "compare (total period = " << total_period << ") and " 
                //              << "(block_list[" << current_step << "].period = " << maxPeriod 
                //              << ") by (relation = " << print_Relation(block_list[currentBlock.next].relation) << ") "
                //              << " is " << compare(total_period, maxPeriod, block_list[currentBlock.next].relation) <<"\n";
                if(!compare(total_period, maxPeriod, block_list[currentBlock.next].relation))
                {
                    current_step = (block_list[currentBlock.next].next == 255) ? currentBlock.next + 1 : block_list[currentBlock.next].next;
                //    std::cout << "not enter loop with current_step = " << current_step << "\n";
                }
                else
                {
                    while (current_step + i < currentBlock.next && total_period > 0)
                    {
                        //std::cout << "compare (total period = " << total_period << ") and " 
                        //      << "(block_list[" << current_step << "].period = " << currentBlock.period 
                        //      << ") by (relation = " << print_Relation(currentBlock.relation) << ") "
                        //      << " is " << compare(total_period, currentBlock.period, currentBlock.relation) << "\n";
                        if(compare(total_period, block_list[current_step + i].period, block_list[current_step + i].relation))
                        {
                            //std::cout << "relation Correct for block[" << current_step << "]\n"; 
                            //std::cout << "current_step + i = " << current_step + i << "\n"; 
                            subAmount += block_list[current_step + i].amount;
                            total_period -= block_list[current_step + i].period;
                            delete_period(_parking_period ,block_list[current_step + i].period);
                            subPeriod += block_list[current_step + i].period;
                            //std::cout << "total_period = " << total_period << "\n";
                            //std::cout << "subAmount = " << subAmount << "\n";
                            if(!time_t_is_inside_period(_parking_period.entryTime, block_list[current_step].startTime, block_list[current_step].endTime))
                            {
                                current_step = (block_list[currentBlock.next].next == 255) ? currentBlock.next + 1 : block_list[currentBlock.next].next;
                                //std::cout << "end loop with current_step = " << current_step << "\n";
                                break;
                            }
                        }
                        else
                        {
                            i++;
                        }
                    }
                    if (subAmount > max) subAmount = max;
                    total_amount += subAmount;
                    //std::cout << "total_period = " << total_period << "\n";
                    //std::cout << "total_amount = " << total_amount << "\n";
                }
            }
            else if(currentBlock.type == Sub_amount_end)
            {
                current_step = (currentBlock.next == 255) ? current_step + 1 : currentBlock.next;
            }
            if (total_period <= 0) break;
        }
    } 
    while (current_step < block_list.size() && total_period > 0);
    return total_amount;
}


Proof::Proof(MYSQL *_mysql, int _rule_name_number, int site_address) : dashou(), parser()
{
    site_address = site_address;
    mysql = _mysql;
    rule_name_number = _rule_name_number;
    std::cout << "rule name number = " << rule_name_number << "\n";
    rule_name_hourly_type tmp_rule_name_hourly(mysql);
    for (int i = 0; i < 16; i++)
    {
        tmp_rule_name_hourly.Select_rule_name_hourly_type_by_rule_serial(i);
        if(tmp_rule_name_hourly.aid > 0 && tmp_rule_name_hourly.gid > 0 && tmp_rule_name_hourly.rule_serial < 16)
        {
            rule_name_hourly_list.push_back(tmp_rule_name_hourly);
            tmp_rule_name_hourly.aid = 0;
            tmp_rule_name_hourly.gid = 0;
            tmp_rule_name_hourly.rule_serial = 255;
        }
    }
    rule_step_hourly_type tmp_rule_step_hourly(mysql);
    for (int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            tmp_rule_step_hourly.Select_rule_step_hourly_type_by_rule_block_serial(i, j);
            if(tmp_rule_step_hourly.gid > 0 && tmp_rule_step_hourly.rule_serial < 16 && tmp_rule_step_hourly.block_serial < 256)
            {
                rule_step_hourly_list.push_back(tmp_rule_step_hourly);
                tmp_rule_step_hourly.gid = 0;
                tmp_rule_step_hourly.rule_serial = 255;
                tmp_rule_step_hourly.block_serial = 256;
            }
        }
    }
    block_list.clear();
    for(int i = 0; i < rule_step_hourly_list.size(); i++)
    {
        if(rule_step_hourly_list[i].rule_serial == rule_name_number)
        {
            Block block;
            make_block(block, rule_step_hourly_list[i].block_serial, get_block_type(rule_step_hourly_list[i].type),
                    rule_step_hourly_list[i].duration, get_block_Relation(rule_step_hourly_list[i].relation),
                    rule_step_hourly_list[i].deduct, rule_step_hourly_list[i].sum, rule_step_hourly_list[i].max_sum,
                    rule_step_hourly_list[i].next_serial, rule_step_hourly_list[i].starttime, rule_step_hourly_list[i].endtime);
            block_list.push_back(block);
                        
            std::cout << block_list[block_list.size()-1].srNo << "\t" << print_block_type(block_list[block_list.size()-1].type) << "\t"
                              << dashou.Print_time(block_list[block_list.size()-1].startTime) << "\t" << dashou.Print_time(block_list[block_list.size()-1].endTime) << "\t"
                              << block_list[block_list.size()-1].period << "\t" << print_Relation(block_list[block_list.size()-1].relation) << "\t"
                              << block_list[block_list.size()-1].deduct << " \t" << block_list[block_list.size()-1].cross_period << " \t" 
                              << block_list[block_list.size()-1].amount << " \t"
                             << block_list[block_list.size()-1].max_amount << "\t" << block_list[block_list.size()-1].next <<"\n";    
        }
    }
}

Proof::Proof(std::string _ticket, std::string _plate, int _proof_entry_exit_type, int _ticket_type, time_t time, int _serial, int entry_serial): dashou(), parser()
{
	ticket = _ticket;
	plate = _plate;
        proof_entry_exit_type = _proof_entry_exit_type;
	ticket_type = _ticket_type;
	entryTime = time;
        payappTime = time;
        exitTime = time;
	serial = _serial;
	Entry_serial = entry_serial;
	Status = "In";
        event_time = time;
        event_serial_number = entry_serial;
}

Proof::Proof(std::string _ticket, std::string _plate, int _proof_entry_exit_type, int _ticket_type, time_t time, int event_serial): dashou(), parser()
{
	ticket = _ticket;
	plate = _plate;
        proof_entry_exit_type = _proof_entry_exit_type;
	ticket_type = _ticket_type;
        payappTime = time;
        exitTime = time;
	Exit_serial = event_serial;
        APPpay_serial = event_serial;
	Status = "In";
        event_time = time;
        event_serial_number = event_serial;
}

void Proof::exit()
{
	Status = "Out";
	exitTime = time(0);
}

void Proof::exit(time_t t)
{
	Status = "Out";
	exitTime = t;
}

std::string Proof::get_TicketASCIIHEX()
{
    std::string ticket_ascii_hex_lower;
    std::string ticket_ascii_hex = "00000000000000000000000000000000000000";
    if(ticket == "                                      " || ticket == "" || ticket == "00000000000000000000000000000000000000")
    {
        return ticket_ascii_hex;
    }
    else
    {
        for (int i = 0; ticket[i] != '\0'; i++)
        {
            char ch = ticket[i];
            int in = (int)ch;
            std::stringstream stream;
            stream << std::hex << in;
            ticket_ascii_hex_lower += stream.str();
        }
        for (int i = 0; ticket_ascii_hex_lower[i] != '\0'; i++)
        {
            ticket_ascii_hex[i] = toupper(ticket_ascii_hex_lower[i]);
        }
    }
    return ticket_ascii_hex;
}

std::string Proof::get_StatusASCIIHEX()
{
    std::string status_ascii_hex_lower;
    std::string status_ascii_hex = "000000";
    if(site_status == "      " || site_status == "" || site_status == "000000")
    {
        return status_ascii_hex;
    }
    else
    {
        for (int i = 0; i < 3 ; i++)//site_status[i] != '\0'
        {
            char ch = site_status[i];
            int in = (int)ch;
            std::stringstream stream;
            stream << std::hex << in;
            status_ascii_hex_lower += stream.str();
        }
        for (int i = 0; i < 6 ; i++) // status_ascii_hex_lower[i] != '\0'
        {
            status_ascii_hex[i] = toupper(status_ascii_hex_lower[i]);
        }
    }
    return status_ascii_hex;
}

std::string Proof::get_plate()
{
    if (plate == "")
            return "No Plate!";
    return plate;
}

std::string Proof::get_PlateASCIIHEX()
{
    std::string plate_ascii_hex_lower;
    std::string plate_ascii_hex = "000000000000000000000000";
    if(plate == "                        " || plate == "" || plate == "000000000000000000000000")
    {
        return plate_ascii_hex;
    }
    else
    {
        for (int i = 0; plate[i] != '\0'; i++)
        {
            char ch = plate[i];
            int in = (int)ch;
            std::stringstream stream;
            stream << std::hex << in;
            plate_ascii_hex_lower += stream.str();
        }
        for (int i = 0; plate_ascii_hex_lower[i] != '\0'; i++)
        {
            plate_ascii_hex[i] = toupper(plate_ascii_hex_lower[i]);
        }
    }
    return plate_ascii_hex;
}

duration Proof::calculate_TimeSpan_duration()
{
	long double duration = std::difftime(payappTime, entryTime);
	TimeSpan_duration.hour	= duration / 3600;
	TimeSpan_duration.min	= ((int)duration % 3600) / 60;
	TimeSpan_duration.sec	= ((int)duration % 3600) % 60;
	return TimeSpan_duration;
}

duration Proof::seconds_To_duration(unsigned int seconds)
{
    duration result;
	result.hour = seconds / 3600;
	result.min = ((int)seconds % 3600) / 60;
	result.sec = ((int)seconds % 3600) % 60;
	return result;
}

unsigned int Proof::get_parking_time_is_sec()
{
	Current_Parking_Time = std::difftime(payappTime, entryTime);
	return Current_Parking_Time;
}

duration Proof::calculate_Totaltime_duration()
{
	long double duration = std::difftime(exitTime, entryTime);
	Totaltime.hour = duration / 3600;
	Totaltime.min = ((int)duration % 3600) / 60;
	Totaltime.sec = ((int)duration % 3600) % 60;
	return Totaltime;
}

unsigned int Proof::get_Totaltime_is_sec()
{
	Current_Parking_Time = std::difftime(exitTime, entryTime);
	return Current_Parking_Time;
}

int Proof::get_parking_cost(time_t enter_parking ,time_t pay_t_parking)
{
    entryTime = enter_parking;
    payappTime = pay_t_parking;
    
    dashou.Print_time(entryTime);    
    dashou.Print_time(payappTime);  
    
    parking_period _parking_period;

    std::vector<time_date_daily> parking_days = turn_tow_date_into_vector_days(pay_t_parking, enter_parking);
    if(parking_days.size() == 0) 
    {
        std::cout << "parking_days.size == 0" << "\n";
        return  0;
    }
    _parking_period.entryTime = entryTime;
    _parking_period.payappTime = payappTime;
    _parking_period.parking_days = parking_days;
    calculate_every_day_period(_parking_period);
    Current_Parking_Fee = _get_parking_cost(_parking_period, block_list);
    return Current_Parking_Fee;
}

std::string Proof::get_EntryTime()
{
	tm *time = localtime(&entryTime);
	std::string s = std::to_string(time->tm_year + 1900) + "-" + std::to_string(time->tm_mon + 1) + "-" + std::to_string(time->tm_mday)
		+ " " + std::to_string(time->tm_hour % 12) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec);
	if (time->tm_hour > 12)
		s += " PM";
	else
		s += " AM";
	return s;
}

std::string Proof::get_ExitTime()
{
	tm *time = localtime(&exitTime);
	std::string s = std::to_string(time->tm_year + 1900) + "-" + std::to_string(time->tm_mon + 1) + "-" + std::to_string(time->tm_mday)
		+ " " + std::to_string(time->tm_hour % 12) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec);
	if (time->tm_hour > 12)
		s += " PM";
	else
		s += " AM";
	return s;
}

std::string Proof::get_PayAPPTime()
{
	tm *time = localtime(&payappTime);
	std::string s = std::to_string(time->tm_year + 1900) + "-" + std::to_string(time->tm_mon + 1) + "-" + std::to_string(time->tm_mday)
		+ " " + std::to_string(time->tm_hour % 12) + ":" + std::to_string(time->tm_min) + ":" + std::to_string(time->tm_sec);
	if (time->tm_hour > 12)
		s += " PM";
	else
		s += " AM";
	return s;
}

int Proof::get_rest_cost()
{
	rest_cost = Current_Parking_Fee - Amount_Received;
        Current_Parking_Fee = rest_cost;
	return rest_cost;
}


