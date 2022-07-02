#include "accountInfo.h"

accountInfo::accountInfo(MYSQL *_mysql)
{
    mysql = _mysql;
}

accountInfo::~accountInfo()
{
    id = 0;
    gid = 0;
    strcpy(tickets, "");
    ticket_type = 255;
    strcpy(plate, "");
    access_group = 0;
    inner_group = 0;
    time_group = 0;
    lots_group = 0;
    account_state = 0;
    parking_type = 0;
    strcpy(addr, "");
    strcpy(description, "");
    strcpy(email, "");
    strcpy(phone, "");
    strcpy(owner_name, "");
    strcpy(hour_ticket_num, "");
    hour_ticket_type = 0;
    lot_id = 0;
    strcpy(online_member, "");
    prepaid_charge_rule = 0;
    monthly_charge_rule = 0;
    ticket_lpbind = 0;
    monthly_type = 0;
    _operator = 0;
    strcpy(photo_id, "");
    strcpy(add_info1, "");
    strcpy(add_info2, "");
    start_time = 0;
    end_time = 0;
    limit_time = 0;
    create_time = 0;
}

int accountInfo::print_accountInfo()
{
    try
    {
        printf("%d %d %s %d %s %ld %ld %d %d %d %d %d %d %s %s %s %s %s %s %d %d %s %d %d %d %d %ld %d %ld %s %s %s\n",
            id,
            gid,
            tickets,
            ticket_type,
            plate,
            start_time,
            end_time,
            access_group,
            inner_group,
            time_group,
            lots_group,
            account_state,
            parking_type,
            addr,
            description,
            email,
            phone,
            owner_name,
            hour_ticket_num,
            hour_ticket_type,
            lot_id,
            online_member,
            prepaid_charge_rule,
            monthly_charge_rule,
            ticket_lpbind,
            monthly_type,
            limit_time,
            _operator,
            create_time,
            photo_id,
            add_info1,
            add_info2
            );
    }
    catch(...)
    {
        return -3770;
    }
    return 0;
}

int accountInfo::Select_account_by_ID(int index)
{
    int id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(limit_time),UNIX_TIMESTAMP(createtime) FROM v32_account_info WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3702;
        }
        if (!stmt)
        {
            return -3702;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3703;
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
                return -3704;
            }
            if (stmt_bind_param)
            {
                return -3704;
            }
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3705;
            }
            if (param_count != 1)
            {
                return -3705;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3706;
            }
            if (!prepare_meta_result)
            {
                return -3706;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3707;
            }
            if (column_count != 36) /* validate column count */
            {
                return -3707;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3708;
            }
            if (stmt_execute)
            {
                return -3708;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)tickets;
                bind[2].buffer_length= 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(tickets);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&ticket_type;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&start_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&end_time;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&access_group;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&inner_group;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&time_group;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&lots_group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&account_state;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_SHORT;
                bind[12].buffer= (char *)&parking_type;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)addr;
                bind[13].buffer_length= 100;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(addr);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)description;
                bind[14].buffer_length= 100;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(description);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)email;
                bind[15].buffer_length= 64;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(email);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)phone;
                bind[16].buffer_length= 16;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(phone);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)owner_name;
                bind[17].buffer_length= 20;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(owner_name);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)hour_ticket_num;
                bind[18].buffer_length= 20;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(hour_ticket_num);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&hour_ticket_type;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lot_id;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_member;
                bind[21].buffer_length= 20;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_member);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&prepaid_charge_rule;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&monthly_charge_rule;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&ticket_lpbind;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&monthly_type;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&limit_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&_operator;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&create_time;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)photo_id;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(photo_id);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_STRING;
                bind[30].buffer= (char *)add_info1;
                bind[30].buffer_length= 20;
                bind[30].is_null= &is_null[30];
                length[30] = strlen(add_info1);
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_STRING;
                bind[31].buffer= (char *)add_info2;
                bind[31].buffer_length= 20;
                bind[31].is_null= &is_null[31];
                length[31] = strlen(add_info2);
                bind[31].length= &length[31];
            }
            catch(...)
            {
                return -3771;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3709;
            }
            if (stmt_bind_result)
            {
                return -3709;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3710;
            }
            if (stmt_store_result)
            {
                return -3710;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3711;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3712;
            }
        }
        else
        {
            return -3703;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3713;
        }
    }
    else
    {
        return -3701;
    }
    return 0;
}

