#include "monthly_to_hourly.h"

monthly_to_hourly_type::monthly_to_hourly_type(MYSQL *_mysql)
{
    mysql = _mysql;
    memset(bind_param, 0, sizeof(bind));
    memset(bind, 0, sizeof(bind));
    memset(is_null, 0, sizeof(is_null));
    memset(length, 0, sizeof(length));
}

monthly_to_hourly_type::~monthly_to_hourly_type()
{
    
}

int monthly_to_hourly_type::print_monthly_to_hourly_type()
{
    try
    {
        printf("%d\t%d\t%s\t%s\t%d\t%d\t%ld\n", 
            id, 
            gid, 
            name, 
            hour_charge_type, 
            flag, 
            _operator, 
            create_time);
    }
    catch(...)
    {
        return -1930;
    }
    return 0;
}

int monthly_to_hourly_type::Select_monthly_to_hourly_type_by_id(int index)
{
    int idx;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime) FROM v32_monthly_to_hourly WHERE id = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1902;
        }
        if (!stmt)
        {
            return -1902;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1903;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_LONG;
                bind_param[0].buffer= (char *)&idx;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1904;
            }
            if (stmt_bind_param)
            {
                return -1904;
            }
                   
            idx = index;

            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1905;
            }
            if (param_count != 1)
            {
                return -1905;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1906;
            }
            if (!prepare_meta_result)
            {
                return -1906;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1907;
            }
            if (column_count != 8) /* validate column count */
            {
                return -1907;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1908;
            }
            if (stmt_execute)
            {
                return -1908;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)hour_charge_type;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&flag;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
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
                bind[7].buffer= (char *)&create_time;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];
            }
            catch(...)
            {
                return -1931;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1909;
            }
            if (stmt_bind_result)
            {
                return -1909;
            }
            
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1910;
            }
            if (stmt_store_result)
            {
                return -1910;
            }
            
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1911;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1912;
            }
        }
        else
        {
            return -1903;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1913;
        }
    }
    else
    {
        return -1901;
    }
    return 0;
}

int monthly_to_hourly_type::Update_monthly_to_hourly_type()
{
    std::string statment = "INSERT INTO `v32_monthly_to_hourly` (`id`, `gid`, `name`, `hour_charge_type`, `flag`, `operator`, `createtime`) VALUES (?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE id=VALUES(id), gid=VALUES(gid), name=VALUES(name), hour_charge_type=VALUES(hour_charge_type), flag=VALUES(flag), operator=VALUES(operator), createtime=VALUES(createtime)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1915;
        }
        if (!stmt)
        {
            return -1915;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1916;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)name;          
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(name);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)hour_charge_type;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(hour_charge_type);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&flag;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&_operator;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&create_time;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];
            }
            catch(...)
            {
                return -1932;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1917;
            }
            if (stmt_bind_param)
            {
                return -1917;
            }
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1918;
            }
            if (param_count != 7)
            {
                return -1918;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1919;
            }
            if (stmt_execute)
            {
                return -1919;
            }
            
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1920;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "monthly to hourly is inserted\n");
            }
            else
            {
                fprintf(stderr, "monthly to hourly is updated\n");
            }
        }
        else
        {
            return -1916;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1921;
        }
    }
    else
    {
        return -1914;
    }
    return 0;
}

int monthly_to_hourly_type::Delete_monthly_to_hourly_type()
{
    try
    {
        gid = 0;
        _operator = 0;
        flag = 0;
        strcpy(name, "");
        strcpy(hour_charge_type, "");
        create_time = 0;
    }
    catch(...)
    {
        return -1933;
    }
    std::string statment = "DELETE FROM `v32_monthly_to_hourly` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1923;
        }
        if (!stmt)
        {
            return -1923;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1924;
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
                return -1925;
            }
            if (stmt_bind_param)
            {
                return -1925;
            }
            int param_count = 0;
            try
            {
                mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1926;
            }
            if (param_count != 1)
            {
                return -1926;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1927;
            }
            if (stmt_execute)
            {
                return -1927;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1928;
            }
            if (stmt_affected_rows < 1)
            {
                return -1928;
            }    
        }
        else
        {
            return -1924;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1929;
        }
    }
    else
    {
        return -1922;
    }
    id = 0;
    return 0;
    
}


