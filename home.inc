<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Hero Block
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
<div id="hero-block" class="hero-block bg-overlay bg-image" style="background-image: url('assets/images/bg/hero.jpg')">
	<div id="particles-js"></div>
	<div class="container">
		<div class="row align-items-center justify-content-center hero-content-main">
			<div class="col-lg-8">
				<div class="hero-content-area text-center ptb-120">
					<div class="hero-title-area">
						<h2 class="hero-title">YANGABID &#8358;100 NAIRA MARKET</h2><!-- /.hero-title -->
					</div><!-- /.hero-title-area -->
					<div class="hero-desc">
						<p>THIS PLATFORM IS FOR CHARITY!!!<br />(Donate &#8358;100 to charity, bid and stand a chance to win expensive products on Yangabid)</p>
					</div><!-- /.hero-desc -->
					<div class="form-group-btn">
						<a class="btn btn-default" href=".?page=auction">All Auction</a>
						<a class="btn btn-default btn-white" href=".?page=about">Learn more</a>
					</div><!-- /.form-group-btn -->
				</div><!-- /.hero-content-area -->
			</div><!-- /.col-lg-8 -->
		</div><!--  /.row -->
	</div><!-- /.container -->
</div><!-- /.hero-block -->

<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Facility Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="facility-area">
            <div class="container ml-b-30">
                <div class="row facility-content">
                    <div class="col-lg-4 col-md-6">
                        <div class="facility-box">
                            <div class="icon" onclick="javascript:document.location.href='.?page=signup'">
                                <span class="fa fa-user"></span>
                            </div>
                            <h3 class="title">Sign Up</h3>
							<p>Join the community and stay up to date on the latest deals and auctions.</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                     <div class="col-lg-4 col-md-6">
                        <div class="facility-box">
                            <div class="icon" onclick="javascript:document.location.href='.?page=account'">
                                <span class="fa fa-dungeon"></span>
                            </div>
                            <h3 class="title">Get Pass</h3>
							<p>Purchase your daily gate pass of &#8358;100</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                    <div class="col-lg-4 col-md-6">
                        <div class="facility-box" onclick="javascript:document.location.href='.?page=account'">
                            <div class="icon">
                                <span class="fa fa-coins"></span>
                            </div>
                            <h3 class="title">Get Bid</h3>					
							<p>Be ready to go toe-to-toe with other bidders for what you like.</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                    <div class="col-lg-4 col-md-6">
                        <div class="facility-box" onclick="javascript:document.location.href='.?page=auction'">
                            <div class="icon">
                                <span class="fa fa-gavel"></span>
                            </div>
                            <h3 class="title">Start Bidding</h3>
							<p>Choose an auction to participate in and click “bid now”.</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                    <div class="col-lg-4 col-md-6">
                        <div class="facility-box" onclick="javascript:document.location.href='.?page=winners'">
                            <div class="icon">
                                <span class="fas fa-gift"></span>
                            </div>
                            <h3 class="title">Win</h3>
							<p>Confirm auction won, get in touch and claim your item.</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                    <div class="col-lg-4 col-md-6">
                        <div class="facility-box" onclick="javascript:document.location.href='.?page=winners'">
                            <div class="icon">
                                <span class="fa fa-thumbs-up"></span>
                            </div>
                            <h3 class="title">Share Experience</h3>
							<p>Continue winning and keep sharing your experience.</p>
                        </div><!-- /.facility-box -->
                    </div><!-- /.col-lg-3 -->
                </div><!-- /.row -->
            </div><!-- /.container -->
        </div><!-- /.facility-area -->
		
		

        <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Live Auction Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
		<?php
		    date_default_timezone_set("Africa/Lagos");
			$list = mysqli_query(Yanga::db(), 'select * from auctions where status = "ACTIVE" order by created_date desc');
			if(mysqli_num_rows($list) > 0) {
			?>
			<div class="live-auction-block ptb-120">
				<div class="container ml-b-30">
					<div class="row justify-content-center">
						<div class="col-lg-9">
							<div class="section-title text-center">
								<h2 class="title-main" data-animate="hg-fadeInUp">live <span>Auction</span></h2><!-- /.title-main -->
							</div><!-- /.section-title -->
						</div><!-- /.col-lg-9 -->
					</div><!-- /.row -->
					<div class="row items-two-1199">
			<?php
				while($item = mysqli_fetch_array($list)) {
				$current = date('Y-m-d H:i:s');
                $end = date($item['end_date']);
				if($current > $end) {
				    continue;
				} else {
				
				$product = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id = "'.$item['item_id'].'"'));
				$bidders_count = mysqli_num_rows(mysqli_query(Yanga::db(), 'select distinct(profile_id) from bids where auction_id = "'.$item['auction_id'].'"'));
			?>
				<div class="col-lg-4 col-md-4 col-6">
					<div class="auction-item">
						<div class="item-header">
							<h3 class="heading"><a href="auction-details.html"><?php print stripslashes($product['title']); ?></a></h3>
							<div class="auction-id">Auction ID: <?php print $item['auction_id']; ?></div>
						</div><!-- /.item-footer -->
						<div class="item-img">
							<a href="#">
								<?php
									if(strlen($product['pics_1']) > 3) {
										print '<img src="'.$product['pics_1'].'" alt="'.stripslashes($product['title']).'" style="min-height:150px; max-height:150px">';
									}
									
									/*if(strlen($product['pics_2']) > 3) {
										print '<img class="prod2" src="'.$product['pics_2'].'png" alt="'.stripslashes($product['title']).'">';
									}*/
									
								?>
							</a>
							
							<div class="item-price">Price: &#8358; <?php print number_format($product['actual_price']); ?></div>
						</div><!-- /.item-img -->
						<div class="item-footer">
						    <div><small><?php print stripslashes($item['description']); ?></small></div>
							<div class="item-footer-top">
								<div class="bid-timer text-white" data-countdown="<?php echo date("Y/m/d H:i:s", strtotime($item['end_date'])); ?>"></div>
								<p><i class="fa fa-user"></i> <?php echo number_format($bidders_count); ?></p>
							</div>
							<div class="bid-button">
								<button class="btn btn-default place-bid" auction="<?php print $item['auction_id']; ?>" href="#" data-toggle="modal" data-target="#bidModal">Bid Now</button>
							</div>
						</div><!-- /.item-footer -->
					</div><!-- /.auction-item -->
				</div><!-- /.col-lg-3 -->
			<?php
				}
				}
			?>
					</div><!-- /.row -->
				</div>
			</div><!-- /.live-auction-block -->
			<?php
			}
		?>
		
		<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Closed Auction Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
		<?php
			$list = mysqli_query(Yanga::db(), "select * from auctions as a where a.status = 'CLOSED' order by end_date desc LIMIT 6");
			if(mysqli_num_rows($list) > 0) {
			?>
			<div class="live-auction-block bg-white-smoke ptb-120">
				<div class="container ml-b-30">
					<div class="row justify-content-center">
						<div class="col-lg-9">
							<div class="section-title text-center">
								<h2 class="title-main" data-animate="hg-fadeInUp">closed <span>Auction</span></h2><!-- /.title-main -->
							</div><!-- /.section-title -->
						</div><!-- /.col-lg-9 -->
					</div><!-- /.row -->
					<div class="row items-two-1199">
			<?php
				while($item = mysqli_fetch_array($list)) {
				$product = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id = "'.$item['item_id'].'"'));
			?>
				<div class="col-lg-4 col-md-4 col-6">
					<div class="auction-item style-three">
						<div class="item-header">
							<h3 class="heading"><a href="auction-details.html"><?php print stripslashes($product['title']); ?></a></h3>
							<div class="auction-id">Auction ID: <?php print $item['auction_id']; ?></div>
						</div><!-- /.item-footer -->
						<div class="item-img">
							<a href="#">
								<?php
									if(strlen($product['pics_1']) > 3) {
										print '<img src="'.$product['pics_1'].'" alt="'.stripslashes($product['title']).'" style="min-height:150px; max-height:150px">';
									}
									
									/*if(strlen($product['pics_2']) > 3) {
										print '<img class="prod2" src="'.$product['pics_2'].'" alt="'.stripslashes($product['title']).'">';
									}*/
									
								?>
							</a>
							<div class="item-price">Price: &#8358;<?php print number_format($product['discount_price']); ?></div>
						</div><!-- /.item-img -->
						<div class="item-footer">
						    <div><small><?php print stripslashes($item['description']); ?></small></div>
							<div class="item-footer-top">
								<div class="bid-status">Closed</div>
								<div class="bid-winner"></div>
							</div>
						</div><!-- /.item-footer -->
					</div><!-- /.auction-item -->
				</div><!-- /.col-lg-3 -->
			<?php
				}
			?>
					</div><!-- /.row -->
				</div>
			</div><!-- /.live-auction-block -->
			<?php
			}
		?>
      
		