int accountInfo::Select_account_by_ticket(std::string ticket)
{
    char ticket_[20];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(limit_time),UNIX_TIMESTAMP(createtime) FROM v32_account_info WHERE ticket=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3715;
        }
        if (!stmt)
        {
            return -3715;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3716;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)ticket_;
                bind_param[0].buffer_length= strlen(ticket.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3717;
            }
            if (stmt_bind_param)
            {
                return -3717;
            }
            int param_count = 0;
            try
            {
                strcpy( ticket_, ticket.c_str());
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3718;
            }
            if (param_count != 1)
            {
                return -3718;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3719;
            }
            if (!prepare_meta_result)
            {
                return -3719;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3720;
            }
            if (column_count != 36) /* validate column count */
            {
                return -3720;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3721;
            }
            if (stmt_execute)
            {
                return -3721;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)tickets;
                bind[2].buffer_length= 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(tickets);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&ticket_type;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&start_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&end_time;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&access_group;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&inner_group;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&time_group;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&lots_group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&account_state;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_SHORT;
                bind[12].buffer= (char *)&parking_type;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)addr;
                bind[13].buffer_length= 100;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(addr);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)description;
                bind[14].buffer_length= 100;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(description);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)email;
                bind[15].buffer_length= 64;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(email);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)phone;
                bind[16].buffer_length= 16;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(phone);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)owner_name;
                bind[17].buffer_length= 20;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(owner_name);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)hour_ticket_num;
                bind[18].buffer_length= 20;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(hour_ticket_num);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&hour_ticket_type;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lot_id;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_member;
                bind[21].buffer_length= 20;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_member);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&prepaid_charge_rule;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&monthly_charge_rule;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&ticket_lpbind;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&monthly_type;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&limit_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&_operator;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&create_time;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)photo_id;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(photo_id);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_STRING;
                bind[30].buffer= (char *)add_info1;
                bind[30].buffer_length= 20;
                bind[30].is_null= &is_null[30];
                length[30] = strlen(add_info1);
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_STRING;
                bind[31].buffer= (char *)add_info2;
                bind[31].buffer_length= 20;
                bind[31].is_null= &is_null[31];
                length[31] = strlen(add_info2);
                bind[31].length= &length[31];
            }
            catch(...)
            {
                return -3772;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3722;
            }
            if (stmt_bind_result)
            {
                return -3722;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3723;
            }
            if (stmt_store_result)
            {
                return -3723;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3724;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3725;
            }
        }
        else
        {
            return -3716;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3726;
        }
    }
    else
    {
        return -3714;
    }
    return 0;
}

