#include "DashouParser.h"
#define min(a,b) ((a)<(b)?(a):(b))

enum block_type { Normal, Sub_amount_start, Sub_amount_end };
enum Relation { Great, GreatOrEqual, Less, LessOrEqual};

struct Block
{
    int srNo;
    block_type type;
    time_t startTime, endTime;
    int period;
    Relation relation;
    bool deduct, cross_period;
    int amount, max_amount;
    int next;
    time_t sTime;
    time_t eTime;

};

struct hour_in_day
{
    int hour;
    int minute;
    int second;
};

struct time_date_daily
{
    int year;
    int month;
    int month_day;
    int weekday;
    const char * week_day;
    std::vector<hour_in_day> all_hour_in_day;
    int day_period;
};

struct parking_period
{
    time_t entryTime = 0;
    time_t payappTime = 0;
    std::vector<time_date_daily> parking_days;
    int total_period;
};

struct duration
{
	int hour = 0;
	int min = 0;
	int sec = 0;
};

class Proof
{
public:
        
        MYSQL *mysql;
        int rule_name_number = 0;
        std::vector<rule_name_hourly_type> rule_name_hourly_list;
        std::vector<rule_step_hourly_type> rule_step_hourly_list;
	DashouParser parser;
	Dashou dashou;
        
	unsigned int rest_cost = 0;
	unsigned int total_in_sec = 0;
	duration TimeSpan_duration;
	duration Totaltime;
	int zone_id = 0xff;
        
	std::string TicketASCIIHEX = "";
	std::string PlateASCIIHEX = "";
	std::string Type = "";
	std::string EntryTime = "";
	std::string ExitTime = "";
	std::string PayAPPTime = "";
	std::string Status = "";

	int serial = 0;
        int control = -1;                                   //		length 1
        int proof_entry_exit_type = -1;                     //		length 1
        int site_address = 0;                               //		length 1
        int ticket_type = -1;                               //		length 1
        std::string ticket = "";                            //		length 19
        std::string plate = "";                             //          length 12
        int account_type = -1;                              //		length 1
        int Presence_Sign = -1;                             //		length 1
        time_t entryTime = 0;                               //          length 6
	int Entry_serial = 0;                               //          length 2
        time_t exitTime = 0;                                //          length 6
	int Exit_serial = 0;                                //          length 2
        time_t payappTime = 0;                              //          length 6
	int APPpay_serial = 0;                              //          length 2
        unsigned int Amount_Received = 0;                   //       	length 4
        int Charge_Type_Charging_Standard = 0;              //		length 1
        time_t Start_Time = 0;                              //          length 6
        time_t End_Time = 0;                                //          length 6
        unsigned int Prepay_Account_Balance = 0;            //          length 4
        int Prepay_Account_Charge_Type = 0;                 //          length 1
        int Prepay_Account_License_Plate_Binding = 0;       //          length 1
        int Access_Control_Group_Number = 0;                //          length 1
        int Parking_Space_Group_Number = 0;                 //          length 2
        int Parking_Space_Group_Maximum_Space_Number = 0;   //          length 2
        int Parking_Space_Current_Occupied_Space_Number = 0;//          length 2
        int Time_Group = 0;                                 //          length 1
        int Site_in_Site_Area_Group_Number = 0;             //          length 1
        time_t Site_in_Site_Enter_Time;                     //          length 6
        int Site_in_Site_Enter_Serial_Number = 0;           //          length 2
        time_t Site_in_Site_Exit_Time = 0;                  //          length 6
        int Site_in_Site_Exit_Serial_Number = 0;            //          length 2
        unsigned int Online_Order_Serial_Number_low = 0;    //          length 4
        unsigned int Online_Order_Serial_Number_high = 0;   //          length 4
        std::string Parking_Space_Number = 
                "00000000000000000000000000000000";         //          length 16
        std::string Hourly_Carpark_Ticket_Number_String =
                "0000000000000000000000000000000000000000"; //          length 20
        time_t Expiry_Time_for_Charge_Upper_Limit = 0;      //          length 6
        unsigned int Received_Amount_Subtotal = 0;          //          length 4
        unsigned int Current_Parking_Time = 0;              //          length 4
        unsigned int Current_Parking_Fee = 0;               //          length 4
        int Let_pass_or_not = 0;                            //          length 1	(1=true) Let pass or not
        int Result_of_Error_Response = 0;                   //          length 1
        time_t Recent_Period_Start_Time;                    //          length 6
        time_t Recent_Period_End_Time;                      //          length 6
        unsigned int Recent_Period_Length_Seconds = 0;      //          length 4
        int Entry_Address = 0;                              //          length 1
        int Cashier_Address = 0;                            //          length 1
        int Exit_Address = 0;                               //          length 1
        int Site_in_Site_Entry_Address = 0;                 //          length 1
        int Site_in_Site_Exit_Address = 0;                  //          length 1
        unsigned int Parking_Coupon_Time_Length = 0;        //          length 4
        int Parking_Coupon_Limit_Status = 0;                //          length 1
        unsigned int Credit_Value_Total = 0;                //          length 4
        unsigned int Credit_Value_Deduct = 0;               //          length 4
        unsigned int Coupon_Value  = 0;                     //          length 4
        std::string Reserved = 
                "000000000000000000000000000000000000";     //          length 18
        std::string site_status = "";
        int site_status_Tail = 0;
        
        time_t event_time = 0;
        int event_serial_number = 0;
        int Out_Type = 0;
        int Payment_type = 0;
        unsigned int should_pay = 0;                        //          length 4
        unsigned int already_pay = 0;                       //          length 4
        int payment_site = 0;
        
        
        int Fo_AccountDatasLib = 255;
        int MonthlyTypeSerial = 0;
        int VIP_Flag = 255;
        int InnerGarageGroup = 255;
        int PrepaidChargeTypeID = 255;
        
	Proof(MYSQL *_mysql, int _rule_name_number, int site_address);

        Proof(std::string _ticket, std::string _plate, int _proof_entry_exit_type, int _ticket_type, time_t time, int _serial, int entry_serial);

	Proof(std::string _ticket, std::string _plate, int _proof_entry_exit_type, int _ticket_type, time_t time, int event_serial);

	void exit();

	void exit(time_t t);

	std::string get_plate();

	std::string get_PlateASCIIHEX();

	std::string get_TicketASCIIHEX();
        
        std::string get_StatusASCIIHEX();

	duration calculate_TimeSpan_duration();

	unsigned int get_parking_time_is_sec();

	duration calculate_Totaltime_duration();

	unsigned int get_Totaltime_is_sec();

	int get_parking_cost(time_t enter_parking ,time_t pay_t_parking);

	int get_rest_cost();

	std::string get_EntryTime();

	std::string get_ExitTime();

	std::string get_PayAPPTime();
        
        duration seconds_To_duration(unsigned int duration);
        
private:

};
