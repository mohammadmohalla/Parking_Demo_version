#include "Site_type.h"

Site_type::Site_type(MYSQL *_mysql)
{
    mysql = _mysql;
}

Site_type::~Site_type()
{
    
}

int Site_type::print_site()
{
    try
    {
        printf("%d %d %d %d %d %d %d %d %d %d %d %d %s %d %s %s %d %d %d %d %ld %ld %d\n",
                id,
                gid,
                same_EntryExit_filter,
                same_EntryExit_group,
                same_EntryExit_site,
                hourlyParkingFullAccessDeny,
                monthlyParkingFullAccessDeny,
                oneCard_oneCar,
                _operator,
                id_PresetType_id,
                id_PresetSite_in_Site_Group,
                entryPresetLicensePlateNumber,
                cache_plate,
                cache_etype,
                site_Address,
                db_name,
                status,
                type,
                exitFreeLetPass,
                credentialMode,
                createtime,
                cache_time,
                season_to_hourly_swich);
    }
    catch(...)
    {
        return -1543;
    }
    return 0;
}

int Site_type::Select_Site_type_by_id(int index)
{
    short id_;
    std::string statment = "SELECT * ,Unix_Timestamp(createtime), Unix_Timestamp(cache_time) FROM v32_site WHERE id=?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1502;
        }
        if (!stmt)
        {
            return -1502;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1503;
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
                return -1504;
            }
            if(stmt_bind_param)
            {
                return -1504;
            }
            id_ = index;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1505;
            }
            if (param_count != 1)
            {
                return -1505;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1506;
            }
            if (!prepare_meta_result)
            {
                return -1506;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1507;
            }
            if (column_count != 25) /* validate column count */
            {
                return -1507;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1508;
            }
            if (stmt_execute)
            {
                return -1508;
            }
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_SHORT;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&same_EntryExit_filter;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&same_EntryExit_group;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&same_EntryExit_site;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&hourlyParkingFullAccessDeny;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&monthlyParkingFullAccessDeny;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&oneCard_oneCar;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&_operator;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&id_PresetType_id;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_SHORT;
                bind[10].buffer= (char *)&id_PresetSite_in_Site_Group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&entryPresetLicensePlateNumber;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)cache_plate;
                bind[12].buffer_length= 12;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&cache_etype;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)site_Address;
                bind[14].buffer_length= 22;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)db_name;
                bind[15].buffer_length= 50;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&status;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&type;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&exitFreeLetPass;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&credentialMode;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[20].buffer= (char *)&crt;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[21].buffer= (char *)&cht;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&season_to_hourly_swich;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* INTEGER COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&createtime;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* INTEGER COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&cache_time;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];
            }
            catch(...)
            {
                return -1544;
            }
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1509;
            }
            if (stmt_bind_result)
            {
                return -1509;
            }
            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1510;
            }
            if (stmt_store_result)
            {
                return -1510;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1511;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1512;
            }
        }
        else
        {
            return -1503;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1513;
        }
    }
    else
    {
        return -1501;
    }
    return 0;
}

