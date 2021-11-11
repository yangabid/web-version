<div class="content container">
	<h2 class="page-title"><i class="fa fa-clock-o"></i> Auction System</h2>
	<section class="widget">
		<header>
			<h4>
				Live Auction List
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
		<?php
			if(isset($_GET['task']) && $_GET['task'] === "close" && isset($_GET['auction'])) {
				$id = $_GET['auction'];
				
				$entries = mysqli_query(Yanga::db(), '
				select 
					auction_id, 
					profile_id, 
					item_id, 
					sum(bid) as total_bids 
				from bids 
				where bids.auction_id= "'.$id.'" 
				group by auction_id, profile_id, item_id
				ORDER BY total_bids desc limit 3');
				$winner_list = array();
				while($bid = mysqli_fetch_array($entries)) {
					array_push($winner_list, array("total_bids" => $bid['total_bids'], "auction" => $bid['auction_id'], "item" => $bid['item_id'], "profile" => $bid['profile_id']));
				}
				$max = $winner_list[0]; 

				$now = date('Y-m-d H:i:s');
				
				$first_winner = mysqli_query(Yanga::db(), 'INSERT INTO winners(auction_id, item_id, profile_id, created_date) values("'.$max['auction'].'", "'.$max['item'].'", "'.$max['profile'].'", "'.$now.'")');

				if($first_winner) {
					$first = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from profile where profile_id = "'.$max['profile'].'"'));
					
					$item = mysqli_fetch_array(mysqli_query(Yanga::db(), 'select * from bid_items where item_id="'.$max['item'].'"'));
					
					$message = "Congratulations ".stripslashes($first['first_name'].' '.$first['last_name'])."\nYou won [".$item['title']." - N".number_format($item['actual_price'])."] on Yangabid. You won with ".$max['total_bids']." bids";

					mysqli_query(Yanga::db(), 'UPDATE auctions SET status = "CLOSED" WHERE auction_id="'.$id.'"');
				
					Yanga::notify($message, $first['phone']);
					
					$header = 'From: Yangabid <noreply@yangabid.com>';
				    mail($first['email'], 'Yangabid Notification', $message, $header);
				}
				
				print '<div class="alert alert-info mb-3">Auction closed successfully</div>';
			}
		?>
		<div class="widget-table-overflow table-responsive">
			<table class="table table-striped table-lg mt-sm mb-0 sources-table">
				<thead>
					<tr>
						<th></th>
						<th>Item</th>
						<th>State</th>
						<th>Entry Bid</th>
						<th>Start</th>
						<th>End</th>
						<th>Creation Date</th>
						<th></th>
					</tr>
				</thead>
				<tbody>
				<?php
					$list = mysqli_query(Yanga::db(), "select * from auctions as a left join bid_items as b on a.item_id= b.item_id where a.status <> 'CLOSED' order by a.created_date desc");
					if(mysqli_num_rows($list) > 0) {
					    if(!isset($page)) {
                			$page=1;
                		}
                		$page_rows=10;
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
                		
                		$list = mysqli_query(Yanga::db(), "select * from auctions as a left join bid_items as b on a.item_id= b.item_id where a.status <> 'CLOSED' order by a.created_date desc $max");
                		
						while($item = mysqli_fetch_array($list)) {
							print '
							<tr>
								<td valign="middle"><img src="../'.$item['pics_1'].'" class="img-responsive img" style="width:40px;" /></td>
								
								<td valign="middle">'.stripslashes($item['title']).'<br /><small style="color:#777;">Actual:</small> &#8358;'.number_format($item['actual_price']).' / <small style="color:#777;">Discounted:</small> &#8358;'.number_format($item['discount_price']).'</td>
								<td valign="middle">'.stripslashes($item['state']).'</td>
								<td valign="middle">'.number_format($item['bid']).'</td>
								<td valign="middle">'.date("d-m-Y H:i:s", strtotime($item['start_date'])).'</td>
								<td valign="middle">'.date("d-m-Y H:i:s", strtotime($item['end_date'])).'</td>
								<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
								<td valign="middle">
									<a href=".?page=auction-analytics&auction='.$item['auction_id'].'" target="_new" class="btn btn-info btn-xs"><i class="fa fa-bar-chart"></i> Statics</a> &nbsp; &nbsp; &nbsp; &nbsp;
									';
							if($item[6]!="CLOSED") {
								print '<a href=".?page=list-auction&task=close&auction='.$item['auction_id'].'" class="btn btn-danger btn-xs">CLOSE</a>';
							}
									print '
								</td>
							</tr>';
						}
					} else {
						print '<tr>
							<td colspan="7"><div class="alert alert-info">No item added yet!</div></td>
							</tr>';
					}
				?>
				</tbody>
			</table>
		</div>
	</section>
	<?php
	if(mysqli_num_rows($list) > 0) { ?>
	<nav>
        <ul class="pagination justify-content-center">
            <?php
			if($page==1){}
			else {
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=list-auction"  style="color:#fff;">First Page</a></li>';
				$previous=$page-1;
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=list-auction&p='.$previous.'"  style="color:#fff;">Previous</a></li>';
			}
			if($page==$last){}
			else {
				$next=$page+1;
				echo '<li class="page-item"><a class="page-link" title="Goto Next Page" href=".?page=list-auction&p='.$next.'" style="color:#fff;">Next Page</a></li>';
				echo '<li class="page-item"><a class="page-link" title="Goto Last Page" href=".?page=list-auction&p='.$last.'" style="color:#fff;">Last Page</a></li>';
			}
			?>
        </ul>
    </nav>
    <?php }?>
</div>