int accountInfo::Select_account_by_plate(std::string curr_plate, int match_plate)
{
    char plate_[12];
    std::string statment = "SELECT *,UNIX_TIMESTAMP(start_time),UNIX_TIMESTAMP(end_time),UNIX_TIMESTAMP(limit_time),UNIX_TIMESTAMP(createtime) FROM v32_account_info WHERE SUBSTR(plate,1," + std::to_string(match_plate) +")=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3728;
        }
        if (!stmt)
        {
            return -3728;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3729;
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
                return -3730;
            }
            if(stmt_bind_param)
            {
                return -3730;
            }
            int param_count = 0;
            try
            {
                strncpy( plate_, curr_plate.c_str(), match_plate);
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3731;
            }
            if (param_count != 1)
            {
                return -3731;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3732;
            }
            if (!prepare_meta_result)
            {
                return -3732;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3733;
            }
            if (column_count != 36)
            {
                return -3733;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3734;
            }
            if (stmt_execute)
            {
                return -3734;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));
                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)tickets;
                bind[2].buffer_length= 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(tickets);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&ticket_type;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)plate;
                bind[4].buffer_length= 12;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(plate);
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[32].buffer_type= MYSQL_TYPE_LONG;
                bind[32].buffer= (char *)&start_time;
                bind[32].is_null= &is_null[32];
                bind[32].length= &length[32];

                /* SHORT COLUMN */
                bind[33].buffer_type= MYSQL_TYPE_LONG;
                bind[33].buffer= (char *)&end_time;
                bind[33].is_null= &is_null[33];
                bind[33].length= &length[33];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&access_group;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&inner_group;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&time_group;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&lots_group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&account_state;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_SHORT;
                bind[12].buffer= (char *)&parking_type;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)addr;
                bind[13].buffer_length= 100;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(addr);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)description;
                bind[14].buffer_length= 100;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(description);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)email;
                bind[15].buffer_length= 64;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(email);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)phone;
                bind[16].buffer_length= 16;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(phone);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)owner_name;
                bind[17].buffer_length= 20;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(owner_name);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)hour_ticket_num;
                bind[18].buffer_length= 20;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(hour_ticket_num);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&hour_ticket_type;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lot_id;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_member;
                bind[21].buffer_length= 20;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_member);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&prepaid_charge_rule;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&monthly_charge_rule;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&ticket_lpbind;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&monthly_type;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[34].buffer_type= MYSQL_TYPE_LONG;
                bind[34].buffer= (char *)&limit_time;
                bind[34].is_null= &is_null[34];
                bind[34].length= &length[34];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&_operator;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[35].buffer_type= MYSQL_TYPE_LONG;
                bind[35].buffer= (char *)&create_time;
                bind[35].is_null= &is_null[35];
                bind[35].length= &length[35];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)photo_id;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(photo_id);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_STRING;
                bind[30].buffer= (char *)add_info1;
                bind[30].buffer_length= 20;
                bind[30].is_null= &is_null[30];
                length[30] = strlen(add_info1);
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_STRING;
                bind[31].buffer= (char *)add_info2;
                bind[31].buffer_length= 20;
                bind[31].is_null= &is_null[31];
                length[31] = strlen(add_info2);
                bind[31].length= &length[31];
            }
            catch(...)
            {
                return -3773;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3735;
            }
            if (stmt_bind_result)
            {
                return -3735;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3736;
            }
            if(stmt_store_result)
            {
                return -3736;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3737;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3738;
            }
        }
        else
        {
            return -3729;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3739;
        }
    }
    else
    {
        return -3727;
    }
    return 0;
}

int accountInfo::Insert_accountInfo()
{
    std::string statment = "INSERT INTO `v32_account_info` (`aid`, `gid`, `ticket`, `ticket_type`, `plate`, `start_time`, `end_time`, `access_group`, `inner_group`, `time_group`, `lots_group`, `account_state`, `parking_type`, `addr`, `description`, `email`, `phone`, `owner_name`, `hour_ticket_num`, `hour_ticket_type`, `lot_id`, `online_member`, `prepaid_charge_rule`, `monthly_charge_rule`, `ticket_lpbind`, `monthly_type`, `limit_time`, `operator`, `createtime`, `photo_id`, `add_info1`, `add_info2`) VALUES ( ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3741;
        }
        if (!stmt)
        {
            return -3741;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3742;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)tickets;
                bind[2].buffer_length= 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(tickets);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&ticket_type;
                bind[3].is_null= &is_null[3];
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
                bind[5].buffer= (char *)&start_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&end_time;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&access_group;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&inner_group;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&time_group;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&lots_group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&account_state;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_SHORT;
                bind[12].buffer= (char *)&parking_type;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)addr;
                bind[13].buffer_length= 100;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(addr);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)description;
                bind[14].buffer_length= 100;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(description);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)email;
                bind[15].buffer_length= 64;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(email);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)phone;
                bind[16].buffer_length= 16;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(phone);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)owner_name;
                bind[17].buffer_length= 20;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(owner_name);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)hour_ticket_num;
                bind[18].buffer_length= 20;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(hour_ticket_num);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&hour_ticket_type;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lot_id;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_member;
                bind[21].buffer_length= 20;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_member);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&prepaid_charge_rule;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&monthly_charge_rule;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&ticket_lpbind;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&monthly_type;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&limit_time;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&_operator;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&create_time;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)photo_id;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(photo_id);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_STRING;
                bind[30].buffer= (char *)add_info1;
                bind[30].buffer_length= 20;
                bind[30].is_null= &is_null[30];
                length[30] = strlen(add_info1);
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_STRING;
                bind[31].buffer= (char *)add_info2;
                bind[31].buffer_length= 20;
                bind[31].is_null= &is_null[31];
                length[31] = strlen(add_info2);
                bind[31].length= &length[31];
            }
            catch(...)
            {
                return -3774;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3743;
            }
            if (stmt_bind_param)
            {
                return -3743;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3744;
            }
            if (param_count != 32)
            {
                return -3744;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3745;
            }
            if (stmt_execute)
            {
                return -3745;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3746;
            }
            if (stmt_affected_rows != 1)
            {
                return -3746;
            }
        }
        else
        {
            return -3742;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3747;
        }
    }
    else
    {
        return -3740;
    }
    return 0;
}

