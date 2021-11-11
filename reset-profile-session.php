<?php
  	date_default_timezone_set("Africa/Lagos");
    include('yanga.php');
    $auctions = mysqli_query(Yanga::db(), 'truncate table session_locker');
?>