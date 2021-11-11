<?php
@session_start();
if(isset($_POST['ref']) && isset($_POST['gate'])) {
    $bidder = addslashes($_SESSION['bidder']);
    $gate = $_POST['gate'];
    $amount = $gate * 100;
    $package = $gate.' Days';
    $ref = ($_POST['ref']);
    $now = date('Y-m-d H:i:s');
    include('yanga.php');
    if(mysqli_query(Yanga::db(), 'INSERT INTO bid_purchase (profile_id, amount, channel, yanga_reference, package_id, created_date) VALUES ("'.$bidder.'", "'.$amount.'", "WEB-PayStack", "'.$ref.'", "'.$package.'", "'.$now.'")')) {       print 'valid';
    } else {
        print 'invalid';
    }
}
else if(isset($_POST['handle']) && $_POST['handle'] == "verify" && isset($_POST['trxref'])) {
    include('yanga.php');
    $bidder = $_SESSION['bidder'];
    $now = date('Y-m-d H:i:s');
    $trans = addslashes($_POST['trans']);
    $status = addslashes($_POST['status']);
    $trxref = addslashes($_POST['trxref']);
    $msg = addslashes($_POST['msg']);
    $payment = mysqli_query(Yanga::db(), 'SELECT * FROM bid_purchase WHERE profile_id = "'.$bidder.'" and yanga_reference = "'.$trxref.'"');
    if(mysqli_num_rows($payment) == 1) {
        $data = mysqli_fetch_array($payment);
        $pass_day = ($data['amount']/100);
        $get_gate = mysqli_fetch_array(mysqli_query(Yanga::db(), 'SELECT * from profile_bid_account WHERE profile_id = "'.$bidder.'"'));
        $current_expiry = $get_gate['gate_pass_expiry'];
        $new_expiry = date('Y-m-d', strtotime($current_expiry. " + $pass_day days"));
        
        $diff = abs(strtotime($new_expiry) - strtotime(date('Y-m-d')));
            
        $years = floor($diff / (365*60*60*24));
        $months = floor(($diff - $years * 365*60*60*24) / (30*60*60*24));
        $days = floor(($diff - $years * 365*60*60*24 - $months*30*60*60*24)/ (60*60*24));

		$_SESSION['gate_pass'] = $days;
        
        mysqli_query(Yanga::db(), 'UPDATE bid_purchase SET payment_reference="'.$trxref.'",  pay_status="'.$status.'", payment_response = "'.$msg.'", updated_date = "'.$now.'" WHERE profile_id = "'.$bidder.'" AND yanga_reference = "'.$trxref.'"');
        
        if(mysqli_query(Yanga::db(), 'UPDATE profile_bid_account SET gate_pass_expiry = "'.$new_expiry.'", updated_date = "'.$now.'" WHERE profile_id = "'.$bidder.'"')) {
            $output = array(
                'pass' => $_SESSION['gate_pass'],
                'notif' => '<div class="card" style="background:#D9D900; border:2px solid #fff;">
                    <div class="card-body">
                        <h3 style="color: #0b0e3c">Gate pass successfully purchased</h3>
                        <p class="lead" style="color:#0B0E3C">
                        Reference: <strong>'.$trxref.'</strong><br />
                        Response: <strong>'.$msg.'</strong><br />
                        Status: <strong>'.$status.'</strong></p>
                        <p class="lead" style="color:#0B0E3C; font-weight:bold;">You can now get your bids</p>
                    </div>
                </div>'
            );
            echo json_encode($output);
        } else {
            print '<div class="alert alert-danger mt-3 mb-0"><i class="fa fa-info-circle"></i> Cannot display result at the moment, please retry.</div>';
        }
    }
} else {
    echo 'Invalid transaction';
}
?>