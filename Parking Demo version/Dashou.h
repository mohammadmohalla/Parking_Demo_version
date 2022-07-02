#include <iostream>
#include <ctime>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <dlfcn.h>
#include <vector>
#include <unistd.h>
#include <limits>
#include "Setting.h"
#include "Site_type.h"
#include "Camera_type.h"
#include "monthly_to_hourly.h"
#include "rule_name_hourly.h"
#include "rule_step_hourly.h"
#include "black_list.h"
#include "garage_info.h"
#include "accountInfo.h"
#include "account_state.h"
#include "event_in.h"
#include "event_out.h"
#include "event_payment.h"
#include "event_charge.h"
#include "temp_card.h"
#include "group_inner.h"
#include "monthly_type.h"
#include "rule_name_monthly.h"
#include "rule_step_monthly.h"
#include "server_errors_log.h"
#include "sys_user.h"
#include "photo.h"

#ifndef definded_variables

#define	PROOF_MODEL_PLATE_ONLY 0
#define	PROOF_MODEL_PLATE_AND_PROOF 1
#define	PROOF_MODEL_HOURLY_PROOF_SEASON_PLATE 2
#define	PROOF_MODEL_HOURLY_PLATE_SEASON_PROOF 3
#define	PROOF_MODEL_PROOF_ONLY 4
#define SEASON_TO_HOURLY_SWITCH_OPENED 1
#define SEASON_TO_HOURLY_SWITCH_CLOSED 0

// Entry type
#define ENTRY_EXIT_TYPE_TICKET "04"
#define ENTRY_EXIT_TYPE_PLATE "02"

#define CONTROL_ENTRY_REQUEST_RESPONSE 1                        // 0x01 Entry Request/Response Frame
#define CONTROL_EXIT_REQUEST_RESPONSE 2                         // 0x01 Exit Request/Response Frame
#define CONTROL_TABLET_REQUEST_RESPONSE 3                       // 0x03 Tablet Request/Response Frame
#define CONTROL_INIT_REQUEST_RESPONSE 4                         // 0x04 Initialization Request/Response Frame
#define CONTROL_HEARTBEAT 7					// 0x07 Heartbeat Frame
#define CONTROL_PAYMENT_BOARD_STATUS 13                         // 0x0D Heartbeat Frame
#define CONTROL_ACK_FRAME 23					// 0x17 ACK Frame
#define CONTROL_FISCARD_TRANSACTION 24                          // 0x18 Fiscard Transaction Record Frame
#define CONTROL_BROADCAST_TABLET_ADDRESS 27                     // 0x1B Tablet Address Broadcasting Frame (UDP)
#define CONTROL_BROADCAST_TIME_AND_SPACES 28                    // 0x1C Time/Parkng Spaces Broadcasting Frame (UDP)
#define CONTROL_Sys_PARAM_FRAME 29				// 0x1D System Parameter Frame


#define PMS_PORT 18890
#define SERVICEBOARD_TCP_PORT 1030
#define SERVICEBOARD_UDP_PORT 1036
#define PAYMENTAPP_TCP_PORT 1035

#define SERVICEBOARD_HOST "localhost"                           // "172.16.57.20";

#define HEADER "AAA5"
#define TAIL "CD"
#define CITY_ID "3075"                                          //30000
#define Garage_ID "0300"                                        //1
#define Online_master_ip "FE7A833D"				//61.131.122.254
#define Online_master_port "DA70"				//28890
#define Online_slave_ip "00000000"				//0.0.0.0
#define Online_slave_port "0000"				//0
#define ScanCodeIP "7777772e757262616e7061726b696e672e636e"     //www.urbanparking.cn
#define E_Transaction_ip "00000000"				//0.0.0.0
#define E_Transaction_port "0000"				//0

#define Zones_Number 16
#define Service_board_version "504f535345565f5633494931303042413038505f313930383039003042413038"			// POSSEV_V3II100BA08P_1908090BA08
#define Service_board_version_short "504f535345565f5633494931303042413038505f31393038303900000000000000"		// POSSEV_V3II100BA08P_190809
#define Entry_Board_Version "456E74727952414D5F56334949313030414130375F32303139303932395F656E"                          // EntryRAM_V3II100AA07_20190929_en
#define Exit_Board_Version "4578697452414d5f56334949313030414130375f323031393039323900000000"				// ExitRAM_V3II100AA07_20190929



