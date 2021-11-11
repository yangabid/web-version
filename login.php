<?php
@session_start();
if(isset($_POST['phone']) && isset($_POST['password'])) {
	$phone = addslashes($_POST['phone']);
	$passwd = md5(addslashes($_POST['password']));
	include('yanga.php');
	if(mysqli_num_rows(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE phone = "'.$phone.'" AND passwd = "'.$passwd.'"'))) {
		$data = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE phone = "'.$phone.'" AND passwd = "'.$passwd.'"'));

		$check_session = mysqli_query(Yanga::db(), 'select * from session_locker where profile_id="'.$data['profile_id'].'"');
		if(mysqli_num_rows($check_session) > 0) {
			$_SESSION['msg'] = '<div class="alert alert-warning">You are currently logged in on another device, please logout from the other device to be able to login on this device.</div>';
			print '<script>document.location.href=".?page=signin"</script>';
		} else {
			$id = $data['profile_id'];
			$now = date('Y-m-d H:i:s');
			mysqli_query(Yanga::db(), 'insert into session_locker (profile_id, lock_status, created_date, updated_date) values("'.$data['profile_id'].'", "ACTIVE", "'.$now.'", "'.$now.'")');
			$account = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$id.'"'));

			$_SESSION['bidder'] = $data['profile_id'];
			$_SESSION['f_name'] = $data['first_name'];
			$_SESSION['l_name'] = $data['last_name'];
			$_SESSION['email'] = $data['email'];
			$_SESSION['phone'] = $data['phone'];
			$_SESSION['balance'] = $account['bid_balance'];
			$_SESSION['location'] = $data['state'];
			$_SESSION['expiry'] = $account['expiry_date'];
			$_SESSION['pics'] = $data['profile_pics'];

            $diff = abs(strtotime($account['gate_pass_expiry']) - strtotime(date('Y-m-d')));
            
            $years = floor($diff / (365*60*60*24));
            $months = floor(($diff - $years * 365*60*60*24) / (30*60*60*24));
            $days = floor(($diff - $years * 365*60*60*24 - $months*30*60*60*24)/ (60*60*24));

			$_SESSION['gate_pass'] = $days;
			
			if($data['status'] == "INACTIVE") {
				$_SESSION['is_active'] = false;
				print '<script>document.location.href=".?page=activate-account"</script>';
			} else {
				$_SESSION['is_active'] = true;
				print '<script>document.location.href=".?page=account"</script>';
			}
		}
	} else {
		$_SESSION['msg'] = '<div class="alert alert-danger"> Invalid login details</div>';
		print '<script>document.location.href=".?page=signin"</script>';
	}
} else if(isset($_POST['ajax_phone']) && isset($_POST['ajax_password']))  {
	$phone = addslashes($_POST['ajax_phone']);
	$passwd = md5(addslashes($_POST['ajax_password']));
	include('yanga.php');
	if(mysqli_num_rows(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE phone = "'.$phone.'" AND passwd = "'.$passwd.'"'))) {
		$check_session = mysqli_query(Yanga::db(), 'select * from session_locker where profile_id="'.$data['profile_id'].'"');
		if(mysqli_num_rows($check_session) > 0) {
			echo json_encode(array("error"=> true, "msg"=> "You are currently logged in on another device, please logout from the other device to be able to login on this device."));
		} else {

			$now = date('Y-m-d H:i:s');
			mysqli_query(Yanga::db(), 'insert into session_locker (profile_id, lock_status, created_date, updated_date) values("'.$data['profile_id'].'", "ACTIVE", "'.$now.'", "'.$now.'")');

			$data = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE phone = "'.$phone.'" AND passwd = "'.$passwd.'"'));
			if($data['status'] == "INACTIVE") {
				$_SESSION['is_active'] = false;
			} else {
				$_SESSION['is_active'] = true;
			}
			$id = $data['profile_id'];
			$account = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$id.'"'));
			$_SESSION['bidder'] = $data['profile_id'];
			$_SESSION['email'] = $data['email'];
			$_SESSION['f_name'] = $data['first_name'];
			$_SESSION['l_name'] = $data['last_name'];
			$_SESSION['location'] = $data['state'];
			$_SESSION['balance'] = $account['bid_balance'];
			$_SESSION['expiry'] = $account['expiry_date'];
			echo json_encode(array("error"=> false, "msg"=> "success"));	
		}
	} else {
		echo json_encode(array("error"=> true, "msg"=> "Invalid login details"));
	}
} else {
	print '<script>document.location.href=".?page=404"</script>';
}
?>