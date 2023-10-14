<?php
$text = $_POST['text'];
$key = $_POST['key'];
$action = $_POST['action']; 


// change "teste" for "main"
$command = "teste $text $key $action 2>&1";
$result = shell_exec($command);

$response = array(
    "action" => $action == 1 ? 'crypyo' : 'decrypto',
    "key" => $key,
    "text" => $text,
    "output" => trim($result)
);

echo json_encode($response);
?>