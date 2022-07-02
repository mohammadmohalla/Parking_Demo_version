#include "Dashou.h"

Dashou::Dashou()
{

}

Dashou::~Dashou()
{

}

std::string Dashou::to_String_X8(unsigned int v)
{
	v &= 0xffffffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(8)
		<< std::hex << v;
	std::string v_temp_string = stream.str();
	std::string v_ = "        ";
	// s.Substring(6, 2) + s.Substring(4, 2) + s.Substring(2, 2) + s.Substring(0, 2)
	v_[0] = toupper(v_temp_string[6]);
	v_[1] = toupper(v_temp_string[7]);
	//
	v_[2] = toupper(v_temp_string[4]);
	v_[3] = toupper(v_temp_string[5]);
	//
	v_[4] = toupper(v_temp_string[2]);
	v_[5] = toupper(v_temp_string[3]);
	//
	v_[6] = toupper(v_temp_string[0]);
	v_[7] = toupper(v_temp_string[1]);
	//
	return v_;
}

std::string Dashou::to_String_X4(int v)
{
	v &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << v;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";
	// s.Substring(2, 2) + s.Substring(0, 2
	v_[0] = toupper(v_temp_string[2]);
	v_[1] = toupper(v_temp_string[3]);
	//
	v_[2] = toupper(v_temp_string[0]);
	v_[3] = toupper(v_temp_string[1]);
	return v_;
}

std::string Dashou::to_String_X2(int v)
{
	v &= 0xff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(2)
		<< std::hex << v;
	std::string v_temp_string = stream.str();
	std::string v_ = "  ";
	for (int i = 0; v_temp_string[i] != '\0'; i++)
	{
		v_[i] = toupper(v_temp_string[i]);
	}
	return v_;
}

std::string Dashou::to_String_00(int v)
{
	if (v < 10)
	{
		return "0" + std::to_string(v);
	}
	else
		return std::to_string(v);
}

char* Dashou::StringToByteArray(std::string hex)
{
	std::string temp = "";
	char *val = new char[hex.length() + 1];
	int x[10000] = { 0 };
	std::stringstream ss;
	for (int i = 0; hex[i] != '\0'; i += 2)
	{
		temp += hex[i];
		temp += hex[i + 1];
		ss << std::hex << temp;
		ss >> x[i / 2];
		val[i / 2] = x[i / 2];
		temp = "";
		ss.clear();
	}
	return val;
}

std::string Dashou::int2HexStrReverse2Byte(int v)
{
	v &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << v;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";

	for (int i = 0; v_temp_string[i] != '\0'; i++)
		v_[i] = toupper(v_temp_string[(i + 2) % 4]);
	return v_;
}

std::string Dashou::calcLength(int length)
{
	length &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << length;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";
	for (int i = 0; v_temp_string[i] != '\0';i++)
		v_[i] = toupper(v_temp_string[(i + 2) % 4]);
	return v_;
}

std::string Dashou::calcSerial(int serial)
{
	serial &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << serial;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";
	for (int i = 0; v_temp_string[i] != '\0'; i++)
		v_[i] = toupper(v_temp_string[(i + 2) % 4]);
	return v_;
}

std::string Dashou::calcCurrentTime(time_t now)
{
    if(std::difftime(now, Reference_date) == 0) return "000000000000";
    if(now == 0) return "000000000000";
    tm *my_time = localtime(&now);
    std::string date = "now = ";
    date += std::to_string(my_time->tm_year + 1900);
    date += "-";
    date += std::to_string(my_time->tm_mon + 1);
    date += "-";
    date += std::to_string(my_time->tm_mday);
    date += " ";
    date += std::to_string(my_time->tm_hour);
    date += ":";
    date += std::to_string(my_time->tm_min);
    date += ":";
    date += std::to_string(my_time->tm_sec);
    date += " ";
    if (my_time->tm_hour > 12)
            date += "PM";
    else
            date += "AM";

    if (debug)
            std::cout << date << std::endl;


    std::stringstream hex_date;
    hex_date << std::setfill('0') << std::setw(2) << std::hex << (my_time->tm_year - 100)
            << std::setfill('0') << std::setw(2) << std::hex << (my_time->tm_mon + 1)
            << std::setfill('0') << std::setw(2) << std::hex << my_time->tm_mday
            << std::setfill('0') << std::setw(2) << std::hex << (my_time->tm_hour)
            << std::setfill('0') << std::setw(2) << std::hex << my_time->tm_min
            << std::setfill('0') << std::setw(2) << std::hex << my_time->tm_sec;

    std::string v_temp_string = hex_date.str();
    std::string v_ = "123456789ABC";;
    for (int i = 0; v_temp_string[i] != '\0'; i++)
    {
            v_[i] = toupper(v_temp_string[i]);
    }
    return v_;
}

