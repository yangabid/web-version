<div class="content container">
	<h2 class="page-title"><i class="fa fa-exchange"></i> Transactions</h2>
	<section class="widget">
		<header>
			<h4>
				Transactions List
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
		<div class="widget-table-overflow">
			<table class="table table-striped table-lg mt-sm mb-0 sources-table">
				<thead>
					<tr>
						<th>Customer</th>
						<th>Bid</th>
						<th>Price</th>
						<th>Channel</th>
						<th>Reference</th>
						<th>Pay Reference</th>
						<th>Pay Response</th>
						<th>Status</th>
						<th>Created</th>
						<th>Updated</th>
					</tr>
				</thead>
				<tbody>
				<?php
					$list = mysqli_query(Yanga::db(), "select * from bid_purchase left join profile on bid_purchase.profile_id = profile.profile_id");
					if(mysqli_num_rows($list) > 0) {
					    if(!isset($page)) {
                			$page=1;
                		}
                		$page_rows=20;
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
                		
                		$list = mysqli_query(Yanga::db(), "select * from bid_purchase left join profile on bid_purchase.profile_id = profile.profile_id order by bid_purchase.updated_date desc $max");
                		
						while($item = mysqli_fetch_array($list)) {
							print '
							<tr>
								<td valign="middle">'.stripslashes($item['first_name'].' '.$item['last_name']).'</td>
								<td valign="middle">'.stripslashes($item['amount']).'</td>
								<td valign="middle">'.number_format($item['amount']).'</td>
								<td valign="middle">'.stripslashes($item['channel']).'</td>
								<td valign="middle">'.stripslashes($item['reference']).'</td>
								<td valign="middle">'.stripslashes($item['payment_reference']).'</td>
								<td valign="middle">'.stripslashes($item['payment_response']).'</td>
								<td valign="middle"><span class="label label-success">'.$item['pay_status'].'</span></td>
								<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
								<td valign="middle">'.date("d-m-Y ", strtotime($item['updated_date'])).'</td>
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
	</section>
	<?php
	if(mysqli_num_rows($list) > 0) { ?>
	<nav>
        <ul class="pagination justify-content-center">
            <?php
			if($page==1){}
			else {
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=transaction-list"  style="color:#fff;">First Page</a></li>';
				$previous=$page-1;
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=transaction-list&p='.$previous.'"  style="color:#fff;">Previous</a></li>';
			}
			if($page==$last){}
			else {
				$next=$page+1;
				echo '<li class="page-item"><a class="page-link" title="Goto Next Page" href=".?page=transaction-list&p='.$next.'" style="color:#fff;">Next Page</a></li>';
				echo '<li class="page-item"><a class="page-link" title="Goto Last Page" href=".?page=transaction-list&p='.$last.'" style="color:#fff;">Last Page</a></li>';
			}
			?>
        </ul>
    </nav>
    <?php }?>
</div>