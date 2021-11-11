<?php

@session_start();
date_default_timezone_set("Africa/Lagos");
if(isset($_POST['op']) && $_POST['op'] == "update-location") {
	$_SESSION['location'] = $_POST['loc'];
	die();
}
if(!isset($_SESSION['bidder'])) {
?>
<div class="user-register-area">
	<div class="form-content">
		<div class="form-header">
			<h4 class="form-subheading">Sign in to continue</h4>
		</div>
		<div class="login-res mb-3"></div>
		<input type="hidden" value="<?php print $_POST['bid']; ?>" id="auction_id"/>
		<div class="default-form signin-form">
			<div class="form-group">
				<label for="email">Phone number</label>
				<input id="ajax_phone" name="ajax_phone" class="form-controller" type="email" required>
			</div><!--/.form-group-->
			
			<div class="form-group">
				<label for="email">Password</label>
				<input id="ajax_pass" name="ajax_password" class="form-controller" type="password" required>
			</div><!--/.form-group-->
			
			<div class="remember-and-password">
				<div class="login-form-remember"> 
					<label><input id="remembermesignin" value="" type="checkbox"><span>Keep me looged in</span></label>
				</div>
			</div><!--/.remember-and-password-->

			<div class="form-btn-group">
				<div class="form-login-area">
					<button type="button" class="ajax-login btn btn-default">
						Sign In
					</button>
				</div>
				<div class="login-form-register-now">
					You have no account ? <a class="btn-register-now" href=".?page=signup">Sign Up</a>
				</div>
			</div>
		</div>  
	</div>
</div>
<script>
$('.ajax-login').on('click', function() {
	var phone = $('#ajax_phone').val();
	var pass = $('#ajax_pass').val();
	$(this).attr({'disabled':'disabled'});
	var auction = $('#auction_id').val();
	var settings = {
        "url": "login.php",
        "method": "POST",
        "mimeType": "multipart/form-data",
        "data": {'ajax_phone':phone, 'ajax_password':pass}
    }

    $.ajax(settings).done(function (response) {
		res = JSON.parse(response);
        if(res.error) {
			$('div.login-res').html('<div class="alert alert-danger"><i class="fa fa-warning"></i> '+res.msg+'</div>');
			$('.ajax-login').removeAttr('disabled');
		} else {
			var settings = {
				"url": "bid.php",
				"method": "POST",
				"mimeType": "multipart/form-data",
				"data": {'op':'bid', 'bid':auction}
			}
			$.ajax(settings).done(function (response) {
				$('div.bid-output').html(response);
			}).fail(function (jqXHR, textStatus, error) {
				$('.login-res').html('<div class="text-center mb-5 text-danger"><i class="fa fa-info-circle"></i> Cannot login at the moment, please retry.</div>');
				$('.ajax-login').removeAttr('disabled');
				return false;
			});
		}
    }).fail(function (jqXHR, textStatus, error) {
        $('.login-res').html('<div class="text-center mb-5 text-danger"><i class="fa fa-info-circle"></i> Cannot login at the moment, please retry.</div>');
		$('.ajax-login').removeAttr('disabled');
		return false;
    });	
});
</script>
<?php
} else {
	if(isset($_POST['op'])) {
		$op = $_POST['op'];
		if($op === "bid") {
			include('yanga.php');
			$auction = addslashes($_POST['bid']);
			$get_auction = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from auctions where auction_id = "'.$auction.'"'));
			
			$account = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$_SESSION['bidder'].'"'));
			
			$diff = abs(strtotime($account['gate_pass_expiry']) - strtotime(date('Y-m-d')));
            
            $years = floor($diff / (365*60*60*24));
            $months = floor(($diff - $years * 365*60*60*24) / (30*60*60*24));
            $days = floor(($diff - $years * 365*60*60*24 - $months*30*60*60*24)/ (60*60*24));

			$_SESSION['gate_pass'] = $days;
			
			if($_SESSION['gate_pass'] < 1) {
				?>
<!-- Bid balance is low -->
<p class="lead" style="margin-top:-15px; color:#0B0E3C;">Dear <?php print $_SESSION['f_name']; ?>, <br />You don't have a gate pass. You need at least 1 gate pass to start bidding.</p>
<a class="btn btn-default" href=".?page=account">Purchase gate pass here</a>
<?php			
			}
			else if($_SESSION['gate_pass'] > 0 && $_SESSION['balance'] < 1) {
				?>
<!-- Bid balance is low -->
<p class="lead" style="margin-top:-15px; color:#0B0E3C;">Dear <?php print $_SESSION['f_name']; ?>, <br />You don't have any bid left. You need at least 1 bid for this auction.</p>
<h4 style="color:#0B0E3C;">Get bid</h4>
<div class="purchase-res"></div>
<p class="mt-3 pb-0 mb-0" style="color:#0B0E3C;">Get 1 - 1000 bids. Valid for 1hr</p>
<div class="input-group">
	<input type="text" class="form-control numbersonly" placeholder="How many?" id="bid" name="bid"/>
		<button class="btn btn-dark ajax-purchase">Get now</button>
</div>
<script>
$('.numbersonly').keypress(function (e) {    
	var charCode = (e.which) ? e.which : event.keyCode    
	if (String.fromCharCode(charCode).match(/[^0-9]/g))    
	return false;                        
});
$('input#bid').keyup(function() {
	var count = $('input#bid').val();
	if(count.length > 0) {
		var price = parseInt(count) * 100;
		$('.total-price').html("&#8358;"+price);
	} else {
		$('.total-price').html("&#8358;100");
	}
});
$('.ajax-purchase').click(function() {
	$('.purchase-res').html("");
	var bid = 1; //$('input#bid').val();
	if(parseInt(bid)
	< 1) {
		$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Minimum is One bid @ &#8358;100 per bid</div>');
		return false;
	} else if(parseInt(bid)
	> 1000) {
		$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Maximum bid you can buy is 1,000</div>');
		return false;
	} else {
		$(this).attr({'disabled':'disabled'});
		var settings = {
			"url": "bid.php",
			"method": "POST",
			"mimeType": "multipart/form-data",
			"data": {'bid':bid, 'op':'purchase-bid'}
		}
		$.ajax(settings).done(function (response) {
			$('.purchase-res').html(response);
			setTimeout(function(){ document.location.href=".?page=account"; }, 3000);
		}).fail(function (jqXHR, textStatus, error) {
			$('.purchase-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot purchase bid pack at the moment, please retry.</div>');
			return false;
		});	
	}
});
</script>
				<?php
			} else {
				$product = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id = "'.$get_auction['item_id'].'"'));
				$account = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$_SESSION['bidder'].'"'));
				$_SESSION['expiry'] = $account['expiry_date'];
			?>