std::string Dashou::Print_time(time_t now)
{
    if(now == 0) return "000000000000";
    tm *my_time = localtime(&now);
    std::string date = "";
    date += std::to_string(my_time->tm_year + 1900);
    date += "-";
    date += to_String_00(my_time->tm_mon + 1);
    date += "-";
    date += to_String_00(my_time->tm_mday);
    date += " ";
    date += to_String_00(my_time->tm_hour);
    date += ":";
    date += to_String_00(my_time->tm_min);
    date += ":";
    date += to_String_00(my_time->tm_sec);
    return date;

}

std::string Dashou::calcChecksum_broadcast()
{
	return "FF0F";
}

std::string Dashou::calcChecksum_server(int length, int serial, int function, int year, int month, int day, int hour)
{
	int header = 335;    // AA + A5 = 14F
	int checksum = header + (length & 255) + ((length >> 8) & 255) + (serial & 255) + ((serial >> 8) & 255) + function + year + month + day + hour;
	checksum &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << checksum;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";
	for (int i = 0; v_temp_string[i] != '\0'; i++)
		v_[i] = toupper(v_temp_string[(i + 2) % 4]);
	return v_;
}

std::string Dashou::calcChecksum_client(int length, int serial, int function1, int function2)
{
	int header = 335;    // AA + A5 = 14F
	int city = 165;      // 30 + 75 = A5
	int checksum = header + (length & 255) + ((length >> 8) & 255) + (serial & 255) + ((serial >> 8) & 255) + function1 + function2 + city;
	checksum &= 0xffff;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4)
		<< std::hex << checksum;
	std::string v_temp_string = stream.str();
	std::string v_ = "    ";
	for (int i = 0; v_temp_string[i] != '\0';i++)
		v_[i] = toupper(v_temp_string[(i + 2) % 4]);
	return v_;
}

unsigned int Dashou::get_TABLET_cost(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4)
{
	return ((0x1000000 * data4) + (0x10000 * data3) + (0x100 * data2) + data1);
}

unsigned int Dashou::get_TABLET_PAID(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4)
{
	return ((0x1000000 * data4) + (0x10000 * data3) + (0x100 * data2) + data1);
}

unsigned int Dashou::get_X2_Number(unsigned char data1, unsigned char data2)
{
	return ((0x100 * data2) + data1);
}

unsigned int Dashou::get_X4_Number(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4)
{
    return ((0x1000000 * data4) + (0x10000 * data3) + (0x100 * data2) + data1);
}

std::string Dashou::ticket_types_To_string(int ticket_type)
{
    switch(ticket_type)
    {
        case TICKET_TYPE_NO_TICKET:
        {
            return "TICKET TYPE NO TICKET";
	} 
        break;
        case TICKET_TYPE_TRANSPORTATION_CARD:
        { 
            return "TICKET TYPE TRANSPORTATION CARD";
	} 
        break;
        case TICKET_TYPE_CHINA_UNION_CARD:
        { 
            return "TICKET TYPE CHINA UNION CARD";
	} 
        break;
        case TICKET_TYPE_INTERNAL_CARD:
        { 
            return "TICKET TYPE INTERNAL CARD";
	} 
        break;
        case TICKET_TYPE_TICKET:
        { 
            return "TICKET TYPE TICKET";
	} 
        break;
        case TICKET_TYPE_QR_CODE:
        { 
            return "TICKET TYPE QR CODE";
        } 
        break;
        default:
        {
            return "TICKET TYPE IS UNKNOWN";
        }
        break;
    }
}

