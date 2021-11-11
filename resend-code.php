<?php
@session_start();
if(isset($_SESSION['bidder'])) {
    include('yanga.php');
    $bidder = $_SESSION['bidder'];
    $data = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from activation_codes where profile_id="'.$bidder.'"'));
    $profile = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id = "'.$bidder.'"'));
    $activation = $data['CODE'];
	$message = "Hello ".stripslashes($profile['first_name']).", to activate your Yangabid account, use ".$activation;
		
	mail($profile['email'], 'Yangabid Activation Code', $message);
	
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
	print '<div class="alert alert-success mt-3 mb-0"><i class="fa fa-check-circle"></i> Activation code resent to your registered phone number and email address successfully</div>';
} else {
    print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot resend activation code, please login and retry.</div>';
}
?>