<div class="user-register-area" style="margin-top:-30px;">
	<div class="form-content">
		<div class="form-header">
			<h4 class="form-subheading"><img src="<?php print $product['pics_1']; ?>" style="width:70px; display:inline-block; float: left !important; border-radius: .25rem !important; padding: .25rem; background-color: #fff; border: 1px solid #dee2e6; margin-right:10px;" /><span style="padding-top:10px; display:inline-block;"><?php print stripslashes($product['title']); ?><br /><small style="color:purple;">Available Bid</small> <span class="inline-balance"> <?php print number_format($_SESSION['balance']); ?></span></span><br />Expiry: <span style="font-size:16px; color:#000;" data-countdown="<?php echo date("Y/m/d H:i:s", strtotime($_SESSION['expiry'])); ?>"></span></h4>
		</div>
		<div class="bid-res mb-3"></div>
		<input type="hidden" value="<?php print $_POST['bid']; ?>" id="auction_id"/>
		<div class="default-form signin-form">
				<label for="email"><span>Enter a number between 1 and 500</span></label>
				<input id="bid_entry" name="bid_entry" class="form-controller numberonly" type="text" required maxlength="3">
			</div><!--/.form-group-->
			<div class="form-btn-group">
				<div class="form-login-area mt-3">
					<button type="button" class="ajax-bid btn btn-default">
						<i class="fas fa-gavel"></i> Bid
					</button>
				</div>
			</div>
		</div>
	</div>
</div>
<script>

$('[data-countdown]').each(function() {
	var $this = $(this), finalDate = $(this).data('countdown');
	$this.countdown(finalDate, function(event) {
		$this.html(event.strftime('%H:%M:%S'));
	});
});

$('.numberonly').keypress(function (e) {    
	var charCode = (e.which) ? e.which : event.keyCode    
	if (String.fromCharCode(charCode).match(/[^0-9]/g))    
	return false;                        
});

