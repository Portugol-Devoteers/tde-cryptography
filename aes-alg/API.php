<?php
$text = $_POST['text'];
$key = $_POST['key'];
$action = $_POST['action']; 

$command = "main --text \"$text\" --key \"$key\" --action ".intval($action)." 2>&1";

$result = exec($command);
$response = [
    "action" => intval($action),
    "key" => $key,
    "text" => $text,
    "output" => $result
];

echo json_encode($response);
?>