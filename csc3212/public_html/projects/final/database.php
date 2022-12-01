<?php
    $dsn = 'mysql:host=joecool.highpoint.edu;dbname=CSC3212_S22_mburton_db';
    $username = 'mburton';
    $password = '1803337';

    try {
        $db = new PDO($dsn, $username, $password);
    } catch (PDOException $e) {
        $error_message = $e->getMessage();
        include('database-error.php');
        exit();
    }
?>
