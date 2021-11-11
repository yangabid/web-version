<div class="content container">
	<h2 class="page-title">Items Management</h2>
	<section class="widget">
		<header>
			<h4>
				Item List
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
						<th></th>
						<th>Name</th>
						<th>Description</th>
						<th>Bid</th>
						<th>Price</th>
						<th>Creation Date</th>
						<th></th>
					</tr>
				</thead>
				<tbody>
				<?php
					$list = mysqli_query(Yanga::db(), "select * from bid_items");
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
                		
                		$list = mysqli_query(Yanga::db(), "select * from bid_items $max");
						while($item = mysqli_fetch_array($list)) {
							print '
							<tr>
								<td valign="middle"><img src="../'.$item['pics_1'].'" class="img-responsive img" style="width:40px;" /></td>
								<td valign="middle">'.stripslashes($item['title']).'</td>
								<td valign="middle">'.substr(stripslashes($item['description']), 0, 100).'</td>
								<td valign="middle">'.stripslashes($item['bid']).'</td>
								<td valign="middle"><small class="table-info">Actual:</small> &#8358;'.number_format($item['actual_price']).'<br /><small class="table-info">Discounted:</small> &#8358;'.number_format($item['discount_price']).'</td>
								<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
								<td valign="middle">
									<a href="..?page=view-product&product='.$item['item_id'].'" target="_new" class="btn btn-info btn-xs">View</a> 
									<a href=".?page=list-item&task=d&product='.$item['item_id'].'" class="btn btn-danger btn-xs">Delete</a>
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
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=list-item"  style="color:#fff;">First Page</a></li>';
				$previous=$page-1;
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=list-item&p='.$previous.'"  style="color:#fff;">Previous</a></li>';
			}
			if($page==$last){}
			else {
				$next=$page+1;
				echo '<li class="page-item"><a class="page-link" title="Goto Next Page" href=".?page=list-item&p='.$next.'" style="color:#fff;">Next Page</a></li>';
				echo '<li class="page-item"><a class="page-link" title="Goto Last Page" href=".?page=list-item&p='.$last.'" style="color:#fff;">Last Page</a></li>';
			}
			?>
        </ul>
    </nav>
    <?php }?>
</div>