int Site_type::Select_Site_type_by_address(int _address)
{
    char site_ip[22];
    std::string site_address = "172.16.57." + std::to_string(_address);
    std::string statment = "SELECT * ,Unix_Timestamp(createtime), Unix_Timestamp(cache_time) FROM v32_site WHERE siteip = ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1515;
        }
        if (!stmt)
        {
            return -1515;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1516;
        }
        if (!stmt_prepare)
        {
            bool stmt_bind_param = true;
            try
            {
                memset(bind_param, 0, sizeof(bind));
                bind_param[0].buffer_type= MYSQL_TYPE_STRING;
                bind_param[0].buffer= (char *)site_ip;
                bind_param[0].buffer_length= strlen(site_address.c_str());
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind_param);
            }
            catch(...)
            {
                return -1517;
            }
            if (stmt_bind_param)
            {
                return -1517;
            }
            int param_count = 0;
            try
            {
                strncpy(site_ip, site_address.c_str(), strlen(site_address.c_str()));
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1518;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -1518;
            }
            try
            {
                prepare_meta_result = mysql_stmt_result_metadata(stmt);
            }
            catch(...)
            {
                return -1519;
            }
            if (!prepare_meta_result)
            {
                return -1519;
            }
            int column_count = 0;
            try
            {
                column_count = mysql_num_fields(prepare_meta_result);
            }
            catch(...)
            {
                return -1520;
            }
            if (column_count != 25) /* validate column count */
            {
                return -1520;
            }
            
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1521;
            }
            if (stmt_execute)
            {
                return -1521;
            }
            
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));

                bind[0].buffer_type= MYSQL_TYPE_SHORT;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&same_EntryExit_filter;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&same_EntryExit_group;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&same_EntryExit_site;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&hourlyParkingFullAccessDeny;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&monthlyParkingFullAccessDeny;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&oneCard_oneCar;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&_operator;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&id_PresetType_id;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_SHORT;
                bind[10].buffer= (char *)&id_PresetSite_in_Site_Group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&entryPresetLicensePlateNumber;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)cache_plate;
                bind[12].buffer_length= 12;
                bind[12].is_null= &is_null[12];
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&cache_etype;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)site_Address;
                bind[14].buffer_length= 22;
                bind[14].is_null= &is_null[14];
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)db_name;
                bind[15].buffer_length= 50;
                bind[15].is_null= &is_null[15];
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&status;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&type;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&exitFreeLetPass;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&credentialMode;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[20].buffer= (char *)&crt;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_TIMESTAMP;
                bind[21].buffer= (char *)&cht;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&season_to_hourly_swich;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];

                /* INTEGER COLUMN */
                bind[23].buffer_type= MYSQL_TYPE_LONG;
                bind[23].buffer= (char *)&createtime;
                bind[23].is_null= &is_null[23];
                bind[23].length= &length[23];

                /* INTEGER COLUMN */
                bind[24].buffer_type= MYSQL_TYPE_LONG;
                bind[24].buffer= (char *)&cache_time;
                bind[24].is_null= &is_null[24];
                bind[24].length= &length[24];
            }
            catch(...)
            {
                return -1545;
            }
            
            bool stmt_bind_result = true;
            try
            {
                stmt_bind_result = mysql_stmt_bind_result(stmt, bind);
            }
            catch(...)
            {
                return -1522;
            }
            if (stmt_bind_result)
            {
                return -1522;
            }

            bool stmt_store_result = true;
            try
            {
                stmt_store_result = mysql_stmt_store_result(stmt);
            }
            catch(...)
            {
                return -1523;
            }
            if (stmt_store_result)
            {
                return -1523;
            }
            try
            {
                while (!mysql_stmt_fetch(stmt));
            }
            catch(...)
            {
                return -1524;
            }
            try
            {
                mysql_free_result(prepare_meta_result);
            }
            catch(...)
            {
                return -1525;
            }
        }
        else
        {
            return -1516;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1526;
        }
    }
    else
    {
        return -1514;
    }
    return 0;
}

