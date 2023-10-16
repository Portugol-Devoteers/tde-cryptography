<?php
$text = $_POST['text'];
$key = $_POST['key'];
$action = $_POST['action']; 


// change "teste" for "main"
$command = "teste $text $key $action 2>&1";
$result = exec($command);

$response = [
    "action" => $action == 1 ? 'crypto' : 'decrypto',
    "key" => $key,
    "text" => $text,
    "output" => base64_encode(trim($result))
];

echo json_encode($response);
?>