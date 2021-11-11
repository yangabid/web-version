<?php
	$row_count = mysqli_num_rows(mysqli_query(Yanga::db(), 'select * from bids where auction_id = "'.$_GET['auction'].'"'));
	$auction_coins = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select bids.auction_id, sum(bid) as total_coins from bids where bids.auction_id = "'.$_GET['auction'].'" group by bids.auction_id'));
	$auction_data = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from auctions left join bid_items on auctions.item_id = bid_items.item_id where auction_id = "'.$_GET['auction'].'"'));
	$customer_count = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select count(DISTINCT(profile_id)) as customers from bids where auction_id = "'.$_GET['auction'].'"'));
?>

<div class="content container">
	<h2 class="page-title"><i class="fa fa-bar-chart"></i> Auction Analytics</h2>
	<section class="widget">
		<header>
			<h4>
				Auction Analytics
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
		<div class="row">
    		<div class="col-xl-12 col-md-12">
    			<section class="widget widget-card">
    				<div class="widget-body clearfix">
    					<div class="pull-left">
    						<img src="../<?php echo $auction_data['pics_1']; ?>" class="img-responsive img" style="max-width:100px;" /> 
    					</div>
    					<div class="pull-right text-right">
    						<h3 class="no-margin text-white">Item</h3>
    						<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php echo stripslashes($auction_data['title']); ?></p>
    					</div>
    				</div>
    			</section>
    		</div>
    	</div>
		<?php
			if(isset($_GET['task']) && $_GET['task'] === "close" && isset($_GET['auction'])) {
				$id = $_GET['auction'];
				if(mysqli_query(Yanga::db(), 'update auctions set status = "CLOSED" where auction_id="'.$id.'"')) {
					print '<div class="alert alert-info mb-3">Auction closed successfully</div>';
				}
			}
		?>
		<div class="row">
			<div class="col-xl-6 col-md-6">
				<section class="widget widget-card">
					<div class="widget-body clearfix">
						<div class="pull-left">
							<i class="fa fa-thumbs-up text-primary fa-5x"></i> 
						</div>
						<div class="pull-right text-right">
							<h3 class="no-margin text-white">Auction Entry</h3>
							<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print number_format($row_count); ?></p>
						</div>
					</div>
				</section>
			</div>
		    <!-- <div class="col-xl-4 col-md-4">
				<section class="widget widget-card">
					<div class="widget-body clearfix">
						<div class="pull-left">
							<i class="fa fa-eercast text-primary fa-5x"></i> 
						</div>
						<div class="pull-right text-right">
							<h3 class="no-margin text-white">Coins</h3>
							<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print number_format($auction_coins['total_coins']); ?></p>
						</div>
					</div>
				</section>
			</div> -->
			<div class="col-xl-6 col-md-6">
				<section class="widget widget-card">
					<div class="widget-body clearfix">
						<div class="pull-left">
							<i class="fa fa-user text-primary fa-5x"></i> 
						</div>
						<div class="pull-right text-right">
							<h3 class="no-margin text-white">Customers</h3>
							<p class="lead mb-0 pb-0" style="font-weight:bold; font-size:28px;"><?php print number_format($customer_count['customers']); ?></p>
						</div>
					</div>
				</section>
			</div>
		</div>
		<div class="widget-table-overflow table-responsive">
			<table class="table table-striped table-lg mt-sm mb-0 sources-table">
				<thead>
					<tr>
						<th>Customer</th>
						<th>Total  Bid</th>
					</tr>
				</thead>
				<tbody>
				<?php
					$list = mysqli_query(Yanga::db(), 'select bids.profile_id, bids.auction_id, bids.item_id, sum(bid) as total_bids from bids where bids.auction_id = "'.$_GET['auction'].'" group by bids.profile_id, bids.item_id, bids.auction_id order by sum(bid) desc');
					if(mysqli_num_rows($list) > 0) {
						while($item = mysqli_fetch_array($list)) {
							$profile = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id ="'.$item['profile_id'].'"'));
							print '
							<tr>
								<td valign="middle">'.stripslashes($profile['first_name'].' '.$profile['last_name']).'</td>
								<td valign="middle">'.number_format($item['total_bids']).'</td>
							</tr>';
						}
					} else {
						print '<tr>
							<td colspan="7"><div class="alert alert-info">No bid added yet!</div></td>
							</tr>';
					}
				?>
				</tbody>
			</table>
		</div>
	</section>
</div>