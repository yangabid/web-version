<?php
class Yanga {
	public static function db() {
		return mysqli_connect('localhost', 'root', '', 'yanga');
	}

	public static function notify($message, $recipient) {
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

	public static function getMaxBid($array, $prop) {
		return max(array_map(function($o) use($prop) {
			return array("Maxbid" => $o["$prop"], "auction" => $o['auction_id'], "item" => $o['item_id'], "profile" => $o['profile_id']);
		},
		$array));
	}
	
	public static function getMinBid($array, $prop) {
		return min(array_map(function($o) use($prop) {
			return array("Maxbid" => $o["$prop"], "auction" => $o['auction_id'], "item" => $o['item_id'], "profile" => $o['profile_id']);
		},
		$array));
	}
}
?>