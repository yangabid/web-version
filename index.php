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
include('yanga.php');
if(isset($_SESSION['bidder'])) {
	$bal = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile_bid_account where profile_id = "'.$_SESSION['bidder'].'"'));
	$_SESSION['balance'] = $bal['bid_balance'];
}
if(!isset($_SESSION['location'])) {
	$_SESSION['location'] = "All";
}

include('header.inc');
if(!isset($_GET['page'])) {
    //if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
        include('home.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "about") {
    //if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
        include('about.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "contact") {
    //if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	   // include('buy-bid.inc');
    //} else {
	    include('contact.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "service") {
	//if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
	    include('service.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "apply") {
	//(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
	    include('apply.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "signin") {
	//if(isset($_SESSION['bidder'])) {
	    //include('profile.inc');
    //} else {
	    include('login.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "tou") {
	//if(isset($_SESSION['bidder'])) {
	    //include('profile.inc');
    //} else {
	    include('tou.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "signup") {
    if(isset($_SESSION['bidder'])) {
        $_SESSION['msg'] = '<div class="card mb-5"><div class="card-body"><h3 style="color:#000036">Logged in</h3><p class="lead" style="color:#6449E7">You already logged in on Yangabid</p></div></div>';
        include('profile.inc');
    } else {
	    include('register.inc');
    }
} else if(isset($_GET['page']) && $_GET['page'] == "signout") {
	@session_start();
	mysqli_query(Yanga::db(), 'delete from session_locker where profile_id="'.$_SESSION['bidder'].'"');
	session_destroy();
	$_SESSION['msg'] = '<div class="alert alert-success"><i class="fa fa-check"></i> You\'re logged out of Yanga bid platform</div>';
	print '<script>document.location.href=".?page=signin";</script>';
} else if(isset($_GET['page']) && $_GET['page'] == "account" || $_GET['page'] == "profile") {
	include('profile.inc');
//} else if(isset($_GET['page']) && $_GET['page'] == "account"  || $_GET['page'] == "profile") {
	//include('buy-bid.inc');
} else if(isset($_GET['page']) && $_GET['page'] == "winners") {
    //if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	   // include('buy-bid.inc');
    //} else {
	    include('winners-list.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "auction") {
	//if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	   // include('buy-bid.inc');
    //} else {
	    include('auction.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "live-auction") {
	//if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
	    include('live-auction.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "closed-auction") {
	//if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
	    include('closed-auction.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "reg-successful" || $_GET['page'] == "activate-account") {
	include('reg-success.inc');
} else if(isset($_GET['page']) && $_GET['page'] == "how-it-works") {
	//if(isset($_SESSION['bidder']) && $_SESSION['balance'] < 1) {
	    //include('buy-bid.inc');
    //} else {
	    include('how-it-work.inc');
    //}
} else if(isset($_GET['page']) && $_GET['page'] == "reset-password") {
	include('reset-password.inc');
} else if(isset($_GET['page']) && $_GET['page'] == "what-is-yangabid") {
	include('what-is-yangabid.inc');
} else if(isset($_GET['page']) && $_GET['page'] == "faq") {
	include('faq.inc');
}

include('footer.inc');
?>