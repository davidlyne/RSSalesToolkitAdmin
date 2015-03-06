<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class Database {
    
    private static $_dbname = 'salestoolkit';
    private static $_servername = 'localhost';
    private static $_dbusername = 'root';
    private static $_dbpassword = '';
    private static $_dbconn;
    
    public static function Connect()
    {
        Database::$_dbconn = new mysqli(Database::$_servername,Database::$_dbusername,Database::$_dbpassword);
       
        
        /* check connection */
        if (mysqli_connect_errno()) {
            printf("Connect failed: %s\n", mysqli_connect_error());
            exit();
        }
        
        if (Database::$_dbconn->select_db(Database::$_dbname) == FALSE)
        {
            printf("Failed to connect to db\n");
            exit();
        }

	$sql = "SET SESSION sql_mode = ''";
	Database::$_dbconn->query($sql);        
    }
    
    public static function Query($sql)
    {
        $result = Database::$_dbconn->query($sql);
        return $result;  
    }
    
    public static function FetchRow($result)
    {
        $row = $result->fetch_row();
        return $row;
    }
    
    public static function FetchArray($result)
    {
        $row = $result->fetch_array();
        return $row;
    }
    
    public static function GetInsertID()
    {
        return Database::$_dbconn->insert_id;
    }
}