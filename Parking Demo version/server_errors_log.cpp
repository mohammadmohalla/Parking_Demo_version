#include "server_errors_log.h"

server_errors_log::server_errors_log(MYSQL *_mysql)
{
    mysql = _mysql;
}

server_errors_log::~server_errors_log()
{

}

int server_errors_log::Print_server_errors_log()
{
    try
    {
        printf("%d %d %s %s %s %ld %ld\n",
            id,
            gid,
            err_code,
            err_msg,
            err_pos,
            err_time,
            created_at);
    }
    catch(...)
    {
        return -2930;
    }
    return 0;
}

int server_errors_log::select_server_errors_log(int index)
{
    int id_;
    std::string statment = "SELECT * , Unix_Timestamp(err_time), Unix_Timestamp(created_at) FROM server_errors_log WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2902;
        }
        if (!stmt)
        {
            return -2902;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2903;
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
                return -2904;
            }
            if (stmt_bind_param)
            {
                return -2904;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2905;
            }
            if (param_count != 1)
            {
                return -2905;
            }

            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -2906;
            }
            if (!prepare_meta_result)
            {
                return -2906;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -2907;
            }
            if (column_count != 9) /* validate column count */
            {
                return -2907;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2908;
            }
            if (stmt_execute)
            {
                return -2908;
            }
            
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
                bind[2].buffer= (char *)&err_code;
                bind[2].buffer_length = 20;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)&err_msg;
                bind[3].buffer_length = 65535;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)&err_pos;
                bind[4].buffer_length = 255;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[5].buffer= (char *)&err_t;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[6].buffer= (char *)&created_t;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_LONG;
                bind[7].buffer= (char *)&err_time;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&created_at;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
            }
            catch(...)
            {
                return -2932;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -2909;
            }
            if (stmt_bind_result)
            {
                return -2909;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -2910;
            }
            if (stmt_store_result)
            {
                return -2910;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -2911;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -2912;
            }
        }
        else
        {
            return -2903;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2913;
        }
    }
    else
    {
        return -2901;
    }
    return 0;
}
    
int server_errors_log::insert_update_server_errors_log()
{
    std::string statment = "INSERT INTO `server_errors_log` (`id`, `gid`, `err_code`, `err_msg`, `err_pos`, `err_time`, `created_at`) VALUES (?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?)) ON DUPLICATE KEY UPDATE id=VALUES(id), gid=VALUES(gid), err_code=VALUES(err_code), err_msg=VALUES(err_msg), err_pos=VALUES(err_pos), err_time=VALUES(err_time), created_at=VALUES(created_at)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2915;
        }
        if (!stmt)
        {
            return -2915;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2916;
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
                bind[2].buffer= (char *)&err_code;
                bind[2].buffer_length = 20;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(err_code);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)&err_msg;
                bind[3].buffer_length = 65535;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(err_msg);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)&err_pos;
                bind[4].buffer_length = 255;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(err_pos);
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&err_time;
                is_null[5] = (err_time == -1);
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_LONG;
                bind[6].buffer= (char *)&created_at;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];
            }
            catch(...)
            {
                return -2932;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -2917;
            }
            if (stmt_bind_param)
            {
                return -2917;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2918;
            }
            if (param_count != 7) /* validate parameter count */
            {
                return -2918;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2919;
            }
            if (stmt_execute)
            {
                return -2919;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2920;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "server errors log inserted\n");
            }
            else
            {
                fprintf(stderr, "server errors log updated\n");
            }
        }
        else
        {
            return -2916;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2921;
        }
    }
    else
    {
        return -2914;
    }
    return 0;
}
    
int server_errors_log::delete_server_errors_log()
{
    try
    {
        gid = -1;
        strcpy(err_code, "");
        strcpy(err_msg, "");
        strcpy(err_pos, "");
        err_time = -1;
        created_at = 0;
    }
    catch(...)
    {
        return -2933;
    }
    int id_;
    std::string statment = "DELETE FROM `server_errors_log` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -2923;
        }
        if (!stmt)
        {
            return -2923;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -2924;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_SHORT;
                bind_param[0].buffer= (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -2925;
            }
            if (stmt_bind_param)
            {
                return -2925;
            }
            id_ = id;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -2926;
            }
            if (param_count != 1)
            {
                return -2926;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -2927;
            }
            if (stmt_execute)
            {
                return -2927;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -2928;
            }
            if (stmt_affected_rows < 1)
            {
                return -2928;
            }    
        }
        else
        {
            return -2924;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -2929;
        }
    }
    else
    {
        return -2922;
    }
    id = 0;
    return 0;
}

