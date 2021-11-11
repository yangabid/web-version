<!doctype html>
<html lang="eng">

<head>
    <!-- Basic Page Needs
    ================================================== -->
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <!-- Specific Meta
    ================================================== -->
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <meta name="description" content="Yanga Bid Auction">

    <!-- Titles
    ================================================== -->
    <title>Yanga - Bid And Auction</title>

    <!-- Favicons
    ================================================== -->
    <link rel="shortcut icon" href="assets/images/favicon.ico">
    <link rel="apple-touch-icon" sizes="72x72" href="assets/images/android-icon-72x72.png">
    <link rel="apple-touch-icon" sizes="114x114" href="assets/images/apple-icon-144x144.png">

    <!-- Custom Font
    ================================================== -->
    <link href="https://fonts.googleapis.com/css?family=Lato:300,400,700,700i,900&display=swap" rel="stylesheet">  

    <!-- CSS
    ================================================== -->
    <link rel="stylesheet" href="assets/css/bootstrap.min.css">
    <link rel="stylesheet" href="assets/css/owl.carousel.min.css">
    <link rel="stylesheet" href="assets/css/meanmenu.min.css">
    <link rel="stylesheet" href="assets/css/simple-scrollbar.css">
    <link rel="stylesheet" href="assets/css/odometer-theme-default.css">
    <link rel="stylesheet" href="assets/css/icomoon.css">
    <link rel="stylesheet" href="assets/css/style.css">
    <style>
    .mean-container a.meanmenu-reveal span {
        background:green !important;
    }
    </style>
    <script src="assets/js/modernizr.min.js"></script>
</head>

