<!-- 
SEED Lab: SQL Injection Education Web plateform
Author: Kailiang Ying
Email: kying@syr.edu
-->

<!DOCTYPE html>
<html>
<body>


<?php
   session_start(); 
   $input_email = $_GET['Email'];
   $input_nickname = $_GET['NickName'];
   $input_address= $_GET['Address'];
   $input_pwd = $_GET['Password']; 
   $input_phonenumber = $_GET['PhoneNumber']; 
   $input_id = $_SESSION['id'];
   $conn = getDB();
  
   // Don't do this, this is not safe against SQL injection attack

  $stmt = $conn->prepare("UPDATE credential SET nickname = ?, email = ?, address = ?, PhoneNumber = ? WHERE ID = ?");

   if($input_pwd!=''){
   	$input_pwd = sha1($input_pwd);
        $stmt = $conn->prepare("UPDATE credential SET nickname = ?, email = ?, address = ?, Password = ?PhoneNumber = ? WHERE ID = ?");
         $stmt->bind_param("sssssi", $input_nickname, $input_email, $input_address, $input_pwd, $input_PhoneNumber, $input_id);
         $stmt->execute();
         $stmt->bind_result($bind_id, $bind_name, $bind_eid, $bind_salary, $bind_birth, $bind_ssn, $bind_phoneNumber, $bind_address, $bind_email, $bind_nickname, $bind_Password);
         $stmt->fetch();
   }else{
      $stmt->bind_param("ssssi", $input_nickname, $input_email, $input_address, $input_PhoneNumber, $input_id);
      $stmt = $conn->prepare("UPDATE credential SET nickname = ?, email = ?, address = ?, PhoneNumber = ? WHERE ID = ?");
      $stmt->execute();
      $stmt->bind_result($bind_id, $bind_name, $bind_eid, $bind_salary, $bind_birth, $bind_ssn, $bind_phoneNumber, $bind_address, $bind_email, $bind_nickname, $bind_Password);
      $stmt->fetch();
   }

   $conn->close();	

   header("Location: unsafe_credential.php");

   exit();

function getDB() {
   $dbhost="localhost";
   $dbuser="root";
   $dbpass="seedubuntu";
   $dbname="Users";


   // Create a DB connection
   $conn = new mysqli($dbhost, $dbuser, $dbpass, $dbname);
   if ($conn->connect_error) {
         die("Connection failed: " . $conn->connect_error . "\n");
   }
return $conn;
}
 
?>

</body>
</html> 
