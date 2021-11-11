<?php
	if(!$_SESSION['bidder']) {
		print '<script>document.location.href=".?page=signin";</script>';
	}
	if(!$_SESSION['is_active']) {
		print '<script>document.location.href=".?page=activate-account";</script>';
	}
?>
<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">My Account</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active"><a href=".?page=auction">Auction</a></li>
                                </ol>
                            </div><!--~~./ breadcrumb-area ~~-->
                            <div><img src="assets/images/logo/hon-logo.PNG" style="width:100px;" class="img-fluid"/>
                            <p class="lead"><strong>HON Foundation Partner</strong><br />Every profit goes to charity</p></div>
                        </div><!--~~./ page-header-content ~~-->
                    </div>
                </div>
            </div><!--~~./ end container ~~-->
        </div><!--~~./ end page title area ~~--> 

        <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start About Us Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="auction-item-details ptb-80">
            <div class="container">
                <!-- Title Row -->
                <div class="row align-items-center">
					<div class="col-12">
						<?php
						    $bal = $_SESSION['balance'];
							if(isset($_SESSION['msg'])) {
								print $_SESSION['msg'];
								unset($_SESSION['msg']);
							}
						?>
						<div class="item-info-area" style="border:none; padding:0px; margin:0px;">
							<div class="filter-info-tab">
								<ul class="nav nav-tabs" role="tablist" style="display:block;">
									<li style="display:inline-block">
										<a class="active show" data-toggle="tab" href="#dashboard" role="tab" aria-selected="true">Dashboard</a>
									</li>
                                    <li style="display:inline-block">
										<a data-toggle="tab" href="#edit_profile" role="tab" class="" aria-selected="false">Edit Profile</a>
									</li>
									<li style="display:inline-block">
										<a data-toggle="tab" href="#purchase_history" role="tab" class="" aria-selected="false">Purchase History</a>
									</li>
									<li style="display:inline-block">
										<a data-toggle="tab" href="#bid_history" role="tab" class="" aria-selected="false">Bid History</a>
									</li>
								</ul>
							</div>
								
							<div class="mt-5 tab-content filter-info-tab-content">
								<!--~~~~~ Start Tab Pane ~~~~~--> 
								<div class="tab-pane fade active show" id="dashboard" role="tabpanel" data-animate="hg-fadeInUp"> 
									<div class="float-left">
										<h3>Hi <?php print $_SESSION['f_name']; ?></h3>
									</div>
									<div class="float-right">
										<?php
				                                            $check = mysqli_query(Yanga::db(), 'select * from auctions left join bid_items on auctions.item_id = bid_items.item_id where auctions.status = "CLOSED" order by auctions.end_date desc LIMIT 20');
				                                            if(mysqli_num_rows($check) > 0) { ?>
					                                        <div class="dropdown">
					                                            <button class="btn btn-secondary dropdown-toggle" type="button" id="dropdownMenuButton" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true">
					                                                Result Check
					                                            </button>
					                                            <div class="dropdown-menu" aria-labelledby="dropdownMenuButton" style="z-index:-9999px !important;">
					                                                <?php
					                                                    while($auction = mysqli_fetch_array($check)) {
					                                                        print '<a data-toggle="modal" data-target="#resultModal" href="#" class="auction-res dropdown-item" aval="'.$auction['auction_id'].'"><img src="'.$auction['pics_1'].'" class="img responsive" style="width:45px;">'.$auction['auction_id'].' - '.$auction['title'].' <u>'.date("d/m/Y", strtotime($auction['end_date'])).'</u></a>';
					                                                        }
					                                                    } else {
					                                                        print '<a class="dropdown-item">No active acution at the moment</a>';
					                                                    }
					                                                ?>
					                                            </div>
					                                        </div>
									</div>
									<div class="clearfix"></div>
									<div class="payment-op mt-3 mb-3"></div>
									<div class="row">
										<div class="col-md-3 mb-3">
											<div class="card">
												<div class="card-body">
													<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold;"><i class="fas fa-plus"></i> Gate Pass</p>
													<div class="mb-2">Get pass and start winning</div>
													<div class="input-group">
														<!-- <div class="input-group-prepend"><span class="input-group-text total-price">1 </span></div> -->
														<select class="form-control numbersonly gate-pass-days" placeholder="How many?">
															<option disabled selected>Select gate pass</option>
															<option value="1">&#8358;100 for 1 day</option>
															<option value="2">&#8358;200 for 2 days</option>
															<option value="3">&#8358;300 for 3 days</option>
															<option value="4">&#8358;400 for 4 days</option>
															<option value="5">&#8358;500 for 5 days</option>
															<option value="6">&#8358;600 for 6 days</option>
															<option value="7">&#8358;700 for 7 days</option>
														</select>
															<button type="button" class="btn btn-dark" onclick="payWithPaystack()">Get Now</button>
													</div>
													<div class="payment-res"></div>
												</div>
											</div>
										</div>

										<div class="col-md-3 mb-3">
											<div class="card">
												<div class="card-body">
													<div class="d-flex align-items-center justify-content-between m-0 p-0">
														<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold; font-size:30px;" class="gate-pass"><span id="gatePass"><?php print $_SESSION['gate_pass']; ?></span> day(s)<br /><small>Pass</small></p>
														<p class="pb-0 mb-2 mt-3" style="color:green"><i class="fas fa-door-open fa-2x"></i></p>
													</div>
												</div>
											</div>
										</div>

                                        <div class="col-md-3 mb-3">
											<div class="card">
												<div class="card-body">
													<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold;"><i class="fas fa-plus"></i> Get Bid</p>
													<div class="mb-2">Bids are valid for 1 hour</div>
													<div class="input-group">
														<input type="text" class="form-control numbersonly" placeholder="How many?" id="bid" name="bid"/>
														<button class="btn btn-dark dashboard-purchase">Get now</button>
													</div>
													<div class="purchase-res"></div>
												</div>
											</div>
										</div>

                                        <div class="col-md-3 mb-3">
											<div class="card">
												<div class="card-body">
													<div class="d-flex align-items-center justify-content-between m-0 p-0">
														<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold; font-size:30px;"><?php print $bal; //print number_format($_SESSION['balance']); ?><br /><small>Bid</small></p>
														<p class="pb-0 mb-2 mt-3" style="color:green"><i class="fas fa-coins fa-2x"></i></p>
													</div>
												</div>
											</div>
										</div>

									</div>
								</div><!--~./ end tab pane ~-->
                                <!--~~~~~ Start Tab Pane ~~~~~--> 
								<div class="tab-pane fade" id="edit_profile" role="tabpanel"> 
									<h3>Edit Profile</h3>
				<?php
				
				$buyer = $_SESSION['bidder'];
				$data= mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id = "'.$buyer.'"'));
				?>
                                    <form class="default-form signup-form" action="update-profile.php" method="POST" enctype="multipart/form-data">
                                        <div class="row">
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="f_name">First Name</label>
                                                    <input id="f_name" name="f_name" class="form-controller" type="text" required value="<?php echo stripslashes($data['first_name']); ?>" >
                                                </div><!--/.form-group-->
                                            </div>
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="l_name">Last Name</label>
                                                    <input id="l_name" name="l_name" class="form-controller" type="text" required value="<?php echo stripslashes($data['last_name']); ?>">
                                                </div><!--/.form-group-->
                                            </div>
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="phone">Phone</label>
                                                    <input id="phone" name="phone" class="form-controller" type="text" required value="<?php echo stripslashes($data['phone']); ?>">
                                                </div><!--/.form-group-->
                                            </div>
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="email">Email Address</label>
                                                    <input id="email" name="email" class="form-controller" type="email" required value="<?php echo stripslashes($data['email']); ?>">
                                                </div><!--/.form-group-->
                                            </div>
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="pass">State of Residence</label>
                                                    <select name="state" class="form-controller" required >
                                                        <option value="<?php echo stripslashes($data['state']); ?>" selected="selected"><?php echo stripslashes($data['state']); ?></option>
                                                        <option value="Abuja FCT">Abuja FCT</option>
                                                        <option value="Abia">Abia</option>
                                                        <option value="Adamawa">Adamawa</option>
                                                        <option value="Akwa Ibom">Akwa Ibom</option>
                                                        <option value="Anambra">Anambra</option>
                                                        <option value="Bauchi">Bauchi</option>
                                                        <option value="Bayelsa">Bayelsa</option>
                                                        <option value="Benue">Benue</option>
                                                        <option value="Borno">Borno</option>
                                                        <option value="Cross River">Cross River</option>
                                                        <option value="Delta">Delta</option>
                                                        <option value="Ebonyi">Ebonyi</option>
                                                        <option value="Edo">Edo</option>
                                                        <option value="Ekiti">Ekiti</option>
                                                        <option value="Enugu">Enugu</option>
                                                        <option value="Gombe">Gombe</option>
                                                        <option value="Imo">Imo</option>
                                                        <option value="Jigawa">Jigawa</option>
                                                        <option value="Kaduna">Kaduna</option>
                                                        <option value="Kano">Kano</option>
                                                        <option value="Katsina">Katsina</option>
                                                        <option value="Kebbi">Kebbi</option>
                                                        <option value="Kogi">Kogi</option>
                                                        <option value="Kwara">Kwara</option>
                                                        <option value="Lagos">Lagos</option>
                                                        <option value="Nassarawa">Nassarawa</option>
                                                        <option value="Niger">Niger</option>
                                                        <option value="Ogun">Ogun</option>
                                                        <option value="Ondo">Ondo</option>
                                                        <option value="Osun">Osun</option>
                                                        <option value="Oyo">Oyo</option>
                                                        <option value="Plateau">Plateau</option>
                                                        <option value="Rivers">Rivers</option>
                                                        <option value="Sokoto">Sokoto</option>
                                                        <option value="Taraba">Taraba</option>
                                                        <option value="Yobe">Yobe</option>
                                                        <option value="Zamfara">Zamfara</option>
                                                    </select>
                                                </div><!--/.form-group-->
                                            </div>
                                            <div class="col-lg-6">
                                                <div class="form-group">
                                                    <label for="con_pass">Profile Picture</label>
                                                    <input type="file" class="form-control" id="pic" name="pic" />
                                                </div><!--/.form-group-->
                                            </div>
                                        </div>

                                        <div class="form-btn-group">
                                            <div class="form-login-area">
                                                <button type="submit" class="btn btn-default btn-primary">
                                                    Save Changes
                                                </button>
                                            </div>
                                        </div>
                                        <!--
                                        <div class="reg-others-media">
                                            <div class="text">Or, User social media to sign in</div>
                                            <div class="social-media-icons">
                                                <a href="signup.html#"><i class="fab fa-facebook-f"></i></a>
                                                <a href="signup.html#"><i class="fab fa-twitter"></i></a><a href="signup.html#"><i class="fab fa-linkedin-in"></i></a>
                                            </div>
                                        </div>
                                        -->
                                    </form>
                                </div>
								<!--~~~~~ Start Tab Pane ~~~~~--> 
								<div class="tab-pane fade" id="purchase_history" role="tabpanel"> 
									<h3>Purchase History</h3>
									<div class="widget-table-overflow table-responsive table">
									<table class="table table-striped table-lg mt-sm mb-0 sources-table">
										<thead>
											<tr>
												<th>Bid</th>
												<th>Price</th>
												<th>Channel</th>
												<th>Reference</th>
												<th>Pay Reference</th>
												<th>Pay Response</th>
												<th>Status</th>
												<th>Created</th>
											</tr>
										</thead>
										<tbody>
										<?php
											$buyer = $_SESSION['bidder'];
											$list = mysqli_query(Yanga::db(), 'select * from bid_purchase where profile_id = "'.$buyer.'" order by bid_purchase.created_date desc');
											if(mysqli_num_rows($list) > 0) {
												while($item = mysqli_fetch_array($list)) {
													print '
													<tr>
														<td valign="middle">'.stripslashes($item['amount']).'</td>
														<td valign="middle">'.number_format($item['amount']).'</td>
														<td valign="middle">'.stripslashes($item['channel']).'</td>
														<td valign="middle">'.stripslashes($item['yanga_reference']).'</td>
														<td valign="middle">'.stripslashes($item['payment_reference']).'</td>
														<td valign="middle">'.stripslashes($item['payment_response']).'</td>
														<td valign="middle"><span class="label label-success">'.$item['pay_status'].'</span></td>
														<td valign="middle">'.date("d M Y", strtotime($item['created_date'])).'</td>
													</tr>';
												}
											} else {
												print '<tr>
													<td colspan="7"><div class="alert alert-info">No bid purchase yet!</div></td>
													</tr>';
											}
										?>
										</tbody>
									</table>
								</div>
							</div><!--~./ end tab pane ~-->
							<div class="tab-pane fade" id="bid_history" role="tabpanel"> 
								<h3>Bid History</h3>
								<div class="widget-table-overflow table-responsive">
									<table class="table table-striped table-lg mt-sm mb-0 sources-table">
										<thead>
											<tr>
												<th>Auction</th>
												<th>Item</th>
												<th>Price</th>
												<th>Total Bid</th>
											</tr>
										</thead>
										<tbody>
										<?php
											$buyer = $_SESSION['bidder'];
											$list = mysqli_query(Yanga::db(), 'select bids.auction_id, bids.item_id, sum(bid) as total_bids from bids where bids.profile_id= "'.$buyer.'" group by bids.item_id, bids.auction_id');
											if(mysqli_num_rows($list) > 0) {
												while($item = mysqli_fetch_array($list)) {
													$bid_item = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id ="'.$item['item_id'].'"'));
													print '
													<tr>
														<td valign="middle">'.stripslashes($item['auction_id']).'</td>
														<td valign="middle">'.stripslashes($bid_item['title']).'</td>
														<td valign="middle">&#8358; '.number_format($bid_item['actual_price']).'</td>
														<td valign="middle"><i class="fa fa-coins"></i> '.number_format($item['total_bids']).'</td>
													</tr>';
												}
											} else {
												print '<tr>
													<td colspan="7"><div class="alert alert-info">No auction bidded yet!</div></td>
													</tr>';
											}
										?>
										</tbody>
									</table>
								</div>
							</div>
						</div><!-- /.tab-content -->
					</div>
				</div>
			</div><!-- /.row -->
		</div><!-- /.container -->
	</div><!--~~./ end about us block ~~-->
	
	<div class="modal fade" id="resultModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-body result-container">
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-primary close-result" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>

