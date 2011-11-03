<?php
/**
 * a bit of a hack. this active version is for aegir
 * in a ~/.drush context include_once(dirname(__FILE__) . '/../provision.service.inc');
 */

include_once('/usr/share/drush/commands/provision/provision.service.inc');

/**
 * Expose the service type this extension defines to provision.
 *
 * @return
 *   An array with the service type the key, and the default implementation the value.
 */
function http_basic_auth_ldap_provision_services() {
  return array('http_basic_auth_ldap' => NULL);
}

/**
 * The subfolder service base class.
 */
class provisionService_http_basic_auth_ldap extends provisionService {
  public $service = 'http_basic_auth_ldap';

  /**
   * Add the subfolder_path property to the site context.
   */
  static function subscribe_site($context) {
    $context->setProperty('http_basic_auth_ldap_server');
    $context->setProperty('http_basic_auth_ldap_require');
    $context->setProperty('http_basic_auth_ldap_message');
  }
}


/*
 * Implementation of hook_provision_apache_vhost_config()
 */
function http_basic_auth_ldap_provision_apache_vhost_config($uri, $data) {
  $lines = array();
  $server = d()->http_basic_auth_ldap_server;
  $require = d()->http_basic_auth_ldap_require;

  if (!empty($server) && !empty($require)) {
    // Now add config to the vhost:
    $root = d()->root;
    $message = !empty(d()->http_basic_auth_ldap_message) ? d()->http_basic_auth_ldap_message : dt('Restricted access');
    $lines[] = "  <Directory \"$root\">";
    $lines[] = "    AuthType Basic";
    $lines[] = "    AuthName \"$message\"";
    $lines[] = "    AuthBasicProvider ldap";
    $lines[] = "    AuthLDAPURL \"$server\"";
    $lines[] = "    Require \"$require\"";
    $lines[] = "    AuthzLDAPAuthoritative on";
    $lines[] = "  </Directory>";
  }

  return implode("\n", $lines);
}
/*
 * Implementation of !FIX ME hook_provision_nginx_vhost_config()
 */
function http_basic_auth_ldap_provision_nginx_vhost_config($uri, $data) {
  $lines = array();
  $server = d()->http_basic_auth_ldap_server;
  $require = d()->http_basic_auth_ldap_require;

  if (!empty($server) && !empty($require)) {
    // Create the password file.
    $path = _http_basic_auth_ldap_create_file($uri, $data, $server, $require);

    // Now add the file to the vhost:
    $root = d()->root;
    $message = !empty(d()->http_basic_auth_ldap_message) ? d()->http_basic_auth_ldap_message : dt('Restricted access');
    $lines[] = "auth_basic \"$message\";";
    $lines[] = "auth_basic_user_file $path;";
    $lines[] = "";
  }

  return implode("\n", $lines);
}
