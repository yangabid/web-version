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
							<li class="breadcrumb-item active">Closed Auctions</li>
						</ol>
					</div><!--~~./ breadcrumb-area ~~-->
				</div><!--~~./ page-header-content ~~-->
			</div>
		</div>
	</div><!--~~./ end container ~~-->
</div><!--~~./ end page title area ~~--> 
<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Live Auction Block
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
<?php
	$list = mysqli_query(Yanga::db(), "select * from auctions where status = 'CLOSED'");
	if(mysqli_num_rows($list) > 0) {
	?>
	<div class="live-auction-block ptb-120">
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
		<div class="col-lg-4 col-md-4">
			<div class="auction-item style-three">
				<div class="item-header">
					<h3 class="heading"><a href="auction-details.html"><?php print stripslashes($product['title']); ?></a></h3>
					<div class="auction-id">Auction ID: <?php print $item['auction_id']; ?></div>
				</div><!-- /.item-footer -->
				<div class="item-img">
					<a href="#">
						<?php
							if(strlen($product['pics_1']) > 3) {
								print '<img src="'.$product['pics_1'].'" alt="'.stripslashes($product['title']).'">';
							}
							
							if(strlen($product['pics_2']) > 3) {
								print '<img class="prod2" src="'.$product['pics_2'].'" alt="'.stripslashes($product['title']).'">';
							}
							
						?>
					</a>
					<div class="item-price">Price: &#8358;<?php print number_format($product['discount_price']); ?></div>
				</div><!-- /.item-img -->
				<div class="item-footer">
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
	} else {
		print '<div class="container"><div class="row"><div class="col-md-12 mb-5"><div class="card"><div class="card-body"><p class="lead" style="color:#0B0E3C"><i class="fa fa-info-circle"></i> No closed auction at the moment</p></div></div></div></div></div>';
	}
?>

