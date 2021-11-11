<style>
.form-control {
    background-color: #040620;
    border: none;
    color: rgba(244,244,245,0.701961);
    box-shadow: none;
}
</style>

<div class="content container">
	<h2 class="page-title"><i class="fa fa-search"></i> Search Engine</h2>
	<section class="widget">
		<form action=".?page=search" method="get" class="form-horizontal" role="form" style="margin-top:25px">
		    <input type="hidden" name="page" value="search" />
		    <div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Search Type</label>
				<div class="col-sm-3">
					<select class="form-control" name="type" id="type" required onchange="updatePlaceholder()">
					    <option selected disabled>Select search type</option>
					    <option value="customer">Customers</option>
					    <option value="auction">Auction</option>
					    <option value="item">Bid Item</option>
					    <option value="transaction">Transactions</option>
					</select>
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Search Keyword</label>
				<div class="col-sm-6">
					<input type="text" class="form-control" name="term" id="term" placeholder="" required>
				</div>
			</div>
			<hr>
			<div class="form-group" style="padding-top:25px">
				<div class="col-sm-offset-3 col-sm-9">
					<button type="submit" class="btn btn-primary"><i class="fa fa-search"></i> Begin Search</button>
				</div>
			</div> <!-- form-group // -->
		</form>
	</section>
	<?php
	    if(isset($_GET['type']) && isset($_GET['term'])) {
	        $type = addslashes($_GET['type']);
	        $term = addslashes($_GET['term']);
	        // Customer search
	        if($type == "customer") {
	            print '<h2><i class="fa fa-users"></i> Bidders Search <small>(Search term - '.$term.')</small></h2>';
	            $list = mysqli_query(Yanga::db(), 'select * from profile where first_name like "%'.$term.'%" or last_name like "%'.$term.'%" or email like "%'.$term.'%" or phone like "%'.$term.'%" order by first_name asc');
	       ?>
	       <div class="widget-table-overflow table-responsive">
			<table class="table table-striped table-lg mt-sm mb-0 sources-table">
				<thead>
					<tr>
						<th></th>
						<th>First Name</th>
						<th>Last Name</th>
						<th>Phone</th>
						<th>Email</th>
						<th>Status</th>
						<th>Creation Date</th>
						<th></th>
					</tr>
				</thead>
				<tbody>
	       <?php
	            if(mysqli_num_rows($list) > 0) {
	                while($item = mysqli_fetch_array($list)) {
						print '
						<tr>
							<td style="width:0px;"><i class="fa fa-user"></i></td>
							<td valign="middle">'.stripslashes($item['first_name']).'</td>
							<td valign="middle">'.stripslashes($item['last_name']).'</td>
							<td valign="middle">'.stripslashes($item['phone']).'</td>
							<td valign="middle">'.stripslashes($item['email']).'</td>
							<td valign="middle">'.stripslashes($item['status']).'</td>
							<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
							<td valign="middle">
							    <a onclick="return confirm(\'Are you sure?\')" href=".?page=customers-list&op=d&user='.$item['profile_id'].'" class="btn btn-danger btn-xs">Delete</a>
							</td>
						</tr>';
					}
	            }
	            else {
	                print '<tr>
					<td colspan="7"><div class="alert alert-info">No registered customer found!</div></td>
					</tr>';
	            }
	            ?>
				</tbody>
			</table>
		</div>
		<?php
	        }
	        // Auction search
	        if($type == "auction") {
	            print '<h2><i class="fa fa-clock-o"></i> Auction Search <small>(Search term - '.$term.')</small></h2>';
	            $list = mysqli_query(Yanga::db(), 'select * from auctions as a left join bid_items as b on a.item_id= b.item_id where a.auction_id like "%'.$term.'%" order by a.created_date desc');
	            ?>
	            <div class="widget-table-overflow table-responsive">
        			<table class="table table-striped table-lg mt-sm mb-0 sources-table">
        				<thead>
        					<tr>
        						<th></th>
        						<th>Auction ID</th>
        						<th>Item</th>
        						<th>State</th>
        						<th>Entry Bid</th>
        						<th>Start</th>
        						<th>End</th>
        						<th>Creation Date</th>
        						<th>Status</th>
        						<th></th>
        					</tr>
        				</thead>
        				<tbody>
        		<?php
	                if(mysqli_num_rows($list) > 0) {
	                    while($item = mysqli_fetch_array($list)) {
	                    print '
							<tr>
								<td valign="middle"><img src="../'.$item['pics_1'].'" class="img-responsive img" style="width:40px;" /></td>
								<td valign="middle">'.stripslashes($item['auction_id']).'</td>
								<td valign="middle">'.stripslashes($item['title']).'<br /><small style="color:#777;">Actual:</small> &#8358;'.number_format($item['actual_price']).' / <small style="color:#777;">Discounted:</small> &#8358;'.number_format($item['discount_price']).'</td>
								<td valign="middle">'.stripslashes($item['state']).'</td>
								<td valign="middle">'.number_format($item['bid']).'</td>
								<td valign="middle">'.date("d-m-Y H:i:s", strtotime($item['start_date'])).'</td>
								<td valign="middle">'.date("d-m-Y H:i:s", strtotime($item['end_date'])).'</td>
								<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
								<td valign="middle">'.$item[7].'</td>
								
								<td valign="middle">
									<a href=".?page=auction-analytics&auction='.$item['auction_id'].'" target="_new" class="btn btn-info btn-xs"><i class="fa fa-bar-chart"></i> Statics</a> &nbsp; &nbsp; &nbsp; &nbsp;
									';
							if($item[7]!="CLOSED") {
								print '<a href=".?page=list-auction&task=close&auction='.$item['auction_id'].'" class="btn btn-danger btn-xs">CLOSE</a>';
							}
									print '
								</td>
							</tr>';
						}
	                } else {
						print '<tr>
							<td colspan="7"><div class="alert alert-info">No auction with found with the specified search term!</div></td>
							</tr>';
					}
					?>
				</tbody>
			</table>
		</div>
		    <?php
	        }
	        // Items
	        if($type == "item") {
	            print '<h2><i class="fa fa-shopping-cart"></i> Item Search <small>(Search term - '.$term.')</small></h2>';
	            $list = mysqli_query(Yanga::db(), 'select * from bid_items where item_id like "%'.$term.'%" or title like "%'.$term.'%" or description like "%'.$term.'%" or bid like "%'.$term.'%" or actual_price like "%'.$term.'%" order by title asc');
	            ?>
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
        		    if(mysqli_num_rows($list) > 0) {
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
        	<?php
	        }
	        // Transaction search
	        if($type == "transaction") {
	            print '<h2><i class="fa fa-exchange"></i> Transaction Search <small>(Search term - '.$term.')</small></h2>';
	            
	            $list = mysqli_query(Yanga::db(), 'select * from bid_purchase left join profile on bid_purchase.profile_id = profile.profile_id where bid_purchase.reference like "%'.$term.'%"  or bid_purchase.payment_reference like "%'.$term.'%"');
	            ?>
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
	            if(mysqli_num_rows($list) > 0) {
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
							<td colspan="7"><div class="alert alert-info">No transaction found!</div></td>
							</tr>';
    			}
	        }
	    }
	?>
</div>
<script>
function updatePlaceholder() {
    op_type = document.getElementById("type").value;
    if(op_type == "customer") {
        document.getElementsByName('term')[0].placeholder='Enter first name or last name or phone number or email';
    }
    else if(op_type == "auction") {
        document.getElementsByName('term')[0].placeholder='Enter Auction ID';
    }
    else if(op_type == "item") {
        document.getElementsByName('term')[0].placeholder='Enter Item ID or item title or item price or item description';
    }
    else if(op_type == "transaction") {
        document.getElementsByName('term')[0].placeholder='Enter Reference or Pay Reference';
    }
    else {
        document.getElementsByName('term')[0].placeholder='';
    }
}
</script>