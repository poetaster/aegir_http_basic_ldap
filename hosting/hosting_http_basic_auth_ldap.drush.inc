<?php

/**
 * Implementation of hook_hosting_site_context_options().
 */
function hosting_http_basic_auth_ldap_hosting_site_context_options(&$task) {
  if (isset($task->ref->http_basic_auth_ldap_server) && !empty($task->ref->http_basic_auth_ldap_server)) {
    $task->context_options['http_basic_auth_ldap_server'] = $task->ref->http_basic_auth_ldap_server;
    $task->context_options['http_basic_auth_ldap_require'] = $task->ref->http_basic_auth_ldap_require;
    $task->context_options['http_basic_auth_ldap_message'] = $task->ref->http_basic_auth_ldap_message;
  }
  else {
    $task->context_options['http_basic_auth_ldap_server'] = 'null';
    $task->context_options['http_basic_auth_ldap_require'] = 'null';
    $task->context_options['http_basic_auth_ldap_message'] = 'null';
  }
}

/**
 * Implementation of hook_drush_context_import().
 */
function hosting_http_basic_auth_ldap_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    if (isset($context->http_basic_auth_ldap_server) && !empty($context->http_basic_auth_ldap_server)) {
      $node->http_basic_auth_ldap_server = $context->http_basic_auth_ldap_server;
      $node->http_basic_auth_ldap_require = $context->http_basic_auth_ldap_require;
      $node->http_basic_auth_ldap_message = $context->http_basic_auth_ldap_message;
    }
  }

}
