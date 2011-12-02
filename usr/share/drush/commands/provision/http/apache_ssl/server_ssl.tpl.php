  NameVirtualHost <?php print "*:" . $http_ssl_port . "\n"; ?>

<IfModule !ssl_module>
  LoadModule ssl_module modules/mod_ssl.so
</IfModule>

<?php include('http/apache/server.tpl.php'); ?>