int accountInfo::Insert_update_accountInfo()
{
    std::string statment = "INSERT INTO `v32_account_info` (`aid`, `gid`, `ticket`, `ticket_type`, `plate`, `start_time`, `end_time`, `access_group`, `inner_group`, `time_group`, `lots_group`, `account_state`, `parking_type`, `addr`, `description`, `email`, `phone`, `owner_name`, `hour_ticket_num`, `hour_ticket_type`, `lot_id`, `online_member`, `prepaid_charge_rule`, `monthly_charge_rule`, `ticket_lpbind`, `monthly_type`, `limit_time`, `operator`, `createtime`, `photo_id`, `add_info1`, `add_info2`) VALUES ( ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?) ON DUPLICATE KEY UPDATE aid=VALUES(aid), gid=VALUES(gid), ticket=VALUES(ticket), ticket_type=VALUES(ticket_type), plate=VALUES(plate), start_time=VALUES(start_time), end_time=VALUES(end_time), access_group=VALUES(access_group), inner_group=VALUES(inner_group), time_group=VALUES(time_group), lots_group=VALUES(lots_group), account_state=VALUES(account_state), parking_type=VALUES(parking_type), addr=VALUES(addr), description=VALUES(description), email=VALUES(email), phone=VALUES(phone), owner_name=VALUES(owner_name), hour_ticket_num=VALUES(hour_ticket_num), hour_ticket_type=VALUES(hour_ticket_type), lot_id=VALUES(lot_id), online_member=VALUES(online_member), prepaid_charge_rule=VALUES(prepaid_charge_rule), monthly_charge_rule=VALUES(monthly_charge_rule), ticket_lpbind=VALUES(ticket_lpbind), monthly_type=VALUES(monthly_type), limit_time=VALUES(limit_time), operator=VALUES(operator), createtime=VALUES(createtime), photo_id=VALUES(photo_id), add_info1=VALUES(add_info1), add_info2=VALUES(add_info2)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3749;
        }
        if (!stmt)
        {
            return -3749;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3750;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null,0,sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)tickets;
                bind[2].buffer_length= 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(tickets);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&ticket_type;
                bind[3].is_null= &is_null[3];
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
                bind[5].buffer= (char *)&start_time;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&end_time;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&access_group;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&inner_group;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&time_group;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&lots_group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&account_state;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_SHORT;
                bind[12].buffer= (char *)&parking_type;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)addr;
                bind[13].buffer_length= 100;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(addr);
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)description;
                bind[14].buffer_length= 100;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(description);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)email;
                bind[15].buffer_length= 64;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(email);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)phone;
                bind[16].buffer_length= 16;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(phone);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)owner_name;
                bind[17].buffer_length= 20;
                bind[17].is_null= &is_null[17];
                length[17] = strlen(owner_name);
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)hour_ticket_num;
                bind[18].buffer_length= 20;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(hour_ticket_num);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&hour_ticket_type;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&lot_id;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)online_member;
                bind[21].buffer_length= 20;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(online_member);
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&prepaid_charge_rule;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_SHORT;
                bind[23].buffer= (char *)&monthly_charge_rule;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* SHORT COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_SHORT;
                bind[24].buffer= (char *)&ticket_lpbind;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* SHORT COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_SHORT;
                bind[25].buffer= (char *)&monthly_type;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];

                /* SHORT COLUMN */
                bind[26].buffer_type= MYSQL_TYPE_LONG;
                bind[26].buffer= (char *)&limit_time;
                bind[26].is_null= &is_null[26];
                bind[26].length= &length[26];

                /* SHORT COLUMN */
                bind[27].buffer_type= MYSQL_TYPE_SHORT;
                bind[27].buffer= (char *)&_operator;
                bind[27].is_null= &is_null[27];
                bind[27].length= &length[27];

                /* SHORT COLUMN */
                bind[28].buffer_type= MYSQL_TYPE_LONG;
                bind[28].buffer= (char *)&create_time;
                bind[28].is_null= &is_null[28];
                bind[28].length= &length[28];

                /* VARCHAR COLUMN */
                bind[29].buffer_type= MYSQL_TYPE_STRING;
                bind[29].buffer= (char *)photo_id;
                bind[29].buffer_length= 20;
                bind[29].is_null= &is_null[29];
                length[29] = strlen(photo_id);
                bind[29].length= &length[29];

                /* VARCHAR COLUMN */
                bind[30].buffer_type= MYSQL_TYPE_STRING;
                bind[30].buffer= (char *)add_info1;
                bind[30].buffer_length= 20;
                bind[30].is_null= &is_null[30];
                length[30] = strlen(add_info1);
                bind[30].length= &length[30];

                /* VARCHAR COLUMN */
                bind[31].buffer_type= MYSQL_TYPE_STRING;
                bind[31].buffer= (char *)add_info2;
                bind[31].buffer_length= 20;
                bind[31].is_null= &is_null[31];
                length[31] = strlen(add_info2);
                bind[31].length= &length[31];
            }
            catch(...)
            {
                return -3775;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3751;
            }
            if (stmt_bind_param)
            {
                return -3751;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3752;
            }
            if (param_count != 32)
            {
                return -3752;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3753;
            }
            if (stmt_execute)
            {
                return -3753;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3754;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Account info is inserted\n");
            }
            else
            {
                printf("Account info is updated\n");
            }
        }
        else
        {
            return -3750;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3755;
        }
    }
    else
    {
        return -3748;
    }
    return 0;
}

