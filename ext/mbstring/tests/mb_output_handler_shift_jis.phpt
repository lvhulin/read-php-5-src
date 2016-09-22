--TEST--
mb_output_handler() (Shift_JIS)
--SKIPIF--
<?php extension_loaded('mbstring') or die('skip mbstring not available'); ?>
--INI--
output_handler=mb_output_handler
mbstring.internal_encoding=Shift_JIS
mbstring.http_output=EUC-JP
--FILE--
<?php
// Shift_JIS
var_dump("テスト用日本語文字列。このモジュールはPHPにマルチバイト関数を提供します。");
?>

--EXPECT--
string(73) "･ﾆ･ｹ･ﾈﾍﾑﾆ�ﾋﾜｸ�ﾊｸｻ�ﾎ�｡｣､ｳ､ﾎ･筵ｸ･蝪ｼ･�､ﾏPHP､ﾋ･ﾞ･�･ﾁ･ﾐ･､･ﾈｴﾘｿ�､�ﾄ�ｶ｡､ｷ､ﾞ､ｹ｡｣"
