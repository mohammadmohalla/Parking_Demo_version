#include "sys_user.h"

sys_user::sys_user(MYSQL *_mysql)
{
    mysql = _mysql;
}

sys_user::~sys_user()
{

}

int sys_user::Print_sys_user()
{
    try
    {
        printf("%d %s %s %s %ld %s %s %s %s %s %ld %d %ld %d %ld %d %d %s\n",
            id,
            full_name,
            username,
            password_hash,
            dob_time,
            mobile,
            phone,
            email,
            photo,
            login_from_ip,
            last_login_time,
            is_blocked,
            block_time,
            is_locked,
            lock_time,
            password_try_counter,
            first_login_success,
            authorities);
    }
    catch(...)
    {
        return -4130;
    }
    return 0;
}

int sys_user::select_sys_user(int index)
{
    int id_;
    std::string statment = "SELECT * , Unix_Timestamp(dob), Unix_Timestamp(last_login), Unix_Timestamp(block_date), Unix_Timestamp(lock_date) FROM sys_user WHERE id=?;";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4102;
        }
        if (!stmt)
        {
            return -4102;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4103;
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
                return -4104;
            }
            if (stmt_bind_param)
            {
                return -4104;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4105;
            }
            if (param_count != 1)
            {
                return -4105;
            }

            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -4106;
            }
            if (!prepare_meta_result)
            {
                return -4106;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -4107;
            }
            if (column_count != 23) /* validate column count */
            {
                return -4107;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4108;
            }
            if (stmt_execute)
            {
                return -4108;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_LONG;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_STRING;
                bind[1].buffer= (char *)full_name;
                bind[1].buffer_length = 255;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)username;
                bind[2].buffer_length = 255;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)password_hash;
                bind[3].buffer_length = 255;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_TIME;
                bind[4].buffer= (char *)&dob_t;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)mobile;
                bind[5].buffer_length = 255;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)phone;
                bind[6].buffer_length = 255;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)email;
                bind[7].buffer_length = 255;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)photo;
                bind[8].buffer_length = 255;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
                
                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)login_from_ip;
                bind[9].buffer_length = 255;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];
                
                bind[10].buffer_type= MYSQL_TYPE_TIME;
                bind[10].buffer= (char *)&last_login_t;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&is_blocked;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];
                
                bind[12].buffer_type= MYSQL_TYPE_TIME;
                bind[12].buffer= (char *)&block_t;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&is_locked;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];
                
                bind[14].buffer_type= MYSQL_TYPE_TIME;
                bind[14].buffer= (char *)&lock_t;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];
                
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&password_try_counter;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&first_login_success;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)authorities;
                bind[17].buffer_length = 255;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];
                
                bind[18].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[18].buffer= (char *)&dob_time;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                bind[19].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[19].buffer= (char *)&dob_time;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];
                
                bind[20].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[20].buffer= (char *)&last_login_time;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];
                
                bind[21].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[21].buffer= (char *)&block_time;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];
                
                bind[22].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[22].buffer= (char *)&lock_time;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];
            }
            catch(...)
            {
                return -4132;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -4109;
            }
            if (stmt_bind_result)
            {
                return -4109;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -4110;
            }
            if (stmt_store_result)
            {
                return -4110;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -4111;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -4112;
            }
        }
        else
        {
            return -4103;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4113;
        }
    }
    else
    {
        return -4101;
    }
    return 0;
}
    
