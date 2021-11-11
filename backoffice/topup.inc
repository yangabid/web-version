<style>
.form-control {
    background-color: #040620;
    border: none;
    color: rgba(244,244,245,0.701961);
    box-shadow: none;
}
</style>

<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/selectize.js/0.12.6/css/selectize.bootstrap3.min.css" integrity="sha256-ze/OEYGcFbPRmvCnrSeKbRTtjG4vGLHXgOqsyLFTRjg=" crossorigin="anonymous" />
<div class="content container">
	<h2 class="page-title"><i class="fa fa-dollar"></i> Bid System</h2>
	<section class="widget">
		<header>
			<h4>
				<i class="fa fa-money"></i> Customer Balance Topup
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
		<?php
			if(isset($_GET['res'])) {
				if($_GET['res'] == "0") {
					print '<br /><div class="alert alert-success">Customer balance Topup was successfully</div>';
				} else if($_GET['res'] == "1") {
					print '<br /><div class="alert alert-danger">Customer balance Topup failed!</div>';
				}
			}
		?>
		<form action="./" method="post" class="form-horizontal" role="form" style="margin-top:25px">
			<input type="hidden" name="action" value="topup-balance" />
			<div class="form-group">
				<label for="name" class="col-sm-3 control-label">Customer</label>
				<div class="col-sm-5">
					<select name="customer" id="filterUser" required>
						<option selected value="">Select a customer</option>
						<?php
						$list = mysqli_query(Yanga::db(), "select * from profile left join profile_bid_account on profile.profile_id = profile_bid_account.profile_id");
						if(mysqli_num_rows($list) > 0) {
							while($item = mysqli_fetch_array($list)) {
								print '
								<option value="'.$item['profile_id'].'">'.stripslashes($item['profile_id']).' - '.stripslashes($item['first_name']).' '.stripslashes($item['last_name']).' ['.number_format($item['bid_balance']).']</option>';
							}
						} else {
							print '<option>No user found!</option>';
						}
						?>
					</select>
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Bid (1 = 100 bid)</label>
				<div class="col-sm-5">
					<input type="number" class="form-control" name="bid" required/>
				</div>
			</div>
			<hr>
			<div class="form-group" style="padding-top:25px">
				<div class="col-sm-offset-3 col-sm-9">
					<button type="submit" class="btn btn-primary"><i class="fa fa-money"></i> Topup</button>
				</div>
			</div> <!-- form-group // -->
		</form>
	</section>
</div>