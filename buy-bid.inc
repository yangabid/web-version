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
									<h3>Hi <?php print $_SESSION['f_name']; ?></h3>
									<div class="row">
										<div class="col-md-3 mb-3">
											<div class="card">
												<div class="card-body">
													<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold;"><i class="fas fa-plus"></i> Gate Pass</p>
													<!-- div class="mb-2">Buy bid pack for &#8358;100. Valid for 1hr</div> -->
													<div class="input-group">
														<!-- <div class="input-group-prepend"><span class="input-group-text total-price">1 </span></div> -->
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
														<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold; font-size:28px;"><?php print $bal; //print number_format($_SESSION['balance']); ?><br /><small>Available Pass</small></p>
														<p class="pb-0 mb-2 mt-3" style="color:green"><i class="fas fa-coins fa-5x"></i></p>
													</div>
												</div>
											</div>
										</div>

                                        <div class="col-md-6 mb-3">
											<div class="card">
												<div class="card-body">
													<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold;"><i class="fas fa-plus"></i> Gat Bid</p>
													<div class="mb-2">Buy is valid for 1hr</div> -->
													<div class="input-group">
														<input type="text" class="form-control numbersonly" placeholder="How many?" id="bid" name="bid"/>
														<button class="btn btn-dark dashboard-purchase">Get now</button>
													</div>
													<div class="purchase-res"></div>
												</div>
											</div>
										</div>

                                        <div class="col-md-6 mb-3">
											<div class="card">
												<div class="card-body">
													<div class="d-flex align-items-center justify-content-between m-0 p-0">
														<p class="lead pb-0 mb-0" style="color:#0B0E3C; font-weight:bold; font-size:28px;"><?php print $bal; //print number_format($_SESSION['balance']); ?><br /><small>Available Bid</small></p>
														<p class="pb-0 mb-2 mt-3" style="color:green"><i class="fas fa-coins fa-5x"></i></p>
													</div>
												</div>
											</div>
										</div>

									</div>
								</div><!--~./ end tab pane ~-->

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
														<td valign="middle">'.stripslashes($item['reference']).'</td>
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