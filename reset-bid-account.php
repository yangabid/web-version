<?php
  	date_default_timezone_set("Africa/Lagos");
    include('yanga.php');
    $auctions = mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE bid_balance > 0'); 
		$count = 0;
    if(mysqli_num_rows($auctions) > 0) {

		while($a = mysqli_fetch_array($auctions)) {
		    $current = date('Y-m-d H:i:s');
            $expire = date($a['expiry_date']);
            if($current > $expire) {
                mysqli_query(Yanga::db(), 'update profile_bid_account set bid_balance=0 where profile_id="'.$a['profile_id'].'"');
		        $_SESSION['balance'] = 0; 
            }
			$count++;
		}				
		print $count.' bid balance was processed and updated';
      }
    else {
        // do nothing
    }
?>