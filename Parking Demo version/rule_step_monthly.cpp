#include "rule_step_monthly.h"

rule_step_monthly::rule_step_monthly(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

rule_step_monthly::~rule_step_monthly()
{
    
}

int rule_step_monthly::print_rule_step_monthly()
{
    try
    {
        printf("%ld %ld %ld %ld %ld %ld %d %d %ld\n",
            gid,
            rule_serial,
            step_serial,
            max_units,
            duration,
            unit_sum,
            flag,
            _operator,
            createtime);
    }
    catch(...)
    {
        return -2538;
    }
    return 0;
}

int rule_step_monthly::Select_rule_step_monthly_by_serial(int garage_id, int _rule_serial, int _step_serial)
{
    int _gid;
    int _rule_ser;
    int _step_ser;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_rule_step_monthly WHERE `gid`= ? and `rule_serial` = ? and `step_serial` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2502;
        }
        if (!stmt)
        {
            return -2502;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2503;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));

                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&_gid;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&_rule_ser;

                bind_param[2].buffer_type= MYSQL_TYPE_LONG;
                bind_param[2].buffer= (char *)&_step_ser;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2504;
            }
            if (stmt_bind_param)
            {
                return -2504;
            }
                   
            _gid = garage_id;
            _rule_ser = _rule_serial;
            _step_ser = _step_serial;

            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2505;
            }
            if (param_count != 3)
            {
                return -2505;
            }

            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2506;
            }
            if (!prepare_meta_result)
            {
                return -2506;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2507;
            }
            if (column_count != 10) /* validate column count */
            {
                return -2507;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2508;
            }
            if (stmt_execute)
            {
                return -2508;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&gid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&rule_serial;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&step_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&max_units;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&duration;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&unit_sum;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&flag;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&_operator;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* TIMESTAMP COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[8].buffer= (char *)&crt;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* INTEGER COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_LONG;
                bind[9].buffer= (char *)&createtime;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];
            }
            catch(...)
            {
                return -2539;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2509;
            }
            if (stmt_bind_result)
            {
                return -2509;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2510;
            }
            if (stmt_store_result)
            {
                return -2510;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2511;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2512;
            }
        }
        else
        {
            return -2503;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2513;
        }
    }
    else
    {
        return -2501;
    }
    return 0;
}

int rule_step_monthly::Insert_Update_rule_step_monthly()
{
    std::string statment = "INSERT INTO `v32_rule_step_monthly` (`gid`, `rule_serial`, `step_serial`, `max_units`, `duration`, `unit_sum`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE gid=VALUES(gid), rule_serial=VALUES(rule_serial), step_serial=VALUES(step_serial), max_units=VALUES(max_units), duration=VALUES(duration), unit_sum=VALUES(unit_sum), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2515;
        }
        if (!stmt)
        {
            return -2515;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2516;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&gid;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&rule_serial;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&step_serial;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_LONG;
                bind[3].buffer= (char *)&max_units;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_LONG;
                bind[4].buffer= (char *)&duration;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&unit_sum;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&flag;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&_operator;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* TIMESTAMP COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&createtime;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
            }
            catch(...)            
            {
                return -2540;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)            
            {
                return -2517;
            }
            if (stmt_bind_param)
            {
                return -2517;
            }
            
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)            
            {
                return -2518;
            }
            if (param_count != 9) /* validate parameter count */
            {
                return -2518;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2519;
            }
            if (stmt_execute)
            {
                return -2519;
            }
            
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2520;
            }
            if (stmt_affected_rows == 1)
            {
                printf("rule step monthly is inserted\n");
            }
            else
            {
                printf("rule step monthly is updated\n");
            }
        }
        else
        {
            return -2516;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2521;
        }
    }
    else
    {
        return -2514;
    }
    return 0;
}

int rule_step_monthly::Delete_rule_step_monthly()
{
    try
    {
        max_units = 0;
        duration = 0;
        unit_sum = 0;
        flag = 0;
        _operator = 0;
        createtime = 0;
    }
    catch(...)
    {
        return -2541;
    }
    std::string statment = "DELETE FROM `v32_rule_step_monthly` WHERE `gid`= ? and `rule_serial` = ? and `step_serial` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2523;
        }
        if (!stmt)
        {
            return -2523;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2524;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind_param));        
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&gid;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&rule_serial;

                bind_param[2].buffer_type= MYSQL_TYPE_LONG;
                bind_param[2].buffer= (char *)&step_serial;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2525;
            }
            if (stmt_bind_param)
            {
                return -2525;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2526;
            }
            if (param_count != 3)
            {
                return -2526;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2527;
            }
            if (stmt_execute)
            {
                return -2527;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2528;
            }
            if (stmt_affected_rows < 1)
            {
                return -2528;
            }    
        }
        else
        {
            return -2524;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2529;
        }
    }
    else
    {
        return -2522;
    }
    gid = 0;
    rule_serial = -1;
    step_serial = -1;
    return 0;
}

int rule_step_monthly::Delete_all_rule_step_monthly(int garage_id, int _rule_serial)
{
    int _gid;
    int _rule_ser;
    std::string statment = "DELETE FROM `v32_rule_step_monthly` WHERE `gid`= ? and `rule_serial` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2531;
        }
        if (!stmt)
        {
            return -2531;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2532;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind_param));        
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&_gid;

                bind_param[1].buffer_type= MYSQL_TYPE_LONG;
                bind_param[1].buffer= (char *)&_rule_ser;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2533;
            }
            if (stmt_bind_param)
            {
                return -2533;
            }
            
            _gid = garage_id;
            _rule_ser = _rule_serial;
            
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2534;
            }
            if (param_count != 2)
            {
                return -2534;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2535;
            }
            if (stmt_execute)
            {
                return -2535;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2536;
            }
            if(stmt_affected_rows < 1)
            {
                return -2536;
            }
            else
            {
                printf("Delete (%d) Records\n", stmt_affected_rows);
            }
        }
        else
        {
            return -2532;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2537;
        }
    }
    else
    {
        return -2530;
    }
    return 0;
}