int accountInfo::Delete_accountInfo()
{
    try
    {
        gid = 130000;
        strcpy(tickets, "");
        ticket_type = 255;
        strcpy(plate, "");
        access_group = 0;
        inner_group = 0;
        time_group = 0;
        lots_group = 0;
        account_state = 0;
        parking_type = 0;
        strcpy(addr, "");
        strcpy(description, "");
        strcpy(email, "");
        strcpy(phone, "");
        strcpy(owner_name, "");
        strcpy(hour_ticket_num, "");
        hour_ticket_type = 0;
        lot_id = 0;
        strcpy(online_member, "");
        prepaid_charge_rule = 0;
        monthly_charge_rule = 0;
        ticket_lpbind = 0;
        monthly_type = 0;
        _operator = 0;
        strcpy(photo_id, "");
        strcpy(add_info1, "");
        strcpy(add_info2, "");
        start_time = 0;
        end_time = 0;
        limit_time = 0;
        create_time = 0;
    }
    catch(...)
    {
        return -3776;
    }
    std::string statment = "DELETE FROM `v32_account_info` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3757;
        }
        if (!stmt)
        {
            return -3757;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3758;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3759;
            }
            if (stmt_bind_param)
            {
                return -3759;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3760;
            }
            if (param_count != 1)
            {
                return -3760;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3761;
            }
            if (stmt_execute)
            {
                return -3761;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3762;
            }
            if (stmt_affected_rows < 1)
            {
                return -3762;
            }
        }
        else
        {
            return -3758;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3763;
        }
    }
    else
    {
        return -3756;
    }
    id = 0;
    return 0;
}

int accountInfo::Delete_all_accountInfo()
{
    std::string statment = "DELETE FROM `v32_account_info`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3765;
        }
        if (!stmt)
        {
            return -3765;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3766;
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
                return -3767;
            }
            if (stmt_execute)
            {
                return -3767;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
                printf("Delete (%d) Records\n", stmt_affected_rows);
            }
            catch(...)
            {
                return -3768;
            }
            if (stmt_affected_rows < 1)
            {
                return -3768;
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
            return -3769;
        }
    }
    else
    {
        return -3764;
    }
    return 0;
}