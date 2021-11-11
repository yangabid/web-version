<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Start Page Title Area
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
<div class="page-title-area bg-white-smoke">
	<div class="container">
		<div class="row">
			<div class="col-12">
				<div class="page-header-content text-center">
					<div class="page-header-caption">
						<h2 class="page-title">Auctions</h2>
					</div><!--~~./ page-header-caption ~~-->
					<div class="breadcrumb-area">
						<ol class="breadcrumb">
							<li class="breadcrumb-item"><a href="./">Home</a></li>  
							<li class="breadcrumb-item">Auction</li>
							<li class="breadcrumb-item">
								<select name="location" id="location" style="padding-right:40px; -webkit-appearance: none; -moz-appearance: none; appearance: none; background:transparent url(assets/images/select.png) no-repeat right center; color:#a2aec2;">
								    <option selected disabled><?php echo $_SESSION['location']; ?></option>
									<option value="Instant">Instant Auction</option>
									<option value="Jackpot">Jackpot</option>
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
									<option value="All">All States</option>
								</select>
							</li>
						</ol>
					</div>
					<p class="lead">You are viewing <?php echo $_SESSION['location']; ?> auctions</p>
				</div><!--~~./ page-header-content ~~-->
			</div>
		</div>
	</div><!--~~./ end container ~~-->
</div><!--~~./ end page title area ~~--> 
<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Live Auction Block
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
<?php
    date_default_timezone_set("Africa/Lagos");
    
    if($_SESSION['location'] != "All") {
        $list = mysqli_query(Yanga::db(), 'select * from auctions where status = "ACTIVE" and state = "'.$_SESSION['location'].'" and end_date > SYSDATE()');
    }
    if($_SESSION['location'] == "All") {
        $list = mysqli_query(Yanga::db(), 'select * from auctions where status = "ACTIVE" and end_date > SYSDATE()');
    }
	
	if(mysqli_num_rows($list) > 0) {
	    if(!isset($page)) {
			$page=1;
		}
		$page_rows=12;
		$last = ceil(mysqli_num_rows($list)/$page_rows);
		if(isset($_GET['p'])) {
			$page=$_GET['p'];
		}
		if($page<1) {
			$page=1;
		}
		else if($page>$last) {
			$page=$last;
		}
		$cur_page = ($page-1) * $page_rows;
		$max="LIMIT ".($page-1) * $page_rows.", ".$page_rows;
		
		if($_SESSION['location'] != "All") {
            $list = mysqli_query(Yanga::db(), "select * from auctions where status = 'ACTIVE' and state = '".$_SESSION['location']."' order by created_date desc $max");
        }
        if($_SESSION['location'] == "All") {
            $list = mysqli_query(Yanga::db(), "select * from auctions where status = 'ACTIVE' order by created_date desc $max");
        }
	?>
	<div class="live-auction-block ptb-120">
		<div class="container ml-b-30">
			<div class="row justify-content-center">
				<div class="col-lg-9">
					<div class="section-title text-center">
						<h2 class="title-main" data-animate="hg-fadeInUp">Live <span>Auctions</span></h2><!-- /.title-main -->
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
								print '<img class="prod2" src="'.$product['pics_2'].'" alt="'.stripslashes($product['title']).'">';
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
			<div class="row">
			    <div class="col-12">
                    <!--~~~~~ Start Paging Navigation ~~~~~-->
                    <nav class="paging-navigation paging-center pd-t-60">
                        <ul class="nav-links">
                            <?php
                			if($page==1){}
                			else {
                				print '<li class="nav-next"><a class="page-numbers" title="Goto First Page" href=".?page=auction"  style="color:#fff;">First</a></li>';
                				$previous=$page-1;
                				print '<li class="nav-next"><a class="page-numbers" title="Goto First Page" href=".?page=auction&p='.$previous.'"  style="color:#fff;">Prev</a></li>';
                			}
                			if($page==$last){}
                			else {
                				$next=$page+1;
                				echo '<li class="nav-next"><a class="page-numbers" title="Goto Next Page" href=".?page=auction&p='.$next.'" style="color:#fff;">Next</a></li>';
                				echo '<li class="nav-next"><a class="page-numbers" title="Goto Last Page" href=".?page=auction&p='.$last.'" style="color:#fff;">Last</a></li>';
                			}
                			?>
                        </ul>
                    </nav><!--~./ end paging navigation ~-->
                </div>
			</div>
		</div>
	</div><!-- /.live-auction-block -->
	<?php
	}
	else {
		print "
			<div class='container mb-5'>
				<div class='card' style='background:none; border:1px solid #6449E7; color:#fff'>
					<div class='card-body'>
						<p class='lead'>There is no auction in the selected location. Please select another state or check back after sometime.</p>
					</div>
				</div>
			</div>";
	}
?>

