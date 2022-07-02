#include "event_payment.h"

event_payment::event_payment(MYSQL *_mysql)
{
    mysql = _mysql;
}

event_payment::~event_payment()
{
    
}

int event_payment::print_event_payment()
{
    try
    {
        printf("%ld %d %ld %d %ld %d %s %d %s %d %d %d %d %d %d\n",
            aid,
            gid,
            event_time,
            serial,
            rece_time,
            type,
            ticket,
            ticket_type,
            plate,
            currency_sum,
            coin_sum,
            currency_balance,
            coin_balance,
            _operator,
            site);
    }
    catch(...)
    {
        return -3336;
    }
    return 0;
}

int event_payment::Select_payment_event_by_id(int index)
{
    int id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(event_time),UNIX_TIMESTAMP(rece_time) FROM v32_event_payment WHERE aid=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3302;
        }
        if (!stmt)
        {
            return -3302;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3303;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3304;
            }
            if (stmt_bind_param)
            {
                return -3304;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3305;
            }
            if (param_count != 1)
            {
                return -3305;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -3306;
            }
            if (!prepare_meta_result)
            {
                return -3306;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -3307;
            }
            if (column_count != 15) /* validate column count */
            {
                return -3307;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3308;
            }
            if (stmt_execute)
            {
                return -3308;
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

                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&event_time;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&rece_time;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)ticket;
                bind[6].buffer_length= 20;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&ticket_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)plate;
                bind[8].buffer_length= 12;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&currency_sum;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&coin_sum;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&currency_balance;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&coin_balance;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&_operator;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_SHORT;
                bind[14].buffer= (char *)&site;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];
            }
            catch(...)
            {
                return -3337;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -3309;
            }
            if (stmt_bind_result)
            {
                return -3309;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -3310;
            }
            if (stmt_store_result)
            {
                return -3310;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -3311;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -3312;
            }
        }
        else
        {
            return -3303;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3313;
        }
    }
    else
    {
        return -3301;
    }
    return 0;
}

int event_payment::Insert_payment_event()
{
    std::string statment = "INSERT INTO `v32_event_payment` (`aid`, `gid`, `event_time`, `serial`, `rece_time`, `type`, `ticket`, `ticket_type`, `plate`, `currency_sum`, `coin_sum`, `currency_balance`, `coin_balance`, `operator`, `site`) VALUES ( ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3315;
        }
        if (!stmt)
        {
            return -3315;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3316;
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

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&event_time;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&serial;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&rece_time;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&type;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)ticket;
                bind[6].buffer_length= 20;
                bind[6].is_null= &is_null[6];
                length[6] = strlen(ticket);
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&ticket_type;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)plate;
                bind[8].buffer_length= 12;
                bind[8].is_null= &is_null[8];
                length[8] = strlen(plate);
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&currency_sum;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_LONG;
                bind[10].buffer= (char *)&coin_sum;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&currency_balance;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_LONG;
                bind[12].buffer= (char *)&coin_balance;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* STRING COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&_operator;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_SHORT;
                bind[14].buffer= (char *)&site;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];
            }
            catch(...)
            {
                return -3338;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -3317;
            }
            if (stmt_bind_param)
            {
                return -3317;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3318;
            }
            if (param_count != 15) /* validate parameter count */
            {
                return -3318;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3319;
            }
            if (stmt_execute)
            {
                return -3319;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3320;
            }
            if (stmt_affected_rows != 1)
            {
                return -3320;
            }
        }
        else
        {
            return -3316;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3321;
        }
    }
    else
    {
        return -3314;
    }
    return 0;
}

int event_payment::Delete_Payment_event()
{
    try
    {
        gid = 13000;
        _operator = 0;
        serial = 0;
        type = 0;
        strcpy(ticket, "");
        ticket_type = 0;
        strcpy(plate, "");
        currency_sum = 0;
        coin_sum = 0;
        currency_balance = 0;
        coin_balance = 0;
        site = 255;
        event_time = 0;
        rece_time = 0;
    }
    catch(...)
    {
        return -3339;
    }
    int id_;
    std::string statment = "DELETE FROM `v32_event_payment` WHERE `aid`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3323;
        }
        if (!stmt)
        {
            return -3323;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3324;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_LONG;
                bind_param[0].buffer = (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -3325;
            }
            if (stmt_bind_param)
            {
                return -3325;
            }
            id_ = aid;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -3326;
            }
            if (param_count != 1)
            {
                return -3326;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -3327;
            }
            if (stmt_execute)
            {
                return -3327;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3328;
            }
            if (stmt_affected_rows < 1)
            {
                return -3328;
            }    
        }
        else
        {
            return -3324;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3329;
        }
    }
    else
    {
        return -3322;
    }
    aid = 0;
    return true;
    
}

int event_payment::Delete_All_Payment_Events()
{
    std::string statment = "DELETE FROM `v32_event_payment`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -3331;
        }
        if (!stmt)
        {
            return -3331;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -3332;
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
                return -3333;
            }
            if (stmt_execute)
            {
                return -3333;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -3334;
            }
            if (stmt_affected_rows < 1)
            {
                return -3334;
            }   
        }
        else
        {
            return -3332;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -3335;
        }
    }
    else
    {
        return -3330;
    }
    return 0;
}