std::string Dashou::account_types_To_string(int account_type)
{
    switch(account_type)
    {
        case times_based_monthly_parking:
        { 
            return "times based monthly parking";
	} 
        break;
        case prepaid_based_monthly_parking:
        { 
            return "prepaid based monthly parking";
	} 
        break;
        case hourly_based_monthly_parker:
        { 
            return "hourly based monthly parker";
	} 
        break;
        case hourly_parker:
        { 
            return "hourly parker";
	} 
        break;
        default:
        {
            return "account type is unknown";
        }
        break;

    }
}

std::string Dashou::ENTRY_EXIT_TYPE_To_string(int proof_entry_exit_type)
{
    switch(proof_entry_exit_type)
    {
        case undefine_inout_type:
        { 
            return "undefine inout type";
        } 
        break;
        case monthly_by_num:
        { 
            return "monthly by num";
        } 
        break;
        case monthly_by_store:
        { 
            return "monthly by store";
        } 
        break;
        case monthly_to_hourly:
        { 
            return "monthly to hourly";
        } 
        break;
        case monthly_by_time:
        { 
            return "monthly by time";
        } 
        break;
        case monthly_catch_hourly:
        { 
            return "monthly catch hourly";
        } 
        break;
        case stagger_time_park:
        { 
            return "stagger time park";
        } 
        break;
        case inner_monthly:
        { 
            return "inner monthly";
        } 
        break;
        case stagger_time_too_soon:
        { 
            return "stagger time too soon";
        } 
        break;
        case please_avoid:
        { 
            return "please avoid";
        } 
        break;
        case loss_monthly:
        { 
            return "loss monthly";
        } 
        break;
        case space_not_enough:
        { 
            return "space not enough";
        } 
        break;
        case access_limit:
        { 
            return "access limit";
        } 
        break;
        case repeat_in_out:
        { 
            return "repeat in out";
        } 
        break;
        case monthly_full:
        { 
            return "monthly full";
        } 
        break;
        case filtered:
        { 
            return "filtered";
        } 
        break;
        case card_plate_mismatch:
        { 
            return "card plate mismatch";
        } 
        break;
        case store_not_enough:
        { 
            return "store not enough";
        } 
        break;
        case num_not_enough:
        { 
            return "num not enough";
        } 
        break;
        case monthly_overdue:
        { 
            return "monthly overdue";
        } 
        break;
        case being:
        { 
            return "being";
        } 
        break;
        case ticket_hourly:
        { 
            return "ticket hourly";
        } 
        break;
        case card_hourly:
        { 
            return "card hourly";
        } 
        break;
        case plate_hourly:
        { 
            return "plate hourly";
        } 
        break;
        case transportation_card_hourly:
        { 
            return "transportation card hourly";
        } 
        break;
        case unionpay_card_hourly:
        { 
            return "unionpay card hourly";
        } 
        break;
        case QR_code_hourly:
        { 
            return "QR code hourly";
        } 
        break;
        case card_hourly_2:
        { 
            return "card hourly 2";
        } 
        break;
        case reserve_hourly:
        { 
            return "reserve hourly";
        } 
        break;
        case inner_hourly:
        { 
            return "inner hourly";
        } 
        break;
        case out_prices:
        { 
            return "out prices";
        } 
        break;
        case reserve_overdue:
        { 
            return "reserve overdue";
        } 
        break;
        case being_preset:
        { 
            return "being preset";
        } 
        break;
        case hourly_full:
        { 
            return "hourly full";
        } 
        break;
        case abnormal_open:
        { 
            return "abnormal open";
        } 
        break;
        case privilege_open:
        { 
            return "privilege open";
        } 
        break;
        case man_open:
        { 
            return "man open";
        } 
        break;
        case man_close:
        { 
            return "man close";
        } 
        break;
        case blacklist:
        { 
            return "blacklist";
        } 
        break;
        default:
        {
            return "proof entry exit type is unknown";
        }
        break;
    }
}