int Site_type::Insert_Update_Site_type()
{
    std::string statment = "INSERT INTO `v32_site` (`id`, `gid`, `filter_sec`, `group_serial`, `both_way_site`, `hourly_full_close`, `monthly_full_close`, `only_one_car`, `operator`, `preset_hourly_type`, `preset_inner_group`, `preset_plate`, `cache_plate`, `cache_etype`, `siteip`, `name`, `state`, `type`, `zero_pass`, `io_mode`, `createtime`, `cache_time`, `enalbe_monthlytohourly`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?), FROM_UNIXTIME(?), ?) ON DUPLICATE KEY UPDATE id=VALUES(id), gid=VALUES(gid), filter_sec=VALUES(filter_sec), group_serial=VALUES(group_serial), both_way_site=VALUES(both_way_site), hourly_full_close=VALUES(hourly_full_close), monthly_full_close=VALUES(monthly_full_close), only_one_car=VALUES(only_one_car), operator=VALUES(operator), preset_hourly_type=VALUES(preset_hourly_type), preset_inner_group=VALUES(preset_inner_group), preset_plate=VALUES(preset_plate), cache_plate=VALUES(cache_plate), cache_etype=VALUES(cache_etype), siteip=VALUES(siteip), name=VALUES(name), state=VALUES(state), zero_pass=VALUES(zero_pass), io_mode=VALUES(io_mode), createtime=VALUES(createtime), cache_time=VALUES(cache_time), enalbe_monthlytohourly=VALUES(enalbe_monthlytohourly)";
    if (mysql != NULL) 
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1528;
        }
        if (!stmt)
        {
            return -1528;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1529;
        }
        if (!stmt_prepare)
        {
            try
            {
                memset(bind, 0, sizeof(bind));
                memset(is_null, 0, sizeof(is_null));
                memset(length, 0, sizeof(length));

                bind[0].buffer_type= MYSQL_TYPE_SHORT;
                bind[0].buffer= (char *)&id;
                bind[0].is_null= &is_null[0];
                bind[0].length= &length[0];

                bind[1].buffer_type= MYSQL_TYPE_LONG;
                bind[1].buffer= (char *)&gid;
                bind[1].is_null= &is_null[1];
                bind[1].length= &length[1];

                bind[2].buffer_type= MYSQL_TYPE_LONG;
                bind[2].buffer= (char *)&same_EntryExit_filter;
                bind[2].is_null= &is_null[2];
                bind[2].length= &length[2];

                bind[3].buffer_type= MYSQL_TYPE_SHORT;
                bind[3].buffer= (char *)&same_EntryExit_group;
                bind[3].is_null= &is_null[3];
                bind[3].length= &length[3];

                /* SHORT COLUMN */
                bind[4].buffer_type= MYSQL_TYPE_SHORT;
                bind[4].buffer= (char *)&same_EntryExit_site;
                bind[4].is_null= &is_null[4];
                bind[4].length= &length[4];

                /* SHORT COLUMN */
                bind[5].buffer_type= MYSQL_TYPE_SHORT;
                bind[5].buffer= (char *)&hourlyParkingFullAccessDeny;
                bind[5].is_null= &is_null[5];
                bind[5].length= &length[5];

                /* SHORT COLUMN */
                bind[6].buffer_type= MYSQL_TYPE_SHORT;
                bind[6].buffer= (char *)&monthlyParkingFullAccessDeny;
                bind[6].is_null= &is_null[6];
                bind[6].length= &length[6];

                /* SHORT COLUMN */
                bind[7].buffer_type= MYSQL_TYPE_SHORT;
                bind[7].buffer= (char *)&oneCard_oneCar;
                bind[7].is_null= &is_null[7];
                bind[7].length= &length[7];

                /* SHORT COLUMN */
                bind[8].buffer_type= MYSQL_TYPE_SHORT;
                bind[8].buffer= (char *)&_operator;
                bind[8].is_null= &is_null[8];
                bind[8].length= &length[8];

                /* SHORT COLUMN */
                bind[9].buffer_type= MYSQL_TYPE_SHORT;
                bind[9].buffer= (char *)&id_PresetType_id;
                bind[9].is_null= &is_null[9];
                bind[9].length= &length[9];

                /* SHORT COLUMN */
                bind[10].buffer_type= MYSQL_TYPE_SHORT;
                bind[10].buffer= (char *)&id_PresetSite_in_Site_Group;
                bind[10].is_null= &is_null[10];
                bind[10].length= &length[10];

                /* SHORT COLUMN */
                bind[11].buffer_type= MYSQL_TYPE_SHORT;
                bind[11].buffer= (char *)&entryPresetLicensePlateNumber;
                bind[11].is_null= &is_null[11];
                bind[11].length= &length[11];

                /* STRING COLUMN */
                bind[12].buffer_type= MYSQL_TYPE_STRING;
                bind[12].buffer= (char *)cache_plate;
                bind[12].buffer_length= 12;
                bind[12].is_null= &is_null[12];
                length[12] = strlen(cache_plate);
                bind[12].length= &length[12];

                /* SHORT COLUMN */
                bind[13].buffer_type= MYSQL_TYPE_SHORT;
                bind[13].buffer= (char *)&cache_etype;
                bind[13].is_null= &is_null[13];
                bind[13].length= &length[13];

                /* STRING COLUMN */
                bind[14].buffer_type= MYSQL_TYPE_STRING;
                bind[14].buffer= (char *)site_Address;
                bind[14].buffer_length= 22;
                bind[14].is_null= &is_null[14];
                length[14] = strlen(site_Address);
                bind[14].length= &length[14];

                /* STRING COLUMN */
                bind[15].buffer_type= MYSQL_TYPE_STRING;
                bind[15].buffer= (char *)db_name;
                bind[15].buffer_length= 50;
                bind[15].is_null= &is_null[15];
                length[15] = strlen(db_name);
                bind[15].length= &length[15];

                /* INTEGER COLUMN */
                bind[16].buffer_type= MYSQL_TYPE_LONG;
                bind[16].buffer= (char *)&status;
                bind[16].is_null= &is_null[16];
                bind[16].length= &length[16];

                /* SHORT COLUMN */
                bind[17].buffer_type= MYSQL_TYPE_SHORT;
                bind[17].buffer= (char *)&type;
                bind[17].is_null= &is_null[17];
                bind[17].length= &length[17];

                /* SHORT COLUMN */
                bind[18].buffer_type= MYSQL_TYPE_SHORT;
                bind[18].buffer= (char *)&exitFreeLetPass;
                bind[18].is_null= &is_null[18];
                bind[18].length= &length[18];

                /* SHORT COLUMN */
                bind[19].buffer_type= MYSQL_TYPE_SHORT;
                bind[19].buffer= (char *)&credentialMode;
                bind[19].is_null= &is_null[19];
                bind[19].length= &length[19];

                /* TIMESTAMP COLUMN */
                bind[20].buffer_type= MYSQL_TYPE_LONG;
                bind[20].buffer= (char *)&createtime;
                bind[20].is_null= &is_null[20];
                bind[20].length= &length[20];

                /* TIMESTAMP COLUMN */
                bind[21].buffer_type= MYSQL_TYPE_LONG;
                bind[21].buffer= (char *)&cache_time;
                bind[21].is_null= &is_null[21];
                bind[21].length= &length[21];

                /* SHORT COLUMN */
                bind[22].buffer_type= MYSQL_TYPE_SHORT;
                bind[22].buffer= (char *)&season_to_hourly_swich;
                bind[22].is_null= &is_null[22];
                bind[22].length= &length[22];
            }
            catch(...)
            {
                return -1546;
            }
            bool stmt_bind_param = true;
            try
            {
                stmt_bind_param = mysql_stmt_bind_param(stmt, bind);
            }
            catch(...)
            {
                return -1530;
            }
            if (stmt_bind_param)
            {
                return -1530;
            }
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1531;
            }
            if (param_count != 23) /* validate parameter count */
            {
                return -1531;
            }
            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1532;
            }
            if (stmt_execute)
            {
                return -1532;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1533;
            }
            if (stmt_affected_rows == 1)
            {
                printf("Site is inserted\n");
            }
            else
            {
                printf("Site is updated\n");
            }
        }
        else
        {
            return -1529;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1534;
        }
    }
    else
    {
        return -1527;
    }
    return 0;
}

