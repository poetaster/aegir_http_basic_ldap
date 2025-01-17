<?php


/**
 * @file
 *   The hosting feature definition for HTTP basic authentication.
 */

/**
 * Register a hosting feature with Aegir.
 *
 * This will be used to generate the 'admin/hosting' page.
 *
 * @return array
 *  associative array indexed by feature key.
 */
function hosting_http_basic_auth_ldap_hosting_feature() {
  $features['http_basic_auth_ldap'] = array(
    // title to display in form
    'title' => t('HTTP Basic Ldap Authentication'),
    // description
    'description' => t('Allows admins to specify HTTP basic ldap authentication for sites.'),
    'status' => HOSTING_FEATURE_DISABLED,
    // module to enable/disable alongside feature
    'module' => 'hosting_http_basic_auth_ldap',
    // which group to display in ( null , experimental )
    'group' => 'experimental'
    );
  return $features;
}