<body>
    
    <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Start Preloader
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~--> 
    <div class="preloader">
        <div class="preloader-inner">
            <div class="preloader-icon">
                <span></span>
                <span></span>
            </div><!-- /preloader-icon -->
        </div><!-- /preloader-inner -->
    </div><!-- /preloader -->

   <!--********************************************************-->
    <!--********************* SITE CONTENT *********************-->
    <!--********************************************************-->
    <div class="site-content">
        <!--~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Start Site Header
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-->
        <header class="site-header">
            <div class="header-top-navbar">
                <div class="container">
                    <div class="row">
                        <div class="col-lg-5">
                            <div class="top-navbar-left">
                                <ul class="info">
                                    <li class="info-date"><span class="fa fa-envelope"></span> <a href="mailto:talk2us@yangabid.com">talk2us@yangabid.com</a>, <a href="mailto:yangabid21@gmail.com">yangabid21@gmail.com</a></li>
                                    <li class="temperature"><span style="color:#4FCE5D;" class="fab fa-whatsapp"></span> 07062013791</li>
                                </ul>
                            </div><!--~./ top-navbar-left ~-->
                        </div>
						<div class="col-lg-2">
							<div class="top-navbar-left ">
								<?php
									if(isset($_SESSION['bidder'])) {
										print '
										<ul class="info">
											<li class="temperature"><a><i class="fas fa-coins" style="color:green"></i></a> BID: <span class="bid-balance" style="color:#fff !important; font-weight:bold;"> '.$_SESSION['balance'].'</span></li>
										</ul>';
									
									}
								?>
							</div>
						</div>
                        <div class="col-lg-5">
                            <div class="top-navbar-right">
                                <div class="user-registration-area">
									<?php
										if(!isset($_SESSION['bidder'])) {
											print '
                                    <a class="user-reg-btn" href=".?page=signin">
                                        <span class="fas fa-lock"></span>
                                        Login
                                    </a>
                                    <a class="user-reg-btn" href=".?page=signup">
                                        <span class="icon-user-1"></span>
                                        Sign Up
                                    </a>';
										}
									?>
									<?php
									    //'.number_format($_SESSION['balance']).'
										if(isset($_SESSION['bidder'])) {
										    if(strlen($_SESSION['pics']) > 4) {
										        print '<img src="'.$_SESSION['pics'].'" class="rounded-circle img-thumbnail" style="width:44px; height:44px"/>';
										    }
											print '
									
                                    <strong class="ml-3 mr-3">'.$_SESSION['f_name'].'</strong> 
                                    <a class="user-reg-btn" href=".?page=signout">
                                        <span class="icon-logout"></span>
                                        Sign out
                                    </a>
                                    <button class="btn btn-outline-light d-sm-none d-inline p-0">
                                        <span class="fas fa-coins" style="color:green"></span>
                                        BID: <span class="bid-balance" style="color:#fff !important; font-weight:bold;">'.$_SESSION['balance'].'</span>
                                    </button>';
										}
									?>
                                </div>
                            </div><!--~./ top-navbar-right ~-->
                        </div>
                    </div>
                </div>
            </div><!-- /.header-top-navbar -->

            <div class="site-navigation">
                <div class="container">
                    <div class="row">
                        <div class="col-12">
                            <div class="navbar navbar-expand-lg navigation-area">
                                <!-- Site Branding -->
                                <div class="site-branding">
                                    <a class="site-logo" href="./">
                                        <img src="assets/images/logo/yanga-logo.PNG" alt="Yangabid Logo" style="width:150px;"/>
                                    </a>
                                </div><!-- /.site-branding -->
                                <div class="mainmenu-area">
                                    <nav class="menu">
                                        <ul id="nav">                  
                                            <li><a class="active" href="./">Home</a></li>
                                            <li class="dropdown-trigger">
                                                <a href="#">Auctions</a>
                                                <ul class="dropdown-content">
                                                    <li><a href=".?page=auction">States</a></li>
                                                </ul>
                                            </li>       
                                            <li><a href=".?page=winners">Winners</a></li>
											<li class="dropdown-trigger">
                                                <a href="#">Account</a>
                                                <ul class="dropdown-content">
													<?php
														if(!isset($_SESSION['bidder'])) {
															print '<li><a href=".?page=signin">Sign In</a></li>';
														} else {
															print '
															<li><a href=".?page=profile">My Profile</a></li>
															<li><a href=".?page=signout">Sign out</a></li>';
														}
													?>
                                                </ul>
                                            </li>
                                            <li>
                                                <a href=".?page=contact">Contact</a>
                                            </li>
                                        </ul> <!-- /.menu-list -->
                                    </nav><!--/.menu-->
									<!--
                                    <div class="header-navigation-right">
                                        <div class="search-wrap">
                                            <div class="search-btn">
                                                <i class="fas fa-search"></i>  
                                            </div>
                                            <div class="search-form">
                                                <form action="#">
                                                    <input type="search" placeholder="Search">
                                                    <button type="submit"><i class="fas fa-search"></i> </button>
                                                </form>
                                            </div>
                                        </div>
										
                                    </div>
									-->
                                </div><!--~./ mainmenu-wrap ~-->
                            </div><!--~./ navigation-area ~-->
                        </div><!--  /.col-12 -->
                    </div><!--  /.row -->
                </div>
            </div><!-- /.site-navigation -->

            <div class="mobile-menu-area">
                <div class="container">
                    <div class="row">
                        <div class="col-12">
                            <!--~~~~~~~ Start Mobile Menu ~~~~~~~~-->
                            <div class="mobile-menu">
                                <a class="mobile-logo" href="./">
                                    <img src="assets/images/logo/yanga-logo.PNG" alt="logo">
                                </a>
                            </div><!--~~./ end mobile menu ~~-->
                        </div><!--  /.col-12 -->
                    </div><!--  /.row -->
                </div><!-- /.container -->
            </div><!-- /.mobile-menu-area -->
        </header><!--~~./ end site header ~~-->
        <!--~~~ Sticky Header ~~~-->
        <div id="sticky-header"></div><!--~./ end sticky header ~-->