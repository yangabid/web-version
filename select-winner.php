<?php
  	date_default_timezone_set("Africa/Lagos");
	function notify($message, $recipient) {
		$email = "wasiukareem@icloud.com";
		$password = "Sha1weezy";
		$sender_name = "Yangabid";
		$forcednd = "1";	  
		$data = array("email" => $email, "password" => $password,"message"=>$message, "sender_name"=>$sender_name,"recipients"=>$recipient,"forcednd"=>$forcednd);
		$data_string = json_encode($data);
		$ch = curl_init('https://app.multitexter.com/v2/app/sms');
		curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json','Content-Length: ' . strlen($data_string)));
		$result = curl_exec($ch);
	}	
	
    include('yanga.php');
    $auctions = mysqli_query(Yanga::db(), 'SELECT * FROM auctions WHERE SYSDATE() > end_date AND status = "ACTIVE"');
		$count = 0;
    if(mysqli_num_rows($auctions) > 0) {
			while($a = mysqli_fetch_array($auctions)) {
				$entries = mysqli_query(Yanga::db(), '
				select 
					auction_id, 
					profile_id, 
					item_id, 
					sum(bid) as total_bids 
				from bids 
				where bids.auction_id= "'.$a['auction_id'].'" 
				group by auction_id, profile_id, item_id
				ORDER BY total_bids desc limit 3');
				$winner_list = array();
				while($bid = mysqli_fetch_array($entries)) {
					array_push($winner_list, array("total_bids" => $bid['total_bids'], "auction" => $bid['auction_id'], "item" => $bid['item_id'], "profile" => $bid['profile_id']));
				}
				$max = $winner_list[0]; 

				$now = date('Y-m-d H:i:s');
				
				$first_winner = mysqli_query(Yanga::db(), 'INSERT INTO winners(auction_id, item_id, profile_id, created_date) values("'.$max['auction'].'", "'.$max['item'].'", "'.$max['profile'].'", "'.$now.'")');

				if($first_winner) {
					$first = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id = "'.$max['profile'].'"'));
					
					$item = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id="'.$max['item'].'"'));
					
					$message = "Congratulations ".stripslashes($first['first_name'].' '.$first['last_name'])."\nYou won [".$item['title']." - N".number_format($item['actual_price'])."] on Yangabid. You won with ".$max['total_bids'];

					mysqli_query(Yanga::db(), 'UPDATE auctions SET status = "CLOSED" WHERE auction_id="'.$a['auction_id'].'"');
				
					notify($message, $first['phone']);
					
					$header = 'From: Yangabid <noreply@yangabid.com>';
				    mail($first['email'], 'Yangabid Notification', $message, $header);
				}
/*
				$second_total_bid = $second['total_bids'];

				$second_cur_bal = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile_bid_account where profile_id="'.$second['profile'].'"'));

				$second_winner = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id="'.$second['profile'].'"'));
				
				$second_price = ceil($second_cur_bal['bid_balance'] + ($second_total_bid/2));

				$second_message = "Congratulations ".stripslashes($second_winner['first_name'].' '.$second_winner['last_name'])."\nYou are the second highest bidder. You have been credited ".number_format($second_price)." bids on Yangabid.";

				if(mysqli_query(Yanga::db(), 'update profile_bid_account set bid_balance = "'.$second_price.'" where profile_id="'.$second['profile'].'"')) {
					notify($second_message, $second_winner['phone']);
					mysqli_query(Yanga::db(), 'UPDATE auctions SET status = "SECOND" WHERE auction_id="'.$a['auction_id'].'"');
				}

				$third_total_bid = $third['total_bids'];

				$third_cur_bal = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile_bid_account where profile_id="'.$third['profile'].'"'));

				$third_winner = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id="'.$third['profile'].'"'));
				
				$third_price = ceil($third_cur_bal['bid_balance'] + ($third_total_bid/2));

				$third_message = "Congratulations ".stripslashes($third_winner['first_name'].' '.$third_winner['last_name'])."\nYou are the third highest bidder. You have been credited ".number_format($third_price)." bids on Yangabid.";

				if(mysqli_query(Yanga::db(), 'update profile_bid_account set bid_balance = "'.$third_price.'" where profile_id="'.$third['profile'].'"')) {
					notify($third_message, $third_winner['phone']);
					mysqli_query(Yanga::db(), 'UPDATE auctions SET status = "COMPLETED" WHERE auction_id="'.$a['auction_id'].'"');
				}
*/		
				$count++;
      }
			print $count.' auction was processed and closed';
    } else {
        // do nothing
    }
?>