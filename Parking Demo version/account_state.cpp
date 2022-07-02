#include "account_state.h"

account_state::account_state(MYSQL *_mysql)
{
    mysql = _mysql;
}

account_state::~account_state()
{
    aid = 0;
    gid = 0;
    ticket_type = 255;
    strcpy(ticket, "");
    strcpy(plate, "");
    create_time = 0;
    parking_type = 0;
    present_type = 0;
    intime = 0;
    inserial = 0;
    outtime = 0;
    outserial = 0;
    pay_time = 0;
    pay_serial = 0;
    paid_sum = 0;
    charge_type = 0;
    inner_intime = 0;
    inner_inserial = 0;
    inner_outtime = 0;
    inner_outserial = 0;
    limit_sum = 0;
    strcpy(online_order, "");
    insite = 0;
    charge_site = 0;
    inner_insite = 0;
    inner_outsite = 0;
    prepaid_balance = 0;
    l2_id = 0;
    prepaid_account_id = 0;
    strcpy(hour_ticket_num, "");
    hour_ticket_type = 0;
    coupon_total_sum = 0;
    coupon_total_time = 0;
    total_sum = 0;
}

int account_state::print_account_state()
{
    try
    {
        printf("%d %d %d %s %s %ld %d %d %ld %d %ld %d %ld %d %d %d %ld %d %ld %d %d %s %d %d %d %d %d %d %d %s %d %d %d %d\n",
            aid,
            gid,
            ticket_type,
            ticket,
            plate,
            create_time,
            parking_type,
            present_type,
            intime,
            inserial,
            outtime,
            outserial,
            pay_time,
            pay_serial,
            paid_sum,
            charge_type,
            inner_intime,
            inner_inserial,
            inner_outtime,
            inner_outserial,
            limit_sum,
            online_order,
            insite,
            charge_site,
            inner_insite,
            inner_outsite,
            prepaid_balance,
            l2_id,
            prepaid_account_id,
            hour_ticket_num,
            hour_ticket_type,
            coupon_total_sum,
            coupon_total_time,
            total_sum
            );
    }
    catch(...)
    {
        return -3870;
    }
    return 0;
}

int account_state::Select_account_state_by_ID(int index)
{
    int id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(createtime),UNIX_TIMESTAMP(intime),UNIX_TIMESTAMP(outtime),UNIX_TIMESTAMP(pay_time),UNIX_TIMESTAMP(inner_intime),UNIX_TIMESTAMP(inner_outtime) FROM v32_account_state WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3802;
        }
        if (!stmt)
        {
            return -3802;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3803;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3804;
            }
            if (stmt_bind_param)
            {
                return -3804;
            }
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3805;
            }
            if (param_count != 1)
            {
                return -3805;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3806;
            }
            if (!prepare_meta_result)
            {
                return -3806;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3807;
            }
            if (column_count != 40)
            {
                return -3807;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3808;
            }
            if (stmt_execute)
            {
                return -3808;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&create_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&intime;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&inserial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&outtime;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&outserial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&pay_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&pay_serial;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&paid_sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&charge_type;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&inner_intime;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&inner_inserial;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&inner_outtime;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&inner_outserial;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&limit_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&insite;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&charge_site;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&inner_insite;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inner_outsite;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&prepaid_balance;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&l2_id;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_account_id;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)hour_ticket_num;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&hour_ticket_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&coupon_total_sum;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_total_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&total_sum;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3871;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3809;
            }
            if (stmt_bind_result)
            {
                return -3809;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3810;
            }
            if (stmt_store_result)
            {
                return -3810;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3811;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3812;
            }
        }
        else
        {
            return -3803;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3813;
        }
    }
    else
    {
        return -3801;
    }
    return 0;
}

