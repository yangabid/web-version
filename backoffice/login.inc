<div class="single-widget-container">
	<section class="widget login-widget">
		<header class="text-align-center">
			<h4>Yanga Bid - Back Office</h4>
		</header>
		<div class="body">
			<?php
				if(isset($_SESSION['msg'])) {
					echo $_SESSION['msg'];
					unset($_SESSION['msg']);
				}
			?>
			<form class="no-margin"
				  action="?page=perform-login" method="post">
				<fieldset>
					<input type="hidden" name="action" value="login" />
					<div class="form-group">
						<label for="email" >Username</label>
						<div class="input-group">
							<span class="input-group-addon">
								<i class="fa fa-user"></i>
							</span>
							<input name="username" id="username" type="text" class="form-control input-lg input-transparent"
								   placeholder="Your username">
						</div>
					</div>
					<div class="form-group">
						<label for="password" >Password</label>

						<div class="input-group input-group-lg">
							<span class="input-group-addon">
								<i class="fa fa-lock"></i>
							</span>
							<input name="password" id="password" type="password" class="form-control input-lg input-transparent"
								   placeholder="Your password">
						</div>
					</div>
				</fieldset>
				<div class="form-actions">
					<button type="submit" class="btn btn-block btn-lg btn-danger">
						<span class="small-circle"><i class="fa fa-caret-right"></i></span>
						<small>Sign In</small>
					</button>
					<a class="forgot" href="#">Forgot Username or Password?</a>
				</div>
			</form>
		</div>
	</section>
</div>