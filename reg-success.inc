<?php @session_start(); ?>
<!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Page Title Area
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <div class="page-title-area bg-white-smoke">
            <div class="container">
                <div class="row">
                    <div class="col-12">
                        <div class="page-header-content text-center">
                            <div class="page-header-caption">
                                <h2 class="page-title">Account Activation</h2>
                            </div><!--~~./ page-header-caption ~~-->
                            <div class="breadcrumb-area">
                                <ol class="breadcrumb">
                                    <li class="breadcrumb-item"><a href="./">Home</a></li>  
                                    <li class="breadcrumb-item active">Activation</li>
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
        <div class="user-signup-block ptb-120">
            <div class="bg-left bg-image" style="background-image: url('assets/images/shape/signup-shape.png')"></div>
            <div class="container">
                <div class="row">
                    <div class="col-lg-6">
                        <div class="sing-in-mockup md-mrb-60">
                            <img src="assets/images/others/signin-mockup.png" alt="Mockup">
                        </div>
                    </div><!--/.col-lg-2-->
                    <div class="col-lg-6">
                        <div class="user-register-area">
                            <div class="form-content">
                                <div class="card bg-primary">
									<div class="card-body">
										<h3 style="color:#fff;"><?php @session_start(); print $_SESSION['f_name'].' '.$_SESSION['l_name']; ?> </h3> 
										<p style="color:#fff;">Enter the code sent to your registered phone number and email address below to complete your registration.</p>
                                        <div class="input-group">
                                            <input type="text" id="activation-code" class="form-control" style="border-radius:28px; font-size:18px; font-weight:bold" placeholder="Activation code">
                                            <button class="btn btn-default ml-3 resend-code">Resend Code</button>
                                            <button class="btn btn-white btn-default ml-3 profile-activation">Activate</button>
                                        </div>
                                        <div class="activation-res mt-3"></div>
									</div>
								</div>
                            </div>
                        </div><!--~./ end user register area ~--> 
                    </div><!-- /.col-lg-10 -->
                </div><!-- /.row -->
            </div><!-- /.container -->
        </div><!--~~./ end user signup block ~~-->