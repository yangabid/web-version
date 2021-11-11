<style>
.form-control {
    background-color: #040620;
    border: none;
    color: rgba(244,244,245,0.701961);
    box-shadow: none;
}
</style>

<div class="content container">
	<h2 class="page-title"><i class="fa fa-clock-o"></i> Auction System</h2>
	<section class="widget">
		<header>
			<h4>
				<i class="fa fa-dollar"></i> New Auction
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
					print '<br /><div class="alert alert-success">Item added successfully</div>';
				} else if($_GET['res'] == "1") {
					print '<br /><div class="alert alert-danger">Item creation failed!</div>';
				} else if($_GET['res'] == "dup") {
					print '<br /><div class="alert alert-info">Auction creation failed because the selected auction item is ACTIVE!</div>';
				} else {}
			}
		?>
		<form action="./" method="post" class="form-horizontal" role="form" style="margin-top:25px">
			<input type="hidden" name="action" value="add-auction" />
			<div class="form-group">
				<label for="name" class="col-sm-3 control-label">Auction Item</label>
				<div class="col-sm-5">
					<select name="item" id="item" required class="form-control">
						<option selected value="">Pick one auctionable item</option>
						<?php
						$list = mysqli_query(Yanga::db(), "select * from bid_items");
						if(mysqli_num_rows($list) > 0) {
							while($item = mysqli_fetch_array($list)) {
								print '
								<option value="'.$item['item_id'].'">'.stripslashes($item['title']).' [&#8358;'.number_format($item['actual_price']).'] - [&#8358;'.number_format($item['discount_price']).']</option>';
							}
						} else {
							print '<option>No item found!</option>';
						}
						?>
					</select>
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Bid Quantity</label>
				<div class="col-sm-3">
					<input type="text" class="form-control" name="bid" id="bid" placeholder="Minimum entry bid" required>
				</div>
			</div>
			<div class="form-group">
				<label class="col-sm-3 control-label">Duration</label>
				<div class="col-sm-3"> 
					<label class="control-label small" for="date_start">Beginning: </label>
					<input type="date" class="form-control" name="date_start" id="date_start" placeholder="Start date"  style="border-bottom-left-radius:0px; border-bottom-right-radius:0px;" required>
					<input type="time" class="form-control" name="time_start" id="time_start" placeholder="Start Time" style="border-top-left-radius:0px; border-top-right-radius:0px;" required>
				</div>
				<div class="col-sm-3">   
					<label class="control-label small" for="date_finish">End:</label>
					<input type="date" class="form-control" name="date_end" id="date_end" placeholder="End date" style="border-bottom-left-radius:0px; border-bottom-right-radius:0px;" required>
					<input type="time" class="form-control" name="time_end" id="time_end" placeholder="End Time" style="border-top-left-radius:0px; border-top-right-radius:0px;" required>
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Target State</label>
				<div class="col-sm-3">
					<select name="state" class="form-control" required>
						<option value="" disabled selected="selected">Select</option>
						<option value="Instant">Instant Auction</option>
						<option value="Jackpot">Jackpot</option>
						<option value="Abuja FCT">Abuja FCT</option>
						<option value="Abia">Abia</option>
						<option value="Adamawa">Adamawa</option>
						<option value="Akwa Ibom">Akwa Ibom</option>
						<option value="Anambra">Anambra</option>
						<option value="Bauchi">Bauchi</option>
						<option value="Bayelsa">Bayelsa</option>
						<option value="Benue">Benue</option>
						<option value="Borno">Borno</option>
						<option value="Cross River">Cross River</option>
						<option value="Delta">Delta</option>
						<option value="Ebonyi">Ebonyi</option>
						<option value="Edo">Edo</option>
						<option value="Ekiti">Ekiti</option>
						<option value="Enugu">Enugu</option>
						<option value="Gombe">Gombe</option>
						<option value="Imo">Imo</option>
						<option value="Jigawa">Jigawa</option>
						<option value="Kaduna">Kaduna</option>
						<option value="Kano">Kano</option>
						<option value="Katsina">Katsina</option>
						<option value="Kebbi">Kebbi</option>
						<option value="Kogi">Kogi</option>
						<option value="Kwara">Kwara</option>
						<option value="Lagos">Lagos</option>
						<option value="Nassarawa">Nassarawa</option>
						<option value="Niger">Niger</option>
						<option value="Ogun">Ogun</option>
						<option value="Ondo">Ondo</option>
						<option value="Osun">Osun</option>
						<option value="Oyo">Oyo</option>
						<option value="Plateau">Plateau</option>
						<option value="Rivers">Rivers</option>
						<option value="Sokoto">Sokoto</option>
						<option value="Taraba">Taraba</option>
						<option value="Yobe">Yobe</option>
						<option value="Zamfara">Zamfara</option>
						<option value="All">All State</option>
				</select>
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Description</label>
				<div class="col-sm-6">
					<textarea class="form-control" name="description" id="description" placeholder="Short Description"></textarea>
				</div>
			</div>
			<hr>
			<div class="form-group" style="padding-top:25px">
				<div class="col-sm-offset-3 col-sm-9">
					<button type="submit" class="btn btn-primary">Create</button>
				</div>
			</div> <!-- form-group // -->
		</form>
	</section>
</div>