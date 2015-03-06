<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class UserDB {
 
    private static $_dbconn;
    public static $salt = "C93x9ANe"; // Must be the same as booking system
    
    private static function connectDB()
    {
        UserDB::$_dbconn = new mysqli(Config::$UserDBServername,Config::$UserDBUsername,Config::$UserDBPassword);
       
        
        /* check connection */
        if (mysqli_connect_errno()) {
            printf("Connect failed: %s\n", mysqli_connect_error());
            exit();
        }
        
        if (UserDB::$_dbconn->select_db(Config::$UserDBName) == FALSE)
        {
            printf("Connect to select db\n");
            exit();
        }

	$sql = "SET SESSION sql_mode = ''";
	UserDB::$_dbconn->query($sql);
        
    }
    
    static public function EscapeChars($str)
    {
        $str = htmlspecialchars($str);
	$str = UserDB::$_dbconn->real_escape_string($str);
        return $str;
    }
    
    static public function genMD5Password($password)
    {
        $password = UserDB::$_dbconn->real_escape_string($password);
        $password = md5(UserDB::$salt . $password);
        return $password;
    }
    
    public static function getPermissionLevel()
    {
        UserDB::connectDB();
        
        $password = UserDB::EscapeChars($_POST["password"]);
        $email = UserDB::EscapeChars($_POST["username"]);
        
        if (strlen($email) == 0 || strlen($password) == 0)
            return 0;
        
        $password = UserDB::genMD5Password($password);
         
        $sql = "SELECT Access FROM users WHERE Email='$email' AND Password='$password'";
        $result = UserDB::$_dbconn->query($sql);

        $row = $result->fetch_row();
        
        if (!$row)
            return 0;
        
        // Map booking system access level to toolkit access level
        $accessLevel = $row[0];
        switch ($accessLevel)
        {
            case 0:
                return 0; // standard users not permitted
            case 1:
            case 2:
                return 1; // admin and senior users permitted
            case 3:
                return 2; // super admin allowed to change categories
        }
        
        return 0;
    }
    
}