int Site_type::Delete_Site_type()
{
    try
    {
        socket = -1;
        gid = 0;
        _operator = 0;
        type = 0;
        site_Type;
        address = 0;
        strcpy(site_Address, "");
        status = 0;
        site_Status = "000000";
        strcpy(db_name, "");
        versionLength = 0;
        version = "";
        VersionASCIIHEX = "";
        localSerial = 0;
        oneCard_oneCar = 0;
        same_EntryExit_group = 255;
        same_EntryExit_site = 0;
        same_EntryExit_filter = 0;
        entryPresetLicensePlateNumber = 0;
        exitFreeLetPass = 0;
        hourlyParkingFullAccessDeny = 0;
        monthlyParkingFullAccessDeny = 0;
        id_PresetType_id = 0;
        id_PresetSite_in_Site_Group = 255;
        credentialMode = 1;
        season_to_hourly_swich = 0;
        credentialMode_app = 1;
        strcpy(cache_plate, "");
        cache_etype = 0;
        createtime = 0;
        cache_time = 0;
        site_createtime = "";
        site_cache_time = "";
        balanceNotificationThreshold = 0;
        expireForecastThreshold = 0;
    }
    catch(...)
    {
        return -1547;
    }
    
    short id_;
    std::string statment = "DELETE FROM `v32_site` WHERE `id`= ?";
    if (mysql != NULL)   
    {
        try
        {
            stmt = mysql_stmt_init(mysql);
        }
        catch(...)
        {
            return -1536;
        }
        if (!stmt)
        {
            return -1536;
        }
        bool stmt_prepare = true;
        try
        {
            stmt_prepare = mysql_stmt_prepare(stmt,statment.c_str(),strlen(statment.c_str()));
        }
        catch(...)
        {
            return -1537;
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
                return -1538;
            }
            if (stmt_bind_param)
            {
                return -1538;
            }
            id_ = id;
            int param_count = 0;
            try
            {
                param_count = mysql_stmt_param_count(stmt);
            }
            catch(...)
            {
                return -1539;
            }
            if (param_count != 1) /* validate parameter count */
            {
                return -1539;
            }

            bool stmt_execute = true;
            try
            {
                stmt_execute = mysql_stmt_execute(stmt);
            }
            catch(...)
            {
                return -1540;
            }
            if (stmt_execute)
            {
                return -1540;
            }
            int stmt_affected_rows = 0;
            try
            {
                stmt_affected_rows = mysql_stmt_affected_rows(stmt);
            }
            catch(...)
            {
                return -1541;
            }
            if (stmt_affected_rows < 1)
            {
                return -1541;
            }    
        }
        else
        {
            return -1537;
        }
        try
        {
            mysql_stmt_close(stmt);
        }
        catch(...)
        {
            return -1542;
        }
    }
    else
    {
        return -1535;
    }
    return 0;
    
}