#define CONTROL_DIRECTION_UPLOAD 128                            // 0x80 = 1000 0000
#define CONTROL_DIRECTION_DOWNLOAD 0                            // 0x00 = 0000 0000

// List of sites types
#define SITE_TYPE_SERVICE_BOARD 1				// 0x01
#define SITE_TYPE_SITE_BOARD 2					// 0x02
#define SITE_TYPE_ENTRY_BOARD 3					// 0x03
#define SITE_TYPE_EXIT_BOARD 4					// 0x04
#define SITE_TYPE_COUNTING_BOARD 5				// 0x05
#define SITE_TYPE_TABLET_APP 6					// 0x06
#define SITE_TYPE_PAYMENT_BOARD 7				// 0x07

// List of sites addresses
#define SITE_ADDRESS_ENTRY 4					// 0x04 (172.16.57.4)
#define SITE_ADDRESS_EXIT 3					// 0x03 (172.16.57.3)
#define SITE_ADDRESS_PAYMENT_APP 16				// 0x10 (172.16.57.16)
#define SITE_ADDRESS_SERVICE_BOARD 20                           // 0x14 (172.16.57.20)

#define SITE_STATUS_SERVICE_BOARD "00000000"

#define CONTROL_TYPE_SITE_SETTING 1				// 0100
#define CONTROL_TYPE_BALANCE_NOTIFICATION 14                    // 0E00
#define CONTROL_TYPE_EXPIRE_FORECAST 15                         // 0F00
#define CONTROL_TYPE_CAMERA_SITE 20				// 1400
#define CONTROL_TYPE_NETWORK_PARAM 26                           // 1A00
#define CONTROL_TYPE_SITE_NAME 27				// 1B00
#define CONTROL_TYPE_LED_DISPLAY 28				// 1C00
#define CONTROL_TYPE_TICKET_HEADER 29                           // 1D00
#define CONTROL_TYPE_RECEIPT_FORMAT 30                          // 1E00
#define CONTROL_TYPE_CHARGE_RATE 34				// 2200

// ticket types
#define TICKET_TYPE_NO_TICKET 0					// 0x00
#define TICKET_TYPE_TRANSPORTATION_CARD 1                       // 0x01
#define TICKET_TYPE_CHINA_UNION_CARD 2                          // 0x02
#define TICKET_TYPE_INTERNAL_CARD 51                            // 0x33
#define TICKET_TYPE_TICKET 102					// 0x66
#define TICKET_TYPE_QR_CODE 128					// 0x80

// Parking types
#define times_based_monthly_parking 1                           // 0X01
#define prepaid_based_monthly_parking 2                         // 0X02
#define hourly_based_monthly_parker 4	                        // 0X04
#define hourly_parker 64                                        // 0X40


// ENTRY TYPE
#define  undefine_inout_type 0                                  // 0x00
#define  monthly_by_num 1                                       // 0x01
#define  monthly_by_store 2                                     // 0x02
#define  monthly_to_hourly 3                                    // 0x03
#define  monthly_by_time 4                                      // 0x04
#define  monthly_catch_hourly 5                                 // 0x05
#define  stagger_time_park 6                                    // 0x06
#define  inner_monthly 32                                       // 0x20
#define  stagger_time_too_soon 50                               // 0x32
#define  please_avoid 51                                        // 0x33
#define  loss_monthly 52                                        // 0x34
#define  space_not_enough 54                                    // 0x36
#define  access_limit 55                                        // 0x37
#define  repeat_in_out 56                                       // 0x38
#define  monthly_full 57                                        // 0x39
#define  filtered 58                                            // 0x3A
#define  card_plate_mismatch 59                                 // 0x3B
#define  store_not_enough 60                                    // 0x3C
#define  num_not_enough 61                                      // 0x3D
#define  monthly_overdue 62                                     // 0x3E
#define  being 63                                               // 0x3F
#define  ticket_hourly 64                                       // 0x40
#define  card_hourly 65                                         // 0x41
#define  plate_hourly 66                                        // 0x42
#define  transportation_card_hourly 67                          // 0x43
#define  unionpay_card_hourly 68                                // 0x44
#define  QR_code_hourly 69                                      // 0x45
#define  card_hourly_2 70                                       // 0x46
#define  reserve_hourly 72                                      // 0x48
#define  inner_hourly 96                                        // 0x60
#define  out_prices 124                                         // 0x7C
#define  reserve_overdue 125                                    // 0x7D
#define  being_preset 126                                       // 0x7E
#define  hourly_full 127                                        // 0x7F
#define  abnormal_open 192                                      // 0xC0
#define  privilege_open 193                                     // 0xC1
#define  man_open 194                                           // 0xC2
#define  man_close 200                                          // 0xC8
#define  blacklist 255                                          // 0xFF


