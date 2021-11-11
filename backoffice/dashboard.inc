<?php
	$user_count = mysqli_num_rows(mysqli_query(Yanga::db(), 'select * from profile'));
	$auction_count = mysqli_num_rows(mysqli_query(Yanga::db(), 'select * from auctions'));
	$item_count = mysqli_num_rows(mysqli_query(Yanga::db(), 'select * from bid_items'));
?>

<div class="content container">
	<h2 class="page-title">Dashboard <small>Statistics and more</small></h2>
	<div class="row">
		<div class="col-xl-4 col-md-4">
			<section class="widget widget-card">
				<div class="widget-body clearfix">
					<div class="pull-left">
						<i class="fa fa-thumbs-up text-primary fa-5x"></i> 
					</div>
					<div class="pull-right text-right">
						<h3 class="no-margin text-white">USERS GROWTH</h3>
						<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print $user_count; ?></p>
					</div>
				</div>
			</section>
		</div>
		<div class="col-xl-4 col-md-4">
			<section class="widget widget-card">
				<div class="widget-body clearfix">
					<div class="pull-left">
						<i class="fa fa-clock-o text-primary fa-5x"></i> 
					</div>
					<div class="pull-right text-right">
						<h3 class="no-margin text-white">AUCTIONS</h3>
						<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print $auction_count; ?></p>
					</div>
				</div>
			</section>
		</div>
		<div class="col-xl-4 col-md-4">
			<section class="widget widget-card">
				<div class="widget-body clearfix">
					<div class="pull-left">
						<i class="fa fa-shopping-cart text-primary fa-5x"></i> 
					</div>
					<div class="pull-right text-right">
						<h3 class="no-margin text-white">ITEMS</h3>
						<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print $item_count; ?></p>
					</div>
				</div>
			</section>
		</div>
	</div>
</div>