std::string Dashou::PAY_TYPE_To_string(int pay_type)
 {
     switch(pay_type)
     {
        case tablet_scans_ticket:
        { 
            return "tablet scans ticket";
        } 
        break;
        case tablet_input_license_plate_number:
        { 
            return "tablet input license plate number";
        } 
        break;
        case tablet_reads_card:
        { 
            return "tablet reads card";
        } 
        break;
        case tablet_reads_QR_code:
        { 
            return "tablet reads QR code";
        } 
        break;
        case central_pay_system_tablet_payment_confirm:
        { 
            return "central pay system tablet payment confirm";
        } 
        break;
        case exit_pay_system_tablet_payment_confirm:
        { 
            return "exit pay system tablet payment confirm";
        } 
        break;
        case tablet_switching_charge_type:
        { 
            return "tablet switching charge type";
        } 
        break;
        case table_confirms_prepaid_card_fee_deduction:
        { 
            return "table confirms prepaid card fee deduction";
        } 
        break;
        case parking_coupon_applied_on_tablet:
        { 
            return "parking coupon applied on tablet";
        } 
        break;
        case special_let_pass:
        { 
            return "special let pass";
        } 
        break;
        case manual_open_gate:
        { 
            return "manual open gate";
        } 
        break;
        case monthly_user_let_pass_as_hourly_user_1:
        { 
            return "monthly user let pass as hourly user 1";
        }
        break;
        case close_gate:
        {
            return "close gate";
        } 
        break;
        case entry_preset_license_plate_number:
        { 
            return "entry preset license plate number";
        } 
        break;
        case exit_preset_license_plate_number:
        { 
            return "exit preset license plate number";
        } 
        break;
        default:
        {
            return "pay type is unknown";
        }
        break;
     }
 }
 
std::string Dashou::functions_codes_To_string(int functions_codes)
{
    switch(functions_codes)
    {
        case CONTROL_ENTRY_REQUEST_RESPONSE:
        { 
            return "CONTROL ENTRY REQUEST RESPONSE";
	} 
        break;
        case CONTROL_EXIT_REQUEST_RESPONSE:
        { 
            return "CONTROL EXIT REQUEST RESPONSE";
	} 
        break;
        case CONTROL_TABLET_REQUEST_RESPONSE:
        { 
            return "CONTROL TABLET REQUEST RESPONSE";
	} 
        break;
        case CONTROL_INIT_REQUEST_RESPONSE:
        { 
            return "CONTROL INIT REQUEST RESPONSE";
	} 
        break;
        case CONTROL_HEARTBEAT:
        {
            return "CONTROL HEARTBEAT";
	} 
        break;
        case CONTROL_PAYMENT_BOARD_STATUS:
        { 
            return "CONTROL PAYMENT BOARD STATUS";
	} 
        break;
        case CONTROL_ACK_FRAME:
        { 
            return "CONTROL ACK FRAME";
	} 
        break;
        case CONTROL_FISCARD_TRANSACTION:
        { 
            return "CONTROL FISCARD TRANSACTION";
	} 
        break;
        case CONTROL_BROADCAST_TABLET_ADDRESS:
        { 
            return "CONTROL BROADCAST TABLET ADDRESS";
	} 
        break;
        case CONTROL_BROADCAST_TIME_AND_SPACES:
        { 
            return "CONTROL BROADCAST TIME AND SPACES";
        } 
        break;
        case CONTROL_Sys_PARAM_FRAME:
        { 
            return "CONTROL Sys PARAM FRAME";
        } 
        break;
        default:
        {
            return "functions codes is unknown";
        }
        break;

    }
}

std::string Dashou::get_STRINGASCIIHEX(std::string s)
{
    std::string ascii_hex_lower;
    std::string ascii_hex = "";
    if(s[0] == 0)
    {
        return ascii_hex;
    }
    else
    {
        for (int i = 0; s[i] != '\0'; i++)
        {
            char ch = s[i];
            int in = (int)ch;
            std::stringstream stream;
            stream << std::hex << in;
            ascii_hex_lower += stream.str();
        }
        for (int i = 0; ascii_hex_lower[i] != '\0'; i++)
        {
            ascii_hex += toupper(ascii_hex_lower[i]);
        }
    }
    return ascii_hex;
}

time_t Dashou::char_to_time_t(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4, unsigned char data5, unsigned char data6)
{
    tm time_and_date;
    time_and_date.tm_year = data1 + 100;
    time_and_date.tm_mon = data2 - 1;
    time_and_date.tm_mday = data3;
    time_and_date.tm_hour = data4;
    time_and_date.tm_min = data5;
    time_and_date.tm_sec = data6;
    time_t datetime = mktime(&time_and_date);
    if(std::difftime(datetime, Reference_date) < 0) return Reference_date;
    return datetime;
};

std::string Dashou::convertToString(char* a, int size) 
{ 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) 
    { 
        s = s + a[i]; 
    } 
    return s; 
} 