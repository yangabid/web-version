<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">My Account</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active">Sign In</li>
                                </ol>
                            </div><!--~~./ breadcrumb-area ~~-->
                        </div><!--~~./ page-header-content ~~-->
                    </div>
                </div>
            </div><!--~~./ end container ~~-->
        </div><!--~~./ end page title area ~~--> 

         <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            User Signin Block
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="user-signin-block ptb-120">
            <div class="container">
                <div class="row align-items-center">
                    <div class="col-lg-6">
                        <div class="sing-in-mockup md-mrb-60">
                            <img src="assets/images/others/signin-mockup.png" alt="Mockup">
                        </div>
                    </div><!--/.col-lg-2-->
                    <div class="col-lg-6">
                        <div class="user-register-area">
                            <div class="form-content">
                                <div class="form-header">
                                    <h4 class="form-subheading">Sign in here</h4>
                                    <h2 class="heading">Welcome to Yangabid</h2>
                                </div>
								<?php
									if(isset($_SESSION['msg'])) {
										print $_SESSION['msg'];
										unset($_SESSION['msg']);
									}
								?>
                                <form class="default-form signin-form" method="POST" action="login.php">
                                    <div class="form-group">
                                        <label for="phone">Phone number</label>
                                        <input id="phone" name="phone" class="numberonly form-controller" type="text" required>
                                    </div><!--/.form-group-->
                                    
                                    <div class="form-group">
                                        <div class="d-flex justify-content-between">
                                            <label for="pass">Password</label>
                                            <div class="custom-control custom-switch">
                                                <input type="checkbox" onclick="showPass()" class="custom-control-input" id="customSwitch">
                                                <label class="custom-control-label" for="customSwitch">Show Password</label>
                                            </div>
                                        </div>
                                        <input id="pass" name="password" class="form-controller" type="password" required>
                                    </div><!--/.form-group-->
                                    
 <script>
 function showPass() {
  var x = document.getElementById("pass");
  if (x.type === "password") {
    x.type = "text";
  } else {
    x.type = "password";
  }
}
</script>                              
                                    <div class="remember-and-password">
                                        <div class="login-form-remember"> 
                                            <label><input id="remembermesignin" value="" type="checkbox"><span>Keep me looged in</span></label>
                                        </div>
                                        <div class="forget-pass">
                                            <a class="btn-password pointer" data-toggle="modal" data-target="#forgotPassword">Forget Password</a>
                                        </div>
                                    </div><!--/.remember-and-password-->
    
                                    <div class="form-btn-group">
                                        <div class="form-login-area">
                                            <button type="submit" class="btn btn-default">
                                                Sign In
                                            </button>
                                        </div>
                                        <div class="login-form-register-now">
                                            You have no account ? <a class="btn-register-now" href=".?page=signup">Sign Up</a>
                                        </div>
                                    </div>
                                    <div class="reg-others-media">
                                        <div class="text">Or, User social media to sign in</div>
                                        <div class="social-media-icons">
                                            <a href="signin.html#"><i class="fab fa-facebook-f"></i></a>
                                            <a href="signin.html#"><i class="fab fa-twitter"></i></a><a href="signin.html#"><i class="fab fa-linkedin-in"></i></a>
                                        </div>
                                    </div>
                                </form>  
                            </div>
                        </div><!--~./ end user register area ~--> 
                    </div><!-- /.col-lg-10 -->
                </div><!-- /.row -->
            </div><!-- /.container -->
        </div><!--~~./ end user signin block ~~-->

<div class="modal" tabindex="-1" role="dialog" id="forgotPassword">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <div class="modal-title">
            Password Reset
        </div>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        <p class="lead">Let's Help Reset Your Password</p>
        <div class="form-group">
            <label for="phone">Phone number</label>
            <input id="phone_recover" name="phone_recover" class="form-controller numberonly" type="text" required>
        </div>
        <div class="mt-3 mb-3 reset-res">

        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-primary do-reset">Reset</button>
        <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>