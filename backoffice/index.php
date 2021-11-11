<?php
/*
http_response_code(503);
//Seconds until the client should retry.
$retryAfterSeconds = 300;
//Retry-After header.
header('Retry-After: ' . $retryAfterSeconds);
//Custom message.
echo '<h1>503 Service Temporarily Unavailable</h1>';
//Exit the script.
exit;
*/
@session_start();
date_default_timezone_set("Africa/Lagos");
if(isset($_POST['action'])) {
	include('../yanga.php');
	if($_POST['action'] == "login") {
		$username = addslashes($_POST['username']);
		$passwd = md5(addslashes($_POST['password']));
		if(mysqli_num_rows(mysqli_query(Yanga::db(), 'SELECT * FROM bo_user_profile WHERE username = "'.$username.'" AND passwd = "'.$passwd.'"')) > 0) {
			$record = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM bo_user_profile WHERE username = "'.$username.'" AND passwd = "'.$passwd.'"'));
			$_SESSION['user_name'] = stripslashes($record['full_name']);
			$_SESSION['username'] = stripslashes($record['username']);
			print '<script>document.location.href=".?page=dashboard"</script>';
		} else {
			$_SESSION['msg'] = '<div class="alert alert-danger">Invalid login details</div>';
			print '<script>document.location.href=".?page=login"</script>';
		}
	}
	if($_POST['action'] == "add-product") {
		$pics1 = "";
		$pics2 = "";
		$pics3 = "";
		if(isset($_FILES['pics1'])) {
			$target_dir = "items/";
			$target_file = $target_dir . basename($_FILES["pics1"]["name"]);
			$FileType = pathinfo($target_file,PATHINFO_EXTENSION);
			$rand = mt_rand();
			$target_file = $target_dir .$rand.".".$FileType;
			$pics1 = $target_file;
			move_uploaded_file($_FILES["pics1"]["tmp_name"], "../$target_file");
		}
		
		if(isset($_FILES['pics2'])) {
			$target_dir = "items/";
			$target_file = $target_dir . basename($_FILES["pics2"]["name"]);
			$FileType = pathinfo($target_file,PATHINFO_EXTENSION);
			$rand = mt_rand();
			$target_file = $target_dir .$rand.".".$FileType;
			$pics2 = $target_file;
			move_uploaded_file($_FILES["pics2"]["tmp_name"], "../$target_file");
		}
		
		if(isset($_FILES['pics3'])) {
			$target_dir = "items/";
			$target_file = $target_dir . basename($_FILES["pics3"]["name"]);
			$FileType = pathinfo($target_file,PATHINFO_EXTENSION);
			$rand = mt_rand();
			$target_file = $target_dir .$rand.".".$FileType;
			$pics3 = $target_file;
			move_uploaded_file($_FILES["pics3"]["tmp_name"], "../$target_file");
		}
	
		$name = addslashes($_POST['name']);
		$description = addslashes($_POST['description']);
		$a_amt = addslashes($_POST['a_amt']);
		$d_amt = addslashes($_POST['d_amt']);
		$bid = addslashes($_POST['qty']);
		$item_id = "YBID-".mt_rand();
		$now = date('Y-m-d H:i:s');

		if(mysqli_query(Yanga::db(), '
			INSERT INTO bid_items (item_id, title, description, bid, actual_price, discount_price, pics_1, pics_2, pics_3, status, created_date, updated_date) 
			VALUES("'.$item_id.'", "'.$name.'", "'.$description.'", "'.$bid.'", "'.$a_amt.'", "'.$d_amt.'", "'.$pics1.'", "'.$pics2.'", "'.$pics3.'", "ACTIVE", "'.$now.'", "'.$now.'")
		')) {
			print '<script>document.location.href=".?page=create-item&res=0"</script>';
		} else {
			print '<script>document.location.href=".?page=create-item&res=1"</script>';
		}
	}
	if($_POST['action'] == "add-bid-pack") {
		$name = addslashes($_POST['name']);
		$price = addslashes($_POST['price']);
		$bid = addslashes($_POST['bid']);
		$item_id = "YBP-".mt_rand();
		$now = date('Y-m-d H:i:s');

		if(mysqli_query(Yanga::db(), '
			INSERT INTO bid_package (package_id, title, bid_count, price, status, created_date, updated_date) 
			VALUES("'.$item_id.'", "'.$name.'", "'.$bid.'", "'.$price.'", "ACTIVE", "'.$now.'", "'.$now.'")
		')) {
			print '<script>document.location.href=".?page=create-bid&res=0"</script>';
		} else {
			print '<script>document.location.href=".?page=create-bid&res=1"</script>';
		}
	}
	if($_POST['action'] == "topup-balance") {
	    $customer = $_POST['customer'];
			
		$bid_count = $_POST['bid'];
		
		if($bid_count < 1) {
		    print '<script>document.location.href=".?page=topup&res=1"</script>';
		    die();
		}
		
		if($bid_count > 1000) {
		    print '<script>document.location.href=".?page=topup&res=1"</script>';
		    die();
		}

		$bid_price = ($bid_count * 100);
		
		$purchase_count = ($bid_count * 100);
		
		$customer_bal = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$customer.'" AND status = "ACTIVE"'));
		
		$customer = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE profile_id = "'.$customer.'" AND status = "ACTIVE"'));
		
		$new_balance = intval($customer_bal['bid_balance'] + $purchase_count);
		
		$now = date('Y-m-d H:i:s');
		$today = date('Y-m-d H:i:s');
		$time = strtotime($today) + 3600; // Add 1 hour
		$expiry = date('Y-m-d H:i:s', $time); // Back to string
		
		if(mysqli_query(Yanga::db(), 'UPDATE profile_bid_account SET bid_balance="'.$new_balance.'", expiry_date = "'.$expiry.'", updated_date = "'.$now.'" WHERE profile_id="'.$customer_bal['profile_id'].'"')) {
			mysqli_query(Yanga::db(), 'INSERT INTO bid_purchase (profile_id, package_id, amount, channel, reference, payment_reference, payment_response, pay_status, created_date, updated_date) VALUES ("'.$customer_bal['profile_id'].'", "--", "'.$bid_price.'", "SELF-WEB", "REF-'.rand().'", "PAY-'.rand().'", "Internal", "SUCCESSFUL", "'.$now.'", "'.$now.'")');
			$message = "Your purchase of $purchase_count bid is successful. Your availabe bid is $new_balance bids, valid for 1 hours";
			Yanga::notify($message, $customer['phone']);
			$header = 'From: Yangabid <noreply@yangabid.com>';
			mail($customer['email'], 'Yangabid Topup', $message, $header);
			print '<script>document.location.href=".?page=topup&res=0"</script>';
		} else {
			print '<script>document.location.href=".?page=topup&res=1"</script>';
		}
	}
	if($_POST['action'] == "add-auction") {
		$item = $_POST['item'];
		$bid = $_POST['bid'];
		$state = $_POST['state'];
		$description = $_POST['description'];
		$a_id = "YBA-".mt_rand();
		$start_date = date('Y-m-d H:i:s', strtotime($_POST['date_start'].' '.$_POST['time_start'].':00'));
		$end_date = date('Y-m-d H:i:s', strtotime($_POST['date_end'].' '.$_POST['time_end'].':00'));
		$now = date('Y-m-d H:i:s');
		
		/*if(mysqli_num_rows(mysqli_query(Yanga::db(), 'SELECT * FROM auctions WHERE item_id = "'.$item.'" AND status = "ACTIVE"')) > 0) {
			print '<script>document.location.href=".?page=create-auction&res=dup"</script>';
		} else {*/
			if(mysqli_query(Yanga::db(), '
				INSERT INTO auctions (auction_id, item_id, bid, description, start_date, end_date, status, state, created_date, updated_date) 
				VALUES("'.$a_id.'", "'.$item.'", "'.$bid.'", "'.$description.'", "'.$start_date.'", "'.$end_date.'", "ACTIVE", "'.$state.'", "'.$now.'", "'.$now.'")
			')) {
				print '<script>document.location.href=".?page=create-auction&res=0"</script>';
			} else {
				print '<script>document.location.href=".?page=create-auction&res=1"</script>';
			}
		//}
	}
}
include('header.inc');
if(!isset($_GET['page'])) {
	include('login.inc');
} else if(isset($_GET['page']) && $_GET['page'] == "login") {
	include('login.inc');
}  else if(isset($_GET['page']) && ($_GET['page'] != "login" && $_GET['page'] != "logout")) {
    if(!isset($_SESSION['username'])) {
        print '<script>document.location.href="./"</script>';
        exit();
    }
	include('menu.inc');
	if(isset($_GET['page']) && $_GET['page'] == "dashboard") {
		include('../yanga.php');
		include('dashboard.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "create-auction") {
		include('../yanga.php');
		include('create-auction.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "list-auction") {
		include('../yanga.php');
		include('list-auction.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "closed-auction") {
		include('../yanga.php');
		include('closed-auction.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "create-bid") {
		include('create-bid.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "list-bid") {
		include('../yanga.php');
		include('list-bid.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "topup") {
		include('../yanga.php');
		include('topup.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "create-item") {
		include('create-item.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "list-item") {
		include('../yanga.php');
		include('list-item.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "customers-list") {
		include('../yanga.php');
		if(isset($_GET['op']) && $_GET['op']=="d" && isset($_GET['user'])) {
		    $profile = addslashes($_GET['user']);
		    mysqli_query(Yanga::db(), 'delete from profile where profile_id="'.$profile.'"');
		    mysqli_query(Yanga::db(), 'delete from profile_bid_account where profile_id="'.$profile.'"');
		    @session_start();
	        $_SESSION['msg'] = '<div class="alert alert-success">Profile deleted successful</div>';
		}
		include('customers-list.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "bids") {
		include('bids.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "transaction-list") {
		include('../yanga.php');
		include('transaction-list.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "auction-analytics") {
		include('../yanga.php');
		include('auction-analytics.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "winners") {
		include('winners-list.inc');
	} else if(isset($_GET['page']) && $_GET['page'] == "search") {
	    include('../yanga.php');
		include('search.inc');
	}
} else if(isset($_GET['page']) && $_GET['page'] == "logout") {
	@session_destroy();
	@session_start();
	$_SESSION['msg'] = '<div class="alert alert-success">Logged out successful</div>';
	print '<script>document.location.href="./"</script>';
}
include('footer.inc');
?>