int sys_user::insert_update_sys_user()
{
    std::string statment = "INSERT INTO `sys_user` (`id`, `full_name`, `username`, `password_hash`, `dob`, `mobile`, `phone`, `email`, `photo`, `login_from_ip`, `last_login`, `is_blocked`, `block_date`, `is_locked`, `lock_date`, `password_try_counter`, `first_login_success`, `authorities`) VALUES (?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, FROM_UNIXTIME(?), ?, ?, ?) ON DUPLICATE KEY UPDATE id=VALUES(id), full_name=VALUES(full_name), username=VALUES(username), password_hash=VALUES(password_hash), dob=VALUES(dob), mobile=VALUES(mobile), phone=VALUES(phone), email=VALUES(email), photo=VALUES(photo), login_from_ip=VALUES(login_from_ip), last_login=VALUES(last_login), is_blocked=VALUES(is_blocked), block_date=VALUES(block_date), is_locked=VALUES(is_locked), lock_date=VALUES(lock_date), password_try_counter=VALUES(password_try_counter), first_login_success=VALUES(first_login_success), authorities=VALUES(authorities);";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4115;
        }
        if (!stmt)
        {
            return -4115;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4116;
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

                bind[1].buffer_type= MYSQL_TYPE_STRING;
                bind[1].buffer= (char *)full_name;
                bind[1].buffer_length = 255;
                bind[1].is_null= &is_null[1];
                length[1] = strlen(full_name);
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_STRING;
                bind[2].buffer= (char *)username;
                bind[2].buffer_length = 255;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(username);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)password_hash;
                bind[3].buffer_length = 255;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(password_hash);
                bind[3].length= &length[3];

                bind[4].buffer_type= MYSQL_TYPE_TIME;
                bind[4].buffer= (char *)&dob_t;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_STRING;
                bind[5].buffer= (char *)mobile;
                bind[5].buffer_length = 255;
                bind[5].is_null= &is_null[5];
                length[5] = strlen(mobile);
                bind[5].length= &length[5];

                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)phone;
                bind[6].buffer_length = 255;
                bind[6].is_null= &is_null[6];
                length[6] = strlen(phone);
                bind[6].length= &length[6];

                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)email;
                bind[7].buffer_length = 255;
                bind[7].is_null= &is_null[7];
                length[7] = strlen(email);
                bind[7].length= &length[7];

                bind[8].buffer_type= MYSQL_TYPE_STRING;
                bind[8].buffer= (char *)photo;
                bind[8].buffer_length = 255;
                bind[8].is_null= &is_null[8];
                length[8] = strlen(photo);
                bind[8].length= &length[8];
                
                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)login_from_ip;
                bind[9].buffer_length = 255;
                bind[9].is_null= &is_null[9];
                length[9] = strlen(login_from_ip);
                bind[9].length= &length[9];
                
                bind[10].buffer_type= MYSQL_TYPE_TIME;
                bind[10].buffer= (char *)&last_login_t;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                bind[11].buffer_type= MYSQL_TYPE_LONG;
                bind[11].buffer= (char *)&is_blocked;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];
                
                bind[12].buffer_type= MYSQL_TYPE_TIME;
                bind[12].buffer= (char *)&block_t;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                bind[13].buffer_type= MYSQL_TYPE_LONG;
                bind[13].buffer= (char *)&is_locked;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];
                
                bind[14].buffer_type= MYSQL_TYPE_TIME;
                bind[14].buffer= (char *)&lock_t;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];
                
                bind[15].buffer_type= MYSQL_TYPE_LONG;
                bind[15].buffer= (char *)&password_try_counter;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&first_login_success;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                bind[17].buffer_type= MYSQL_TYPE_STRING;
                bind[17].buffer= (char *)authorities;
                bind[17].buffer_length = 255;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];
            }
            catch(...)
            {
                return -4132;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -4117;
            }
            if (stmt_bind_param)
            {
                return -4117;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4118;
            }
            if (param_count != 18) /* validate parameter count */
            {
                return -4118;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4119;
            }
            if (stmt_execute)
            {
                return -4119;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4120;
            }
            if (stmt_affected_rows == 1)
            {
                fprintf(stderr, "system user inserted\n");
            }
            else
            {
                fprintf(stderr, "system user updated\n");
            }
        }
        else
        {
            return -4116;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4121;
        }
    }
    else
    {
        return -4114;
    }
    return 0;
}
    
int sys_user::delete_sys_user()
{
    try
    {
        strcpy(full_name, "");
        strcpy(username, "");
        strcpy(password_hash, "");
        dob_time = 0;
        strcpy(mobile, "");
        strcpy(phone, "");
        strcpy(email, "");
        strcpy(photo, "");
        strcpy(login_from_ip, "");
        last_login_time = 0;
        is_blocked = 0;
        block_time = 0;
        is_locked = 0;
        lock_time = 0;
        password_try_counter = 0;
        first_login_success = 0;
        strcpy(authorities, "");
    }
    catch(...)
    {
        return -4133;
    }
    int id_;
    std::string statment = "DELETE FROM `sys_user` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4123;
        }
        if (!stmt)
        {
            return -4123;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4124;
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
                return -4125;
            }
            if (stmt_bind_param)
            {
                return -4125;
            }
            id_ = id;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4126;
            }
            if (param_count != 1)
            {
                return -4126;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4127;
            }
            if (stmt_execute)
            {
                return -4127;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4128;
            }
            if (stmt_affected_rows < 1)
            {
                return -4128;
            }    
        }
        else
        {
            return -4124;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4129;
        }
    }
    else
    {
        return -4122;
    }
    id = 0;
    return 0;
}

