#include "rule_name_monthly.h"

rule_name_monthly::rule_name_monthly(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

rule_name_monthly::~rule_name_monthly()
{
    
}

int rule_name_monthly::print_rule_name_monthly()
{
    try
    {
        printf("%ld %ld %s %s %d %d %ld\n",
            gid,
            rule_serial,
            name,
            remark,
            flag,
            _operator,
            createtime);
    }
    catch(...)
    {
        return -2430;
    }
    return 0;
}

int rule_name_monthly::Select_rule_name_monthly_by_serial(int _serial, int garage_id)
{
    int sr_idx;
    int _gid;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_rule_name_monthly WHERE gid = ? and rule_serial = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2402;
        }
        if (!stmt)
        {
            return -2402;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2403;
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
                bind_param[1].buffer= (char *)&sr_idx;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2404;
            }
            if (stmt_bind_param)
            {
                return -2404;
            }
                   
            sr_idx = _serial;
            _gid = garage_id;

            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2405;
            }
            if (param_count != 2)
            {
                return -2405;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2406;
            }
            if (!prepare_meta_result)
            {
                return -2406;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2407;
            }
            if (column_count != 8)
            {
                return -2407;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2408;
            }
            if (stmt_execute)
            {
                return -2408;
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

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)&remark;
                bind[3].buffer_length= 200;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&flag;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&_operator;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* TIMESTAMP COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[6].buffer= (char *)&crt;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* INTEGER COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&createtime;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];
            }
            catch(...)
            {
                return -2431;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2409;
            }
            if (stmt_bind_result)
            {
                return -2409;
            }
            
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2410;
            }
            if (stmt_store_result)
            {
                return -2410;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2411;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2412;
            }
        }
        else
        {
            return -2403;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2413;
        }
    }
    else
    {
        return -2401;
    }
    return 0;
}

int rule_name_monthly::Insert_Update_rule_name_monthly()
{
    std::string statment = "INSERT INTO `v32_rule_name_monthly` (`gid`, `rule_serial`, `name`, `remark`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE gid=VALUES(gid), rule_serial=VALUES(rule_serial), name=VALUES(name), remark=VALUES(remark), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2415;
        }
        if (!stmt)
        {
            return -2415;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2416;
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

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(name);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)remark;
                bind[3].buffer_length= 200;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(remark);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&flag;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&_operator;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* TIMESTAMP COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&createtime;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];
            }
            catch(...)
            {
                return -2432;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2417;
            }
            if (stmt_bind_param)
            {
                return -2417;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2418;
            }
            if (param_count != 7) /* validate parameter count */
            {
                return -2418;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2419;
            }
            if (stmt_execute)
            {
                return -2419;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2420;
            }
            if (stmt_affected_rows == 1)
            {
                printf("monthly rule name is inserted\n");
            }
            else
            {
                printf("monthly rule name is updated\n");
            }
        }
        else
        {
            return -2416;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2421;
        }
    }
    else
    {
        return -2414;
    }
    return 0;
}

int rule_name_monthly::Delete_rule_name_monthly()
{
    try
    {
        strcpy(name, "");
        strcpy(remark, "");
        flag = 0;
        _operator = 0;
        createtime = 0;
    }
    catch(...)
    {
        return -2433;
    }
    std::string statment = "DELETE FROM `v32_rule_name_monthly` WHERE `gid`= ? and `rule_serial` = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2423;
        }
        if (!stmt)
        {
            return -2423;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2424;
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
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2425;
            }
            if (stmt_bind_param)
            {
                return -2425;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2426;
            }
            if (param_count != 2)
            {
                return -2426;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2427;
            }
            if (stmt_execute)
            {
                return -2427;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2428;
            }
            if (stmt_affected_rows < 1)
            {
                return -2428;
            }    
        }
        else
        {
            return -2424;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2428;
        }
    }
    else
    {
        return -2422;
    }
    gid = 0;
    rule_serial = -1;
    return 0;
    
}
