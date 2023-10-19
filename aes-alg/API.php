<?php
$text = $_POST['text'];
$key = $_POST['key'];
$action = $_POST['action']; 

$action = $action == 1 ? "Encripter" : "aaaaa";
// change "teste" for "main"
$command = "$action $text $key 2>&1";
$result = exec($command);

$response = [
    "action" => $action,
    "key" => $key,
    "text" => $text,
    "output" => $result
];

echo json_encode($response);
?>