int account_state::Select_account_state_by_ticket(std::string _ticket)
{
    char ticket_[20];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(createtime),UNIX_TIMESTAMP(intime),UNIX_TIMESTAMP(outtime),UNIX_TIMESTAMP(pay_time),UNIX_TIMESTAMP(inner_intime),UNIX_TIMESTAMP(inner_outtime) FROM v32_account_state WHERE ticket=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3815;
        }
        if (!stmt)
        {
            return -3815;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3816;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)ticket_;
                bind_param[0].buffer_length= strlen(_ticket.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
                
            }
            catch(...)
            {
                return -3817;
            }
            if (stmt_bind_param)
            {
                return -3817;
            }
            int param_count = 0;
            try
            {
                strcpy( ticket_, _ticket.c_str());
                param_count = mysql_stmt_param_count(stmt);
                
            }
            catch(...)
            {
                return -3818;
            }
            if(param_count != 1)
            {
                return -3818;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3819;
            }
            if (!prepare_meta_result)
            {
                return -3819;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3820;
            }
            if (column_count != 40)
            {
                return -3820;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3821;
            }
            if (stmt_execute)
            {
                return -3821;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&create_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&intime;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&inserial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&outtime;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&outserial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&pay_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&pay_serial;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&paid_sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&charge_type;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&inner_intime;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&inner_inserial;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&inner_outtime;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&inner_outserial;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&limit_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&insite;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&charge_site;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&inner_insite;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inner_outsite;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&prepaid_balance;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&l2_id;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_account_id;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)hour_ticket_num;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&hour_ticket_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&coupon_total_sum;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_total_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&total_sum;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3872;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3822;
            }
            if (stmt_bind_result)
            {
                return -3822;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3823;
            }
            if (stmt_store_result)
            {
                return -3823;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3824;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3825;
            }
        }
        else
        {
            return -3816;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3826;
        }
    }
    else
    {
        return -3814;
    }
    return true;
}

int account_state::Select_account_state_by_plate(std::string curr_plate, int match_plate)
{
    char plate_[12];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(createtime),UNIX_TIMESTAMP(intime),UNIX_TIMESTAMP(outtime),UNIX_TIMESTAMP(pay_time),UNIX_TIMESTAMP(inner_intime),UNIX_TIMESTAMP(inner_outtime) FROM v32_account_state WHERE SUBSTR(plate,1," + std::to_string(match_plate) +")=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3828;
        }
        if (!stmt)
        {
            return -3828;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3829;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)plate_;
                bind_param[0].buffer_length= strlen(curr_plate.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3830;
            }
            if (stmt_bind_param)
            {
                return -3830;
            }
            int param_count = true;
            try
            {
                strncpy( plate_, curr_plate.c_str(), match_plate);
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3831;
            }
            if (param_count != 1)
            {
                return -3831;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3832;
            }
            if (!prepare_meta_result)
            {
                return -3832;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3833;
            }
            if (column_count != 40)
            {
                return -3833;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3834;
            }
            if (stmt_execute)
            {
                return -3834;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&create_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&intime;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&inserial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[36].buffer_type= MYSQL_TYPE_LONG;
                bind[36].buffer= (char *)&outtime;
                bind[36].is_null= &is_null[36];
                bind[36].length= &length[36];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&outserial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[37].buffer_type= MYSQL_TYPE_LONG;
                bind[37].buffer= (char *)&pay_time;
                bind[37].is_null= &is_null[37];
                bind[37].length= &length[37];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&pay_serial;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&paid_sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&charge_type;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[38].buffer_type= MYSQL_TYPE_LONG;
                bind[38].buffer= (char *)&inner_intime;
                bind[38].is_null= &is_null[38];
                bind[38].length= &length[38];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&inner_inserial;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[39].buffer_type= MYSQL_TYPE_LONG;
                bind[39].buffer= (char *)&inner_outtime;
                bind[39].is_null= &is_null[39];
                bind[39].length= &length[39];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&inner_outserial;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&limit_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&insite;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&charge_site;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&inner_insite;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inner_outsite;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&prepaid_balance;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&l2_id;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_account_id;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)hour_ticket_num;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&hour_ticket_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&coupon_total_sum;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_total_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&total_sum;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3873;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3835;
            }
            if (stmt_bind_result)
            {
                return -3835;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3836;
            }
            if (stmt_store_result)
            {
                return -3836;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3837;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3838;
            }
        }
        else
        {
            return -3829;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3839;
        }
    }
    else
    {
        return -3827;
    }
    return 0;
}

