#include "photo.h"

photo::photo(MYSQL *_mysql)
{
    mysql = _mysql;
}

photo::~photo()
{
    
}

int photo::print_photo()
{
    try
    {
        printf("%d %d %s %s %s %ld %s %s %d %s %s %s %s %s %d %s %s %d %s %ld %s %s %s %s\n",
            id,
            gid,
            country,
            camera_address,
            photo_name,
            receive_time,
            object_type,
            original_bounding_box,
            speed,
            driving_direction,
            master_of_car,
            plate_number,
            ticket,
            garage_event_type,
            garage_event_serial,
            plate_color,
            plate_type,
            event_lane,
            event_type,
            event_time,
            vehicle_color,
            vehicle_size,
            vehicle_type,
            photo_path);
    }
    catch(...)
    {
        return -4236;
    }
    return 0;
}

int photo::Select_photo_by_ID(int index)
{
    short id_;
    std::string statment = "SELECT *,UNIX_TIMESTAMP(receive_time),UNIX_TIMESTAMP(event_time) FROM v32_photo WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4202;
        }
        if (!stmt)
        {
            return -4202;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4203;
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
                return -4204;
            }
            if (stmt_bind_param)
            {
                return -4204;
            }
            
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4205;
            }
            if (param_count != 1)
            {
                return -4205;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -4206;
            }
            if (!prepare_meta_result)
            {
                return -4206;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -4207;
            }
            if (column_count != 26)
            {
                return -4207;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4208;
            }
            if (stmt_execute)
            {
                return -4208;
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
                bind[2].buffer= (char *)country;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)camera_address;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];
                
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)photo_name;
                bind[4].buffer_length= 50;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[5].buffer= (char *)&receive_t;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];
                
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)object_type;
                bind[6].buffer_length= 50;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];
                
                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)original_bounding_box;
                bind[7].buffer_length= 50;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];
                
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&speed;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
                
                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)driving_direction;
                bind[9].buffer_length= 50;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];
                
                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)master_of_car;
                bind[10].buffer_length= 50;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];
                
                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)plate_number;
                bind[11].buffer_length= 12;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];
                
                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];
                
                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)garage_event_type;
                bind[13].buffer_length= 20;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];
                
                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&garage_event_serial;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)plate_color;
                bind[15].buffer_length= 50;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)plate_type;
                bind[16].buffer_length= 50;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&event_lane;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)event_type;
                bind[18].buffer_length= 50;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[19].buffer= (char *)&event_t;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)vehicle_color;
                bind[20].buffer_length= 50;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)vehicle_size;
                bind[21].buffer_length= 50;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* STRING COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_STRING;
                bind[22].buffer= (char *)vehicle_type;
                bind[22].buffer_length= 50;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)photo_path;
                bind[23].buffer_length= 255;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* STRING COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&receive_time;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];

                /* STRING COLUMN */
                bind[25].buffer_type= MYSQL_TYPE_LONG;
                bind[25].buffer= (char *)&event_time;
                bind[25].is_null= &is_null[25];
                bind[25].length= &length[25];
            }
            catch(...)
            {
                return -4237;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -4209;
            }
            if (stmt_bind_result)
            {
                return -4209;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -4210;
            }
            if (stmt_store_result)
            {
                return -4210;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -4211;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -4212;
            }
        }
        else
        {
            return -4203;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4213;
        }
    }
    else
    {
        return -4201;
    }
    return 0;
}

