<div class="content container">
	<h2 class="page-title">Customer Management</h2>
	<?php
	    @session_start();
	    if(isset($_SESSION['msg'])) {
	        print $_SESSION['msg'];
	        unset($_SESSION['msg']);
	    }
	?>
	<section class="widget">
		<header>
			<h4>
				Customers List
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
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
					$list = mysqli_query(Yanga::db(), "select * from profile");
					if(mysqli_num_rows($list) > 0) {
					    if(!isset($page)) {
                			$page=1;
                		}
                		$page_rows=50;
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
                		
                		$list = mysqli_query(Yanga::db(), "select * from profile order by created_date desc $max");
                		
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
					} else {
						print '<tr>
							<td colspan="7"><div class="alert alert-info">No registered customer found!</div></td>
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
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=customers-list"  style="color:#fff;">First Page</a></li>';
				$previous=$page-1;
				print '<li class="page-item"><a class="page-link" title="Goto First Page" href=".?page=customers-list&p='.$previous.'"  style="color:#fff;">Previous</a></li>';
			}
			if($page==$last){}
			else {
				$next=$page+1;
				echo '<li class="page-item"><a class="page-link" title="Goto Next Page" href=".?page=customers-list&p='.$next.'" style="color:#fff;">Next Page</a></li>';
				echo '<li class="page-item"><a class="page-link" title="Goto Last Page" href=".?page=customers-list&p='.$last.'" style="color:#fff;">Last Page</a></li>';
			}
			?>
        </ul>
    </nav>
    <?php } ?>
</div>