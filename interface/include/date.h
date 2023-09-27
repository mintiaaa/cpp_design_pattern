#ifndef DATE_H
#define DATE_H

#include <stdexcept>

/**
 * @brief 日付を表す値オブジェクト(初期化時のエラー処理方法確認のため実装したが未使用)
 *
 */
class Date
{
protected:
    int month_;
    int day_;
    int hour_;
    int minute_;
    int second_;
public:
    // コンストラクタで代入前にエラー処理を行う
    Date(const int month, const int day, const int hour, const int minute, const int second)
    {
        if(month_ < 1 || month_ > 12){
            throw std::invalid_argument("[invalid argument error] month must be between 1 and 12");
        }
        if(day_ < 1 || day_ > 31){
            throw std::invalid_argument("[invalid argument error] day must be between 1 and 31");
        }
        if(hour_ < 0 || hour_ > 24){
            throw std::invalid_argument("[invalid argument error] hour must be between 0 and 24");
        }
        if(minute_ < 0 || minute_ > 60){
            throw std::invalid_argument("[invalid argument error] minute must be between 0 and 60");
        }
        if(second_ < 0 || second_ > 60){
            throw std::invalid_argument("[invalid argument error] second must be between 0 and 60");
        }
        month_ = month;
        day_ = day;
        hour_ = hour;
        minute_ = minute;
        second_ = second;
    }
};

#endif // DATE_H
