<style>
.form-control {
    background-color: #040620;
    border: none;
    color: rgba(244,244,245,0.701961);
    box-shadow: none;
}
</style>

<div class="content container">
	<h2 class="page-title">Bid Management</h2>
	<section class="widget">
		<header>
			<h4>
				<i class="fa fa-shopping-cart"></i> New Bid Pack
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
					print '<br /><div class="alert alert-success">Bid package added successfully</div>';
				} else {
					print '<br /><div class="alert alert-danger">Bid package creation failed!</div>';
				}
			}
		?>
		<form action="./" method="post" class="form-horizontal" role="form" style="margin-top:25px">
			<input type="hidden" name="action" value="add-bid-pack" />
			<div class="form-group">
				<label for="name" class="col-sm-3 control-label">Name</label>
				<div class="col-sm-4">
					<input type="text" class="form-control" name="name" id="name" placeholder="Bid pack title">
				</div>
			</div>
			<div class="form-group">
				<label class="col-sm-3 control-label">Price</label>
				<div class="col-sm-3">
					<input type="text" class="form-control" name="price" id="price" placeholder="">
				</div>
			</div>
			<div class="form-group">
				<label for="qty" class="col-sm-3 control-label">Bid Quantity</label>
				<div class="col-sm-3">
					<input type="text" class="form-control" name="bid" id="bid" placeholder="Package bid count">
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