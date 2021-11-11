<?php
@session_start();
if(isset($_POST['code']) && isset($_SESSION['bidder'])) {
	$code = addslashes($_POST['code']);
	$bidder = $_SESSION['bidder'];
	$now = date('Y-m-d H:i:s');
	include('yanga.php');
	$data = mysqli_query(Yanga::db(), 'select * from activation_codes where code="'.$code.'" and profile_id="'.$bidder.'"');
	if(mysqli_num_rows($data) > 0) {
		$profile = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id="'.$bidder.'"'));
		$message = "Welcome ".stripslashes($profile['first_name']).", your Yangabid account is now active";
		$sender_name = "Yangabid";
		$recipients = $profile['phone'];
		Yanga::notify($message, $recipients);
		$header = 'From: Yangabid <noreply@yangabid.com>';
		mail($profile['email'], 'Welcome to Yangabid', $message, $header);
		mysqli_query(Yanga::db(), 'UPDATE activation_codes SET status = "ACTIVATED", updated_date="'.$now.'" WHERE code="'.$code.'" and profile_id="'.$profile['profile_id'].'"');
		mysqli_query(Yanga::db(), 'UPDATE profile SET status = "ACTIVE", updated_date="'.$now.'" WHERE profile_id="'.$profile['profile_id'].'"');
		$_SESSION['is_active'] = true;
		$_SESSION['msg'] = '<div class="card mb-5"><div class="card-body"><h3 style="color:#000036">Account activated</h3><p class="lead" style="color:#6449E7"><strong>'.stripslashes($profile['first_name']).'</strong> welcome to Yangabid!</p></div></div>';
		print '<script>document.location.href=".?page=account"</script>';
	} else {
		print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Invalid activation code.</div>';
	}
} 
if(isset($_POST['op']) && $_POST['op'] === "reset") {
	include('yanga.php');
	$user = addslashes($_POST['user']);
	$find = mysqli_query(Yanga::db(), 'select * from profile where phone="'.$user.'"');
	if(mysqli_num_rows($find) === 0) {
		print '<div class="card"><div class="card-body"><h3 style="color:#000036">Invalid Phone Number</h3><p class="lead" style="color:darkred">There is no user with the provided phone number</p></div></div>';
	} else {
		$profile = mysqli_fetch_array($find);
		$activation = rand (10000 , 99999);
		$now = date('Y-m-d H:i:s');
		mysqli_query(Yanga::db(), '
			INSERT INTO password_reset (phone, reset_code, reset_status, created_at, updated_at) 
			VALUES("'.$user.'", "'.$activation.'", "ACTIVE", "'.$now.'", "'.$now.'")
		');
		$message = "Hello ".stripslashes($profile['first_name']).", use ".$activation." as your OTP to reset your password";
		Yanga::notify($message, $profile['phone']);
		$header = 'From: Yangabid <noreply@yangabid.com>';
		mail($profile['email'], 'Yangabid Password Reset', $message, $header);
		$_SESSION['reset_user'] = true;
		$_SESSION['user'] = $profile;
		print '<script>document.location.href=".?page=reset-password"</script>';
	}
}
if(isset($_POST['op']) && $_POST['op'] === "do-reset") {
	include('yanga.php');
	if($_SESSION['reset_user'] && isset($_SESSION['user'])) {
		$pass = addslashes($_POST['pass']);
		$otp = addslashes($_POST['otp']);
		$user = $_SESSION['user']['phone'];
		$validate = mysqli_query(Yanga::db(), 'select * from password_reset where phone="'.$user.'" and reset_code="'.$otp.'" and reset_status="ACTIVE"');
		if(mysqli_num_rows($validate) > 0) {
			$new_pass = md5($pass);
			if(mysqli_query(Yanga::db(), 'update profile set passwd="'.$new_pass.'" where phone="'.$user.'"')) {
				mysqli_query(Yanga::db(), 'update password_reset set reset_status="USED" where phone="'.$user.'" and reset_code="'.$otp.'"');
				@session_destroy();
				$_SESSION['msg'] = '<div class="alert alert-success"> Your password has been reset. Please login with your new password</div>';
				print '<script>document.location.href=".?page=signin"</script>';
			} else {
				$_SESSION['msg'] = '<div class="alert alert-danger"> Password reset failed. Please try again.</div>';
				print '<script>document.location.href=".?page=signin"</script>';
			}
		} else {
			$_SESSION['msg'] = '<div class="alert alert-danger">Password cannot be reset. Please try again.</div>';
			print '<script>document.location.href=".?page=signin"</script>';
		}
	} else {
		$_SESSION['msg'] = '<div class="alert alert-danger">Your OTP Code has expired. Please retry</div>';
		print '<script>document.location.href=".?page=signin"</script>';
	}
}
die();
?>