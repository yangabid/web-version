<div class="content container">
	<h2 class="page-title">Bid Management</h2>
	<section class="widget">
		<header>
			<h4>
				Bid Package
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
						<th>Name</th>
						<th>Bid</th>
						<th>Price</th>
						<th>Creation Date</th>
						<th></th>
					</tr>
				</thead>
				<tbody>
				<?php
					$list = mysqli_query(Yanga::db(), "select * from bid_package");
					if(mysqli_num_rows($list) > 0) {
						while($item = mysqli_fetch_array($list)) {
							print '
							<tr>
								<td valign="middle">'.stripslashes($item['title']).'</td>
								<td valign="middle">'.number_format($item['bid_count']).'</td>
								<td valign="middle">&#8358;'.number_format($item['price']).'</td>
								<td valign="middle">'.date("d-m-Y", strtotime($item['created_date'])).'</td>
								<td valign="middle">
									<a href=".?page=list-bid&task=d&package='.$item['package_id'].'" class="btn btn-danger btn-xs">Delete</a>
								</td>
							</tr>';
						}
					} else {
						print '<tr>
							<td colspan="7"><div class="alert alert-info">No bid package added yet!</div></td>
							</tr>';
					}
				?>
				</tbody>
			</table>
		</div>
	</section>
</div>