int photo::Insert_photo()
{
    std::string statment = "INSERT INTO `v32_photo` (`id`, `gid`, `country`, `camera_address`, `photo_name`, `receive_time`, `object_type`, `original_bounding_box`, `speed`, `driving_direction`, `master_of_car`, `plate_number`, `ticket`, `garage_event_type`, `garage_event_serial`, `plate_color`, `plate_type`, `event_lane`, `event_type`, `event_time`, `vehicle_color`, `vehicle_size`, `vehicle_type`, `photo_path`) VALUES ( ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), ?, ?, ?, ?)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4215;
        }
        if (!stmt)
        {
            return -4215;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4216;
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
                bind[2].buffer= (char *)country;
                bind[2].buffer_length= 50;
                bind[2].is_null= &is_null[2];
                length[2] = strlen(country);
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_STRING;
                bind[3].buffer= (char *)camera_address;
                bind[3].buffer_length= 50;
                bind[3].is_null= &is_null[3];
                length[3] = strlen(camera_address);
                bind[3].length= &length[3];
                
                bind[4].buffer_type= MYSQL_TYPE_STRING;
                bind[4].buffer= (char *)photo_name;
                bind[4].buffer_length= 50;
                bind[4].is_null= &is_null[4];
                length[4] = strlen(photo_name);
                bind[4].length= &length[4];

                bind[5].buffer_type= MYSQL_TYPE_LONG;
                bind[5].buffer= (char *)&receive_t;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];
                
                bind[6].buffer_type= MYSQL_TYPE_STRING;
                bind[6].buffer= (char *)object_type;
                bind[6].buffer_length= 50;
                bind[6].is_null= &is_null[6];
                length[6] = strlen(object_type);
                bind[6].length= &length[6];
                
                bind[7].buffer_type= MYSQL_TYPE_STRING;
                bind[7].buffer= (char *)original_bounding_box;
                bind[7].buffer_length= 50;
                bind[7].is_null= &is_null[7];
                length[7] = strlen(original_bounding_box);
                bind[7].length= &length[7];
                
                bind[8].buffer_type= MYSQL_TYPE_LONG;
                bind[8].buffer= (char *)&speed;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];
                
                bind[9].buffer_type= MYSQL_TYPE_STRING;
                bind[9].buffer= (char *)driving_direction;
                bind[9].buffer_length= 50;
                bind[9].is_null= &is_null[9];
                length[9] = strlen(driving_direction);
                bind[9].length= &length[9];
                
                bind[10].buffer_type= MYSQL_TYPE_STRING;
                bind[10].buffer= (char *)master_of_car;
                bind[10].buffer_length= 50;
                bind[10].is_null= &is_null[10];
                length[10] = strlen(master_of_car);
                bind[10].length= &length[10];
                
                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_STRING;
                bind[11].buffer= (char *)plate_number;
                bind[11].buffer_length= 12;
                bind[11].is_null= &is_null[11];
                length[11] = strlen(plate_number);
                bind[11].length= &length[11];
                
                /* SHORT COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)ticket;
                bind[12].buffer_length= 20;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(ticket);
                bind[12].length= &length[12];
                
                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_STRING;
                bind[13].buffer= (char *)garage_event_type;
                bind[13].buffer_length= 20;
                bind[13].is_null= &is_null[13];
                length[13] = strlen(garage_event_type);
                bind[13].length= &length[13];
                
                /* SHORT COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_LONG;
                bind[14].buffer= (char *)&garage_event_serial;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* SHORT COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)plate_color;
                bind[15].buffer_length= 50;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(plate_color);
                bind[15].length= &length[15];

                /* SHORT COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_STRING;
                bind[16].buffer= (char *)plate_type;
                bind[16].buffer_length= 50;
                bind[16].is_null= &is_null[16];
                length[16] = strlen(plate_type);
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&event_lane;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_STRING;
                bind[18].buffer= (char *)event_type;
                bind[18].buffer_length= 50;
                bind[18].is_null= &is_null[18];
                length[18] = strlen(event_type);
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_LONG;
                bind[19].buffer= (char *)&event_t;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* SHORT COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_STRING;
                bind[20].buffer= (char *)vehicle_color;
                bind[20].buffer_length= 50;
                bind[20].is_null= &is_null[20];
                length[20] = strlen(vehicle_color);
                bind[20].length= &length[20];

                /* SHORT COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_STRING;
                bind[21].buffer= (char *)vehicle_size;
                bind[21].buffer_length= 50;
                bind[21].is_null= &is_null[21];
                length[21] = strlen(vehicle_size);
                bind[21].length= &length[21];

                /* STRING COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_STRING;
                bind[22].buffer= (char *)vehicle_type;
                bind[22].buffer_length= 50;
                bind[22].is_null= &is_null[22];
                length[22] = strlen(vehicle_type);
                bind[22].length= &length[22];

                /* SHORT COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_STRING;
                bind[23].buffer= (char *)photo_path;
                bind[23].buffer_length= 255;
                bind[23].is_null= &is_null[23];
                length[23] = strlen(photo_path);
                bind[23].length= &length[23];
            }
            catch(...)
            {
                return -4238;
            }
            
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -4217;
            }
            if (stmt_bind_param)
            {
                return -4217;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4218;
            }
            if (param_count != 24)
            {
                return -4218;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4219;
            }
            if (stmt_execute)
            {
                return -4219;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4220;
            }
            if (stmt_affected_rows != 1)
            {
                return -4220;
            }
        }
        else
        {
            return -4216;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4221;
        }
    }
    else
    {
        return -4214;
    }
    return 0;
}

int photo::Delete_photo()
{
    try
    {
        gid = 0;
        strcpy(country, "");
        strcpy(photo_name, "");
        receive_time = 0;
        strcpy(object_type, "");
        strcpy(original_bounding_box, "");
        speed = 0;
        strcpy(driving_direction, "");
        strcpy(master_of_car, "");
        strcpy(plate_number, "");
        strcpy(ticket, "");
        strcpy(garage_event_type, "");
        garage_event_serial = 0;
        strcpy(plate_color, "");
        strcpy(plate_type, "");
        event_lane = 0;
        strcpy(event_type, "");
        event_time = 0;
        strcpy(vehicle_color, "");
        strcpy(vehicle_size, "");
        strcpy(vehicle_type, "");
        strcpy(photo_path, "");
    }
    catch(...)
    {
        return -4239;
    }
    short id_;
    std::string statment = "DELETE FROM `v32_photo` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4223;
        }
        if (!stmt)
        {
            return -4223;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4224;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type = MYSQL_TYPE_SHORT;
                bind_param[0].buffer = (char *)&id_;
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -4225;
            }
            if (stmt_bind_param)
            {
                return -4225;
            }
            id_ = id;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -4226;
            }
            if (param_count != 1)
            {
                return -4226;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -4227;
            }
            if (stmt_execute)
            {
                return -4227;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4228;
            }
            if (stmt_affected_rows < 1)
            {
                return -4228;
            }    
        }
        else
        {
            return -4224;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4229;
        }
    }
    else
    {
        return -4222;
    }
    id = 0;
    return 0;
}

int photo::Delete_all_photo()
{
    std::string statment = "DELETE FROM `v32_photo`";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -4231;
        }
        if (!stmt)
        {
            return -4231;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -4232;
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
                return -4233;
            }
            if (stmt_execute)
            {
                return -4233;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -4234;
            }
            if (stmt_affected_rows < 1)
            {
                return -4234;
            }    
        }
        else
        {
            return -4232;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -4235;
        }
    }
    else
    {
        return -4230;
    }
    return 0;
}