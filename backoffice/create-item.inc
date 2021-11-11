<style>
.form-control {
    background-color: #040620;
    border: none;
    color: rgba(244,244,245,0.701961);
    box-shadow: none;
}
</style>

<div class="content container">
	<h2 class="page-title">Item Management</h2>
	<section class="widget">
		<header>
			<h4>
				<i class="fa fa-shopping-cart"></i> New Auctionable Item
			</h4>
			<div class="widget-controls">
				<a data-widgster="expand" title="Expand" href="#"><i class="glyphicon glyphicon-plus"></i></a>
				<a data-widgster="collapse" title="Collapse" href="#"><i class="glyphicon glyphicon-minus"></i></a>
				<a data-widgster="close" title="Close" href="#"><i class="glyphicon glyphicon-remove"></i></a>
			</div>
		</header>
		<?php
			if(isset($_GET['res'])) {
				if($_GET['res'] == 0) {
					print '<br /><div class="alert alert-success">Item added successfully</div>';
				} else {
					print '<br /><div class="alert alert-danger">Item creation failed!</div>';
				}
			}
		?>
		<form action="./" method="post" enctype="multipart/form-data" class="form-horizontal" role="form" style="margin-top:25px">
			<input type="hidden" name="action" value="add-product" />
			<div class="form-group">
				<label for="name" class="col-sm-3 control-label">Name</label>
				<div class="col-sm-9">
					<input type="text" class="form-control" name="name" id="name" placeholder="Item Name">
				</div>
			</div>
			<div class="form-group">
				<label for="about" class="col-sm-3 control-label">Description</label>
				<div class="col-sm-9">
					<textarea class="form-control" name="description"></textarea>
				</div>
			</div>
			<div class="form-group">
				<label class="col-sm-3 control-label">Price</label>
				<div class="col-sm-3"> 
					<label class="control-label small" for="date_start">Actual: </label>
					<input type="text" class="form-control" name="a_amt" id="a_amt" placeholder="Actual price">
				</div>
				<div class="col-sm-3">   
					<label class="control-label small" for="date_finish">Discounted:</label>
					<input type="text" class="form-control" name="d_amt" id="d_amt" placeholder="Auction price">
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Bid Quantity</label>
				<div class="col-sm-3">
					<input type="text" class="form-control" name="qty" id="qty" placeholder="Minimum required bid">
				</div>
			</div>
			<!--
			<div class="form-group">
				<label class="col-sm-3 control-label">Duration</label>
				<div class="col-sm-3"> 
					<label class="control-label small" for="date_start">Beginning: </label>
					<input type="text" class="form-control" name="date_start" id="date_start" placeholder="Start date">
				</div>
				<div class="col-sm-3">   
					<label class="control-label small" for="date_finish">End:</label>
					<input type="text" class="form-control" name="date_finish" id="date_finish" placeholder="End date">
				</div>
			</div> -->
			<div class="form-group">
				<label for="name" class="col-sm-3 control-label">Item Image</label>
				<div class="col-sm-3">
					<label class="control-label small" for="file_img">Picture 1:</label> <input type="file" name="pics1">
				</div>
				<div class="col-sm-3">
					<label class="control-label small" for="file_img">Picture 2:</label>  <input type="file" name="pics2">
				</div>
				<div class="col-sm-3">
					<label class="control-label small" for="file_img">Picture 3:</label>  <input type="file" name="pics3">
				</div>
			</div> <!-- form-group // -->
			<hr>
			<div class="form-group" style="padding-top:25px">
				<div class="col-sm-offset-3 col-sm-9">
					<button type="submit" class="btn btn-primary">Create</button>
				</div>
			</div> <!-- form-group // -->
		</form>
	</section>
</div>