$("input#bid_entry").keydown(function() {
	var entry = $(this).val();
	if(parseInt(entry) > 500) {
		$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> Invalid number picked. Please enter a number between 1 - 500</div>');
	}
});

$("input#bid_entry").blur(function() {
	var entry = $(this).val();
	if(parseInt(entry) > 500) {
		$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> Invalid number picked. Please enter a number between 1 - 500</div>');
		return false;
	}
});

$('.ajax-bid').on('click', function() {
	$('div.bid-res').html('');
	var auction = $('#auction_id').val();
	var entry = parseInt($('#bid_entry').val());
	if(entry === 0) {
		$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> Please enter a number between 1 - 500</div>');
		return false;
	} 
	else if(entry < 1) {
		$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> Please enter a number between 1 - 500</div>');
		return false;
	} else if(entry > 500) {
		$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> Invalid number picked. Please enter a number between 1 - 500</div>');
		return false;
	} else {
		$(this).attr({'disabled':'disabled'});
		var settings = {
			"url": "bid.php?version=<?php mt_rand(); ?>",
			"method": "POST",
			"mimeType": "multipart/form-data",
			"data": {'op':'do-bid', 'auction':auction, 'entry': entry}
		}
		$.ajax(settings).done(function (response) {
			var res = JSON.parse(response);
			if(res.error) {
				$('div.bid-res').html('<div class="alert alert-danger"><i class="fas fa-info"></i> '+res.msg+'</div>');
				$('.ajax-bid').removeAttr('disabled');
			} else {
				$('.bid-res').html('<div class="alert alert-success">'+res.msg+'</div>');
				$('.bid-balance').html(res.new_balance);
				$('.inline-balance').html(res.new_balance);
				$('#bid_qty').val('');
				$('#bid_entry').val('');
				$('.ajax-bid').removeAttr('disabled');
			}
		}).fail(function (jqXHR, textStatus, error) {
			$('.bid-res').html('<div class="text-center mb-5 text-danger"><i class="fas fa-info"></i> Cannot login at the moment, please retry.</div>');
			$('.ajax-bid').removeAttr('disabled');
			return false;
		});	
	}
});
</script>
<?php			
			}
		}
		
		if($op === "do-bid") {
		    if($_SESSION['gate_pass'] < 1) {
				echo json_encode(array("error"=> true, "msg"=> 'You don\'t have a gate pass. Click <a href=".?page=account"><b>HERE</b></a> to buy purchase a gate pass now', "status"=> false));
				die();
			}
			if($_SESSION['balance'] < 1) {
				echo json_encode(array("error"=> true, "msg"=> 'You don\'t have any bid left', "status"=> false));
				die();
			} else if(intval($_POST['entry']) == 0) {
			    echo json_encode(array("error"=> true, "msg"=> 'Invalid number picked. Please enter a number between 1 - 500', "status"=> false));
			    die();
			} else if(intval($_POST['entry']) > 500) {
			    echo json_encode(array("error"=> true, "msg"=> 'Invalid number picked. Please enter a number between 1 - 500', "status"=> false));
			    die();
			} else {
				include('yanga.php');
				$auction = addslashes($_POST['auction']);
				$entry =  intval($_POST['entry']);
				$now = date('Y-m-d H:i:s');
				$get_auction = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from auctions where auction_id = "'.$auction.'"'));
				$current = date('Y-m-d H:i:s');
                $end = date($get_auction['end_date']);
				if($current > $end) {
				    echo json_encode(array("error"=> true, "msg"=> 'Sorry, auction has expired, winner will be annouced shortly', "status"=> false));
			        die();
				}
				if($_SESSION['balance'] != 0) {
					$bidder = $_SESSION['bidder'];
					if(mysqli_query(Yanga::db(), 'INSERT INTO bids (auction_id, item_id, profile_id, bid, entry, created_date, status) values("'.$get_auction['auction_id'].'", "'.$get_auction['item_id'].'", "'.$bidder.'", "1", "'.$entry.'", "'.$now.'", "BIDDED")')) {
						$new_balance = intval($_SESSION['balance'] - 1);
						mysqli_query(Yanga::db(), 'UPDATE profile_bid_account SET bid_balance = "'.$new_balance.'", updated_date = "'.$now.'" WHERE profile_id="'.$bidder.'"');

						$_SESSION['balance'] = intval($_SESSION['balance'] - 1);
						
						$response_set = array(
						    // '<div>You bidded <strong>'.$entry.'</strong></div><div><marquee direction="left" scrolldelay="2" scrollamount="3" width="100%">You are currently the third highest bidder. Continue bidding to overtake the bidders in front.</marquee></div>',
						    // '<div>You bidded <strong>'.$entry.'</strong></div><div><marquee direction="left" scrolldelay="2" scrollamount="3" width="100%">Congratulations, you are currently the highest bidder for this auction. Well done '.$_SESSION['f_name'].', bid more to ensure your success.</marquee></div>',
						    '<div>You bidded <strong>'.$entry.'</strong></div><div><marquee direction="left" scrolldelay="2" scrollamount="3" width="100%">'.$_SESSION['f_name'].', You need to bid more to ensure your success</marquee></div>',
						    '<div>You bidded <strong>'.$entry.'</strong></div><div><marquee direction="left" scrolldelay="2" scrollamount="3" width="100%">'.$_SESSION['f_name'].', keep bidding to ensure you remain on top</marquee></div>'
					    );
                        $random_keys=array_rand($response_set, 1);
                        
						echo json_encode(
							array(
								"error"=> false, 
								"msg" => $response_set[$random_keys], 
								"status" => true, 
								"new_balance" => $_SESSION['balance']
							)
						);

					} else {
						echo json_encode(array("error"=> true, "msg"=> 'Bidding failed. Please try again later', "status"=> false));
					}
				} else {
					echo json_encode(array("error"=> true, "msg"=> 'Insufficient bid, you need at least 1 bid', "status"=> false));
				}
			}
		}
		if($op === "purchase-bid") {

			$customer = $_SESSION['bidder'];
			include('yanga.php');
			
			$bid_count = $_POST['bid'];
			
			if($bid_count < 1) {
			    print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Purchase failed, Minimum is One bid @ &#8358;100 per bid.</div>';
			    die();
			}
			
			if($bid_count > 1000) {
			    print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Purchase failed, you cannot buy more than 1,000 bid.</div>';
			    die();
			}

			$bid_price = $bid_count;
			
			$purchase_count = $bid_count;
			
			$customer_bal = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile_bid_account WHERE profile_id = "'.$customer.'" AND status = "ACTIVE"'));
			
			$customer = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * FROM profile WHERE profile_id = "'.$customer.'" AND status = "ACTIVE"'));
			
			$new_balance = intval($customer_bal['bid_balance'] + $purchase_count);
			$_SESSION['balance'] = $new_balance;
			
			$now = date('Y-m-d H:i:s');
			$today = date('Y-m-d H:i:s');
			$time = strtotime($today) + 3600; // Add 1 hour
			$expiry = date('Y-m-d H:i:s', $time); // Back to string
            
            $_SESSION['expiry'] = $expiry;
			
			if(mysqli_query(Yanga::db(), 'UPDATE profile_bid_account SET bid_balance="'.$new_balance.'", expiry_date = "'.$expiry.'", updated_date = "'.$now.'" WHERE profile_id="'.$customer_bal['profile_id'].'"')) {
				mysqli_query(Yanga::db(), 'INSERT INTO bid_purchase (profile_id, package_id, amount, channel, reference, payment_reference, payment_response, pay_status, created_date, updated_date) VALUES ("'.$customer_bal['profile_id'].'", "--", "'.$bid_price.'", "SELF-WEB", "REF-'.rand().'", "PAY-'.rand().'", "Internal", "SUCCESSFUL", "'.$now.'", "'.$now.'")');
				$message = "Your purchase of $purchase_count bid is successful. Your availabe bid is $new_balance bids, valid for 1 hours";
				//Yanga::notify($message, $customer['phone']);
				$header = 'From: Yangabid <noreply@yangabid.com>';
				mail($customer['email'], 'Yangabid Topup', $message, $header);
				print '<div class="alert alert-success mt-3"><i class="fas fa-coins"></i> Purchase successful. You now have '.$new_balance.' bids, valid for 1 hour.</div>';
			} else {
				print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Purchase failed, please try again.</div>';
			}
		}

	}
}
?>