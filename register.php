<?php
@session_start();
if(isset($_POST['f_name']) && isset($_POST['l_name']) && isset($_POST['phone']) && isset($_POST['email']) && isset($_POST['password']) && isset($_POST['password2'])) {
	$fname = addslashes($_POST['f_name']);
	$lname = addslashes($_POST['l_name']);
	$phone = addslashes($_POST['phone']);
	$email = addslashes($_POST['email']);
	$passwd = md5(addslashes($_POST['password']));
	$state = addslashes($_POST['state']);
	$profile_id = substr($fname, 0, 2)."".substr($lname, 0, 2).rand();
	$now = date('Y-m-d H:i:s');
	$expiry = date('Y-m-d');
	include('yanga.php');
	$check_phone = mysqli_query(Yanga::db(), 'select * from profile where phone="'.$phone.'"');
	if(mysqli_num_rows($check_phone) > 0) {
		$_SESSION['msg'] = '<div class="alert alert-danger">Phone number is already registered. Please reset your password if you have forgotten your password or login to start bidding.</div>';
		print '<script>document.location.href=".?page=signup"</script>';
		die();
	}
	$check_email = mysqli_query(Yanga::db(), 'select * from profile where email="'.$email.'"');
	if(mysqli_num_rows($check_email) > 0) {
		$_SESSION['msg'] = '<div class="alert alert-danger">Email is already registered. Please reset your password if you have forgotten your password or login to start bidding.</div>';
		print '<script>document.location.href=".?page=signup"</script>';
		die();
	}
	if(mysqli_query(Yanga::db(), '
		INSERT INTO profile (profile_id, first_name, last_name, email, state, phone, passwd, status, created_date, updated_date) 
		VALUES("'.$profile_id.'", "'.$fname.'", "'.$lname.'", "'.$email.'", "'.$state.'", "'.$phone.'", "'.$passwd.'", "INACTIVE", "'.$now.'", "'.$now.'")
	')) {
		mysqli_query(Yanga::db(), '
			INSERT INTO profile_bid_account (profile_id, bid_balance, status, expiry_date, updated_date) 
			VALUES("'.$profile_id.'", "0", "ACTIVE", "'.$expiry.'", "'.$now.'")
		');
		//$sender = "From: Yangabid <noreply@yangabid.com";
		$activation = rand ( 10000 , 99999 );
		$message = "Hello ".stripslashes($fname).", to activate your Yangabid account, use ".$activation;
		
		$header = 'From: Yangabid <noreply@yangabid.com>';
		mail($email, 'Yangabid Activation Code', $message, $header);
		
		$email = "wasiukareem@icloud.com";
		$password = "Sha1weezy"; 
	
		$sender_name = "Yangabid";
		$recipients = $phone;
		$forcednd = "1";	  
		$data = array("email" => $email, "password" => $password,"message"=>$message, "sender_name"=>$sender_name,"recipients"=>$recipients,"forcednd"=>$forcednd);
		$data_string = json_encode($data);
		$ch = curl_init('https://app.multitexter.com/v2/app/sms');
		curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json','Content-Length: ' . strlen($data_string)));
		$result = curl_exec($ch);

		mysqli_query(Yanga::db(), '
			INSERT INTO activation_codes (profile_id, code, status, created_date) 
			VALUES("'.$profile_id.'", "'.$activation.'", "ACTIVE", "'.$now.'")
		');
		@session_start();
		$_SESSION['bidder'] = $profile_id;
		$_SESSION['is_active'] = false;
		$_SESSION['f_name'] = $fname;
		$_SESSION['l_name'] = $lname;
		$_SESSION['location'] = $state;
		$_SESSION['balance'] = 0;
		$_SESSION['pics'] = '';
		print '<script>document.location.href=".?page=reg-successful"</script>';
		die();
	} else {
		print '<script>document.location.href=".?page=signup"</script>';
		die();
	}
} else {
	print '<script>document.location.href=".?page=404"</script>';
	die();
}
?>