// PAY TYPE
#define  tablet_scans_ticket 0                                      // 0x00
#define  tablet_input_license_plate_number 2                        // 0x20
#define  tablet_reads_card 3                                        // 0x03
#define  tablet_reads_QR_code 4                                     // 0x04
#define  central_pay_system_tablet_payment_confirm 127              // 0x7f
#define  exit_pay_system_tablet_payment_confirm 128                 // 0x80
#define  tablet_switching_charge_type 129                           // 0x81
#define  table_confirms_prepaid_card_fee_deduction 130              // 0x82
#define  parking_coupon_applied_on_tablet 131                       // 0x83
#define  special_let_pass 193                                       // 0xc1
#define  manual_open_gate 194                                       // 0xc2
#define  monthly_user_let_pass_as_hourly_user_1 195                 // 0xc3
#define  monthly_user_let_pass_as_hourly_user_2 196                 // 0xc4
#define  monthly_user_let_pass_as_hourly_user_3 197                 // 0xc5
#define  monthly_user_let_pass_as_hourly_user 198                   // 0xc6
#define  monthly_user_let_pass_as_hourly_user_5 199                 // 0xc7
#define  close_gate 200                                            // 0xc8
#define  entry_preset_license_plate_number 224                      // 0xe0
#define  exit_preset_license_plate_number 225                       // 0xe1

// charge type
#define num_renew_netpay 1
#define store_renew_netpay 2
#define stagger_rent_netpay 3
#define num_renew_netpay_1 4
#define time_issue_netpay 16
#define num_issue_netpay 17
#define store_issue_netpay 18
#define time_issue_cash_1 32
#define num_renew_cash 33
#define store_renew_cash 34
#define time_issue_cash 48
#define num_issue_cash 49
#define store_issue_cash 50
#define reserve_netpay 64
#define hourly_neypay 128
#define credit_ 144
#define cash 160
#define traffic_card_electronic_pay 161
#define union_electronic_pay_ 162
#define inner_store_pay 163
#define abnormal_charge 164
#define privilege_charge 165
#define man_open_charge 166
#define P_R 167
#define unionpay_reduce 168
#define online_use_coupon 192
#define unline_use_coupon 193
#define lock 232
#define unlock 233
#define monthly_in 256
#define monthly_out 257
#define buy_coupon 258


#define INVALID_SOCKET -1
#define SOCKET_ERROR -2

#define Reference_date 946684800
#endif

struct ChargingStandard
{
    int id;
    std::string name;
};

class Dashou
{
public:
	static const bool debug = false;

	Dashou();

	~Dashou();
              
	static std::string to_String_X8(unsigned int v);

	static std::string to_String_X4(int val);
        
	static std::string to_String_X2(int val);

	static std::string to_String_00(int v);

	static char* StringToByteArray(std::string hex);

	static std::string int2HexStrReverse2Byte(int v);

	static std::string calcLength(int length);

	static std::string calcSerial(int serial);

	static std::string calcCurrentTime(time_t now);
        
        static std::string Print_time(time_t now);

	static std::string calcChecksum_broadcast();

	static std::string calcChecksum_server(int length, int serial, int function, int year, int month, int day, int hour);

	static std::string calcChecksum_client(int length, int serial, int function1, int function2);
        
        static std::string ticket_types_To_string(int ticket_type);
        
        static std::string account_types_To_string(int account_type);
        
        static std::string ENTRY_EXIT_TYPE_To_string(int proof_entry_exit_type);
        
        static std::string PAY_TYPE_To_string(int pay_type);
        
        static std::string functions_codes_To_string(int functions_codes);

	unsigned int get_TABLET_cost(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4);

	unsigned int get_TABLET_PAID(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4);
        
        unsigned int get_X2_Number(unsigned char data1, unsigned char data2);
        
        unsigned int get_X4_Number(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4);
        
        std::string get_STRINGASCIIHEX(std::string s);
        
        time_t char_to_time_t(unsigned char data1, unsigned char data2, unsigned char data3, unsigned char data4, unsigned char data5, unsigned char data6);
        
        std::string convertToString(char* a, int size);

};