int account_state::Insert_account_state()
{
    std::string statment = "INSERT INTO `v32_account_state` (`aid`, `gid`, `ticket_type`, `ticket`, `plate`, `createtime`, `parking_type`, `present_type`,`intime`, `inserial`, `outtime`, `outserial`, `pay_time`, `pay_serial`, `paid_sum`, `charge_type`, `inner_intime`, `inner_inserial`, `inner_outtime`, `inner_outserial`, `limit_sum`, `online_order`, `insite`, `charge_site`, `inner_insite`, `inner_outsite`, `prepaid_balance`, `l2_id`, `prepaid_account_id`, `hour_ticket_num`, `hour_ticket_type`, `coupon_total_sum`, `coupon_total_time`, `total_sum`) VALUES ( ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3841;
        }
        if (!stmt)
        {
            return -3841;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3842;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(ticket);
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&create_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&intime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&inserial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&outtime;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&outserial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&pay_time;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&pay_serial;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&paid_sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&charge_type;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&inner_intime;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&inner_inserial;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&inner_outtime;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&inner_outserial;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&limit_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_order);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&insite;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&charge_site;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&inner_insite;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inner_outsite;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&prepaid_balance;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&l2_id;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_account_id;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)hour_ticket_num;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(hour_ticket_num);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&hour_ticket_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&coupon_total_sum;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_total_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&total_sum;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3874;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3843;
            }
            if (stmt_bind_param)
            {
                return -3843;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3844;
            }
            if (param_count != 34)
            {
                return -3844;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3845;
            }
            if(stmt_execute)
            {
                return -3845;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3846;
            }
            if (stmt_affected_rows != 1)
            {
                return -3846;
            }
        }
        else
        {
            return -3842;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3847;
        }
    }
    else
    {
        return -3840;
    }
    return 0;
}

int account_state::Insert_update_account_state()
{
    std::string statment = "INSERT INTO `v32_account_state` (`aid`, `gid`, `ticket_type`, `ticket`, `plate`, `createtime`, `parking_type`, `present_type`,`intime`, `inserial`, `outtime`, `outserial`, `pay_time`, `pay_serial`, `paid_sum`, `charge_type`, `inner_intime`, `inner_inserial`, `inner_outtime`, `inner_outserial`, `limit_sum`, `online_order`, `insite`, `charge_site`, `inner_insite`, `inner_outsite`, `prepaid_balance`, `l2_id`, `prepaid_account_id`, `hour_ticket_num`, `hour_ticket_type`, `coupon_total_sum`, `coupon_total_time`, `total_sum`) VALUES ( ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), ticket_type=VALUES(ticket_type), ticket=VALUES(ticket), plate=VALUES(plate), createtime=VALUES(createtime), parking_type=VALUES(parking_type), present_type=VALUES(present_type), intime=VALUES(intime), inserial=VALUES(inserial), outtime=VALUES(outtime), outserial=VALUES(outserial), pay_time=VALUES(pay_time), pay_serial=VALUES(pay_serial), paid_sum=VALUES(paid_sum), charge_type=VALUES(charge_type), inner_intime=VALUES(inner_intime), inner_inserial=VALUES(inner_inserial), inner_outtime=VALUES(inner_outtime), inner_outserial=VALUES(inner_outserial), limit_sum=VALUES(limit_sum), online_order=VALUES(online_order), insite=VALUES(insite), charge_site=VALUES(charge_site), inner_insite=VALUES(inner_insite), inner_outsite=VALUES(inner_outsite), prepaid_balance=VALUES(prepaid_balance), l2_id=VALUES(l2_id), prepaid_account_id=VALUES(prepaid_account_id), hour_ticket_num=VALUES(hour_ticket_num), hour_ticket_type=VALUES(hour_ticket_type), coupon_total_sum=VALUES(coupon_total_sum),  coupon_total_time=VALUES(coupon_total_time),  total_sum=VALUES(total_sum)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3849;
        }
        if (!stmt)
        {
            return -3849;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3850;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&aid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_SHORT;
                bind[2].buffer= (char *)&ticket_type;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)ticket;
                bind[3].buffer_length= 20;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(ticket);
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&create_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&parking_type;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&present_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&intime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&inserial;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&outtime;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&outserial;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&pay_time;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&pay_serial;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&paid_sum;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&charge_type;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&inner_intime;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_LONG;
                bind[17].buffer= (char *)&inner_inserial;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_LONG;
                bind[18].buffer= (char *)&inner_outtime;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&inner_outserial;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&limit_sum;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_order;
                bind[21].buffer_length= 255;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_order);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&insite;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&charge_site;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&inner_insite;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&inner_outsite;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&prepaid_balance;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_LONG;
                bind[27].buffer= (char *)&l2_id;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&prepaid_account_id;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)hour_ticket_num;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(hour_ticket_num);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_SHORT;
                bind[30].buffer= (char *)&hour_ticket_type;
                bind[30].is_null= &is_null[30];
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_LONG;
                bind[31].buffer= (char *)&coupon_total_sum;
                bind[31].is_null= &is_null[31];
                bind[31].length= &length[31];

                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&coupon_total_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&total_sum;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];
            }
            catch(...)
            {
                return -3875;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3851;
            }
            if (stmt_bind_param)
            {
                return -3851;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3852;
            }
            if (param_count != 34)
            {
                return -3852;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3853;
            }
            if (stmt_execute)
            {
                return -3853;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3854;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Account state is inserted\n");
            }
            else
            {
                printf("Account state is updated\n");
            }
        }
        else
        {
            return -3850;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3855;
        }
    }
    else
    {
        return -3848;
    }
    return 0;
}

