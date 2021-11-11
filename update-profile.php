<?php
@session_start();
if(isset($_POST['f_name']) && isset($_POST['l_name']) && isset($_POST['phone']) && isset($_POST['email'])) {
	$fname = addslashes($_POST['f_name']);
	$lname = addslashes($_POST['l_name']);
	$phone = addslashes($_POST['phone']);
	$email = addslashes($_POST['email']);
	$state = addslashes($_POST['state']);
	$now = date('Y-m-d H:i:s');
    if(isset($_FILES['pic'])) {
        $target_dir = "bidders/";
        $target_file = $target_dir . basename($_FILES["pic"]["name"]);
        $FileType = pathinfo($target_file,PATHINFO_EXTENSION);
        $rand = mt_rand();
        $target_file = $target_dir .$rand.".".$FileType;
        $pics = $target_file;
        move_uploaded_file($_FILES["pic"]["tmp_name"], "$target_file");
    }
	include('yanga.php');
	$profile = $_SESSION['bidder'];
	$check_phone = mysqli_query(Yanga::db(), 'select * from profile where phone="'.$phone.'" and profile_id <> "'.$profile.'"');
	if(mysqli_num_rows($check_phone) > 0) {
		$_SESSION['msg'] = '<div class="alert alert-danger">The updated phone number is already in use. Please use another phone number.</div>';
		print '<script>document.location.href=".?page=account"</script>';
		die();
	}
	$check_email = mysqli_query(Yanga::db(), 'select * from profile where email="'.$email.'" and profile_id <> "'.$profile.'"');
	if(mysqli_num_rows($check_email) > 0) {
		$_SESSION['msg'] = '<div class="alert alert-danger">the updated Email is already in use. Please use another email address.</div>';
		print '<script>document.location.href=".?page=account"</script>';
		die();
	}
	if(mysqli_query(Yanga::db(), "
		UPDATE profile SET first_name = '$fname', last_name = '$lname', email = '$email', state = '$state', phone = '$phone', updated_date = '$now', profile_pics = '$pics' WHERE profile_id = '$profile'")) {
            $_SESSION['msg'] = '<div class="alert alert-success">Your profile was updated successfully.</div>';
		print '<script>document.location.href=".?page=account"</script>';
		die();
	} else {
        $_SESSION['msg'] = '<div class="alert alert-danger">Error, your profile was update was not successfully.</div>';
		print '<script>document.location.href=".?page=account"</script>';
		die();
	}
} else {
	print '<script>document.location.href=".?page=404"</script>';
	die();
}
?>