<script src="https://js.paystack.co/v1/inline.js"></script>
<script>
    function payWithPaystack(){
        var ref = 'YP'+Math.floor((Math.random() * 1000000000) + 1);
        var gate = $('select.gate-pass-days').val();
        var settings = {
    		"url": "log-payment.php",
    		"method": "POST",
    		"data": {ref:ref, gate:gate},
    	}
    	$.ajax(settings).done(function (response) {
    		if(response == "valid") {
    		    var handler = PaystackPop.setup({
                    key: 'pk_test_8a0d84b1b6223f02cd2c9e9f530efc099d54e77a',
                    email:'<?php print $_SESSION['email']; ?>',
                    firstname:'<?php print $_SESSION['f_name']; ?>',
                    lastname:'<?php print $_SESSION['l_name']; ?>',
                    amount: parseInt($('select.gate-pass-days').val()) * 10000,
                    ref: ref, 
                    callback:  function(response){
                        var settings = {
                    		"url": "log-payment.php",
                    		"method": "POST",
                    		"data": {handle:"verify", trans:response.trans, status:response.status, trxref:response.trxref , msg:response.message},
                    	}
                    	$.ajax(settings).done(function (res) {
                    	    var output = JSON.parse(res);
    		                $('.payment-op').html(output.notif);
    		                $('span#gatePass').html(output.pass);
    		            }).fail(function (jqXHR, textStatus, error) {
                    		$('.payment-op').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>');
                    		return false;
                    	});
                    },
                    onClose:  function(){
						var consent = confirm("Are you sure you want to cancel the gate pass payment");
						if(consent) {
							$('.payment-res').html('<div class="alert alert-warning mt-3 mb-0"><i class="fa fa-info-circle"></i> Gate pass payment cancelled successfully.</div>');
							return false;
						}	
                    }
              });
              handler.openIframe();
    		} else {
    		    $('.payment-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>');
    		    return false;
    		}
    	}).fail(function (jqXHR, textStatus, error) {
    		$('.payment-res').html('<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>');
    		return false;
    	});
    }
</script>