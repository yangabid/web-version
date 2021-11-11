<?php
if(isset($_POST['auction'])) {
    include('yanga.php');
?>
<div class="widget-table-overflow table-responsive" style="color:#000036; font-weight:bold; font-size:15px;">
	<table class="table table-lg mt-sm mb-0 sources-table">
		<thead>
			<tr>
				<th>Customer</th>
				<th>Total  Bid</th>
			</tr>
		</thead>
		<tbody>
		<?php
			$list = mysqli_query(Yanga::db(), 'select bids.profile_id, bids.auction_id, bids.item_id, sum(bid) as total_bids from bids where bids.auction_id = "'.$_POST['auction'].'" group by bids.profile_id, bids.item_id, bids.auction_id order by sum(bid) desc LIMIT 10');
			if(mysqli_num_rows($list) > 0) {
				while($item = mysqli_fetch_array($list)) {
					$profile = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id ="'.$item['profile_id'].'"'));
					print '
					<tr>
						<td valign="middle">'.@stripslashes($profile['first_name'].' '.$profile['last_name']).'</td>
						<td valign="middle">'.@number_format($item['total_bids']).'</td>
					</tr>';
				}
			} else {
				print '<tr>
					<td colspan="7"><div class="alert alert-info">No bidders yet!</div></td>
					</tr>';
			}
		?>
		</tbody>
	</table>
</div>
<?php
} else {
    echo 'no data';
}
?>