int account_state::Delete_account_state()
{
    try
    {
        gid = 130000;
        ticket_type = 255;
        strcpy(ticket, "");
        strcpy(plate, "");
        create_time = 0;
        parking_type = 0;
        present_type = 0;
        intime = 0;
        inserial = 0;
        outtime = 0;
        outserial = 0;
        pay_time = 0;
        pay_serial = 0;
        paid_sum = 0;
        charge_type = 0;
        inner_intime = 0;
        inner_inserial = 0;
        inner_outtime = 0;
        inner_outserial = 0;
        limit_sum = 0;
        strcpy(online_order, "");
        insite = 0;
        charge_site = 0;
        inner_insite = 0;
        inner_outsite = 0;
        prepaid_balance = 0;
        l2_id = 0;
        prepaid_account_id = 0;
        strcpy(hour_ticket_num, "");
        hour_ticket_type = 0;
        coupon_total_sum = 0;
        coupon_total_time = 0;
        total_sum = 0;
    }
    catch(...)
    {
        return -3876;
    }
    std::string statment = "DELETE FROM `v32_account_state` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3857;
        }
        if (!stmt)
        {
            return -3857;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3858;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&aid;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3859;
            }
            if (stmt_bind_param)
            {
                return -3859;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3860;
            }
            if (param_count != 1)
            {
                return -3860;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3861;
            }
            if (stmt_execute)
            {
                return -3861;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3862;
            }
            if (stmt_affected_rows < 1)
            {
                return -3862;
            }    
        }
        else
        {
            return -3858;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3863;
        }
    }
    else
    {
        return -3856;
    }
    aid = 0;
    return 0;
}

int account_state::Delete_all_account_state()
{
    std::string statment = "DELETE FROM `v32_account_state`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3865;
        }
        if (!stmt)
        {
            return -3865;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3866;
        }
        if (!stmt_prepare)
        {    
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3867;
            }
            if (stmt_execute)
            {
                return -3867;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
                printf("Delete (%d) Records\n", stmt_affected_rows);
            }
            catch(...)
            {
                return -3868;
            }
            if (stmt_affected_rows < 1)
            {
                return -3868;
            }
        }
        else
        {
            return -3766;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3869;
        }
    }
    else
    {
        return -3864;
    }
    return 0;
}