<?php
include_once '../incl/sql-connect.php';
include_once '../incl/functions.php';

sec_session_start(); // Our custom secure way of starting a PHP session.


if (isset($_POST['username'], $_POST['p'])) {
    $username = $_POST['username'];
    $password = $_POST['p']; // The hashed password.

    if (login($username, $password, $mysqli) == true) {
        // Login success
        header('Location: ../adm_page.php');
    } else {
        // Login failed
        header('Location: ../index.php?error=1');
    }
} else {
    // The correct POST variables were not sent to this page.
    echo 'Invalid Request';
}
?>
